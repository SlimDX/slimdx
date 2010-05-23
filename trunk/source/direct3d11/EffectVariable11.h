/*
* Copyright (c) 2007-2010 SlimDX Group
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

#include "../ComObject.h"

#include "Enums11.h"

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class EffectConstantBuffer;
		ref class EffectMatrixVariable;
		ref class EffectResourceVariable;
		ref class EffectShaderVariable;
		ref class EffectScalarVariable;
		ref class EffectVectorVariable;
		ref class EffectStringVariable;
		ref class EffectUnorderedAccessViewVariable;
		value class EffectVariableDescription;
		ref class EffectType;
		
		/// <summary>
		/// Defines a base class for all effect variables.
		/// </summary>
		/// <unmanaged>ID3DX11EffectVariable</unmanaged>
		public ref class EffectVariable
		{
		private:
			ID3DX11EffectVariable* m_Pointer;
			
		internal:
			EffectVariable( ID3DX11EffectVariable* pointer );

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="EffectVariable"/> class.
			/// </summary>
			/// <param name="pointer">A pointer to the unmanaged interface.</param>
			EffectVariable( System::IntPtr pointer );

			/// <summary>
			/// Gets the effect variable's description.
			/// </summary>
			property EffectVariableDescription Description
			{
				EffectVariableDescription get();
			}
			
			/// <summary>
			/// Indicates whether the data type matches the data stored after casting to a specific interface.
			/// </summary>
			property bool IsValid
			{
				bool get();
			}

			/// <summary>
			/// Gets the parent constant buffer for this variable.
			/// </summary>
			property EffectConstantBuffer^ ParentConstantBuffer
			{
				EffectConstantBuffer^ get();
			}

			/// <summary>
			/// Get an annotation by index.
			/// </summary>
			/// <param name="index">The zero-based index of the annotation to retrieve.</param>
			/// <returns>The annotation at the specified index.</returns>
			EffectVariable^ GetAnnotationByIndex( int index );

			/// <summary>
			/// Get an annotation by name.
			/// </summary>
			/// <param name="name">The name of the annotation to retrieve.</param>
			/// <returns>The annotation with the given name.</returns>
			EffectVariable^ GetAnnotationByName( System::String^ name );
			
			/// <summary>
			/// Gets an element of an array variable.
			/// </summary>
			/// <param name="index">The zero-based index of the element to retrieve.</param>
			/// <returns>The element at the specified index in the array.</returns>
			EffectVariable^ GetElement( int index );
			
			/// <summary>
			/// Get a structure member by index.
			/// </summary>
			/// <param name="index">The zero-based index of the structure member to retrieve.</param>
			/// <returns>The structure member at the specified index.</returns>
			EffectVariable^ GetMemberByIndex( int index );

			/// <summary>
			/// Get a structure member by name.
			/// </summary>
			/// <param name="name">The name of the structure member to retrieve.</param>
			/// <returns>The structure member with the given name.</returns>
			EffectVariable^ GetMemberByName( System::String^ name );

			/// <summary>
			/// Get a structure member by semantic.
			/// </summary>
			/// <param name="name">The semantic of the structure member to retrieve.</param>
			/// <returns>The structure member with the given semantic.</returns>
			EffectVariable^ GetMemberBySemantic( System::String^ name );
			
			EffectConstantBuffer^ AsConstantBuffer();
			EffectMatrixVariable^ AsMatrix();
			EffectResourceVariable^ AsResource();
			EffectShaderVariable^ AsShader();
			EffectScalarVariable^ AsScalar();
			EffectVectorVariable^ AsVector();
			EffectStringVariable^ AsString();
			EffectUnorderedAccessViewVariable^ AsUnorderedAccessView();

			/// <summary>
			/// Gets information about the variable type.
			/// </summary>
			/// <returns>A type descriptor containing information about the variable type.</returns>
			EffectType^ GetVariableType();

			/// <summary>
			/// Sets the value of the variable using raw bytes.
			/// </summary>
			/// <param name="count">The number of bytes to set.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result SetRawValue(DataStream^ data, int count);

			/// <summary>
			/// Gets the value of the variable in raw bytes.
			/// </summary>
			/// <param name="count">The number of bytes to retrieve.</param>
			/// <returns>The raw data representing the value of the variable.</returns>
			DataStream^ GetRawValue(int count);
		};
	}
};