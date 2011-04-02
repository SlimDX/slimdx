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
	interface Formatter
	{
		#region Interface

		/// <summary>
		/// Gets the code for declaring the specified model as a parameter to a managed method.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		string GetFormalParameterCode(ParameterModel model);

		/// <summary>
		/// Gets the code for passing the specified model as parameter to a trampoline method.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		string GetTrampolineParameterCode(ParameterModel model);

		/// <summary>
		/// Gets the code for setup of local variables related to the specified parameter.
		/// </summary>
		/// <param name="marshaller">The marshalling service interface.</param>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		string GetLocalVariableSetupCode(MarshallingService marshaller, ParameterModel model);

		/// <summary>
		/// Gets the code for cleanup of local variables related to the specified parameter.
		/// </summary>
		/// <param name="model">The model.</param>
		/// <returns>The code.</returns>
		string GetLocalVariableCleanupCode(ParameterModel model);

		#endregion
	}
}
