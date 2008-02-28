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

#include "../math/Quaternion.h"
#include "../math/Matrix.h"
#include "../math/Vector4.h"

#include "CallbackKey.h"
#include "Enums.h"
#include "AnimationOutput.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class Frame;

		public ref class AnimationSet : public ComObject
		{
			COMOBJECT(ID3DXAnimationSet, AnimationSet);

		protected:
			AnimationSet() { }

		public:
			static AnimationSet^ FromPointer( System::IntPtr pointer );

			int GetAnimationIndex( System::String^ name );
			System::String^ GetAnimationName( int index );
			System::IntPtr GetCallback( double position, CallbackSearchFlags flags, [Out] double% callbackPosition );
			AnimationOutput^ GetTransformation( double periodicPosition, int animation );
			double GetPeriodicPosition( double position );

			property System::String^ Name { System::String^ get(); }
			property int AnimationCount { int get(); }
			property double Period { double get(); }
		};
	}
}