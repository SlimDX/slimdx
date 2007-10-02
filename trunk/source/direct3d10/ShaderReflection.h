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

#include "../DirectXObject.h"

#include "Enums.h"
#include "Resource.h"

#include "ShaderReflectionParameterDescription.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class ShaderBytecode;
		
		public ref class ShaderReflection : public DirectXObject<ID3D10ShaderReflection>
		{
			UInt32 version;
			String^ creator;
			UInt32 flags; //TODO: No idea what values this can take...?
			UInt32 constantBuffers;
			UInt32 boundResources;
			UInt32 inputParameters;
			UInt32 outputParameters;
			UInt32 instructionCount;
			UInt32 tempRegisterCount;
			UInt32 tempArrayCount;
			UInt32 defCount;
			UInt32 dclCount;
			UInt32 textureNormalInstructions;
			UInt32 textureLoadInstructions;
			UInt32 textureCompInstructions;
			UInt32 textureBiasInstructions;
			UInt32 textureGradientInstructions;
			UInt32 floatInstructionCount;
			UInt32 intInstructionCount;
			UInt32 uint32InstructionCount;
			UInt32 staticFlowControlCount;
			UInt32 dynamicFlowControlCount;
			UInt32 macroInstructionCount;
			UInt32 arrayInstructionCount;
			UInt32 cutInstructionCount;
			UInt32 emitInstructionCount;
			PrimitiveTopology geometryShaderOutputTopology;
			UInt32 geometryShaderMaxOutputVertexCount;
			UInt32 movInstructionCount;
			UInt32 movcInstructionCount;
			UInt32 conversionInstructionCount;
			UInt32 bitwiseInstructionCount;
			
			List<ShaderReflectionParameterDescription>^ inputParametersInfo;
			List<ShaderReflectionParameterDescription>^ outputParametersInfo;
			
			void Construct();
			
		internal:
			ShaderReflection( ID3D10ShaderReflection* reflection );
				
		public:
			/// <summary>
			/// Gets the version.
			/// </summary>
			property UInt32 Version
			{
				UInt32 get() { return version; }
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
			property UInt32 ConstantBufferCount
			{
				UInt32 get() { return constantBuffers; }
			}
			
			/// <summary>
			/// Gets the number of resource (textures and buffers) bound to a shader. 
			/// </summary>
			property UInt32 BoundResourcesCount
			{
				UInt32 get() { return boundResources; }
			}
			
			/// <summary>
			/// Gets the number of parameters in the input signature. 
			/// </summary>
			property UInt32 InputParameterCount
			{
				UInt32 get() { return inputParameters; }
			}
			
			/// <summary>
			/// Gets the number of parameters in the output signature. 
			/// </summary>
			property UInt32 OutputParameterCount
			{
				UInt32 get() { return outputParameters; }
			}
			
			property UInt32 InstructionCount
			{
				UInt32 get() { return instructionCount; }
			}
			
			property UInt32 TemporaryRegisterCount
			{
				UInt32 get() { return tempRegisterCount; }
			}
			
			property UInt32 TemporaryArrayCount
			{
				UInt32 get() { return tempArrayCount; }
			}
			
			property UInt32 ConstantDefinitionCount
			{
				UInt32 get() { return defCount; }
			}
			
			property UInt32 InputOutputDeclarationCount
			{
				UInt32 get() { return dclCount; }
			}
			
			property UInt32 TextureNormalInstructionCount
			{
				UInt32 get() { return textureNormalInstructions; }
			}
			
			property UInt32 TextureLoadInstructionCount
			{
				UInt32 get() { return textureLoadInstructions; }
			}
			
			property UInt32 TextureCompInstructionCount
			{
				UInt32 get() { return textureCompInstructions; }
			}
			
			property UInt32 TextureBiasInstructionCount
			{
				UInt32 get() { return textureBiasInstructions; }
			}
			
			property UInt32 TextureGradientInstructionCount
			{
				UInt32 get() { return textureGradientInstructions; }
			}
			
			property UInt32 FloatInstructionCount
			{
				UInt32 get() { return floatInstructionCount; }
			}
			
			property UInt32 IntegerInstructionCount
			{
				UInt32 get() { return intInstructionCount; }
			}
			
			property UInt32 UnsignedIntegerInstructionCount
			{
				UInt32 get() { return uint32InstructionCount; }
			}
			
			property UInt32 StaticFlowControlInstructionCount
			{
				UInt32 get() { return staticFlowControlCount; }
			}
			
			property UInt32 DynamicFlowControlInstructionCount
			{
				UInt32 get() { return dynamicFlowControlCount; }
			}
			
			property UInt32 MacroInstructionCount
			{
				UInt32 get() { return macroInstructionCount; }
			}
			
			property UInt32 ArrayInstructionCount
			{
				UInt32 get() { return arrayInstructionCount; }
			}
			
			property UInt32 CutInstructionCount
			{
				UInt32 get() { return cutInstructionCount; }
			}
			
			property UInt32 EmitInstructionCount
			{
				UInt32 get() { return emitInstructionCount; }
			}
			
			property PrimitiveTopology GeometryShaderOutputTopology
			{
				PrimitiveTopology get() { return geometryShaderOutputTopology; }
			}

			property UInt32 GeometryShaderMaxOutputVertexCount
			{
				UInt32 get() { return geometryShaderMaxOutputVertexCount; }
			}
			
			//property UInt32 MOVInstructionCount
			//{
			//	UInt32 get() { return movInstructionCount; }
			//}
			//
			//property UInt32 MOVCInstructionCount
			//{
			//	UInt32 get() { return movcInstructionCount; }
			//}
			
			//property UInt32 ConversionInstructionCount
			//{
			//	UInt32 get() { return conversionInstructionCount; }
			//}
			//
			//property UInt32 BitwiseInstructionCount
			//{
			//	UInt32 get() { return bitwiseInstructionCount; }
			//}
			
			property ReadOnlyCollection<ShaderReflectionParameterDescription>^ InputParameters
			{
				ReadOnlyCollection<ShaderReflectionParameterDescription>^ get()
				{
					return gcnew ReadOnlyCollection<ShaderReflectionParameterDescription>( inputParametersInfo );
				}
			}
			
			property ReadOnlyCollection<ShaderReflectionParameterDescription>^ OutputParameters
			{
				ReadOnlyCollection<ShaderReflectionParameterDescription>^ get()
				{
					return gcnew ReadOnlyCollection<ShaderReflectionParameterDescription>( outputParametersInfo );
				}
			}
		
			ShaderReflection( IntPtr reflection );
			ShaderReflection( ShaderBytecode^ shaderBytecode );
			
			virtual ~ShaderReflection() { Destruct(); }
		};
	}
};