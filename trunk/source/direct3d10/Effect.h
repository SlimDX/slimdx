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
using namespace System::Runtime::InteropServices;

#include "../DirectXObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		ref class EffectTechnique;
		ref class EffectVariable;
		
		public ref class Effect : public DirectXObject<ID3D10Effect>
		{
			bool m_IsChildEffect;
			int m_ConstantBufferCount;
			int m_SharedConstantBufferCount;
			int m_GlobalVariableCount;
			int m_TechniqueCount;
		
		internal:
			Effect( ID3D10Effect* effect );
		
		public:
			virtual ~Effect() { Destruct(); }

			property bool IsChildEffect
			{
				bool get() { return m_IsChildEffect; }
			}
			
			property int ConstantBufferCount
			{
				int get() { return m_ConstantBufferCount; }
			}
			
			property int SharedConstantBufferCount
			{
				int get() { return m_SharedConstantBufferCount; }
			}
			
			property int SharedGlobalVariablesCount
			{
				int get() { return m_GlobalVariableCount; }
			}
			
			property int TechniqueCount
			{
				int get() { return m_TechniqueCount; }
			}
			
			property bool IsOptimized
			{
				bool get() { return m_Pointer->IsOptimized() ? true : false; }
			}
			
			property bool IsPooled
			{
				bool get() { return m_Pointer->IsPool() ? true : false; }
			}
			
			property bool IsValid
			{
				bool get() { return m_Pointer->IsValid() ? true : false; }
			}
			
			EffectTechnique^ GetTechniqueByIndex( int index );
			EffectTechnique^ GetTechniqueByName( String^ name );
			
			EffectVariable^ GetVariableByIndex( int index );
			EffectVariable^ GetVariableByName( String^ name );
			EffectVariable^ GetVariableBySemantic( String^ name );
			
			void Optimize();
			
			static Effect^ FromFile( Device^ device, String^ fileName, String^ profile );
			static Effect^ FromString( Device^ device, String^ code, String^ profile );
			static Effect^ FromString( Device^ device, String^ code, String^ profile, [Out] String^ %compilationErrors  );
		};
	}
};