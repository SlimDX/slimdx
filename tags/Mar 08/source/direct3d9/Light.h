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

#include "../math/Color4.h"
#include "../math/Vector3.h"

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class Light : System::IEquatable<Light>
		{
		public:
			property LightType Type;
			property Color4 Diffuse;
			property Color4 Specular;
			property Color4 Ambient;
			property Vector3 Position;
			property Vector3 Direction;
			property float Range;
			property float Falloff;
			property float Attenuation0;
			property float Attenuation1;
			property float Attenuation2;
			property float Theta;
			property float Phi;

			static bool operator == ( Light left, Light right );
			static bool operator != ( Light left, Light right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( Light other );
			static bool Equals( Light% value1, Light% value2 );
		};
	}
}