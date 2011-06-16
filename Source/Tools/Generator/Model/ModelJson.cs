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
using System.Collections.Generic;
using System.IO;
using Newtonsoft.Json.Linq;

namespace SlimDX.Generator
{
	static class ModelJson
	{
		#region Interface

		public static ApiModel Parse(JObject root, IEnumerable<string> searchPaths)
		{
			var name = (string)root["name"];
			var api = new ApiModel(name, ParseDependencies(root, searchPaths));

			// Translations and enumerations only need a single processing phase.
			ParseTranslations(root, api);
			ParseEnumerations(root, api);

			// Structure and interface models must be declared first, and
			// then defined in a second pass to prevent definition order problems.
			DeclareStructures(root, api);
			DeclareInterfaces(root, api);
			DefineStructures(root, api);
			DefineInterfaces(root, api);

			// Functions may reference any of the above, but cannot be referenced themselves,
			// and so can be parsed in one pass at the end.
			ParseFunctions(root, api);

			return api;
		}

		#endregion
		#region Implementation

		/// <summary>
		/// Parses API dependencies within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the API JSON tree.</param>
		/// <param name="searchPaths">The set of directories to search when resolving relative file references.</param>
		/// <returns>A list of API models representing dependencies.</returns>
		static List<ApiModel> ParseDependencies(JObject root, IEnumerable<string> searchPaths)
		{
			var results = new List<ApiModel>();
			var processed = new HashSet<string>();
			JToken dependencies;
			if (root.TryGetValue("dependencies", out dependencies))
			{
				foreach (var dependency in dependencies)
				{
					var file = (string)dependency;
					if (processed.Contains(file))
						continue;

					foreach (var searchPath in searchPaths)
					{
						var path = Path.Combine(searchPath, file);
						if (File.Exists(path))
						{
							var json = JObject.Parse(File.ReadAllText(path));
							results.Add(ModelJson.Parse(json, searchPaths));
							break;
						}
					}
				}
			}

			return results;
		}

		/// <summary>
		/// Parses translation model definitions within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the API JSON tree.</param>
		/// <param name="api">The API model being constructed.</param>
		static void ParseTranslations(JObject root, ApiModel api)
		{
			var results = new List<TranslationModel>();
			JToken items;
			if (root.TryGetValue("translations", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var target = (string)item["target"];
					api.AddTranslation(key, null, target);
				}
			}
		}

		/// <summary>
		/// Parses enumeration model definitions within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the API JSON tree.</param>
		/// <param name="api">The API model being constructed.</param>
		static void ParseEnumerations(JObject root, ApiModel api)
		{
            JToken items;
			if (root.TryGetValue("enumerations", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var model = api.AddEnumeration(key);
					foreach (var value in ParseEnumerationValues(item as JObject))
						model.AddValue(value);
				}
			}
		}

		/// <summary>
		/// Parses function model definitions within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the API JSON tree.</param>
		/// <param name="api">The API model being constructed.</param>
		static void ParseFunctions(JObject root, ApiModel api)
		{
            JToken items;
			if (root.TryGetValue("functions", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var type = api.FindType((string)item["type"]);
					var model = api.AddFunction(key, type);
					foreach (var parameter in ParseFunctionParameters(item as JObject, api))
						model.AddParameter(parameter);
				}
			}
		}

		/// <summary>
		/// Parses enumeration value model definitions within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the JSON tree for the enumeration.</param>
		/// <param name="api">The API model being constructed.</param>
		/// <returns>A list of enumeration value models.</returns>
		static IEnumerable<EnumerationValueModel> ParseEnumerationValues(JObject root)
		{
			var results = new List<EnumerationValueModel>();

            JToken items;
			if (root.TryGetValue("values", out items))
			{
				foreach (var item in items)
					results.Add(new EnumerationValueModel((string)item["key"], item["value"].Value<string>()));
			}

			return results;
		}

		/// <summary>
		/// Parses structure member model definitions within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the JSON tree for the structure.</param>
		/// <param name="api">The API model being constructed.</param>
		/// <returns>A list of structure member models.</returns>
		static List<StructureMemberModel> ParseStructureMembers(JObject root, ApiModel api)
		{
			var results = new List<StructureMemberModel>();

            JToken items;
			if (root.TryGetValue("members", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var type = api.FindType((string)item["type"]);
					results.Add(new StructureMemberModel(key, type));
				}
			}

			return results;
		}

		/// <summary>
		/// Parses interface method model definitions within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the JSON tree for the interface.</param>
		/// <param name="api">The API model being constructed.</param>
		/// <returns>A list of interface method models.</returns>
		static List<MethodModel> ParseInterfaceMethods(JObject root, ApiModel api)
		{
			var results = new List<MethodModel>();

            JToken items;
			if (root.TryGetValue("methods", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var type = api.FindType((string)item["type"]);
					var index = int.Parse(item["index"].Value<string>());
					var model = new MethodModel(api, key, type, index);
                    foreach (var parameter in ParseFunctionParameters(item as JObject, api))
						model.AddParameter(parameter);

					results.Add(model);
				}
			}

			return results;
		}

		/// <summary>
		/// Parses method parameter model definitions within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the JSON tree for the method.</param>
		/// <param name="api">The API model being constructed.</param>
		/// <returns>A list of method parameter models.</returns>
		static IEnumerable<ParameterModel> ParseFunctionParameters(JObject root, ApiModel api)
		{
			var results = new List<ParameterModel>();

            JToken items;
			if (root.TryGetValue("parameters", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var type = api.FindType((string)item["type"]);
                    var flags = ParseInterfaceMethodParameterFlags(item as JObject);
                    JToken indirection;
                    (item as JObject).TryGetValue("indirection", out indirection);

                    JToken length;
                    (item as JObject).TryGetValue("size", out length);

					results.Add(new ParameterModel(
						key,
						type,
						indirection != null ? (int)indirection : 0,
						flags,
						length != null ? (string)length : null
					));
				}
			}

			return results;
		}

		/// <summary>
		/// Parses parameter model flags within a JSON tree.
		/// </summary>
		/// <param name="root">The root of the JSON tree for the parameter.</param>
		/// <returns>The parameter flags.</returns>
		static ParameterModelFlags ParseInterfaceMethodParameterFlags(JObject root)
		{
			var results = ParameterModelFlags.None;

            JToken flags;
			if (root.TryGetValue("flags", out flags))
			{
				foreach (var flag in flags)
				{
					switch ((string)flag)
					{
						case "binary_size":
							results |= ParameterModelFlags.HasBinarySize;
							break;
						case "element_count":
							results |= ParameterModelFlags.HasElementCount;
							break;
						case "out":
							results |= ParameterModelFlags.IsOutput;
							break;
					}
				}
			}

			return results;
		}

		/// <summary>
		/// Declares structures in an API model based on the contents of a JSON tree.
		/// </summary>
		/// <param name="root">The root of the API JSON tree.</param>
		/// <param name="api">The API model being constructed.</param>
		static void DeclareStructures(JObject root, ApiModel api)
		{
            JToken items;
			if (root.TryGetValue("structures", out items))
			{
				foreach (var item in items)
					api.AddStructure((string)item["key"]);
			}
		}

		/// <summary>
		/// Defines structures in an API model based on the contents of a JSON tree.
		/// </summary>
		/// <param name="root">The root of the JSON tree for the API.</param>
		/// <param name="api">The API model being constructed.</param>
		static void DefineStructures(JObject root, ApiModel api)
		{
            JToken items;
			if (root.TryGetValue("structures", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var model = (StructureModel)api.FindType(key);
					foreach (var value in ParseStructureMembers(item as JObject, api))
						model.AddMember(value);
				}
			}
		}

		/// <summary>
		/// Declares interfaces in an API model based on the contents of a JSON tree.
		/// </summary>
		/// <param name="root">The root of the API JSON tree.</param>
		/// <param name="api">The API model being constructed.</param>
		static void DeclareInterfaces(JObject root, ApiModel api)
		{
            JToken items;
			if (root.TryGetValue("interfaces", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var guid = new Guid((string)item["guid"]);

					api.AddInterface(key, guid);
				}
			}
		}

		/// <summary>
		/// Defines interfaces in an API model based on the contents of a JSON tree.
		/// </summary>
		/// <param name="root">The root of the JSON tree for the API.</param>
		/// <param name="api">The API model being constructed.</param>
		static void DefineInterfaces(JObject root, ApiModel api)
		{
            JToken items;
			if (root.TryGetValue("interfaces", out items))
			{
				foreach (var item in items)
				{
					var key = (string)item["key"];
					var model = (InterfaceModel)api.FindType(key);

					JToken parent = null;
					if ((item as JObject).TryGetValue("type", out parent))
						model.Parent = api.FindType((string)parent);

					foreach (var method in ParseInterfaceMethods(item as JObject, api))
						model.AddMethod(method);
				}
			}
		}

		#endregion
	}
}