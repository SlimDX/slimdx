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
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Text.RegularExpressions;
using Microsoft.VisualStudio.TextTemplating;
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    [Flags]
    public enum TypeContext
    {
        Enum = 1,
        Type = 2,
        Function = 4,
        Struct = 8,
        EnumItem = 0x10,
        Interface = 0x20,
        All = Interface | EnumItem | Struct | Function | Type | Enum,
        Root = Interface | Struct | Function | Type | Enum,
    }


    public class CSharpGenerator
    {
        private static readonly string[] _csharpKeywords = new[]
                                                               {
                                                                   "abstract",
                                                                   "as",
                                                                   "base",
                                                                   "bool",
                                                                   "break",
                                                                   "byte",
                                                                   "case",
                                                                   "catch",
                                                                   "char",
                                                                   "checked",
                                                                   "class",
                                                                   "const",
                                                                   "continue",
                                                                   "decimal",
                                                                   "default",
                                                                   "delegate",
                                                                   "do",
                                                                   "double",
                                                                   "else",
                                                                   "enum",
                                                                   "event",
                                                                   "explicit",
                                                                   "extern",
                                                                   "false",
                                                                   "finally",
                                                                   "fixed",
                                                                   "float",
                                                                   "for",
                                                                   "foreach",
                                                                   "goto",
                                                                   "if",
                                                                   "implicit",
                                                                   "in",
                                                                   "int",
                                                                   "interface",
                                                                   "internal",
                                                                   "is",
                                                                   "lock",
                                                                   "long",
                                                                   "namespace",
                                                                   "new",
                                                                   "null",
                                                                   "object",
                                                                   "operator",
                                                                   "out",
                                                                   "override",
                                                                   "params",
                                                                   "private",
                                                                   "protected",
                                                                   "public",
                                                                   "readonly",
                                                                   "ref",
                                                                   "return",
                                                                   "sbyte",
                                                                   "sealed",
                                                                   "short",
                                                                   "sizeof",
                                                                   "stackalloc",
                                                                   "static",
                                                                   "string",
                                                                   "struct",
                                                                   "switch",
                                                                   "this",
                                                                   "throw",
                                                                   "true",
                                                                   "try",
                                                                   "typeof",
                                                                   "uint",
                                                                   "ulong",
                                                                   "unchecked",
                                                                   "unsafe",
                                                                   "ushort",
                                                                   "using",
                                                                   "virtual",
                                                                   "volatile",
                                                                   "void",
                                                                   "while",
                                                               };

        private readonly Dictionary<string, List<CppEnumItem>> _enumItemToAdd =
            new Dictionary<string, List<CppEnumItem>>();

        private readonly Dictionary<string, CSharpType> _mapCSharpTypeNameToCSharpType =
            new Dictionary<string, CSharpType>();

        private readonly Dictionary<string, MapStructField> _mapChangeStructField =
            new Dictionary<string, MapStructField>();

        private readonly Dictionary<string, CSharpType> _mapCppNameToCSharpType = new Dictionary<string, CSharpType>();

        private readonly Dictionary<string, CSharpNamespace> _mapIncludeToNamespace =
            new Dictionary<string, CSharpNamespace>();

        private readonly List<Regex> _mapMakeCallbackInterface = new List<Regex>();

        private readonly Dictionary<Regex, InnerInterfaceMethod> _mapMoveMethodToInnerInterface =
            new Dictionary<Regex, InnerInterfaceMethod>();

        private readonly Dictionary<Regex, string> _mapMoveStructToInner = new Dictionary<Regex, string>();

        private readonly Dictionary<Regex, bool> _mapTypeToKeepUnderscore = new Dictionary<Regex, bool>();

        private readonly Dictionary<Regex, CSharpNamespace> _mapTypeToNamespace =
            new Dictionary<Regex, CSharpNamespace>();

        private readonly Dictionary<string, CppTypedef> _mapTypedefToType = new Dictionary<string, CppTypedef>();
        private readonly InteropGenerator _registeredInteropCall = new InteropGenerator();

        private readonly Dictionary<Regex, string> _renameTypePart = new Dictionary<Regex, string>();
        private readonly List<Regex> _typeToRemove = new List<Regex>();
        private readonly Dictionary<Regex, RenameValue> _typeToRename = new Dictionary<Regex, RenameValue>();

//        private readonly Dictionary<string, CSharpType> _typeToRename = new Dictionary<Regex, RenameValue>();


        public CSharpGenerator(CppIncludeGroup cppIncludeGroup)
        {
            CppIncludeGroup = cppIncludeGroup;
            Assemblies = new List<CSharpAssembly>();
            CallContext.SetData("Generator", this);
        }

        public CppIncludeGroup CppIncludeGroup { get; private set; }
        public List<CSharpAssembly> Assemblies { get; private set; }
        public string GeneratedPath { get; set; }

        public InteropGenerator Interop
        {
            get { return _registeredInteropCall; }
        }

        public CSharpType ImportTypeFromName(string typeName, int sizeOf, bool isReference = false,
                                             bool isStruct = false)
        {
            CSharpType cSharpType;

            Type type = null;
            switch (typeName)
            {
                case "string":
                    type = typeof (string);
                    break;
                case "bool":
                    type = typeof (bool);
                    break;
                case "byte":
                    type = typeof (byte);
                    break;
                case "char":
                    type = typeof (char);
                    break;
                case "int":
                    type = typeof (int);
                    break;
                case "uint":
                    type = typeof (uint);
                    break;
                case "long":
                    type = typeof (long);
                    break;
                case "ulong":
                    type = typeof (ulong);
                    break;
                case "float":
                    type = typeof (float);
                    break;
                case "IntPtr":
                    type = typeof (IntPtr);
                    break;
            }

            if (!_mapCSharpTypeNameToCSharpType.TryGetValue(typeName, out cSharpType))
            {
                cSharpType = isStruct ? new CSharpStruct(null) : new CSharpType();
                cSharpType.Name = typeName;
                cSharpType.Type = type;
                cSharpType.IsReference = isReference;
                cSharpType.SizeOf = sizeOf;
                _mapCSharpTypeNameToCSharpType.Add(typeName, cSharpType);
            }

            return cSharpType;
        }

        internal CSharpType FindCppType(string cppName)
        {
            CSharpType type;
            _mapCppNameToCSharpType.TryGetValue(cppName, out type);
            return type;
        }


        public CSharpType ImportType(Type type, bool isReference = false)
        {
            CSharpType cSharpType;

            int sizeOf = 0;

            string typeName = "";
            if (type == typeof (string))
            {
                typeName = "string";
            }
            else
            {
                sizeOf = Marshal.SizeOf(type);
                if (type == typeof (bool))
                    typeName = "bool";
                else if (type == typeof (byte))
                    typeName = "byte";
                else if (type == typeof (char))
                    typeName = "char";
                else if (type == typeof (int))
                    typeName = "int";
                else if (type == typeof (uint))
                    typeName = "uint";
                else if (type == typeof (long))
                    typeName = "long";
                else if (type == typeof (ulong))
                    typeName = "ulong";
                else if (type == typeof (float))
                    typeName = "float";
                else if (type == typeof (IntPtr))
                    typeName = "IntPtr";
                else if (type == typeof (Guid))
                    typeName = "Guid";
                else if (type == typeof (void))
                    typeName = "void";
                else if (type == typeof (void*))
                    typeName = "void*";
                else
                    throw new ArgumentException(string.Format("Unsupported type {0}", type));
            }


            if (!_mapCSharpTypeNameToCSharpType.TryGetValue(typeName, out cSharpType))
            {
                cSharpType = new CSharpType();
                cSharpType.Name = typeName;
                cSharpType.Type = type;
                cSharpType.IsReference = isReference;
                cSharpType.SizeOf = sizeOf;
                _mapCSharpTypeNameToCSharpType.Add(typeName, cSharpType);
            }

            return cSharpType;
        }


        public void Generate()
        {
            MapAll();

            string relativePath = GeneratedPath ?? @".\";


            var host = new CustomTemplateHost();
            var engine = new Engine();
            host.Session = host.CreateSession();

            _registeredInteropCall.Generate(relativePath);

            CallContext.LogicalSetData("Generator", this);

            foreach (string generatedType in new[] {"Enumerations", "Structures", "Interfaces", "Functions"})
            {
                Console.WriteLine();
                Console.WriteLine("Generate {0}", generatedType);
                string templateFileName = generatedType + ".tt";
                host.TemplateFileValue = templateFileName;

                string input = Utilities.GetResource(templateFileName);

                foreach (CSharpAssembly assembly in Assemblies)
                {
                    string assemblyDirectory = relativePath + assembly.Name;

                    if (!Directory.Exists(assemblyDirectory))
                        Directory.CreateDirectory(assemblyDirectory);

                    Console.WriteLine("Process Assembly {0} => {1}", assembly.Name, assemblyDirectory);

                    foreach (CSharpNamespace cSharpNamespace in assembly.Namespaces)
                    {
                        string subDirectory = cSharpNamespace.Name.Substring(assembly.Name.Length);
                        if (subDirectory.StartsWith("."))
                            subDirectory = subDirectory.Substring(1);

                        string nameSpaceDirectory = assemblyDirectory + "\\" + subDirectory;
                        if (!Directory.Exists(nameSpaceDirectory))
                            Directory.CreateDirectory(nameSpaceDirectory);

                        Console.WriteLine("\tProcess Namespace {0} => {1}", cSharpNamespace.Name, nameSpaceDirectory);

                        CallContext.LogicalSetData("Namespace", cSharpNamespace);
                        ////host.Session = new TextTemplatingSession();
                        //host.Session = host.CreateSession();

                        //Transform the text template.
                        string output = engine.ProcessTemplate(input, host);
                        string outputFileName = Path.GetFileNameWithoutExtension(templateFileName);

                        outputFileName = Path.Combine(nameSpaceDirectory, outputFileName);
                        outputFileName = outputFileName + host.FileExtension;
                        File.WriteAllText(outputFileName, output, host.FileEncoding);

                        foreach (CompilerError error in host.Errors)
                        {
                            Console.WriteLine(error.ToString());
                        }
                    }
                }
            }

            host.TemplateFileValue = "Interop.tt";
            // Write Dynamic Interop
            File.WriteAllText(relativePath + @"\SlimDX2\CppObjectInterop.cs",
                              engine.ProcessTemplate(Utilities.GetResource(host.TemplateFileValue), host));
        }

        private void MapCppEnumToCSharpEnum(CppInclude cppInclude, CppEnum cppEnum)
        {
            if (IsTypeToRemove(cppEnum.Name))
                return;

            CSharpNamespace nameSpace = ResolveNamespace(cppInclude, cppEnum);

            var newEnum = new CSharpEnum();
            newEnum.Name = ConvertCppNameToCSharpName(cppEnum.Name, TypeContext.Enum);
            newEnum.CppElement = cppEnum;
            newEnum.SizeOf = 4;
            nameSpace.Add(newEnum);
            _mapCppNameToCSharpType.Add(cppEnum.Name, newEnum);

            //Console.WriteLine("Enum {0}",newEnum.Name);

            // Add new EnumItems);
            if (_enumItemToAdd.ContainsKey(cppEnum.Name))
            {
                foreach (CppEnumItem item in _enumItemToAdd[cppEnum.Name])
                    cppEnum.Add(item);
                _enumItemToAdd.Remove(cppEnum.Name);
            }

            //// Remove EnumItems that need to me removed
            //for (int i = cppEnum.InnerElements.Count - 1; i >= 0; i--)
            //{
            //    CppEnumItem cppEnumItem = cppEnum.Items[i];
            //    if (IsTypeToRemove(cppEnumItem.Name))
            //        cppEnum.InnerElements.RemoveAt(i);
            //}

            // Find Root Name 
            string rootName = cppEnum.Name;
            string rootNameFound = null;
            bool isRootNameFound = false;
            for (int i = rootName.Length; i >= 0 && !isRootNameFound; i--)
            {
                rootNameFound = rootName.Substring(0, i);

                isRootNameFound = true;
                foreach (CppEnumItem cppEnumItem in cppEnum.Items)
                {
                    if (!cppEnumItem.Name.StartsWith(rootNameFound))
                    {
                        isRootNameFound = false;
                        break;
                    }
                }
            }
            if (isRootNameFound)
            {
                rootName = rootNameFound;
            }


            foreach (CppEnumItem cppEnumItem in cppEnum.Items)
            {
                if (IsTypeToRemove(cppEnumItem.Name))
                    continue;

                var csharpEnumItem =
                    new CSharpEnum.Item(
                        ConvertCppNameToCSharpName(cppEnumItem.Name, TypeContext.EnumItem, rootName),
                        cppEnumItem.Value);
                csharpEnumItem.CppElement = cppEnumItem;
                newEnum.Add(csharpEnumItem);
                _mapCppNameToCSharpType.Add(cppEnumItem.Name, csharpEnumItem);

                //Console.WriteLine("{0},{1},{2},{3},{4},{5}", nameSpace, newEnum.Name, csharpEnumItem.Name,
                //                  csharpEnumItem.Value, cppEnumItem.Name, cppInclude.Name);
            }

            if (cppEnum.Name.EndsWith("FLAG") || cppEnum.Name.EndsWith("FLAGS"))
            {
                newEnum.IsFlag = true;

                bool noneIsFound = false;
                foreach (CSharpEnum.Item item in newEnum.Items)
                {
                    if (item.Name == "None")
                    {
                        noneIsFound = true;
                        break;
                    }
                }
                if (!noneIsFound)
                {
                    var csharpEnumItem = new CSharpEnum.Item("None", "0");
                    csharpEnumItem.CppElement = new CppElement {Description = "None."};
                    newEnum.Add(csharpEnumItem);
                    //Console.WriteLine("{0},{1},{2},{3},{4},{5}", nameSpace, newEnum.Name, csharpEnumItem.Name,
                    //                  csharpEnumItem.Value, "", cppInclude.Name);
                }
            }
        }

        private CSharpStruct PrepareStructForMap(CppInclude cppInclude, CppStruct cppStruct)
        {
            if (_mapCppNameToCSharpType.ContainsKey(cppStruct.Name))
            {
                return null;
            }
            var cSharpStruct = new CSharpStruct(cppStruct);
            CSharpNamespace nameSpace = ResolveNamespace(cppInclude, cppStruct);
            cSharpStruct.Name = ConvertCppNameToCSharpName(cppStruct.Name, TypeContext.Struct);
            nameSpace.Add(cSharpStruct);
            _mapCppNameToCSharpType.Add(cppStruct.Name, cSharpStruct);
            return cSharpStruct;
        }

        private void MapCppStructToCSharpStruct(CSharpStruct cSharpStruct)
        {
            foreach (var keyValuePair in _mapMoveStructToInner)
            {
                if (keyValuePair.Key.Match(cSharpStruct.CppElementName).Success)
                {
                    var destSharpStruct = _mapCppNameToCSharpType[keyValuePair.Value] as CSharpStruct;
                    // Remove the struct from his container
                    cSharpStruct.ParentContainer.Remove(cSharpStruct);
                    // Add this struct to the new container struct
                    destSharpStruct.Add(cSharpStruct);
                }
            }

            var cppStruct = cSharpStruct.CppElement as CppStruct;
            bool hasMarshalType = false;

            int currentOffset = 0;

            var offsetOfFields = new int[cppStruct.InnerElements.Count];

            int lastCppFieldOffset = -1;
            int lastFieldSize = 0;

            int maxSizeOfField = 0;

            bool isInUnion = false;

            for (int fieldIndex = 0; fieldIndex < cppStruct.InnerElements.Count; fieldIndex++)
            {
                CppField cppField = cppStruct.InnerElements[fieldIndex] as CppField;

                CSharpType publicType = null;
                CSharpType marshalType = null;
                bool hasArray = cppField.IsArray;
                int arrayDimension = string.IsNullOrWhiteSpace(cppField.ArrayDimension)
                                         ? 0
                                         : int.Parse(cppField.ArrayDimension);
                string fieldType = cppField.Type;
                string fieldName = ConvertCppNameToCSharpName(cppField.Name, TypeContext.Struct);

                bool hasPointer = !string.IsNullOrEmpty(cppField.Specifier) && cppField.Specifier.Contains("*");

                MapStructField mapStructField = FindMapStructField(cSharpStruct.CppElement.Name, cppField.Name);
                if (mapStructField.FieldName != null)
                    fieldName = mapStructField.FieldName;
                if (mapStructField.NativeFieldType != null)
                    fieldType = mapStructField.NativeFieldType;


                int fieldSize = 0;

                // Default IntPtr type for pointer, unless modified by specialized type (like char* map to string)
                if (hasPointer)
                {
                    publicType = ImportType(typeof (IntPtr));

                    // Pointer has a variable size depending on x86/x64 architecture, so set field size to -1
                    fieldSize = -1;

                    switch (fieldType)
                    {
                        case "CHAR":
                        case "char":
                            publicType = ImportType(typeof (string));
                            marshalType = ImportType(typeof (IntPtr));
                            hasMarshalType = true;
                            break;
                        case "WCHAR":
                        case "wchar":
                            publicType = ImportType(typeof (string));
                            marshalType = ImportType(typeof (IntPtr));
                            hasMarshalType = true;
                            break;
                    }
                }
                else
                {
                    switch (fieldType)
                    {
                        case "INT32":
                        case "INT":
                        case "int":
                        case "LONG":
                        case "long":
                        case "UINT32":
                        case "UINT":
                        case "ULONG":
                        case "DWORD":
                            fieldSize = 4;
                            publicType = ImportType(typeof (int));
                            if (arrayDimension == 4)
                            {
                                fieldSize = 4*4;
                                publicType = ImportTypeFromName(Global.Name + ".Int4", 4*4, false, true);
                                arrayDimension = 0;
                                hasArray = false;
                            }
                            break;
                        case "FLOAT":
                        case "float":
                            fieldSize = 4;
                            publicType = ImportType(typeof (float));

                            if (arrayDimension == 3)
                            {
                                fieldSize = 3*4;
                                publicType = ImportTypeFromName("SlimMath.Vector3", 3*4, false, true);
                                arrayDimension = 0;
                                hasArray = false;
                            }
                            else if (arrayDimension == 4)
                            {
                                fieldSize = 4*4;
                                publicType = ImportTypeFromName("SlimMath.Vector4", 4 * 4, false, true);
                                arrayDimension = 0;
                                hasArray = false;
                            }
                            break;
                        case "BOOL":
                            fieldSize = 4;
                            publicType = ImportType(typeof (bool));
                            marshalType = ImportType(typeof (int));
                            break;
                        case "BYTE":
                        case "UINT8":
                            fieldSize = 1;
                            publicType = ImportType(typeof (byte));
                            break;
                        case "UINT64":
                        case "LARGE_INTEGER":
                            fieldSize = 8;
                            publicType = ImportType(typeof (long));
                            break;
                        case "SIZE_T":
                            fieldSize = 4;
                            publicType = ImportTypeFromName(Global.Name + ".Size", 4, false, true);
                            break;
                        case "LPCSTR":
                        case "LPSTR":
                            fieldSize = 4;
                            publicType = ImportType(typeof (string));
                            marshalType = ImportType(typeof (IntPtr));
                            hasMarshalType = true;
                            break;
                        case "HMODULE":
                        case "HWND":
                        case "HANDLE":
                        case "HMONITOR":
                        case "REFIID":
                        case "REFGUID":
                            fieldSize = 4;
                            publicType = ImportType(typeof (IntPtr));
                            break;
                        case "CHAR":
                        case "char":
                            fieldSize = 1;
                            publicType = ImportType(typeof (byte));
                            if (hasArray)
                            {
                                fieldSize = 1*arrayDimension;
                                publicType = ImportType(typeof (string));
                                marshalType = ImportType(typeof (byte));
                                hasMarshalType = true;
                            }
                            break;
                        case "WCHAR":
                        case "wchar":
                            fieldSize = 2;
                            publicType = ImportType(typeof (char));
                            if (hasArray)
                            {
                                fieldSize = 2*arrayDimension;
                                publicType = ImportType(typeof (string));
                                marshalType = ImportType(typeof (char));
                                hasMarshalType = true;
                            }
                            break;
                        case "LUID":
                            fieldSize = 8;
                            publicType = ImportType(typeof (ulong));
                            break;
                        case "LPCVOID":
                            fieldSize = 4;
                            publicType = ImportType(typeof (IntPtr));
                            break;
                        default:
                            // Try to get a declared struct
                            // If it fails, then this struct is unknown
                            if (!_mapCppNameToCSharpType.TryGetValue(fieldType, out publicType))
                            {
                                throw new ArgumentException("Unknown Structure!");
                            }
                            if (publicType is CSharpStruct)
                            {
                                var referenceStruct = publicType as CSharpStruct;
                                // If referenced structure has a specialized marshalling, then specify marshalling
                                if (referenceStruct.HasMarshalType)
                                {
                                    marshalType = publicType;
                                }
                            }
                            fieldSize = (publicType).SizeOf;
                            break;
                    }
                }
                if (hasArray)
                {
                    hasMarshalType = true;
                }
                var fieldStruct = new CSharpStruct.Field(cSharpStruct, cppField, publicType, marshalType, fieldName);

                // If last field has same offset, then it's a union
                // CurrentOffset is not moved
                if (isInUnion && lastCppFieldOffset != cppField.Offset)
                {
                    lastFieldSize = maxSizeOfField;
                    maxSizeOfField = 0;
                    isInUnion = false;
                }

                currentOffset += lastFieldSize;
                offsetOfFields[cppField.Offset] = currentOffset;
                // Get correct offset (for handling union)
                fieldStruct.Offset = offsetOfFields[cppField.Offset];
                fieldStruct.SizeOf = fieldSize;
                fieldStruct.IsArray = hasArray;
                fieldStruct.ArrayDimension = arrayDimension;
                cSharpStruct.Add(fieldStruct);
                // TODO : handle packing rules here!!!!!

                // If last field has same offset, then it's a union
                // CurrentOffset is not moved
                if (lastCppFieldOffset == cppField.Offset ||
                    ((fieldIndex + 1) < cppStruct.InnerElements.Count &&
                     (cppStruct.InnerElements[fieldIndex + 1] as CppField).Offset == cppField.Offset))
                {
                    isInUnion = true;
                    cSharpStruct.ExplicitLayout = true;
                    maxSizeOfField = fieldSize > maxSizeOfField ? fieldSize : maxSizeOfField;
                    lastFieldSize = 0;
                }
                else
                {
                    lastFieldSize = fieldSize;
                }
                lastCppFieldOffset = cppField.Offset;
            }
            cSharpStruct.SizeOf = currentOffset;
            cSharpStruct.HasMarshalType = hasMarshalType;
        }

        private CSharpFunction PrepareFunctionForMap(CppInclude cppInclude, CppFunction cppFunction)
        {
            var cSharpFunction = new CSharpFunction(cppFunction);

            var functionGroupAndDll = ResolveFunctionGroup(cppFunction.Name);
            if (functionGroupAndDll == null)
                throw new ArgumentException("CppFunction " + cppFunction.Name + " is not mapped to any FunctionGroup");

            cSharpFunction.DllName = functionGroupAndDll.DllName;

            functionGroupAndDll.Group.Add(cSharpFunction);

            _mapCppNameToCSharpType.Add(cppFunction.Name, cSharpFunction);

            return cSharpFunction;
        }

        private CSharpInterface PrepareInterfaceForMap(CppInclude cppInclude, CppInterface cppInterface)
        {
            var cSharpInterface = new CSharpInterface(cppInterface);
            CSharpNamespace nameSpace = ResolveNamespace(cppInclude, cppInterface);
            cSharpInterface.Name = ConvertCppNameToCSharpName(cppInterface.Name, TypeContext.Interface);
            nameSpace.Add(cSharpInterface);

            // Associate Parent
            CSharpType parentType;
            if (_mapCppNameToCSharpType.TryGetValue(cppInterface.Parent, out parentType))
            {
                cSharpInterface.Parent = parentType;
            }

            _mapCppNameToCSharpType.Add(cppInterface.Name, cSharpInterface);
            return cSharpInterface;
        }

        private static string ConvertMethodParameterName(CppParameter cppParameter)
        {
            string name = cppParameter.Name;
            bool hasPointer = !string.IsNullOrEmpty(cppParameter.Specifier) &&
                              (cppParameter.Specifier.Contains("*") || cppParameter.Specifier.Contains("&"));
            if (hasPointer)
            {
                if (name.StartsWith("pp"))
                    name = name.Substring(2) + "Ref";
                else if (name.StartsWith("p"))
                    name = name.Substring(1) + "Ref";
            }
            name = new string(name[0], 1).ToLower() + name.Substring(1);

            if (_csharpKeywords.Contains(name))
                name = "@" + name;
            return name;
        }

        private CSharpMapType MapReturnParameter(CppMethod method)
        {
            CppType cpptype = method.ReturnType;
            CSharpType publicType = null;
            CSharpType marshalType = null;

            bool hasPointer = false;
            switch (cpptype.Type)
            {
                case "void":
                    publicType = ImportType(typeof (void));
                    break;
                case "INT32":
                case "INT":
                case "int":
                case "LONG":
                case "long":
                case "UINT32":
                case "UINT":
                case "ULONG":
                case "DWORD":
                    publicType = ImportType(typeof (int));
                    break;
                case "FLOAT":
                case "float":
                    publicType = ImportType(typeof (float));
                    break;
                case "BOOL":
                    publicType = ImportType(typeof (bool));
                    marshalType = ImportType(typeof (int));
                    break;
                case "BYTE":
                case "UINT8":
                    publicType = ImportType(typeof (byte));
                    marshalType = ImportType(typeof (int));
                    break;
                case "UINT64":
                case "LARGE_INTEGER":
                    publicType = ImportType(typeof (long));
                    break;
                case "SIZE_T":
                    publicType = ImportTypeFromName(Global.Name + ".Size", 4, false, true);
                    marshalType = ImportType(typeof (void*));
                    break;
                case "LPCSTR":
                case "LPSTR":
                    publicType = ImportType(typeof (string));
                    hasPointer = true;
                    break;
                case "HMODULE":
                case "HWND":
                case "HDC":
                case "HANDLE":
                case "HMONITOR":
                    publicType = ImportType(typeof (IntPtr));
                    hasPointer = true;
                    break;
                case "REFIID":
                case "REFGUID":
                    publicType = ImportType(typeof (IntPtr));
                    hasPointer = true;
                    break;
                case "CHAR":
                case "char":
                    publicType = ImportType(typeof (byte));
                    break;
                case "WCHAR":
                case "wchar":
                    publicType = ImportType(typeof (char));
                    break;
                case "LUID":
                    publicType = ImportType(typeof (long));
                    marshalType = ImportType(typeof (long));
                    break;
                case "LPCVOID":
                    publicType = ImportType(typeof (IntPtr));
                    hasPointer = true;
                    break;
                case "HRESULT":
                    publicType = ImportTypeFromName(Global.Name + ".Result", 4, false, true);
                    marshalType = ImportType(typeof (int));
                    break;
                default:
                    // Try to get a declared struct
                    // If it fails, then this struct is unknown
                    if (!_mapCppNameToCSharpType.TryGetValue(cpptype.Type, out publicType))
                    {
                        throw new ArgumentException("Unknown return type! {0}", cpptype.Type);
                    }
                    //if (!hasPointer)
                    //    throw new ArgumentException("Expecting pointer for param");
                    break;
            }


            if (!string.IsNullOrEmpty(method.ReturnType.Specifier) && method.ReturnType.Specifier.Contains("*"))
            {
                if (!(publicType is CSharpInterface))
                    publicType = ImportType(typeof (IntPtr));
                hasPointer = true;
            }

            if (hasPointer)
                marshalType = ImportType(typeof (void*));
            if (marshalType == null && publicType.Type == typeof (uint))
                marshalType = ImportType(typeof (int));

            return new CSharpMapType(null, method.ReturnType, publicType, marshalType, "");
        }


        private CSharpInteropCalliSignature RegisterNativeInterop(Type returnType, Type[] paramType)
        {
            var cSharpInteropCalliSignature = new CSharpInteropCalliSignature {ReturnType = returnType};
            cSharpInteropCalliSignature.ParameterTypes.AddRange(paramType);

            if (!_registeredInteropCall.Methods.Contains(cSharpInteropCalliSignature))
            {
                _registeredInteropCall.Methods.Add(cSharpInteropCalliSignature);
                cSharpInteropCalliSignature.Index = _registeredInteropCall.Methods.Count;
            }

            return cSharpInteropCalliSignature;
        }


        private List<Type> BuildCSharpMethodFromCppMethod(string cppPathContext, CSharpMethod cSharpMethod)
        {
            CppMethod cppMethod = (CppMethod) cSharpMethod.CppElement;

            if (!string.IsNullOrEmpty(cppPathContext))
                cppPathContext = cppPathContext + "::";

            cppPathContext += cppMethod.Name;

            cSharpMethod.Name = ConvertCppNameToCSharpName(cppMethod.Name, TypeContext.Interface);
            cSharpMethod.Offset = cppMethod.Offset;

            bool isWideChar = false;

            cSharpMethod.ReturnType = MapReturnParameter(cppMethod);

            bool hasMarshalType = false;

            var marshalMethodTypes = new List<Type>();

            foreach (CppParameter cppParameter in cppMethod.Parameters)
            {
                CSharpType publicType = null;
                CSharpType marshalType = null;

                foreach (KeyValuePair<PathRegex, CppAttribute> changeCppAtribute in _mapMethodParamAttribute)
                {
                    if (changeCppAtribute.Key.Match(cppPathContext + "::" + cppParameter.Name))
                    {
                        cppParameter.Attribute = changeCppAtribute.Value;
                        break;
                    }
                }

                foreach (KeyValuePair<PathRegex, string> changeCppTypeParam in _mapMethodParamTypeToCppType)
                {
                    if (changeCppTypeParam.Key.Match(cppPathContext + "::" + cppParameter.Name))
                    {
                        cppParameter.Type = changeCppTypeParam.Value;
                        break;
                    }
                }


                bool hasArray = cppParameter.IsArray || ((cppParameter.Attribute & CppAttribute.Buffer) != 0);
                int arrayDimension = string.IsNullOrWhiteSpace(cppParameter.ArrayDimension)
                                         ? 0
                                         : int.Parse(cppParameter.ArrayDimension);
                string paramType = GetFinalCppType(cppParameter.Type);
                string paramName = ConvertMethodParameterName(cppParameter);

                bool hasPointer = !string.IsNullOrEmpty(cppParameter.Specifier) &&
                                  (cppParameter.Specifier.Contains("*") || cppParameter.Specifier.Contains("&"));
                bool isOptional = (cppParameter.Attribute & CppAttribute.Optional) != 0;


                if (hasArray)
                    hasPointer = true;

                //var mapInterfaceField = FindMapInterfaceField(cSharpInterface.CppElement.Name, cppField.Name);
                //if (mapInterfaceField.FieldName != null)
                //    paramName = mapInterfaceField.FieldName;
                //if (mapInterfaceField.NativeFieldType != null)
                //    paramType = mapInterfaceField.NativeFieldType;


                CSharpMethod.ParameterAttribute parameterAttribute = CSharpMethod.ParameterAttribute.In;

                if (paramType == "void" && !hasPointer)
                    continue;

                switch (paramType)
                {
                    case "INT32":
                    case "INT":
                    case "int":
                    case "LONG":
                    case "long":
                    case "UINT32":
                    case "UINT":
                    case "ULONG":
                    case "DWORD":
                        publicType = ImportType(typeof (int));
                        if (arrayDimension == 4)
                        {
                            publicType = ImportTypeFromName(Global.Name + ".Int4", 4*4, false, true);
                            arrayDimension = 0;
                            hasArray = false;
                        }
                        break;
                    case "FLOAT":
                    case "float":
                        publicType = ImportType(typeof (float));

                        if (arrayDimension == 3)
                        {
                            publicType = ImportTypeFromName("SlimMath.Vector3", 3 * 4, false, true);
                            arrayDimension = 0;
                            hasArray = false;
                        }
                        else if (arrayDimension == 4)
                        {
                            publicType = ImportTypeFromName("SlimMath.Vector4", 4 * 4, false, true);
                            arrayDimension = 0;
                            hasArray = false;
                        }
                        break;
                    case "BOOL":
                        publicType = ImportType(typeof (bool));
                        marshalType = ImportType(typeof (int));
                        break;
                    case "BYTE":
                    case "UINT8":
                        publicType = ImportType(typeof (byte));
                        marshalType = ImportType(typeof (int));
                        break;
                    case "UINT64":
                    case "LARGE_INTEGER":
                        publicType = ImportType(typeof (long));
                        break;
                    case "SIZE_T":
                        publicType = ImportTypeFromName(Global.Name + ".Size", 4, false, true);
                        marshalType = ImportType(typeof (void*));
                        break;
                    case "LPCSTR":
                    case "LPSTR":
                        publicType = ImportType(typeof (string));
                        hasPointer = true;
                        break;
                    case "HMODULE":
                    case "HWND":
                    case "HDC":
                    case "HANDLE":
                    case "HMONITOR":
                        publicType = ImportType(typeof (IntPtr));
                        break;
                    case "REFIID":
                    case "REFGUID":
                        publicType = ImportType(typeof (Guid));
                        hasPointer = true;
                        break;
                    case "CHAR":
                    case "char":
                        publicType = ImportType(typeof (byte));
                        if (hasPointer)
                            publicType = ImportType(typeof (string));
                        if (hasArray)
                        {
                            publicType = ImportType(typeof (string));
                            marshalType = ImportType(typeof (byte));
                        }
                        break;
                    case "WCHAR":
                    case "wchar":
                        isWideChar = true;
                        publicType = ImportType(typeof (char));
                        if (hasPointer)
                            publicType = ImportType(typeof (string));
                        if (hasArray)
                        {
                            publicType = ImportType(typeof (string));
                            marshalType = ImportType(typeof (char));
                        }
                        break;
                    case "LUID":
                        publicType = ImportType(typeof (long));
                        break;
                    case "LPCVOID":
                        publicType = ImportType(typeof (IntPtr));
                        if ((cppParameter.Attribute & CppAttribute.Buffer) != 0)
                        {
                            hasArray = false;
                            cppParameter.Attribute = cppParameter.Attribute & ~CppAttribute.Buffer;
                        }
                        hasPointer = true;
                        break;
                    case "void":
                        publicType = ImportType(typeof (IntPtr));
                        break;
                    case "LPD3D10INCLUDE":
                        hasPointer = true;
                        if (!_mapCppNameToCSharpType.TryGetValue("ID3DInclude", out publicType))
                            throw new ArgumentException("Unknown type : " + paramType);
                        break;
                    case "ID3D10Effect":
                        publicType = ImportType(typeof (IntPtr));
                        break;
                    default:
                        // Try to get a declared struct
                        // If it fails, then this struct is unknown
                        if (!_mapCppNameToCSharpType.TryGetValue(paramType, out publicType))
                        {
                            throw new ArgumentException("Unknown type : " + paramType);
                        }
                        //if (!hasPointer)
                        //    throw new ArgumentException("Expecting pointer for param");
                        break;
                }

                // Change parameter type
                foreach (KeyValuePair<PathRegex, CSharpType> changeCSharpTypeParam in _mapMethodParamTypeToCSharpType)
                {
                    if (changeCSharpTypeParam.Key.Match(cppPathContext + "::" + cppParameter.Name))
                    {
                        publicType = changeCSharpTypeParam.Value;
                        break;
                    }
                }

                if (hasPointer)
                {
                    marshalType = ImportType(typeof (void*));

                    if (publicType is CSharpInterface)
                    {
                        if (cppParameter.Attribute == CppAttribute.None ||
                            (cppParameter.Attribute & CppAttribute.In) != 0)
                        {
                            parameterAttribute = CSharpMethod.ParameterAttribute.In;

                            // Force all array of interface to support null
                            if (hasArray)
                            {
                                isOptional = true;
                            }
                        }
                        else if ((cppParameter.Attribute & CppAttribute.InOut) != 0)
                            parameterAttribute = CSharpMethod.ParameterAttribute.Ref;
                        else if ((cppParameter.Attribute & CppAttribute.Out) != 0)
                            parameterAttribute = CSharpMethod.ParameterAttribute.Out;
                    }
                    else
                    {
                        if (cppParameter.Attribute == CppAttribute.None ||
                            (cppParameter.Attribute & CppAttribute.In) != 0)
                        {
                            parameterAttribute = publicType.Type == typeof (IntPtr) ||
                                                 publicType.Type == typeof (string)
                                                     ? CSharpMethod.ParameterAttribute.In
                                                     : CSharpMethod.ParameterAttribute.RefIn;
                        }
                        else if ((cppParameter.Attribute & CppAttribute.InOut) != 0)
                            parameterAttribute = CSharpMethod.ParameterAttribute.Ref;
                        else if ((cppParameter.Attribute & CppAttribute.Out) != 0)
                            parameterAttribute = CSharpMethod.ParameterAttribute.Out;

                        // Handle void* with Buffer attribute
                        if (paramType == "void" && (cppParameter.Attribute & CppAttribute.Buffer) != 0)
                        {
                            hasArray = false;
                            arrayDimension = 0;
                            parameterAttribute = CSharpMethod.ParameterAttribute.In;
                        }
                        else if (publicType.Type == typeof (string) && (cppParameter.Attribute & CppAttribute.Out) != 0)
                        {
                            publicType = ImportType(typeof (IntPtr));
                            parameterAttribute = CSharpMethod.ParameterAttribute.In;
                            hasArray = false;
                        }
                        else if (publicType is CSharpStruct &&
                                 (parameterAttribute == CSharpMethod.ParameterAttribute.Out || hasArray))
                        {
                            // Set IsOut on structure to generate proper marshalling
                            (publicType as CSharpStruct).IsOut = true;
                        }
                    }
                }
                if (publicType == null)
                {
                    throw new ArgumentException("Publictype cannot be null");
                }
                if (marshalType == null)
                    marshalType = publicType;

                var paramMethod = new CSharpMethod.Parameter(cSharpMethod, cppParameter, publicType, marshalType,
                                                             paramName);
                paramMethod.IsArray = hasArray;
                paramMethod.ArrayDimension = arrayDimension;
                paramMethod.Attribute = parameterAttribute;
                paramMethod.IsOptionnal = isOptional;
                paramMethod.IsWideChar = isWideChar;

                if (marshalType.Type == typeof (uint))
                {
                    marshalMethodTypes.Add(typeof (int));
                }
                else if (marshalType.Type == typeof (IntPtr))
                {
                    marshalMethodTypes.Add(typeof (void*));
                }
                else
                {
                    marshalMethodTypes.Add(marshalType.Type);
                }

                cSharpMethod.Add(paramMethod);
            }
            return marshalMethodTypes;
        }

        private void MapCppInterfaceToCSharpInterface(CSharpInterface cSharpInterface)
        {
            var cppInterface = cSharpInterface.CppElement as CppInterface;

            // Check if the interface is a callback
            foreach (Regex regexInterfaceName in _mapMakeCallbackInterface)
            {
                if (regexInterfaceName.Match(cppInterface.Name).Success)
                {
                    cSharpInterface.IsCallback = true;
                    break;
                }
            }

            int virtualMethodOffset = 0;

            string guidName = "IID_" + cppInterface.Name;


            CppGuid cppGuid = (from guid in CppIncludeGroup.Find<CppGuid>(".*")
                               where guid.Name == guidName
                               select guid).FirstOrDefault();

            if (cppGuid != null)
            {
                cSharpInterface.Guid = cppGuid.Guid.ToString();
            }

            List<CSharpMethod> generatedMethods = new List<CSharpMethod>();

            foreach (CppMethod cppMethod in cppInterface.Methods)
            {
                var cSharpMethod = new CSharpMethod(cppMethod);
                generatedMethods.Add(cSharpMethod);
                cSharpInterface.Add(cSharpMethod);

                var marshalMethodTypes = BuildCSharpMethodFromCppMethod(cppInterface.Name, cSharpMethod);

                cSharpMethod.Interop = RegisterNativeInterop(cSharpMethod.ReturnType.MarshalType.Type,
                                                             marshalMethodTypes.ToArray());

                _mapCppNameToCSharpType.Add(cppInterface.Name + "::" + cppMethod.Name, cSharpMethod);
            }

            var mapInnerInterface = new Dictionary<string, CSharpInterface>();
            // Dispatch method to inner interface if any
            foreach (var keyValuePair in _mapMoveMethodToInnerInterface)
            {
                foreach (CppMethod cppMethod in cppInterface.Methods)
                {
                    CppMethod newCppMethod = cppMethod;
                    CSharpMethod cSharpMethod = null;
                    foreach (var newCSharpMethod in cSharpInterface.Methods)
                    {
                        if (newCSharpMethod.CppElement == cppMethod)
                        {
                            cSharpMethod = newCSharpMethod;
                            break;
                        }
                    }

                    string cppName = cSharpInterface.CppElementName + "::" + cppMethod.Name;

                    if (keyValuePair.Key.Match(cppName).Success)
                    {
                        string innerInterfaceName = keyValuePair.Value.InnerInterface;
                        string parentInterfaceName = keyValuePair.Value.InheritedInterfaceName;
                        string newMethodName = keyValuePair.Key.Replace(cppName, keyValuePair.Value.NewMethodName);
                        cSharpMethod.Name = newMethodName;

                        CSharpInterface innerInterface;
                        CSharpInterface parentInterface = null;

                        if (parentInterfaceName != null)
                        {
                            if (!mapInnerInterface.TryGetValue(parentInterfaceName, out parentInterface))
                            {
                                parentInterface = new CSharpInterface(null);
                                parentInterface.Name = parentInterfaceName;
                                mapInnerInterface.Add(parentInterfaceName, parentInterface);
                            }
                        }

                        if (!mapInnerInterface.TryGetValue(innerInterfaceName, out innerInterface))
                        {
                            // TODO custom cppInterface?
                            innerInterface = new CSharpInterface(cppInterface);
                            innerInterface.Name = innerInterfaceName;
                            innerInterface.PropertyAccesName = keyValuePair.Value.PropertyAccessName;

                            if (parentInterface != null)
                                innerInterface.Parent = parentInterface;

                            // Add inner interface to root interface
                            cSharpInterface.Add(innerInterface);
                            // Move method to inner interface
                            mapInnerInterface.Add(innerInterfaceName, innerInterface);
                        }
                        cSharpInterface.Remove(cSharpMethod);
                        innerInterface.Add(cSharpMethod);
                    }
                }
            }

            // Remove dispatched methods from outer interface
            foreach (var innerInterface in mapInnerInterface)
            {
                foreach (CSharpMethod method in innerInterface.Value.Methods)
                    cppInterface.Remove(method.CppElement);
            }

            // Refactor Properties
            CreateProperties(generatedMethods);
        }

        private void CreateProperties(List<CSharpMethod> methods)
        {
            Dictionary<string, CSharpProperty> cSharpProperties = new Dictionary<string, CSharpProperty>();

            foreach (var cSharpMethod in methods)
            {
                bool isGet = cSharpMethod.Name.StartsWith("Get");
                bool isSet = cSharpMethod.Name.StartsWith("Set");
                if (!(isGet || isSet))
                    continue;
                string propertyName = cSharpMethod.Name.Substring("Get".Length);

                int parameterCount = cSharpMethod.ParameterCount;
                var parameterList = cSharpMethod.Parameters.ToList();

                CSharpProperty property;
                bool isPropertyToAdd = false;

                if (!cSharpProperties.TryGetValue(propertyName, out property))
                {
                    property = new CSharpProperty(propertyName);
                    isPropertyToAdd = true;
                }

                // If the property has already a getter and a setter, this must be an error, remove the property
                // (Should never happen, unless there are some polymorphism on the interface's methods)
                if (property.Getter != null && property.Setter != null)
                {
                    cSharpProperties.Remove(propertyName);
                    continue;
                }

                // Check Getter
                if (isGet)
                {
                    if ((cSharpMethod.IsHResult || !cSharpMethod.HasReturnType) && parameterCount == 1 &&
                        parameterList[0].IsOut)
                    {
                        property.Getter = cSharpMethod;
                        property.PublicType = parameterList[0].PublicType;
                        property.IsPropertyParam = true;
                    }
                    else if (parameterCount == 0 && cSharpMethod.HasReturnType)
                    {
                        property.Getter = cSharpMethod;
                        property.PublicType = property.Getter.ReturnType.PublicType;
                    }
                    else
                    {
                        // If there is a getter, but the setter is not valid, then remove the getter
                        if (property.Setter != null)
                            cSharpProperties.Remove(propertyName);
                        continue;
                    }
                }
                else
                {
                    // Check Setter
                    if ((cSharpMethod.IsHResult || !cSharpMethod.HasReturnType) && parameterCount == 1 &&
                        (parameterList[0].IsRefIn || parameterList[0].IsIn))
                    {
                        property.Setter = cSharpMethod;
                    }
                    else if (parameterCount == 1 && !cSharpMethod.HasReturnType)
                    {
                        property.Setter = cSharpMethod;
                    }
                    else
                    {
                        // If there is a getter, but the setter is not valid, then remove the getter
                        if (property.Getter != null)
                            cSharpProperties.Remove(propertyName);
                        continue;
                    }
                }

                // Check when Setter and Getter together that they have the same return type
                if (property.Setter != null && property.Getter != null)
                {
                    bool removeProperty = false;

                    //// Dont add property that doesn't match with return type
                    //if (property.Setter != property.Getter.IsHResult)
                    //    continue;
                    if (property.IsPropertyParam)
                    {
                        var getterParameter = property.Getter.Parameters.First();
                        var setterParameter = property.Setter.Parameters.First();
                        if (getterParameter.PublicType.FullName != setterParameter.PublicType.FullName)
                        {
                            removeProperty = true;
                        }
                    }
                    else
                    {
                        var getterType = property.Getter.ReturnType;
                        var setterType = property.Setter.Parameters.First();
                        if (getterType.PublicType.FullName != setterType.PublicType.FullName)
                            removeProperty = true;
                    }
                    if (removeProperty)
                    {
                        cSharpProperties.Remove(propertyName);
                    }
                }

                if (isPropertyToAdd)
                    cSharpProperties.Add(propertyName, property);
            }

            // Add the property to the ParentContainer
            foreach (var cSharpProperty in cSharpProperties)
            {
                var property = cSharpProperty.Value;
                if (property.Getter == null)
                    continue;

                // Associate the property with the Getter element
                property.CppElement = property.Getter.CppElement;
                var parent = property.Getter.ParentContainer;

                // If Getter has no propery, 
                if (property.Getter.NoProperty)
                    continue;

                if (property.Setter != null)
                {
                    // If Getter has no propery, 
                    if (property.Setter.NoProperty)
                        continue;

                    property.Setter.Visibility = Visibility.Internal;
                }
                // Update visibility for getter and setter (set to internal)
                property.Getter.Visibility = Visibility.Internal;

                parent.Add(property);
            }
        }


        public void MoveMethodsToInnerInterface(string methodNameRegExp, string innerInterface, string propertyAccess,
                                                string newMethodName, string inheritedInterfaceName = null)
        {
            _mapMoveMethodToInnerInterface.Add(new Regex(methodNameRegExp),
                                               new InnerInterfaceMethod(innerInterface, propertyAccess, newMethodName,
                                                                        inheritedInterfaceName));
        }

        public void MoveStructToInner(string fromStruct, string toStruct)
        {
            _mapMoveStructToInner.Add(new Regex(fromStruct), toStruct);
        }


        public void MakeCallbackInterface(string regexInterfaceName)
        {
            _mapMakeCallbackInterface.Add(new Regex(regexInterfaceName));
        }

        private void MapAll()
        {
            // Process all Enums
            foreach (CppInclude cppInclude in CppIncludeGroup.Includes)
            {
                foreach (CppEnum cppEnum in cppInclude.Enums)
                {
                    if (IsTypeToRemove(cppEnum.Name))
                        continue;
                    MapCppEnumToCSharpEnum(cppInclude, cppEnum);
                }
            }

            var selectedCSharpType = new List<CSharpCppElement>();

            // Predefine all structs and interfaces
            foreach (CppInclude cppInclude in CppIncludeGroup.Includes)
            {
                // Iterate on structs
                foreach (CppStruct cppStruct in cppInclude.Structs)
                {
                    if (IsTypeToRemove(cppStruct.Name))
                        continue;
                    CSharpStruct csharpStruct = PrepareStructForMap(cppInclude, cppStruct);
                    if (csharpStruct != null)
                        selectedCSharpType.Add(csharpStruct);
                }

                // Iterate on interfaces
                foreach (CppInterface cppInterface in cppInclude.Interfaces)
                {
                    if (IsTypeToRemove(cppInterface.Name))
                        continue;
                    CSharpInterface csharpInterface = PrepareInterfaceForMap(cppInclude, cppInterface);
                    if (csharpInterface != null)
                        selectedCSharpType.Add(csharpInterface);
                }

                // Prebuild global map typedef
                foreach (CppTypedef typeDef in cppInclude.Typedefs)
                {
                    if (!_mapTypedefToType.ContainsKey(typeDef.Name))
                        _mapTypedefToType.Add(typeDef.Name, typeDef);
                }

                // Iterate on interfaces
                foreach (CppFunction cppFunction in cppInclude.Functions)
                {
                    if (IsTypeToRemove(cppFunction.Name))
                        continue;
                    CSharpFunction cSharpFunction = PrepareFunctionForMap(cppInclude, cppFunction);
                    if (cSharpFunction != null)
                        selectedCSharpType.Add(cSharpFunction);
                }
            }

            // MAp all typedef to final CSharpType
            foreach (CppInclude cppInclude in CppIncludeGroup.Includes)
            {
                // Iterate on structs
                foreach (CppTypedef cppTypedef in cppInclude.Typedefs)
                {
                    if (string.IsNullOrEmpty(cppTypedef.Specifier) && !cppTypedef.IsArray)
                    {
                        CSharpType type;
                        if (_mapCppNameToCSharpType.TryGetValue(cppTypedef.Type, out type))
                        {
                            if (!_mapCppNameToCSharpType.ContainsKey(cppTypedef.Name))
                                _mapCppNameToCSharpType.Add(cppTypedef.Name, type);
                        }
                        else
                        {
                            throw new ArgumentException("Invalid type");
                        }
                    }
                }
            }

            // Transform structures
            foreach (CSharpStruct cSharpStruct in selectedCSharpType.OfType<CSharpStruct>())
            {
                MapCppStructToCSharpStruct(cSharpStruct);
                // Add Constants to Struct
                AddConstantFromMacros(cSharpStruct);
            }

            // Transform interfaces
            foreach (CSharpInterface cSharpInterface in selectedCSharpType.OfType<CSharpInterface>())
            {
                MapCppInterfaceToCSharpInterface(cSharpInterface);
                // Add Constants to Interface
                AddConstantFromMacros(cSharpInterface);
            }

            // Transform Functions
            foreach (CSharpFunction cSharpFunction in selectedCSharpType.OfType<CSharpFunction>())
            {
                MapCppFunctionToCSharpFunction(cSharpFunction);
            }

            // Add constant to FunctionGroup
            foreach (CSharpAssembly cSharpAssembly in Assemblies)
                foreach (var ns in cSharpAssembly.Namespaces)
                    foreach (var cSharpFunctionGroup in ns.FunctionGroups)
                        AddConstantFromMacros(cSharpFunctionGroup);
        }

        private void MapCppFunctionToCSharpFunction(CSharpFunction cSharpFunction)
        {
            BuildCSharpMethodFromCppMethod("", cSharpFunction);
        }

        private CSharpNamespace ResolveNamespace(CppInclude include, CppElement element)
        {
            foreach (var regExp in _mapTypeToNamespace)
            {
                if (regExp.Key.Match(element.Name).Success)
                    return regExp.Value;
            }

            return _mapIncludeToNamespace[include.Name];
        }


        public void KeepUnderscoreForType(string typeName)
        {
            _mapTypeToKeepUnderscore.Add(new Regex(typeName), true);
        }

        //public void MapCppTypeToCSharpType(string cppTypeName, string csharpTypeName)
        //{
        //    if (!_mapCppNameToCSharpType.ContainsKey(cppTypeName)


        //    ImportTypeFromName(csharpTypeName);


        private Dictionary<PathRegex, string> _mapCppNameToCppName = new Dictionary<PathRegex, string>();

        public void MapCppTypeToCppType(string cppTypeName, string newCppTypeName)
        {
            _mapCppNameToCppName.Add(new PathRegex(cppTypeName), newCppTypeName);
        }

        private string GetFinalCppType(string cppTypeName)
        {
            foreach (KeyValuePair<PathRegex, string> keyValuePair in _mapCppNameToCppName)
            {
                if (keyValuePair.Key.Match(cppTypeName))
                {
                    return keyValuePair.Value;
                }
            }
            return cppTypeName;
        }


        public void MapCppTypeToCSharpType(string cppTypeName, CSharpType csharpType)
        {
            _mapCppNameToCSharpType.Add(cppTypeName, csharpType);
        }

        public void MapCppTypeToCSharpType(string cppTypeName, string csharpType, int sizeOf = 0,
                                           bool isReference = false, bool isStruct = false)
        {
            _mapCppNameToCSharpType.Add(cppTypeName, ImportTypeFromName(csharpType, sizeOf, isReference, isStruct));
        }

        public void MapCppTypeToCSharpType(string cppTypeName, Type csharpType, bool isReference = false)
        {
            _mapCppNameToCSharpType.Add(cppTypeName, ImportType(csharpType, isReference));
        }

        private MapStructField FindMapStructField(string cppStructName, string fieldName, bool createIfNotExist = true)
        {
            MapStructField mapStructField;
            string fullPathName = cppStructName + "." + fieldName;
            if (!_mapChangeStructField.TryGetValue(fullPathName, out mapStructField) && createIfNotExist)
            {
                mapStructField = new MapStructField();
                _mapChangeStructField.Add(fullPathName, mapStructField);
            }
            return mapStructField;
        }

        public void ChangeStructFieldTypeToNative(string cppStructName, string fieldName, string newNativeTypeName,
                                                  string newFieldName = null)
        {
            var mapStructField = FindMapStructField(cppStructName, fieldName);
            mapStructField.NativeFieldType = newNativeTypeName;
            if (newFieldName != null)
                mapStructField.FieldName = newFieldName;
        }

        public void ChangeStructFieldTypeTo(string cppStructName, string fieldName, string newTypeName)
        {
            FindMapStructField(cppStructName, fieldName).FieldType = newTypeName;
        }

        public void ChangeStructFieldName(string cppStructName, string fieldName, string newFieldName)
        {
            FindMapStructField(cppStructName, fieldName).FieldName = newFieldName;
        }

        private class PathRegex
        {
            private static Regex splitPath = new Regex(@"\:\:");

            public PathRegex(string path)
            {
                string[] subRegx = splitPath.Split(path);
                regex = new Regex[subRegx.Length];
                for (int i = 0; i < subRegx.Length; i++)
                    regex[i] = new Regex(subRegx[i]);
            }

            private Regex[] regex;

            //public bool Match(CppType cppType)
            //{
            //    if (regex.Length > 0 && !regex[0].Match(cppType.Name).Success)
            //        return false;
            //    return true;
            //}

            //public bool Match(CppInterface cppInterface)
            //{
            //    if (regex.Length > 0 && !regex[0].Match(cppInterface.Name).Success)
            //        return false;
            //    return true;
            //}

            //public bool Match(CppInterface cppInterface, CppMethod cppMethod)
            //{
            //    if (!Match(cppInterface))
            //        return false;
            //    if (regex.Length > 1 && !regex[1].Match(cppMethod.Name).Success)
            //        return false;
            //    return true;
            //}

            //public bool Match(CppInterface cppInterface, CppMethod cppMethod, CppParameter cppParameter)
            //{
            //    if (!Match(cppInterface, cppMethod))
            //        return false;
            //    if (regex.Length > 2 && !regex[2].Match(cppParameter.Name).Success)
            //        return false;
            //    return true;
            //}

            public bool Match(string pathToMatch)
            {
                string[] subPath = splitPath.Split(pathToMatch);
                if (subPath.Length != regex.Length)
                    return false;

                for (int i = 0; i < regex.Length; i++)
                {
                    if (!regex[i].Match(subPath[i]).Success)
                        return false;
                }

                return true;
            }
        }


        private Dictionary<PathRegex, CppAttribute> _mapMethodParamAttribute = new Dictionary<PathRegex, CppAttribute>();

        private Dictionary<PathRegex, string> _mapMethodParamTypeToCppType = new Dictionary<PathRegex, string>();

        private Dictionary<PathRegex, CSharpType> _mapMethodParamTypeToCSharpType =
            new Dictionary<PathRegex, CSharpType>();

        public void ChangeMethodParamTypeToCppType(string regexMethodPath, string cppType)
        {
            _mapMethodParamTypeToCppType.Add(new PathRegex(regexMethodPath), cppType);
        }

        public void ChangeMethodParamTypeToCSharpType(string regexMethodPath, CSharpType cSharpType)
        {
            _mapMethodParamTypeToCSharpType.Add(new PathRegex(regexMethodPath), cSharpType);
        }


        public void ChangeMethodParamAttribute(string fullPath, CppAttribute attribute)
        {
            _mapMethodParamAttribute.Add(new PathRegex(fullPath), attribute);
        }

        private CSharpNamespace GetNamespace(string assemblyName, string nameSpace)
        {
            if (assemblyName == null)
                assemblyName = nameSpace;

            IEnumerable<CSharpAssembly> listOfAssembly = from assembly in Assemblies
                                                         where assembly.Name == assemblyName
                                                         select assembly;
            CSharpAssembly selectedAssembly = listOfAssembly.FirstOrDefault();
            if (selectedAssembly == null)
            {
                selectedAssembly = new CSharpAssembly(assemblyName);
                Assemblies.Add(selectedAssembly);
            }
            IEnumerable<CSharpNamespace> listOfNameSpace = from nameSpaceObject in selectedAssembly.Namespaces
                                                           where nameSpaceObject.Name == nameSpace
                                                           select nameSpaceObject;
            CSharpNamespace selectedNamespace = listOfNameSpace.FirstOrDefault();
            if (selectedNamespace == null)
            {
                selectedNamespace = new CSharpNamespace(selectedAssembly, nameSpace);
                selectedAssembly.Add(selectedNamespace);
            }
            return selectedNamespace;
        }


        private class FunctionGroupAndDll
        {
            public CSharpFunctionGroup Group;
            public string DllName;
        }

        private Dictionary<Regex, FunctionGroupAndDll> _mapCppFunctionNameToFunctionGroup =
            new Dictionary<Regex, FunctionGroupAndDll>();


        private FunctionGroupAndDll ResolveFunctionGroup(string functionName)
        {
            return (from functionGroupAndDll in _mapCppFunctionNameToFunctionGroup
                    where functionGroupAndDll.Key.Match(functionName).Success
                    select functionGroupAndDll.Value).FirstOrDefault();
        }

        private CSharpFunctionGroup GetOrCreateFunctionGroup(string assembly, string nameSpace, string functionGroupName)
        {
            CSharpNamespace cSharpNameSpace = GetNamespace(assembly, nameSpace);

            foreach (var cSharpFunctionGroup in  cSharpNameSpace.FunctionGroups)
            {
                if (cSharpFunctionGroup.Name == functionGroupName)
                {
                    return cSharpFunctionGroup;
                }
            }

            var group = new CSharpFunctionGroup();
            group.Name = functionGroupName;
            cSharpNameSpace.Add(group);

            return group;
        }

        public CSharpFunctionGroup CreateFunctionGroup(string assembly, string nameSpace, string functionGroupName)
        {
            return GetOrCreateFunctionGroup(assembly, nameSpace, functionGroupName);
        }

        private class ConstantDefinition
        {
            public ConstantDefinition(string cSharpTypeName, string type)
            {
                CSharpTypeName = cSharpTypeName;
                Type = type;
            }

            public string CSharpTypeName;
            public string Type;
        }


        private Dictionary<string, ConstantDefinition> _mapMacroToConstantInCSharpType =
            new Dictionary<string, ConstantDefinition>();

        public void AddConstantFromMacroToCSharpType(string regexpMacro, string fullNameCSharpType, string type)
        {
            _mapMacroToConstantInCSharpType.Add(regexpMacro, new ConstantDefinition(fullNameCSharpType, type));
        }

        private void AddConstantFromMacros(CSharpContainer cSharpContainer)
        {
            foreach (KeyValuePair<string, ConstantDefinition> keyValuePair in _mapMacroToConstantInCSharpType)
            {
                if (cSharpContainer.FullName == keyValuePair.Value.CSharpTypeName)
                {
                    var macroDefinitions = CppIncludeGroup.Find<CppMacroDefinition>(keyValuePair.Key);
                    foreach (CppMacroDefinition cppMacroDefinition in macroDefinitions)
                    {
                        CSharpConstant constant = new CSharpConstant(cppMacroDefinition);
                        constant.Name = ConvertCppNameToCSharpName(cppMacroDefinition.Name, TypeContext.All);
                        constant.Value = ParseMacroValue(cppMacroDefinition.Value);
                        constant.TypeName = keyValuePair.Value.Type;
                        cSharpContainer.Add(constant);
                    }
                }
            }
        }

        public void MapFunctionToFunctionGroup(string regexFunction, string dllName, CSharpFunctionGroup group)
        {
            _mapCppFunctionNameToFunctionGroup.Add(new Regex(regexFunction),
                                                   new FunctionGroupAndDll() {Group = group, DllName = dllName});
        }

        public void MapIncludeToNamespace(string includeName, string nameSpace, string assemblyName = null)
        {
            _mapIncludeToNamespace.Add(includeName, GetNamespace(assemblyName, nameSpace));
        }

        public void MapTypeToNamespace(string typeNameRegex, string nameSpace, string assemblyName = null)
        {
            _mapTypeToNamespace.Add(new Regex(typeNameRegex), GetNamespace(assemblyName, nameSpace));
        }

        public void AddNoteEnumItem(string enumName)
        {
            AddEnumItem(enumName, "None", "0");
        }

        public void CreateEnumFromMacros(string macroRegexpStr, string enumName)
        {
            var cppEnum = new CppEnum {Name = enumName};
            var regexMacro = new Regex(macroRegexpStr);
            CppInclude includeToAddTo = null;
            foreach (CppInclude cppInclude in CppIncludeGroup.Includes)
            {
                foreach (CppMacroDefinition macroDef in cppInclude.Macros)
                {
                    if (regexMacro.Match(macroDef.Name).Success)
                    {
                        bool isAlreadyAdded = false;
                        foreach (CppEnumItem cppEnumItem in cppEnum.Items)
                        {
                            if (cppEnumItem.Name == macroDef.Name)
                            {
                                isAlreadyAdded = true;
                                break;
                            }
                        }
                        if (!isAlreadyAdded)
                        {
                            includeToAddTo = cppInclude;
                            string value = ParseMacroValue(macroDef.Value);
                            cppEnum.Add(new CppEnumItem {Name = macroDef.Name, Value = value});
                        }
                    }
                }
            }
            includeToAddTo.Add(cppEnum);
        }


        private static Regex regexRemoveIntLitteral = new Regex("([0-9]U?)L");
        private static Regex regexMakeDXGIResult = new Regex(@"MAKE_DXGI_HRESULT\(([0-9]+)\)");
        private static Regex regexMakeDXGIStatus = new Regex(@"MAKE_DXGI_STATUS\(([0-9]+)\)");


        private static string _FACDXGIMacroValue = null;


        private string MakeHResult(string sev, string fac, string code)
        {
            return string.Format("((({0})<<31) | (({1})<<16) | ({2}))", sev, fac, code);
        }


        private void InitDXGIEnum()
        {
            if (_FACDXGIMacroValue == null)
                _FACDXGIMacroValue = CppIncludeGroup.Find<CppMacroDefinition>("_FACDXGI").FirstOrDefault().Value;
        }


        private string MakeDXGIResult(Match match)
        {
            InitDXGIEnum();
            return MakeHResult("" + 1, _FACDXGIMacroValue, match.Groups[1].Value);
        }

        private string MakeDXGIStatus(Match match)
        {
            InitDXGIEnum();
            return MakeHResult("" + 0, _FACDXGIMacroValue, match.Groups[1].Value);
        }

        private string ParseMacroValue(string value)
        {
            value = regexRemoveIntLitteral.Replace(value, "$1");
            value = regexMakeDXGIResult.Replace(value, MakeDXGIResult);
            value = regexMakeDXGIStatus.Replace(value, MakeDXGIStatus);
            return value;
        }

        public void RenameTypePart(string partName, string replaceString)
        {
            _renameTypePart.Add(new Regex(partName), replaceString);
        }

        public void AddEnumItem(string enumName, string itemName, string value)
        {
            List<CppEnumItem> items;
            if (!_enumItemToAdd.TryGetValue(enumName, out items))
            {
                items = new List<CppEnumItem>();
                _enumItemToAdd.Add(enumName, items);
            }
            items.Add(new CppEnumItem {Name = itemName, Value = value});
        }

        public void RenameType(string regexTypeName, string newTypeName, bool isFinalRename = false,
                               TypeContext context = TypeContext.All)
        {
            _typeToRename.Add(new Regex(regexTypeName), new RenameValue(newTypeName, context, isFinalRename));
        }

        //public void RemoveType(string regexTypeName)
        //{
        //    _typeToRemove.Add(new Regex(regexTypeName));
        //}

        private bool IsTypeToRemove(string name)
        {
            foreach (Regex regex in _typeToRemove)
            {
                if (regex.Match(name).Success)
                {
                    return true;
                }
            }
            return false;
        }

        private string ConvertCppNameToCSharpName(string name, TypeContext context, string rootName = null)
        {
            string newName = name;


            // Keep underscore for some types
            bool keepUnderscore = false;
            foreach (var keyValuePair in _mapTypeToKeepUnderscore)
            {
                if (keyValuePair.Key.Match(name).Success)
                {
                    keepUnderscore = true;
                    break;
                }
            }

            // Process Rename by regexp
            bool containsUnderscoreBeforeReplace = newName.Contains("_");
            bool isFinalRename = false;
            foreach (var regExp in _typeToRename)
            {
                if (regExp.Key.Match(newName).Success)
                {
                    if ((regExp.Value.Context & context) != 0)
                    {
                        newName = regExp.Key.Replace(newName, regExp.Value.Name);
                        if (regExp.Value.FinalRename)
                        {
                            isFinalRename = true;
                            break;
                        }
                    }
                }
            }

            // Rename is tagged as final, then return the string
            // If the string still contains some "_" then continue while processing
            if (isFinalRename ||
                (containsUnderscoreBeforeReplace && !newName.Contains("_") && newName.ToUpper() != newName))
                return newName;

            // Remove Prefix (for enums)
            if (rootName != null && newName.StartsWith(rootName))
                newName = newName.Substring(rootName.Length, newName.Length - rootName.Length);

            name = newName;

            // Remove leading "_"
            while (name.StartsWith("_"))
                name = name.Substring(1);

            // Convert rest of the string in CamelCase
            name = ConvertCaseString(name, keepUnderscore);
            return name;
        }

        private static bool IsValidCamelCase(string str, out int lowerCount)
        {
            // Count the number of char in lower case
            lowerCount = str.Count(charInStr => char.IsLower(charInStr));

            if (str.Length == 0)
                return false;

            // First char must be a letter
            if (!char.IsLetter(str[0]))
                return false;

            // First letter must be upper
            if (!char.IsUpper(str[0]))
                return false;

            // Second letter must be lower
            if (str.Length > 1 && char.IsUpper(str[1]))
                return false;

            // other chars must be letter or numbers
            //foreach (char charInStr in str)
            //{
            //    if (!char.IsLetterOrDigit(charInStr))
            //        return false;
            //}
            return str.All(charInStr => char.IsLetterOrDigit(charInStr));
        }

        private string ConvertCaseString(string phrase, bool keepUnderscore)
        {
            string[] splittedPhrase = phrase.Split('_');
            var sb = new StringBuilder();

            for (int i = 0; i < splittedPhrase.Length; i++)
            {
                string subPart = splittedPhrase[i];
                bool isRenameRegexpFound = false;


                // Try to match a subpart and replace it if necessary
                foreach (var regExp in _renameTypePart)
                {
                    if (regExp.Key.Match(subPart).Success)
                    {
                        subPart = regExp.Key.Replace(subPart, regExp.Value);
                        isRenameRegexpFound = true;
                        sb.Append(subPart);
                        break;
                    }
                }

                // Else, perform a standard convertion
                if (!isRenameRegexpFound)
                {
                    int numberOfCharLowercase;
                    // If string is not camel case, then camel case it
                    if (IsValidCamelCase(subPart, out numberOfCharLowercase))
                    {
                        sb.Append(subPart);
                    }
                    else
                    {
                        char[] splittedPhraseChars = (numberOfCharLowercase > 0)
                                                         ? subPart.ToCharArray()
                                                         : subPart.ToLower().ToCharArray();

                        if (splittedPhraseChars.Length > 0)
                            splittedPhraseChars[0] =
                                ((new String(splittedPhraseChars[0], 1)).ToUpper().ToCharArray())[0];
                        sb.Append(new String(splittedPhraseChars));
                    }
                }

                if (keepUnderscore && (i + 1) < splittedPhrase.Length)
                    sb.Append("_");
            }
            return sb.ToString();
        }

        #region Nested type: InnerInterfaceMethod

        private class InnerInterfaceMethod
        {
            public readonly string InnerInterface;
            public readonly string PropertyAccessName;
            public readonly string NewMethodName;
            public readonly string InheritedInterfaceName;

            public InnerInterfaceMethod(string innerInterface, string propertyAccess, string newMethodName,
                                        string inheritedInterfaceName)
            {
                InnerInterface = innerInterface;
                PropertyAccessName = propertyAccess;
                NewMethodName = newMethodName;
                InheritedInterfaceName = inheritedInterfaceName;
            }
        }

        #endregion

        #region Nested type: MapStructField

        internal class MapStructField
        {
            public string FieldName;
            public string FieldType;
            public string NativeFieldType;
        }

        #endregion

        #region Nested type: RenameValue

        private class RenameValue
        {
            public readonly TypeContext Context;
            public readonly bool FinalRename;
            public readonly string Name;

            public RenameValue(string name, TypeContext context, bool isFinalRename)
            {
                Name = name;
                Context = context;
                FinalRename = isFinalRename;
            }
        }

        #endregion
    }
}