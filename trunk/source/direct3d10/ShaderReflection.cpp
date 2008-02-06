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

#include <d3d10.h>
#include <d3dx10.h>

//#include "Direct3D10ErrorHandler.h"

#include "ShaderReflection.h"
#include "ShaderBytecode.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	/* Unused.
	ShaderReflection::ShaderReflection( ID3D10ShaderReflection* reflection ) : ComObject( reflection )
	{
		Construct();
	}
	*/
	
	ShaderReflection::ShaderReflection( IntPtr reflection )
	{
		Construct( reflection, NativeInterface );
		Construct();
	}
	
	ShaderReflection::ShaderReflection( ShaderBytecode^ shaderBytecode )
	{
		if( shaderBytecode == nullptr )
			throw gcnew ArgumentNullException( "shaderBytecode" );
		
		ID3D10ShaderReflection* reflection;
		HRESULT hr = D3D10ReflectShader( shaderBytecode->Buffer, shaderBytecode->Length, &reflection );
		Result::Record( hr );
		
		Construct(reflection);
		Construct();
	}
	
	void ShaderReflection::Construct()
	{
		D3D10_SHADER_DESC description;
		HRESULT hr = static_cast<ID3D10ShaderReflection*>( InternalPointer )->GetDesc( &description );
		Result::Record( hr );
		
		version = description.Version;
		creator = gcnew String( description.Creator );
		flags = 0;//TODO ...
		constantBuffers = description.ConstantBuffers;
		boundResources = description.BoundResources;
		inputParameters = description.InputParameters;
		outputParameters = description.OutputParameters;
		instructionCount = description.InstructionCount;
		tempRegisterCount = description.TempRegisterCount;
		tempArrayCount = description.TempArrayCount;
		defCount = description.DefCount;
		dclCount = description.DclCount;
		textureNormalInstructions = description.TextureNormalInstructions;
		textureLoadInstructions = description.TextureLoadInstructions;
		textureCompInstructions = description.TextureCompInstructions;
		textureBiasInstructions = description.TextureBiasInstructions;
		textureGradientInstructions = description.TextureGradientInstructions;
		floatInstructionCount = description.FloatInstructionCount;
		intInstructionCount = description.IntInstructionCount;
		uintInstructionCount = description.UintInstructionCount;
		staticFlowControlCount = description.StaticFlowControlCount;
		dynamicFlowControlCount = description.DynamicFlowControlCount;
		macroInstructionCount = description.MacroInstructionCount;
		arrayInstructionCount = description.ArrayInstructionCount;
		cutInstructionCount = description.CutInstructionCount;
		emitInstructionCount = description.EmitInstructionCount;
		geometryShaderOutputTopology = static_cast<PrimitiveTopology>( description.GSOutputTopology );
		geometryShaderMaxOutputVertexCount= description.GSMaxOutputVertexCount;
		//movInstructionCount = description.MovInstructionCount;
		//movcInstructionCount = description.MovcInstructionCount;
		//conversionInstructionCount = description.ConversionInstructionCount;
		//bitwiseInstructionCount = description.BitwiseInstructionCount;
		
		inputParametersInfo = gcnew List<ShaderParameterDescription>();
		for( int inputIndex = 0; inputIndex < inputParameters; ++inputIndex )
		{
			D3D10_SIGNATURE_PARAMETER_DESC parameterDesc;
			hr = 	static_cast<ID3D10ShaderReflection*>( InternalPointer )->GetInputParameterDesc( inputIndex, &parameterDesc );
			Result::Record( hr );
			
			inputParametersInfo->Add( ShaderParameterDescription( parameterDesc ) );
		}
		
		outputParametersInfo = gcnew List<ShaderParameterDescription>();
		for( int outputIndex = 0; outputIndex < outputParameters; ++outputIndex )
		{
			D3D10_SIGNATURE_PARAMETER_DESC parameterDesc;
			hr = 	static_cast<ID3D10ShaderReflection*>( InternalPointer )->GetOutputParameterDesc( outputIndex, &parameterDesc );
			Result::Record( hr );
			
			outputParametersInfo->Add( ShaderParameterDescription( parameterDesc ) );
		}
	}
}
}
