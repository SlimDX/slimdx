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
using System.Text;

namespace SlimDX.Generator
{
	class ArrayFormatter : Formatter
	{
		#region Interface

		/// <summary>
		/// Gets the code for declaring the specified model as a parameter to a managed method.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		public string GetFormalParameterCode(ParameterModel model)
		{
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
				return string.Format("out {0}[] {1}", model.Type.Name, model.Name);
			return string.Format("{0}[] {1}", model.Type.Name, model.Name);
		}

		/// <summary>
		/// Gets the code for passing the specified model as parameter to a trampoline method.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		public string GetTrampolineParameterCode(ParameterModel model)
		{
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
				return "System.IntPtr.Zero";
			return string.Format("new System.IntPtr(_{0})", model.Name);
		}

		/// <summary>
		/// Gets the code for setup of local variables related to the specified parameter.
		/// </summary>
		/// <param name="marshaller">The marshalling service interface.</param>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		public string GetLocalVariableSetupCode(MarshallingService marshaller, ParameterModel model)
		{
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
				return string.Empty;

			var builder = new StringBuilder();
			switch (marshaller.ResolveBehavior(model.Type))
			{
				case MarshalBehavior.Structure:
					builder.AppendLine(string.Format("{0}Marshaller* _{1} = stackalloc {0}Marshaller[{1}.Length];", model.Type.Name, model.Name));
					builder.AppendLine(string.Format("for(int i = 0; i < {0}.Length; ++i)", model.Name));
					builder.AppendLine(string.Format("\t_{0}[i] = {1}.ToMarshaller({0}[i]);", model.Name, model.Type.Name));
					break;
				case MarshalBehavior.Interface:
					builder.AppendLine(string.Format("System.IntPtr* _{1} = stackalloc System.IntPtr[{1}.Length];", model.Type.Name, model.Name));
					builder.AppendLine(string.Format("for(int i = 0; i < {0}.Length; ++i)", model.Name));
					builder.AppendLine(string.Format("\t_{0}[i] = {0}[i].NativePointer;", model.Name, model.Type.Name));
					break;
				default:
					builder.AppendLine(string.Format("{0}* _{1} = stackalloc {0}[{1}.Length];", model.Type.Name, model.Name));
					builder.AppendLine(string.Format("for(int i = 0; i < {0}.Length; ++i)", model.Name));
					builder.AppendLine(string.Format("\t_{0}[i] = {0}[i];", model.Name, model.Type.Name));
					break;
			}

			return builder.ToString();
		}

		/// <summary>
		/// Gets the code for cleanup of local variables related to the specified parameter.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		public string GetLocalVariableCleanupCode(ParameterModel model)
		{
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
				return string.Format("{0} = null;", model.Name);
			return string.Empty;
		}

		#endregion
	}
}
