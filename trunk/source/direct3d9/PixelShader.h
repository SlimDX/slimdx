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

#include "ConstantTable.h"

namespace SlimDX
{
	namespace Direct3D9
	{	
		public ref class PixelShader : public ComObject
		{
			COMOBJECT(IDirect3DPixelShader9, PixelShader);

		private:
			ConstantTable^ m_ConstantTable;

			PixelShader( IDirect3DPixelShader9* pixelShader, ID3DXConstantTable* constantTable );

		internal:
			static PixelShader^ FromPointer( IDirect3DPixelShader9* pixelShader, ID3DXConstantTable* constantTable );

		public:
			static PixelShader^ FromPointer( System::IntPtr pointer );

			virtual ~PixelShader() { delete m_ConstantTable; }

			literal int MaxDynamicFlowControlDepth = D3DPS20_MAX_DYNAMICFLOWCONTROLDEPTH;
			literal int MinDynamicFlowControlDepth = D3DPS20_MIN_DYNAMICFLOWCONTROLDEPTH;
			literal int MaxTemps = D3DPS20_MAX_NUMTEMPS;
			literal int MinTemps = D3DPS20_MIN_NUMTEMPS;
			literal int MaxStaticFlowControlDepth = D3DPS20_MAX_STATICFLOWCONTROLDEPTH;
			literal int MinStaticFlowControlDepth = D3DPS20_MIN_STATICFLOWCONTROLDEPTH;
			literal int MaxInstructionSlots = D3DPS20_MAX_NUMINSTRUCTIONSLOTS;
			literal int MinInstructionSlots = D3DPS20_MIN_NUMINSTRUCTIONSLOTS;

			property SlimDX::Direct3D9::Device^ Device
			{
				SlimDX::Direct3D9::Device^ get();
			}
			
			Result RetrieveConstantTable();
			property ConstantTable^ Constants
			{
				ConstantTable^ get() { return m_ConstantTable; }
			}
			
			static PixelShader^ FromString( SlimDX::Direct3D9::Device^ device, System::String^ sourceCode, System::String^ entryPoint, System::String^ profile, ShaderFlags flags, [Out] System::String^ %compilationErrors );
		};
	}
}
