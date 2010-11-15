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
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;

namespace SlimDX.XIDL
{
    [DataContract]
    public class CppInclude : CppElement
    {
        public override string FullName
        {
            get { return ""; }
        }

        [DataMember(Order = 0, Name = "Depends")]
        private List<CppDependency> _Depends
        {
            get { return Depends.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppDependency> Depends
        {
            get { return InnerElements.OfType<CppDependency>(); }
        }

        [DataMember(Order = 1, Name = "Macros")]
        private List<CppMacroDefinition> _Macros
        {
            get { return Macros.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppMacroDefinition> Macros
        {
            get { return InnerElements.OfType<CppMacroDefinition>(); }
        }

        [DataMember(Order = 2, Name = "Interfaces")]
        private List<CppInterface> _Interfaces
        {
            get { return Interfaces.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppInterface> Interfaces
        {
            get { return InnerElements.OfType<CppInterface>(); }
        }

        [DataMember(Order = 3, Name = "Functions")]
        private List<CppFunction> _Functions
        {
            get { return Functions.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppFunction> Functions
        {
            get { return InnerElements.OfType<CppFunction>(); }
        }

        [DataMember(Order = 4, Name = "Structs")]
        private List<CppStruct> _Structs
        {
            get { return Structs.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppStruct> Structs
        {
            get { return InnerElements.OfType<CppStruct>(); }
        }

        [DataMember(Order = 5, Name = "Enums")]
        private List<CppEnum> _Enums
        {
            get { return Enums.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppEnum> Enums
        {
            get { return InnerElements.OfType<CppEnum>(); }
        }

        [DataMember(Order = 6, Name = "Typedefs")]
        private List<CppTypedef> _Typedefs
        {
            get { return Typedefs.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppTypedef> Typedefs
        {
            get { return InnerElements.OfType<CppTypedef>(); }
        }

        [DataMember(Order = 7, Name = "Guids")]
        private List<CppGuid> _Guids
        {
            get { return Guids.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppGuid> Guids
        {
            get { return InnerElements.OfType<CppGuid>(); }
        }

        public bool Empty
        {
            get { return InnerElements.Count == 0; }
        }
    }
}