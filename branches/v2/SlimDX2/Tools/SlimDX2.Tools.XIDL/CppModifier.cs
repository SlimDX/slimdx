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
namespace SlimDX2.Tools.XIDL
{
    public class Modifiers
    {
        public delegate bool ProcessModifier(PathRegex pathRegex, CppElement cppElement);

        /// <summary>
        ///   Returns a new Remove modifier.
        /// </summary>
        /// <param name = "typeName"></param>
        /// <param name = "specifier"></param>
        /// <returns></returns>
        public static ProcessModifier Remove
        {
            get { return (pathREgex, element) => true; }
        }

        /// <summary>
        ///   Fully rename a type and all references
        /// </summary>
        /// <param name = "fromType"></param>
        /// <param name = "toType"></param>
        /// <returns></returns>
        public static ProcessModifier RenameType(string fromType, string toType)
        {
            return (pathREgex, element) =>
                       {
                           var cppType = element as CppType;
                           if (cppType != null && cppType.Type == fromType)
                               cppType.Type = toType;
                           else if (element.Name == fromType)
                               element.Name = toType;
                           return false;
                       };
        }

        /// <summary>
        ///   Returns a new TypeModifier.
        /// </summary>
        /// <param name = "typeName"></param>
        /// <param name = "specifier"></param>
        /// <returns></returns>
        public static ProcessModifier Type(string typeName, string specifier = null, bool? hasArray = null,
                                           string arrayDimension = null)
        {
            return new TypeModifier(typeName, specifier, hasArray, arrayDimension).Process;
        }

        /// <summary>
        ///   Change the attribute of a Parameter's Method.
        /// </summary>
        private class TypeModifier
        {
            private readonly string _typeName;
            private readonly string _specifier;
            private readonly bool? _hasArray;
            private readonly string _arrayDimension;

            public TypeModifier(string typeName, string specifier = null, bool? hasArray = null,
                                string arrayDimension = null)
            {
                _typeName = typeName;
                _specifier = specifier;
                _hasArray = hasArray;
                _arrayDimension = arrayDimension;
            }

            public bool Process(PathRegex pathRegex, CppElement cppElement)
            {
                CppType cppType = cppElement as CppType;
                if (cppType != null)
                {
                    if (_typeName != null)
                        cppType.Type = _typeName.Contains("$")
                                           ? pathRegex.Regex.Replace(cppType.Type, _typeName)
                                           : _typeName;
                    ;
                    if (_specifier != null)
                        cppType.Specifier = _specifier;
                    if (_hasArray.HasValue)
                        cppType.IsArray = _hasArray.Value;
                    if (_arrayDimension != null)
                        cppType.ArrayDimension = _arrayDimension;
                }
                return false;
            }
        }

        /// <summary>
        ///   Returns a new MethodParameter Attribute Modifier.
        /// </summary>
        /// <param name = "newAttribute">attribute to apply</param>
        /// <returns></returns>
        public static ProcessModifier ParameterAttribute(CppAttribute newAttribute)
        {
            return new MethodAttributeModifier(newAttribute).Process;
        }

        /// <summary>
        ///   Change the attribute of a Parameter's Method.
        /// </summary>
        private class MethodAttributeModifier
        {
            private readonly CppAttribute _attribute;

            public MethodAttributeModifier(CppAttribute attribute)
            {
                _attribute = attribute;
            }

            public bool Process(PathRegex pathRegex, CppElement cppElement)
            {
                CppParameter cppParameter = cppElement as CppParameter;
                if (cppParameter != null)
                {
                    cppParameter.Attribute = _attribute;
                }
                return false;
            }
        }

        /// <summary>
        ///   Return a new Name Modifier.
        /// </summary>
        /// <param name = "newName">new name to apply, may be null if no change is required</param>
        /// <param name = "description">new descipriotn. May be null.</param>
        /// <param name = "remarks">new remarks. May be null.</param>
        /// <returns></returns>
        public static ProcessModifier Name(string newName = null, string description = null, string remarks = null)
        {
            return new NameModifier(newName, description, remarks).Process;
        }

        /// <summary>
        ///   Change the name of an element.
        /// </summary>
        private class NameModifier
        {
            private readonly string _name;
            private readonly string _description;
            private readonly string _remarks;

            public NameModifier(string newName = null, string description = null, string remarks = null)
            {
                _name = newName;
                _description = description;
                _remarks = remarks;
            }

            public bool Process(PathRegex pathRegex, CppElement cppElement)
            {
                if (_name != null)
                    cppElement.Name = _name.Contains("$") ? pathRegex.Regex.Replace(cppElement.Name, _name) : _name;

                if (_description != null)
                    cppElement.Description = _description;

                if (_remarks != null)
                    cppElement.Remarks = _remarks;

                return false;
            }
        }
    }
}