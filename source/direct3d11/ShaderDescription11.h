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

#include "Enums11.h"
#include "../d3dcompiler/EnumsDC.h"

namespace SlimDX
{
	namespace Direct3D11
	{	
		public ref class ShaderDescription
		{
		internal:
			ShaderDescription( const D3D11_SHADER_DESC &desc );

		public:
			property int Version;
			property System::String^ Creator;
			property D3DCompiler::ShaderFlags Flags;
			property int ConstantBuffers;
			property int BoundResources;
			property int InputParameters;
			property int OutputParameters;
			property int InstructionCount;
			property int TempRegisterCount;
			property int TempArrayCount;
			property int DefineCount;
			property int DeclarationCount;
			property int TextureNormalInstructions;
			property int TextureLoadInstructions;
			property int TextureCompareInstructions;
			property int TextureBiasInstructions;
			property int TextureGradientInstructions;
			property int FloatInstructionCount;
			property int IntInstructionCount;
			property int UintInstructionCount;
			property int StaticFlowControlCount;
			property int DynamicFlowControlCount;
			property int MacroInstructionCount;
			property int ArrayInstructionCount;
			property int CutInstructionCount;
			property int EmitInstructionCount;
			property PrimitiveTopology GeometryShaderOutputTopology;
			property int MaximumOutputVertexCount;
			property InputPrimitive InputPrimitive;
			property int PatchConstantParameters;
			property int GeometryShaderInstanceCount;
			property int ControlPoints;
			property TessellatorOutputPrimitive HullShaderOutputPrimitive;
			property TessellatorPartitioning HullShaderPartitioning;
			property TessellatorDomain TessellatorDomain;
			property int BarrierInstructions;
			property int InterlockedInstructions;
			property int TextureStoreInstructions;
		};
	}
}