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
using System.Text;
using Boost.Wave;
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.HeaderToXIDL
{
    public class CppHeaderParser : PreProcessCallbackBase
    {
        #region ParseState enum

        public enum ParseState
        {
            Root,
            InterfaceBody,
            StructBody,
        }

        #endregion

        private readonly Dictionary<string, CppInterface> declaredInterface = new Dictionary<string, CppInterface>();

        private readonly CppIncludeGroup includeGroup;
        private readonly Stack<CppInclude> includeStack;
        private readonly Dictionary<string, List<Token>> mapIncludeToTokens;
        private readonly Dictionary<string, string> nameToValue = new Dictionary<string, string>();

        private readonly CppInclude rootInclude;
        private int currentIndex;
        private string rootDoc = "Documentation";
        private List<Token> tokens;

        public CppHeaderParser()
        {
            rootInclude = new CppInclude();
            mapIncludeToTokens = new Dictionary<string, List<Token>>();
            includeGroup = new CppIncludeGroup();
            IncludesToProcess = new List<string>();
            includeStack = new Stack<CppInclude>();
            tokens = new List<Token>();

            CppInterface iUnknownInterface = new CppInterface();
            iUnknownInterface.Name = "IUnknown";
            iUnknownInterface.Add(new CppMethod {Name = "QueryInterface"});
            iUnknownInterface.Add(new CppMethod {Name = "AddRef"});
            iUnknownInterface.Add(new CppMethod {Name = "Release"});
            declaredInterface.Add(iUnknownInterface.Name, iUnknownInterface);
        }

        public CppIncludeGroup IncludeGroup
        {
            get { return includeGroup; }
        }

        private CppInclude CurrentInclude
        {
            get
            {
                if (includeStack.Count == 0)
                    return rootInclude;
                return includeStack.Peek();
            }
        }

        private Token CurrentToken
        {
            get
            {
                if (currentIndex < 0 || currentIndex >= tokens.Count)
                    return null;
                return tokens[currentIndex];
            }
        }

        private bool IsEndOfToken
        {
            get { return CurrentToken == null; }
        }

        private List<string> IncludesToProcess { get; set; }
        public string IncludePath { get; set; }

        private string GetNameFromInclude(string name)
        {
            return Path.GetFileNameWithoutExtension(name).ToLower();
        }

        private CppInclude FindOrCreateInclude(string name)
        {
            foreach (var include in includeGroup.Includes)
            {
                if (include.Name == name)
                {
                    return include;
                }
            }
            var includeToReturn = new CppInclude {Name = name};
            includeGroup.Add(includeToReturn);
            return includeToReturn;
        }

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

        public override void OnIncludBegin(string name)
        {
            string includeName = GetNameFromInclude(name);

            includeStack.Push(FindOrCreateInclude(includeName));

            if (!mapIncludeToTokens.TryGetValue(includeName, out tokens))
            {
                tokens = new List<Token>();
                mapIncludeToTokens.Add(includeName, tokens);
            }
        }

        public override string OnIncludeLoad(string name)
        {
            //Console.Out.WriteLine("OnIncludeLoad {0}", name);
            string includeName = GetNameFromInclude(name);
            if (IncludesToProcess.Contains(Path.GetFileName(name)))
            {
                return File.ReadAllText(name);
            }
            return "";
        }

        public override void OnIncludEnd()
        {
            currentIndex = 0;
            tokens = mapIncludeToTokens[CurrentInclude.Name];


            Console.Out.WriteLine("Begin Process Include {0}", CurrentInclude.Name);
            bool isParsed = false;
            if (!IsEndOfToken)
            {
                Parse();
                isParsed = true;
            }
            Console.Out.WriteLine("End Process Include {0}", CurrentInclude.Name);

            CppInclude lastIncluded = includeStack.Pop();

            // Add a dependency
            if (isParsed)
                CurrentInclude.Add(new CppDependency {Name = lastIncluded.Name});

            // Clear tokens for current stack
            tokens.Clear();
            //Console.Out.WriteLine("OnIncludEnd");
        }

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

        private void ReadNextToken()
        {
            if (currentIndex == tokens.Count)
            {
                return;
            }
            currentIndex++;
        }

        private Token PreviewNextToken()
        {
            return GetTokenFrom(1);
        }

        private string PreviewNextTokenValue()
        {
            Token token = GetTokenFrom(1);
            if (token == null)
                token = CurrentToken;
            if (token == null)
                return null;
            return token.Value;
        }

        private Token GetTokenFrom(int relativePosition)
        {
            int index = currentIndex + relativePosition;
            if (index < 0 || index >= tokens.Count)
                return null;
            return tokens[index];
        }

        //private void SkipUntilTokenId(TokenId tokenToFind)
        //{
        //    while (CurrentToken != null && CurrentToken.Id != tokenToFind)
        //    {
        //        ReadNextToken();
        //    }
        //}

        private void SkipUntilTokenId(params TokenId[] tokenToFind)
        {
            while (CurrentToken != null)
            {
                for (int i = 0; i < tokenToFind.Length; i++)
                {
                    if (tokenToFind[i] == CurrentToken.Id)
                        return;
                }
                ReadNextToken();
            }
        }


        private void SkipUntilTokenIdUnless(TokenId tokenToFind, TokenId unlessTokenId)
        {
            while (CurrentToken != null && CurrentToken.Id != tokenToFind && CurrentToken.Id != unlessTokenId)
            {
                ReadNextToken();
            }
        }

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
                    {
                        breakOnLastBrace = true;
                    }
                    else
                    {
                        break;
                    }
                }
                if (count == 0 && breakOnLastBrace)
                    break;
                ReadNextToken();
            }

            // Stop on last SemiColon after right brace
            do
            {
                if (PreviewNextToken() != null && PreviewNextToken().Id == TokenId.Semicolon)
                {
                    ReadNextToken();
                }
                else
                {
                    break;
                }
            } while (true);
        }


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
                    valueToParse = valueToParse.Replace("L", "");
                    value += valueToParse;
                }
                else if (nextId == TokenId.Identifier)
                {
                    string inlineValue = "";
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

        private CppElement ParseEnum()
        {
            ReadNextToken();

            CppEnum cppEnum = new CppEnum();
            cppEnum.Name = StripLeadingUnderscore(CurrentToken.Value);
            CurrentInclude.Add(cppEnum);

            SkipUntilTokenId(TokenId.Leftbrace);
            do
            {
                ReadNextToken();

                if (CurrentToken.Id == TokenId.Rightbrace)
                    break;

                CppEnumItem enumItem = new CppEnumItem();
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

            return cppEnum;
        }

        private T ReadType<T>(bool withDeclaration) where T : CppType, new()
        {
            T cppType = new T();
            if (CurrentToken.Id == TokenId.Const)
            {
                cppType.Const = true;
                ReadNextToken();
            }
            // Skip token if enum or struct
            if (CurrentToken.Id == TokenId.Enum || CurrentToken.Id == TokenId.Struct ||
                (CurrentToken.Value == "interface"))
            {
                ReadNextToken();
            }
            cppType.Type = CurrentToken.Value;
            cppType.Specifier = "";

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
                if (CurrentToken.Id == TokenId.Star)
                {
                    cppType.Specifier += "*";
                }
                else if (CurrentToken.Id == TokenId.And)
                {
                    cppType.Specifier += "&";
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

        private string ReadStringUpTo(TokenId id)
        {
            StringBuilder builder = new StringBuilder();
            do
            {
                ReadNextToken();
                if (CurrentToken.Id == id)
                    break;
                builder.Append(CurrentToken.Value);
            } while (true);
            return builder.ToString();
        }

        private CppCallingConvention ParseCallingConvention(string value)
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

        private CppField ReadStructField(int fieldOffset)
        {
            CppField field = ReadType<CppField>(true);
            field.Offset = fieldOffset;
            NextStatement();
            return field;
        }

        private CppStruct ParseStruct()
        {
            ReadNextToken();

            CppStruct cppStruct = new CppStruct();
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

            CppTypedef newTypeDef = new CppTypedef();

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

            return cppStruct;
        }

        private CppMethod ParseVirtualMethod()
        {
            // Skip Virtual
            if (CurrentToken.Id == TokenId.Virtual)
                ReadNextToken();
            return ParseMethod();
        }

        private bool SkipNextParenthesis()
        {
            return SkipMatchingBraces(TokenId.Leftparen, TokenId.Rightparen);
        }

        private bool SkipMatchingBraces(TokenId leftParent, TokenId rightParent)
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
                return true;
            }
            return false;
        }

        //private string ParseExpression()
        //{
        //    do
        //    {
        //        TokenId id = PreviewNextToken().Id;
        //        if (id == TokenId.Leftbrace)
        //        {

        //        }


        //        if (id == TokenId.Comma || id == TokenId.Rightbrace || id == TokenId.Semicolon)
        //            break;


        //    } while (true);
        //}

        private CppAttribute ReadAnnotation()
        {
            string annotation = CurrentToken.Value;
            if (!annotation.StartsWith("__"))
                return CppAttribute.None;

            string[] sub_annotation = annotation.Substring(2).Split('_');

            CppAttribute attr = CppAttribute.None;

            foreach (string annotationPart in sub_annotation)
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

        private CppParameter ParseMethodParameter()
        {
            var attribute = ReadAnnotation();
            CppParameter methodArgument = ReadType<CppParameter>(true);
            methodArgument.Attribute = attribute;

            if (PreviewNextToken().Id == TokenId.Assign)
            {
                SkipUntilTokenId(TokenId.Comma, TokenId.Rightparen);

                // Go back to current token
                currentIndex--;
            }
            return methodArgument;
        }


        private void ParseFunction()
        {
            CppFunction function = ParseGenericMethod<CppFunction>();
            if (function != null)
                CurrentInclude.Add(function);
        }

        private CppMethod ParseMethod()
        {
            return ParseGenericMethod<CppMethod>();
        }

        private T ParseGenericMethod<T>() where T : CppMethod, new()
        {
            T method = new T();

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

        private string StripLeadingUnderscore(string name)
        {
            if (name.StartsWith("_"))
            {
                name = name.Substring(1);
            }
            return name;
        }

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

            CppInterface cppInterface = new CppInterface();
            CurrentInclude.Add(cppInterface);

            cppInterface.Name = CurrentToken.Value;
            declaredInterface.Add(cppInterface.Name, cppInterface);

            cppInterface.Parent = "";

            // Read Inheritance
            ReadNextToken();
            if (CurrentToken.Id == TokenId.Colon)
            {
                ReadNextToken(); // public

                ReadNextToken(); // inherited name
                cppInterface.Parent = CurrentToken.Value;
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

            //
            RemoveDuplicateInheritance(cppInterface);

            NextStatement();

            // Add pointer to interface
            CppTypedef newTypeDef = new CppTypedef();


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
        ///   Remove duplicated inherited methods
        /// </summary>
        /// <param name = "rootInterface"></param>
        private void RemoveDuplicateInheritance(CppInterface rootInterface)
        {
            List<CppInterface> parents = new List<CppInterface>();

            int methodOffset = 0;

            // Look for Parents interfaces
            CppInterface parentInterface = rootInterface;
            do
            {
                string parentName = parentInterface.Parent;
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
            foreach (var cppInterface in parents)
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
                    CppMethod inheritedMethod = cppInterface.InnerElements[i] as CppMethod;
                    CppMethod derivedMethod = rootInterface.InnerElements[i] as CppMethod;
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
            foreach (var cppInterface in parents)
                methodOffset += cppInterface.InnerElements.Count;

            // Set virtual offset for each method
            foreach (var method in rootInterface.Methods)
            {
                method.Offset = methodOffset;
                methodOffset++;
            }
        }


        private void AddTypeDef(CppTypedef cppNewTypedef)
        {
            if (cppNewTypedef.Name == cppNewTypedef.Type)
                return;

            foreach (var cppTypeDef in CurrentInclude.Typedefs)
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


        private void ParseStructOrTypeDef()
        {
            if (CheckBody())
                ParseStruct();
            else
                ParseTypedef();
        }


        private void Parse()
        {
            while (CurrentToken != null)
            {
                if (CurrentToken.Id == TokenId.Typedef)
                {
                    //ReadNextToken();
                    ParseTypedef();
                    //if (CurrentToken.Id == TokenId.Enum)
                    //{
                    //    ParseEnum();
                    //}
                    //else {
                    //    ParseStructOrTypeDef();
                    //} 
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

        public override void OnMacroDefine(MacroDefinition macroDefinition)
        {
            // Only register MacroDefinition without any parameters
            if (macroDefinition.ParameterNames.Count == 0 && macroDefinition.Name != "INTERFACE")
            {
                CppMacroDefinition cppMacroDefinition = new CppMacroDefinition();
                cppMacroDefinition.Name = macroDefinition.Name;
                foreach (Token token in macroDefinition.Body)
                {
                    cppMacroDefinition.Value += token.Value;
                }
                if (!string.IsNullOrWhiteSpace(cppMacroDefinition.Value))
                    CurrentInclude.Add(cppMacroDefinition);
            }
        }

        public override void OnMacroUndef(string name)
        {
            //Console.Out.WriteLine("OnMacroUndef {0}", name);
        }


        public override void OnMacroFunctionExpand(MacroFunctionCall macroFunctionCall)
        {
            if (macroFunctionCall.Name == "DEFINE_GUID")
            {
                //Console.Out.WriteLine("OnMacroFunctionExpand {0}", macroFunctionCall);
                //Console.Out.Flush();

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
                CppGuid cppGuid = new CppGuid();
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

        private string FindInclude(string include)
        {
            string fullPath = IncludePath + Path.DirectorySeparatorChar + include;
            if (!File.Exists(fullPath))
                throw new ArgumentException(string.Format("include [{0}] cannot be found from include path [{1}]",
                                                          include, fullPath));

            return Path.GetFullPath(fullPath);
        }

        public void AddInclude(string include)
        {
            FindInclude(include);
            IncludesToProcess.Add(Path.GetFileName(include).ToLower());
        }

        public void Run()
        {
            string header = "";
            foreach (string includeName in IncludesToProcess)
                header += "#include \"" + includeName + "\"\n";

            PreProcessor preProcessor = new PreProcessor(header, "root.h", this);

            preProcessor.AddIncludePath(IncludePath);

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
            preProcessor.DefineMacro("DECLARE_INTERFACE(name)=MIDL_INTERFACE(\"\") name ", true);
            preProcessor.DefineMacro("DECLARE_INTERFACE_(name,parent)=MIDL_INTERFACE(\"\") name : public parent ", true);
            preProcessor.DefineMacro("PURE==0", true);
            preProcessor.DefineMacro("THIS_=", true);
            preProcessor.DefineMacro("THIS=void", true);
            preProcessor.DefineMacro("__field_ecount_opt(x)=", true);
            preProcessor.DefineMacro("DEFINE_ENUM_FLAG_OPERATORS(x)=", true);
            preProcessor.DefineMacro("D2D1_DECLARE_INTERFACE(name)=MIDL_INTERFACE(\"name\")", true);
            preProcessor.DefineMacro(
                "DEFINE_GUID(name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11)=",
                true);
            preProcessor.DefineMacro("MAKE_HRESULT(sev,fac,code)=( ((sev)<<31) | ((fac)<<16) | (code) )", true);
            preProcessor.Run();

            // Remove all empty includes
            IncludeGroup.InnerElements.RemoveAll(
                delegate(CppElement include) { return include.InnerElements.Count == 0; });

            ApplyDocumentation();
        }

        //private MsdnDoc.Item GetDocumentation(CppInclude include, string name)
        //{
        //    string originalName = name;

        //    // Handle name with ends A or W
        //    if (name.EndsWith("A") || name.EndsWith("W"))
        //    {
        //        string previouewChar = new string(name[name.Length - 2], 1);

        //        if (previouewChar.ToUpper() != previouewChar)
        //        {
        //            name = name.Substring(0, name.Length - 1);
        //        }
        //    }




        //    string fileName = rootDoc + "\\" + include.Name + "-" + name.Replace("::", "-") + ".html";
        //    string doc;
        //    if (!File.Exists(fileName))
        //    {
        //        doc = MsdnDoc.GetDocumentationFromMsdn(name);
        //        File.WriteAllText(fileName, doc);
        //    }
        //    else
        //    {
        //        doc = File.ReadAllText(fileName);
        //    }
        //    return MsdnDoc.ParseDocumentation(doc);
        //}

        private void ApplyDocumentation()
        {
            //if (!Directory.Exists(rootDoc))
            //    Directory.CreateDirectory(rootDoc);

            MsdnDoc msdnDoc = new MsdnDoc();

            msdnDoc.Begin();

            foreach (CppInclude cppInclude in IncludeGroup.Includes)
            {
                foreach (CppEnum cppEnum in cppInclude.Enums)
                {
                    MsdnDoc.Item docItem = msdnDoc.GetDocumentation(cppInclude.Name, cppEnum.Name);
                    cppEnum.Description = docItem.Description;
                    cppEnum.Remarks = docItem.Remarks;
                    if (cppEnum.InnerElements.Count != docItem.Items.Count)
                        Console.WriteLine("Warning Invalid number enum items in of documentation for Enum {0}",
                                          cppEnum.Name);
                    int count = Math.Min(cppEnum.InnerElements.Count, docItem.Items.Count);
                    int i = 0;
                    foreach (var cppEnumItem in cppEnum.Items)
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
                    foreach (var cppEnumItem in cppStruct.Fields)
                    {
                        if (i < count)
                            cppEnumItem.Description = docItem.Items[i];
                        else break;
                        i++;
                    }
                }

                foreach (var cppInterface in cppInclude.Interfaces)
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
                        foreach (var cppParameter in cppMethod.Parameters)
                        {
                            if (i < count)
                                cppParameter.Description = methodDocItem.Items[i];
                            else break;
                            i++;
                        }
                    }
                }

                foreach (var cppFunction in cppInclude.Functions)
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
                    foreach (var cppParameter in cppFunction.Parameters)
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