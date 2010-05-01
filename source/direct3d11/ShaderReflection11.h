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

#include "ConstantBuffer11.h"
#include "ShaderDescription11.h"
#include "ShaderParameterDescription11.h"
#include "InputBindingDescription11.h"

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class ShaderBytecode;

		public ref class ShaderReflection : ComObject
		{
			COMOBJECT(ID3D11ShaderReflection, ShaderReflection);

		private:
			ShaderDescription^ description;
			
		public:
			ShaderReflection( ShaderBytecode^ bytecode );

			ConstantBuffer^ GetConstantBuffer( int index );
			ConstantBuffer^ GetConstantBuffer( System::String^ name );

			ShaderParameterDescription GetInputParameterDescription( int index );
			ShaderParameterDescription GetOutputParameterDescription( int index );
			ShaderParameterDescription GetPatchConstantParameterDescription( int index );

			InputBindingDescription GetResourceBindingDescription( int index );
			InputBindingDescription GetResourceBindingDescription( System::String^ name );

			property FeatureLevel MinimumFeatureLevel
			{
				FeatureLevel get();
			}

			property InputPrimitive GeometryShaderInputPrimitive
			{
				InputPrimitive get();
			}

			property ShaderDescription^ Description
			{
				ShaderDescription^ get() { return description; }
			}
			
			/// <summary>
			/// Gets the number of bitwise instructions.
			/// </summary>
			property int BitwiseInstructionCount 
			{
				int get();
			}
			
			/// <summary>
			/// Gets the number of conversion instructions.
			/// </summary>
			property int ConversionInstructionCount
			{
				int get();
			}
			
			/// <summary>
			/// Gets the number of move instructions.
			/// </summary>
			property int MoveInstructionCount
			{
				int get();
			}
			
			/// <summary>
			/// Gets the number of conditional move instructions.
			/// </summary>
			property int ConditionalMoveInstructionCount
			{
				int get();
			}
			
			/// <summary>
			/// Gets the number of interface slots.
			/// </summary>
			property int InterfaceSlotCount
			{
				int get();
			}
			
			/// <summary>
			/// Gets a value indicating whether the shader is a sample frequency shader.
			/// </summary>
			property bool IsSampleFrequencyShader
			{
				bool get();
			}
		};
	}
}