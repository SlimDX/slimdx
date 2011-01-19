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

namespace SlimDX.Generator
{
	static class ModelXml
	{
		public static ApiModel Parse(XElement root)
		{
			var result = new ApiModel(ReadName(root));

			// First establish the existence of all types.
			var typeMap = new Dictionary<string, TypeModel>();
			var typeXml = new Dictionary<TypeModel, XElement>();

			foreach (var modelElement in root.XPathSelectElements("external|interface"))
			{
				var modelName = ReadName(modelElement);
				var modelKind = ReadKind(modelElement);
				var model = new TypeModel(modelName, modelKind);
				typeMap.Add(modelName.Native, model);
				typeXml.Add(model, modelElement);
			}

			// Then complete the definition of all types.
			foreach (var item in typeXml)
			{
				var typeModel = item.Key;
				var typeElement = item.Value;
				foreach (var methodElement in typeElement.Elements("method"))
				{
					var methodName = ReadName(methodElement);
					var returnType = ReadNativeType(methodElement);
					var methodModel = new MethodModel(methodName, typeMap[returnType]);
					foreach (var parameterElement in methodElement.Elements("parameter"))
					{
						var parameterName = ReadName(parameterElement);
						var parameterType = ReadNativeType(parameterElement);
						methodModel.AddParameter(new VariableModel(parameterName, typeMap[parameterType]));
					}

					typeModel.AddMethod(methodModel);
				}
			}

			foreach (var type in typeMap.Select(x => x.Value).Where(x => x.Kind == TypeModelKind.Interface))
				result.AddInterface(type);
			foreach (var type in typeMap.Select(x => x.Value).Where(x => x.Kind == TypeModelKind.Structure))
				result.AddStructure(type);
			foreach (var type in typeMap.Select(x => x.Value).Where(x => x.Kind == TypeModelKind.Enumeration))
				result.AddEnumeration(type);
			return result;
		}

		static TypeModelKind ReadKind(XElement element)
		{
			switch (element.Name.LocalName)
			{
				case "interface":
					return TypeModelKind.Interface;
				default:
					return TypeModelKind.External;
			}
		}

		static ModelName ReadName(XElement element)
		{
			var nativeName = ReadAttribute("nativeName", element);
			var managedName = ReadAttribute("managedName", element);

			return new ModelName(nativeName, managedName);
		}

		static string ReadNativeType(XElement element)
		{
			return ReadAttribute("nativeType", element);
		}

		static string ReadAttribute(string name, XElement element)
		{
			var attribute = element.Attribute(name);
			if (attribute == null)
				return null;
			return attribute.Value;
		}
	}
}