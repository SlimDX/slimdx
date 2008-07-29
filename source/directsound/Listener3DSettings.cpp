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
#include <dsound.h>

#include "../math/Vector3.h"

#include "Listener3DSettings.h"

namespace SlimDX
{
namespace DirectSound
{
	Listener3DSettings::Listener3DSettings( const DS3DLISTENER &value )
	{
		DistanceFactor = value.flDistanceFactor;
		DopplerFactor = value.flDopplerFactor;
		RolloffFactor = value.flRolloffFactor;
		TopOrientation = Vector3( value.vOrientTop.x, value.vOrientTop.y, value.vOrientTop.z);
		FrontOrientation = Vector3( value.vOrientFront.x, value.vOrientFront.y, value.vOrientFront.z );
		Position = Vector3( value.vPosition.x, value.vPosition.y, value.vPosition.z );
		Velocity = Vector3( value.vVelocity.x, value.vVelocity.y, value.vVelocity.z );
	}

	DS3DLISTENER Listener3DSettings::ToUnmanaged()
	{
		DS3DLISTENER result;
		ZeroMemory(&result, sizeof( DS3DLISTENER ) );
		result.dwSize = sizeof( DS3DLISTENER );
		result.flDistanceFactor = DistanceFactor;
		result.flDopplerFactor = DopplerFactor;
		result.flRolloffFactor = RolloffFactor;
		result.vOrientFront.x = FrontOrientation.X;
		result.vOrientFront.y = FrontOrientation.Y;
		result.vOrientFront.z = FrontOrientation.Z;
		result.vOrientTop.x = TopOrientation.X;
		result.vOrientTop.y = TopOrientation.Y;
		result.vOrientTop.z = TopOrientation.Z;
		result.vPosition.x = Position.X;
		result.vPosition.y = Position.Y;
		result.vPosition.z = Position.Z;
		result.vVelocity.x = Velocity.X;
		result.vVelocity.y = Velocity.Y;
		result.vVelocity.z = Velocity.Z;

		return result;
	}
}
}