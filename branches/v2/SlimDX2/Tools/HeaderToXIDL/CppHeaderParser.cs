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
using System.IO;
using System.Linq;
using System.Text;
using Boost.Wave;
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.HeaderToXIDL
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

        public CppHeaderParser()
        {
            rootInclude = new CppInclude();
            mapIncludeToTokens = new Dictionary<string, List<Token>>();
            includeGroup = new CppIncludeGroup();
            IncludesToProcess = new List<string>();
            includeStack = new Stack<CppInclude>();
            tokens = new List<Token>();

            // Register IUnknown in order to find inheritance
            // And remove duplicated methods
            var iUnknownInterface = new CppInterface();
            iUnknownInterface.Name = "IUnknown";
            iUnknownInterface.Add(new CppMethod {Name = "QueryInterface"});
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
        public string IncludePath { get; set; }

        /// <summary>
        /// Add an include to process (without any path)
        /// </summary>
        /// <param name="include">an include filename to process</param>
        public void AddInclude(string include)
        {
            string fullPath = IncludePath + Path.DirectorySeparatorChar + include;
            if (!File.Exists(fullPath))
                throw new ArgumentException(string.Format("include [{0}] cannot be found from include path [{1}]",
                                                          include, fullPath));

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
            preProcessor.AddIncludePath(IncludePath);

            // Predefines macros
            preProcessor.DefineMacro("D3D11_NO_HELPERS=1", true);
            preProcessor.DefineMacro("D3D10_NO_HELPERS=1", true);
            preProcessor.DefineMacro("CONST=const", true);
            preProcessor.DefineMacro("__RPCNDR_H_VERSION__=1", true);
            preProcessor.DefineMacro("__REQUIRED_RPCNDR_H_VERSION__=475", true);
            preProcessor.DefineMacro("__REQUIRED_RPCSAL_H_VERSION__=100", true);
            preProcessor.DefineMacro("__SAL_H_FULL_VER=140050727", true);
            preProcessor.DefineMacro("LPVOID=void*", true);
            preProcessor.DefineMacro("LPCSTR=const char*", true);
            preProcessor.DefineMacro("LPCWSTR=const wchar*", true);
            preProcessor.DefineMacro("__reserved=", true);
            preProcessor.DefineMacro("WCHAR=wchar", true);
            preProcessor.DefineMacro("STDMETHOD(method)=virtual HRESULT STDMETHODCALLTYPE method", true);
            preProcessor.DefineMacro("STDMETHOD_(type,method)=virtual type STDMETHODCALLTYPE method", true);
            // Macro to transform a old COM interface declaration (DECLARE_INTERFACE) to the new format (MIDL_INTERFACE)
            preProcessor.DefineMacro("DECLARE_INTERFACE(name)=MIDL_INTERFACE(\"\") name ", true);
            preProcessor.DefineMacro("DECLARE_INTERFACE_(name,parent)=MIDL_INTERFACE(\"\") name : public parent ", true);
            preProcessor.DefineMacro("PURE==0", true);
            preProcessor.DefineMacro("THIS_=", true);
            preProcessor.DefineMacro("THIS=void", true);
            preProcessor.DefineMacro("__field_ecount_opt(x)=", true);
            preProcessor.DefineMacro("DEFINE_ENUM_FLAG_OPERATORS(x)=", true);
            preProcessor.DefineMacro("D2D1_DECLARE_INTERFACE(name)=MIDL_INTERFACE(\"name\")", true);
            // Hook the DEFINE_GUID to catch the OnDefineMacro event
            preProcessor.DefineMacro( "DEFINE_GUID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)=", true);
            // Make possible to parse HRESULT macros
            preProcessor.DefineMacro("MAKE_HRESULT(sev,fac,code)=( ((sev)<<31) | ((fac)<<16) | (code) )", true);
            preProcessor.Run();

            // Remove all empty includes
            IncludeGroup.InnerElements.RemoveAll( include => include.InnerElements.Count == 0);

            // Apply documentation final post process
            ApplyDocumentation();
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
            // Process only files that needs to be processed
            if (IncludesToProcess.Contains(Path.GetFileName(name)))
                return File.ReadAllText(name);
            return "";
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
                Parse();
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

        /// <summary>
        /// Called when a macro is expanded. Used for parsing GUID
        /// </summary>
        /// <param name="macroFunctionCall"></param>
        public override void OnMacroFunctionExpand(MacroFunctionCall macroFunctionCall)
        {
            if (macroFunctionCall.Name == "DEFINE_GUID")
            {
                uint value1 = Convert.ToUInt32(macroFunctionCall.Arguments[1].RawValue.Trim(), 16);
                ushort value2 = Convert.ToUInt16(macroFunctionCall.Arguments[2].RawValue.Trim(), 16);
                ushort value3 = Convert.ToUInt16(macroFunctionCall.Arguments[3].RawValue.Trim(), 16);
                byte value4 = Convert.ToByte(macroFunctionCall.Arguments[4].RawValue.Trim(), 16);
                byte value5 = Convert.ToByte(macroFunctionCall.Arguments[5].RawValue.Trim(), 16);
                byte value6 = Convert.ToByte(macroFunctionCall.Arguments[6].RawValue.Trim(), 16);
                byte value7 = Convert.ToByte(macroFunctionCall.Arguments[7].RawValue.Trim(), 16);
                byte value8 = Convert.ToByte(macroFunctionCall.Arguments[8].RawValue.Trim(), 16);
                byte value9 = Convert.ToByte(macroFunctionCall.Arguments[9].RawValue.Trim(), 16);
                byte value10 = Convert.ToByte(macroFunctionCall.Arguments[10].RawValue.Trim(), 16);
                byte value11 = Convert.ToByte(macroFunctionCall.Arguments[11].RawValue.Trim(), 16);

                // Add a guid to the current include
                var cppGuid = new CppGuid();
                cppGuid.Guid = new Guid(value1, value2, value3, value4, value5, value6, value7, value8, value9, value10,
                                        value11);
                cppGuid.Name = macroFunctionCall.Arguments[0].RawValue.Trim();

                CurrentInclude.Add(cppGuid);
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
        /// Go to next Cpp statement
        /// </summary>
        /// <param name="rightBraceFollowedByNoSemiColon">if true, this will stop after a rightbrace } with 
        /// no expected semi colon after. This is used for handling extern "C" {}</param>
        private void NextStatement(bool rightBraceFollowedByNoSemiColon = false)
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
                    if (count == 0 && rightBraceFollowedByNoSemiColon)
                        break;
                    count--;
                }
                else if (CurrentToken.Id == TokenId.Semicolon)
                {
                    if (count > 0 && !breakOnLastBrace)
                        breakOnLastBrace = true;
                    else
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

                if (nextId == TokenId.Intlit || nextId == TokenId.Int)
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
        private void ParseEnum()
        {
            ReadNextToken();

            var cppEnum = new CppEnum();
            cppEnum.Name = StripLeadingUnderscore(CurrentToken.Value);
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
            NextStatement();
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

            // Get Type from token
            cppType.Type = CurrentToken.Value;
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
                            throw new ArgumentException("Expecting identifier followed in type ");

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
                            cppType.ArrayDimension = arrayDimension;
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
                case "STDMETHODCALLTYPE":
                case "WINAPI":
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
        private CppField ReadStructField(int fieldOffset)
        {
            var field = ReadType<CppField>(true);
            field.Offset = fieldOffset;
            NextStatement();
            return field;
        }

        /// <summary>
        /// Parse a struct from current token stream
        /// </summary>
        private void ParseStruct()
        {
            ReadNextToken();

            var cppStruct = new CppStruct();
            cppStruct.Name = StripLeadingUnderscore(CurrentToken.Value);
            CurrentInclude.Add(cppStruct);


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

                // Handle union
                if (type.Id == TokenId.Union)
                {
                    SkipUntilTokenId(TokenId.Leftbrace);

                    do
                    {
                        ReadNextToken();
                        type = CurrentToken;

                        if (type.Id == TokenId.Rightbrace)
                            break;

                        cppStruct.Add(ReadStructField(fieldOffset));
                    } while (true);
                    NextStatement();
                }
                else if (PreviewNextToken().Id == TokenId.Leftparen)
                {
                    // Skip Constructor
                    SkipUntilTokenId(TokenId.Rightbrace);
                }
                else
                {
                    // Else Read Struct Field declaration
                    cppStruct.Add(ReadStructField(fieldOffset));
                }
                fieldOffset++;
            } while (true);

            NextStatement();

            var newTypeDef = new CppTypedef();

            // Create default "LP and LPC" typedefs
            // This is just in case we did not catch them 
            // from a typedef struct declaration

            // Add default pointer to struct
            newTypeDef.Name = "LP" + cppStruct.Name;
            newTypeDef.Specifier = "*";
            newTypeDef.IsArray = false;
            newTypeDef.Const = false;
            newTypeDef.Type = cppStruct.Name;
            AddTypeDef(newTypeDef);

            newTypeDef = new CppTypedef();
            // Add default const pointer to struct
            newTypeDef.Name = "LPC" + cppStruct.Name;
            newTypeDef.Specifier = "*";
            newTypeDef.IsArray = false;
            newTypeDef.Const = true;
            newTypeDef.Type = cppStruct.Name;
            AddTypeDef(newTypeDef);
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

            // Parse Calling Convention
            method.CallingConvention = ParseCallingConvention(CurrentToken.Value);

            // Skip STDMETHODCALLTYPE
            ReadNextToken();

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

        /// <summary>
        /// Parse an interface declaration
        /// </summary>
        private void ParseInterface()
        {
            if (CurrentToken.Value == "interface")
            {
                // Pre-Declare interface
                if (GetTokenFrom(2).Id == TokenId.Semicolon)
                {
                    return;
                }
            }


            SkipUntilTokenId(TokenId.Rightparen);

            // Read Interface Name
            ReadNextToken();

            var cppInterface = new CppInterface();
            CurrentInclude.Add(cppInterface);

            cppInterface.Name = CurrentToken.Value;
            declaredInterface.Add(cppInterface.Name, cppInterface);

            cppInterface.ParentName = "";

            // Read Inheritance
            ReadNextToken();
            if (CurrentToken.Id == TokenId.Colon)
            {
                ReadNextToken(); // public

                ReadNextToken(); // inherited name
                cppInterface.ParentName = CurrentToken.Value;
            }

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

            // Go to next statement
            NextStatement();

            // Add pointer to interface
            var newTypeDef = new CppTypedef();


            string interfaceNameWithoutI = cppInterface.Name.StartsWith("I")
                                               ? cppInterface.Name.Substring(1)
                                               : cppInterface.Name;

            // Add default pointer to struct
            newTypeDef.Name = "LP" + interfaceNameWithoutI;
            newTypeDef.Specifier = "*";
            newTypeDef.IsArray = false;
            newTypeDef.Const = false;
            newTypeDef.Type = cppInterface.Name;
            AddTypeDef(newTypeDef);

            newTypeDef = new CppTypedef();
            // Add default const pointer to struct
            newTypeDef.Name = "LPC" + interfaceNameWithoutI;
            newTypeDef.Specifier = "*";
            newTypeDef.IsArray = false;
            newTypeDef.Const = true;
            newTypeDef.Type = cppInterface.Name;
            AddTypeDef(newTypeDef);
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
                bool isDuplicatingInheritedMethods = true;
                for (int i = 0; i < cppInterface.InnerElements.Count; i++)
                {
                    var inheritedMethod = (CppMethod)cppInterface.InnerElements[i];
                    var derivedMethod = (CppMethod)rootInterface.InnerElements[i];
                    if (inheritedMethod.Name != derivedMethod.Name)
                    {
                        isDuplicatingInheritedMethods = false;
                        break;
                    }
                }

                // If duplicated then remove methods
                if (isDuplicatingInheritedMethods)
                {
                    rootInterface.InnerElements.RemoveRange(0, cppInterface.InnerElements.Count);
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

            // If typedef contains a body then parse it
            if (CheckBody())
            {
                if (CurrentToken.Id == TokenId.Struct)
                {
                    ParseStruct();
                }
                else if (CurrentToken.Id == TokenId.Enum)
                    ParseEnum();
                else
                    throw new ArgumentException(string.Format("Unexpected token {0} after typedef",
                                                              CurrentToken));
            }
            else
            {
                bool stripType = false;
                if (CurrentToken.Value == "interface")
                    ReadNextToken();
                else if (CurrentToken.Id == TokenId.Struct)
                {
                    stripType = true;
                    ReadNextToken();
                }

                var cppTypedef = ReadType<CppTypedef>(true);

                if (cppTypedef != null)
                {
                    // Strip leading underscore for typedef struct
                    if (stripType)
                        cppTypedef.Type = StripLeadingUnderscore(cppTypedef.Type);

                    AddTypeDef(cppTypedef);
                }
                NextStatement();
            }
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

        /// <summary>
        /// Root method for parsing tokens
        /// </summary>
        private void Parse()
        {
            while (CurrentToken != null)
            {
                if (CurrentToken.Id == TokenId.Typedef)
                {
                    ParseTypedef();
                }
                else if (CurrentToken.Id == TokenId.Struct)
                {
                    ParseStruct();
                }
                else if (CurrentToken.Id == TokenId.Enum)
                {
                    ParseEnum();
                }
                else if (CurrentToken.Id == TokenId.Identifier || PreviewNextTokenValue() == "WINAPI")
                {
                    if (CurrentToken.Value == "interface" || CurrentToken.Value == "MIDL_INTERFACE")
                        ParseInterface();
                    else if (CurrentToken.Value == "HRESULT" || PreviewNextTokenValue() == "WINAPI")
                    {
                        ParseFunction();
                    }
                    else
                    {
                        NextStatement(true);
                    }
                }
                else if (CurrentToken.Id == TokenId.Extern && PreviewNextToken().Value.ToLower() == "\"c\"")
                {
                    // "C"
                    ReadNextToken();
                    // "{"
                    ReadNextToken();
                }
                else
                {
                    NextStatement(true);
                }
                ReadNextToken();
            }
        }

        /// <summary>
        /// Apply documentation
        /// </summary>
        private void ApplyDocumentation()
        {
            // Use MSDN 
            var msdnDoc = new MsdnDoc();

            msdnDoc.Begin();


            foreach (CppInclude cppInclude in IncludeGroup.Includes)
            {
                foreach (CppEnum cppEnum in cppInclude.Enums)
                {
                    MsdnDoc.Item docItem = msdnDoc.GetDocumentation(cppInclude.Name, cppEnum.Name);
                    cppEnum.Description = docItem.Description;
                    cppEnum.Remarks = docItem.Remarks;
                    if (cppEnum.InnerElements.Count != docItem.Items.Count)
                        Console.WriteLine("Warning Invalid number enum items in documentation for Enum {0}",
                                          cppEnum.Name);
                    int count = Math.Min(cppEnum.InnerElements.Count, docItem.Items.Count);
                    int i = 0;
                    foreach (CppEnumItem cppEnumItem in cppEnum.Items)
                    {
                        if (i < count)
                            cppEnumItem.Description = docItem.Items[i];
                        else break;
                        i++;
                    }
                }

                foreach (CppStruct cppStruct in cppInclude.Structs)
                {
                    MsdnDoc.Item docItem = msdnDoc.GetDocumentation(cppInclude.Name, cppStruct.Name);
                    cppStruct.Description = docItem.Description;
                    cppStruct.Remarks = docItem.Remarks;
                    if (cppStruct.InnerElements.Count != docItem.Items.Count)
                        Console.WriteLine("Invalid number of fields in documentation for Struct {0}", cppStruct.Name);
                    int count = Math.Min(cppStruct.InnerElements.Count, docItem.Items.Count);
                    int i = 0;
                    foreach (CppField cppEnumItem in cppStruct.Fields)
                    {
                        if (i < count)
                            cppEnumItem.Description = docItem.Items[i];
                        else break;
                        i++;
                    }
                }

                foreach (CppInterface cppInterface in cppInclude.Interfaces)
                {
                    MsdnDoc.Item docItem = msdnDoc.GetDocumentation(cppInclude.Name, cppInterface.Name);
                    cppInterface.Description = docItem.Description;

                    foreach (CppMethod cppMethod in cppInterface.Methods)
                    {
                        string methodName = cppInterface.Name + "::" + cppMethod.Name;
                        MsdnDoc.Item methodDocItem = msdnDoc.GetDocumentation(cppInclude.Name, methodName);
                        cppMethod.Description = methodDocItem.Description;
                        cppMethod.Remarks = methodDocItem.Remarks;
                        cppMethod.ReturnType.Description = methodDocItem.Return;
                        if (cppMethod.InnerElements.Count != methodDocItem.Items.Count)
                            Console.WriteLine("Invalid number of documentation for Parameters for method {0}",
                                              methodName);
                        int count = Math.Min(cppMethod.InnerElements.Count, methodDocItem.Items.Count);
                        int i = 0;
                        foreach (CppParameter cppParameter in cppMethod.Parameters)
                        {
                            if (i < count)
                                cppParameter.Description = methodDocItem.Items[i];
                            else break;
                            i++;
                        }
                    }
                }

                foreach (CppFunction cppFunction in cppInclude.Functions)
                {
                    MsdnDoc.Item docItem = msdnDoc.GetDocumentation(cppInclude.Name, cppFunction.Name);
                    cppFunction.Description = docItem.Description;
                    cppFunction.Remarks = docItem.Remarks;
                    cppFunction.ReturnType.Description = docItem.Return;
                    if (cppFunction.InnerElements.Count != docItem.Items.Count)
                        Console.WriteLine("Invalid number of documentation for Parameters for Function {0}",
                                          cppFunction.Name);
                    int count = Math.Min(cppFunction.InnerElements.Count, docItem.Items.Count);
                    int i = 0;
                    foreach (CppParameter cppParameter in cppFunction.Parameters)
                    {
                        if (i < count)
                            cppParameter.Description = docItem.Items[i];
                        else break;
                        i++;
                    }
                }
            }
            msdnDoc.End();
        }
    }
}