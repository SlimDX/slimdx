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
using System.Linq;
using System.Xml.Linq;
using System.Xml.XPath;

namespace SlimDX.Generator
{
	static class ModelXml
	{
		public static ApiModel Parse(XElement root, params TypeModel[] dependencies)//TODO: Should be taking ApiModel's as dependencies?
		{
			var result = new ApiModel();
			var typeMap = new Dictionary<string, TypeModel>();
			var typeXml = new Dictionary<TypeModel, XElement>();

			typeMap.Add("void", TypeModel.VoidModel);
			foreach (var dependency in dependencies)
				typeMap.Add(dependency.Name, dependency);

			// First establish the existence of all types.
			foreach (var element in root.XPathSelectElements("//class-specifier"))
			{
				var name = element.XPathSelectElement("class-head/identifier");
				var model = new TypeModel(name.Value);
				typeMap.Add(model.Name, model);
				typeXml.Add(model, element);
			}

			// Once models have been declared, they can be filled out.
			foreach (var item in typeXml)
			{
				var model = item.Key;
				var definition = item.Value;
				foreach (var element in definition.XPathSelectElements(".//function-definition"))
					model.AddMethod(ParseMethodDeclaration(element, typeMap));
			}

			return result;
		}

		static MethodModel ParseMethodDeclaration(XElement root, Dictionary<string, TypeModel> types)
		{
			var type = root.XPathSelectElement("simple-type-specifier") ?? root.XPathSelectElement("identifier");
			var name = root.XPathSelectElement("init-declarator/direct-declarator/identifier");
			var model = new MethodModel(name.Value, types[type.Value]);

			foreach (var element in root.XPathSelectElements(".//parameter-declaration"))
				model.AddParameter(ParseParameterDeclaration(element, types));

			return model;
		}

		static VariableModel ParseParameterDeclaration(XElement root, Dictionary<string, TypeModel> types)
		{
			return null;
		}
	}
}