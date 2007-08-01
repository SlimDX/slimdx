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

using namespace System::IO;
using namespace System::Runtime::InteropServices;

#include "../math/Math.h"
#include "Device.h"
#include "EffectHandle.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		//description structures for various things
		public value class EffectDescription
		{
		public:
			String^ Creator;
			int Parameters;
			int Techniques;
			int Functions;
		};

		public value class TechniqueDescription
		{
		public:
			String^ Name;
			int Passes;
			int Annotations;
		};

		public value class FunctionDescription
		{
		public:
			String^ Name;
			int Annotations;
		};

		public value class PassDescription
		{
		public:
			String^ Name;
			int Annotations;
			//TODO: Convert these to something else?
			IntPtr VertexShaderFunction;
			IntPtr PixelShaderFunction;
		};

		public value class ParameterDescription
		{
		public:
			String^ Name;
			String^ Semantic;
			ParameterClass Class;
			ParameterType Type;
			int Rows;
			int Columns;
			int Elements;
			int Annotations;
			int StructMembers;
			ParameterFlags Flags;
			int Bytes;
		};

		public ref class BaseEffect abstract : public DirectXObject<ID3DXBaseEffect>
		{
		protected:
			BaseEffect() { }
			BaseEffect( ID3DXBaseEffect* pointer ) : DirectXObject( pointer )
			{ }

		public:
			EffectHandle^ GetAnnotation( EffectHandle^ handle, int index );
			EffectHandle^ GetAnnotation( EffectHandle^ handle, String^ name );

			EffectHandle^ GetParameter( EffectHandle^ parameter, int index );
			EffectHandle^ GetParameter( EffectHandle^ parameter, String^ name );
			EffectHandle^ GetParameterBySemantic( EffectHandle^ parameter, String^ name );
			EffectHandle^ GetParameterElement( EffectHandle^ parameter, int index );
			ParameterDescription GetParameterDescription( EffectHandle^ parameter );

			EffectHandle^ GetFunction( int index );
			EffectHandle^ GetFunction( String^ name );
			FunctionDescription GetFunctionDescription( EffectHandle^ handle );

			EffectHandle^ GetTechnique( int index );
			EffectHandle^ GetTechnique( String^ name );
			TechniqueDescription GetTechniqueDescription( EffectHandle^ handle );

			EffectHandle^ GetPass( EffectHandle^ technique, int index );
			EffectHandle^ GetPass( EffectHandle^ technique, String^ name );
			PassDescription GetPassDescription( EffectHandle^ handle );

			property EffectDescription Description
			{
				EffectDescription get();
			}

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
			void SetValue( EffectHandle^ param, BaseTexture^ value );
			void SetValue( EffectHandle^ param, String^ value );
			void SetValueTranspose( EffectHandle^ param, Matrix value );
			void SetValueTranspose( EffectHandle^ param, array<Matrix>^ values );

			bool GetBool( EffectHandle^ param );
			array<bool>^ GetBoolArray( EffectHandle^ param, int count );
			int GetInt( EffectHandle^ param );
			array<int>^ GetIntArray( EffectHandle^ param, int count );
			float GetFloat( EffectHandle^ param );
			array<float>^ GetFloatArray( EffectHandle^ param, int count );
			Vector4 GetVector( EffectHandle^ param );
			array<Vector4>^ GetVectorArray( EffectHandle^ param, int count );
			ColorValue GetColor( EffectHandle^ param );
			array<ColorValue>^ GetColorArray( EffectHandle^ param, int count );
			Matrix GetMatrix( EffectHandle^ param );
			array<Matrix>^ GetMatrixArray( EffectHandle^ param, int count );
			Matrix GetMatrixTranspose( EffectHandle^ param );
			array<Matrix>^ GetMatrixTransposeArray( EffectHandle^ param, int count );
			BaseTexture^ GetTexture( EffectHandle^ param );

			String^ GetString( EffectHandle^ param );
			DataStream^ GetValue( EffectHandle^ param, int bytes );
		};
   }
}