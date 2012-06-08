// Copyright (c) 2007-2011 SlimDX Group
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
using System.IO;
using GoldParser;

namespace SlimDX.Generator
{
	/// <summary>
	/// Implements a parser for C++ header files.
	/// </summary>
	class HeaderParser
	{
		Grammar grammar;

		/// <summary>
		/// Initializes a new instance of the <see cref="HeaderParser"/> class.
		/// </summary>
		/// <param name="grammarPath">The path to the compiled GOLD grammar file.</param>
		public HeaderParser(string grammarPath)
		{
			using (var grammarReader = new BinaryReader(File.OpenRead(grammarPath)))
				grammar = new Grammar(grammarReader);
		}

		/// <summary>
		/// Runs a custom "C++ Header" grammar on a preprocessed and transformed file to produce
		/// a tree of source elements in memory.
		/// </summary>
		/// <param name="file">The preprocessed source file.</param>
		public NonTerminal Parse(string file)
		{
			using (var stream = new StreamReader(file))
			{
				var parser = new Parser(stream, grammar);
				parser.TrimReductions = true;

				while (true)
				{
					var result = parser.Parse();
					switch (result)
					{
						case ParseMessage.InternalError:
							throw new InvalidOperationException("Internal error in parser");

						case ParseMessage.LexicalError:
							throw new InvalidOperationException(string.Format("Lexical error: (line:{0}) {1}", parser.TokenLineNumber, parser.TokenText));

						case ParseMessage.SyntaxError:
							throw new InvalidOperationException(string.Format("Syntax error: (line:{0}) {1}\n -- Expected: {2}", parser.LineNumber, parser.LineText,
								string.Join<Symbol>(", ", parser.GetExpectedTokens())));

						case ParseMessage.TokenRead:
							var terminal = new Terminal(parser.TokenSymbol, parser.TokenText);
							parser.TokenSyntaxNode = terminal;
							break;

						case ParseMessage.Reduction:
							var nonTerminal = new NonTerminal(parser.ReductionRule);
							parser.TokenSyntaxNode = nonTerminal;
							for (int i = 0; i < parser.ReductionCount; i++)
								nonTerminal.Add(parser.GetReductionSyntaxNode(i));
							break;

						case ParseMessage.Accept:
							return parser.TokenSyntaxNode as NonTerminal;
					}
				}
			}
		}
	}
}
