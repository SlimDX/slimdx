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

#include "Buffer3DSettings.h"

namespace SlimDX
{
namespace DirectSound
{
	Buffer3DSettings::Buffer3DSettings( const DS3DBUFFER& value )
	{
		ConeOrientation = Vector3( value.vConeOrientation.x, value.vConeOrientation.y, value.vConeOrientation.z );
		ConeOutsideVolume = value.lConeOutsideVolume;
		InsideConeAngle = value.dwInsideConeAngle;
		OutsideConeAngle = value.dwOutsideConeAngle;
		MaxDistance = value.flMaxDistance;
		MinDistance = value.flMinDistance;
		Position = Vector3( value.vPosition.x, value.vPosition.y, value.vPosition.z );
		Velocity = Vector3( value.vVelocity.x, value.vVelocity.y, value.vVelocity.z );
		Mode = static_cast<Mode3D>( value.dwMode );
	}

	DS3DBUFFER Buffer3DSettings::ToUnmanaged()
	{
		DS3DBUFFER result;
		ZeroMemory( &result, sizeof( DS3DBUFFER ) );
		result.dwSize = sizeof( DS3DBUFFER );
		result.vConeOrientation.x = ConeOrientation.X;
		result.vConeOrientation.y = ConeOrientation.Y;
		result.vConeOrientation.z = ConeOrientation.Z;
		result.lConeOutsideVolume = ConeOutsideVolume;
		result.dwInsideConeAngle = InsideConeAngle;
		result.dwOutsideConeAngle = OutsideConeAngle;
		result.flMaxDistance = MaxDistance;
		result.flMinDistance = MinDistance;
		result.vPosition.x = Position.X;
		result.vPosition.y = Position.Y;
		result.vPosition.z = Position.Z;
		result.vVelocity.x = Velocity.X;
		result.vVelocity.y = Velocity.Y;
		result.vVelocity.z = Velocity.Z;
		result.dwMode = static_cast<DWORD>( Mode );

		return result;
	}
}
}