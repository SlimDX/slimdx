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
        public Visibility? Visibility;
        public bool? NoProperty;
        public string MappingName;
    }


    public static class CppElementExtensions
    {
        public static void ModifyTag<T>(this CppElement element, string regex, Visibility? visibility,
                                        bool? noProperty = null, string mappingName = null) where T : CppElement
        {
            element.Modify<T>(regex, Tag(visibility, noProperty, mappingName));
        }

        public static void ModifyTag<T>(this CppElement element, string regex, string mappingName = null)
            where T : CppElement
        {
            element.Modify<T>(regex, Tag(null, null, mappingName));
        }

        /// <summary>
        ///   Fully rename a type and all references
        /// </summary>
        /// <param name = "fromType"></param>
        /// <param name = "toType"></param>
        /// <returns></returns>
        private static Modifiers.ProcessModifier Tag(Visibility? visibility, bool? noProperty, string mappingName)
        {
            return (pathREgex, element) =>
                       {
                           CSharpTag tag = element.Tag as CSharpTag;
                           if (tag == null)
                           {
                               tag = new CSharpTag();
                               element.Tag = tag;
                           }
                           if (visibility.HasValue) tag.Visibility = visibility;
                           if (noProperty.HasValue) tag.NoProperty = noProperty;
                           if (mappingName != null) tag.MappingName = mappingName;
                           return false;
                       };
        }
    }
}