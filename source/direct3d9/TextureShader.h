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

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class TextureShader : public DirectXObject<ID3DXTextureShader>
		{
		internal:
			TextureShader( ID3DXTextureShader* pointer );

		public:
			TextureShader( IntPtr pointer );
			TextureShader( DataStream^ stream );
			virtual ~TextureShader() { Destruct(); }
			DXOBJECT_FUNCTIONS;

			EffectHandle^ GetConstant( EffectHandle^ parent, int index );
			EffectHandle^ GetConstant( EffectHandle^ parent, String^ name );
			EffectHandle^ GetConstantElement( EffectHandle^ handle, int index );

			ConstantDescription GetConstantDescription( EffectHandle^ handle );
			array<ConstantDescription>^ GetConstantDescriptionArray( EffectHandle^ handle );

			DataStream^ GetConstantBuffer();
			DataStream^ GetFunctionStream();

			void SetValue( EffectHandle^ param, bool value );
			void SetValue( EffectHandle^ param, array<bool>^ values );
			void SetValue( EffectHandle^ param, int value );
			void SetValue( EffectHandle^ param, array<int>^ values );
			void SetValue( EffectHandle^ param, float value );
			void SetValue( EffectHandle^ param, array<float>^ values );
			void SetValue( EffectHandle^ param, Vector4 value );
			void SetValue( EffectHandle^ param, array<Vector4>^ values );
			void SetValue( EffectHandle^ param, ColorValue value );
			void SetValue( EffectHandle^ param, array<ColorValue>^ values );
			void SetValue( EffectHandle^ param, Matrix value );
			void SetValue( EffectHandle^ param, array<Matrix>^ values );
			void SetValueTranspose( EffectHandle^ param, Matrix value );
			void SetValueTranspose( EffectHandle^ param, array<Matrix>^ values );

			void SetDefaults();

			property ConstantTableDescription Description
			{
				ConstantTableDescription get();
			}
		};
	}
}