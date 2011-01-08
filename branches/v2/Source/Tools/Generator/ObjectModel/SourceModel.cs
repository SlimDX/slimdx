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
		#region Interface

		public SourceModel(XElement model, NameRules nameService, MetadataService metadataService, IEnumerable<string> initialTypeMap)
		{
			if (model == null)
				throw new ArgumentNullException("root");
			if (nameService == null)
				throw new ArgumentNullException("nameService");
			if (metadataService == null)
				throw new ArgumentNullException("metadataService");

			this.nameService = nameService;
			this.metadataService = metadataService;

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

				AddType(new TypeElement(nativeName, managedType, metadataService.FindTypeMetadata(nativeName)));
			}

			Build(model);
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

		#endregion Interface
		#region Implementation

		Dictionary<string, TypeElement> typesByName = new Dictionary<string, TypeElement>();
		List<EnumerationElement> enumerationElements = new List<EnumerationElement>();
		List<StructureElement> structureElements = new List<StructureElement>();
		List<InterfaceElement> interfaceElements = new List<InterfaceElement>();
		NameRules nameService;
		MetadataService metadataService;

		/// <summary>
		/// Builds the source model from the specified XML.
		/// </summary>
		/// <param name="root">The XML describing the source model.</param>
		void Build(XElement root)
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
				var interfaceData = baseData.Element("DeclspecOrEmpty");
				if (interfaceData != null)
					typeElement = CreateInterface(typeName, baseData, interfaceData);
				else if (baseData.Element("Struct") != null)
					typeElement = CreateStructure(typeName);
				else if (baseData.Element("Enum") != null)
					typeElement = CreateEnumeration(typeName);
				else
					continue;

				AddType(typeElement);
				cache[typeElement.NativeName] = baseData;
			}

			foreach (var interfaceElement in interfaceElements)
				BuildInterface(interfaceElement, cache[interfaceElement.NativeName]);
			foreach (var structureElement in structureElements)
				BuildStructure(structureElement, cache[structureElement.NativeName]);
			foreach (var enumerationElement in enumerationElements)
				BuildEnumeration(enumerationElement, cache[enumerationElement.NativeName]);
		}

		/// <summary>
		/// Creates an interface element as a declaration.
		/// </summary>
		/// <param name="name">The element name.</param>
		/// <param name="baseData">The base element data.</param>
		/// <param name="interfaceData">The interface declaration data.</param>
		/// <returns>The declared interface element.</returns>
		TypeElement CreateInterface(string name, XElement baseData, XElement interfaceData)
		{
			var guidData = interfaceData.Element("DeclspecDef").Element("Declspec");
			var guidValue = guidData.Attribute("Value").Value.Trim('"');
			var inheritanceData = baseData.Element("Inheritance");
			var parentTypeName = inheritanceData.Attribute("Name").Value;
			var parentType = FindTypeByName(parentTypeName);
			var metadata = metadataService.FindTypeMetadata(name);

			var result = new InterfaceElement(name, nameService.Apply(name, NameCasingStyle.Preserve), metadata, parentType, new Guid(guidValue));
			if (parentTypeName == "IUnknown")
			{
				// As a special case, IUnknown is directly implemented. IUnknown's managed analog (the C# interface SlimDX.ComObject)
				// lives in the core SlimDX assembly, which cannot contain generated code or reference the trampoline assembly.
				// Installing the appropriate function elements here also allows for simplified virtual table index management.
				foreach (var functionElement in BuildIUnknownFunctions())
					result.AddFunction(functionElement);
			}

			return result;
		}

		/// <summary>
		/// Creates a structure element as a declaration.
		/// </summary>
		/// <param name="name">The element name.</param>
		/// <returns>The declared structure element.</returns>
		TypeElement CreateStructure(string name)
		{
			var metadata = metadataService.FindTypeMetadata(name);
			return new StructureElement(name, nameService.Apply(name, NameCasingStyle.Pascal), metadata);
		}

		/// <summary>
		/// Creates an enumeration element as a declaration.
		/// </summary>
		/// <param name="name">The element name.</param>
		/// <returns>The declared enumeration element.</returns>
		TypeElement CreateEnumeration(string name)
		{
			var metadata = metadataService.FindTypeMetadata(name);
			return new EnumerationElement(name, nameService.Apply(name, NameCasingStyle.Pascal), metadata);
		}

		/// <summary>
		/// Builds an interface definition from its declaration and XML data.
		/// </summary>
		/// <param name="element">The declaration element to transform to a definition.</param>
		/// <param name="data">The XML data for the interface.</param>
		void BuildInterface(InterfaceElement element, XElement data)
		{
			// Counting base functions in this fashion assumes that base types will be fully
			// defined before child types, which should be true (because the source language
			// is C) and that base types are processed by BuildInterface() in definition order.
			// Note also that elements directly deriving from IUnknown will already have some
			// functions defined.
			var index = element.Functions.Count;
			var baseType = element.BaseType as InterfaceElement;
			while (baseType != null)
			{
				index += baseType.Functions.Count;
				baseType = baseType.BaseType as InterfaceElement;
			}

			foreach (var functionData in data.Descendants("Function"))
			{
				var returnTypeName = ExtractTypeName(functionData.Element("Type"));
				var returnType = FindTypeByName(returnTypeName);

				List<VariableElement> parameterElements = new List<VariableElement>();
				var signatureData = functionData.Element("Signature");
				foreach (var parameterData in signatureData.Descendants("Param"))
					parameterElements.Add(ExtractVariable(parameterData));

				var name = functionData.Attribute("Name").Value;
				var qualifiedName = string.Format("{0}.{1}", element.NativeName, name);
				var metadata = metadataService.FindFunctionMetadata(qualifiedName);
				element.AddFunction(new FunctionElement(name, metadata, index++, returnType, parameterElements.ToArray()));
			}
		}

		/// <summary>
		/// Builds a structure definition from its declaration and XML data.
		/// </summary>
		/// <param name="element">The declaration element to transform to a definition.</param>
		/// <param name="data">The XML data for the structure.</param>
		void BuildStructure(StructureElement element, XElement data)
		{
			foreach (var fieldData in data.Descendants("Variable"))
				element.AddField(ExtractVariable(fieldData));
		}

		/// <summary>
		/// Builds an enumeration definition from its declaration and XML data.
		/// </summary>
		/// <param name="element">The declaration element to transform to a definition.</param>
		/// <param name="data">The XML data for the enumeration.</param>
		void BuildEnumeration(EnumerationElement element, XElement data)
		{
			foreach (var itemData in data.Descendants("EnumVal"))
			{
				var nativeName = itemData.Attribute("Name").Value;
				var managedName = nameService.Apply(nativeName, NameCasingStyle.Pascal).RemovePrefix(element.ManagedName);
				var value = itemData.Attribute("Value").Value;

				// The 0xFFFFFFFF values are used to force the native enumeration to be a particular bit width;
				// they should not appear in the managed layer.
				if (value != "0xffffffff")
					element.AddItem(new EnumerationItemElement(nativeName, managedName, value, metadataService.FindTypeMetadata(element.NativeName)));
			}
		}

		/// <summary>
		/// Builds function elements for the methods of IUnknown.
		/// </summary>
		/// <returns>An array containing function elements for IUnknown's methods.</returns>
		FunctionElement[] BuildIUnknownFunctions()
		{
			var results = new FunctionElement[3];
			var resultType = FindTypeByName("HRESULT");
			var guidType = FindTypeByName("REFIID");
			var unknownType = FindTypeByName("IUnknown");
			var longType = FindTypeByName("ULONG");
			var guidParameter = new VariableElement("riid", new Metadata(), resultType, 0);
			var unknownParameter = new VariableElement("ppvObject", new Metadata(), unknownType, UsageQualifiers.Out);

			results[0] = new FunctionElement("QueryInterface", metadataService.FindFunctionMetadata("IUnknown.QueryInterface"), 0, resultType, guidParameter, unknownParameter);
			results[1] = new FunctionElement("AddRef", metadataService.FindFunctionMetadata("IUnknown.AddRef"), 1, longType);
			results[2] = new FunctionElement("Release", metadataService.FindFunctionMetadata("IUnknown.Release"), 2, longType);

			return results;
		}

		/// <summary>
		/// Extracts a variable element from parameter XML.
		/// </summary>
		/// <param name="typeData">The XML element.</param>
		/// <returns>The type name.</returns>
		VariableElement ExtractVariable(XElement parameterData)
		{
			try
			{
				var parameterTypeData = parameterData.Element("Type");
				var parameterInfoData = parameterData.Element("Var");
				var parameterArrayData = parameterInfoData.Element("Array");
				var parameterTypeName = ExtractTypeName(parameterTypeData);
				var parameterType = FindTypeByName(parameterTypeName);
				var usageData = parameterData.Element("ParamQualifier");
				var usage = ExtractUsage(usageData);
				var name = parameterInfoData.Attribute("Name").Value;
				var dimension = 0;

				if (parameterArrayData != null)
					dimension = int.Parse(parameterArrayData.Attribute("Value").Value);

				if (parameterType.ManagedName == "void")
					parameterType = FindTypeByName("void*");

				return new VariableElement(name, nameService.Apply(name, NameCasingStyle.Camel), new Metadata(), parameterType, usage, dimension);
			}
			catch
			{
				Console.Write(parameterData.ToString());
				throw;
			}
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

		/// <summary>
		/// Extracts the usage information from usage XML.
		/// </summary>
		/// <param name="usageData">The XML element.</param>
		/// <returns>The usage information.</returns>
		UsageQualifiers ExtractUsage(XElement usageData)
		{
			if (usageData == null)
				return UsageQualifiers.None;

			var name = usageData.Element("Token").Value;
			var usage = UsageQualifiers.None;
			if (name.Contains("in"))
				usage |= UsageQualifiers.In;
			if (name.Contains("out"))
				usage |= UsageQualifiers.Out;
			if (name.Contains("opt"))
				usage |= UsageQualifiers.IsOptional;
			if (name.Contains("bcount"))
				usage |= UsageQualifiers.HasBinarySizeRelation;
			if (name.Contains("ecount"))
				usage |= UsageQualifiers.HasElementCountRelation;
			if (name.Contains("part"))
				usage |= UsageQualifiers.IsPartial;

			return usage;
		}

		#endregion
	}
}
