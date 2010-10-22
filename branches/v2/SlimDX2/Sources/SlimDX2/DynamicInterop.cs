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
using System.IO;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.InteropServices;

namespace SlimDX2
{
    /// <summary>
    ///   Helper class to dynamically generate the interop assembly.
    /// </summary>
    internal class DynamicInterop
    {
        /// <summary>
        ///   Internal simple interop signature description.
        /// </summary>
        public class CalliSignature
        {
            public CalliSignature(string name, Type returnType, Type[] parameterTypes)
            {
                Name = name;
                ReturnType = returnType;
                ParameterTypes = parameterTypes;
            }

            public string Name;
            public Type ReturnType;
            public Type[] ParameterTypes;
        }

        /// <summary>
        ///   Generate SlimDX2.Interop assembly based on signatures.
        /// </summary>
        /// <param name = "methods">an array of signatures</param>
        /// <param name = "saveAssembly">true to save the generated assembly</param>
        /// <param name = "relativePath">relative path to current directory to save the assembly</param>
        /// <returns></returns>
        public static Assembly Generate(CalliSignature[] methods, bool saveAssembly, string relativePath)
        {
            string name = typeof (DynamicInterop).Namespace + ".Interop";

            AssemblyName aname = new AssemblyName(name);
            aname.Version = new Version(1, 0, 0, 0);

            // Create Assembly and Module
            AssemblyBuilder asmBldr = AppDomain.CurrentDomain.DefineDynamicAssembly(aname,
                                                                                    AssemblyBuilderAccess.RunAndSave);
            ModuleBuilder modBldr = asmBldr.DefineDynamicModule(name + ".dll", name + ".dll");

            // Create class SlimDX2.Interop
            TypeBuilder tb = modBldr.DefineType(name, TypeAttributes.Public | TypeAttributes.Class);

            // Inherit from System.Object
            Type objType = Type.GetType("System.Object");
            ConstructorInfo objCtor = objType.GetConstructor(new Type[0]);

            // Default constructor private
            Type[] ctorParams = new Type[0] {};
            ConstructorBuilder pointCtor = tb.DefineConstructor(
                MethodAttributes.Private,
                CallingConventions.Standard,
                ctorParams);
            ILGenerator ctorIL = pointCtor.GetILGenerator();
            ctorIL.Emit(OpCodes.Ldarg_0);
            ctorIL.Emit(OpCodes.Call, objCtor);
            ctorIL.Emit(OpCodes.Ret);

            // Determine 32/64bit mode
            bool isx64 = IntPtr.Size == 8;

            // Iterate on each method and generate interop code
            for (int i = 0; i < methods.Length; i++)
            {
                var method = methods[i];

                Type[] calliParameterTypes = new Type[method.ParameterTypes.Length + 1];
                Type[] publicParameterTypes = new Type[method.ParameterTypes.Length + 2];
                publicParameterTypes[0] = typeof (void*);
                publicParameterTypes[1] = typeof (int);
                calliParameterTypes[0] = typeof (void*);
                for (int j = 0; j < method.ParameterTypes.Length; j++)
                {
                    publicParameterTypes[2 + j] = method.ParameterTypes[j];
                    calliParameterTypes[1 + j] = method.ParameterTypes[j];
                }


                MethodBuilder mb1 = tb.DefineMethod(method.Name,
                                                    MethodAttributes.Public | MethodAttributes.Static |
                                                    MethodAttributes.HideBySig,
                                                    CallingConventions.Standard,
                                                    method.ReturnType,
                                                    publicParameterTypes);

                for (int j = 0; j < publicParameterTypes.Length; j++)
                {
                    mb1.DefineParameter(j + 1, ParameterAttributes.None, "arg" + j); // Assign name 
                }


                ILGenerator il1 = mb1.GetILGenerator();


                il1.Emit(OpCodes.Ldarg_0); // first parameter this object

                // Push all parameters
                for (int j = 1; j < calliParameterTypes.Length; j++)
                {
                    if (j == 1)
                        il1.Emit(OpCodes.Ldarg_2);
                    else if (j == 2)
                        il1.Emit(OpCodes.Ldarg_3);
                    else
                        il1.Emit(OpCodes.Ldarg_S, (byte) (j + 1));
                }

                il1.Emit(OpCodes.Ldarg_1); // virtual table offset
                il1.Emit(OpCodes.Conv_I); // convert to native int

                if (isx64)
                {
                    // If x64
                    il1.Emit(OpCodes.Dup); // convert to native int
                    il1.Emit(OpCodes.Add);
                }

                il1.Emit(OpCodes.Ldarg_0); // this
                il1.Emit(OpCodes.Ldind_I); // vtbl
                il1.Emit(OpCodes.Add); // vtbl + offset
                il1.Emit(OpCodes.Ldind_I); // vtbl

                // Call native unmanaged method
                il1.EmitCalli(OpCodes.Calli, CallingConvention.StdCall, method.ReturnType, calliParameterTypes);
                il1.Emit(OpCodes.Ret);
            }

            // Create generic CopyMethod Param
            CreateReadMethod(tb);
            CreateWriteMethod(tb);

            CreateReadRangeMethod(tb);
            CreateWriteRangeMethod(tb);

            CreateMemcpy(tb);

            Type type = tb.CreateType();

            if (saveAssembly)
            {
                string fileName = name + ".dll";
                asmBldr.Save(fileName);
                // Copy file to output
                File.Copy(fileName, relativePath + Path.DirectorySeparatorChar + fileName, true);
                File.Delete(fileName);
            }

            return type.Assembly;
        }

        private static void CreateWriteRangeMethod(TypeBuilder tb)
        {
            MethodBuilder methodCopyStruct = tb.DefineMethod("Write",
                                                             MethodAttributes.Public | MethodAttributes.Static |
                                                             MethodAttributes.HideBySig,
                                                             CallingConventions.Standard);

            GenericTypeParameterBuilder paramT = methodCopyStruct.DefineGenericParameters("T")[0];
            paramT.SetGenericParameterAttributes(GenericParameterAttributes.NotNullableValueTypeConstraint |
                                                 GenericParameterAttributes.DefaultConstructorConstraint);

            var paramTArray = paramT.MakeArrayType();
            methodCopyStruct.SetReturnType(typeof (void*));
            methodCopyStruct.SetParameters(new Type[] {typeof (void*), paramTArray, typeof (int), typeof (int)});


            ParameterBuilder pDest = methodCopyStruct.DefineParameter(1, ParameterAttributes.None, "pDest");
            // Parameter data
            ParameterBuilder data = methodCopyStruct.DefineParameter(2, ParameterAttributes.None, "data");
            // Parameter offset
            ParameterBuilder offset = methodCopyStruct.DefineParameter(3, ParameterAttributes.None, "offset");
            // Parameter count
            ParameterBuilder count = methodCopyStruct.DefineParameter(4, ParameterAttributes.None, "count");

            ILGenerator gen = methodCopyStruct.GetILGenerator();
            // Preparing locals
            LocalBuilder totalSize = gen.DeclareLocal(typeof (int)); // sizeof(T) * count
            LocalBuilder pinnedData = gen.DeclareLocal(paramT.MakePointerType(), true);

            // Push (0) pDest for memcpy
            gen.Emit(OpCodes.Ldarg_0);

            // fixed (void* pinnedData = &data[offset])
            gen.Emit(OpCodes.Ldarg_1);
            gen.Emit(OpCodes.Ldarg_2);
            gen.Emit(OpCodes.Ldelema, paramT);
            gen.Emit(OpCodes.Stloc_1);

            // Push (1) pinnedData for memcpy
            gen.Emit(OpCodes.Ldloc_1);

            // totalSize = sizeof(T) * count
            gen.Emit(OpCodes.Sizeof, paramT);
            gen.Emit(OpCodes.Conv_I4);
            gen.Emit(OpCodes.Ldarg_3);
            gen.Emit(OpCodes.Mul);
            gen.Emit(OpCodes.Stloc_0);

            // Push (2) totalSize
            gen.Emit(OpCodes.Ldloc_0);

            if (IntPtr.Size == 8)
                gen.Emit(OpCodes.Unaligned, 1);

            // Memcpy
            gen.Emit(OpCodes.Cpblk);

            // Return pDest + totalSize
            gen.Emit(OpCodes.Ldloc_0);
            gen.Emit(OpCodes.Conv_I);
            gen.Emit(OpCodes.Ldarg_0);
            gen.Emit(OpCodes.Add);

            // Ret
            gen.Emit(OpCodes.Ret);
        }

        private static void CreateWriteMethod(TypeBuilder tb)
        {
            MethodBuilder methodCopyStruct = tb.DefineMethod("Write",
                                                             MethodAttributes.Public | MethodAttributes.Static |
                                                             MethodAttributes.HideBySig,
                                                             CallingConventions.Standard);

            GenericTypeParameterBuilder paramT = methodCopyStruct.DefineGenericParameters("T")[0];
            paramT.SetGenericParameterAttributes(GenericParameterAttributes.NotNullableValueTypeConstraint |
                                                 GenericParameterAttributes.DefaultConstructorConstraint);

            methodCopyStruct.SetReturnType(typeof (void*));
            methodCopyStruct.SetParameters(new Type[] {typeof (void*), paramT.MakeByRefType()});


            ParameterBuilder pDest = methodCopyStruct.DefineParameter(1, ParameterAttributes.None, "pDest");
            // Parameter data
            ParameterBuilder data = methodCopyStruct.DefineParameter(2, ParameterAttributes.None, "data");


            ILGenerator gen = methodCopyStruct.GetILGenerator();
            // Preparing locals
            LocalBuilder totalSize = gen.DeclareLocal(typeof (int)); // sizeof(T)
            LocalBuilder pinnedData = gen.DeclareLocal(paramT.MakePointerType(), true);

            // Push (0) pDest for memcpy
            gen.Emit(OpCodes.Ldarg_0);

            // fixed (void* pinnedData = &data[offset])
            gen.Emit(OpCodes.Ldarg_1);
            gen.Emit(OpCodes.Stloc_1);

            // Push (1) pinnedData for memcpy
            gen.Emit(OpCodes.Ldloc_1);

            // totalSize = sizeof(T)
            gen.Emit(OpCodes.Sizeof, paramT);
            gen.Emit(OpCodes.Conv_I4);
            gen.Emit(OpCodes.Stloc_0);

            // Push (2) totalSize
            gen.Emit(OpCodes.Ldloc_0);

            if (IntPtr.Size == 8)
                gen.Emit(OpCodes.Unaligned, 1);

            // Memcpy
            gen.Emit(OpCodes.Cpblk);

            // Return pDest + totalSize
            gen.Emit(OpCodes.Ldloc_0);
            gen.Emit(OpCodes.Conv_I);
            gen.Emit(OpCodes.Ldarg_0);
            gen.Emit(OpCodes.Add);

            // Ret
            gen.Emit(OpCodes.Ret);
        }

        private static void CreateReadRangeMethod(TypeBuilder tb)
        {
            MethodBuilder methodCopyStruct = tb.DefineMethod("Read",
                                                             MethodAttributes.Public | MethodAttributes.Static |
                                                             MethodAttributes.HideBySig,
                                                             CallingConventions.Standard);

            GenericTypeParameterBuilder paramT = methodCopyStruct.DefineGenericParameters("T")[0];
            paramT.SetGenericParameterAttributes(GenericParameterAttributes.NotNullableValueTypeConstraint |
                                                 GenericParameterAttributes.DefaultConstructorConstraint);

            var paramTArray = paramT.MakeArrayType();
            methodCopyStruct.SetReturnType(typeof (void*));
            methodCopyStruct.SetParameters(new Type[] {typeof (void*), paramTArray, typeof (int), typeof (int)});


            ParameterBuilder pDest = methodCopyStruct.DefineParameter(1, ParameterAttributes.None, "pSrc");
            // Parameter data
            ParameterBuilder data = methodCopyStruct.DefineParameter(2, ParameterAttributes.None, "data");
            // Parameter offset
            ParameterBuilder offset = methodCopyStruct.DefineParameter(3, ParameterAttributes.None, "offset");
            // Parameter count
            ParameterBuilder count = methodCopyStruct.DefineParameter(4, ParameterAttributes.None, "count");

            ILGenerator gen = methodCopyStruct.GetILGenerator();
            // Preparing locals
            LocalBuilder totalSize = gen.DeclareLocal(typeof (int)); // sizeof(T) * count
            LocalBuilder pinnedData = gen.DeclareLocal(paramT.MakePointerType(), true);

            // fixed (void* pinnedData = &data[offset])
            gen.Emit(OpCodes.Ldarg_1);
            gen.Emit(OpCodes.Ldarg_2);
            gen.Emit(OpCodes.Ldelema, paramT);
            gen.Emit(OpCodes.Stloc_1);

            // Push (0) pinnedData for memcpy
            gen.Emit(OpCodes.Ldloc_1);

            // Push (1) pDest for memcpy
            gen.Emit(OpCodes.Ldarg_0);

            // totalSize = sizeof(T) * count
            gen.Emit(OpCodes.Sizeof, paramT);
            gen.Emit(OpCodes.Conv_I4);
            gen.Emit(OpCodes.Ldarg_3);
            gen.Emit(OpCodes.Conv_I4);
            gen.Emit(OpCodes.Mul);
            gen.Emit(OpCodes.Stloc_0);

            // Push (2) totalSize
            gen.Emit(OpCodes.Ldloc_0);

            if (IntPtr.Size == 8)
                gen.Emit(OpCodes.Unaligned, 1);

            // Memcpy
            gen.Emit(OpCodes.Cpblk);

            // Return pDest + totalSize
            gen.Emit(OpCodes.Ldloc_0);
            gen.Emit(OpCodes.Conv_I);
            gen.Emit(OpCodes.Ldarg_0);
            gen.Emit(OpCodes.Add);

            // Ret
            gen.Emit(OpCodes.Ret);
        }

        private static void CreateReadMethod(TypeBuilder tb)
        {
            MethodBuilder methodCopyStruct = tb.DefineMethod("Read",
                                                             MethodAttributes.Public | MethodAttributes.Static |
                                                             MethodAttributes.HideBySig,
                                                             CallingConventions.Standard);

            GenericTypeParameterBuilder paramT = methodCopyStruct.DefineGenericParameters("T")[0];
            paramT.SetGenericParameterAttributes(GenericParameterAttributes.NotNullableValueTypeConstraint |
                                                 GenericParameterAttributes.DefaultConstructorConstraint);

            methodCopyStruct.SetReturnType(typeof (void*));
            methodCopyStruct.SetParameters(new Type[] {typeof (void*), paramT.MakeByRefType()});


            ParameterBuilder pDest = methodCopyStruct.DefineParameter(1, ParameterAttributes.None, "pSrc");
            // Parameter data
            ParameterBuilder data = methodCopyStruct.DefineParameter(2, ParameterAttributes.None, "data");


            ILGenerator gen = methodCopyStruct.GetILGenerator();
            // Preparing locals
            LocalBuilder totalSize = gen.DeclareLocal(typeof (int)); // sizeof(T)
            LocalBuilder pinnedData = gen.DeclareLocal(paramT.MakePointerType(), true);

            // fixed (void* pinnedData = &data[offset])
            gen.Emit(OpCodes.Ldarg_1);
            gen.Emit(OpCodes.Stloc_1);

            // Push (0) pinnedData for memcpy
            gen.Emit(OpCodes.Ldloc_1);

            // Push (1) pSrc for memcpy
            gen.Emit(OpCodes.Ldarg_0);

            // totalSize = sizeof(T)
            gen.Emit(OpCodes.Sizeof, paramT);
            gen.Emit(OpCodes.Conv_I4);
            gen.Emit(OpCodes.Stloc_0);

            // Push (2) totalSize
            gen.Emit(OpCodes.Ldloc_0);

            if (IntPtr.Size == 8)
                gen.Emit(OpCodes.Unaligned, 1);

            // Memcpy
            gen.Emit(OpCodes.Cpblk);

            // Return pDest + totalSize
            gen.Emit(OpCodes.Ldloc_0);
            gen.Emit(OpCodes.Conv_I);
            gen.Emit(OpCodes.Ldarg_0);
            gen.Emit(OpCodes.Add);

            // Ret
            gen.Emit(OpCodes.Ret);
        }

        private static void CreateMemcpy(TypeBuilder tb)
        {
            bool x64 = (IntPtr.Size == 8);


            MethodBuilder methodCopyStruct;

            if (x64)
                methodCopyStruct = tb.DefineMethod("memcpy",
                                                   MethodAttributes.Public | MethodAttributes.Static |
                                                   MethodAttributes.HideBySig,
                                                   CallingConventions.Standard);
            else
                methodCopyStruct = tb.DefineMethod("memcpy",
                                                   MethodAttributes.Public | MethodAttributes.Static |
                                                   MethodAttributes.HideBySig | MethodAttributes.PinvokeImpl,
                                                   CallingConventions.Standard);

            methodCopyStruct.SetReturnType(typeof (void));
            methodCopyStruct.SetParameters(new Type[] {typeof (void*), typeof (void*), typeof (int)});


            ParameterBuilder pDest = methodCopyStruct.DefineParameter(1, ParameterAttributes.None, "pDest");
            ParameterBuilder pSrc = methodCopyStruct.DefineParameter(2, ParameterAttributes.None, "pSrc");
            ParameterBuilder count = methodCopyStruct.DefineParameter(3, ParameterAttributes.None, "count");

            ILGenerator gen = methodCopyStruct.GetILGenerator();

            gen.Emit(OpCodes.Ldarg_0);
            gen.Emit(OpCodes.Ldarg_1);
            gen.Emit(OpCodes.Ldarg_2);
            if (IntPtr.Size == 8)
                gen.Emit(OpCodes.Unaligned, 1);

            // Memcpy
            gen.Emit(OpCodes.Cpblk);
            // Ret
            gen.Emit(OpCodes.Ret);
        }
    }
}