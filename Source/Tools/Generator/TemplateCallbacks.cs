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
		public static string MethodParameters(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			for (var parameterIndex = 0; parameterIndex < method.Parameters.Count; ++parameterIndex)
			{
				var parameter = method.Parameters[parameterIndex];
				if (parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
					builder.Append("out ");

                if (parameter.Type == TypeModel.VoidModel)
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
				if (parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
				{
                    if (parameter.Type == TypeModel.VoidModel)
                        builder.AppendFormat("System.IntPtr _{0} = System.IntPtr.Zero;", parameter.Name);
                    else
                    {
                        if (parameter.Type is EnumerationModel)
                        {
                            builder.AppendFormat("int _{0} = default(int);", parameter.Name);
                        }
                        else
                        {
                            builder.AppendFormat("{0} _{1} = default({0});", (parameter.Type is InterfaceModel) ? parameter.Type.MarshallingType.FullName : parameter.Type.Name, parameter.Name);
                            if (!(parameter.Type is InterfaceModel) && parameter.Type.MarshallingType == typeof (IntPtr))
                            {
                                builder.AppendLine();
                                builder.AppendFormat("System.IntPtr __{0} = new System.IntPtr(&_{0});", parameter.Name);
                            }
                        }

                    }
				    builder.AppendLine();
				}
			}

			return builder.ToString();
		}

		public static string MethodTrampoline(TemplateEngine engine, object source)
		{
			var method = (MethodModel)source;
			var builder = new StringBuilder();

			if (method.Type != TypeModel.VoidModel)
				builder.AppendFormat("{0} _result = SlimDX.Trampoline.Call{1}(", method.Type.MarshallingType.FullName, method.Type.MarshallingType.Name);
			else
				builder.Append("SlimDX.Trampoline.Call(");

			builder.AppendFormat("System.IntPtr.Size * {0}, NativePointer", method.Index);
			foreach (var parameter in method.Parameters)
			{
			    builder.Append(", ");
                if (!(parameter.Type is InterfaceModel) && parameter.Type.MarshallingType == typeof(IntPtr) && parameter.Type.Name != "System.IntPtr" && parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
                {
                    builder.AppendFormat("ref __{0}", parameter.Name);
                }
                else
                {
                    if (parameter.Flags.HasFlag(ParameterModelFlags.IsOutput))
                        builder.AppendFormat("ref _{0}", parameter.Name);
                    else
                    {
                        if (parameter.Type is EnumerationModel)
                            builder.AppendFormat("(int){0}", parameter.Name);
                        else if (!(parameter.Type is InterfaceModel) && parameter.Type.MarshallingType == typeof(IntPtr) && parameter.Type.Name != "System.IntPtr")
                            builder.AppendFormat("new System.IntPtr(&{0})", parameter.Name);
                        else if(parameter.Type is InterfaceModel)
                            builder.AppendFormat("{0}.NativePointer", parameter.Name);
                        else
                            builder.AppendFormat(parameter.Name);
                    }
                }

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
                    if (parameter.Type is InterfaceModel)
                        builder.AppendFormat("{0} = new {1}(_{0});", parameter.Name, parameter.Type.Name);
                    else
                    {
                        if (parameter.Type is EnumerationModel)
                        {
                            builder.AppendFormat("{0} = ({1})_{0};", parameter.Name, parameter.Type.Name);
                        }
                        else
                        {
                            builder.AppendFormat("{0} = _{0};", parameter.Name);
                        }
                    }
				    builder.AppendLine();
				}
			}

			if (method.Type != TypeModel.VoidModel)
				builder.Append("return _result;");

			return builder.ToString();
		}
	}
}
