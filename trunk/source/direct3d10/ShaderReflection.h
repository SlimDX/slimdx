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

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

#include "../ComObject.h"

#include "Enums.h"
#include "Resource.h"

#include "ShaderParameterDescription.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class ShaderBytecode;
		
		public ref class ShaderReflection : public ComObject
		{
			COMOBJECT(ID3D10ShaderReflection);

		private:
			int version;
			String^ creator;
			int flags; //TODO: No idea what values this can take...?
			int constantBuffers;
			int boundResources;
			int inputParameters;
			int outputParameters;
			int instructionCount;
			int tempRegisterCount;
			int tempArrayCount;
			int defCount;
			int dclCount;
			int textureNormalInstructions;
			int textureLoadInstructions;
			int textureCompInstructions;
			int textureBiasInstructions;
			int textureGradientInstructions;
			int floatInstructionCount;
			int intInstructionCount;
			int uintInstructionCount;
			int staticFlowControlCount;
			int dynamicFlowControlCount;
			int macroInstructionCount;
			int arrayInstructionCount;
			int cutInstructionCount;
			int emitInstructionCount;
			PrimitiveTopology geometryShaderOutputTopology;
			int geometryShaderMaxOutputVertexCount;
			int movInstructionCount;
			int movcInstructionCount;
			int conversionInstructionCount;
			int bitwiseInstructionCount;
			
			List<ShaderParameterDescription>^ inputParametersInfo;
			List<ShaderParameterDescription>^ outputParametersInfo;
			
			void Construct();
			
		internal:
			/* Unused.
			ShaderReflection( ID3D10ShaderReflection* reflection );
			*/
				
		public:
			/// <summary>
			/// Gets the version.
			/// </summary>
			property int Version
			{
				int get() { return version; }
			}
			
			/// <summary>
			/// Gets the creator.
			/// </summary>
			property String^ Creator
			{
				String^ get() { return creator; }
			}
			
			/// <summary>
			/// Gets the number of constant buffers.
			/// </summary>
			property int ConstantBufferCount
			{
				int get() { return constantBuffers; }
			}
			
			/// <summary>
			/// Gets the number of resource (textures and buffers) bound to a shader. 
			/// </summary>
			property int BoundResourcesCount
			{
				int get() { return boundResources; }
			}
			
			/// <summary>
			/// Gets the number of parameters in the input signature. 
			/// </summary>
			property int InputParameterCount
			{
				int get() { return inputParameters; }
			}
			
			/// <summary>
			/// Gets the number of parameters in the output signature. 
			/// </summary>
			property int OutputParameterCount
			{
				int get() { return outputParameters; }
			}
			
			property int InstructionCount
			{
				int get() { return instructionCount; }
			}
			
			property int TemporaryRegisterCount
			{
				int get() { return tempRegisterCount; }
			}
			
			property int TemporaryArrayCount
			{
				int get() { return tempArrayCount; }
			}
			
			property int ConstantDefinitionCount
			{
				int get() { return defCount; }
			}
			
			property int InputOutputDeclarationCount
			{
				int get() { return dclCount; }
			}
			
			property int TextureNormalInstructionCount
			{
				int get() { return textureNormalInstructions; }
			}
			
			property int TextureLoadInstructionCount
			{
				int get() { return textureLoadInstructions; }
			}
			
			property int TextureCompInstructionCount
			{
				int get() { return textureCompInstructions; }
			}
			
			property int TextureBiasInstructionCount
			{
				int get() { return textureBiasInstructions; }
			}
			
			property int TextureGradientInstructionCount
			{
				int get() { return textureGradientInstructions; }
			}
			
			property int FloatInstructionCount
			{
				int get() { return floatInstructionCount; }
			}
			
			property int IntegerInstructionCount
			{
				int get() { return intInstructionCount; }
			}
			
			property int UnsignedIntegerInstructionCount
			{
				int get() { return intInstructionCount; }
			}
			
			property int StaticFlowControlInstructionCount
			{
				int get() { return staticFlowControlCount; }
			}
			
			property int DynamicFlowControlInstructionCount
			{
				int get() { return dynamicFlowControlCount; }
			}
			
			property int MacroInstructionCount
			{
				int get() { return macroInstructionCount; }
			}
			
			property int ArrayInstructionCount
			{
				int get() { return arrayInstructionCount; }
			}
			
			property int CutInstructionCount
			{
				int get() { return cutInstructionCount; }
			}
			
			property int EmitInstructionCount
			{
				int get() { return emitInstructionCount; }
			}
			
			property PrimitiveTopology GeometryShaderOutputTopology
			{
				PrimitiveTopology get() { return geometryShaderOutputTopology; }
			}

			property int GeometryShaderMaxOutputVertexCount
			{
				int get() { return geometryShaderMaxOutputVertexCount; }
			}
			
			//property int MOVInstructionCount
			//{
			//	int get() { return movInstructionCount; }
			//}
			//
			//property int MOVCInstructionCount
			//{
			//	int get() { return movcInstructionCount; }
			//}
			
			//property int ConversionInstructionCount
			//{
			//	int get() { return conversionInstructionCount; }
			//}
			//
			//property int BitwiseInstructionCount
			//{
			//	int get() { return bitwiseInstructionCount; }
			//}
			
			property ReadOnlyCollection<ShaderParameterDescription>^ InputParameters
			{
				ReadOnlyCollection<ShaderParameterDescription>^ get()
				{
					return gcnew ReadOnlyCollection<ShaderParameterDescription>( inputParametersInfo );
				}
			}
			
			property ReadOnlyCollection<ShaderParameterDescription>^ OutputParameters
			{
				ReadOnlyCollection<ShaderParameterDescription>^ get()
				{
					return gcnew ReadOnlyCollection<ShaderParameterDescription>( outputParametersInfo );
				}
			}
		
			ShaderReflection( IntPtr reflection );
			ShaderReflection( ShaderBytecode^ shaderBytecode );
			
			virtual ~ShaderReflection() { Destruct(); }
		};
	}
};