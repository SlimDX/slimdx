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
    public class MacroFunctionCall
    {
        public class MacroArgument : List<Token>
        {
            public string RawValue
            {
                get
                {
                    StringBuilder builder = new StringBuilder();
                    foreach (Token token in this)
                    {
                        builder.Append(token.Value);
                    }
                    return builder.ToString();
                }
            }
        }


        public MacroFunctionCall()
        {
            Arguments = new List<MacroArgument>();
        }

        public string Name { get; set; }

        public IList<MacroArgument> Arguments { get; set; }

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(Name);
            if (Arguments.Count > 0)
            {
                builder.Append("(");
                for (int i = 0; i < Arguments.Count; i++)
                {
                    IList<Token> tokenList = Arguments[i];
                    builder.Append("[");
                    for (int j = 0; j < tokenList.Count; j++)
                    {
                        builder.Append(tokenList[j]);
                        if ((j + 1) < tokenList.Count)
                            builder.Append(",");
                    }
                    builder.Append("]");

                    if ((i + 1) < Arguments.Count)
                        builder.Append(",");
                }
                builder.Append(")");
            }
            return builder.ToString();
        }
    }
}