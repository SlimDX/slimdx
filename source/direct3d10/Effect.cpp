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
		if( technique == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any technique in the effect.", index ) );
		return gcnew EffectTechnique( technique );
	}

	EffectTechnique^ Effect::GetTechniqueByName( System::String^ name )
	{
		ID3D10EffectTechnique* technique;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		technique = m_Pointer->GetTechniqueByName( (LPCSTR) pinnedName );
		if( technique == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any technique in the effect.", name ) );
		return gcnew EffectTechnique( technique );
	}
	
	EffectVariable^ Effect::GetVariableByIndex( int index )
	{
		ID3D10EffectVariable* variable;
		
		variable = m_Pointer->GetVariableByIndex( index );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any variable in the effect.", index ) );
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableByName( System::String^ name )
	{
		ID3D10EffectVariable* variable;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		variable = m_Pointer->GetVariableByName( (LPCSTR) pinnedName );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any variable in the effect.", name ) );
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableBySemantic( System::String^ name )
	{
		ID3D10EffectVariable* variable;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		variable = m_Pointer->GetVariableBySemantic( (LPCSTR) pinnedName );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Semantic '{0}' does not identify any variable in the effect.", name ) );
		return gcnew EffectVariable( variable );
	}
	
	void Effect::Optimize()
	{
		HRESULT hr = m_Pointer->Optimize();
		GraphicsException::CheckHResult( hr );
	}

	Effect^ Effect::FromFile( Device^ device, String ^fileName, String^ profile )
	{
		String^ compilationErrors;
		return (FromFile( device, fileName, profile, compilationErrors ));
	}
	
	Effect^ Effect::FromFile( Device^ device, String ^fileName, String^ profile, [Out] String^ %compilationErrors  )
	{
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10Effect* effect;
		ID3D10Blob* errorBlob;

		HRESULT hr = D3DX10CreateEffectFromFile( pinnedFileName, NULL, NULL, (LPCSTR) pinnedProfile, 0, 0, device->DevicePointer, NULL, NULL, &effect, &errorBlob, NULL );
		GraphicsException::CheckHResult( hr );

		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( (const char*) errorBlob->GetBufferPointer() );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", compilationErrors );
		if( effect == NULL)
			return nullptr;
		return gcnew Effect( effect );
	}
	
	Effect^ Effect::FromString( Device^ device, String^ code, String^ profile )
	{
		String^ compilationErrors;
		return (FromString( device, code, profile, compilationErrors ));
	}
	
	Effect^ Effect::FromString( Device^ device, String^ code, String^ profile, [Out] String^ %compilationErrors  )
	{
		array<unsigned char>^ codeBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( code );
		pin_ptr<unsigned char> pinnedCode = &codeBytes[0];
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10Effect* effect;
		ID3D10Blob* errorBlob;
		
		HRESULT hr = D3DX10CreateEffectFromMemory( pinnedCode, code->Length, "n/a", NULL, NULL, (LPCSTR) pinnedProfile, 0, 0, device->DevicePointer, NULL, NULL, &effect, &errorBlob, NULL );
		
		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( (const char*) errorBlob->GetBufferPointer() );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", compilationErrors );
		if( effect == NULL)
			return nullptr;
		return gcnew Effect( effect );
	}
}
}
