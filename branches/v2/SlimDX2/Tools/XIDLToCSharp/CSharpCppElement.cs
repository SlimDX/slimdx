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
using System.Text;
using System.Text.RegularExpressions;
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpCppElement : CSharpContainer
    {
        private CppElement _cppElement;

        protected CSharpCppElement()
        {
        }

        public CppElement CppElement
        {
            get { return _cppElement; }
            set
            {
                _cppElement = value;
                if (_cppElement != null && _cppElement.Tag != null)
                {
                    UpdateFromTag(_cppElement.GetTag<CSharpTag>());
                }
            }
        }

        protected virtual void UpdateFromTag(CSharpTag tag)
        {
            if (tag.Visibility.HasValue)
                Visibility = tag.Visibility.Value;
        }


        public string CppElementName
        {
            get
            {
                if (CppElement != null && CppElement.Name != null)
                    return CppElement.Name;
                return "None";
            }
        }

        public int SizeOf { get; set; }

        private static readonly Regex RegexLink = new Regex(@"\{\{(.*?)}}");
        private static readonly Regex RegexCode = new Regex(@"\[\[(.*?)]]", RegexOptions.Singleline);

        private string RegexReplaceCReference(Match match)
        {
            string matchName = match.Groups[1].Value;

            if (matchName.EndsWith(" Interface"))
            {
                matchName = matchName.Substring(0, matchName.Length - " Interface".Length);
            }

            CSharpType type = Generator.FindCppType(matchName);
            if (type == null)
                return match.Value;
            return string.Format("<see cref=\"{0}\"/>", type.FullName);
        }

        public virtual List<string> DocItems
        {
            get
            {
                string description = CppElement.Description ?? "No documentation.";
                string remarks = CppElement.Remarks ?? "";

                description = RegexLink.Replace(description, RegexReplaceCReference);
                    // evaluator => "<see cref=\"$1\"/>");
                description = RegexCode.Replace(description, "\r\n<code>$1</code>\r\n");

                List<string> docItems = new List<string>();
                string line = null;

                StringReader stringReader = new StringReader(description);
                docItems.Add("<summary>");
                while ((line = stringReader.ReadLine()) != null)
                    docItems.Add(line);
                docItems.Add("</summary>");

                if (!string.IsNullOrEmpty(remarks))
                {
                    remarks = RegexLink.Replace(remarks, RegexReplaceCReference);
                    remarks = RegexCode.Replace(remarks, "\r\n<code>$1</code>\r\n");

                    stringReader = new StringReader(remarks);
                    docItems.Add("<remarks>");
                    while ((line = stringReader.ReadLine()) != null)
                        docItems.Add(line);
                    docItems.Add("</remarks>");
                }

                return docItems;
            }
        }

        public virtual string SingleDoc
        {
            get
            {
                string description = CppElement.Description ?? "No documentation.";

                // For return type, suppress Return Type in description
                if (description.StartsWith("{{"))
                {
                    int index = description.IndexOf("}}");
                    if (index > 0)
                    {
                        description = description.Substring(index + 2);
                    }
                }

                description = RegexLink.Replace(description, RegexReplaceCReference);
                    // evaluator => "<see cref=\"$1\"/>");
                description = RegexCode.Replace(description, "\r\n<code>$1</code>\r\n");

                StringBuilder docItems = new StringBuilder();
                string line = null;

                StringReader stringReader = new StringReader(description);
                while ((line = stringReader.ReadLine()) != null)
                    docItems.Append(line);

                return docItems.ToString();
            }
        }
    }
}