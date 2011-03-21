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
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace SlimDX.Generator
{
	static class TemplateCallbacks
	{
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
				switch (GetBehavior(parameter))
				{
					case MarshalBehavior.Array:
						builder.AppendFormat("{0}[] {1}", parameter.Type.Name, parameter.Name);
						break;
					case MarshalBehavior.Output:
						builder.AppendFormat("out {0} {1}", parameter.Type.Name, parameter.Name);
						break;
					default:
						builder.AppendFormat("{0} {1}", parameter.Type.Name, parameter.Name);
						break;
				}

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
				var declaration = GetParameterDeclarationString(parameter);
				if (!string.IsNullOrEmpty(declaration))
					builder.AppendLine(declaration);
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
			if (method != null)
				builder.AppendFormat("SlimDX.Trampoline.CallInstance{0}(System.IntPtr.Size * {1}, NativePointer", trampolineSuffix, method.Index);
			else
				builder.AppendFormat("SlimDX.Trampoline.CallFree{0}(functions[{1}]", trampolineSuffix, function.Api.Functions.IndexOf(function));

			foreach (var parameter in function.Parameters)
				builder.AppendFormat(", {0}", GetParameterTrampolineString(parameter));

			builder.Append(");");
			return builder.ToString();
		}

		public static string FunctionEpilogue(TemplateEngine engine, object source)
		{
			var method = (FunctionModel)source;
			var builder = new StringBuilder();

			foreach (var parameter in method.Parameters)
			{
				switch (GetBehavior(parameter))
				{
					case MarshalBehavior.Marshal:
						builder.AppendFormat("_{0}.Release();", parameter.Name);
						builder.AppendLine();
						break;
					case MarshalBehavior.String:
						builder.AppendFormat("System.Runtime.InteropServices.Marshal.FreeHGlobal(_{0});", parameter.Name);
						builder.AppendLine();
						break;
					default:
						if (parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
						{
							if (parameter.Type is InterfaceModel)
								builder.AppendFormat("{0} = new {1}(_{0});", parameter.Name, parameter.Type.Name);
							else
							{
								if (parameter.Type is EnumerationModel)
								{
									builder.AppendFormat("{0} = ({1})_{0};", parameter.Name, parameter.Type.Name);
								}
								else if (parameter.Type.Key == "IUnknown")
								{
									// hacky, mostly to work around GetBuffer issues.
									builder.AppendFormat("{0} = SlimDX.ObjectFactory.Create(_{0}, riid);", parameter.Name);
								}
								else
								{
									builder.AppendFormat("{0} = _{0};", parameter.Name);
								}
							}
							builder.AppendLine();
						}
						break;
				}
			}

			if (method.Type != ApiModel.VoidModel)
				builder.Append("return _result;");

			return builder.ToString();
		}

		public static string StructureMemberMarshallerDeclaration(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			switch (GetBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("public System.IntPtr {0};", member.Name);
					break;
				case MarshalBehavior.Marshal:
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

			switch (GetBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("System.Runtime.InteropServices.Marshal.FreeHGlobal({0});", member.Name);
					break;
				case MarshalBehavior.Marshal:
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

			switch (GetBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("result.{0} = new string((sbyte*)source.{0});", member.Name);
					break;
				case MarshalBehavior.Marshal:
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

			switch (GetBehavior(member))
			{
				case MarshalBehavior.String:
					builder.AppendFormat("result.{0} = source.{0} != null ? System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi(source.{0}) : System.IntPtr.Zero;", member.Name);
					break;
				case MarshalBehavior.Marshal:
					builder.AppendFormat("result.{0} = {1}.ToMarshaller(source.{0});", member.Name, GetQualifiedName(engine, member.Type));
					break;
				default:
					builder.AppendFormat("result.{0} = source.{0};", member.Name);
					break;
			}

			return builder.ToString();
		}

		static string GetParameterDeclarationString(ParameterModel parameter)
		{
			switch (GetBehavior(parameter))
			{
				case MarshalBehavior.Array:
					{
						var builder = new StringBuilder();
						builder.AppendLine(string.Format("{0}Marshaller* _{1} = stackalloc {0}Marshaller[{1}.Length];", parameter.Type.Name, parameter.Name));
						builder.AppendLine(string.Format("for(int i = 0; i < {0}.Length; ++i)", parameter.Name));
						builder.AppendLine(string.Format("\t_{0}[i] = {1}.ToMarshaller({0}[i]);", parameter.Name, parameter.Type.Name));
						return builder.ToString();
					}
				case MarshalBehavior.String:
					return string.Format("System.IntPtr _{0} = System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi({0});", parameter.Name);
				case MarshalBehavior.Output:
					return string.Format("System.IntPtr _{0} = default(System.IntPtr);", parameter.Name);
				case MarshalBehavior.Marshal:
					return string.Format("{0}Marshaller _{1} = {0}.ToMarshaller({1});", parameter.Type.Name, parameter.Name);
				default:
					return null;
			}
		}

		static string GetParameterTrampolineString(ParameterModel parameter)
		{
			switch (GetBehavior(parameter))
			{
				case MarshalBehavior.Array:
					return string.Format("new System.IntPtr(_{0})", parameter.Name);
				case MarshalBehavior.String:
					return string.Format("_{0}", parameter.Name);
				case MarshalBehavior.Output:
					return string.Format("ref _{0}", parameter.Name);
				case MarshalBehavior.Marshal:
					return string.Format("new System.IntPtr(&_{0})", parameter.Name);
				case MarshalBehavior.Wrapped:
					return string.Format("{0} != null ? {0}.NativePointer : System.IntPtr.Zero", parameter.Name);
				default:
					return IsLargeType(parameter.Type) ? string.Format("new System.IntPtr(&{0})", parameter.Name) : parameter.Name;
			}
		}

		public static bool IsLargeType(TypeModel model)
		{
			TranslationModel translationModel = model as TranslationModel;
			if (translationModel != null)
			{
				var type = Type.GetType(translationModel.TargetType);
				return Marshal.SizeOf(type) > sizeof(long);
			}

			return false;
		}

		public static MarshalBehavior GetBehavior(TypeModel model)
		{
			TranslationModel translationModel = model as TranslationModel;
			if (translationModel != null)
			{
				var type = Type.GetType(translationModel.TargetType);
				if (type == typeof(string))
					return MarshalBehavior.String;
			}

			if (model is StructureModel)
				return MarshalBehavior.Marshal;
			if (model is InterfaceModel || model.Key == "IUnknown")
				return MarshalBehavior.Wrapped;
			return MarshalBehavior.Default;
		}

		public static MarshalBehavior GetBehavior(ParameterModel model)
		{
			if (model.LengthParameter != null)
				return MarshalBehavior.Array;
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
				return MarshalBehavior.Output;
			return GetBehavior(model.Type);
		}

		public static MarshalBehavior GetBehavior(StructureMemberModel model)
		{
			return GetBehavior(model.Type);
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
	}
}
