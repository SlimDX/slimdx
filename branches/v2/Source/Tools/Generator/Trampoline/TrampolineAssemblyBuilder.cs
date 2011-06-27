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
using System.IO;
using System.Linq;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.InteropServices;
using System.Text;

namespace SlimDX.Generator
{
	/// <summary>
	/// A component that builds assemblies containing <see cref="Trampoline"/> methods.
	/// </summary>
	class TrampolineAssemblyBuilder
	{
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
		/// <param name="key">The name of the trampoline assembly.</param>
		public void CreateAssembly(string directory, string name)
		{
			if (string.IsNullOrEmpty(name))
				throw new ArgumentException("Value may not be null or empty.", "key");

			var assemblyFileName = string.Format("{0}.dll", name);
			var assemblyName = new AssemblyName(name);
			var assemblyBuilder = AppDomain.CurrentDomain.DefineDynamicAssembly(assemblyName, AssemblyBuilderAccess.Save, directory);
			var moduleBuilder = assemblyBuilder.DefineDynamicModule(assemblyFileName);
			var typeBuilder = moduleBuilder.DefineType(name, trampolineClassAttributes);

			foreach (var trampoline in trampolines)
				BuildTrampolineMethod(trampoline, typeBuilder);

			var result = typeBuilder.CreateType();
			assemblyBuilder.Save(assemblyFileName);

            var codeFileName = Path.Combine(directory, string.Format("{0}.cs", result.Name));
            var codeBuilder = new StringBuilder();
            codeBuilder.AppendLine(string.Format("namespace {0} {{", result.Namespace));
            codeBuilder.AppendLine(string.Format("\tstatic class {0} {{", result.Name));
            foreach (var method in result.GetMethods(BindingFlags.Static | BindingFlags.Public)) {
                BuildTrampolineStub(method, codeBuilder);
            }
            codeBuilder.AppendLine("\t}");
            codeBuilder.AppendLine("}");
            File.WriteAllText(codeFileName, codeBuilder.ToString());
		}

		/// <summary>
		/// Builds an implementation method for the specified trampoline.
		/// </summary>
		/// <param name="trampoline">The trampoline.</param>
		/// <param name="typeBuilder">The type builder for the type that will contain the method.</param>
		static void BuildTrampolineMethod(Trampoline trampoline, TypeBuilder typeBuilder)
		{
			if (!trampoline.IsInstanceCall)
			{
				BuildFreeCall(trampoline, typeBuilder);
				return;
			}

			var methodName = string.Format("CallInstance{0}", trampoline.ReturnType == typeof(void) ? string.Empty : trampoline.ReturnType.Name);
			var methodBuilder = typeBuilder.DefineMethod(methodName, trampolineMethodAttributes);
			var il = methodBuilder.GetILGenerator();
			methodBuilder.SetSignature(trampoline.ReturnType, null, null, ExtractTypes(trampoline.ManagedParameterTypes), null, null);
			methodBuilder.DefineParameter(1, ParameterAttributes.None, offsetParameterName);
			methodBuilder.DefineParameter(2, ParameterAttributes.None, thisParameterName);

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
					il.Emit(OpCodes.Ldarg_S, parameterIndex + 1);
			}

			// Load the instance pointer, and dereference it to leave the base address of
			// the virtual table on the stack.
			il.Emit(OpCodes.Ldarg_1);
			il.Emit(OpCodes.Ldind_I);

			// Load the byte offset from the start of the table and add them to yeild
			// the pointer to the slot containing the desired method's address.
			il.Emit(OpCodes.Ldarg_0);
			il.Emit(OpCodes.Add);

			// Read the table slot, leaving the address of the target method on the stack.
			il.Emit(OpCodes.Ldind_I);

			// Finally, call the method.
			il.EmitCalli(OpCodes.Calli, CallingConvention.StdCall, trampoline.ReturnType, ExtractTypes(trampoline.NativeParameterTypes));
			il.Emit(OpCodes.Ret);
		}

        static void BuildTrampolineStub(MethodInfo method, StringBuilder codeBuilder)
        {
            var returnTypeName = method.ReturnType == typeof(void) ? "void" : method.ReturnType.FullName;
            codeBuilder.AppendFormat("\t\t{0} {1}(", returnTypeName, method.Name);

            var parameters = method.GetParameters();
            for (int parameterIndex = 0; parameterIndex < parameters.Length; ++parameterIndex)
            {
                var parameter = parameters[parameterIndex];
                var parameterName = parameter.Name;

                // Some automatically-generated parameters don't have their own names; C# requires
                // all parameters to be named, however.
                //TODO: Give the trampoline parameters names so this isn't neccessary.
                if(string.IsNullOrEmpty(parameterName))
                    parameterName = string.Format("parameter{0}", parameterIndex - 2);
                
                var parameterType = parameter.ParameterType;
                var decoration = string.Empty;
                if(parameterType.IsByRef)
                {
                    decoration = "ref ";
                    parameterType = parameterType.GetElementType();
                }

                codeBuilder.AppendFormat("{0}{1} {2}", decoration, parameterType.FullName, parameterName);
                if (parameterIndex < parameters.Length - 1)
                    codeBuilder.Append(", ");
            }

            codeBuilder.Append(") { ");
            if (method.ReturnType != typeof(void)) {
                codeBuilder.AppendFormat("return default({0}); ", returnTypeName);
            }
            codeBuilder.AppendLine("}");
        }

        static void BuildFreeCall(Trampoline trampoline, TypeBuilder typeBuilder)
		{
			var methodName = string.Format("CallFree{0}", trampoline.ReturnType == typeof(void) ? string.Empty : trampoline.ReturnType.Name);
			var methodBuilder = typeBuilder.DefineMethod(methodName, trampolineMethodAttributes);
			var il = methodBuilder.GetILGenerator();
			methodBuilder.SetSignature(trampoline.ReturnType, null, null, ExtractTypes(trampoline.ManagedParameterTypes), null, null);
			methodBuilder.DefineParameter(1, ParameterAttributes.None, offsetParameterName);
			methodBuilder.DefineParameter(2, ParameterAttributes.None, thisParameterName);

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
					il.Emit(OpCodes.Ldarg_S, parameterIndex + 1);
			}

			// Load the instance pointer, and dereference it to leave the base address of
			// the virtual table on the stack.
			//il.Emit(OpCodes.Ldarg_1);
			//il.Emit(OpCodes.Ldind_I);

			//// Load the byte offset from the start of the table and add them to yeild
			//// the pointer to the slot containing the desired method's address.
			// For free functions, the offset is the actual entry point.
			il.Emit(OpCodes.Ldarg_0);
			//il.Emit(OpCodes.Add);

			// Read the table slot, leaving the address of the target method on the stack.
			//il.Emit(OpCodes.Ldind_I);

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
			return parameters.Select(p => p.Type == typeof(void) ? typeof(IntPtr) : p.Type).ToArray();
		}

		HashSet<Trampoline> trampolines = new HashSet<Trampoline>();

		static TypeAttributes trampolineClassAttributes = TypeAttributes.Public | TypeAttributes.Class | TypeAttributes.Abstract | TypeAttributes.Sealed;
		static MethodAttributes trampolineMethodAttributes = MethodAttributes.Public | MethodAttributes.Static | MethodAttributes.HideBySig;

		const string offsetParameterName = "offsetInBytes";
		const string thisParameterName = "self";

	}
}
