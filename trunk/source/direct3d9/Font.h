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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public value class FontDescription : System::IEquatable<FontDescription>
		{
		public:
			property int Height;
            property int Width;
            property FontWeight Weight;
            property int MipLevels;
            property bool Italic;
            property CharacterSet CharSet;
            property Precision OutputPrecision;
            property FontQuality Quality;
            property PitchAndFamily PitchAndFamily;
            property System::String^ FaceName;

			static bool operator == ( FontDescription left, FontDescription right );
			static bool operator != ( FontDescription left, FontDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( FontDescription other );
			static bool Equals( FontDescription% value1, FontDescription% value2 );
		};

		public ref class Font : public ComObject
		{
			COMOBJECT(ID3DXFont);

		internal:
			/* Unused for now.
			Font( ID3DXFont* font );
			*/

			void Build( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic, CharacterSet characterSet, Precision outputPrecision, FontQuality quality, PitchAndFamily pitchAndFamily, System::String^ faceName );

		public:
			Font( System::IntPtr font );
			Font( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic, CharacterSet characterSet, Precision outputPrecision, FontQuality quality, PitchAndFamily pitchAndFamily, System::String^ faceName );
			Font( Device^ device, System::Drawing::Font^ font );
			~Font() { Destruct(); }

			int DrawString( Sprite^ sprite, System::String^ text, System::Drawing::Rectangle rectangle, DrawTextFormat format, Color4 color );
			int DrawString( Sprite^ sprite, System::String^ text, int x, int y, Color4 color );

			System::Drawing::Rectangle MeasureString( Sprite^ sprite, System::String^ text, DrawTextFormat format );

			Result PreloadCharacters( int first, int last );
			Result PreloadGlyphs( int first, int last );
			Result PreloadText( System::String^ text );

			Result OnLostDevice();
			Result OnResetDevice();

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
