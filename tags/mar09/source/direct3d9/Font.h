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
#pragma once

#include "Enums.h"
#include "IResettable.h"

#include "FontDescription.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		/// <summary>Encapsulates the textures and resources needed to render a specific font on a specific device.</summary>
		/// <unmanaged>ID3DXFont</unmanaged>
		public ref class Font : public ComObject, IResettable
		{
			COMOBJECT(ID3DXFont, Font);

		internal:
			void Build( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic, CharacterSet characterSet, Precision outputPrecision, FontQuality quality, PitchAndFamily pitchAndFamily, System::String^ faceName );

		public:
			Font( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic, CharacterSet characterSet, Precision outputPrecision, FontQuality quality, PitchAndFamily pitchAndFamily, System::String^ faceName );
			Font( Device^ device, System::Drawing::Font^ font );

			int DrawString( Sprite^ sprite, System::String^ text, System::Drawing::Rectangle rectangle, DrawTextFormat format, Color4 color );
			int DrawString( Sprite^ sprite, System::String^ text, System::Drawing::Rectangle rectangle, DrawTextFormat format, int color );
			int DrawString( Sprite^ sprite, System::String^ text, int x, int y, Color4 color );
			int DrawString( Sprite^ sprite, System::String^ text, int x, int y, int color );

			System::Drawing::Rectangle MeasureString( Sprite^ sprite, System::String^ text, DrawTextFormat format );
			int MeasureString( Sprite^ sprite, System::String^ text, DrawTextFormat format, System::Drawing::Rectangle% rectangle );

			Result PreloadCharacters( int first, int last );
			Result PreloadGlyphs( int first, int last );
			Result PreloadText( System::String^ text );

			virtual Result OnLostDevice();
			virtual Result OnResetDevice();

			property FontDescription Description
			{
				FontDescription get();
			}

			property System::IntPtr DeviceContext
			{
				System::IntPtr get();
			}
		};
	}
}
