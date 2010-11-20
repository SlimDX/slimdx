using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using GoldParser;

namespace Generator
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
		public void Parse(string file)
		{
			using (var stream = new StreamReader(file))
			{
				var parser = new Parser(stream, grammar);
			}
		}
	}
}
