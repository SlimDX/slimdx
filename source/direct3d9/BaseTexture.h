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

#include "../DataStream.h"
#include "Enums.h"
#include "Resource.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class BaseTexture abstract : public Resource
		{
		protected:
			BaseTexture() { }

		internal:
			property IDirect3DBaseTexture9* BaseTexturePointer
			{
				IDirect3DBaseTexture9* get() { return static_cast<IDirect3DBaseTexture9*>( InternalPointer ); }
			}
		
		public:
			virtual ~BaseTexture() { }

			property TextureFilter AutoMipGenerationFilter
			{
				TextureFilter get() { return ( TextureFilter ) BaseTexturePointer->GetAutoGenFilterType(); }
				void set(TextureFilter value) { BaseTexturePointer->SetAutoGenFilterType( (D3DTEXTUREFILTERTYPE) value ); }
			}
			
			property int LevelCount
			{
				int get() { return BaseTexturePointer->GetLevelCount(); }
			}
			
			property int LevelOfDetail
			{
				int get() { return BaseTexturePointer->GetLOD(); }
				void set(int value) { BaseTexturePointer->SetLOD( value ); }
			}

			Result FilterTexture( int sourceLevel, Filter filter, array<PaletteEntry>^ palette );
			Result FilterTexture( int sourceLevel, Filter filter );
			
			void GenerateMipSublevels();

			static DataStream^ ToStream( BaseTexture^ texture, ImageFileFormat format );
			static DataStream^ ToStream( BaseTexture^ texture, ImageFileFormat format, array<PaletteEntry>^ palette );

			static Result ToFile( BaseTexture^ texture, System::String^ fileName, ImageFileFormat format );
			static Result ToFile( BaseTexture^ texture, System::String^ fileName, ImageFileFormat format, array<PaletteEntry>^ palette );
		};
	}
}
