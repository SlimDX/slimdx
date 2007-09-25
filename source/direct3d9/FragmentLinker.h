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

#include "Buffer.h"
#include "Shader.h"
#include "EffectHandle.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class VertexShader;
		ref class PixelShader;

		public value class FragmentDescription
		{
		public:
			property String^ Name;
            property int Target;
		};

		public ref class ShaderFragments : public BufferWrapper
		{
		public:
			ShaderFragments( ID3DXBuffer* buffer ) : BufferWrapper( buffer )
			{ }

			ShaderFragments( int size ) : BufferWrapper( size )
			{ }
		};

		public ref class FragmentLinker : public DirectXObject<ID3DXFragmentLinker>
		{
		public:
			FragmentLinker( ID3DXFragmentLinker* linker );
			FragmentLinker( Device^ device, int cacheSize );
			~FragmentLinker() { Destruct(); }

			static ShaderFragments^ Gather( array<Byte>^ sourceData, array<Macro>^ defines,
				Include^ includeFile, ShaderFlags flags, [Out] String^% errors );
			static ShaderFragments^ Gather( String^ sourceData, array<Macro>^ defines,
				Include^ includeFile, ShaderFlags flags, [Out] String^% errors );

			static ShaderFragments^ GatherFromFile( String^ fileName, array<Macro>^ defines,
				Include^ includeFile, ShaderFlags flags, [Out] String^% errors );

			void AddFragments( array<int>^ fragments );
			void AddFragments( DataStream^ fragments );
			ShaderFragments^ GetFragment( EffectHandle^ name );
			ShaderFragments^ GetAllFragments();
			Device^ GetDevice();

			FragmentDescription GetFragmentDescription( EffectHandle^ name );
			EffectHandle^ GetFragmentHandle( int index );
			EffectHandle^ GetFragmentHandle( String^ name );

			void ClearCache();
			ShaderBytecode^ LinkShader( String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] String^% errors );
			VertexShader^ LinkVertexShader( String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] String^% errors );
			PixelShader^ LinkPixelShader( String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] String^% errors );

			property int FragmentCount
			{
				int get();
			}
		};
	}
}
