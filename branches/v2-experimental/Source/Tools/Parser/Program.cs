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

using System.Xml.Linq;
using Clang;
using SlimDX.Api;
using System;
using System.IO;
using System.Collections.Generic;

namespace Parser
{
	class Options
	{
		public HashSet<string> RelevantFiles;

		public Options()
		{
			RelevantFiles = new HashSet<string>();
		}
	}

	class Program
	{
		static void Main(string[] arguments)
		{
			var options = new Options();
			var apiName = arguments[0];
			var sourceFile = arguments[1];
			var outputFile = arguments[2];

			options.RelevantFiles.Add(sourceFile);

			using (var context = new Context())
			using (var translationUnit = new TranslationUnit(context, sourceFile, TranslationUnitFlags.DetailedPreprocessingRecord | TranslationUnitFlags.NestedMacroExpansions))
			{
				var api = new ApiModel(apiName);

				new Cursor(translationUnit).VisitChildren((c, p) => Visitor(c, p, api, options));

				ModelWriter.ToFile(api, outputFile);
			}
		}

		static CursorVisitResult Visitor(Cursor cursor, Cursor parent, ApiModel api, Options options)
		{
			switch (cursor.Kind)
			{
				case CursorKind.EnumDeclaration:
					VisitEnumeration(cursor, parent, api, options);
					break;

				// Skip all of the following AST elements.
				case CursorKind.TypedefDeclaration:
					return CursorVisitResult.Continue;
			}

			return CursorVisitResult.Recurse;
		}

		static CursorVisitResult VisitEnumeration(Cursor cursor, Cursor parent, ApiModel api, Options options)
		{
			var origin = cursor.Location.SpellingPosition.File.Path;
			if (options.RelevantFiles.Contains(origin))
			{
				var model = api.AddEnumeration(cursor.Name);

				cursor.VisitChildren((c, p) => VisitEnumerationValueName(c, p, model));
			}

			return CursorVisitResult.Continue;
		}

		static CursorVisitResult VisitEnumerationValueName(Cursor cursor, Cursor parent, EnumerationModel enumeration)
		{
			if (cursor.Kind == CursorKind.EnumerationConstantDeclaration)
			{
				var value = enumeration.AddValue(cursor.Name, string.Empty);
				cursor.VisitChildren((c, p) => VisitEnumerationValueConstant(c, p, value));
			}

			return CursorVisitResult.Continue;
		}

		static CursorVisitResult VisitEnumerationValueConstant(Cursor cursor, Cursor parent, EnumerationValueModel value)
		{
			value.Value = ExtractText(cursor.Extent);
			return CursorVisitResult.Continue;
		}

		static string ExtractText(SourceRange range)
		{
			var path = range.Start.ExpansionPosition.File.Path;
			var text = string.Empty;
			if (!fileCache.TryGetValue(path, out text))
			{
				text = System.IO.File.ReadAllText(path);
				fileCache[path] = text;
			}

			var start = range.Start.ExpansionPosition.Offset;
			var length = range.End.ExpansionPosition.Offset - start;
			return text.Substring(start, length);
		}

		static Dictionary<string, string> fileCache = new Dictionary<string, string>();
	}
}
