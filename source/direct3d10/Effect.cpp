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
#include <vcclr.h>

#include "GraphicsException.h"

#include "Effect.h"
#include "Device.h"
#include "EffectTechnique.h"
#include "EffectVariable.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Effect::Effect( ID3D10Effect* effect ) : DirectXObject( effect )
	{
		D3D10_EFFECT_DESC desc;
		HRESULT hr = effect->GetDesc( &desc );
		GraphicsException::CheckHResult( hr );
		
		m_IsChildEffect = desc.IsChildEffect ? true : false;
		m_ConstantBufferCount = desc.ConstantBuffers;
		m_SharedConstantBufferCount = desc.SharedConstantBuffers;
		m_GlobalVariableCount = desc.GlobalVariables;
		m_TechniqueCount = desc.Techniques;
	}

	EffectTechnique^ Effect::GetTechniqueByIndex( int index )
	{
		ID3D10EffectTechnique* technique;

		technique = m_Pointer->GetTechniqueByIndex( index );
		//@TODO D3D10: Throw TechniqueNotFound if not found
		return gcnew EffectTechnique( technique );
	}

	EffectTechnique^ Effect::GetTechniqueByName( System::String^ name )
	{
		ID3D10EffectTechnique* technique;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		technique = m_Pointer->GetTechniqueByName( (LPCSTR) pinnedName );
		//@TODO D3D10: Throw TechniqueNotFound if not fount
		return gcnew EffectTechnique( technique );
	}
	
	EffectVariable^ Effect::GetVariableByIndex( int index )
	{
		ID3D10EffectVariable* variable;
		
		variable = m_Pointer->GetVariableByIndex( index );
		//@TODO D3D10: Throw VariableNotFound if not found.
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableByName( System::String^ name )
	{
		ID3D10EffectVariable* variable;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		variable = m_Pointer->GetVariableByName( (LPCSTR) pinnedName );
		//@TODO D3D10: Throw VariableNotFound if not found.
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableBySemantic( System::String^ name )
	{
		ID3D10EffectVariable* variable;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		variable = m_Pointer->GetVariableBySemantic( (LPCSTR) pinnedName );
		//@TODO D3D10: Throw VariableNotFound if not found.
		return gcnew EffectVariable( variable );
	}
	
	void Effect::Optimize()
	{
		HRESULT hr = m_Pointer->Optimize();
		GraphicsException::CheckHResult( hr );
	}

	Effect^ Effect::FromFile( Device^ device, String ^fileName, String^ profile )
	{
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10Effect* effect;

		HRESULT hr = D3DX10CreateEffectFromFile( pinnedFileName, NULL, NULL, (LPCSTR) pinnedProfile, 0, 0, device->DevicePointer, NULL, NULL, &effect, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		return gcnew Effect( effect );
	}
	
	Effect^ Effect::FromString( Device^ device, String^ code, String^ profile )
	{
		array<unsigned char>^ codeBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( code );
		pin_ptr<unsigned char> pinnedCode = &codeBytes[0];
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10Effect* effect;
		
		HRESULT hr = D3DX10CreateEffectFromMemory( pinnedCode, code->Length, "n/a", NULL, NULL, (LPCSTR) pinnedProfile, 0, 0, device->DevicePointer, NULL, NULL, &effect, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		return gcnew Effect( effect );
	}
}
}
