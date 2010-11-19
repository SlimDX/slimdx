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
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.InteropServices;

namespace SlimDX.Generator
{
	/// <summary>
	/// A component that builds assemblies containing <see cref="Trampoline"/> methods.
	/// </summary>
	class TrampolineAssemblyBuilder
	{
		#region Interface

		/// <summary>
		/// Adds a trampoline to the builder.
		/// </summary>
		/// <param name="trampoline">The trampoline to add.</param>
		public void Add(Trampoline trampoline)
		{
			trampolines.Add(trampoline);
		}

		/// <summary>
		/// Creates a trampoline implementation assembly based on the current state of the builder.
		/// </summary>
		/// <param name="name">The name of the trampoline assembly.</param>
		public void CreateAssembly(string name)
		{
			Contract.Assert(!string.IsNullOrEmpty(name));

			var fileName = string.Format("{0}.dll", name);
			var assemblyName = new AssemblyName(name);
			var assemblyBuilder = AppDomain.CurrentDomain.DefineDynamicAssembly(assemblyName, AssemblyBuilderAccess.Save);
			var moduleBuilder = assemblyBuilder.DefineDynamicModule(fileName);
			var typeBuilder = moduleBuilder.DefineType("Call", dispatchClassAttributes);

			foreach (var trampoline in trampolines)
				BuildTrampolineMethod(trampoline, typeBuilder);

			typeBuilder.CreateType();
			assemblyBuilder.Save(fileName);
		}

		#endregion
		#region Implementation

		HashSet<Trampoline> trampolines = new HashSet<Trampoline>();

		static TypeAttributes dispatchClassAttributes = TypeAttributes.Public | TypeAttributes.Class;
		static MethodAttributes trampolineMethodAttributes = MethodAttributes.Public | MethodAttributes.Static | MethodAttributes.HideBySig;

		/// <summary>
		/// Builds an implementation method for the specified trampoline.
		/// </summary>
		/// <param name="trampoline">The trampoline.</param>
		/// <param name="typeBuilder">The type builder for the type that will contain the method.</param>
		static void BuildTrampolineMethod(Trampoline trampoline, TypeBuilder typeBuilder)
		{
			var methodName = trampoline.ReturnType.Name;
			var methodBuilder = typeBuilder.DefineMethod(methodName, trampolineMethodAttributes);
			var il = methodBuilder.GetILGenerator();
			methodBuilder.SetSignature(trampoline.ReturnType, null, null, ExtractTypes(trampoline.ManagedParameterTypes), null, null);

			// Push the arguments to the native method on the stack.
			for (int parameterIndex = 0; parameterIndex < trampoline.NativeParameterTypes.Count; ++parameterIndex)
			{
				// We use ldarg.1, ldarg.2 and ldarg.3 if possible; these opcodes are much smaller because
				// they don't require an int8 parameter token (and the JIT won't inline methods over a
				// certain number of bytes)
				if (parameterIndex == 0)
					il.Emit(OpCodes.Ldarg_1);
				else if (parameterIndex == 1)
					il.Emit(OpCodes.Ldarg_2);
				else if (parameterIndex == 2)
					il.Emit(OpCodes.Ldarg_3);
				else
					il.Emit(OpCodes.Ldarg_S, parameterIndex + 2);
			}

			// Load the instance pointer, and dereference it to leave the base address of
			// the virtual table on the stack.
			il.Emit(OpCodes.Ldarg_1);
			il.Emit(OpCodes.Ldind_I);

			// Load the byte offset from the start of the table and add them to yeild
			// the pointer to the slot containing the desired method's address.
			il.Emit(OpCodes.Ldarg_0);
			//il.Emit(OpCodes.Conv_I);
			il.Emit(OpCodes.Add);

			// Read the table slot, leaving the address of the target method on the stack.
			il.Emit(OpCodes.Ldind_I);

			// Finally, call the method.
			il.EmitCalli(OpCodes.Calli, CallingConvention.StdCall, trampoline.ReturnType, ExtractTypes(trampoline.NativeParameterTypes));
			il.Emit(OpCodes.Ret);
		}

		/// <summary>
		/// Extracts an array of <see cref="Type"/> objects from a set of <see cref="TrampolineParameter"/> objects.
		/// </summary>
		/// <param name="parameters">The trampoline parameters.</param>
		/// <returns>An array of types.</returns>
		static Type[] ExtractTypes(IEnumerable<TrampolineParameter> parameters)
		{
			return parameters.Select(p => p.Type).ToArray();
		}

		#endregion
	}
}
