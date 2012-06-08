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
	/// <summary>
	/// Stores information about a trampoline function that can be used to invoke
	/// any native COM method that matches the trampoline signature.
	/// 
	/// A trampoline has a managed entry point, which contains two standard parameters:
	/// an offset into a virtual table used to select the target method, and a
	/// native instance pointer. Together these are used to look up a specific native
	/// method; executing the trampoline invokes that method, passing along the
	/// instance pointer and any additional parameters defined by the trampoline.
	/// 
	/// The trampoline's signature consists of the return type and the native parameter
	/// set (including the instance pointer).
	/// </summary>
	class Trampoline
	{
		#region Interface

		/// <summary>
		/// Initializes a new instance of the <see cref="Trampoline"/> class.
		/// </summary>
		/// <param name="returnType">The return type of the target method.</param>
		/// <param name="parameterTypes">Parameters .</param>
		public Trampoline(bool isInstance, Type returnType, params TrampolineParameter[] parameterTypes)
		{
			IsInstanceCall = isInstance;
			ReturnType = returnType ?? typeof(void);

			var nativeParameterTypes = new List<TrampolineParameter>();
			var managedParameterTypes = new List<TrampolineParameter>();
			if (IsInstanceCall)
			{
				nativeParameterTypes.Add(new TrampolineParameter(typeof(IntPtr)));
				managedParameterTypes.Add(new TrampolineParameter(typeof(int)));
				managedParameterTypes.Add(new TrampolineParameter(typeof(IntPtr)));
			}
			else
			{
				// (entry point only)
				managedParameterTypes.Add(new TrampolineParameter(typeof(IntPtr)));
			}

			if (parameterTypes != null)
			{
				nativeParameterTypes.AddRange(parameterTypes);
				managedParameterTypes.AddRange(parameterTypes);
			}

			NativeParameterTypes = new ReadOnlyCollection<TrampolineParameter>(nativeParameterTypes);
			ManagedParameterTypes = new ReadOnlyCollection<TrampolineParameter>(managedParameterTypes);
		}

		public bool IsInstanceCall
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the return type of the trampoline.
		/// </summary>
		public Type ReturnType
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the parameters of the target native method (including the instance pointer).
		/// </summary>
		public ReadOnlyCollection<TrampolineParameter> NativeParameterTypes
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the parameters of the managed entry point into the trampoline
		/// (including the virtual table offset and instance pointer).
		/// </summary>
		public ReadOnlyCollection<TrampolineParameter> ManagedParameterTypes
		{
			get;
			private set;
		}

		/// <summary>
		/// Determines whether the specified <see cref="System.Object"/> is equal to this instance.
		/// </summary>
		/// <param name="other">The <see cref="System.Object"/> to compare with this instance.</param>
		/// <returns>
		/// 	<c>true</c> if the specified <see cref="System.Object"/> is equal to this instance; otherwise, <c>false</c>.
		/// </returns>
		public override bool Equals(object other)
		{
			var trampoline = other as Trampoline;
			if (trampoline == null || trampoline.ReturnType != ReturnType || trampoline.ManagedParameterTypes.Count != ManagedParameterTypes.Count)
				return false;

			for (var parameterIndex = 0; parameterIndex < trampoline.ManagedParameterTypes.Count; ++parameterIndex)
			{
				if (trampoline.ManagedParameterTypes[parameterIndex].Type != ManagedParameterTypes[parameterIndex].Type)
					return false;
			}

			return true;
		}

		/// <summary>
		/// Returns a hash code for this instance.
		/// </summary>
		/// <returns>
		/// A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table. 
		/// </returns>
		public override int GetHashCode()
		{
			var result = ReturnType.GetHashCode();
			foreach (var type in ManagedParameterTypes)
				result += type.Type.GetHashCode();

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
			return string.Format("{0} -> {1}", ReturnType, string.Join(", ", ManagedParameterTypes));
		}
		#endregion
	}
}
