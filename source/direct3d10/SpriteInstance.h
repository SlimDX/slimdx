/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System::Runtime::InteropServices;

#include "../math/Math.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class ShaderResourceView;

		/// <remarks>
		/// Describes instance data for a single sprite rendered by the
		/// <see cref="SlimDX.Direct3D10.Sprite"/> interface.
		/// </remarks>
		/// <unmanaged counterpart="D3DX10_SPRITE" complete="yes"/>
		public ref class SpriteInstance
		{
			Matrix transform;
			Vector2 textureCoordinates;
			Vector2 textureDimensions;
			ColorValue color;
			ShaderResourceView^ texture;
			int textureIndex;
		
		internal:
			void ToNativeObject( D3DX10_SPRITE& object );

		public:
			property Matrix Transform
			{
				Matrix get() { return (transform); }
				void set( Matrix value ) { transform = value; }
			}

			property Vector2 TextureCoordinates
			{
				Vector2 get() { return textureCoordinates; }
				void set( Vector2 value ) { textureCoordinates = value; }
			}

			property Vector2 TextureDimensions
			{
				Vector2 get() { return textureDimensions; }
				void set( Vector2 value ) { textureDimensions = value; }
			}
			
			property ColorValue Color
			{
				ColorValue get() { return color; }
				void set( ColorValue value ) { color = value; }
			}

			property ShaderResourceView^ Texture
			{
				ShaderResourceView^ get() { return texture; }
				void set( ShaderResourceView^ value ) { texture = value; }
			}

			property int TextureIndex
			{
				int get() { return textureIndex; }
				void set( int value ) { textureIndex = value; }
			}

			SpriteInstance( ShaderResourceView^ texture, Vector2 coordinates, Vector2 dimensions );
		};
	}
}
