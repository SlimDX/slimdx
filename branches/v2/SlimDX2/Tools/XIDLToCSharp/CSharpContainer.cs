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
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpContainer
    {
        private List<CSharpContainer> _items;

        public CSharpContainer()
        {
            _items = new List<CSharpContainer>();
            Generator = CallContext.GetData("Generator") as CSharpGenerator;
            Visibility = Visibility.Public;
        }

        internal CSharpGenerator Generator { get; private set; }

        public CSharpContainer ParentContainer { get; set; }

        protected void ClearItems()
        {
            _items = new List<CSharpContainer>();
        }

        public T GetParent<T>() where T : CSharpContainer
        {
            CSharpContainer parent = ParentContainer;
            while (parent != null && !(parent is T))
                parent = parent.ParentContainer;
            return (T) parent;
        }

        public ReadOnlyCollection<CSharpContainer> Items
        {
            get { return _items.AsReadOnly(); }
        }

        public IEnumerable<CSharpConstant> Constants
        {
            get { return Items.OfType<CSharpConstant>(); }
        }

        public void Add(CSharpContainer innerContainer)
        {
            innerContainer.ParentContainer = this;
            _items.Add(innerContainer);
        }

        public void Remove(CSharpContainer innerContainer)
        {
            innerContainer.ParentContainer = null;
            _items.Remove(innerContainer);
        }

        public virtual string Name { get; set; }

        public Visibility Visibility { get; set; }


        public virtual string VisibilityName
        {
            get
            {
                StringBuilder builder = new StringBuilder();


                if ((Visibility & Visibility.Public) != 0)
                    builder.Append("public ");
                else if ((Visibility & Visibility.Protected) != 0)
                    builder.Append("protected ");
                else if ((Visibility & Visibility.Internal) != 0)
                    builder.Append("internal ");
                else if ((Visibility & Visibility.PublicProtected) != 0)
                    builder.Append("");

                if ((Visibility & Visibility.Override) != 0)
                    builder.Append(" override ");

                return builder.ToString();
            }
        }

        public virtual string Path
        {
            get
            {
                if (ParentContainer != null)
                    return ParentContainer.FullName;
                return "";
            }
        }

        public string FullName
        {
            get
            {
                string path = Path;
                string name = Name ?? "";
                return string.IsNullOrEmpty(path) ? name : path + "." + name;
            }
        }
    }
}