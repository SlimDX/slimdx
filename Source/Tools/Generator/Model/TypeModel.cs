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

namespace SlimDX.Generator
{
	class TypeModel
	{
		static TypeModel()
		{
			VoidModel = new TypeModel("void", typeof(void));
		}

		public TypeModel(string key, Type marshallingType)
		{
			if (string.IsNullOrEmpty(key))
				throw new ArgumentException("Value may not be null or empty", "key");
			if (marshallingType == null)
				throw new ArgumentNullException("marshallingType");

			Key = key;
			MarshallingType = marshallingType;
		}

		public string Key
		{
			get;
			private set;
		}

		public virtual string Name
		{
			get
			{
				return Key;
			}
		}

		public Type MarshallingType
		{
			get;
			private set;
		}

		public static TypeModel VoidModel
		{
			get;
			private set;
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
	}
}
