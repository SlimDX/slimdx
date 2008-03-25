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

		/// <summary>Provides a set of methods that simplify the process of drawing sprites.</summary>
		/// <unmanaged>ID3DXSprite</unmanaged>
		public ref class Sprite : public ComObject, IResettable
		{
			COMOBJECT(ID3DXSprite, Sprite);

		public:
			/// <summary>Initializes a new instance of a sprite object.</summary>
			/// <param name="device">The device to use when creating the new sprite object.</param>
			/// <unmanaged>D3DXCreateSprite</unmanaged>
			Sprite( Device^ device );

			/// <summary>Creates a new instance of a sprite object from a user pointer.</summary>
			/// <param name="pointer">The native user pointer to use for the sprite object. This should
			/// be a pointer to an ID3DXSprite.</param>
			/// <returns>The newly created sprite object.</returns>
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
