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
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpInterface : CSharpType
    {
        public CSharpInterface(CppInterface cppInterface)
        {
            CppElement = cppInterface;
            if (cppInterface != null)
                Guid = cppInterface.Guid;
            DefaultImplem = this;
        }

        public IEnumerable<CSharpMethod> Methods
        {
            get { return Items.OfType<CSharpMethod>(); }
        }

        public IEnumerable<CSharpProperty> Properties
        {
            get { return Items.OfType<CSharpProperty>(); }
        }

        protected override void UpdateFromTag(CSharpTag tag)
        {
            base.UpdateFromTag(tag);
            IsCallback = tag.IsCallbackInterface.HasValue?tag.IsCallbackInterface.Value:false;
            IsDualCallback = tag.IsDualCallbackInterface.HasValue ? tag.IsDualCallbackInterface.Value : false;
        }

        /// <summary>
        /// Class Parent inheritance
        /// </summary>
        public CSharpType Parent { get; set; }

        /// <summary>
        /// Interface Parent inheritance
        /// </summary>
        public CSharpType IParent { get; set; }

        public CSharpInterface DefaultImplem { get; set; }

        public string Guid { get; set; }

        /// <summary>
        ///   Only valid for inner interface. Specify the name of the property in the outer interface to access to the inner interface
        /// </summary>
        public string PropertyAccesName { get; set; }

        /// <summary>
        ///   True if this interface is used as a callback to a C# object
        /// </summary>
        public bool IsCallback { get; set; }

        /// <summary>
        ///   True if this interface is used as a dual-callback to a C# object
        /// </summary>
        public bool IsDualCallback { get; set; }

        /// <summary>
        ///   List of declared inner structs
        /// </summary>
        public bool HasInnerInterfaces
        {
            get { return Items.OfType<CSharpInterface>().Count() > 0; }
        }

        /// <summary>
        ///   List of declared inner structs
        /// </summary>
        public IEnumerable<CSharpInterface> InnerInterfaces
        {
            get { return Items.OfType<CSharpInterface>(); }
        }
    }
}