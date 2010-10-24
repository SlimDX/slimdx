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
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Xml;

namespace SlimDX2.Tools.XIDL
{
    [DataContract]
    public class CppIncludeGroup : CppElement
    {
        public override string FullName
        {
            get { return ""; }
        }

        [DataMember(Order = 0, Name = "Includes")]
        private List<CppInclude> _Includes
        {
            get { return Includes.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppInclude> Includes
        {
            get { return InnerElements.OfType<CppInclude>(); }
        }

        public IEnumerable<CppGuid> Guids
        {
            get { return Includes.SelectMany(cppInclude => cppInclude.Guids); }
        }

        public static CppIncludeGroup Read(string file)
        {
            var input = new FileStream(file, FileMode.Open);
            var result = Read(input);
            input.Close();
            return result;
        }

        public static CppIncludeGroup Read(Stream input)
        {
            var ds = new DataContractSerializer(typeof (CppIncludeGroup));

            CppIncludeGroup group = null;
            using (XmlReader w = XmlReader.Create(input))
            {
                group = ds.ReadObject(w) as CppIncludeGroup;
            }
            return group;
        }

        public void Write(string file)
        {
            var output = new FileStream(file, FileMode.Create);
            Write(output);
            output.Close();
        }

        public void Write(Stream output)
        {
            var ds = new DataContractSerializer(typeof (CppIncludeGroup));

            var settings = new XmlWriterSettings() {Indent = true};
            using (XmlWriter w = XmlWriter.Create(output, settings))
            {
                ds.WriteObject(w, this);
            }
        }

        public void CreateEnumFromMacros(string macroRegexpStr, string enumName)
        {
            var cppEnum = new CppEnum { Name = enumName };

            CppInclude includeToAddTo = null;

            foreach (CppMacroDefinition macroDef in Find<CppMacroDefinition>(macroRegexpStr))
            {
                CppInclude cppInclude = macroDef.Parent as CppInclude;
                bool isEnumToAdd = true;
                foreach (CppEnumItem cppEnumItem in cppEnum.Items)
                {
                    if (cppEnumItem.Name == macroDef.Name)
                    {
                        isEnumToAdd = false;
                        break;
                    }
                }
                if (isEnumToAdd)
                {
                    if (includeToAddTo == null)
                        includeToAddTo = cppInclude;
                    cppEnum.Add(new CppEnumItem { Name = macroDef.Name, Value = macroDef.Value });
                }
            }

            includeToAddTo.Add(cppEnum);
        }
    }
}