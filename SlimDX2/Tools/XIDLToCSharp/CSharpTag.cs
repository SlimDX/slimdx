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
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpTag
    {
        public CSharpTag(Visibility? visibility=null, bool? noProperty=null, string mappingName=null, bool? isEnumFlags=null)
        {
            Visibility = visibility;
            NoProperty = noProperty;
            MappingName = mappingName;
            IsEnumFlags = isEnumFlags;
        }

        /// <summary>
        /// General visibility for Methods
        /// </summary>
        public Visibility? Visibility;

        /// <summary>
        /// Used for methods, to force a method to not be translated to a property
        /// </summary>
        public bool? NoProperty;

        /// <summary>
        /// Mapping name
        /// </summary>
        public string MappingName;

        /// <summary>
        /// Mapping type name
        /// </summary>
        public string MappingType;

        /// <summary>
        /// Used for enums, to tag enums that are used as flags
        /// </summary>
        public bool? IsEnumFlags;

        /// <summary>
        /// DLL name attached to a function
        /// </summary>
        public string FunctionDllName;

        /// <summary>
        /// CSharpFunctionGroup attached to a function
        /// </summary>
        public CSharpFunctionGroup FunctionGroup;
    }

    public static class CppElementExtensions
    {
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
                                        bool? noProperty = null, string mappingName = null) where T : CppElement
        {
            element.Modify<T>(regex, Tag(new CSharpTag(visibility, noProperty, mappingName)));
        }

        /// <summary>
        /// Tag an element with a new mapping name.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        /// <param name="mappingName"></param>
        public static void TagName<T>(this CppElement element, string regex, string mappingName)
            where T : CppElement
        {
            element.Modify<T>(regex, Tag(new CSharpTag(null, null, mappingName)));
        }

        /// <summary>
        /// Tag an element with a new Cpp type name (for fields, parameters, return types...) and a new name
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        /// <param name="typeName"></param>
        public static void TagTypeName<T>(this CppElement element, string regex, string typeName, string mappingName = null)
            where T : CppElement
        {
            element.Modify<T>(regex, Tag(new CSharpTag() { MappingType =  typeName, MappingName = mappingName} ));
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
        /// Tag an Enum and force it to be interpreted as a flag.
        /// </summary>
        /// <param name="element"></param>
        /// <param name="regex"></param>
        public static string GetTypeNameWithMapping(this CppType cppType)
        {
            var tag = cppType.GetTag<CSharpTag>();
            if (tag != null && tag.MappingType != null)
                return tag.MappingType;
            return cppType.Type;
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
        private static Modifiers.ProcessModifier Tag(CSharpTag fromTag)
        {
            return (pathREgex, element) =>
                       {
                           CSharpTag tag = element.GetTag<CSharpTag>();
                           if (tag == null)
                           {
                               tag = new CSharpTag();
                               element.Tag = tag;
                           }
                           if (fromTag.Visibility.HasValue) tag.Visibility = fromTag.Visibility;
                           if (fromTag.NoProperty.HasValue) tag.NoProperty = fromTag.NoProperty;
                           if (fromTag.MappingName != null) tag.MappingName = RegexRename(pathREgex, element.FullName, fromTag.MappingName);
                           if (fromTag.MappingType != null) tag.MappingType = RegexRename(pathREgex, element.FullName, fromTag.MappingType);
                           if (fromTag.IsEnumFlags != null) tag.IsEnumFlags = fromTag.IsEnumFlags;
                           if (fromTag.FunctionDllName != null) tag.FunctionDllName = RegexRename(pathREgex, element.FullName, fromTag.FunctionDllName);
                           if (fromTag.FunctionGroup != null) tag.FunctionGroup = fromTag.FunctionGroup;
                           return false;
                       };
        }
    }
}