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
using System.Linq;
using System.Xml.Linq;
using System.Xml.XPath;
using Newtonsoft.Json.Linq;

namespace SlimDX.Api
{
    /// <summary>
    /// Responsible for transforming XML output from the parser into a Json hierarchy.
    /// </summary>
	public static class ModelXml
    {
        public static JObject Transform(XElement root)
        {
            var api = new JObject();
            api["interfaces"] = new JArray();
            api["structures"] = new JArray();
            api["enumerations"] = new JArray();

            // Type definitions are mapped to the original types, effectively ensuring all
            // type references are to unaliased type names.
            Dictionary<string, string> typeDefinitions = new Dictionary<string, string>();
            foreach (var element in root.XPathSelectElements("//storage-class"))
            {
                var parent = element.Parent;
                var identifiers = parent.Elements("identifier");
                if (identifiers.Count() == 2)
                {
                    var type = identifiers.First();
                    var alias = identifiers.Skip(1).First();
                    typeDefinitions[alias.Value] = type.Value;
                }
            }

            // find enums
            foreach (var element in root.XPathSelectElements("//enum-specifier"))
            {
                var item = new JObject();
                var initialKey = element.Element("identifier").Value;
                var finalKey = string.Empty;
                if (!typeDefinitions.TryGetValue(initialKey, out finalKey))
                    finalKey = initialKey;

                item["key"] = finalKey;
                item["values"] = new JArray();

                foreach (var child in element.Descendants("enumerator-definition"))
                {
                    var definition = new JObject();
                    definition["key"] = child.Element("identifier").Value;

                    var value = child.Element("numeric-literal") ?? child.Element("primary-expression") ?? child.Element("identifier");
                    definition["value"] = string.Join(" ", value.DescendantNodes().Where(x => x is XText));

                    (item["values"] as JArray).Add(definition);
                }

                JArray array = api["enumerations"] as JArray;
                array.Add(item);
            }

            // find structs and interfaces
            foreach (var element in root.XPathSelectElements("//class-specifier"))
            {
                // Skip unions, they're not first-class types.
                var key = element.Element("class-key");
                if (key != null && key.Value == "union")
                    continue;

                var nameElement = element.XPathSelectElement("class-head/identifier");
                var guidElement = element.XPathSelectElement("class-head/declspec-list/declspec-definition/declspec/string-literal");
                var parentElement = element.XPathSelectElement("class-head/base-clause/base-specifier/identifier");

                var item = new JObject();
                item["key"] = nameElement.Value;
                if (parentElement != null)
                    item["type"] = parentElement.Value;

                // elements with a GUID are assumed to be COM interfaces
                if (guidElement != null)
                {
                    var interfacesArray = api["interfaces"] as JArray;
                    interfacesArray.Add(item);
                    item["guid"] = guidElement.Value.Trim('"');
                    item["methods"] = new JArray();

                    int index = 0;
                    foreach (var child in element.Descendants("function-definition"))
                    {
                        var returnType = child.Element("identifier") ?? child.Element("simple-type-specifier");
                        nameElement = child.XPathSelectElement("init-declarator/direct-declarator/identifier");

                        var method = new JObject();
                        method["key"] = nameElement.Value;
                        method["type"] = returnType.Value;
                        method["index"] = index++;
                        method["parameters"] = new JArray();

                        foreach (var parameterElement in child.Descendants("parameter-declaration"))
                        {
                            var parameter = TransformParameter(parameterElement);
                            if (parameter != null)
                                (method["parameters"] as JArray).Add(parameter);
                        }

                        (item["methods"] as JArray).Add(method);
                    }
                }
                else
                {
                    var structuresArray = api["structures"] as JArray;
                    structuresArray.Add(item);
                    item["members"] = new JArray();

                    foreach (var child in element.Descendants("member-declaration"))
                    {
                        //TODO: Should not skip member functions probably, but they aren't required until we
                        //      need to support interface implementation shims.
                        if (child.Element("function-definition") != null)
                            continue;

                        XElement classKey = child.XPathSelectElement("class-specifier/class-key");
                        XElement typeElement;

                        if (classKey != null && classKey.Value == "union")
                        {
                            //TODO: Currently processing only the first field; really we need to mark them all
                            //      with field offsets somehow so we can use [FieldOffset] in the managed code.
                            var identifiers = child.XPathSelectElements("class-specifier/member-specification/member-declaration/identifier");
                            typeElement = identifiers.First();
                            nameElement = identifiers.Skip(1).First();
                        }
                        else
                        {
                            nameElement = child.Element("identifier");
                            typeElement = child.Element("simple-type-specifier");
                            if (typeElement == null)
                            {
                                typeElement = child.Element("identifier") ?? child.XPathSelectElement("type-specifier/simple-type-specifier");
                                nameElement = typeElement.ElementsAfterSelf("identifier").FirstOrDefault();
                            }
                        }

                        // TODO: handle pointers, arrays, and reference types here
                        if (nameElement == null)
                            nameElement = child.XPathSelectElement("direct-declarator//identifier") ?? child.XPathSelectElement("declarator//identifier");

                        var member = new JObject();

                        var initialType = typeElement.Value;
                        var finalType = string.Empty;
                        if (!typeDefinitions.TryGetValue(initialType, out finalType))
                            finalType = initialType;

                        member["key"] = nameElement.Value;
                        member["type"] = finalType;

                        (item["members"] as JArray).Add(member);
                    }
                }
            }

            var indices = new Dictionary<string, int>();
            indices.Add("IUnknown", 3);

            foreach (JObject item in api["interfaces"])
                CalculateIndices(item, api["interfaces"] as JArray, indices);

            return api;
        }

        static void CalculateIndices(JObject item, JArray interfaces, Dictionary<string, int> indices)
        {
            var key = (string)item["key"];
            if (indices.ContainsKey((string)item["key"]))
                return;

            var parent = (string)item["type"];
            if (!indices.ContainsKey(parent))
                CalculateIndices(interfaces.First(i => (string)i["key"] == parent) as JObject, interfaces, indices);

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

        static JObject TransformParameter(XElement element)
        {
            var nameElement = element.XPathSelectElement("declarator//identifier") ??
                element.XPathSelectElement("identifier[2]") ??
                element.XPathSelectElement("direct-declarator/identifier");

            var typeElement = element.XPathSelectElement("type-specifier/identifier") ??
                element.XPathSelectElement("type-specifier/simple-type-specifier") ??
                element.XPathSelectElement("simple-type-specifier") ??
                element.Element("identifier");

            if (nameElement == null && typeElement.Value == "void")
                return null;

            var item = new JObject();
            item["key"] = nameElement.Value;
            item["type"] = typeElement.Value;
            item["indirection"] = element.Descendants("ptr-operator").Count();

            var flags = TransformFlags(element.Element("qualifier"));
            if (flags.Any())
            {
                item["flags"] = new JArray(flags);

                var size = element.XPathSelectElement("qualifier/identifier");
                if (size != null)
                    item["size"] = size.Value;
            }

            return item;
        }

        static IEnumerable<JValue> TransformFlags(XElement element)
        {
            if (element == null)
                yield break;

            string value = (string)element.Element("Token") ?? element.Value;
            if (value.Contains("in"))
                yield return new JValue("in");
            if (value.Contains("out"))
                yield return new JValue("out");
            if (value.Contains("opt"))
                yield return new JValue("optional");
            if (value.Contains("part"))
                yield return new JValue("partial");
            if (value.Contains("bcount"))
                yield return new JValue("binary_size");
            if (value.Contains("ecount"))
                yield return new JValue("element_count");
        }
    }
}