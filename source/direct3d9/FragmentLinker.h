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

#include "Shader.h"
#include "EffectHandle.h"
#include "FragmentDescription.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class VertexShader;
		ref class PixelShader;

		public ref class FragmentLinker : public ComObject
		{
			COMOBJECT(ID3DXFragmentLinker, FragmentLinker);

		public:
			FragmentLinker( SlimDX::Direct3D9::Device^ device, int cacheSize );
			static FragmentLinker^ FromPointer( System::IntPtr linker );

			property Device^ Device
			{
				SlimDX::Direct3D9::Device^ get();
			}

			static DataStream^ Gather( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );
			static DataStream^ Gather( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );

			static DataStream^ GatherFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );

			Result AddFragments( array<int>^ fragments );
			Result AddFragments( DataStream^ fragments );
			DataStream^ GetFragment( EffectHandle^ name );
			DataStream^ GetAllFragments();

			FragmentDescription GetFragmentDescription( EffectHandle^ name );
			EffectHandle^ GetFragmentHandle( int index );
			EffectHandle^ GetFragmentHandle( System::String^ name );

			void ClearCache();

			ShaderBytecode^ LinkShader( System::String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] System::String^% errors );
			VertexShader^ LinkVertexShader( System::String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] System::String^% errors );
			PixelShader^ LinkPixelShader( System::String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] System::String^% errors );

			property int FragmentCount
			{
				int get();
			}
		};
	}
}
