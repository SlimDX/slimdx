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
using System.Linq;
using System.Text;
using SlimDX.Generator.ObjectModel;

namespace SlimDX.Generator
{
	static class TemplateCallbacks
	{
		public static string GenerateManagedParameterType(object source)
		{
			var parameter = (VariableElement)source;
			var format = "{0}";
			if ((parameter.Usage & UsageQualifiers.Out) != 0)
				format = (parameter.Usage & UsageQualifiers.In) != 0 ? "ref {0}" : "out {0}";

			return string.Format(format, parameter.Type.ManagedName);
		}

		public static string GenerateConstructors(object source)
		{
			const int indentLevel = 2;

			var type = (InterfaceElement)source;
			var builder = new StringBuilder();

			builder.Indent(indentLevel).AppendFormat("internal {0}(System.IntPtr nativePointer)", type.ManagedName);
			builder.Indent(indentLevel).AppendLine();

			if (type.BaseType.NativeName != "IUnknown")
				builder.Indent(indentLevel + 1).AppendFormat(": base(nativePointer)").AppendLine();

			builder.Indent(indentLevel).AppendLine("{");
			builder.Indent(indentLevel + 1).AppendLine("this.nativePointer = nativePointer;");
			builder.Indent(indentLevel).Append("}");

			return builder.ToString();
		}

		public static string GenerateFunctionBody(object source)
		{
			const int indentLevel = 3;

			var function = (FunctionElement)source;
			var builder = new StringBuilder();

			// The intermidate objects for output parameters must be declared first.
			foreach (var parameter in function.Parameters)
			{
				if ((parameter.Usage & UsageQualifiers.Out) != 0 && (parameter.Usage & UsageQualifiers.In) == 0)
				{
					builder.Indent(indentLevel).AppendFormat("{0} _{1} = default({0});", parameter.Type.IntermediateType.FullName, parameter.NativeName);
					builder.AppendLine();
				}
			}

			var resultVariable = string.Empty;
			if (function.ReturnType.IntermediateType != typeof(void))
				resultVariable = string.Format("{0} _result = ", function.ReturnType.ManagedName);
			builder.Indent(indentLevel).AppendFormat("{0}SlimDX.Trampoline.{1}({2} * System.IntPtr.Size, nativePointer", resultVariable, function.ReturnType.ManagedName, function.Index);

			foreach (var parameter in function.Parameters)
			{
				if ((parameter.Usage & UsageQualifiers.Out) != 0 && (parameter.Usage & UsageQualifiers.In) == 0)
					builder.AppendFormat(", ref _{0}", parameter.NativeName);
				else
					builder.AppendFormat(", {0}", parameter.NativeName);
			}

			builder.AppendLine(");");

			// Once the call has been made, intermediate objects must be transformed to the proper managed types.
			foreach (var parameter in function.Parameters)
			{
				if ((parameter.Usage & UsageQualifiers.Out) != 0 && (parameter.Usage & UsageQualifiers.In) == 0)
				{
					if (parameter.Type.IntermediateType.IsValueType && parameter.Type.IntermediateType != typeof(IntPtr))
						builder.Indent(indentLevel).AppendFormat("{0} =_{0};", parameter.NativeName);
					else
						builder.Indent(indentLevel).AppendFormat("{0} = new {1}(_{0});", parameter.NativeName, parameter.Type.ManagedName);
					builder.AppendLine();
				}
			}

			if (function.ReturnType.IntermediateType != typeof(void))
				builder.Indent(indentLevel).Append("return _result;");
			return builder.ToString();
		}
	}
}
