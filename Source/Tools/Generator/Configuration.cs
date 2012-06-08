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

using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Xml.Linq;

namespace SlimDX.Generator
{
	class Configuration
	{
		public Configuration(string file)
		{
			var path = Path.GetDirectoryName(file);
			var xml = XDocument.Load(file);

			var parser = xml.Root.Element("parser-configuration");
			if (parser != null)
			{
				PrimaryHeader = parser.Attribute("primary-header").Value;
				AdditionalHeaders = DeserializeValueArray(parser.Element("additional-headers"));
				IncludePaths = DeserializeValueArray(parser.Element("include-paths"));
				DefineSymbols = DeserializeValueArray(parser.Element("define-symbols"));
				IgnoreSymbols = DeserializeValueArray(parser.Element("ignore-symbols"));
			}
			var generator = xml.Root.Element("generator-configuration");
			ApiName = generator.Attribute("api").Value;
			GeneratorOutputPath = Path.Combine(path, generator.Attribute("output-path").Value);
			Layers = DeserializePathArray(generator.Element("combine"), path);
			DependencyModelPaths = DeserializePathArray(generator.Element("dependencies"), path);
		}

		public string ApiName
		{
			get;
			private set;
		}

		public string GeneratorOutputPath
		{
			get;
			private set;
		}

		public string PrimaryHeader
		{
			get;
			private set;
		}

		public ReadOnlyCollection<string> AdditionalHeaders
		{
			get;
			private set;
		}

		public ReadOnlyCollection<string> IncludePaths
		{
			get;
			private set;
		}

		public ReadOnlyCollection<string> DefineSymbols
		{
			get;
			private set;
		}

		public ReadOnlyCollection<string> IgnoreSymbols
		{
			get;
			private set;
		}

		public ReadOnlyCollection<string> Layers
		{
			get;
			private set;
		}

		public ReadOnlyCollection<string> DependencyModelPaths
		{
			get;
			private set;
		}

		static ReadOnlyCollection<string> DeserializeValueArray(XElement root)
		{
			var result = new List<string>();
			foreach (var element in root.Elements())
				result.Add(element.Value);
			return result.AsReadOnly();
		}

		static ReadOnlyCollection<string> DeserializePathArray(XElement root, string path)
		{
			var result = new List<string>();
			foreach (var element in root.Elements())
				result.Add(Path.Combine(path, element.Value));
			return result.AsReadOnly();
		}
	}
}
