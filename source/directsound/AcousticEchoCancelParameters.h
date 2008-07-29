/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once
			
namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// Contains parameters for acoustic echo cancellation in a capture buffer.
		/// </summary>		
		public value class AcousticEchoCancelParameters
		{
		internal:
			AcousticEchoCancelParameters( const DSCFXAec& value );
			DSCFXAec Marshal();

		public:
			/// <summary>
			/// Boolean value that specifies whether the effect is enabled.
			/// </summary>
			property bool Enable;

			/// <summary>
			/// Boolean value that specifies whether to enable background comfort noise, which makes the capture signal sound more natural by preventing periods of dead silence. By default, background comfort noise is not enabled.
			/// </summary>
			property bool NoiseFill;

			/// <summary>
			/// Operation mode.
			/// </summary>
			property AcousticEchoCancelMode Mode;
		};
	}
}