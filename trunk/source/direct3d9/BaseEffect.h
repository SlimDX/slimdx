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

#include "Device.h"
#include "EffectHandle.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		public value class EffectDescription : System::IEquatable<EffectDescription>
		{
		public:
			property System::String^ Creator;
            property int Parameters;
            property int Techniques;
            property int Functions;

			static bool operator == ( EffectDescription left, EffectDescription right );
			static bool operator != ( EffectDescription left, EffectDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( EffectDescription other );
			static bool Equals( EffectDescription% value1, EffectDescription% value2 );
		};

		public value class TechniqueDescription : System::IEquatable<TechniqueDescription>
		{
		public:
			property System::String^ Name;
            property int Passes;
            property int Annotations;

			static bool operator == ( TechniqueDescription left, TechniqueDescription right );
			static bool operator != ( TechniqueDescription left, TechniqueDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( TechniqueDescription other );
			static bool Equals( TechniqueDescription% value1, TechniqueDescription% value2 );
		};

		public value class FunctionDescription : System::IEquatable<FunctionDescription>
		{
		public:
			property System::String^ Name;
            property int Annotations;

			static bool operator == ( FunctionDescription left, FunctionDescription right );
			static bool operator != ( FunctionDescription left, FunctionDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( FunctionDescription other );
			static bool Equals( FunctionDescription% value1, FunctionDescription% value2 );
		};

		public value class PassDescription : System::IEquatable<PassDescription>
		{
		public:
			property System::String^ Name;
            property int Annotations;
            property System::IntPtr VertexShaderFunction;
            property System::IntPtr PixelShaderFunction;

			static bool operator == ( PassDescription left, PassDescription right );
			static bool operator != ( PassDescription left, PassDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( PassDescription other );
			static bool Equals( PassDescription% value1, PassDescription% value2 );
		};

		public value class ParameterDescription : System::IEquatable<ParameterDescription>
		{
		public:
			property System::String^ Name;
            property System::String^ Semantic;
            property ParameterClass Class;
            property ParameterType Type;
            property int Rows;
            property int Columns;
            property int Elements;
            property int Annotations;
            property int StructMembers;
            property ParameterFlags Flags;
            property int Bytes;

			static bool operator == ( ParameterDescription left, ParameterDescription right );
			static bool operator != ( ParameterDescription left, ParameterDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ParameterDescription other );
			static bool Equals( ParameterDescription% value1, ParameterDescription% value2 );
		};

		public ref class BaseEffect abstract : public ComObject
		{
			COMOBJECT_BASE(ID3DXBaseEffect);

		protected:
			BaseEffect() { }

		public:
			EffectHandle^ GetAnnotation( EffectHandle^ handle, int index );
			EffectHandle^ GetAnnotation( EffectHandle^ handle, System::String^ name );

			EffectHandle^ GetParameter( EffectHandle^ parameter, int index );
			EffectHandle^ GetParameter( EffectHandle^ parameter, System::String^ name );
			EffectHandle^ GetParameterBySemantic( EffectHandle^ parameter, System::String^ name );
			EffectHandle^ GetParameterElement( EffectHandle^ parameter, int index );
			ParameterDescription GetParameterDescription( EffectHandle^ parameter );

			EffectHandle^ GetFunction( int index );
			EffectHandle^ GetFunction( System::String^ name );
			FunctionDescription GetFunctionDescription( EffectHandle^ handle );

			EffectHandle^ GetTechnique( int index );
			EffectHandle^ GetTechnique( System::String^ name );
			TechniqueDescription GetTechniqueDescription( EffectHandle^ handle );

			EffectHandle^ GetPass( EffectHandle^ technique, int index );
			EffectHandle^ GetPass( EffectHandle^ technique, System::String^ name );
			PassDescription GetPassDescription( EffectHandle^ handle );

			PixelShader^ GetPixelShader( EffectHandle^ parameter );
			VertexShader^ GetVertexShader( EffectHandle^ parameter );

			Result SetValue( EffectHandle^ parameter, bool value );
			Result SetValue( EffectHandle^ parameter, array<bool>^ values );
			Result SetValue( EffectHandle^ parameter, int value );
			Result SetValue( EffectHandle^ parameter, array<int>^ values );
			Result SetValue( EffectHandle^ parameter, float value );
			Result SetValue( EffectHandle^ parameter, array<float>^ values );
			Result SetValue( EffectHandle^ parameter, Vector4 value );
			Result SetValue( EffectHandle^ parameter, array<Vector4>^ values );
			Result SetValue( EffectHandle^ parameter, Color4 value );
			Result SetValue( EffectHandle^ parameter, array<Color4>^ values );
			Result SetValue( EffectHandle^ parameter, Matrix value );
			Result SetValue( EffectHandle^ parameter, array<Matrix>^ values );
			Result SetValue( EffectHandle^ parameter, BaseTexture^ value );
			Result SetValue( EffectHandle^ parameter, System::String^ value );
			Result SetValueTranspose( EffectHandle^ parameter, Matrix value );
			Result SetValueTranspose( EffectHandle^ parameter, array<Matrix>^ values );

			bool GetBool( EffectHandle^ parameter );
			array<bool>^ GetBoolArray( EffectHandle^ parameter, int count );

			int GetInt( EffectHandle^ parameter );
			array<int>^ GetIntArray( EffectHandle^ parameter, int count );

			float GetFloat( EffectHandle^ parameter );
			array<float>^ GetFloatArray( EffectHandle^ parameter, int count );

			Vector4 GetVector( EffectHandle^ parameter );
			array<Vector4>^ GetVectorArray( EffectHandle^ parameter, int count );

			Color4 GetColor( EffectHandle^ parameter );
			array<Color4>^ GetColorArray( EffectHandle^ parameter, int count );

			Matrix GetMatrix( EffectHandle^ parameter );
			array<Matrix>^ GetMatrixArray( EffectHandle^ parameter, int count );

			Matrix GetMatrixTranspose( EffectHandle^ parameter );
			array<Matrix>^ GetMatrixTransposeArray( EffectHandle^ parameter, int count );

			BaseTexture^ GetTexture( EffectHandle^ parameter );

			System::String^ GetString( EffectHandle^ parameter );
			DataStream^ GetValue( EffectHandle^ parameter, int bytes );

			property EffectDescription Description
			{
				EffectDescription get();
			}
		};
   }
}
