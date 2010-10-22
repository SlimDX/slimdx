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
using System.Text;

namespace Boost.Wave
{
    public class MacroDefinition
    {
        public MacroDefinition()
        {
            ParameterNames = new List<Token>();
            Body = new List<Token>();
        }

        public string Name { get; set; }

        public IList<Token> ParameterNames { get; set; }

        public IList<Token> Body { get; set; }

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(Name);
            if (ParameterNames.Count > 0)
            {
                builder.Append("(");
                for (int i = 0; i < ParameterNames.Count; i++)
                {
                    Token token = ParameterNames[i];
                    builder.Append(token);
                    if ((i + 1) < ParameterNames.Count)
                        builder.Append(",");
                }
                builder.Append(")");
            }
            builder.Append(" ");
            for (int i = 0; i < Body.Count; i++)
            {
                Token token = Body[i];
                builder.Append(token);
                if ((i + 1) < Body.Count)
                    builder.Append(",");
            }
            return builder.ToString();
        }
    }
}