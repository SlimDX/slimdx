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
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Text.RegularExpressions;
using Microsoft.VisualStudio.TextTemplating;
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    public class CSharpGenerator
    {
        private readonly Dictionary<string, CSharpType> _mapCSharpTypeNameToCSharpType =
            new Dictionary<string, CSharpType>();

        private readonly Dictionary<string, CSharpType> _mapCppNameToCSharpType = new Dictionary<string, CSharpType>();

        private readonly Dictionary<string, CSharpNamespace> _mapIncludeToNamespace =
            new Dictionary<string, CSharpNamespace>();

        private readonly Dictionary<Regex, InnerInterfaceMethod> _mapMoveMethodToInnerInterface =
            new Dictionary<Regex, InnerInterfaceMethod>();

        private readonly Dictionary<Regex, string> _mapMoveStructToInner = new Dictionary<Regex, string>();

        private readonly Dictionary<Regex, bool> _mapTypeToKeepUnderscore = new Dictionary<Regex, bool>();

        private readonly Dictionary<Regex, CSharpNamespace> _mapTypeToNamespace = new Dictionary<Regex, CSharpNamespace>();

        private readonly Dictionary<string, CppTypedef> _mapTypedefToType = new Dictionary<string, CppTypedef>();
        private readonly InteropGenerator _registeredInteropCall = new InteropGenerator();

        private readonly Dictionary<Regex, string> _renameTypePart = new Dictionary<Regex, string>();
        private readonly MacroParser _macroParser;
        private readonly CSharpType DefaultInterfaceCppObject;

        //        private readonly Dictionary<string, CSharpType> _typeToRename = new Dictionary<Regex, RenameValue>();


        public CSharpGenerator(CppIncludeGroup cppIncludeGroup)
        {
            CppIncludeGroup = cppIncludeGroup;
            _macroParser = new MacroParser(cppIncludeGroup);
            Assemblies = new List<CSharpAssembly>();
            CallContext.SetData("Generator", this);

            // Create IUnknown object
            DefaultInterfaceCppObject = new CSharpType();
            DefaultInterfaceCppObject.Name = Global.Name + ".CppObject";
        }

        public CppIncludeGroup CppIncludeGroup { get; private set; }
        public List<CSharpAssembly> Assemblies { get; private set; }
        public string GeneratedPath { get; set; }

        public InteropGenerator Interop
        {
            get { return _registeredInteropCall; }
        }

        public void Dump(string fileName)
        {
            StreamWriter log = new StreamWriter(fileName, false, Encoding.ASCII);

            string csv = CultureInfo.CurrentCulture.TextInfo.ListSeparator;
            string format = "{1}{0}{2}{0}{3}{0}{4}";

            foreach (var assembly in Assemblies)
            {
                foreach (var ns in assembly.Namespaces)
                {
                    foreach (var element in ns.Enums)
                        log.WriteLine(format, csv, "enum", ns.Name, element.Name, element.CppElementName);
                    foreach (var element in ns.Structs)
                        log.WriteLine(format, csv, "struct", ns.Name, element.Name, element.CppElementName);
                    foreach (var element in ns.Interfaces)
                        log.WriteLine(format, csv, "interface", ns.Name, element.Name, element.CppElementName);
                }
            }
            log.Close();
        }


        public CSharpType ImportTypeFromName(string typeName, int sizeOf, bool isReference = false,
                                             bool isStruct = false)
        {
            CSharpType cSharpType;

            Type type = null;
            switch (typeName)
            {
                case "string":
                    type = typeof(string);
                    break;
                case "bool":
                    type = typeof(bool);
                    break;
                case "byte":
                    type = typeof(byte);
                    sizeOf = sizeof(byte);
                    break;
                case "char":
                    type = typeof(char);
                    sizeOf = sizeof(char);
                    break;
                case "int":
                    type = typeof(int);
                    sizeOf = sizeof(int);
                    break;
                case "uint":
                    type = typeof(uint);
                    sizeOf = sizeof(uint);
                    break;
                case "long":
                    type = typeof(long);
                    sizeOf = sizeof(long);
                    break;
                case "ulong":
                    type = typeof(ulong);
                    sizeOf = sizeof(ulong);
                    break;
                case "float":
                    type = typeof(float);
                    break;
                case "IntPtr":
                    type = typeof(IntPtr);
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
            if (type == typeof(string))
            {
                typeName = "string";
            }
            else
            {
                sizeOf = Marshal.SizeOf(type);
                if (type == typeof(bool))
                    typeName = "bool";
                else if (type == typeof(byte))
                    typeName = "byte";
                else if (type == typeof(char))
                    typeName = "char";
                else if (type == typeof(int))
                    typeName = "int";
                else if (type == typeof(uint))
                    typeName = "uint";
                else if (type == typeof(long))
                    typeName = "long";
                else if (type == typeof(ulong))
                    typeName = "ulong";
                else if (type == typeof(float))
                    typeName = "float";
                else if (type == typeof(double))
                    typeName = "double";
                else if (type == typeof(IntPtr))
                    typeName = "IntPtr";
                else if (type == typeof(Guid))
                    typeName = "Guid";
                else if (type == typeof(void))
                    typeName = "void";
                else if (type == typeof(void*))
                    typeName = "void*";
                else if (type == typeof(short))
                    typeName = "short";
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

            foreach (string generatedType in new[] { "Enumerations", "Structures", "Interfaces", "Functions", "LocalInterop" })
            {
                Console.WriteLine();
                Console.WriteLine("Generate {0}", generatedType);
                string templateFileName = generatedType + ".tt";
                host.TemplateFileValue = templateFileName;

                string input = Utilities.GetResource(templateFileName);

                foreach (CSharpAssembly assembly in Assemblies)
                {
                    CallContext.LogicalSetData("Assembly", assembly);

                    string assemblyDirectory = Path.Combine(relativePath + assembly.Name, "Generated");

                    if (!Directory.Exists(assemblyDirectory))
                        Directory.CreateDirectory(assemblyDirectory);

                    Console.WriteLine("Process Assembly {0} => {1}", assembly.Name, assemblyDirectory);

                    if (generatedType == "LocalInterop")
                    {
                        Console.WriteLine("\tProcess Interop {0} => {1}", assembly.Name, assemblyDirectory);

                        //Transform the text template.
                        string output = engine.ProcessTemplate(input, host);
                        string outputFileName = Path.GetFileNameWithoutExtension(templateFileName);

                        outputFileName = Path.Combine(assemblyDirectory, outputFileName);
                        outputFileName = outputFileName + host.FileExtension;
                        File.WriteAllText(outputFileName, output, host.FileEncoding);

                        foreach (CompilerError error in host.Errors)
                        {
                            Console.WriteLine(error.ToString());
                        }
                    }
                    else
                    {

                        foreach (CSharpNamespace cSharpNamespace in assembly.Namespaces)
                        {
                            string subDirectory = cSharpNamespace.OutputDirectory ?? ".";

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
            }

            //host.TemplateFileValue = "Interop.tt";
            //// Write Dynamic Interop
            //File.WriteAllText(relativePath + @"\SlimDX\CppObjectInterop.cs",
            //                  engine.ProcessTemplate(Utilities.GetResource(host.TemplateFileValue), host));
            //foreach (CompilerError error in host.Errors)
            //{
            //    Console.WriteLine(error.ToString());
            //}
        }


        private void Log(string message, params object[] args)
        {
            Console.WriteLine(message, args);
        }

        private void LogError(string message, params object[] args)
        {
            throw new GeneratorException(message, args);
        }

        private void LogError(string message, Exception ex, params object[] args)
        {
            throw new GeneratorException(message, ex, args);
        }

        /// <summary>
        /// Maps all C++ types to C#
        /// </summary>
        private void MapAll()
        {
            var selectedCSharpType = new List<CSharpCppElement>();

            // Process all Enums

            // Predefine all structs, typedefs and interfaces
            foreach (CppInclude cppInclude in IncludeToProcess)
            {
                try
                {
                    foreach (CppEnum cppEnum in cppInclude.Enums)
                        MapCppEnumToCSharpEnum(cppEnum);
                }
                catch (Exception ex)
                {
                    LogError("Error in include [{0}]", ex, cppInclude.Name);
                }
            }

            // Predefine all structs, typedefs and interfaces
            foreach (CppInclude cppInclude in IncludeToProcess)
            {
                try
                {
                    // Iterate on structs
                    foreach (CppStruct cppStruct in cppInclude.Structs)
                    {
                        CSharpStruct csharpStruct = PrepareStructForMap(cppInclude, cppStruct);
                        if (csharpStruct != null)
                            selectedCSharpType.Add(csharpStruct);
                    }

                    // Iterate on interfaces
                    foreach (CppInterface cppInterface in cppInclude.Interfaces)
                    {
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
                        CSharpFunction cSharpFunction = PrepareFunctionForMap(cppInclude, cppFunction);
                        if (cSharpFunction != null)
                            selectedCSharpType.Add(cSharpFunction);
                    }                    
                }
                catch (Exception ex)
                {
                    LogError("Error in include [{0}]", ex, cppInclude.Name);
                }
            }

            // MAp all typedef to final CSharpType
            foreach (CppInclude cppInclude in IncludeToProcess)
            {
                // Iterate on structs
                foreach (CppTypedef cppTypedef in cppInclude.Typedefs)
                {
                    if (string.IsNullOrEmpty(cppTypedef.Specifier) && !cppTypedef.IsArray)
                    {
                        CSharpType type;
                        if (_mapCppNameToCSharpType.TryGetValue(cppTypedef.GetTypeNameWithMapping(), out type))
                        {
                            if (!_mapCppNameToCSharpType.ContainsKey(cppTypedef.Name))
                                MapCppNameToCSharpType(cppTypedef.Name, type);
                        }
                    }
                }
            }

            // Transform structures
            foreach (CSharpStruct cSharpStruct in selectedCSharpType.OfType<CSharpStruct>())
            {
                try
                {
                    MapCppStructToCSharpStruct(cSharpStruct);
                    // Add Constants to Struct
                    AttachConstants(cSharpStruct);
                }
                catch (Exception ex)
                {
                    CppInclude cppInclude = (cSharpStruct.CppElement != null) ? cSharpStruct.CppElement.ParentInclude : null;
                    LogError("Error on struct [{0}] mapped to [{1}] from include [{2}]", ex, cSharpStruct.CppElementName, cSharpStruct.FullName, cppInclude);
                }
            }

            // Transform interfaces
            foreach (CSharpInterface cSharpInterface in selectedCSharpType.OfType<CSharpInterface>())
            {
                try
                {
                    MapCppInterfaceToCSharpInterface(cSharpInterface);
                    // Add Constants to Interface
                    AttachConstants(cSharpInterface);
                }
                catch (Exception ex)
                {
                    CppInclude cppInclude = (cSharpInterface.CppElement != null) ? cSharpInterface.CppElement.ParentInclude : null;
                    LogError("Error on interface [{0}] mapped to [{1}] from include [{2}]", ex, cSharpInterface.CppElementName, cSharpInterface.FullName, cppInclude);
                }
            }

            // Transform Functions
            foreach (CSharpFunction cSharpFunction in selectedCSharpType.OfType<CSharpFunction>())
            {
                try {
                    MapCppFunctionToCSharpFunction(cSharpFunction);
                }
                catch (Exception ex)
                {
                    CppInclude cppInclude = (cSharpFunction.CppElement != null) ? cSharpFunction.CppElement.ParentInclude : null;
                    LogError("Error on function [{0}] mapped to [{1}] from include [{2}]", ex, cSharpFunction.CppElementName, cSharpFunction.FullName, cppInclude);
                }
            }

            // Add constant to FunctionGroup
            foreach (CSharpAssembly cSharpAssembly in Assemblies)
                foreach (var ns in cSharpAssembly.Namespaces)
                    foreach (var cSharpFunctionGroup in ns.FunctionGroups)
                        AttachConstants(cSharpFunctionGroup);
        }


        /// <summary>
        /// Maps a C++ type name to a C# class
        /// </summary>
        /// <param name="cppName">Name of the CPP.</param>
        /// <param name="type">The type.</param>
        private void MapCppNameToCSharpType(string cppName, CSharpType type)
        {
            if (_mapCppNameToCSharpType.ContainsKey(cppName))
            {
                var old = _mapCppNameToCSharpType[cppName];
                LogError("Mapping Cpp element [{0}] to CSharp type [{1}/{2}] is already mapped to [{3}/{4}]", cppName, type.CppElementName, type.FullName, old.CppElementName, old.FullName);
            }
            _mapCppNameToCSharpType.Add(cppName, type);
        }

        /// <summary>
        /// Maps a C++ Enum to a C# enum.
        /// </summary>
        /// <param name="cppEnum">the c++ enum.</param>
        private void MapCppEnumToCSharpEnum(CppEnum cppEnum)
        {
            // Get the namespace for this particular include and enum
            CSharpNamespace nameSpace = ResolveNamespace(cppEnum);

            // Create the enum
            var newEnum = new CSharpEnum();
            newEnum.Name = ConvertCppNameToCSharpName(cppEnum);
            newEnum.CppElement = cppEnum;
            nameSpace.Add(newEnum);
            MapCppNameToCSharpType(cppEnum.Name, newEnum);

            // Determine enum type. Default is int
            string typeName = cppEnum.GetTypeNameWithMapping();
            switch (typeName)
            {
                case "byte":
                    newEnum.Type = typeof(byte);
                    newEnum.SizeOf = 1;
                    break;
                case "short":
                    newEnum.Type = typeof(short);
                    newEnum.SizeOf = 1;
                    break;
                case "int":
                    newEnum.Type = typeof(int);
                    newEnum.SizeOf = 4;
                    break;
                default:
                    LogError("Invalid type [{0}] for enum [{1}]. Types supported are : int, byte, short", typeName, cppEnum);
                    break;
            }

            // Find Root Name of this enum
            // All enum items should start with the same root name and the root name should be at least 4 chars
            string rootName = cppEnum.Name;
            string rootNameFound = null;
            bool isRootNameFound = false;
            for (int i = rootName.Length; i >= 4 && !isRootNameFound; i--)
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
                rootName = rootNameFound;


            // Create enum items for enum
            foreach (CppEnumItem cppEnumItem in cppEnum.Items)
            {
                string enumName = ConvertCppNameToCSharpName(cppEnumItem, rootName);
                string enumValue = _macroParser.Parse(cppEnumItem.Value);

                var csharpEnumItem = new CSharpEnum.Item(enumName, enumValue) { CppElement = cppEnumItem };

                newEnum.Add(csharpEnumItem);

                if (cppEnumItem.Name != "None")
                    MapCppNameToCSharpType(cppEnumItem.Name, csharpEnumItem);
            }

            // If C++ enum name is ending with FLAG OR FLAGS
            // Then tag this enum as flags and add None if necessary
            if (cppEnum.Name.EndsWith("FLAG") || cppEnum.Name.EndsWith("FLAGS"))
            {
                newEnum.IsFlag = true;

                bool noneIsFound = newEnum.Items.Cast<CSharpEnum.Item>().Any(item => item.Name == "None");

                if (!noneIsFound)
                {
                    var csharpEnumItem = new CSharpEnum.Item("None", "0");
                    csharpEnumItem.CppElement = new CppElement { Description = "None." };
                    newEnum.Add(csharpEnumItem);
                }
            }
        }

        /// <summary>
        /// Prepares C++ struct for mapping. This method is creating the associated C# struct.
        /// </summary>
        /// <param name="cppInclude">The CPP include.</param>
        /// <param name="cppStruct">The CPP struct.</param>
        /// <returns></returns>
        private CSharpStruct PrepareStructForMap(CppInclude cppInclude, CppStruct cppStruct)
        {
            // If a struct is already mapped, it means that there is already a predefined mapping
            if (_mapCppNameToCSharpType.ContainsKey(cppStruct.Name))
                return null;

            // Create a new C# struct
            CSharpNamespace nameSpace = ResolveNamespace(cppStruct);
            var cSharpStruct = new CSharpStruct(cppStruct);
            cSharpStruct.Name = ConvertCppNameToCSharpName(cppStruct);
            // IsFullyMapped to false => The structure is being mapped
            cSharpStruct.IsFullyMapped = false;

            // Add the C# struct to its namepsace
            nameSpace.Add(cSharpStruct);

            // Map the C++ name to the C# struct
            MapCppNameToCSharpType(cppStruct.Name, cSharpStruct);
            return cSharpStruct;
        }


        /// <summary>
        /// Maps the C++ struct to C# struct.
        /// </summary>
        /// <param name="cSharpStruct">The c sharp struct.</param>
        private void MapCppStructToCSharpStruct(CSharpStruct cSharpStruct)
        {
            // If a struct was already mapped, then return immediatly
            // The method MapCppStructToCSharpStruct can be called recursivelly
            if (cSharpStruct.IsFullyMapped)
                return;

            // Get the associated CppStruct and CSharpTag
            var cppStruct = (CppStruct)cSharpStruct.CppElement;
            bool hasMarshalType = cSharpStruct.HasMarshalType;

            // If this structure need to me moved to anoter container, move it now
            foreach (var keyValuePair in _mapMoveStructToInner)
            {
                if (keyValuePair.Key.Match(cSharpStruct.CppElementName).Success)
                {
                    string cppName = keyValuePair.Key.Replace(cSharpStruct.CppElementName, keyValuePair.Value);
                    var destSharpStruct = (CSharpStruct)_mapCppNameToCSharpType[cppName];
                    // Remove the struct from his container
                    cSharpStruct.ParentContainer.Remove(cSharpStruct);
                    // Add this struct to the new container struct
                    destSharpStruct.Add(cSharpStruct);
                }
            }

            // Current offset of a field
            int currentOffset = 0;

            // Offset stored for each field
            int[] offsetOfFields = new int[cppStruct.InnerElements.Count];

            // Last field offset
            int lastCppFieldOffset = -1;

            // Size of the last field
            int lastFieldSize = 0;

            // 
            int maxSizeOfField = 0;

            bool isInUnion = false;

            int cumulatedBitOffset = 0;

            // -------------------------------------------------------------------------------
            // Iterate on all fields and perform mapping
            // -------------------------------------------------------------------------------
            for (int fieldIndex = 0; fieldIndex < cppStruct.InnerElements.Count; fieldIndex++)
            {
                CppField cppField = cppStruct.InnerElements[fieldIndex] as CppField;

                CSharpType publicType;
                CSharpType marshalType = null;
                bool hasArray = cppField.IsArray;
                int fieldSize;
                int arrayDimension = 0;

                string fieldType = cppField.GetTypeNameWithMapping();
                string fieldName = ConvertFieldName(cppField);

                string fieldSpecifier = string.IsNullOrEmpty(cppField.Specifier) ? "" : cppField.Specifier;

                // Resolve from typedef
                TypedefResolve(fieldType, out fieldType, ref fieldSpecifier);

                bool hasPointer = !string.IsNullOrEmpty(fieldSpecifier) && fieldSpecifier.Contains("*");


                // Handle array dimension
                if (!string.IsNullOrWhiteSpace(cppField.ArrayDimension))
                {
                    string arrayDimensionValue = cppField.ArrayDimension;

                    CSharpType arrayDimensionType;
                    bool hasArrayDimensionPtr = false;
                    if (FindType(cppField.ArrayDimension, out arrayDimensionType, ref hasArrayDimensionPtr))
                    {
                        if (arrayDimensionType is CSharpEnum.Item)
                        {
                            arrayDimensionValue = (arrayDimensionType as CSharpEnum.Item).Value;
                        }
                        else
                        {
                            throw new ArgumentException(string.Format("Invalid array dimension {0}", arrayDimensionValue));
                        }
                    }
                    arrayDimension = (int)float.Parse(arrayDimensionValue, CultureInfo.InvariantCulture);
                }

                // Default IntPtr type for pointer, unless modified by specialized type (like char* map to string)
                if (hasPointer)
                {
                    publicType = ImportType(typeof(IntPtr));

                    // Pointer has a variable size depending on x86/x64 architecture, so set field size to -1
                    fieldSize = 8;

                    switch (fieldType)
                    {
                        case "char":
                            publicType = ImportType(typeof(string));
                            marshalType = ImportType(typeof(IntPtr));
                            hasMarshalType = true;
                            break;
                        case "wchar_t":
                            publicType = ImportType(typeof(string));
                            marshalType = ImportType(typeof(IntPtr));
                            hasMarshalType = true;
                            break;
                    }
                }
                else
                {
                    switch (fieldType)
                    {
                        case "int":
                        case "long":
                            fieldSize = 4;
                            publicType = ImportType(typeof(int));
                            if (arrayDimension == 4)
                            {
                                fieldSize = 4 * 4;
                                publicType = ImportTypeFromName(Global.Name + ".Int4", 4 * 4, false, true);
                                arrayDimension = 0;
                                hasArray = false;
                            }
                            break;
                        case "short":
                            fieldSize = 2;
                            publicType = ImportType(typeof(short));
                            break;
                        case "float":
                            fieldSize = 4;
                            publicType = ImportType(typeof(float));

                            if (arrayDimension == 3)
                            {
                                fieldSize = 3 * 4;
                                publicType = ImportTypeFromName("SlimMath.Vector3", 3 * 4, false, true);
                                arrayDimension = 0;
                                hasArray = false;
                            }
                            else if (arrayDimension == 4)
                            {
                                fieldSize = 4 * 4;
                                publicType = ImportTypeFromName("SlimMath.Vector4", 4 * 4, false, true);
                                arrayDimension = 0;
                                hasArray = false;
                            }
                            break;
                        case "double":
                            fieldSize = 8;
                            publicType = ImportType(typeof(double));
                            break;
                        case "BOOL":
                            fieldSize = 4;
                            publicType = ImportType(typeof(bool));
                            marshalType = ImportType(typeof(int));
                            break;
                        case "byte":
                            fieldSize = 1;
                            publicType = ImportType(typeof(byte));
                            break;
                        case "__int64":
                            fieldSize = 8;
                            publicType = ImportType(typeof(long));
                            break;
                        case "SIZE_T":
                            fieldSize = 8;
                            publicType = ImportTypeFromName(Global.Name + ".Size", 4, false, false);
                            publicType.Type = typeof(IntPtr);
                            break;
                        case "char":
                            fieldSize = 1;
                            publicType = ImportType(typeof(byte));
                            if (hasArray)
                            {
                                publicType = ImportType(typeof(string));
                                marshalType = ImportType(typeof(byte));
                                hasMarshalType = true;
                            }
                            break;
                        case "wchar_t":
                            fieldSize = 2;
                            publicType = ImportType(typeof(char));
                            if (hasArray)
                            {
                                publicType = ImportType(typeof(string));
                                marshalType = ImportType(typeof(char));
                                hasMarshalType = true;
                            }
                            break;
                        case "D3DCOLOR":
                            fieldSize = 4;
                            FindType("D3DCOLOR", out publicType, ref hasPointer);
                            marshalType = ImportType(typeof(int));
                            hasMarshalType = true;
                            break;
                        default:
                            // Try to get a declared struct
                            // If it fails, then this struct is unknown
                            if (!FindType(fieldType, out publicType, ref hasPointer))
                            {
                                throw new ArgumentException("Unknown Structure!");
                            }
                            if (publicType is CSharpStruct)
                            {
                                var referenceStruct = publicType as CSharpStruct;

                                // If a structure was not already parsed, then parsed it before going further
                                if (!referenceStruct.IsFullyMapped)
                                {
                                    MapCppStructToCSharpStruct(referenceStruct);
                                }


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

                // Force fieldSize to 8 if this is a pointer
                if (hasPointer)
                {
                    fieldSize = 8;
                }

                if (arrayDimension > 1)
                    fieldSize = fieldSize * arrayDimension;

                if (hasArray)
                {
                    hasMarshalType = true;
                }
                var fieldStruct = new CSharpStruct.Field(cppField, publicType, marshalType, fieldName);

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
                fieldStruct.IsBitField = cppField.IsBitField;

                // Handle bit fields : calculate BitOffset and BitMask for this field
                if (lastCppFieldOffset != cppField.Offset)
                {
                    cumulatedBitOffset = 0;
                }
                if (cppField.IsBitField)
                {
                    int lastCumulatedBitOffset = cumulatedBitOffset;
                    cumulatedBitOffset += cppField.BitOffset;
                    fieldStruct.BitMask = ((1 << (cumulatedBitOffset + 1)) - 1); // &~((1 << (lastCumulatedBitOffset + 1)) - 1);
                    fieldStruct.BitOffset = lastCumulatedBitOffset;
                }

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
            cSharpStruct.SizeOf = currentOffset + lastFieldSize;
            cSharpStruct.HasMarshalType = hasMarshalType;
            cSharpStruct.IsFullyMapped = true;


            if (sizeOfWriter == null)
                sizeOfWriter = new StreamWriter("sizeof_test.cpp");

            sizeOfWriter.WriteLine(@"if ( sizeof({1}) != {2} ) printf(""%s,%s,%d,%d\n"",""{0}"", ""{1}"",sizeof({1}), {2});", cppStruct.Parent.Name, cppStruct.Name, cSharpStruct.SizeOf);
            sizeOfWriter.Flush();
        }

        private static StreamWriter sizeOfWriter;

        private CSharpFunction PrepareFunctionForMap(CppInclude cppInclude, CppFunction cppFunction)
        {
            var cSharpFunction = new CSharpFunction(cppFunction);

            // All functions must have a tag
            var tag = cppFunction.GetTagOrDefault<CSharpTag>();

            if (tag == null || tag.FunctionGroup == null)
                throw new ArgumentException("CppFunction " + cppFunction.Name + " is not tagged and attached to any FunctionGroup");

            // Set the DllName for this CSharpFunction
            cSharpFunction.DllName = tag.FunctionDllName;

            // Add the CSharpFunction to the CSharpFunctionGroup
            tag.FunctionGroup.Add(cSharpFunction);

            // Map the C++ name to the CSharpType
            MapCppNameToCSharpType(cppFunction.Name, cSharpFunction);

            return cSharpFunction;
        }

        private CSharpInterface PrepareInterfaceForMap(CppInclude cppInclude, CppInterface cppInterface)
        {
            var cSharpInterface = new CSharpInterface(cppInterface);
            CSharpNamespace nameSpace = ResolveNamespace(cppInclude, cppInterface);
            cSharpInterface.Name = ConvertCppNameToCSharpName(cppInterface);
            nameSpace.Add(cSharpInterface);

            // Associate Parent
            CSharpType parentType;
            bool hasPointer = false;
            if (FindType(cppInterface.ParentName, out parentType, ref hasPointer))
            {
                cSharpInterface.Parent = parentType;
            }
            else
            {
                if (!cSharpInterface.IsCallback)
                    cSharpInterface.Parent = DefaultInterfaceCppObject;
            }

            MapCppNameToCSharpType(cppInterface.Name, cSharpInterface);
            return cSharpInterface;
        }

        private string ConvertFieldName(CppField cppField)
        {
            string name = ConvertCppNameToCSharpName(cppField);
            if (CSharpKeywords.IsKeyword(name))
                name = "@" + name;
            return name;
        }

        private string ConvertMethodParameterName(CppParameter cppParameter)
        {
            string name = ConvertCppNameToCSharpName(cppParameter);
            bool hasPointer = !string.IsNullOrEmpty(cppParameter.Specifier) &&
                              (cppParameter.Specifier.Contains("*") || cppParameter.Specifier.Contains("&"));
            if (hasPointer)
            {
                if (name.ToLower().StartsWith("pp"))
                    name = name.Substring(2) + "Ref";
                else if (name.ToLower().StartsWith("p"))
                    name = name.Substring(1) + "Ref";
            }
            if (char.IsDigit(name[0]))
                name = "arg" + name;
            name = new string(name[0], 1).ToLower() + name.Substring(1);

            if (CSharpKeywords.IsKeyword(name))
                name = "@" + name;
            return name;
        }

        private CSharpMapType MapReturnParameter(CppMethod method)
        {
            CppType cpptype = method.ReturnType;
            CSharpType publicType = null;
            CSharpType marshalType = null;

            string paramType = cpptype.GetTypeNameWithMapping();
            string paramSpecifier = string.IsNullOrEmpty(cpptype.Specifier) ? "" : cpptype.Specifier;
            // Resolve from typedef
            TypedefResolve(paramType, out paramType, ref paramSpecifier);

            bool hasPointer = paramSpecifier.Contains("*");

            switch (paramType)
            {
                case "void":
                    publicType = ImportType(typeof(void));
                    break;
                case "int":
                case "long":
                    publicType = ImportType(typeof(int));
                    break;
                case "short":
                    publicType = ImportType(typeof(short));
                    break;
                case "float":
                    publicType = ImportType(typeof(float));
                    break;
                case "double":
                    publicType = ImportType(typeof(double));
                    break;
                case "BOOL":
                    publicType = ImportType(typeof(bool));
                    marshalType = ImportType(typeof(int));
                    break;
                case "byte":
                    publicType = ImportType(typeof(byte));
                    marshalType = ImportType(typeof(int));
                    break;
                case "__int64":
                    publicType = ImportType(typeof(long));
                    break;
                case "SIZE_T":
                    publicType = ImportTypeFromName(Global.Name + ".Size", 4, false, false);
                    publicType.Type = typeof(IntPtr);
                    break;
                case "GUID":
                    publicType = ImportType(typeof(Guid));
                    break;
                case "char":
                    publicType = ImportType(typeof(byte));
                    if (hasPointer)
                        publicType = ImportType(typeof(string));
                    break;
                case "wchar_t":
                    publicType = ImportType(typeof(char));
                    if (hasPointer)
                        publicType = ImportType(typeof(string));
                    break;
                case "HRESULT":
                    publicType = ImportTypeFromName(Global.Name + ".Result", 4, false, false);
                    marshalType = ImportType(typeof(int));
                    break;
                default:
                    // Try to get a declared struct
                    // If it fails, then this struct is unknown
                    if (!FindType(paramType, out publicType, ref hasPointer))
                    {
                        throw new ArgumentException(string.Format("Unknown return type! {0}", paramType));
                    }
                    //if (!hasPointer)
                    //    throw new ArgumentException("Expecting pointer for param");
                    break;
            }


            if (hasPointer && !(publicType is CSharpInterface))
                publicType = ImportType(typeof(IntPtr));

            if (hasPointer)
                marshalType = ImportType(typeof(IntPtr));

            if (marshalType == null && publicType is CSharpStruct && !hasPointer)
            {
                marshalType = publicType;
            }

            return new CSharpMapType(method.ReturnType, publicType, marshalType, "");
        }


        private void RegisterNativeInterop(CSharpMethod method)
        {
            var cSharpInteropCalliSignature = new CSharpInteropCalliSignature();

            // Handle Return Type parameter
            // MarshalType.Type == null, then check that it is a structure
            if (method.ReturnType.PublicType is CSharpStruct)
            {
                // Return type and 1st parameter are implicitly a pointer to the structure to fill 
                cSharpInteropCalliSignature.ReturnType = typeof(void*);
                cSharpInteropCalliSignature.ParameterTypes.Add(typeof(void*));
            }
            else if (method.ReturnType.MarshalType.Type != null)
            {
                Type type = method.ReturnType.MarshalType.Type;
                if (type == typeof(IntPtr))
                    type = typeof(void*);
                cSharpInteropCalliSignature.ReturnType = type;
            }
            else
            {
                throw new ArgumentException(string.Format("Invalid return type {0} for method {1}", method.ReturnType.PublicType.FullName, method.CppElement));
            }

            // Handle Parameters
            foreach (var param in method.Parameters)
            {
                if (param.MarshalType.Type == null)
                {
                    if (param.PublicType is CSharpStruct)
                    {
                        // If parameter is a struct, then a LocalInterop is needed
                        cSharpInteropCalliSignature.ParameterTypes.Add(param.PublicType.FullName);
                        cSharpInteropCalliSignature.IsLocal = true;
                    }
                    else
                    {
                        throw new ArgumentException(string.Format("Invalid parameter {0} for method {1}", param.PublicType.FullName, method.CppElement));
                    }
                }
                else
                {
                    Type type = param.MarshalType.Type;
                    if (type == typeof(IntPtr))
                        type = typeof(void*);
                    cSharpInteropCalliSignature.ParameterTypes.Add(type);
                }
            }

            if (cSharpInteropCalliSignature.IsLocal)
            {
                var assembly = method.GetParent<CSharpAssembly>();
                cSharpInteropCalliSignature = assembly.Interop.Add(cSharpInteropCalliSignature);
            }
            else
            {
                cSharpInteropCalliSignature = _registeredInteropCall.Add(cSharpInteropCalliSignature);
            }

            method.Interop = cSharpInteropCalliSignature;
        }


        private void BuildCSharpMethodFromCppMethod(string cppPathContext, CSharpMethod cSharpMethod)
        {
            CppMethod cppMethod = (CppMethod)cSharpMethod.CppElement;

            if (!string.IsNullOrEmpty(cppPathContext))
                cppPathContext = cppPathContext + "::";

            cppPathContext += cppMethod.Name;

            cSharpMethod.Name = ConvertCppNameToCSharpName(cppMethod);
            cSharpMethod.Offset = cppMethod.Offset;

            bool isWideChar = false;

            cSharpMethod.ReturnType = MapReturnParameter(cppMethod);

            foreach (CppParameter cppParameter in cppMethod.Parameters)
            {
                CSharpType publicType = null;
                CSharpType marshalType = null;

                var cppAttribute = cppParameter.Attribute;

                bool hasArray = cppParameter.IsArray || ((cppAttribute & CppAttribute.Buffer) != 0);
                int arrayDimension = string.IsNullOrWhiteSpace(cppParameter.ArrayDimension)
                                         ? 0
                                         : int.Parse(cppParameter.ArrayDimension);
                //string paramType = cppParameter.GetTypeName(); //GetFinalCppType(cppParameter.Type);
                string paramType = cppParameter.GetTypeNameWithMapping();
                string paramName = ConvertMethodParameterName(cppParameter);


                var paramSpecifier = !string.IsNullOrEmpty(cppParameter.Specifier) ? cppParameter.Specifier : "";
                // Resolve from typedef
                TypedefResolve(paramType, out paramType, ref paramSpecifier);

                bool hasPointer = paramSpecifier.Contains("*") || paramSpecifier.Contains("&");
                bool isOptional = (cppAttribute & CppAttribute.Optional) != 0;

                if (hasArray)
                    hasPointer = true;

                //var mapInterfaceField = FindMapInterfaceField(cSharpInterface.CppElement.Name, cppField.Name);
                //if (mapInterfaceField.FieldName != null)
                //    paramName = mapInterfaceField.FieldName;
                //if (mapInterfaceField.NativeFieldType != null)
                //    paramType = mapInterfaceField.NativeFieldType;



                CSharpMethod.ParameterAttribute parameterAttribute = CSharpMethod.ParameterAttribute.In;

                if (paramType.ToLower() == "void" && !hasPointer)
                    continue;

                switch (paramType)
                {
                    case "int":
                    case "long":
                        publicType = ImportType(typeof(int));
                        if (arrayDimension == 4)
                        {
                            publicType = ImportTypeFromName(Global.Name + ".Int4", 4 * 4, false, true);
                            arrayDimension = 0;
                            hasArray = false;
                        }
                        break;
                    case "short":
                        publicType = ImportType(typeof(short));
                        break;
                    case "float":
                        publicType = ImportType(typeof(float));

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
                    case "double":
                        publicType = ImportType(typeof(double));
                        //if (arrayDimension == 3)
                        //{
                        //    publicType = ImportTypeFromName("SlimMath.Vector3", 3 * 4, false, true);
                        //    arrayDimension = 0;
                        //    hasArray = false;
                        //}
                        //else if (arrayDimension == 4)
                        //{
                        //    publicType = ImportTypeFromName("SlimMath.Vector4", 4 * 4, false, true);
                        //    arrayDimension = 0;
                        //    hasArray = false;
                        //}
                        break;
                    case "BOOL":
                        publicType = ImportType(typeof(bool));
                        marshalType = ImportType(typeof(int));
                        break;
                    case "byte":
                        publicType = ImportType(typeof(byte));
                        marshalType = ImportType(typeof(int));
                        break;
                    case "__int64":
                        publicType = ImportType(typeof(long));
                        break;
                    case "SIZE_T":
                        publicType = ImportTypeFromName(Global.Name + ".Size", 4, false, false);
                        publicType.Type = typeof(IntPtr);
                        break;
                    case "GUID":
                        publicType = ImportType(typeof(Guid));
                        if (cppAttribute == CppAttribute.None)
                            cppAttribute = CppAttribute.In;
                        break;
                    case "char":
                        publicType = ImportType(typeof(byte));
                        if (hasPointer)
                            publicType = ImportType(typeof(string));
                        if (hasArray)
                        {
                            publicType = ImportType(typeof(string));
                            marshalType = ImportType(typeof(byte));
                        }
                        break;
                    case "wchar_t":
                        isWideChar = true;
                        publicType = ImportType(typeof(char));
                        if (hasPointer)
                            publicType = ImportType(typeof(string));
                        if (hasArray)
                        {
                            publicType = ImportType(typeof(string));
                            marshalType = ImportType(typeof(char));
                            // Then this is more likely a plain string
                            hasArray = false;
                        }
                        break;
                    case "void":
                        publicType = ImportType(typeof(IntPtr));

                        //if ((cppAttribute & CppAttribute.Buffer) != 0)
                        //{
                        //    hasArray = false;
                        //    cppAttribute = cppAttribute & ~CppAttribute.Buffer;
                        //}
                        //hasPointer = true;

                        break;
                    //case "LPD3D10INCLUDE":
                    //    hasPointer = true;
                    //    if (!FindType("ID3DInclude", out publicType, ref hasPointer))
                    //        throw new ArgumentException("Unknown type : " + paramType);
                    //    break;
                    case "ID3D10Effect":
                        publicType = ImportType(typeof(IntPtr));
                        break;
                    case "D3DCOLOR":
                        FindType("D3DCOLOR", out publicType, ref hasPointer);
                        marshalType = ImportType(typeof(int));
                        break;
                    default:
                        // Try to get a declared struct
                        // If it fails, then this struct is unknown
                        if (!FindType(paramType, out publicType, ref hasPointer))
                        {
                            throw new ArgumentException("Unknown type : " + paramType);
                        }
                        //if (!hasPointer)
                        //    throw new ArgumentException("Expecting pointer for param");
                        break;
                }

                // --------------------------------------------------------------------------------
                // Pointer - Handle special cases
                // --------------------------------------------------------------------------------
                if (hasPointer)
                {
                    marshalType = ImportType(typeof(IntPtr));

                    // --------------------------------------------------------------------------------
                    // Handling Parameter Interface
                    // --------------------------------------------------------------------------------
                    if (publicType is CSharpInterface)
                    {
                        // Force Interface** to be CppAttribute.Out when None
                        if (cppAttribute == CppAttribute.None)
                        {
                            if (paramSpecifier == "**")
                                cppAttribute = CppAttribute.Out;
                        }

                        if ((cppAttribute == CppAttribute.None ||
                            (cppAttribute & CppAttribute.In) != 0) || (cppAttribute & CppAttribute.InOut) != 0)
                        {
                            parameterAttribute = CSharpMethod.ParameterAttribute.In;

                            // Force all array of interface to support null
                            if (hasArray)
                            {
                                isOptional = true;
                            }

                            // If Interface is a callback, use IntPtr as a public marshalling type
                            CSharpInterface publicInterface = (CSharpInterface)publicType;
                            if (publicInterface.IsCallback)
                            {
                                publicType = ImportType(typeof(IntPtr));
                                // By default, set the Visibility to internal for methods using callbacks
                                // as we need to provide user method. Don't do this on functions as they
                                // are already hidden by the container
                                if (!(cSharpMethod is CSharpFunction))
                                {
                                    cSharpMethod.Visibility = Visibility.Internal;
                                    cSharpMethod.Name = cSharpMethod.Name + "_";
                                }
                            }
                        }
                        //else if ((cppParameter.Attribute & CppAttribute.InOut) != 0)
                        //    parameterAttribute = CSharpMethod.ParameterAttribute.Ref;
                        else if ((cppAttribute & CppAttribute.Out) != 0)
                            parameterAttribute = CSharpMethod.ParameterAttribute.Out;
                    }
                    else
                    {
                        // --------------------------------------------------------------------------------
                        // Handling Parameter Interface
                        // --------------------------------------------------------------------------------


                        if (cppAttribute == CppAttribute.None ||
                            (cppAttribute & CppAttribute.In) != 0)
                        {
                            parameterAttribute = publicType.Type == typeof(IntPtr) || publicType.Name == Global.Name + ".FunctionCallback" ||
                                                 publicType.Type == typeof(string)
                                                     ? CSharpMethod.ParameterAttribute.In
                                                     : ((cppAttribute & CppAttribute.In) != 0 ? CSharpMethod.ParameterAttribute.RefIn : CSharpMethod.ParameterAttribute.Ref);
                            //parameterAttribute = CSharpMethod.ParameterAttribute.Ref;
                        }
                        else if ((cppAttribute & CppAttribute.InOut) != 0)
                        {
                            if ((cppAttribute & CppAttribute.Optional) != 0)
                            {
                                publicType = ImportType(typeof(IntPtr));
                                parameterAttribute = CSharpMethod.ParameterAttribute.In;
                            }
                            else
                            {
                                parameterAttribute = CSharpMethod.ParameterAttribute.Ref;
                            }

                        }
                        else if ((cppAttribute & CppAttribute.Out) != 0)
                            parameterAttribute = CSharpMethod.ParameterAttribute.Out;

                        // Handle void* with Buffer attribute
                        if (paramType == "void" && (cppAttribute & CppAttribute.Buffer) != 0)
                        {
                            hasArray = false;
                            arrayDimension = 0;
                            parameterAttribute = CSharpMethod.ParameterAttribute.In;
                        }
                        else if (publicType.Type == typeof(string) && (cppAttribute & CppAttribute.Out) != 0)
                        {
                            publicType = ImportType(typeof(IntPtr));
                            parameterAttribute = CSharpMethod.ParameterAttribute.In;
                            hasArray = false;
                        }
                        else if (publicType is CSharpStruct &&
                                 (parameterAttribute == CSharpMethod.ParameterAttribute.Out || hasArray || parameterAttribute == CSharpMethod.ParameterAttribute.RefIn || parameterAttribute == CSharpMethod.ParameterAttribute.Ref))
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

                var paramMethod = new CSharpMethod.Parameter(cppParameter, publicType, marshalType,
                                                             paramName);
                paramMethod.IsArray = hasArray;
                paramMethod.ArrayDimension = arrayDimension;
                paramMethod.Attribute = parameterAttribute;
                paramMethod.IsOptionnal = isOptional;
                paramMethod.IsWideChar = isWideChar;
                paramMethod.HasPointer = hasPointer;

                //if (marshalType.Type == typeof (IntPtr))
                //{
                //    marshalMethodTypes.Add(typeof (void*));
                //}
                //else
                //{
                //    if (publicType is CSharpStruct && !hasPointer && marshalType.Type == null)
                //    {
                //        CSharpStruct cSharpStruct = publicType as CSharpStruct;
                //        foreach (var field in cSharpStruct.Fields)
                //            marshalMethodTypes.Add(field.MarshalType.Type);
                //    }
                //    else
                //    {
                //        marshalMethodTypes.Add(marshalType.Type);
                //    }
                //}

                cSharpMethod.Add(paramMethod);
            }
        }

        private void TypedefResolve(string cppTypeName, out string newTypeName, ref string pointerSpecifier)
        {
            CppTypedef typedef;

            newTypeName = cppTypeName;
            while (_mapTypedefToType.TryGetValue(newTypeName, out typedef))
            {
                if (newTypeName == typedef.Type)
                    break;
                newTypeName = typedef.Type;
                if (typedef.Specifier != null && typedef.Specifier.Contains("*"))
                    pointerSpecifier += typedef.Specifier;
            }
        }

        private bool FindType(string cppTypeName, out CSharpType publicType, ref bool hasPointer)
        {
            bool isFound = _mapCppNameToCSharpType.TryGetValue(cppTypeName, out publicType);

            // Handle special case where LPXXX is not registered, but with have XXX type
            // Assume that it is a XXX*
            if (!isFound && cppTypeName.StartsWith("LP"))
            {
                isFound = _mapCppNameToCSharpType.TryGetValue(cppTypeName.Substring(2), out publicType);
                hasPointer = true;
            }
            return isFound;
        }

        private void MapCppInterfaceToCSharpInterface(CSharpInterface cSharpInterface)
        {
            var cppInterface = cSharpInterface.CppElement as CppInterface;

            // Setup GUID from CppGuid if any
            string guidName = "IID_" + cppInterface.Name;
            CppGuid cppGuid = (from guid in CppIncludeGroup.Find<CppGuid>(".*")
                               where guid.Name == guidName
                               select guid).FirstOrDefault();
            if (cppGuid != null && cSharpInterface.Guid == null)
                cSharpInterface.Guid = cppGuid.Guid.ToString();

            // Handle Methods
            List<CSharpMethod> generatedMethods = new List<CSharpMethod>();
            foreach (CppMethod cppMethod in cppInterface.Methods)
            {
                var cSharpMethod = new CSharpMethod(cppMethod);
                generatedMethods.Add(cSharpMethod);
                cSharpInterface.Add(cSharpMethod);

                BuildCSharpMethodFromCppMethod(cppInterface.Name, cSharpMethod);

                RegisterNativeInterop(cSharpMethod);

                MapCppNameToCSharpType(cppInterface.Name + "::" + cppMethod.Name, cSharpMethod);
            }

            // Dispatch method to inner interface if any
            var mapInnerInterface = new Dictionary<string, CSharpInterface>();
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
                            {
                                innerInterface.Parent = parentInterface;
                            }
                            else
                            {
                                innerInterface.Parent = DefaultInterfaceCppObject;
                            }

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

            // If CSharpInterface is DualCallback, then need to generate a default implem
            if (cSharpInterface.IsDualCallback)
            {
                var tagForInterface = cppInterface.GetTagOrDefault<CSharpTag>();
                CSharpInterface nativeCallback = new CSharpInterface(cSharpInterface.CppElement as CppInterface);
                nativeCallback.Name = cSharpInterface.Name + "Native";
                nativeCallback.Visibility = Visibility.Internal;

                // Update nativeCallback from tag
                if (tagForInterface != null)
                {
                    if (tagForInterface.NativeCallbackVisibility.HasValue)
                        nativeCallback.Visibility = tagForInterface.NativeCallbackVisibility.Value;
                    if (tagForInterface.NativeCallbackName != null)
                        nativeCallback.Name = tagForInterface.NativeCallbackName;
                }

                nativeCallback.Parent = cSharpInterface.Parent;

                // If Parent is a DualInterface, then inherit from Default Callback
                if (cSharpInterface.Parent is CSharpInterface)
                {
                    var parentInterface = cSharpInterface.Parent as CSharpInterface;
                    if (parentInterface.IsDualCallback)
                        nativeCallback.Parent = parentInterface.DefaultImplem;
                }

                nativeCallback.IParent = cSharpInterface;
                cSharpInterface.DefaultImplem = nativeCallback;

                foreach (var innerElement in cSharpInterface.Items)
                {
                    if (innerElement is CSharpMethod)
                    {
                        var method = (CSharpMethod)innerElement;
                        CSharpMethod newMethod = (CSharpMethod)method.Clone();
                        newMethod.Visibility = Visibility.Internal;
                        newMethod.Name = newMethod.Name + "_";
                        nativeCallback.Add(newMethod);
                    }
                    else
                    {
                        Console.WriteLine("Unhandled innerElement {0} for DualCallbackInterface {1}", innerElement, cSharpInterface.Name);
                    }
                }
                nativeCallback.IsCallback = false;
                nativeCallback.IsDualCallback = true;
                cSharpInterface.ParentContainer.Add(nativeCallback);
            }
            else
            {
                // Refactor Properties
                CreateProperties(generatedMethods);
            }

            // If interface is a callback and parent is ComObject, then remove it
            if (cSharpInterface.IsCallback && cSharpInterface.Parent is CSharpInterface)
            {
                if ((cSharpInterface.Parent as CSharpInterface).FullName == Global.Name + ".ComObject")
                {
                    cSharpInterface.Parent = null;
                }
            }
        }

        private void CreateProperties(List<CSharpMethod> methods)
        {
            Dictionary<string, CSharpProperty> cSharpProperties = new Dictionary<string, CSharpProperty>();

            foreach (var cSharpMethod in methods)
            {
                bool isIs = cSharpMethod.Name.StartsWith("Is");
                bool isGet = cSharpMethod.Name.StartsWith("Get") || isIs;
                bool isSet = cSharpMethod.Name.StartsWith("Set");
                if (!(isGet || isSet))
                    continue;
                string propertyName = isIs ? cSharpMethod.Name : cSharpMethod.Name.Substring("Get".Length);

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
                        (parameterList[0].IsRefIn || parameterList[0].IsIn || parameterList[0].IsRef))
                    {
                        property.Setter = cSharpMethod;
                        property.PublicType = parameterList[0].PublicType;
                    }
                    else if (parameterCount == 1 && !cSharpMethod.HasReturnType)
                    {
                        property.Setter = cSharpMethod;
                        property.PublicType = property.Setter.ReturnType.PublicType;
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

                CSharpMethod getterOrSetter = property.Getter ?? property.Setter;

                // Associate the property with the Getter element
                property.CppElement = getterOrSetter.CppElement;
                var parent = getterOrSetter.ParentContainer;

                // If Getter has no propery, 
                if ((property.Getter != null && property.Getter.NoProperty) || (property.Setter != null && property.Setter.NoProperty))
                    continue;

                // Update visibility for getter and setter (set to internal)
                if (property.Getter != null)
                    property.Getter.Visibility = Visibility.Internal;

                if (property.Setter != null)
                    property.Setter.Visibility = Visibility.Internal;

                if (property.Getter != null && property.Name.StartsWith("Is"))
                    property.Getter.Name = property.Getter.Name + "_";

                parent.Add(property);
            }
        }


        public void MoveMethodsToInnerInterface(string methodNameRegExp, string innerInterface, string propertyAccess,
                                                 string inheritedInterfaceName = null)
        {
            _mapMoveMethodToInnerInterface.Add(new Regex(methodNameRegExp),
                                               new InnerInterfaceMethod(innerInterface, propertyAccess,
                                                                        inheritedInterfaceName));
        }

        public void MoveStructToInner(string fromStruct, string toStruct)
        {
            _mapMoveStructToInner.Add(new Regex(fromStruct), toStruct);
        }

        private IEnumerable<CppInclude> IncludeToProcess
        {
            get
            {
                // Process all Enums
                return CppIncludeGroup.Includes.Where(cppInclude => _mapIncludeToNamespace.ContainsKey(cppInclude.Name));
            }
        }

        private void MapCppFunctionToCSharpFunction(CSharpFunction cSharpFunction)
        {
            BuildCSharpMethodFromCppMethod("", cSharpFunction);
        }

        private CSharpNamespace ResolveNamespace(CppElement element)
        {
            return ResolveNamespace(element.ParentInclude, element);
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

        public void MapCppTypeToCSharpType(string cppTypeName, CSharpType csharpType)
        {
            MapCppNameToCSharpType(cppTypeName, csharpType);
        }

        public void MapCppTypeToCSharpType(string cppTypeName, string csharpType, int sizeOf = 0,
                                           bool isReference = false, bool isStruct = false)
        {
            MapCppNameToCSharpType(cppTypeName, ImportTypeFromName(csharpType, sizeOf, isReference, isStruct));
        }

        public void MapCppTypeToCSharpType(string cppTypeName, Type csharpType, bool isReference = false)
        {
            MapCppNameToCSharpType(cppTypeName, ImportType(csharpType, isReference));
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

        public CSharpFunctionGroup CreateFunctionGroup(string assembly, string nameSpace, string functionGroupName)
        {
            CSharpNamespace cSharpNameSpace = GetNamespace(assembly, nameSpace);

            foreach (var cSharpFunctionGroup in cSharpNameSpace.FunctionGroups)
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

        private Dictionary<string, List<CSharpConstant>> _mapConstantToCSharpType = new Dictionary<string, List<CSharpConstant>>();

        public void AddConstantFromMacroToCSharpType(string macroRegexp, string fullNameCSharpType, string type, string fieldName = null)
        {
            var macroDefinitions = CppIncludeGroup.Find<CppMacroDefinition>(macroRegexp);
            Regex regex = new Regex(macroRegexp);
            foreach (var macroDef in macroDefinitions)
            {
                string finalFieldName = fieldName == null ? macroDef.Name : ConvertCaseString(regex.Replace(macroDef.Name, fieldName), false);

                AddConstantToCSharpType(fullNameCSharpType, type, finalFieldName, macroDef.Value).Visibility = Visibility.Public | Visibility.Const;
            }
        }

        public CSharpConstant AddConstantToCSharpType(string fullNameCSharpType, string type, string fieldName, string value)
        {
            List<CSharpConstant> constantDefinitions;
            if (!_mapConstantToCSharpType.TryGetValue(fullNameCSharpType, out constantDefinitions))
            {
                constantDefinitions = new List<CSharpConstant>();
                _mapConstantToCSharpType.Add(fullNameCSharpType, constantDefinitions);
            }

            var contantToAdd = new CSharpConstant(type, fieldName, value);
            constantDefinitions.Add(contantToAdd);
            return contantToAdd;
        }

        private void AttachConstants(CSharpContainer cSharpContainer)
        {
            foreach (KeyValuePair<string, List<CSharpConstant>> keyValuePair in _mapConstantToCSharpType)
            {
                if (cSharpContainer.FullName == keyValuePair.Key)
                {
                    foreach (var constantDef in keyValuePair.Value)
                        cSharpContainer.Add(constantDef);
                }
            }
        }

        public void MapIncludeToNamespace(string includeName, string assemblyName, string nameSpace, string outputDirectory = null)
        {
            var cSharpNamespace = GetNamespace(assemblyName, nameSpace);
            cSharpNamespace.OutputDirectory = outputDirectory;
            _mapIncludeToNamespace.Add(includeName, cSharpNamespace);
        }

        public void MapTypeToNamespace(string typeNameRegex, string assemblyName, string nameSpace, string outputDirectory = null)
        {
            var cSharpNamespace = GetNamespace(assemblyName, nameSpace);
            cSharpNamespace.OutputDirectory = outputDirectory;
            _mapTypeToNamespace.Add(new Regex(typeNameRegex), cSharpNamespace);
        }


        public void RenameTypePart(string partName, string replaceString)
        {
            _renameTypePart.Add(new Regex(partName), replaceString);
        }

        private string ConvertCppNameToCSharpName(CppElement cppElement, string rootName = null)
        {
            string originalName = cppElement.Name;
            string name = cppElement.Name;

            bool nameModifiedByTag = false;

            // Handle Tag
            var tag = cppElement.GetTagOrDefault<CSharpTag>();
            if (tag != null && !string.IsNullOrEmpty(tag.MappingName))
            {
                nameModifiedByTag = true;
                name = tag.MappingName;
                // If Final Mapping name then don't proceed further
                if (tag.IsFinalMappingName.HasValue && tag.IsFinalMappingName.Value)
                    return name;
            }

            // Keep underscore for some types
            bool keepUnderscore = false;
            foreach (var keyValuePair in _mapTypeToKeepUnderscore)
            {
                if (keyValuePair.Key.Match(originalName).Success)
                {
                    keepUnderscore = true;
                    break;
                }
            }

            // Rename is tagged as final, then return the string
            // If the string still contains some "_" then continue while processing
            if (!name.Contains("_") && name.ToUpper() != name && char.IsUpper(name[0]))
                return name;

            // Remove Prefix (for enums). Don't modify names that are modified by tag
            if (!nameModifiedByTag && rootName != null && originalName.StartsWith(rootName))
                name = originalName.Substring(rootName.Length, originalName.Length - rootName.Length);

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
            public readonly string InheritedInterfaceName;

            public InnerInterfaceMethod(string innerInterface, string propertyAccess, string inheritedInterfaceName)
            {
                InnerInterface = innerInterface;
                PropertyAccessName = propertyAccess;
                InheritedInterfaceName = inheritedInterfaceName;
            }
        }

        #endregion

    }
}