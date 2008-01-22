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

using namespace System::Drawing;

#include "../SlimDXObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		ref class Sprite;
		
		/// <remarks>
		/// An interface for performing text rendering.
		/// </remarks>
		/// <unmanaged counterpart="ID3DX10Font" complete="no"/>
		public ref class Font : public SlimDXObject
		{
			DXOBJECT(ID3DX10Font);

		internal:
			Font( ID3DX10Font* font );

		public:
			Font( IntPtr pointer );
			Font( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool isItalic,
				FontCharacterSet characterSet, FontPrecision outputPrecision, FontQuality quality,
				FontPitchAndFamily pitchAndFamily, String^ faceName );
			~Font() { Destruct(); }

			int Draw( Sprite^ sprite, String^ text, Drawing::Rectangle rect, FontDrawFlags flags, int color );

			void PreloadCharacters( int first, int last );
			void PreloadGlyphs( int first, int last );
			void PreloadText( String^ text );
		};
	}
}
