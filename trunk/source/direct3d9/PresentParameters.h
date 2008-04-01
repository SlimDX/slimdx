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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		/// <summary>Describes the presentation parameters.</summary>
		/// <unmanaged>D3DPRESENT_PARAMETERS</unmanaged>
		public ref class PresentParameters : System::ICloneable, System::IEquatable<PresentParameters^>
		{
		internal:
			D3DPRESENT_PARAMETERS ToUnmanaged();

			virtual System::Object^ Clone2() = System::ICloneable::Clone
			{
				return Clone();
			}

		public:
			PresentParameters();

			property int BackBufferWidth;
			property int BackBufferHeight;
			property Format BackBufferFormat;
			property int BackBufferCount;

			property MultisampleType Multisample;
			property int MultisampleQuality;

			property SwapEffect SwapEffect;
			property System::IntPtr DeviceWindowHandle;
			property bool Windowed;
			property bool EnableAutoDepthStencil;
			property Format AutoDepthStencilFormat;
			property PresentFlags PresentFlags;

			property int FullScreenRefreshRateInHertz;
			property PresentInterval PresentationInterval;

			PresentParameters^ Clone();

			static bool operator == ( PresentParameters^ left, PresentParameters^ right );
			static bool operator != ( PresentParameters^ left, PresentParameters^ right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( PresentParameters^ other );
			static bool Equals( PresentParameters^ value1, PresentParameters^ value2 );
		};
	}
}