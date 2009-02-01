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

#include "../math/Color4.h"
#include "../math/Matrix.h"
#include "../math/Vector4.h"

#include "ConstantTableDescription.h"
#include "ConstantDescription.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		ref class EffectHandle;
		ref class Device;
		
		/// <summary>
		/// Used to access the constant table. This table contains the variables that are used by high-level language shaders and effects.
		/// </summary>
		/// <unmanaged>ID3DXConstantTable</unmanaged>
		public ref class ConstantTable : public ComObject
		{
			COMOBJECT(ID3DXConstantTable, ConstantTable);

		public:
			EffectHandle^ GetConstant( EffectHandle^ handle, int index );
			EffectHandle^ GetConstant( EffectHandle^ handle, System::String^ name );
			EffectHandle^ GetConstantElement( EffectHandle^ handle, int index );
			ConstantDescription GetConstantDescription( EffectHandle^ handle );
			array<ConstantDescription>^ GetConstantDescriptionArray( EffectHandle^ handle );
			
			int GetSamplerIndex( EffectHandle^ sampler );

			DataStream^ GetBuffer();
			Result SetDefaults( Device^ device );

			Result SetValue( Device^ device, EffectHandle^ constant, bool value );
			Result SetValue( Device^ device, EffectHandle^ constant, array<bool>^ value );
			Result SetValue( Device^ device, EffectHandle^ constant, int value );
			Result SetValue( Device^ device, EffectHandle^ constant, array<int>^ values );
			Result SetValue( Device^ device, EffectHandle^ constant, float value );
			Result SetValue( Device^ device, EffectHandle^ constant, array<float>^ values );
			Result SetValue( Device^ device, EffectHandle^ constant, Vector4 value );
			Result SetValue( Device^ device, EffectHandle^ constant, array<Vector4>^ values );
			Result SetValue( Device^ device, EffectHandle^ constant, Color4 value );
			Result SetValue( Device^ device, EffectHandle^ constant, array<Color4>^ values );
			Result SetValue( Device^ device, EffectHandle^ constant, Matrix value );
			Result SetValue( Device^ device, EffectHandle^ constant, array<Matrix>^ values );
			Result SetValueTranspose( Device^ device, EffectHandle^ constant, Matrix value );
			Result SetValueTranspose( Device^ device, EffectHandle^ constant, array<Matrix>^ values );

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
