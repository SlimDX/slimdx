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
using System.Collections.ObjectModel;

namespace SlimDX.Generator
{
	class ApiModel
	{
		#region Interface

		/// <summary>
		/// Initializes a new instance of the <see cref="ApiModel"/> class.
		/// </summary>
		/// <param name="name">The name of the API.</param>
		public ApiModel(string name)
			: this(name, null)
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="ApiModel"/> class.
		/// </summary>
		/// <param name="name">The name of the API.</param>
		/// <param name="dependencies">The dependencies of the API. May be null, indicating no dependencies.</param>
		public ApiModel(string name, IEnumerable<ApiModel> dependencies)
		{
			if (string.IsNullOrEmpty(name))
				throw new ArgumentException("Value may not be null or empty.", "name");

			Name = name;
			if (dependencies != null)
				this.dependencies.AddRange(dependencies);

			AddTranslation(VoidModel);
		}

		/// <summary>
		/// Gets the name of the API.
		/// </summary>
		public string Name
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the model that represents the 'void' incomplete type.
		/// </summary>
		public static TranslationModel VoidModel {
			get;
			private set;
		}

		/// <summary>
		/// Gets the collection of APIs that the API depends on.
		/// </summary>
		public ReadOnlyCollection<ApiModel> Dependencies
		{
			get
			{
				return dependencies.AsReadOnly();
			}
		}

		public ReadOnlyCollection<TranslationModel> Translations
		{
			get
			{
				return translations.AsReadOnly();
			}
		}

		public ReadOnlyCollection<EnumerationModel> Enumerations
		{
			get
			{
				return enumerations.AsReadOnly();
			}
		}

		public ReadOnlyCollection<StructureModel> Structures
		{
			get
			{
				return structures.AsReadOnly();
			}
		}

		public ReadOnlyCollection<InterfaceModel> Interfaces
		{
			get
			{
				return interfaces.AsReadOnly();
			}
		}

		public void AddTranslation(TranslationModel model)
		{
			if (model == null)
				throw new ArgumentNullException("model");
			translations.Add(model);
			index.Add(model.Key, model);
		}

		public void AddEnumeration(EnumerationModel model)
		{
			if (model == null)
				throw new ArgumentNullException("model");
			enumerations.Add(model);
			index.Add(model.Key, model);
		}

		public void AddStructure(StructureModel model)
		{
			if (model == null)
				throw new ArgumentNullException("model");
			structures.Add(model);
			index.Add(model.Key, model);
		}

		public void AddInterface(InterfaceModel model)
		{
			if (model == null)
				throw new ArgumentNullException("model");
			interfaces.Add(model);
			index.Add(model.Key, model);
		}

		/// <summary>
		/// Finds a type in the API or any dependencies.
		/// </summary>
		/// <param name="key">The key of the desired type.</param>
		/// <returns>The type, or null if no type was found with the specified key.</returns>
		public TypeModel FindType(string key)
		{
			if (key == null)
				throw new ArgumentException("Value may not be null or empty.", "key");

			TypeModel result;
			if (!index.TryGetValue(key, out result))
			{
				foreach (var dependency in dependencies)
				{
					result = dependency.FindType(key);
					if (result != null)
						break;
				}
			}

			return result;
		}

		/// <summary>
		/// Returns a <see cref="System.String"/> that represents this instance.
		/// </summary>
		/// <returns>
		/// A <see cref="System.String"/> that represents this instance.
		/// </returns>
		public override string ToString()
		{
			return Name;
		}

		#endregion
		#region Implementation

		/// <summary>
		/// Initializes the <see cref="ApiModel"/> class.
		/// </summary>
		static ApiModel() {
			VoidModel = new TranslationModel("void", "void", "System.Void");
		}

		List<ApiModel> dependencies = new List<ApiModel>();
		List<TranslationModel> translations = new List<TranslationModel>();
		List<EnumerationModel> enumerations = new List<EnumerationModel>();
		List<StructureModel> structures = new List<StructureModel>();
		List<InterfaceModel> interfaces = new List<InterfaceModel>();

		Dictionary<string, TypeModel> index = new Dictionary<string, TypeModel>();

		#endregion
	}
}