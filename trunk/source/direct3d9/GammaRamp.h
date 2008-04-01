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
	namespace Direct3D9
	{
		/// <summary>Contains red, green, and blue ramp data.</summary>
		/// <unmanaged>D3DGAMMARAMP</unmanaged>
		public ref class GammaRamp
		{
		private:
			System::Collections::ObjectModel::Collection<System::Int16>^ red;
			System::Collections::ObjectModel::Collection<System::Int16>^ green;
			System::Collections::ObjectModel::Collection<System::Int16>^ blue;

		internal:
			GammaRamp( const D3DGAMMARAMP &ramp );

			D3DGAMMARAMP ToUnmanaged();

		public:
			GammaRamp();

			property System::Collections::ObjectModel::Collection<System::Int16>^ Red
			{
				System::Collections::ObjectModel::Collection<System::Int16>^ get() { return red; }
			}

			property System::Collections::ObjectModel::Collection<System::Int16>^ Green
			{
				System::Collections::ObjectModel::Collection<System::Int16>^ get() { return green; }
			}

			property System::Collections::ObjectModel::Collection<System::Int16>^ Blue
			{
				System::Collections::ObjectModel::Collection<System::Int16>^ get() { return blue; }
			}
		};
	}
}