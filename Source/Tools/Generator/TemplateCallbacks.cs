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
using SlimDX.Generator.ObjectModel;

namespace SlimDX.Generator
{
	static class TemplateCallbacks
	{
		public static string MethodParameters(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			for (var parameterIndex = 0; parameterIndex < method.Parameters.Count; ++parameterIndex)
			{
				var parameter = method.Parameters[parameterIndex];
				if (parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
					builder.Append("out ");

				builder.AppendFormat("{0} {1}", parameter.Type.Name, parameter.Name);

				if (parameterIndex < method.Parameters.Count - 1)
					builder.Append(", ");
			}

			return builder.ToString();
		}

		public static string MethodTrampoline(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			if (method.Type != TypeModel.VoidModel)
				builder.AppendFormat("{0} _result = SlimDX.Trampoline.Call{0}(", method.Type.Name);
			else
				builder.Append("SlimDX.Trampoline.Call(");

			for (var parameterIndex = 0; parameterIndex < method.Parameters.Count; ++parameterIndex)
			{
				var parameter = method.Parameters[parameterIndex];
				if (parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
					builder.AppendFormat("out _{0}", parameter.Name);
				else
					builder.AppendFormat(parameter.Name);

				if (parameterIndex < method.Parameters.Count - 1)
					builder.Append(", ");
			}

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
					builder.AppendFormat("{0} = _{0};", parameter.Name);
					builder.AppendLine();
				}
			}

			if (method.Type != TypeModel.VoidModel)
				builder.Append("return _result;");

			return builder.ToString();
		}

		public static string GenerateStructureFromMarshallerBody(TemplateEngine engine, object source)
		{
			var structure = (StructureElement)source;
			var builder = new StringBuilder();

			foreach (var field in structure.Fields)
			{
				builder.Append("\t\t\t");
				if (field.Dimension > 0 && field.Type.NativeName == "WCHAR")
					builder.AppendFormat("result.{0} = new string(marshaller.{0});", field.ManagedName);
				else if (field.Dimension > 0)
					builder.AppendFormat("/* skipped {0} - not supported */", field.ManagedName);
				else if (field.Type is StructureElement || field.Type is EnumerationElement)
					builder.AppendFormat("/* skipped {0} - not supported */", field.ManagedName);
				else
					builder.AppendFormat("result.{0} = marshaller.{0};", field.ManagedName);
				builder.AppendLine();
			}

			return builder.ToString();
		}

		public static string GenerateStructureField(TemplateEngine engine, object source)
		{
			var variable = (VariableElement)source;
			var builder = new StringBuilder("public ");

			if (variable.Dimension > 0 && variable.Type.NativeName == "WCHAR")
				builder.AppendFormat("string {0};", variable.ManagedName);
			else if (variable.Type is StructureElement)
				builder.AppendFormat("{0}Marshaller {1};", variable.Type.ManagedName, variable.ManagedName);
			else if (variable.Type is EnumerationElement)
				builder.AppendFormat("int {0};", variable.ManagedName);
			else
				builder.AppendFormat("{0} {1};", variable.Type.ManagedName, variable.ManagedName);
			return builder.ToString();
		}

		public static string GenerateStructureMarshallerField(TemplateEngine engine, object source)
		{
			var variable = (VariableElement)source;
			var builder = new StringBuilder("public ");

			if (variable.Type is StructureElement)
				builder.AppendFormat("{0}Marshaller {1};", variable.Type.ManagedName, variable.ManagedName);
			else if (variable.Type is EnumerationElement)
				builder.AppendFormat("int {0};", variable.ManagedName);
			else if (variable.Type.IntermediateType == typeof(void*))
			{
				//TODO: This is neccessary to work around the fixed Rgb buffer in GammaControl; need
				// a better way to handle it.
				builder.AppendFormat("{0} {1};", variable.Type.ManagedName, variable.ManagedName);
			}
			else
			{
				if (variable.Dimension > 0)
					builder.Append("fixed ");
				builder.AppendFormat("{0} {1}", variable.Type.ManagedName, variable.ManagedName);
				if (variable.Dimension > 0)
					builder.AppendFormat("[{0}]", variable.Dimension);
				builder.Append(";");
			}
			return builder.ToString();
		}

		public static string GenerateManagedParameterType(TemplateEngine engine, object source)
		{
			var format = "{0}";
			var parameter = (VariableElement)source;
			if (parameter.Usage.HasFlag(UsageQualifiers.Out))
				format = parameter.Usage.HasFlag(UsageQualifiers.In) ? "ref {0}" : "out {0}";

			return string.Format(format, parameter.Type.ManagedName);
		}

		public static string InterfaceBaseInitialization(TemplateEngine engine, object source)
		{
			var type = (InterfaceElement)source;
			var builder = new StringBuilder();
			if (type.BaseType.NativeName != "IUnknown")
				return ": base(nativePointer) ";
			return string.Empty;
		}

		public static bool IsParameterStructure(VariableElement parameterElement)
		{
			return parameterElement.Type is StructureElement;
		}

		public static bool IsParameterInitializable(VariableElement parameterElement)
		{
			var isOutput = parameterElement.Usage.HasFlag(UsageQualifiers.Out) && !parameterElement.Usage.HasFlag(UsageQualifiers.In);
			return !IsParameterStructure(parameterElement) && isOutput;
		}

		public static string FunctionParameters(TemplateEngine engine, object source)
		{
			var function = (FunctionElement)source;
			return string.Join(", ", function.Parameters.Select(p => string.Format("{0} {1}", p.Type.ManagedName, p.NativeName)));
		}

		public static string FunctionBody(TemplateEngine engine, object source)
		{
			var function = (FunctionElement)source;
			var parametersToMarshal = function.Parameters.Where(x => IsParameterStructure(x)).ToList();
			var parametersToInitialize = function.Parameters
									.Where(p => IsParameterInitializable(p))
									.Select(p => new { TypeName = p.Type.IntermediateType.FullName, Name = p.NativeName });

			var initializerText = engine.Apply(@"{initializers:OutInitializer \n\t\t\t}", new { initializers = parametersToInitialize });
			if (!string.IsNullOrEmpty(initializerText))
				initializerText = string.Format("{0}{1}\t\t\t", initializerText, Environment.NewLine);

			var resultVariable = string.Empty;
			var returnStatement = string.Empty;
			if (function.ReturnType.IntermediateType != typeof(void))
			{
				resultVariable = string.Format("{0} _result = ", function.ReturnType.ManagedName);
				returnStatement = "return _result;";
			}

			var marshalStatements = engine.Apply(@"{Parameters:ParameterFixStatement \n\t\t\t}", new { Parameters = parametersToMarshal });
			var marshalAssignments = engine.Apply(
				@"{Parameters:ParameterMarshalledAssignment \n\t\t\t}",
				new { Parameters = parametersToMarshal }
			);

			var result = engine.ApplyByName("FunctionBody", new
			{
				Initializers = initializerText,
				Result = resultVariable,
				ReturnType = function.ReturnType.NativeName == "void" ? string.Empty : function.ReturnType.ManagedName,
				Index = function.Index,
				Return = returnStatement,
				Source = function,

				FixedStatements = marshalStatements,
				MarshalledAssignments = marshalAssignments
			});

			return result.TrimEnd();
		}

		public static string FunctionLocals(TemplateEngine engine, object source)
		{
			var function = (FunctionElement)source;
			var builder = new StringBuilder();

			foreach (var parameter in function.Parameters)
			{
				if (IsParameterInitializable(parameter))
					builder.AppendFormat("{0} _{1} = default({0});", parameter.Type.IntermediateType.Name, parameter.NativeName);
				else if (IsParameterStructure(parameter))
					builder.AppendLine(engine.ApplyByName("ParameterFixStatement", parameter));
			}

			return builder.ToString();
		}

		public static string FunctionTrampolineCall(TemplateEngine engine, object source)
		{
			var function = (FunctionElement)source;
			var builder = new StringBuilder();

			if (function.ReturnType.IntermediateType != typeof(void))
				builder.AppendFormat("{0} _result = ", function.ReturnType.ManagedName);

			var callSuffix = function.ReturnType.NativeName == "void" ? string.Empty : function.ReturnType.ManagedName;
			builder.AppendFormat("SlimDX.Trampoline.Call{0}({1} * System.IntPtr.Size, nativePointer", callSuffix, function.Index);
			foreach (var parameter in function.Parameters)
			{
				if (parameter.Type is StructureElement)
					builder.AppendFormat(", &{0}Marshaller", parameter.NativeName);
				else if (parameter.Usage.HasFlag(UsageQualifiers.Out) && !parameter.Usage.HasFlag(UsageQualifiers.In))
					builder.AppendFormat(", ref _{0}", parameter.NativeName);
				else
					builder.AppendFormat(", {0}", parameter.NativeName);
			}
			builder.Append(");");

			return builder.ToString();
		}

		public static string FunctionReturnStatement(TemplateEngine engine, object source)
		{
			var function = (FunctionElement)source;
			if (function.ReturnType.IntermediateType != typeof(void))
				return "return _result;";
			return string.Empty;
		}

		public static string GenerateTrampolineParameters(TemplateEngine engine, object source)
		{
			var builder = new StringBuilder();
			var function = (FunctionElement)source;
			foreach (var parameter in function.Parameters)
			{
				if (parameter.Type is StructureElement)
					builder.AppendFormat(", &{0}Marshaller", parameter.NativeName);
				else if (parameter.Usage.HasFlag(UsageQualifiers.Out) && !parameter.Usage.HasFlag(UsageQualifiers.In))
					builder.AppendFormat(", ref _{0}", parameter.NativeName);
				else
					builder.AppendFormat(", {0}", parameter.NativeName);
			}

			return builder.ToString();
		}

		public static string ConstructResults(TemplateEngine engine, object source)
		{
			const int indentLevel = 3;

			var builder = new StringBuilder();
			var function = (FunctionElement)source;
			foreach (var parameter in function.Parameters)
			{
				if (parameter.Type is StructureElement)
					continue;
				if (parameter.Usage.HasFlag(UsageQualifiers.Out) && !parameter.Usage.HasFlag(UsageQualifiers.In))
				{
					if (parameter.Type is EnumerationElement)
						builder.Indent(indentLevel).AppendFormat("{0} =({1})_{0};", parameter.NativeName, parameter.Type.ManagedName);
					else if (parameter.Type is InterfaceElement)
						builder.Indent(indentLevel).AppendFormat("{0} = new {1}(_{0});", parameter.NativeName, parameter.Type.ManagedName);
					else
						builder.Indent(indentLevel).AppendFormat("{0} =_{0};", parameter.NativeName);

					builder.AppendLine();
				}
			}

			return builder.ToString();
		}
	}
}
