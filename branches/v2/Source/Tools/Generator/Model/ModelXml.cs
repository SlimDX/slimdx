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
using System.Linq;

namespace SlimDX.Generator
{
	static class ModelXml
	{
		public static JsonObject Transform(XElement root)
		{
			var api = new JsonObject();
			api["interfaces"] = new JsonObject(JsonType.Array);
			api["structures"] = new JsonObject(JsonType.Array);
			api["enumerations"] = new JsonObject(JsonType.Array);

			// find enums
			foreach (var element in root.XPathSelectElements("//enum-specifier"))
			{
				var item = new JsonObject();
				item["key"] = element.Element("identifier").Value;
				item["values"] = new JsonObject(JsonType.Array);

				foreach (var child in element.Descendants("enumerator-definition"))
				{
					var definition = new JsonObject();
					definition["key"] = child.Element("identifier").Value;
					definition["value"] = child.Element("numeric-literal").Value;

					item["values"].Add(definition);
				}

				api["enumerations"].Add(item);
			}

			// find structs and interfaces
			foreach (var element in root.XPathSelectElements("//class-specifier"))
			{
				var nameElement = element.XPathSelectElement("class-head/identifier");
				var guidElement = element.XPathSelectElement("class-head/declspec-list/declspec-definition/declspec/string-literal");

				var item = new JsonObject();
				item["key"] = nameElement.Value;

				// elements with a GUID are assumed to be COM interfaces
				if (guidElement != null)
				{
					item["guid"] = guidElement.Value.Trim('"');
					api["interfaces"].Add(item);
					item["methods"] = new JsonObject(JsonType.Array);

					int index = 0;
					foreach (var child in element.Descendants("function-definition"))
					{
						var returnType = child.Element("identifier") ?? child.Element("simple-type-specifier");
						nameElement = child.XPathSelectElement("init-declarator/direct-declarator/identifier");

						var method = new JsonObject();
						method["key"] = nameElement.Value;
						method["type"] = returnType.Value;
						method["index"] = index++;
						method["parameters"] = new JsonObject(JsonType.Array);

						foreach (var parameterElement in child.Descendants("parameter-declaration"))
						{
						}

						item["methods"].Add(method);
					}
				}
				else
				{
					api["structures"].Add(item);
					item["members"] = new JsonObject(JsonType.Array);

					foreach (var child in element.Descendants("member-declaration"))
					{
						nameElement = child.Element("identifier");
						var typeElement = child.Element("simple-type-specifier");
						if (typeElement == null)
						{
							typeElement = child.Element("identifier");
							nameElement = typeElement.ElementsAfterSelf("identifier").FirstOrDefault();
						}

						// TODO: handle pointers, arrays, and reference types here
						if (nameElement == null)
							nameElement = child.XPathSelectElement("direct-declarator//identifier") ?? child.XPathSelectElement("declarator//identifier");

						var member = new JsonObject();
						member["key"] = nameElement.Value;
						member["type"] = typeElement.Value;

						item["members"].Add(member);
					}
				}
			}

			return api;
		}
	}
}