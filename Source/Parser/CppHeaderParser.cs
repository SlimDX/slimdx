// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using Boost.Wave;
using SlimDX2.Tools.XIDL;

namespace SlimDX.Parser
{
    /// <summary>
    /// A class to parse DirectX headers.
    /// </summary>
    public class CppHeaderParser : PreProcessCallbackBase
    {
        private readonly Dictionary<string, CppInterface> declaredInterface = new Dictionary<string, CppInterface>();

        private readonly CppIncludeGroup includeGroup;
        private readonly Stack<CppInclude> includeStack;
        private readonly Dictionary<string, List<Token>> mapIncludeToTokens;
        private readonly Dictionary<string, string> nameToValue = new Dictionary<string, string>();

        private readonly CppInclude rootInclude;
        private int currentIndex;
        private List<Token> tokens;
        private Guid currentInterfaceGuid;

        public CppHeaderParser()
        {
            rootInclude = new CppInclude();
            mapIncludeToTokens = new Dictionary<string, List<Token>>();
            includeGroup = new CppIncludeGroup();
            IncludesToProcess = new List<string>();
            includeStack = new Stack<CppInclude>();
            tokens = new List<Token>();
            IncludePath = new List<string>();

            // Register IUnknown in order to find inheritance
            // And remove duplicated methods
            var iUnknownInterface = new CppInterface();
            iUnknownInterface.Name = "IUnknown";
            var queryMethod = new CppMethod {Name = "QueryInterface"};
            queryMethod.Add(new CppParameter());
            queryMethod.Add(new CppParameter());
            iUnknownInterface.Add(queryMethod);
            iUnknownInterface.Add(new CppMethod {Name = "AddRef"});
            iUnknownInterface.Add(new CppMethod {Name = "Release"});
            declaredInterface.Add(iUnknownInterface.Name, iUnknownInterface);
        }

        /// <summary>
        /// Attached IncludeGroup
        /// </summary>
        public CppIncludeGroup IncludeGroup
        {
            get { return includeGroup; }
        }

        /// <summary>
        /// Include path used to search DirectX headers
        /// </summary>
        public List<string> IncludePath { get; set; }

        /// <summary>
        /// Add an include to process (without any path)
        /// </summary>
        /// <param name="include">an include filename to process</param>
        public void AddInclude(string include)
        {
            bool isFileExist = false;
            foreach (var includeDir in IncludePath)
            {
                string fullPath = includeDir + Path.DirectorySeparatorChar + include;
                if (File.Exists(fullPath))
                {
                    isFileExist = true;
                    break;
                }                
            }
            if (!isFileExist)
                throw new ArgumentException(string.Format("include [{0}] cannot be found from include path [{1}]",
                                                          include, IncludePath));

            IncludesToProcess.Add(Path.GetFileName(include).ToLower());
        }

        /// <summary>
        /// Run the preprocessor
        /// </summary>
        public void Run()
        {

            // Create a fake include that contains #include directives for the include to process
            string header = "";
            foreach (string includeName in IncludesToProcess)
                header += "#include \"" + includeName + "\"\n";

            var preProcessor = new PreProcessor(header, "root.h", this);

            // Add an include path to Boost.Wave
            foreach (var includeDir in IncludePath)
            {
                preProcessor.AddIncludePath(includeDir);
            }

            // Predefines macros
            preProcessor.DefineMacro("LF_FACESIZE=32", true);
            preProcessor.DefineMacro("D3D11_NO_HELPERS=1", true);
            preProcessor.DefineMacro("D3D10_NO_HELPERS=1", true);
            preProcessor.DefineMacro("CONST=const", true);
            preProcessor.DefineMacro("LPRECT=RECT *", true);
            preProcessor.DefineMacro("LPCSTR=const char *", true);
            preProcessor.DefineMacro("__RPCNDR_H_VERSION__=1", true);
            preProcessor.DefineMacro("__REQUIRED_RPCNDR_H_VERSION__=475", true);
            preProcessor.DefineMacro("__REQUIRED_RPCSAL_H_VERSION__=100", true);
            preProcessor.DefineMacro("__SAL_H_FULL_VER=140050727", true);
            preProcessor.DefineMacro("LPVOID=void*", true);
            preProcessor.DefineMacro("LPCSTR=const char*", true);
            preProcessor.DefineMacro("LPCWSTR=const wchar*", true);
            preProcessor.DefineMacro("DECLARE_HANDLE(name)=", true);
            preProcessor.DefineMacro("__reserved=", true);
            preProcessor.DefineMacro("WCHAR=wchar", true);
            preProcessor.DefineMacro("STDMETHOD(method)=virtual HRESULT __stdcall method", true);
            preProcessor.DefineMacro("STDMETHOD_(type,method)=virtual type __stdcall method", true);

            preProcessor.DefineMacro("__DEFINE_GUID__(value)=", true);

            // Interface declaration
            // MIDL_INTERFACE("9B7E4C00-342C-4106-A19F-4F2704F689F0") ID3D10DeviceChild : public IUnknown
            preProcessor.DefineMacro("MIDL_INTERFACE(guid)=interface __DEFINE_GUID__(guid)", true);
            preProcessor.DefineMacro("DECLARE_INTERFACE(name)=interface name ", true);
            preProcessor.DefineMacro("DECLARE_INTERFACE_(name,parent)=interface name : public parent ", true);
            preProcessor.DefineMacro("D2D1_DECLARE_INTERFACE(guid)=__DEFINE_GUID__(guid)", true);
            preProcessor.DefineMacro("DWRITE_DECLARE_INTERFACE(guid)=__DEFINE_GUID__(guid)", true);
            preProcessor.DefineMacro("DECLSPEC_UUID(guid)=__DEFINE_GUID__(guid)", true);
            preProcessor.DefineMacro("DECLSPEC_NOVTABLE=", true);

            // Macro to transform a old COM interface declaration (DECLARE_INTERFACE) to the new format (MIDL_INTERFACE)
            preProcessor.DefineMacro("PURE==0", true);
            preProcessor.DefineMacro("THIS_=", true);
            preProcessor.DefineMacro("THIS=void", true);
            preProcessor.DefineMacro("__field_ecount_opt(x)=", true);
            preProcessor.DefineMacro("DEFINE_ENUM_FLAG_OPERATORS(x)=", true);
            // Hook the DEFINE_GUID to catch the OnDefineMacro event
            preProcessor.DefineMacro("DEFINE_IID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)=", true);
            preProcessor.DefineMacro("DEFINE_CLSID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)=", true);
            preProcessor.DefineMacro("DEFINE_GUID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)=", true);
            // Make possible to parse HRESULT macros
            preProcessor.DefineMacro("MAKE_HRESULT(sev,fac,code)=( ((sev)<<31) | ((fac)<<16) | (code) )", true);

            // D3D9
            preProcessor.DefineMacro("D3DVECTOR_DEFINED=", true);
            preProcessor.DefineMacro("D3DCOLORVALUE_DEFINED=", true);
            preProcessor.DefineMacro("D3DRECT_DEFINED=", true);
            preProcessor.DefineMacro("D3DMATRIX_DEFINED=", true);
            preProcessor.DefineMacro("D3DVECTOR_DEFINED=", true);
            preProcessor.DefineMacro("MAX_FVF_DECL_SIZE=65",true);
            preProcessor.DefineMacro("WOW64_ENUM_WORKAROUND=", true);
            preProcessor.DefineMacro("STDAPI=HRESULT WINAPI", true);

            // DWrite macros
            preProcessor.DefineMacro("DWRITE_EXPORT=WINAPI", true);
            preProcessor.DefineMacro("DEFINE_ENUM_FLAG_OPERATORS(x)=", true);
            preProcessor.DefineMacro("EXTERN_C=", true);            
            preProcessor.Run();

            // Remove all empty includes
            IncludeGroup.InnerElements.RemoveAll( include => include.InnerElements.Count == 0);
        }

        // ------------------------------------------------------------------------------------------
        #region // Implements methods from PreProcessCallbackBase to parse all tokens returned by Boost.Wav
        // ------------------------------------------------------------------------------------------
        
        /// <summary>
        /// Called for each tokens processed
        /// </summary>
        /// <param name="token"></param>
        public override void OnToken(Token token)
        {
            if (token.Id == TokenId.Eof)
                return;

            // Filter Space token
            if (!IsTokenSpace(token))
            {
                List<Token> tokenList = mapIncludeToTokens[CurrentInclude.Name];

                if (tokenList.Count > 0 && tokenList[tokenList.Count-1].Id == TokenId.Special1 && token.Value == "interface")
                    mapIncludeToTokens[CurrentInclude.Name].Insert(tokenList.Count-1, token);
                else
                    mapIncludeToTokens[CurrentInclude.Name].Add(token);
            }
        }

        /// <summary>
        /// Called before an include is going to be processed
        /// </summary>
        /// <param name="name"></param>
        public override void OnIncludBegin(string name)
        {
            string includeName = GetNameFromInclude(name);

            // Update the current include stack
            includeStack.Push(FindOrCreateInclude(includeName));

            // Create tokens for the current include
            if (!mapIncludeToTokens.TryGetValue(includeName, out tokens))
            {
                tokens = new List<Token>();
                mapIncludeToTokens.Add(includeName, tokens);
            }
        }

        /// <summary>
        /// Called when Boost.Wave is asking to load a particular include
        /// </summary>
        /// <param name="name"></param>
        /// <returns>the include file as a sttring</returns>
        public override string OnIncludeLoad(string name)
        {
            try
            {

                // Process only files that needs to be processed
                if (IncludesToProcess.Contains(Path.GetFileName(name)))
                    return LoadInclude(name);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
            }
            // Empty
            return "\r\n\r\n\r\n\r\n";
        }

        private string LoadInclude(string name)
        {
            StreamReader reader = new StreamReader(name, true);
            StringBuilder builder = new StringBuilder();

            string line;

            Regex matchPragma = new Regex(@"^\s*#(pragma\s+pack.*)");

            while ((line = reader.ReadLine()) != null)
            {
                if (matchPragma.Match(line).Success)
                {
                    // Make pragma as regular statement
                    line = matchPragma.Replace(line, "$1") + "\n;"; // << Important : put a \n before ";" as "$1" could contains comment line // that would comment the ;
                }
                builder.Append(line);
                builder.Append("\n");
            }
            return builder.ToString();
        }

        /// <summary>
        /// Called after an include has been processed
        /// </summary>
        public override void OnIncludEnd()
        {
            currentIndex = 0;
            tokens = mapIncludeToTokens[CurrentInclude.Name];

            Console.Out.WriteLine("Begin Process Include {0}", CurrentInclude.Name);
            bool isParsed = false;

            // If there are any tokens, start parsing
            if (!IsEndOfToken)
            {
                try
                {
                    Parse();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex);
                    Environment.Exit(1);
                }
                isParsed = true;
            }
            Console.Out.WriteLine("End Process Include {0}", CurrentInclude.Name);

            CppInclude lastIncluded = includeStack.Pop();

            // Add a dependency
            if (isParsed)
                CurrentInclude.Add(new CppDependency { Name = lastIncluded.Name });

            // Clear tokens for current stack
            tokens.Clear();
        }

        /// <summary>
        /// Called when a macro is being defined
        /// </summary>
        /// <param name="macroDefinition"></param>
        public override void OnMacroDefine(MacroDefinition macroDefinition)
        {
            // Only register MacroDefinition without any parameters
            if (macroDefinition.ParameterNames.Count == 0 && macroDefinition.Name != "INTERFACE")
            {
                var cppMacroDefinition = new CppMacroDefinition();
                cppMacroDefinition.Name = macroDefinition.Name;
                foreach (Token token in macroDefinition.Body)
                {
                    cppMacroDefinition.Value += token.Value;
                }
                if (!string.IsNullOrWhiteSpace(cppMacroDefinition.Value))
                    CurrentInclude.Add(cppMacroDefinition);
            }
        }

        /// <summary>
        /// Called when a macro is undefined. This is not used.
        /// </summary>
        /// <param name="name"></param>
        public override void OnMacroUndef(string name)
        {
            //Console.Out.WriteLine("OnMacroUndef {0}", name);
        }


        private uint ConvertMacroNumber(MacroFunctionCall.MacroArgument arg)
        {
            string str;
            try
            {
                str = arg.RawValue.Trim();
                str = str.Replace("L", "");
                str = str.Replace("U", "");
                return Convert.ToUInt32(str, 16);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Unable to parse Macro {0} to unsigned int.",ex);
                throw;
            }
        }

        /// <summary>
        /// Called when a macro is expanded. Used for parsing GUID
        /// </summary>
        /// <param name="macroFunctionCall"></param>
        public override void OnMacroFunctionExpand(MacroFunctionCall macroFunctionCall)
        {
            if (macroFunctionCall.Name == "DEFINE_GUID" || macroFunctionCall.Name == "DEFINE_CLSID" || macroFunctionCall.Name == "DEFINE_IID" )
            {
                uint value1 = ConvertMacroNumber(macroFunctionCall.Arguments[1]);
                ushort value2 = (ushort)ConvertMacroNumber(macroFunctionCall.Arguments[2]);
                ushort value3 = (ushort)ConvertMacroNumber(macroFunctionCall.Arguments[3]);
                byte value4 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[4]);
                byte value5 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[5]);
                byte value6 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[6]);
                byte value7 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[7]);
                byte value8 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[8]);
                byte value9 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[9]);
                byte value10 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[10]);
                byte value11 = (byte)ConvertMacroNumber(macroFunctionCall.Arguments[11]);

                // Add a guid to the current include
                var cppGuid = new CppGuid();
                cppGuid.Guid = new Guid(value1, value2, value3, value4, value5, value6, value7, value8, value9, value10,
                                        value11);
                switch (macroFunctionCall.Name)
                {
                    case "DEFINE_GUID":
                        cppGuid.Name = macroFunctionCall.Arguments[0].RawValue.Trim();
                        break;
                    case "DEFINE_CLSID":
                        cppGuid.Name = "CLSID_" + macroFunctionCall.Arguments[0].RawValue.Trim();
                        break;
                    case "DEFINE_IID":
                        cppGuid.Name = "IID_" + macroFunctionCall.Arguments[0].RawValue.Trim();
                        break;
                }

                CurrentInclude.Add(cppGuid);
            }
            else if (macroFunctionCall.Name == "__DEFINE_GUID__")
            {
                Token token = new Token();
                token.Id = TokenId.Special1;
                token.Value = macroFunctionCall.Arguments[0].RawValue;

                mapIncludeToTokens[CurrentInclude.Name].Add(token);
            }
        }

        public override void OnLogException(WaveExceptionSeverity severity, WaveExceptionErrorCode errorCode,
                                            string message)
        {
            //Console.Out.WriteLine("OnLogException {0},{1},{2}", severity, errorCode, message);
        }
        #endregion
        // ------------------------------------------------------------------------------------------

        /// <summary>
        /// Return true if token is considered as a space
        /// </summary>
        /// <param name="token"></param>
        /// <returns>true if token is a space</returns>
        private bool IsTokenSpace(Token token)
        {
            switch (token.Id)
            {
                case TokenId.Space:
                case TokenId.Cppcomment:
                case TokenId.Ccomment:
                    return true;
            }
            return false;
        }
        
        /// <summary>
        /// Current Include being processed in the stack
        /// </summary>
        private CppInclude CurrentInclude
        {
            get
            {
                if (includeStack.Count == 0)
                    return rootInclude;
                return includeStack.Peek();
            }
        }

        /// <summary>
        /// List of includes to process
        /// </summary>
        private List<string> IncludesToProcess { get; set; }


        /// <summary>
        /// Current token being processed. May return null if no tokens
        /// </summary>
        private Token CurrentToken
        {
            get
            {
                if (currentIndex < 0 || currentIndex >= tokens.Count)
                    return null;
                return tokens[currentIndex];
            }
        }

        /// <summary>
        /// Return true if no more tokens
        /// </summary>
        private bool IsEndOfToken
        {
            get { return CurrentToken == null; }
        }

        /// <summary>
        /// Get include name from filename. For example: D3D11.h returns d3d11
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        private string GetNameFromInclude(string fileName)
        {
            return Path.GetFileNameWithoutExtension(fileName).ToLower();
        }

        /// <summary>
        /// Return the CppInlucde from an include name
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private CppInclude FindOrCreateInclude(string name)
        {
            foreach (CppInclude include in includeGroup.Includes)
            {
                if (include.Name == name)
                    return include;
            }
            var includeToReturn = new CppInclude {Name = name};
            includeGroup.Add(includeToReturn);
            return includeToReturn;
        }

        /// <summary>
        /// Go to next available token
        /// </summary>
        private void ReadNextToken()
        {
            if (currentIndex == tokens.Count)
            {
                return;
            }
            currentIndex++;
        }

        /// <summary>
        /// Returns the next token without taking it
        /// </summary>
        /// <returns>next token to be read</returns>
        private Token PreviewNextToken()
        {
            return GetTokenFrom(1);
        }

        /// <summary>
        /// Returns the value of the next token
        /// </summary>
        /// <returns>value of the next token</returns>
        private string PreviewNextTokenValue()
        {
            Token token = GetTokenFrom(1);
            if (token == null)
                token = CurrentToken;
            if (token == null)
                return null;
            return token.Value;
        }

        /// <summary>
        /// Preview a token from a relative position
        /// </summary>
        /// <param name="relativePosition"></param>
        /// <returns></returns>
        private Token GetTokenFrom(int relativePosition)
        {
            int index = currentIndex + relativePosition;
            if (index < 0 || index >= tokens.Count)
                return null;
            return tokens[index];
        }

        /// <summary>
        /// Skip until one of the tokensToFind is found
        /// </summary>
        /// <param name="tokensToFind">tokens to find</param>
        private void SkipUntilTokenId(params TokenId[] tokensToFind)
        {
            while (CurrentToken != null)
            {
                if (tokensToFind.Any(t => t == CurrentToken.Id))
                    return;
                ReadNextToken();
            }
        }

        /// <summary>
        /// Return true if next statements are probably a function
        /// </summary>
        /// <returns></returns>
        private bool IsProbablyFunction()
        {
            int position = 0;
            int count = 0;
            do
            {
                Token token = GetTokenFrom(position);
                if (token == null)
                    break;
                if (token.Id == TokenId.Leftparen)
                    count++;
                else if (token.Id == TokenId.Rightparen)
                    count--;
                else if (token.Id == TokenId.Leftbrace)
                    break;
                else if (token.Id == TokenId.Semicolon)
                {
                    if (GetTokenFrom(position - 1).Id == TokenId.Rightparen)
                    {
                        return true;
                    }
                }
                position++;
            } while (true);
            return false;
        }


        /// <summary>
        /// Go to next Cpp statement
        /// </summary>
        /// <param name="rightBraceFollowedByNoSemiColon">if true, this will stop after a rightbrace } with 
        /// no expected semi colon after. This is used for handling extern "C" {}</param>
        private void NextStatement()
        {
            int count = 0;
            bool breakOnLastBrace = false;
            while (CurrentToken != null)
            {
                if (CurrentToken.Id == TokenId.Leftbrace)
                    count++;
                else if (CurrentToken.Id == TokenId.Rightbrace)
                {
                    // If orphan rightbrace, then go as next statement (need to better handle extern "C" {})
                    if (count == 0)
                        break;
                    count--;
                }
                else if (CurrentToken.Id == TokenId.Semicolon)
                {
                    if (count > 0 && !breakOnLastBrace)
                        breakOnLastBrace = true;
                    else if (!breakOnLastBrace)
                        break;
                }
                if (count == 0 && breakOnLastBrace)
                    break;
                ReadNextToken();
            }

            // Stop on last SemiColon after right brace
            do
            {
                if (PreviewNextToken() != null && PreviewNextToken().Id == TokenId.Semicolon)
                    ReadNextToken();
                else
                    break;
            } while (true);
        }

        /// <summary>
        /// Parse an enum value
        /// </summary>
        /// <param name="map">already declared enum values for the enum being currently processed</param>
        /// <returns>a parsed enum value</returns>
        private string ParseEnumValue(Dictionary<string, string> map)
        {
            string value = "";

            do
            {
                TokenId nextId = PreviewNextToken().Id;
                if (nextId == TokenId.Comma || nextId == TokenId.Rightbrace)
                    break;

                ReadNextToken();

                if (nextId == TokenId.Intlit)
                {
                    string valueToParse = CurrentToken.Value;
                    // Remove L postfix if it's an integer
                    // TODO: check if it's necessary, as it is done also in XIDLToCsharp
                    valueToParse = valueToParse.Replace("L", "");
                    value += valueToParse;
                }
                else if (nextId == TokenId.Identifier)
                {
                    string inlineValue;
                    if (!map.TryGetValue(CurrentToken.Value, out inlineValue))
                        inlineValue = CurrentToken.Value;
                    value += inlineValue;
                }
                else
                {
                    value += CurrentToken.Value;
                }
            } while (true);
            return value;
        }

        /// <summary>
        /// Parse an enum from the current token
        /// </summary>
        private CppEnum ParseEnum()
        {
            string enumName = "";
            // Handle anonymous enums
            if (PreviewNextToken().Id == TokenId.Leftbrace)
            {
                int enumCount = CurrentInclude.Find<CppEnum>(".*").Count();
                enumName = CurrentInclude.Name.ToUpper() + "_ENUM_" + enumCount;
            }
            else
            {
                ReadNextToken();
                enumName = CurrentToken.Value;
            }

            var cppEnum = new CppEnum();
            cppEnum.Name = enumName; // StripLeadingUnderscore(CurrentToken.Value);
            CurrentInclude.Add(cppEnum);

            SkipUntilTokenId(TokenId.Leftbrace);
            do
            {
                ReadNextToken();

                if (CurrentToken.Id == TokenId.Rightbrace)
                    break;

                var enumItem = new CppEnumItem();
                enumItem.Name = CurrentToken.Value;

                ReadNextToken();
                Token nextToken = CurrentToken;
                enumItem.Value = "";
                if (nextToken.Id == TokenId.Assign)
                {
                    enumItem.Value = ParseEnumValue(nameToValue);
                    enumItem.Value = Evaluator.EvalToString(enumItem.Value);
                    nameToValue.Add(enumItem.Name, enumItem.Value);
                }

                //// Skip FORCE enums
                //if (!enumItem.Name.EndsWith("FORCE_DWORD") && !enumItem.Name.EndsWith("FORCE_UINT"))
                cppEnum.Add(enumItem);

                SkipUntilTokenId(TokenId.Comma, TokenId.Rightbrace);
                if (CurrentToken.Id == TokenId.Rightbrace)
                    break;
            } while (true);

            // Parse Tokens
            // NextStatement();
            return cppEnum;
        }

        /// <summary>
        /// Return true if the token is a numeric (int,char,short,long)
        /// </summary>
        /// <param name="tokenId"></param>
        /// <returns></returns>
        private bool IsTokenNumeric(TokenId tokenId)
        {
            return (tokenId == TokenId.Char || tokenId == TokenId.Int || tokenId == TokenId.Short || tokenId == TokenId.Long);
        }

        /// <summary>
        /// Read a Type with an optional declaration
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="withDeclaration"></param>
        /// <returns></returns>
        private T ReadType<T>(bool withDeclaration) where T : CppType, new()
        {
            var cppType = new T();

            // if typedef XXX (api_calling_convention )  => this is more likely to be a function declaration
            if (PreviewNextToken().Id == TokenId.Leftparen)
            {
                ReadNextToken(); // CurrentToken => (

               do {
                   ReadNextToken(); // Current
                   if (CurrentToken.Id == TokenId.Rightparen)
                   {
                       cppType.Name = GetTokenFrom(-1).Value;
                       break;
                   }

                   if (CurrentToken.Value == "__stdcall" || CurrentToken.Value == "__cdecl")
                       cppType.Type = "__function" + CurrentToken.Value;
                   else if (CurrentToken.Id == TokenId.Star)
                        cppType.Specifier += "*";

                } while (true);
               
                if (PreviewNextToken().Id != TokenId.Leftparen)
                   throw new ArgumentException(string.Format("Unable to parse type {0}. Expecting a function declaration with (", cppType));
               SkipNextParenthesis();

                return cppType;
            }

            if (CurrentToken.Id == TokenId.Const)
            {
                cppType.Const = true;
                ReadNextToken();
            }
            // Skip token if enum or struct or interface
            if (CurrentToken.Id == TokenId.Enum || CurrentToken.Id == TokenId.Struct ||
                (CurrentToken.Value == "interface"))
            {
                ReadNextToken();
            }

            string type;
            // Handle unsigned
            if (CurrentToken.Id == TokenId.Unsigned)
            {
                ReadNextToken();
                // If next token is not numeric, unsigned default is int type
                if (IsTokenNumeric(CurrentToken.Id))
                {
                    type = CurrentToken.Value;
                }
                else
                {
                    type = "int";
                }
            }
            else
            {
                type = CurrentToken.Value;
            }

            // Get Type from token
            cppType.Type = type;
            cppType.Specifier = "";

            // Handles specifiers (const, pointers) and declaration
            do
            {
                // Skip name in nameless type declaration in method
                if (PreviewNextToken().Id == TokenId.Comma || PreviewNextToken().Id == TokenId.Rightparen)
                    break;

                // Handle Function declaration (skip them)
                if (PreviewNextToken().Id == TokenId.Leftparen)
                {
                    return null;
                }

                ReadNextToken();

                // Handle pointer specifiers
                if (CurrentToken.Id == TokenId.Star || CurrentToken.Id == TokenId.And)
                {
                    cppType.Specifier += "*";
                }
                else if (CurrentToken.Id == TokenId.Const)
                {
                    cppType.Const = true;
                }
                else
                {
                    if (withDeclaration)
                    {
                        if (CurrentToken.Id != TokenId.Identifier)
                            throw new ArgumentException("Expecting identifier followed in type [" + CurrentToken.Value + "]");

                        cppType.Name = CurrentToken.Value;

                        string arrayDimension = null;
                        while (PreviewNextToken().Id == TokenId.Leftbracket)
                        {
                            // Read Left [
                            ReadNextToken();
                            cppType.IsArray = true;
                            string localDimension = ReadStringUpTo(TokenId.Rightbracket);
                            arrayDimension = (arrayDimension == null)
                                                 ? localDimension
                                                 : arrayDimension + "," + localDimension;
                        }
                        if (cppType.IsArray)
                            cppType.ArrayDimension = Evaluator.EvalToString(arrayDimension);
                    }
                    break;
                }
            } while (true);
            return cppType;
        }

        /// <summary>
        /// Returns a string from the token stream until a particular token is find
        /// </summary>
        /// <param name="id"></param>
        /// <returns>a string from the tokens</returns>
        private string ReadStringUpTo(TokenId id)
        {
            var builder = new StringBuilder();
            do
            {
                ReadNextToken();
                if (CurrentToken.Id == id)
                    break;
                builder.Append(CurrentToken.Value);
            } while (true);
            return builder.ToString();
        }

        /// <summary>
        /// Parse a calling convention
        /// </summary>
        /// <param name="value">a string representation of the calling convention</param>
        /// <returns>enum CallingConvention</returns>
        private static CppCallingConvention ParseCallingConvention(string value)
        {
            switch (value)
            {
                case "__stdcall":
                    return CppCallingConvention.StdCall;
                default:
                    return CppCallingConvention.Unknown;
            }
        }

        /// <summary>
        /// Read simple structure field
        /// </summary>
        /// <param name="fieldOffset"></param>
        /// <returns></returns>
        private CppField ReadStructField(CppStruct cppStruct, ref int fieldOffset)
        {
            CppAttribute attribute = ReadAnnotation();
            var field = ReadType<CppField>(true);

            bool goToNextFieldOffset = true;

            // If colon, then this is a bitfield
            if (PreviewNextToken().Id == TokenId.Colon)
            {
                // Set bitfield for struct
                field.IsBitField = true;

                ReadNextToken();    // Skip ":"
                ReadNextToken();    // => CurrentToken is bitoffset
                int bitOffset;

                // TODO handle bitoffset of 0!
                if (int.TryParse(CurrentToken.Value, out bitOffset))
                {
                    field.BitOffset = bitOffset;
                    if (bitOffset != 0)
                        goToNextFieldOffset = false;
                }
                else
                {
                    throw new ArgumentException(string.Format("Expecting integer literal for field {0}",field.Name));
                }
            }
            field.Offset = fieldOffset;
            if (goToNextFieldOffset)
                fieldOffset++;
            NextStatement();
            return field;
        }

        /// <summary>
        /// Parse a struct from current token stream
        /// </summary>
        private CppStruct ParseStruct(bool isAnonymousStruct = false, CppStruct parentStruct = null)
        {
            var cppStruct = new CppStruct();

            if (!isAnonymousStruct)
            {
                ReadNextToken();
                cppStruct.Name = CurrentToken.Value; // StripLeadingUnderscore(CurrentToken.Value);
            }
            else
            {
                cppStruct.Name = parentStruct.Name + "Inner";
            }
            CurrentInclude.Add(cppStruct);

            cppStruct.Pack = _currentPackingValue;

            // Skip to structure fields declaration
            SkipUntilTokenId(TokenId.Leftbrace);

            int fieldOffset = 0;


            // Iterate on fields
            do
            {
                ReadNextToken();

                Token type = CurrentToken;
                if (type.Id == TokenId.Rightbrace)
                    break;

                // Handle anonymous struct
                if (type.Id == TokenId.Struct)
                {
                    CppField cppField;
                    if (PreviewNextToken().Value == cppStruct.Name)
                    {
                        ReadNextToken();
                        cppField = ReadStructField(cppStruct, ref fieldOffset);
                    }
                    else
                    {
                        CppStruct innerStruct = ParseStruct(true, cppStruct);
                        NextStatement();
                        cppField = new CppField {Type = innerStruct.Name, Name = "_anonymous_field_", Offset = fieldOffset};
                    }
                    cppStruct.Add(cppField);
                }
                else if (type.Id == TokenId.Union)
                {
                    // Handle union
                    SkipUntilTokenId(TokenId.Leftbrace);

                    int unionFieldOffset;
                    do
                    {
                        // Force field offset for an union to be the same
                        unionFieldOffset = fieldOffset;
                        ReadNextToken();
                        type = CurrentToken;

                        // Handle inner struct inside union (!)
                        if (type.Id == TokenId.Struct)
                        {
                            CppField cppField;
                            if (PreviewNextToken().Value == cppStruct.Name)
                            {
                                ReadNextToken();
                                cppField = ReadStructField(cppStruct, ref unionFieldOffset);
                            }
                            else
                            {
                                CppStruct innerStruct = ParseStruct(true, cppStruct);
                                NextStatement();
                                cppField = new CppField { Type = innerStruct.Name, Name = "_anonymous_field_", Offset = fieldOffset };
                            }
                            cppStruct.Add(cppField);
                        }
                        else if (type.Id == TokenId.Rightbrace)
                            break;
                        else
                            cppStruct.Add(ReadStructField(cppStruct, ref unionFieldOffset));
                    } while (true);
                    // For union, go to next field at the end of the union
                    fieldOffset++;
                    NextStatement();
                }
                else if (PreviewNextToken().Id == TokenId.Leftparen && !CurrentToken.Value.StartsWith("__"))
                {
                    // Skip Constructor
                    SkipUntilTokenId(TokenId.Rightbrace);
                }
                else
                {
                    // Else Read Struct Field declaration
                    cppStruct.Add(ReadStructField(cppStruct, ref fieldOffset));
                }
            } while (true);

            //NextStatement();

            //var newTypeDef = new CppTypedef();

            //// Create default "LP and LPC" typedefs
            //// This is just in case we did not catch them 
            //// from a typedef struct declaration

            //// Add default pointer to struct
            //newTypeDef.Name = "LP" + cppStruct.Name;
            //newTypeDef.Specifier = "*";
            //newTypeDef.IsArray = false;
            //newTypeDef.Const = false;
            //newTypeDef.Type = cppStruct.Name;
            //AddTypeDef(newTypeDef);

            //newTypeDef = new CppTypedef();
            //// Add default const pointer to struct
            //newTypeDef.Name = "LPC" + cppStruct.Name;
            //newTypeDef.Specifier = "*";
            //newTypeDef.IsArray = false;
            //newTypeDef.Const = true;
            //newTypeDef.Type = cppStruct.Name;
            //AddTypeDef(newTypeDef);
            return cppStruct;
        }

        /// <summary>
        /// Parse a virtual method
        /// </summary>
        /// <returns></returns>
        private CppMethod ParseVirtualMethod()
        {
            // Skip Virtual
            if (CurrentToken.Id == TokenId.Virtual)
                ReadNextToken();
            return ParseMethod();
        }

        /// <summary>
        /// Skip the next parenthesis from the token stream, corretly handling inner parenthesis.
        /// </summary>
        private void SkipNextParenthesis()
        {
            SkipMatchingBraces(TokenId.Leftparen, TokenId.Rightparen);
        }

        /// <summary>
        /// Skip matching brace from the token stream, corretly handling inner braces.
        /// </summary>
        /// <param name="leftParent">The left tokenId to match</param>
        /// <param name="rightParent">The right tokenId to match</param>
        /// <returns></returns>
        private void SkipMatchingBraces(TokenId leftParent, TokenId rightParent)
        {
            if (PreviewNextToken().Id == leftParent)
            {
                int count = 0;
                do
                {
                    ReadNextToken();
                    if (CurrentToken.Id == leftParent)
                        count++;
                    else if (CurrentToken.Id == rightParent)
                        count--;
                } while (count > 0);
            }
        }

        /// <summary>
        /// Read attributes annotation
        /// </summary>
        /// <returns></returns>
        private CppAttribute ReadAnnotation()
        {
            string annotation = CurrentToken.Value;

            // An annotation should start with __
            if (!annotation.StartsWith("__"))
                return CppAttribute.None;

            // Parse sub annotations part
            var subAnnotation = annotation.Substring(2).Split('_');

            CppAttribute attr = CppAttribute.None;

            foreach (string annotationPart in subAnnotation)
            {
                switch (annotationPart)
                {
                    case "in":
                        attr |= CppAttribute.In;
                        break;
                    case "out":
                        attr |= CppAttribute.Out;
                        break;
                    case "inout":
                        attr |= CppAttribute.InOut;
                        break;
                    case "opt":
                        attr |= CppAttribute.Optional;
                        break;
                    case "bcount":
                    case "ecount":
                        attr |= CppAttribute.Buffer;
                        break;
                }
            }

            SkipNextParenthesis();
            ReadNextToken();

            return attr;
        }

        /// <summary>
        /// Parse a method parameter
        /// </summary>
        /// <returns></returns>
        private CppParameter ParseMethodParameter()
        {
            CppAttribute attribute = ReadAnnotation();
            var methodArgument = ReadType<CppParameter>(true);
            methodArgument.Attribute = attribute;

            if (PreviewNextToken().Id == TokenId.Assign)
            {
                SkipUntilTokenId(TokenId.Comma, TokenId.Rightparen);

                // Go back to current token
                currentIndex--;
            }
            return methodArgument;
        }

        /// <summary>
        /// Parse a function
        /// </summary>
        private void ParseFunction()
        {
            var function = ParseGenericMethod<CppFunction>();
            if (function != null)
                CurrentInclude.Add(function);
        }

        /// <summary>
        /// Parse a method
        /// </summary>
        /// <returns></returns>
        private CppMethod ParseMethod()
        {
            return ParseGenericMethod<CppMethod>();
        }

        /// <summary>
        /// Generic function to parse a method (virtual method, method, function)
        /// </summary>
        /// <typeparam name="T">a type inheriting CppMethod</typeparam>
        /// <returns>the method or function</returns>
        private T ParseGenericMethod<T>() where T : CppMethod, new()
        {
            var method = new T();

            method.ReturnType = ReadType<CppType>(false);

            if (PreviewNextToken().Id != TokenId.Leftparen)
            {
                // Parse Calling Convention
                method.CallingConvention = ParseCallingConvention(CurrentToken.Value);

                // Skip STDMETHODCALLTYPE
                ReadNextToken();

                if (PreviewNextToken().Id != TokenId.Leftparen)
                {
                    Console.WriteLine("Unexpected token");
                }
            }


            // MethodName
            method.Name = CurrentToken.Value;

            SkipUntilTokenId(TokenId.Leftparen);

            do
            {
                ReadNextToken();
                if (CurrentToken.Id == TokenId.Rightparen)
                    break;

                // If single param is void, then no arguments
                if (CurrentToken.Id == TokenId.Void)
                {
                    if (PreviewNextToken().Id == TokenId.Rightparen)
                        break;
                }

                // If Comma then read next token
                if (CurrentToken.Id == TokenId.Comma)
                    ReadNextToken();

                CppParameter arg = ParseMethodParameter();
                // Parameter lest name
                if (arg.Name == null)
                {
                    arg.Name = "arg" + method.InnerElements.Count;                    
                }
                method.Add(arg);
            } while (true);


            // Check any body
            // If body, then method is skipped           
            do
            {
                ReadNextToken();
                if (CurrentToken.Id == TokenId.Semicolon)
                    break;
                if (CurrentToken.Id == TokenId.Leftbrace)
                {
                    currentIndex--;
                    SkipMatchingBraces(TokenId.Leftbrace, TokenId.Rightbrace);
                    return null;
                }
            } while (true);


            return method;
        }

        /// <summary>
        /// Remove leading score from a string
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private static string StripLeadingUnderscore(string name)
        {
            if (name.StartsWith("_"))
                name = name.Substring(1);
            return name;
        }

        private bool IsInterfaceFromCurrentToken()
        {
            if (CurrentToken == null)
                return false;
            bool value1 = (CurrentToken.Value == "interface" );
            if (PreviewNextToken() != null)
            {
                string name = PreviewNextToken().Value;
                if (CurrentToken.Id == TokenId.Struct && name.StartsWith("I"))
                    return true;
                return value1;
            }
            return false;
        }


        /// <summary>
        /// Parse an interface declaration
        /// </summary>
        private void ParseInterface()
        {
            if (IsInterfaceFromCurrentToken())
            {
                // Pre-Declare interface
                if (GetTokenFrom(2).Id == TokenId.Semicolon)
                {
                    return;
                }
            }

            string guid = null;

            // Read Interface Name
            ReadNextToken();
            if (CurrentToken.Id == TokenId.Special1)
            {
                guid = CurrentToken.RawValue;
                ReadNextToken();
            }

            string interfaceName = CurrentToken.Value;

            // Retreive any previously declared interface
            var cppInterface = CurrentInclude.FindFirst<CppInterface>("^" + interfaceName + "$");
            if (cppInterface == null)
            {
                cppInterface = new CppInterface();
                cppInterface.Name = interfaceName;
                CurrentInclude.Add(cppInterface);
                declaredInterface.Add(cppInterface.Name, cppInterface);
            }

            if (guid != null)
                cppInterface.Guid = guid;
            

            cppInterface.ParentName = "";

            // Read Inheritance
            ReadNextToken();
            if (CurrentToken.Id == TokenId.Colon)
            {
                ReadNextToken(); // public
                if (CurrentToken.Id != TokenId.Public)
                {
                    throw new ArgumentException("Exception public in interface parent " + cppInterface.Name);
                }

                ReadNextToken(); // inherited name
                cppInterface.ParentName = CurrentToken.Value;
            }

            if (CurrentToken.Id != TokenId.Semicolon)
            {
                // Until {
                SkipUntilTokenId(TokenId.Leftbrace);

                do
                {
                    ReadNextToken();
                    if (CurrentToken.Id == TokenId.Rightbrace)
                        break;
                    if (CurrentToken.Id == TokenId.Public)
                    {
                        // Consume public
                        ReadNextToken();
                        continue;
                    }

                    CppMethod method = ParseVirtualMethod();

                    // Method could be null if it has a body
                    if (method != null)
                        cppInterface.Add(method);
                } while (true);

                // Remove duplicate inheritance for old COM declaration
                RemoveDuplicateInheritance(cppInterface);
            }
            // Go to next statement
            NextStatement();

            //// Add pointer to interface
            //var newTypeDef = new CppTypedef();


            //string interfaceNameWithoutI = cppInterface.Name.StartsWith("I")
            //                                   ? cppInterface.Name.Substring(1)
            //                                   : cppInterface.Name;

            //// Add default pointer to struct
            //newTypeDef.Name = "LP" + interfaceNameWithoutI;
            //newTypeDef.Specifier = "*";
            //newTypeDef.IsArray = false;
            //newTypeDef.Const = false;
            //newTypeDef.Type = cppInterface.Name;
            //AddTypeDef(newTypeDef);

            //newTypeDef = new CppTypedef();
            //// Add default const pointer to struct
            //newTypeDef.Name = "LPC" + interfaceNameWithoutI;
            //newTypeDef.Specifier = "*";
            //newTypeDef.IsArray = false;
            //newTypeDef.Const = true;
            //newTypeDef.Type = cppInterface.Name;
            //AddTypeDef(newTypeDef);
        }

        /// <summary>
        /// Remove duplicated inherited methods that are presents in old interface declaration style.
        /// </summary>
        /// <param name = "rootInterface">the interface to process</param>
        private void RemoveDuplicateInheritance(CppInterface rootInterface)
        {
            var parents = new List<CppInterface>();

            int methodOffset = 0;

            // Look for Parents interfaces
            CppInterface parentInterface = rootInterface;
            do
            {
                string parentName = parentInterface.ParentName;
                parentInterface = null;
                if (!string.IsNullOrEmpty(parentName))
                {
                    if (declaredInterface.TryGetValue(parentName, out parentInterface))
                        parents.Add(parentInterface);
                }
            } while (parentInterface != null);

            // From older parents to newer parents
            parents.Reverse();

            // Iterate from older parents to newer parents
            foreach (CppInterface cppInterface in parents)
            {
                // If older parent has more methods than newer parents, then 
                // this interface doesn't have probably any duplicate methods
                if (cppInterface.InnerElements.Count > rootInterface.InnerElements.Count)
                {
                    break;
                }

                // Else, try to match duplicated methods
                for (int i = 0; i < cppInterface.InnerElements.Count; i++)
                {
                    var inheritedMethod = (CppMethod)cppInterface.InnerElements[i];
                    var inheritedMethodCountParam = inheritedMethod.Parameters.Count();
                    for(int j = rootInterface.InnerElements.Count-1; j >= 0; j--)
                    {
                        var derivedMethod = (CppMethod) rootInterface.InnerElements[j];
                        var derivedMethodCountParam = derivedMethod.Parameters.Count();
                        // TODO : better check the whole signature
                        if (inheritedMethod.Name == derivedMethod.Name && inheritedMethodCountParam == derivedMethodCountParam)
                        {
                            rootInterface.InnerElements.RemoveAt(j);
                            break;
                        }
                    }
                }
            }


            // Calculate starting offset
            foreach (CppInterface cppInterface in parents)
                methodOffset += cppInterface.InnerElements.Count;

            // Set virtual offset for each method
            foreach (CppMethod method in rootInterface.Methods)
            {
                method.Offset = methodOffset;
                methodOffset++;
            }
        }

        /// <summary>
        /// Add a typedef to the list of typedef for the current include. This this typedef already exists, then don't add it.
        /// </summary>
        /// <param name="cppNewTypedef"></param>
        private void AddTypeDef(CppTypedef cppNewTypedef)
        {
            if (cppNewTypedef.Name == cppNewTypedef.Type)
                return;

            foreach (CppTypedef cppTypeDef in CurrentInclude.Typedefs)
            {
                if (cppTypeDef.Name == cppNewTypedef.Name
                    && cppTypeDef.Specifier == cppNewTypedef.Specifier
                    && cppTypeDef.Const == cppNewTypedef.Const
                    && cppTypeDef.Type == cppNewTypedef.Type)
                {
                    return;
                }
            }
            CurrentInclude.Add(cppNewTypedef);
        }

        /// <summary>
        /// Parse a typedef
        /// </summary>
        private void ParseTypedef()
        {
            // Skip typedef token
            ReadNextToken();

            string typeName = null;

            // If typedef contains a body then parse it
            if (CheckBody())
            {
                CppElement cppTypeDefDeclare;
                if (CurrentToken.Id == TokenId.Struct)
                {
                    cppTypeDefDeclare = ParseStruct();
                }
                else if (CurrentToken.Id == TokenId.Enum)
                    cppTypeDefDeclare = ParseEnum();
                else
                    throw new ArgumentException(string.Format("Unexpected token {0} after typedef",
                                                              CurrentToken));

                ReadNextToken();

                string newStructName = CurrentToken.Value;

                // Generate a fake typedef from struct to real typedef
                if (newStructName != cppTypeDefDeclare.Name)
                    AddTypeDef(new CppTypedef() {Name = cppTypeDefDeclare.Name, Type = newStructName});

                // Special case where a field in a struct is referencing the struct itself
                // We need to reflect the new struct name to the field type
                if (cppTypeDefDeclare is CppStruct)
                {
                    CppStruct cppStruct = cppTypeDefDeclare as CppStruct;
                    foreach (var cppField in cppStruct.Fields)
                    {
                        if (cppField.Type == cppStruct.Name)
                            cppField.Type = newStructName;
                    }
                }
                cppTypeDefDeclare.Name = newStructName;
                typeName = cppTypeDefDeclare.Name;
            }
            else
            {
                bool stripType = false;
                if (CurrentToken.Value == "interface")
                    ReadNextToken();
                else if (CurrentToken.Id == TokenId.Struct)
                {
                    //stripType = true;
                    ReadNextToken();
                }

                var cppTypedef = ReadType<CppTypedef>(true);

                if (cppTypedef != null)
                {
                    //// Strip leading underscore for typedef struct
                    //if (stripType)
                    //    cppTypedef.Type = StripLeadingUnderscore(cppTypedef.Type);

                    AddTypeDef(cppTypedef);
                    typeName = cppTypedef.Name;
                }
            }

            // If we found a typename, then continue, else It is more likely to be 
            // a typedef for a function that we don't parse
            if (typeName != null)
            {
                do
                {                    
                    if (PreviewNextToken().Id == TokenId.Semicolon)
                        break;

                    ReadNextToken();
                    if (CurrentToken.Id == TokenId.Comma)
                    {
                        CppTypedef newTypeDef = new CppTypedef();
                        newTypeDef.Type = typeName;
                        do
                        {
                            TokenId previewTokenId = PreviewNextToken().Id;
                            if (previewTokenId == TokenId.Comma || previewTokenId == TokenId.Semicolon)
                                break;

                            ReadNextToken();
                            // Handle pointer specifiers
                            if (CurrentToken.Id == TokenId.Star || CurrentToken.Id == TokenId.And)
                            {
                                newTypeDef.Specifier += "*";
                            }
                            else if (CurrentToken.Id == TokenId.Const)
                            {
                                newTypeDef.Const = true;
                            }
                            else if (CurrentToken.Id == TokenId.Identifier)
                            {
                                newTypeDef.Name = CurrentToken.Value;
                            }
                            else
                            {
                                throw new ArgumentException(string.Format("Invalid token found in typedef {0} {1}", CurrentToken.Id, CurrentToken.Value));
                            }
                        } while (true);
                        AddTypeDef(newTypeDef);
                    }
                } while (true);
            }
            NextStatement();
        }

        /// <summary>
        /// Return true if there is probably a body of a function/method in the next tokens
        /// </summary>
        /// <returns></returns>
        private bool CheckBody()
        {
            bool leftBraceFound = false;
            int index = 1;
            do
            {
                if (GetTokenFrom(index).Id == TokenId.Semicolon)
                    break;
                if (GetTokenFrom(index).Id == TokenId.Leftbrace)
                {
                    leftBraceFound = true;
                    break;
                }
                index++;
            } while (true);
            return leftBraceFound;
        }


        private class PragmaStackValue
        {
            public string Identifier;
            public string Value;
        }

        private string _currentPackingValue = "0";
        private Stack<PragmaStackValue> _pragmaStack = new Stack<PragmaStackValue>();

        private void ParsePragma()
        {
            ReadNextToken();
            if (CurrentToken.Value != "pack")
            {
                throw new ArgumentException(string.Format("Invalid pragma found [{0}] Unable to handle pragma different from #pragma pack", CurrentToken.Value));
            }

            ReadNextToken(); // (

            bool isShow = false;
            bool isPush = false;
            bool isPop = false;
            string identifier = null;
            string packValue = null;

            do
            {
                ReadNextToken();

                if (CurrentToken.Id == TokenId.Rightparen)
                    break;
                if (CurrentToken.Value == "push")
                    isPush = true;
                else if (CurrentToken.Value == "pop")
                    isPop = true;
                else if (CurrentToken.Value == "show")
                    isShow = true;
                else if (CurrentToken.Id == TokenId.Identifier)
                    identifier = CurrentToken.Value;
                else if (CurrentToken.Id == TokenId.Intlit)
                    packValue = CurrentToken.Value;
            } while (true);

            if (isPush)
            {
                if (identifier == null)
                    identifier = "";
                _pragmaStack.Push(new PragmaStackValue() { Identifier = identifier, Value = _currentPackingValue });
                _currentPackingValue = packValue;
            }
            else if (isPop)
            {
                PragmaStackValue popPack = null;
                if (identifier != null)
                {
                    var lastPack = _pragmaStack.Peek();
                    if (lastPack != null)
                    {
                        if (lastPack.Identifier == identifier)
                        {
                            popPack = _pragmaStack.Pop();
                        }
                    }
                }
                else
                {
                    popPack = _pragmaStack.Pop();
                }

                if (packValue != null)
                {
                    _currentPackingValue = packValue;
                } 
                else if (popPack != null)
                {
                    _currentPackingValue = popPack.Value;
                }
            }
            else if (isShow)
            {
                Console.WriteLine("Pack Show {0}", _currentPackingValue);
            }
            else
            {
                _currentPackingValue = "0";
            }
            NextStatement();
        }

        /// <summary>
        /// Root method for parsing tokens
        /// </summary>
        private void Parse()
        {
            while (CurrentToken != null)
            {
                if (CurrentToken.Id == TokenId.Inline || CurrentToken.Value == "__inline")
                {
                    NextStatement();
                } else if (CurrentToken.Id == TokenId.Typedef)
                {
                    ParseTypedef();
                } else if (CurrentToken.Id == TokenId.Identifier && CurrentToken.Value == "pragma")
                {
                    ParsePragma();  
                } else if (IsInterfaceFromCurrentToken() || CurrentToken.Id == TokenId.Identifier || PreviewNextTokenValue() == "__stdcall")
                {
                    if (IsInterfaceFromCurrentToken())
                        ParseInterface();
                    else if (IsProbablyFunction())
                    {                        
                        //CurrentToken.Value == "HRESULT" || PreviewNextTokenValue() == "WINAPI"
                        ParseFunction();
                    }
                    else
                    {
                        NextStatement();
                    }
                }
                else if (CurrentToken.Id == TokenId.Struct)
                {
                    ParseStruct();
                    NextStatement();
                }
                else if (CurrentToken.Id == TokenId.Enum)
                {
                    ParseEnum();
                    NextStatement();
                }
                else if (CurrentToken.Id == TokenId.Extern)
                {
                    // Extern "C"
                    if (PreviewNextToken().Value.ToLower() == "\"c\"")
                        ReadNextToken();
                    // "{"
                    if (PreviewNextToken().Id == TokenId.Leftbrace)
                    {
                        ReadNextToken();
                        _externBraceCount++;
                    }
                }
                else if (CurrentToken.Id == TokenId.Rightbrace)
                {
                    if (_externBraceCount == 0)
                        throw new ArgumentException("Invalid brace found not matching previous extern \"C\" brace");
                    _externBraceCount--;
                }
                else
                {
                    NextStatement();
                }
                ReadNextToken();
            }
        }

        private int _externBraceCount;
    }
}