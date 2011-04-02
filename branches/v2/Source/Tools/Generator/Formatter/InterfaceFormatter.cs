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

namespace SlimDX.Generator
{
	class InterfaceFormatter : Formatter
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
				return string.Format("out {0} {1}", model.Type.Name, model.Name);
			else
				return string.Format("{0} {1}", model.Type.Name, model.Name);

		}

		/// <summary>
		/// Gets the code for passing the specified model as parameter to a trampoline method.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		public string GetTrampolineParameterCode(ParameterModel model)
		{
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
				return string.Format("ref _{0}", model.Name);
			return string.Format("{0} != null ? {0}.NativePointer : System.IntPtr.Zero", model.Name);
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
				return string.Format("System.IntPtr _{0} = default(System.IntPtr);", model.Name);
			return string.Empty;
		}

		/// <summary>
		/// Gets the code for cleanup of local variables related to the specified parameter.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		public string GetLocalVariableCleanupCode(ParameterModel model)
		{
			if (model.Flags.HasFlag(ParameterModelFlags.IsOutput))
			{
				//TODO: This check against IUnknown is a hack for DXGISwapChain::GetBuffer. To remove the
				//      hack, it must be made possible to mark a function for removal -- GetBuffer must be
				//      hand-written in terms of the trampoline that would be generated for it, because it
				//      does not make sense for the model layer to understand the relationship between the
				//      output parameter in question, the IID parameter ("riid"), and the object factory.
				if (model.Type.Key == "IUnknown")
					return string.Format("{0} = SlimDX.ObjectFactory.Create(_{0}, riid);", model.Name);
				return string.Format("{0} = _{0} != System.IntPtr.Zero ? new {1}(_{0}) : null;", model.Name, model.Type.Name);
			}

			return string.Empty;
		}

		#endregion
	}
}
