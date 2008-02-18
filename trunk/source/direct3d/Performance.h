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
	namespace Direct3D
	{
		[System::Flags]
		public enum class PerformanceOptions : System::Int32
		{
			None = 0,
			DoNotAllowProfiling = 1,
		};

		public ref class Performance sealed
		{
		private:
			Performance() { }

		public:
			static int BeginEvent( int color, System::String^ name );
			static int BeginEvent( System::Drawing::Color color, System::String^ name );
			static int EndEvent();

			static bool GetStatus();
			static bool QueryRepeatFrame();

			static void SetMarker( int color, System::String^ name );
			static void SetMarker( System::Drawing::Color color, System::String^ name );
			static void SetOptions( PerformanceOptions options );
			static void SetRegion( int color, System::String^ name );
			static void SetRegion( System::Drawing::Color color, System::String^ name );
		};
	}
}
