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
using System.Json;
using System.Xml.Linq;
using System.Xml.XPath;

namespace SlimDX.Generator
{
	static class ModelXml
	{
		public static JsonObject Transform(XElement root)
		{
			var api = new JsonObject(JsonType.Object);
			var interfaces = new JsonObject(JsonType.Array);
			var structures = new JsonObject(JsonType.Array);
			var enums = new JsonObject(JsonType.Array);

			// find enums
			foreach (var element in root.XPathSelectElements("//enum-specifier"))
			{
				var item = new JsonObject(JsonType.Object);
				item["key"] = new JsonObject(element.Element("identifier").Value);

				var definitions = new JsonObject(JsonType.Array);
				foreach (var definition in element.XPathSelectElements("//enumerator-definition"))
				{
					var definitionItem = new JsonObject(JsonType.Object);
					definitionItem["key"] = new JsonObject(definition.Element("identifier").Value);
					definitionItem["value"] = new JsonObject(definition.Element("numeric-literal").Value);

					definitions.Add(definitionItem);
				}

				item.Add("values", definitions);
				enums.Add(item);
			}

			// find structs and interfaces
			foreach (var element in root.XPathSelectElements("//class-specifier"))
			{
				var nameElement = element.XPathSelectElement("class-head/identifier");
				var guidElement = element.XPathSelectElement("class-head/declspec-list/declspec-definition/declspec/string-literal");

				var item = new JsonObject(JsonType.Object);
				item["key"] = new JsonObject(nameElement.Value);
				if (guidElement != null)
					item["guid"] = new JsonObject(guidElement.Value.Trim('"'));

				// elements with a GUID are assumed to be COM interfaces
				if (guidElement != null)
					interfaces.Add(item);
				else
					structures.Add(item);
			}

			api.Add("interfaces", interfaces);
			api.Add("structures", structures);
			api.Add("enumerations", enums);
			return api;
		}
	}
}