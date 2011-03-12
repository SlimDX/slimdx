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
using System.Reflection;
using System.Collections.Generic;

namespace SlimDX
{
	//TODO: This should be replaced by a Reflection.Emit based fast factory
	//      This method should be used by end-users to construct SlimDX objects from a native pointer
	//      obtained through something other than SlimDX and SHOULD NOT MODIFY THE REFERENCE COUNT OF THE NATIVE POINTER. (it can also be used internally)
	//      Should the count need to be adjusted, the calling code should AddReference().
	public static class ObjectFactory
	{
		#region Interface

		static public T Create<T>(IntPtr nativePointer) where T : ComObject
		{
			if (nativePointer == IntPtr.Zero)
				throw new ArgumentNullException("nativePointer");

			var constructor = typeof(T).GetConstructor(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public, null, new[] { typeof(IntPtr) }, null);
			if (constructor == null)
				return null;

			return (T)constructor.Invoke(new object[] { nativePointer });
		}

		static public ComObject Create(IntPtr nativePointer, Guid interfaceGuid)
		{
			if (nativePointer == IntPtr.Zero)
				throw new ArgumentNullException("nativePointer");

			//TODO: this is likely too slow in practice. should restrict this search to assemblies
			//      known to have slimdx types in them. or do some other optimization. do not forget to
			//      account for manual delay- load of the slimdx assemblies (i.e., we can't use a static
			//      ctor in this type since the d3d11 assembly may not be loaded the first time we call this function).
			Type targetType;
			if (!interfaceGuids.TryGetValue(interfaceGuid, out targetType))
			{
				foreach (var assembly in AppDomain.CurrentDomain.GetAssemblies())
				{
					foreach (var type in assembly.GetTypes())
					{
						if (type.IsSubclassOf(typeof(ComObject)))
						{
							foreach (var attribute in type.GetCustomAttributes(false))
							{
								var guid = attribute as GuidAttribute;
								if (guid != null)
								{
									targetType = type;
									interfaceGuids[new Guid(guid.Value)] = type;
								}
							}
						}
					}
				}
			}

			var constructor = targetType.GetConstructor(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public, null, new[] { typeof(IntPtr) }, null);
			if (constructor == null)
				return null;

			return (ComObject)constructor.Invoke(new object[] { nativePointer });
		}

		#endregion
		#region Implementation

		static Dictionary<Guid, Type> interfaceGuids = new Dictionary<Guid, Type>();

		#endregion
	}
}
