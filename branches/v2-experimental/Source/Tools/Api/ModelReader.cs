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

namespace SlimDX.Api
{
	public class ModelReader
	{
		public static ApiModel FromFile(string file, IEnumerable<ApiModel> dependencies)
		{
			var xml = XDocument.Load(file);
			var api = new ApiModel(xml.Root.Attribute("name").Value, dependencies);

			foreach (var element in xml.Root.Elements("enumeration"))
				DeserializeEnumeration(element, api);

			foreach (var element in xml.Root.Elements("interface"))
			{
				// Currently structures only have members and classes only have functions.
				if (element.Elements("member").Any())
					DeserializeStructure(element, api);
				else
					DeserializeInterface(element, api);
			}

			foreach (var element in xml.Root.Elements("function"))
				DeserializeFunction(element, api);

			return api;
		}

		static void DeserializeEnumeration(XElement element, ApiModel model)
		{
			var result = model.AddEnumeration(element.Attribute("name").Value);
			foreach (var member in element.Elements("member"))
				result.AddValue(new EnumerationValueModel(member.Attribute("name").Value, member.Attribute("value").Value));
		}

		static void DeserializeStructure(XElement element, ApiModel model)
		{
			var result = model.AddStructure(element.Attribute("name").Value);
			foreach (var member in element.Elements("member"))
				result.AddMember(new StructureMemberModel(member.Attribute("name").Value, model.FindType(member.Attribute("type-name").Value)));
		}

		static void DeserializeInterface(XElement element, ApiModel model)
		{
			var result = model.AddInterface(element.Attribute("name").Value, new Guid(element.Attribute("guid").Value));
			result.Parent = model.FindType(element.Attribute("type-name").Value);
			foreach (var member in element.Elements("function"))
			{
				var method = new MethodModel(model, member.Attribute("name").Value, model.FindType(member.Attribute("type-name").Value), int.Parse(member.Attribute("index").Value));
				foreach (var param in member.Elements("parameter"))
				{
					var flags = ParseFlags(param.Attribute("flags"));
					var argument = new ParameterModel(param.Attribute("name").Value, model.FindType(param.Attribute("type-name").Value), 0, flags, null);

					method.AddParameter(argument);
				}

				result.AddMethod(method);
			}
		}

		static void DeserializeFunction(XElement element, ApiModel model)
		{
			var result = model.AddFunction(element.Attribute("name").Value, model.FindType(element.Attribute("type-name").Value));
			foreach (var param in element.Elements("parameter"))
			{
				var flags = ParseFlags(param.Attribute("flags"));
				var argument = new ParameterModel(param.Attribute("name").Value, model.FindType(param.Attribute("type-name").Value), 0, flags, null);

				result.AddParameter(argument);
			}
		}

		static ParameterModelFlags ParseFlags(XAttribute flags)
		{
			if (flags != null && flags.Value == "out")
				return ParameterModelFlags.IsOutput;
			return ParameterModelFlags.None;
		}
	}
}
