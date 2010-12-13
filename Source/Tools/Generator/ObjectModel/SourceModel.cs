// Copyright (c) 2007-2010 SlimDX Group
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
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Xml.Linq;

namespace SlimDX.Generator.ObjectModel
{
	/// <summary>
	/// Implements a model of a C++ header in memory.
	/// </summary>
	class SourceModel
	{
		public SourceModel(XElement root, NameRules nameService, IEnumerable<string> initialTypeMap)
		{
			foreach (var item in initialTypeMap)
			{
				int index = item.IndexOf(' ');
				if (index < 0)
					throw new InvalidDataException(string.Format("One of the initial type mappings is invalid: \"{0}\"", item));

				var nativeName = item.Substring(0, index);
				var managedName = item.Substring(index + 1);
				var managedType = Type.GetType(managedName);
				if (managedType == null)
					throw new InvalidDataException(string.Format("One of the initial type mappings is invalid: \"{0}\"", item));

				AddType(new TypeElement(nativeName, managedType));
			}

			Build(root, nameService);
		}

		/// <summary>
		/// Gets the interfaces in the model.
		/// </summary>
		public ReadOnlyCollection<InterfaceElement> Interfaces
		{
			get
			{
				return new ReadOnlyCollection<InterfaceElement>(interfaceElements);
			}
		}

		/// <summary>
		/// Gets the structures in the model.
		/// </summary>
		public ReadOnlyCollection<StructureElement> Structures
		{
			get
			{
				return new ReadOnlyCollection<StructureElement>(structureElements);
			}
		}

		/// <summary>
		/// Gets the enumerations in the model.
		/// </summary>
		public ReadOnlyCollection<EnumerationElement> Enumerations
		{
			get
			{
				return new ReadOnlyCollection<EnumerationElement>(enumerationElements);
			}
		}

		/// <summary>
		/// Adds a type element to the source model.
		/// </summary>
		/// <param name="element">The type element.</param>
		public void AddType(TypeElement element)
		{
			if (typesByName.ContainsKey(element.NativeName))
				throw new InvalidOperationException(string.Format("An element for the native type '{0}' already exists in the model.", element.NativeName));
			typesByName[element.NativeName] = element;

			if (element is InterfaceElement)
				interfaceElements.Add((InterfaceElement)element);
			else if (element is StructureElement)
				structureElements.Add((StructureElement)element);
			else if (element is EnumerationElement)
				enumerationElements.Add((EnumerationElement)element);
		}

		/// <summary>
		/// Looks up a type element by its native name.
		/// </summary>
		/// <param name="nativeName">The native name of the target type.</param>
		/// <returns>The type element, or null if no element exists with the specified native name.</returns>
		public TypeElement FindTypeByName(string nativeName)
		{
			if (string.IsNullOrEmpty(nativeName))
				throw new ArgumentException("Value may not be null or empty.", "nativeName");

			TypeElement result;
			if (typesByName.TryGetValue(nativeName, out result))
				return result;
			return null;
		}

		Dictionary<string, TypeElement> typesByName = new Dictionary<string, TypeElement>();
		List<EnumerationElement> enumerationElements = new List<EnumerationElement>();
		List<StructureElement> structureElements = new List<StructureElement>();
		List<InterfaceElement> interfaceElements = new List<InterfaceElement>();

		/// <summary>
		/// Builds the source model from the specified XML.
		/// </summary>
		/// <param name="root">The XML describing the source model.</param>
		/// <param name="nameService">The name service.</param>
		void Build(XElement root, NameRules nameService)
		{
			// The build occurs in two phases; the first phase populates the model with all 
			// the basic type declarations, and the second phase adds content to those types.
			// The cache is used for direct access to type XML during the second phase.
			Dictionary<string, XElement> cache = new Dictionary<string, XElement>();
			List<XElement> items = new List<XElement>(root.Descendants("Variable"));
			items.AddRange(root.Descendants("Typedef"));
			foreach (var itemData in items)
			{
				var typeData = itemData.Element("Type");
				if (typeData == null)
					continue;

				var baseData = typeData.Element("Base");
				if (baseData == null)
					continue;

				TypeElement typeElement = null;
				var typeName = baseData.Attribute("Name").Value;
				var declarationData = baseData.Element("DeclspecOrEmpty");
				var structureData = baseData.Element("Struct");
				var enumerationData = baseData.Element("Enum");

				if (declarationData != null)
				{
					var guidData = declarationData.Element("DeclspecDef").Element("Declspec");
					var guidValue = guidData.Attribute("Value").Value.Trim('"');
					var inheritanceData = baseData.Element("Inheritance");
					var parentTypeName = inheritanceData.Attribute("Name").Value;
					var parentType = FindTypeByName(parentTypeName);

					typeElement = new InterfaceElement(typeName, nameService.Apply(typeName, NameCasingStyle.Pascal), parentType, new Guid(guidValue));
				}
				else if (structureData != null)
				{
					typeElement = new StructureElement(typeName, nameService.Apply(typeName, NameCasingStyle.Pascal));
				}
				else if (enumerationData != null)
				{
					typeElement = new EnumerationElement(typeName, nameService.Apply(typeName, NameCasingStyle.Pascal));
				}
				else
				{
					continue;
				}

				AddType(typeElement);
				cache[typeElement.NativeName] = baseData;
			}

			foreach (var interfaceElement in interfaceElements)
				BuildInterface(interfaceElement, cache[interfaceElement.NativeName]);
			foreach (var structureElement in structureElements)
				BuildStructure(structureElement, cache[structureElement.NativeName]);
		}

		/// <summary>
		/// Builds an interface definition from its declaration and XML data.
		/// </summary>
		/// <param name="element">The declaration element to transform to a definition.</param>
		/// <param name="data">The XML data for the interface.</param>
		void BuildInterface(InterfaceElement element, XElement data)
		{
			foreach (var functionData in data.Descendants("Function"))
			{
				var returnTypeName = ExtractTypeName(functionData.Element("Type"));
				var returnType = FindTypeByName(returnTypeName);

				List<VariableElement> parameterElements = new List<VariableElement>();
				var signatureData = functionData.Element("Signature");
				foreach (var parameterData in signatureData.Descendants("Param"))
					parameterElements.Add(ExtractParameter(parameterData));

				element.AddFunction(new FunctionElement(functionData.Attribute("Name").Value, returnType, parameterElements.ToArray()));
			}
		}

		void BuildStructure(StructureElement element, XElement data)
		{
		}

		/// <summary>
		/// Extracts a variable element from parameter XML.
		/// </summary>
		/// <param name="typeData">The XML element.</param>
		/// <returns>The type name.</returns>
		VariableElement ExtractParameter(XElement parameterData)
		{
			var parameterTypeData = parameterData.Element("Type");
			var parameterTypeName = ExtractTypeName(parameterTypeData);
			var parameterType = FindTypeByName(parameterTypeName);
			var indirectionLevel = parameterTypeData.Descendants("Pointers").Count();

			return new VariableElement(parameterData.Element("Var").Attribute("Name").Value, parameterType, indirectionLevel);
		}

		/// <summary>
		/// Extracts a type name from type XML.
		/// </summary>
		/// <param name="typeData">The XML element.</param>
		/// <returns>The type name.</returns>
		string ExtractTypeName(XElement typeData)
		{
			var attribute = typeData.Attribute("Name");
			if (attribute != null)
				return attribute.Value;

			// Only complex types use the attribute to hold the name; simple scalar
			// types like "void" and "float" store it in nested elements.
			var scalarData = typeData.Element("Scalar");
			var tokenData = scalarData.Element("Token");
			return tokenData.Value;
		}
	}
}
