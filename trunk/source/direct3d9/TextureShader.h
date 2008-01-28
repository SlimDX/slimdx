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
		public ref class TextureShader : public ComObject
		{
			COMOBJECT(ID3DXTextureShader);

		internal:
			TextureShader( ID3DXTextureShader* pointer );

		public:
			TextureShader( IntPtr pointer );
			TextureShader( DataStream^ stream );
			virtual ~TextureShader() { Destruct(); }

			EffectHandle^ GetConstant( EffectHandle^ parent, int index );
			EffectHandle^ GetConstant( EffectHandle^ parent, String^ name );
			EffectHandle^ GetConstantElement( EffectHandle^ handle, int index );

			ConstantDescription GetConstantDescription( EffectHandle^ handle );
			array<ConstantDescription>^ GetConstantDescriptionArray( EffectHandle^ handle );

			DataStream^ GetConstantBuffer();
			DataStream^ GetFunctionStream();

			void SetValue( EffectHandle^ parameter, bool value );
			void SetValue( EffectHandle^ parameter, array<bool>^ values );
			void SetValue( EffectHandle^ parameter, int value );
			void SetValue( EffectHandle^ parameter, array<int>^ values );
			void SetValue( EffectHandle^ parameter, float value );
			void SetValue( EffectHandle^ parameter, array<float>^ values );
			void SetValue( EffectHandle^ parameter, Vector4 value );
			void SetValue( EffectHandle^ parameter, array<Vector4>^ values );
			void SetValue( EffectHandle^ parameter, ColorValue value );
			void SetValue( EffectHandle^ parameter, array<ColorValue>^ values );
			void SetValue( EffectHandle^ parameter, Matrix value );
			void SetValue( EffectHandle^ parameter, array<Matrix>^ values );
			void SetValueTranspose( EffectHandle^ parameter, Matrix value );
			void SetValueTranspose( EffectHandle^ parameter, array<Matrix>^ values );

			void SetDefaults();

			property ConstantTableDescription Description
			{
				ConstantTableDescription get();
			}
		};
	}
}