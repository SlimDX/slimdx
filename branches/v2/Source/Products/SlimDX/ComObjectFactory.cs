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

namespace SlimDX
{
	//TODO: This should be replaced by a Reflection.Emit based fast factory
	//      This method should be used to constructo SlimDX objects from a native pointer
	//      obtained through something other than SlimDX and SHOULD NOT MODIFY THE REFERENCE COUNT OF THE NATIVE POINTER.
	//      Should the count need to be adjusted, the calling code should AddReference().
	public static class ObjectFactory
	{
		static public T Create<T>(IntPtr nativePointer) where T : ComObject
		{
			if (nativePointer == IntPtr.Zero)
				throw new ArgumentNullException("nativePointer");

			var constructor = typeof(T).GetConstructor(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public, null, new[] { typeof(IntPtr) }, null);
			if (constructor == null)
				return null;

			return (T)constructor.Invoke(new object[] { nativePointer });
		}
	}
}
