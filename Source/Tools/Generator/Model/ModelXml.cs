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
	/// <summary>
	/// Responsible for transforming XML output from the parser into a Json hierarchy.
	/// </summary>
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

					var value = child.Element("numeric-literal") ?? child.Element("primary-expression");
					definition["value"] = string.Join(" ", value.Nodes().Where(x => x is XText));

					item["values"].Add(definition);
				}

				api["enumerations"].Add(item);
			}

			// find structs and interfaces
			foreach (var element in root.XPathSelectElements("//class-specifier"))
			{
				var nameElement = element.XPathSelectElement("class-head/identifier");
				var guidElement = element.XPathSelectElement("class-head/declspec-list/declspec-definition/declspec/string-literal");
				var parentElement = element.XPathSelectElement("class-head/base-clause/base-specifier/identifier");

				var item = new JsonObject();
				item["key"] = nameElement.Value;
				if (parentElement != null)
					item["type"] = parentElement.Value;

				// elements with a GUID are assumed to be COM interfaces
				if (guidElement != null)
				{
					api["interfaces"].Add(item);
					item["guid"] = guidElement.Value.Trim('"');
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
							var parameter = TransformParameter(parameterElement);
							if (parameter != null)
								method["parameters"].Add(parameter);
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
							typeElement = child.Element("identifier") ?? child.XPathSelectElement("type-specifier/simple-type-specifier");
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

			var indices = new Dictionary<string, int>();
			indices.Add("IUnknown", 3);

			foreach (var item in api["interfaces"])
				CalculateIndices(item, api["interfaces"], indices);

			return api;
		}

		static void CalculateIndices(JsonObject item, IEnumerable<JsonObject> interfaces, Dictionary<string, int> indices)
		{
			var key = (string)item["key"];
			if (indices.ContainsKey((string)item["key"]))
				return;

			var parent = (string)item["type"];
			if (!indices.ContainsKey(parent))
				CalculateIndices(interfaces.First(i => (string)i["key"] == parent), interfaces, indices);

			int offset = indices[parent];
			int count = 0;

			foreach (var method in item["methods"])
			{
				int index = (int)method["index"];
				method["index"] = index + offset;
				count++;
			}

			indices.Add(key, count + offset);
		}

		static JsonObject TransformParameter(XElement element)
		{
			var nameElement = element.XPathSelectElement("declarator//identifier") ??
				element.XPathSelectElement("identifier[2]");

			var typeElement = element.XPathSelectElement("type-specifier/identifier") ??
				element.XPathSelectElement("type-specifier/simple-type-specifier") ??
				element.XPathSelectElement("simple-type-specifier") ??
				element.Element("identifier");

			if (nameElement == null && typeElement.Value == "void")
				return null;

			var item = new JsonObject();
			item["key"] = nameElement.Value;
			item["type"] = typeElement.Value;
			item["indirection"] = element.Descendants("ptr-operator").Count();

			var flags = TransformFlags(element.Element("qualifier"));
			if (flags.Any())
			{
				item["flags"] = new JsonObject(flags);

				var size = element.XPathSelectElement("qualifier/identifier");
				if (size != null)
					item["size"] = size.Value;
			}

			return item;
		}

		static IEnumerable<JsonObject> TransformFlags(XElement element)
		{
			if (element == null)
				yield break;

			string value = (string)element.Element("Token") ?? element.Value;
			if (value.Contains("in"))
				yield return "in";
			if (value.Contains("out"))
				yield return "out";
			if (value.Contains("opt"))
				yield return "optional";
			if (value.Contains("part"))
				yield return "partial";
			if (value.Contains("bcount"))
				yield return "binary_size";
			if (value.Contains("ecount"))
				yield return "element_count";
		}
	}
}