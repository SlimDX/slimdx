/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System;
using namespace System::Collections::ObjectModel;
using namespace System::Runtime::InteropServices;

#include "../ComObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Surface;
		value class FrameStatistics;
		value class GammaControlCapabilities;
		value class ModeDescription;
		value class OutputDescription;

		public ref class Output : public ComObject
		{
			COMOBJECT(IDXGIOutput);
		
		internal:
			Output( IDXGIOutput* pointer );

		public:
			Result GetDescription( [Out] OutputDescription% description );
			
			ReadOnlyCollection<ModeDescription>^ GetDisplayModeList( Format format, DisplayModeEnumerationFlags flags );
			
			Result GetFrameStatistics( [Out] FrameStatistics% statistics );
			Result GetGammaControlCapabilities( [Out] GammaControlCapabilities% capabilities );
			
			Result FindClosestMatchingMode( ComObject^ device, ModeDescription modeToMatch, [Out] ModeDescription %result );
			
			Result SetDisplaySurface( Surface^ surface );
			
			Result TakeOwnership( ComObject^ device, bool exclusive );
			void ReleaseOwnership();
			
			Result WaitForVerticalBlank();
		};
	}
};