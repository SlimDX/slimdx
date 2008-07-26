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

#include <dsound.h>

#include "Enums.h"
#include "../Math/Vector3.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// Contains all information necessary to uniquely describe the location, orientation, and motion of a 3-D sound buffer.
		/// </summary>
		public value class Buffer3DSettings
		{
		internal:
			DS3DBUFFER ToUnmanaged();
			Buffer3DSettings( const DS3DBUFFER& value );

		public:
			/// <summary>
			/// Describes the current orientation of this 3-D buffer's sound projection cone.
			/// </summary>
			property Vector3 ConeOrientation;
			/// <summary>
			/// The cone outside volume.
			/// </summary>
			property int ConeOutsideVolume;
			/// <summary>
			/// The angle of the inside sound projection cone.
			/// </summary>
			property int InsideConeAngle;
			/// <summary>
			/// The maximum distance.
			/// </summary>
			property float MaxDistance;
			/// <summary>
			/// The minimum distance.
			/// </summary>
			property float MinDistance;
			/// <summary>
			/// The 3-D sound processing mode to be set.
			/// </summary>
			property Mode3D Mode;
			/// <summary>
			/// The angle of the outside sound projection cone.
			/// </summary>
			property int OutsideConeAngle;
			/// <summary>
			/// Describes the current position of the 3-D sound buffer.
			/// </summary>
			property Vector3 Position;
			/// <summary>
			/// Describes the current velocity of the 3-D sound buffer.
			/// </summary>
			property Vector3 Velocity;
		};
	}
}