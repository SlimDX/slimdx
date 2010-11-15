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
using System.IO;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.InteropServices;

namespace SlimDX
{
    /// <summary>
    /// Type used for template
    /// </summary>
    public class TypeWrapper
    {
        private Type _type;
        private string _typeName;

        public TypeWrapper(Type type)
        {
            _type = type;
        }

        public TypeWrapper(string typeName)
        {
            _typeName = typeName;
        }

        public Type Type
        {
            get { return _type; }
        }

        public static implicit operator TypeWrapper(Type input)
        {
            return new TypeWrapper(input);
        }

        public static implicit operator TypeWrapper(string input)
        {
            return new TypeWrapper(input);
        }

        public string TypeName
        {
            get
            {
                Type type = Type;

                if (type != null)
                {
                    if (type == typeof(int))
                        return "int";
                    if (type == typeof(short))
                        return "short";
                    if (type == typeof(void*) || type == typeof(IntPtr))
                        return "void*";
                    if (type == typeof(void))
                        return "void";
                    if (type == typeof(float))
                        return "float";
                    if (type == typeof(long))
                        return "long";

                    return type.FullName;
                }
                return _typeName;
            }
        }

        public string ParamTypeOfName
        {
            get
            {
                return "typeof(" + TypeName + ")";
            }
        }


        public bool IsPrimitive
        {
            get
            {
                if (Type != null)
                    return Type.IsPrimitive;
                return false;
            }
        }

        public bool IsValueType
        {
            get
            {
                if (Type != null)
                    return Type.IsValueType;
                // If typename != null is necessary a ValueType
                return true;
            }
        }

        public override bool Equals(object obj)
        {
            TypeWrapper against = obj as TypeWrapper;
            if (against == null)
                return false;
            return Type == against.Type && _typeName == against._typeName;
        }

        public static bool operator ==(TypeWrapper a, Type b)
        {
            // If both are null, or both are same instance, return true.
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }

            // If one is null, but not both, return false.
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }

            return a.Type == b;
        }

        public static bool operator !=(TypeWrapper a, Type b)
        {
            return !(a == b);
        }

        public static bool operator ==(TypeWrapper a, TypeWrapper b)
        {
            // If both are null, or both are same instance, return true.
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }

            // If one is null, but not both, return false.
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }

            return a.Equals(b);
        }

        public static bool operator !=(TypeWrapper a, TypeWrapper b)
        {
            return !(a == b);
        }
    }

#if XIDLToCSharp
    public class DynamicInterop
#else
    /// <summary>
    ///   Helper class to dynamically generate the interop assembly.
    /// </summary>
    internal class DynamicInterop
#endif
    {

        /// <summary>
        ///   Internal simple interop signature description.
        /// </summary>
        public class CalliSignature
        {
            public CalliSignature(string name, TypeWrapper returnType, params TypeWrapper[] parameterTypes)
            {
                Name = name;
                ReturnType = returnType;
                ParameterTypes = parameterTypes;
            }

            public string Name;
            public TypeWrapper ReturnType;
            public TypeWrapper[] ParameterTypes;
        }

        /// <summary>
        ///   Generate SlimDX.Interop assembly based on signatures.
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

            // Create class SlimDX.Interop
            TypeBuilder tb = modBldr.DefineType(name, TypeAttributes.Public | TypeAttributes.Class);

            // Inherit from System.Object
            Type objType = Type.GetType("System.Object");
            ConstructorInfo objCtor = objType.GetConstructor(new Type[0]);

            // Default constructor private
            Type[] ctorParams = new Type[0] {};
            ConstructorBuilder pointCtor = tb.DefineConstructor(
                MethodAttributes.Public,
                CallingConventions.Standard,
                ctorParams);
            ILGenerator ctorIL = pointCtor.GetILGenerator();
            ctorIL.Emit(OpCodes.Ldarg_0);
            ctorIL.Emit(OpCodes.Call, objCtor);
            ctorIL.Emit(OpCodes.Ret);

            // Iterate on each method and generate interop code
            foreach (CalliSignature t in methods)
                Create(tb, t, null);

            // Create generic CopyMethod Param
            CreateReadMethod(tb);
            CreateWriteMethod(tb);

            CreateReadRangeMethod(tb);
            CreateWriteRangeMethod(tb);

            CreateMemcpy(tb);

            CreateSizeOfStructGeneric(tb);

            Type type = tb.CreateType();

            if (saveAssembly)
            {
                string fileName = name + ".dll";
                asmBldr.Save(fileName);
                if (relativePath != null && relativePath != ".")
                {
                    // Copy file to output
                    File.Copy(fileName, relativePath + Path.DirectorySeparatorChar + fileName, true);
                    File.Delete(fileName);
                }
            }

            return type.Assembly;
        }


        public static void InitDelegates(Type interopType)
        {
            var fields = interopType.GetFields();
            foreach (var fieldInfo in fields)
            {
                if (fieldInfo.FieldType.IsSubclassOf(typeof(System.MulticastDelegate)))
                {
                    var calliDelegate = CreateDelegate(fieldInfo.FieldType);
                    fieldInfo.SetValue(null, calliDelegate);
                }
            }
        }

        private static Delegate CreateDelegate(Type typeOfDelegate)
        {
            var methodInfo = typeOfDelegate.GetMethod("Invoke");
            var parametersInfo = methodInfo.GetParameters();
            var parametersSignature = new List<TypeWrapper>();
            for (int i = 2; i < parametersInfo.Length; i++)
                parametersSignature.Add(parametersInfo[i].ParameterType);

            var signature = new CalliSignature("none", methodInfo.ReturnType, parametersSignature.ToArray());

            return Create(null, signature, typeOfDelegate);
        }

        private static Delegate CreateDelegate(CalliSignature method, Type typeOfDelegate)
        {
            return Create(null, method, typeOfDelegate);
        }

        private static Delegate Create(TypeBuilder tb, CalliSignature method, Type delegateType)
        {
            Type[] calliParameterTypes = new Type[method.ParameterTypes.Length + 1];
            Type[] publicParameterTypes = new Type[method.ParameterTypes.Length + 2];
            publicParameterTypes[0] = typeof(void*);
            publicParameterTypes[1] = typeof(int);
            calliParameterTypes[0] = typeof(void*);

            // Construct methods parameters type
            for (int j = 0; j < method.ParameterTypes.Length; j++)
            {
                var typeWrap = method.ParameterTypes[j];
                Type paramType = typeWrap.Type;
                publicParameterTypes[2 + j] = paramType;
                calliParameterTypes[1 + j] = paramType;
            }

            Type returnType = method.ReturnType.Type;


            ILGenerator il1;
            Delegate methodDelegate = null;
            DynamicMethod builder = null;

            if (tb != null )
            {
                MethodBuilder mb1 = tb.DefineMethod(method.Name,
                                                    MethodAttributes.Public | MethodAttributes.Static |
                                                    MethodAttributes.HideBySig,
                                                    CallingConventions.Standard);

                // Set Return type and parameters type
                mb1.SetParameters(publicParameterTypes);
                mb1.SetReturnType(returnType);

                for (int j = 0; j < publicParameterTypes.Length; j++)
                {
                    mb1.DefineParameter(j + 1, ParameterAttributes.None, "arg" + j); // Assign name 
                }

                il1 = mb1.GetILGenerator();
            }
            else 
            {
                builder = new DynamicMethod(method.Name, returnType, publicParameterTypes, typeof(DynamicInterop).Module);

                for (int j = 0; j < publicParameterTypes.Length; j++)
                {
                    builder.DefineParameter(j + 1, ParameterAttributes.None, "arg" + j); // Assign name 
                }
                il1 = builder.GetILGenerator();
            }


            il1.Emit(OpCodes.Ldarg_0); // first parameter this object

            // Push all parameters
            for (int j = 1; j < calliParameterTypes.Length; j++)
            {
                if (j == 1)
                    il1.Emit(OpCodes.Ldarg_2);
                else if (j == 2)
                    il1.Emit(OpCodes.Ldarg_3);
                else
                    il1.Emit(OpCodes.Ldarg_S, (byte)(j + 1));

                //if (tb == null && calliParameterTypes[j].IsValueType)
                //{
                //    il1.Emit(OpCodes.Unbox, calliParameterTypes[j]);
                //}
            }

            il1.Emit(OpCodes.Ldarg_1); // virtual table offset
            il1.Emit(OpCodes.Conv_I); // convert to native int

            if (IntPtr.Size == 8)
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
            il1.EmitCalli(OpCodes.Calli, CallingConvention.StdCall, returnType, calliParameterTypes);
            il1.Emit(OpCodes.Ret);


            if (tb == null)
            {
                methodDelegate = builder.CreateDelegate(delegateType);
            }
            return methodDelegate;
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

            //if (x64)
                methodCopyStruct = tb.DefineMethod("memcpy",
                                                   MethodAttributes.Public | MethodAttributes.Static |
                                                   MethodAttributes.HideBySig,
                                                   CallingConventions.Standard);

            // NEED MORE TEST : memcpy seems to be far more inefficient on x86 targets
            // I need to perform more test with it.
            // A possible solution is to generate :
            // - a memcpy using cpblk for x64 architecture
            // - a memcpy using DllImpotr memcpy from msvcrt.dll for x86 architecture

            //else
            //    methodCopyStruct = tb.DefineMethod("memcpy",
            //                                       MethodAttributes.Public | MethodAttributes.Static |
            //                                       MethodAttributes.HideBySig | MethodAttributes.PinvokeImpl,
            //                                       CallingConventions.Standard);

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

        private static void CreateSizeOfStructGeneric(TypeBuilder tb)
        {
            MethodBuilder methodCopyStruct = tb.DefineMethod("SizeOf",
                                                             MethodAttributes.Public | MethodAttributes.Static |
                                                             MethodAttributes.HideBySig,
                                                             CallingConventions.Standard);

            GenericTypeParameterBuilder paramT = methodCopyStruct.DefineGenericParameters("T")[0];
            paramT.SetGenericParameterAttributes(GenericParameterAttributes.NotNullableValueTypeConstraint |
                                                 GenericParameterAttributes.DefaultConstructorConstraint);

            methodCopyStruct.SetReturnType(typeof(int));
            methodCopyStruct.SetParameters(new Type[0]);


            ILGenerator gen = methodCopyStruct.GetILGenerator();
            gen.Emit(OpCodes.Sizeof, paramT);
            // Ret
            gen.Emit(OpCodes.Ret);            
        }

    }
}