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

#include "../math/Math.h"
#include "../Direct3D/ColorValue.h"

using namespace System::Runtime::InteropServices;
using namespace SlimDX::Direct3D;

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		public enum class RegisterSet : Int32
		{
			Bool = D3DXRS_BOOL,
			Int4 = D3DXRS_INT4,
			Float4 = D3DXRS_FLOAT4,
			Sampler = D3DXRS_SAMPLER,
		};

		public value class ConstantTableDescription
		{
		public:
			property String^ Creator;
			property Version^ Version;
			property int Constants;
		};

		public value class ConstantDescription
		{
		public:
			property String^ Name;
			property RegisterSet RegisterSet;
			property int RegisterIndex;
			property int RegisterCount;
			property ParameterClass Class;
			property ParameterType Type;
			property int Rows;
			property int Columns;
			property int Elements;
			property int StructMembers;
			property int Bytes;
			//TODO: default value?

			void Initialize( const D3DXCONSTANT_DESC& desc );
		};

		ref class EffectHandle;
		
		public ref class ConstantTable : public DirectXObject<ID3DXConstantTable>
		{
		private:
			IDirect3DDevice9* m_Device;

		internal:
			ConstantTable( ID3DXConstantTable* table );

		public:
			ConstantTable( IntPtr table );
			ConstantTable( IDirect3DDevice9* device, ID3DXConstantTable* constantTable );
			~ConstantTable();
			
			EffectHandle^ GetConstant( EffectHandle^ handle, int index );
			EffectHandle^ GetConstant( EffectHandle^ handle, String^ name );
			EffectHandle^ GetConstantElement( EffectHandle^ handle, int index );
			ConstantDescription GetConstantDescription( EffectHandle^ handle );
			array<ConstantDescription>^ GetConstantDescriptionArray( EffectHandle^ handle );
			
			int GetSamplerIndex( EffectHandle^ sampler );

			property ConstantTableDescription Description
			{
				ConstantTableDescription get();
			}
			
			DataStream^ GetBuffer();
			int GetBufferSize();

			void SetDefaults();

			void SetValue( EffectHandle^ constant, bool value );
			void SetValue( EffectHandle^ constant, array<bool>^ value );
			void SetValue( EffectHandle^ constant, int value );
			void SetValue( EffectHandle^ constant, array<int>^ values );
			void SetValue( EffectHandle^ constant, float value );
			void SetValue( EffectHandle^ constant, array<float>^ values );
			void SetValue( EffectHandle^ constant, Vector4 value );
			void SetValue( EffectHandle^ constant, array<Vector4>^ values );
			void SetValue( EffectHandle^ constant, ColorValue value );
			void SetValue( EffectHandle^ constant, array<ColorValue>^ values );
			void SetValue( EffectHandle^ constant, Matrix value );
			void SetValue( EffectHandle^ constant, array<Matrix>^ values );
			void SetValueTranspose( EffectHandle^ constant, Matrix value );
			void SetValueTranspose( EffectHandle^ constant, array<Matrix>^ values );
		};
	}
}
