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
using SlimDX2.Tools.XIDL;
using System.Linq;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpTag
    {
        /// <summary>
        /// General visibility for Methods
        /// </summary>
        public Visibility? Visibility;

        /// <summary>
        /// General visibility for DefaultCallback class
        /// </summary>
        public Visibility? NativeCallbackVisibility;

        /// <summary>
        /// Name of a native callback
        /// </summary>
        public string NativeCallbackName;

        /// <summary>
        /// Used for methods, to force a method to not be translated to a property
        /// </summary>
        public bool? NoProperty;

        /// <summary>
        /// Mapping name
        /// </summary>
        public string MappingName;

        /// <summary>
        /// True if the MappingName doesn't need any further rename processing
        /// </summary>
        public bool? IsFinalMappingName;

        /// <summary>
        /// True if a struct should used a native value type marshalling
        /// </summary>
        public bool? StructHasNativeValueType;

        /// <summary>
        /// True if a struct should be used as a class instead of struct (imply StructHasNativeValueType)
        /// </summary>
        public bool? StructToClass;

        /// <summary>
        /// True if a struct is using some Custom Marshal (imply StructHasNativeValueType)
        /// </summary>
        public bool? StructCustomMarshall;

        /// <summary>
        /// True if a struct is using some a Custom New for the Native struct (imply StructHasNativeValueType)
        /// </summary>
        public bool? StructCustomNew;

        /// <summary>
        /// True to force a struct with Native marshalling to have the method __MarshalTo generated
        /// </summary>
        public bool? StructForceMarshalToToBeGenerated;

        /// <summary>
        /// <summary>
        /// Mapping type name
        /// </summary>
        public string MappingType;

        /// <summary>
        /// Used for enums, to tag enums that are used as flags
        /// </summary>
        public bool? IsEnumFlags;

        /// <summary>
        /// Used for interface to mark them as callback interface
        /// </summary>
        public bool? IsCallbackInterface;

        /// <summary>
        /// Used for interface to mark them as dual-callback interface
        /// </summary>
        public bool? IsDualCallbackInterface;

        /// <summary>
        /// DLL name attached to a function
        /// </summary>
        public string FunctionDllName;

        /// <summary>
        /// Parameter Attribute
        /// </summary>
        public CppAttribute? ParameterAttribute;

        /// <summary>
        /// CSharpFunctionGroup attached to a function
        /// </summary>
        public CSharpFunctionGroup FunctionGroup;
    }

    public static class CppElementExtensions
    {

        /// <summary>
        /// Modify all Get methods that are outputing a parameter but don't specify Out.
        /// Replace "None" attribute to "Out" for those methods
        /// </summary>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        public static void DumpGetMethods(this CppElement element, string regex, StreamWriter log)
        {
            element.Modify<CppMethod>(regex, (pathREgex, elementArg) =>
                                                 {
                                                     CppMethod method = elementArg as CppMethod;
                                                     if (!method.Name.Contains("By") && (method.Name.StartsWith("Get") || method.Name.StartsWith("Is")))
                                                     {
                                                         int paramCount = method.Parameters.Count();
                                                         foreach (var cppParameter in method.Parameters)
                                                         {
                                                             var specifier = cppParameter.Specifier ?? "";
                                                             if (cppParameter.Attribute == CppAttribute.None && specifier.Contains("*"))
                                                             {
                                                                 if ( (paramCount == 1 && cppParameter.Type == "char") || cppParameter.Type == "void")
                                                                     continue;
                                                                 log.WriteLine("group.Modify<CppParameter>(@\"^{0}$\", Modifiers.ParameterAttribute(CppAttribute.Out));", cppParameter.FullName);
                                                                 // cppParameter.Attribute = CppAttribute.Out;
                                                             }
                                                         }
                                                     }
                                                     return false;
                                                 });
        }




        /// <summary>
        /// Tag an element with a new visibility, propery and mapping name.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        /// <param name="visibility"></param>
        /// <param name="noProperty"></param>
        /// <param name="mappingName"></param>
        public static void TagVisibility<T>(this CppElement element, string regex, Visibility? visibility,
                                        bool? noProperty = null, string mappingName = null, bool? isFinalRename = true) where T : CppElement
        {
            element.Modify<T>(regex, Tag(new CSharpTag() { Visibility = visibility, NoProperty = noProperty, MappingName = mappingName, IsFinalMappingName = ((mappingName == null)?null:isFinalRename) }));
        }

        /// <summary>
        /// Tag an element with a new visibility, propery and mapping name.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        /// <param name="visibility"></param>
        /// <param name="noProperty"></param>
        /// <param name="mappingName"></param>
        public static void TagParameter(this CppElement element, string regex, CppAttribute attribute, string typeName = null, string mappingName = null)
        {
            element.Modify<CppParameter>(regex, Tag(new CSharpTag() { ParameterAttribute = attribute, MappingType = typeName, MappingName = mappingName }));
        }


        /// <summary>
        /// Tag an element with a new mapping name.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        /// <param name="mappingName"></param>
        public static void TagName<T>(this CppElement element, string regex, string mappingName, bool? isFinalRename = true)
            where T : CppElement
        {
            element.Modify<T>(regex, Tag(new CSharpTag() { MappingName = mappingName, IsFinalMappingName = isFinalRename}));
        }

        /// <summary>
        /// Tag an element with a new Cpp type name (for fields, parameters, return types...) and a new name
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        /// <param name="typeName"></param>
        public static void TagTypeAndName<T>(this CppElement element, string regex, string typeName, string mappingName = null, bool? isFinalRename = true)
            where T : CppElement
        {
            element.Modify<T>(regex, Tag(new CSharpTag() { MappingType = typeName, MappingName = mappingName, IsFinalMappingName = ((mappingName == null) ? null : isFinalRename) }));
        }

        /// <summary>
        /// Tag an Enum and force it to be interpreted as a flag.
        /// </summary>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        public static void TagEnumFlags(this CppElement element, string regex)         
        {
            element.Modify<CppEnum>(regex, Tag(new CSharpTag() { IsEnumFlags = true }));
        }

        /// <summary>
        /// Tag a function and associate it with a dllName and a function group
        /// </summary>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        public static void TagFunction(this CppElement element, string regex, string dllName, CSharpFunctionGroup group)
        {
            element.Modify<CppFunction>(regex, Tag(new CSharpTag() { FunctionDllName = dllName, FunctionGroup = group}));
        }

        /// <summary>
        /// Tag an interface as callback or dualcallback
        /// </summary>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        public static void TagCallback(this CppElement element, string regex, bool isDual = false, Visibility? visibilityForDefault = null, string nativeCallbackName = null)
        {
            element.Modify<CppInterface>(regex, Tag(new CSharpTag() { IsCallbackInterface = true, IsDualCallbackInterface = isDual, NativeCallbackVisibility = visibilityForDefault, NativeCallbackName =  nativeCallbackName}));
        }

        /// <summary>
        /// Tag a structure for native marshalling
        /// </summary>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        /// <param name="transformStructToClass"></param>
        /// <param name="hasCustomMarshalling"></param>
        public static void TagStructToNative(this CppElement element, string regex, bool? transformStructToClass = false, bool? customNew = false, bool? hasCustomMarshalling = false, bool? forceMarshalToToBeGenerated = null)
        {
            element.Modify<CppStruct>(regex, Tag(new CSharpTag() { StructHasNativeValueType = true, StructToClass = transformStructToClass, StructCustomNew = customNew, StructCustomMarshall = hasCustomMarshalling, StructForceMarshalToToBeGenerated = forceMarshalToToBeGenerated }));
        }

        /// <summary>
        /// Tag an Enum and force it to be interpreted as a flag.
        /// </summary>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        public static string GetTypeNameWithMapping(this CppElement cppType)
        {
            var tag = cppType.GetTagOrDefault<CSharpTag>();
            if (tag != null && tag.MappingType != null)
                return tag.MappingType;
            if (cppType is CppEnum)
                return "int";
            if (cppType is CppType)
                return (cppType as CppType).Type;
            throw new ArgumentException(string.Format("Cannot get typename from type {0}", cppType));
        }

        private static string RegexRename(PathRegex regex, string fromName, string replaceName)
        {
            return replaceName.Contains("$")? regex.Replace(fromName, replaceName) : replaceName;            
        }

        /// <summary>
        ///   Fully rename a type and all references
        /// </summary>
        /// <param name = "fromType"></param>
        /// <param name = "toType"></param>
        /// <returns></returns>
        private static CppElement.ProcessModifier Tag(CSharpTag fromTag)
        {
            return (pathREgex, element) =>
                       {
                           CSharpTag tag = element.Tag as CSharpTag;
                           if (tag == null)
                           {
                               tag = new CSharpTag();
                               element.Tag = tag;
                           }
                           if (fromTag.Visibility.HasValue) tag.Visibility = fromTag.Visibility;
                           if (fromTag.NativeCallbackVisibility.HasValue) tag.NativeCallbackVisibility = fromTag.NativeCallbackVisibility;
                           if (fromTag.NativeCallbackName != null) tag.NativeCallbackName = fromTag.NativeCallbackName;
                           if (fromTag.NoProperty.HasValue) tag.NoProperty = fromTag.NoProperty;
                           if (fromTag.MappingName != null) 
                               tag.MappingName = RegexRename(pathREgex, element.FullName, fromTag.MappingName);
                           if (fromTag.IsFinalMappingName != null) tag.IsFinalMappingName = fromTag.IsFinalMappingName;
                           if (fromTag.StructHasNativeValueType != null) tag.StructHasNativeValueType = fromTag.StructHasNativeValueType;
                           if (fromTag.StructToClass != null) tag.StructToClass = fromTag.StructToClass;
                           if (fromTag.StructCustomMarshall != null) tag.StructCustomMarshall = fromTag.StructCustomMarshall;
                           if (fromTag.StructCustomNew != null) tag.StructCustomNew = fromTag.StructCustomNew;
                           if (fromTag.StructForceMarshalToToBeGenerated != null)
                               tag.StructForceMarshalToToBeGenerated = fromTag.StructForceMarshalToToBeGenerated;
                           if (fromTag.MappingType != null) tag.MappingType = RegexRename(pathREgex, element.FullName, fromTag.MappingType);
                           if (fromTag.IsEnumFlags != null) tag.IsEnumFlags = fromTag.IsEnumFlags;
                           if (fromTag.IsCallbackInterface != null) tag.IsCallbackInterface = fromTag.IsCallbackInterface;
                           if (fromTag.IsDualCallbackInterface != null) tag.IsDualCallbackInterface = fromTag.IsDualCallbackInterface;
                           if (fromTag.FunctionDllName != null) tag.FunctionDllName = RegexRename(pathREgex, element.FullName, fromTag.FunctionDllName);
                           if (fromTag.FunctionGroup != null) tag.FunctionGroup = fromTag.FunctionGroup;
                           if (fromTag.ParameterAttribute != null && element is CppParameter)
                               (element as CppParameter).Attribute = fromTag.ParameterAttribute.Value;
                           return false;
                       };
        }
    }
}