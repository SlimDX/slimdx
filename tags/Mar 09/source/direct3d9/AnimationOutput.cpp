/*
* Copyright (c) 2007-2009 SlimDX Group
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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>

#include "AnimationOutput.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	bool AnimationOutput::operator == ( AnimationOutput left, AnimationOutput right )
	{
		return AnimationOutput::Equals( left, right );
	}

	bool AnimationOutput::operator != ( AnimationOutput left, AnimationOutput right )
	{
		return !AnimationOutput::Equals( left, right );
	}

	int AnimationOutput::GetHashCode()
	{
		return Flags.GetHashCode() + Transformation.GetHashCode() + Scaling.GetHashCode()
			 + Translation.GetHashCode() + Rotation.GetHashCode();
	}

	bool AnimationOutput::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<AnimationOutput>( value ) );
	}

	bool AnimationOutput::Equals( AnimationOutput value )
	{
		return ( Flags == value.Flags && Transformation == value.Transformation && Scaling == value.Scaling
			 && Translation == value.Translation && Rotation == value.Rotation );
	}

	bool AnimationOutput::Equals( AnimationOutput% value1, AnimationOutput% value2 )
	{
		return ( value1.Flags == value2.Flags && value1.Transformation == value2.Transformation && value1.Scaling == value2.Scaling
			 && value1.Translation == value2.Translation && value1.Rotation == value2.Rotation );
	}
}
}