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

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// Describes the 3-D world parameters and the position of the listener.
		/// </summary>
		public value class Listener3DSettings
		{
		internal:
			DS3DLISTENER ToUnmanaged();
			Listener3DSettings( const DS3DLISTENER &value );

		public:
			/// <summary>
			/// Number of meters in a vector unit.
			/// </summary>
			property float DistanceFactor;
			/// <summary>
			/// Ratio of Doppler effect to that in the real world.
			/// </summary>
			property float DopplerFactor;
			/// <summary>
			/// Ratio of attenuation over distance to that in the real world.
			/// </summary>
			property float RolloffFactor;
			/// <summary>
			/// Describes the listener's front orientation.
			/// </summary>
			property Vector3 FrontOrientation;
			/// <summary>
			/// Describes the listener's top orientation.
			/// </summary>
			property Vector3 TopOrientation;
			/// <summary>
			/// Describes the listener's position.
			/// </summary>
			property Vector3 Position;
			/// <summary>
			/// Describes the listener's velocity.
			/// </summary>
			property Vector3 Velocity;
		};
	}
}