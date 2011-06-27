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
using System.Linq;
using System.Text;

namespace SlimDX.Generator
{
	static class TemplateCallbacks
	{
		/// <summary>
		/// Initializes the <see cref="TemplateCallbacks"/> class.
		/// </summary>
		static TemplateCallbacks()
		{
			formatters[MarshalBehavior.Direct] = new DirectFormatter();
			formatters[MarshalBehavior.Indirect] = new IndirectFormatter();
			formatters[MarshalBehavior.Enumeration] = new EnumerationFormatter();
			formatters[MarshalBehavior.String] = new StringFormatter();
			formatters[MarshalBehavior.Array] = new ArrayFormatter();
			formatters[MarshalBehavior.Structure] = new StructureFormatter();
			formatters[MarshalBehavior.Interface] = new InterfaceFormatter();
		}

		public static string EnumItem(TemplateEngine engine, object source)
		{
			dynamic s = source;
			if (s.Name.EndsWith("FORCE_DWORD") || s.Name.EndsWith("FORCE_UINT"))
				return string.Empty;

			return s.Name + " = " + s.Value + ",";
		}

		public static string GetQualifiedName(TemplateEngine engine, object source)
		{
			var type = (TypeModel)source;
			if (type.Api != null)
				return string.Format("{0}.{1}", type.Api.Name, type.Name);
			return type.Name;
		}

		public static string FunctionParameters(TemplateEngine engine, object source)
		{
			var function = (FunctionModel)source;
			var builder = new StringBuilder();

			for (var parameterIndex = 0; parameterIndex < function.Parameters.Count; ++parameterIndex)
			{
				var parameter = function.Parameters[parameterIndex];
				var formatter = formatters[marshaller.ResolveBehavior(parameter)];
				builder.Append(formatter.GetFormalParameterCode(parameter));

				if (parameterIndex < function.Parameters.Count - 1)
					builder.Append(", ");
			}

			return builder.ToString();
		}

		public static string FunctionPrologue(TemplateEngine engine, object source)
		{
			var method = (FunctionModel)source;
			var builder = new StringBuilder();

			foreach (var parameter in method.Parameters)
			{
				var formatter = formatters[marshaller.ResolveBehavior(parameter)];
				builder.AppendLine(formatter.GetLocalVariableSetupCode(marshaller, parameter));
			}

			return builder.ToString();
		}

		public static string FunctionTrampoline(TemplateEngine engine, object source)
		{
			var function = (FunctionModel)source;
			var builder = new StringBuilder();

			string trampolineSuffix = string.Empty;
			if (function.Type != ApiModel.VoidModel)
			{
				var methodTypeName = function.Type.Name;
				var translationModel = function.Type as TranslationModel;
				if (translationModel != null)
				{
					var type = Type.GetType(translationModel.TargetType);
					methodTypeName = type.FullName;
					trampolineSuffix = type.Name;
				}

				builder.AppendFormat("{0} _result = ", methodTypeName);
			}

			var method = function as MethodModel;
            var api = function.Api;
			if (method != null)
				builder.AppendFormat("{0}.Trampoline.CallInstance{1}(System.IntPtr.Size * {2}, NativePointer", api.Name, trampolineSuffix, method.Index);
			else
				builder.AppendFormat("{0}.Trampoline.CallFree{1}(functions[{2}]", api.Name, trampolineSuffix, api.Functions.IndexOf(function));

			foreach (var parameter in function.Parameters)
			{
				var formatter = formatters[marshaller.ResolveBehavior(parameter)];
				builder.AppendFormat(", {0}", formatter.GetTrampolineParameterCode(parameter));
			}

			builder.Append(");");
			return builder.ToString();
		}

		public static string FunctionEpilogue(TemplateEngine engine, object source)
		{
			var method = (FunctionModel)source;
			var builder = new StringBuilder();

			foreach (var parameter in method.Parameters)
			{
				var formatter = formatters[marshaller.ResolveBehavior(parameter)];
				builder.AppendLine(formatter.GetLocalVariableCleanupCode(parameter));
			}

			if (method.Type != ApiModel.VoidModel)
				builder.Append("return _result;");

			return builder.ToString();
		}

		public static string StructureMemberMarshallerDeclaration(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			switch (marshaller.ResolveBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("public System.IntPtr {0};", member.Name);
					break;
				case MarshalBehavior.Structure:
					builder.AppendFormat("public {0}Marshaller {1};", GetQualifiedName(engine, member.Type), member.Name);
					break;
				default:
					builder.AppendFormat("public {0} {1};", GetQualifiedName(engine, member.Type), member.Name);
					break;
			}

			return builder.ToString();
		}

		public static string StructureMemberMarshallerReleaseStatement(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			switch (marshaller.ResolveBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("System.Runtime.InteropServices.Marshal.FreeHGlobal({0});", member.Name);
					break;
				case MarshalBehavior.Structure:
					builder.AppendFormat("{0}.Release();", member.Name);
					break;
				default:
					break;
			}

			return builder.ToString();
		}

		public static string MemberFromMarshallerAssignment(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			switch (marshaller.ResolveBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("result.{0} = new string((sbyte*)source.{0});", member.Name);
					break;
				case MarshalBehavior.Structure:
					builder.AppendFormat("result.{0} = {1}.FromMarshaller(source.{0});", member.Name, GetQualifiedName(engine, member.Type));
					break;
				default:
					builder.AppendFormat("result.{0} = source.{0};", member.Name);
					break;
			}

			return builder.ToString();
		}

		public static string MemberToMarshallerAssignment(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			switch (marshaller.ResolveBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("result.{0} = source.{0} != null ? System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi(source.{0}) : System.IntPtr.Zero;", member.Name);
					break;
				case MarshalBehavior.Structure:
					builder.AppendFormat("result.{0} = {1}.ToMarshaller(source.{0});", member.Name, GetQualifiedName(engine, member.Type));
					break;
				default:
					builder.AppendFormat("result.{0} = source.{0};", member.Name);
					break;
			}

			return builder.ToString();
		}

		public static string GetApiClassName(ApiModel api)
		{
			return api.Name.Split('.').Last();
		}

		public static string GetApiDllName(ApiModel api)
		{
			switch (api.Name)
			{
				case "SlimDX.DXGI":
					return "dxgi.dll";
				case "SlimDX.Direct3D11":
					return "d3d11.dll";
				case "SlimDX.ShaderCompiler":
					return "d3dcompiler_43.dll";
				default:
					return string.Empty;
			}
		}

        static MarshallingService marshaller = new MarshallingService();
		static Dictionary<MarshalBehavior, Formatter> formatters = new Dictionary<MarshalBehavior, Formatter>();
	}
}
