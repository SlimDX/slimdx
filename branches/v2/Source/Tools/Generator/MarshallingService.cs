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
using System.Runtime.InteropServices;

namespace SlimDX.Generator
{
	class MarshallingService
	{
		#region Interface

		public Type ResolveType(TypeModel model)
		{
			if (model == null)
				return null;
			if (model is EnumerationModel)
				return typeof(int);

			var translation = model as TranslationModel;
			if (translation != null)
			{
				var type = Type.GetType(translation.TargetType);
				if (type.IsValueType && Marshal.SizeOf(type) <= sizeof(long))
					return type;
			}

			return typeof(IntPtr);
		}

		public Type ResolveType(ParameterModel model)
		{
			if (model == null)
				return null;

			var behavior = new MarshallingService().ResolveBehavior(model);
			if (behavior == MarshalBehavior.Array || behavior == MarshalBehavior.Indirect)
				return typeof(IntPtr);
			return ResolveType(model.Type);
		}

		public MarshalBehavior ResolveBehavior(TypeModel model)
		{
			var translation = model as TranslationModel;
			if (translation != null)
			{
				var type = Type.GetType(translation.TargetType);
				if (type == typeof(string))
					return MarshalBehavior.String;
			}

			if (model is EnumerationModel)
				return MarshalBehavior.Enumeration;
			if (model is StructureModel)
				return MarshalBehavior.Structure;
			if (model is InterfaceModel || model.Key == "IUnknown")
				return MarshalBehavior.Interface;
			return MarshalBehavior.Direct;
		}

		public MarshalBehavior ResolveBehavior(ParameterModel model)
		{
			if (model.IndirectionLevel > 0)
				return MarshalBehavior.Indirect;
			if (model.LengthParameter != null)
				return MarshalBehavior.Array;
			return ResolveBehavior(model.Type);
		}

		public MarshalBehavior ResolveBehavior(StructureMemberModel model)
		{
			return ResolveBehavior(model.Type);
		}

		#endregion
	}
}
