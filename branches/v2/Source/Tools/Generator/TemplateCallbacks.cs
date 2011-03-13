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

using System.Text;
using System;
using System.Runtime.InteropServices;

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

		public static string MethodParameters(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			for (var parameterIndex = 0; parameterIndex < method.Parameters.Count; ++parameterIndex)
			{
				var parameter = method.Parameters[parameterIndex];
				if (parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
					builder.Append("out ");

				if (parameter.Type == ApiModel.VoidModel)
					builder.AppendFormat("System.IntPtr {0}", parameter.Name);
				else
					builder.AppendFormat("{0} {1}", parameter.Type.Name, parameter.Name);

				if (parameterIndex < method.Parameters.Count - 1)
					builder.Append(", ");
			}

			return builder.ToString();
		}

		public static string MethodPrologue(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			foreach (var parameter in method.Parameters)
			{
				var declaration = GetParameterDeclarationString(parameter);
				if (!string.IsNullOrEmpty(declaration))
					builder.AppendLine(declaration);
			}

			return builder.ToString();
		}

		public static string MethodTrampoline(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			string trampolineSuffix = string.Empty;
			if (method.Type != ApiModel.VoidModel)
			{
				var methodTypeName = method.Type.Name;
				var translationModel = method.Type as TranslationModel;
				if (translationModel != null)
				{
					var type = Type.GetType(translationModel.TargetType);
					methodTypeName = type.FullName;
					trampolineSuffix = type.Name;
				}

				builder.AppendFormat("{0} _result = ", methodTypeName);
			}

			builder.AppendFormat("SlimDX.Trampoline.Call{0}(System.IntPtr.Size * {1}, NativePointer", trampolineSuffix, method.Index);
			foreach (var parameter in method.Parameters)
				builder.AppendFormat(", {0}", GetParameterTrampolineString(parameter));

			builder.Append(");");
			return builder.ToString();
		}

		public static string MethodEpilogue(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			foreach (var parameter in method.Parameters)
			{
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
			}

			if (method.Type != ApiModel.VoidModel)
				builder.Append("return _result;");

			return builder.ToString();
		}

		public static string StructureMemberMarshallerDeclaration(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			if (member.Type is StructureModel)
				builder.AppendFormat("public {0}Marshaller {1};", member.Type.Name, member.Name);
			else
				builder.AppendFormat("public {0} {1};", GetQualifiedName(engine, member.Type), member.Name);

			return builder.ToString();
		}

		public static string MemberFromMarshallerAssignment(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			if (member.Type is StructureModel)
				builder.AppendFormat("result.{0} = {1}.FromMarshaller(source.{0});", member.Name, member.Type.Name);
			else
				builder.AppendFormat("result.{0} = source.{0};", member.Name);

			return builder.ToString();
		}

		public static string MemberToMarshallerAssignment(TemplateEngine engine, object source)
		{
			StructureMemberModel member = (StructureMemberModel)source;
			var builder = new StringBuilder();

			if (member.Type is StructureModel)
				builder.AppendFormat("result.{0} = {1}.ToMarshaller(source.{0});", member.Name, member.Type.Name);
			else
				builder.AppendFormat("result.{0} = source.{0};", member.Name);

			return builder.ToString();
		}

		static string GetParameterDeclarationString(ParameterModel parameter)
		{
			switch (GetBehavior(parameter))
			{
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
			if (model is StructureModel)
				return MarshalBehavior.Marshal;
			if (model is InterfaceModel || model.Key == "IUnknown")
				return MarshalBehavior.Wrapped;
			return MarshalBehavior.Default;
		}

		public static MarshalBehavior GetBehavior(ParameterModel model)
		{
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
				return MarshalBehavior.Output;
			return GetBehavior(model.Type);
		}
	}
}
