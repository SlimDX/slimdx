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

#include "../math/Color4.h"
#include "../math/Matrix.h"
#include "../math/Vector4.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		public enum class RegisterSet : System::Int32
		{
			Bool = D3DXRS_BOOL,
			Int4 = D3DXRS_INT4,
			Float4 = D3DXRS_FLOAT4,
			Sampler = D3DXRS_SAMPLER,
		};

		public value class ConstantTableDescription
		{
		public:
			property System::String^ Creator;
			property System::Version^ Version;
			property int Constants;
		};

		public value class ConstantDescription
		{
		internal:
			void Initialize( const D3DXCONSTANT_DESC& description );

		public:
			property System::String^ Name;
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
		};

		ref class EffectHandle;
		
		public ref class ConstantTable : public ComObject
		{
			COMOBJECT(ID3DXConstantTable);

		private:
			IDirect3DDevice9* m_Device;

		internal:
			ConstantTable( ID3DXConstantTable* table );
			ConstantTable( IDirect3DDevice9* device, ID3DXConstantTable* constantTable );

		public:
			ConstantTable( System::IntPtr table );
			~ConstantTable();
			
			EffectHandle^ GetConstant( EffectHandle^ handle, int index );
			EffectHandle^ GetConstant( EffectHandle^ handle, System::String^ name );
			EffectHandle^ GetConstantElement( EffectHandle^ handle, int index );
			ConstantDescription GetConstantDescription( EffectHandle^ handle );
			array<ConstantDescription>^ GetConstantDescriptionArray( EffectHandle^ handle );
			
			int GetSamplerIndex( EffectHandle^ sampler );

			DataStream^ GetBuffer();
			Result SetDefaults();

			Result SetValue( EffectHandle^ constant, bool value );
			Result SetValue( EffectHandle^ constant, array<bool>^ value );
			Result SetValue( EffectHandle^ constant, int value );
			Result SetValue( EffectHandle^ constant, array<int>^ values );
			Result SetValue( EffectHandle^ constant, float value );
			Result SetValue( EffectHandle^ constant, array<float>^ values );
			Result SetValue( EffectHandle^ constant, Vector4 value );
			Result SetValue( EffectHandle^ constant, array<Vector4>^ values );
			Result SetValue( EffectHandle^ constant, Color4 value );
			Result SetValue( EffectHandle^ constant, array<Color4>^ values );
			Result SetValue( EffectHandle^ constant, Matrix value );
			Result SetValue( EffectHandle^ constant, array<Matrix>^ values );
			Result SetValueTranspose( EffectHandle^ constant, Matrix value );
			Result SetValueTranspose( EffectHandle^ constant, array<Matrix>^ values );

			property int BufferSize
			{
				int get() { return InternalPointer->GetBufferSize(); }
			}

			property ConstantTableDescription Description
			{
				ConstantTableDescription get();
			}
		};
	}
}
