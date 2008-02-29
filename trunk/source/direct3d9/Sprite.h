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

#include "IResettable.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class Texture;

		public ref class Sprite : public ComObject, IResettable
		{
			COMOBJECT(ID3DXSprite, Sprite);

		public:
			Sprite( Device^ device );
			static Sprite^ FromPointer( System::IntPtr pointer );

			Result Begin( SpriteFlags flags );
			Result End();
			Result Flush();

			virtual Result OnLostDevice();
			virtual Result OnResetDevice();

			property SlimDX::Direct3D9::Device^ Device
			{
				SlimDX::Direct3D9::Device^ get();
			}

			property Matrix Transform
			{
				Matrix get();
				void set( Matrix value );
			}

			Result SetWorldViewLH( Matrix world, Matrix view );
			Result SetWorldViewRH( Matrix world, Matrix view );

			Result Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Vector3 center, Vector3 position, Color4 color );
			Result Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Color4 color );
			Result Draw( Texture^ texture, Vector3 center, Vector3 position, Color4 color );
			Result Draw( Texture^ texture, Color4 color );
		};
	}
}
