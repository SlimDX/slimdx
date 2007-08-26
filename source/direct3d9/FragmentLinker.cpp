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
#include <d3d9.h>
#include <d3dx9.h>

#include "../DirectXObject.h"
#include "Device.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "FragmentLinker.h"

namespace SlimDX
{
namespace Direct3D9
{
	FragmentLinker::FragmentLinker( ID3DXFragmentLinker* linker ) : DirectXObject( linker )
	{
		if( linker == NULL )
			throw gcnew ArgumentNullException( "linker" );
	}

	FragmentLinker::FragmentLinker( Device^ device, int cacheSize )
	{
		IDirect3DDevice9* devicePointer = device->InternalPointer;
		ID3DXFragmentLinker* linker;

		HRESULT hr = D3DXCreateFragmentLinker( devicePointer, cacheSize, &linker );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = linker;
	}

	ShaderFragments^ FragmentLinker::Gather( array<Byte>^ sourceData, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXBuffer* fragmentBuffer;
		ID3DXBuffer* errorBuffer;
		pin_ptr<const Byte> pinnedData = &sourceData[0];

		ID3DXInclude* include = includeFile != nullptr ? includeFile->Shim : NULL;
		array<GCHandle>^ handles;
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXGatherFragments( (LPCSTR) pinnedData, sourceData->Length, macros, include,
			(DWORD) flags, &fragmentBuffer, &errorBuffer );
		
		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = BufferWrapper::ConvertToString( errorBuffer );
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", errors );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew ShaderFragments( errorBuffer );
	}

	ShaderFragments^ FragmentLinker::Gather( String^ sourceData, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		array<Byte>^ sourceBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceData );
		return Gather( sourceBytes, defines, includeFile, flags, errors );
	}

	ShaderFragments^ FragmentLinker::GatherFromFile( String^ fileName, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXBuffer* fragmentBuffer;
		ID3DXBuffer* errorBuffer;
		pin_ptr<const wchar_t> pinnedFile = PtrToStringChars( fileName );

		ID3DXInclude* include = includeFile != nullptr ? includeFile->Shim : NULL;
		array<GCHandle>^ handles;
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXGatherFragmentsFromFile( (LPCTSTR) pinnedFile, macros, include,
			(DWORD) flags, &fragmentBuffer, &errorBuffer );
		
		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = BufferWrapper::ConvertToString( errorBuffer );
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", errors );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew ShaderFragments( errorBuffer );
	}

	void FragmentLinker::AddFragments( array<int>^ fragments )
	{
		pin_ptr<int> pinnedFragments = &fragments[0];
		HRESULT hr = m_Pointer->AddFragments( (const DWORD*) pinnedFragments );
		GraphicsException::CheckHResult( hr );
	}

	void FragmentLinker::AddFragments( DataStream^ fragments )
	{
		HRESULT hr = m_Pointer->AddFragments( (const DWORD*) fragments->RawPointer );
		GraphicsException::CheckHResult( hr );
	}

	ShaderFragments^ FragmentLinker::GetFragment( EffectHandle^ name )
	{
		D3DXHANDLE handle = name != nullptr ? name->InternalHandle : NULL;
		ID3DXBuffer* fragment;

		HRESULT hr = m_Pointer->GetFragment( handle, &fragment );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew ShaderFragments( fragment );
	}

	ShaderFragments^ FragmentLinker::GetAllFragments()
	{
		ID3DXBuffer* fragments;

		HRESULT hr = m_Pointer->GetAllFragments( &fragments );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew ShaderFragments( fragments );
	}

	Device^ FragmentLinker::GetDevice()
	{
		IDirect3DDevice9* device;
		//This method always returns the value S_OK.
		m_Pointer->GetDevice( &device );

		return gcnew Device( device );
	}

	FragmentDescription FragmentLinker::GetFragmentDesc( EffectHandle^ name )
	{
		D3DXHANDLE handle = name != nullptr ? name->InternalHandle : NULL;
		D3DXFRAGMENT_DESC desc;

		HRESULT hr = m_Pointer->GetFragmentDesc( handle, &desc );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return FragmentDescription();

		FragmentDescription outDesc;
		outDesc.Name = gcnew String( desc.Name );
		outDesc.Target = desc.Target;

		return outDesc;
	}

	EffectHandle^ FragmentLinker::GetFragmentHandle( int index )
	{
		D3DXHANDLE handle = m_Pointer->GetFragmentHandleByIndex( index );
		if( handle == NULL )
			return nullptr;

		return gcnew EffectHandle( handle );
	}

	EffectHandle^ FragmentLinker::GetFragmentHandle( String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<const Byte> pinnedName = &nameBytes[0];

		D3DXHANDLE handle = m_Pointer->GetFragmentHandleByName( (LPCSTR) pinnedName );
		if( handle == NULL )
			return nullptr;

		return gcnew EffectHandle( handle );
	}

	void FragmentLinker::ClearCache()
	{
		//This method always returns the value S_OK.
		m_Pointer->ClearCache();
	}

	ShaderBytecode^ FragmentLinker::LinkShader( String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] String^% errors )
	{
		ID3DXBuffer* bytecode;
		ID3DXBuffer* errorBuffer;
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<const Byte> pinnedProfile = &profileBytes[0];

		D3DXHANDLE* handles = new D3DXHANDLE[fragmentHandles->Length];
		for( int i = 0; i < fragmentHandles->Length; ++i )
		{
			handles[i] = fragmentHandles[i] != nullptr ? fragmentHandles[i]->InternalHandle : NULL;
		}

		HRESULT hr = m_Pointer->LinkShader( (LPCSTR) pinnedProfile, (DWORD) flags, handles, fragmentHandles->Length, &bytecode, &errorBuffer );
		delete[] handles;
		GraphicsException::CheckHResult( hr );
		
		//marshal errors if necessary
		errors = BufferWrapper::ConvertToString( errorBuffer );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew ShaderBytecode( bytecode );
	}

	VertexShader^ FragmentLinker::LinkVertexShader( String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] String^% errors )
	{
		IDirect3DVertexShader9* shader;
		ID3DXBuffer* errorBuffer;
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<const Byte> pinnedProfile = &profileBytes[0];

		D3DXHANDLE* handles = new D3DXHANDLE[fragmentHandles->Length];
		for( int i = 0; i < fragmentHandles->Length; ++i )
		{
			handles[i] = fragmentHandles[i] != nullptr ? fragmentHandles[i]->InternalHandle : NULL;
		}

		HRESULT hr = m_Pointer->LinkVertexShader( (LPCSTR) pinnedProfile, (DWORD) flags, handles, fragmentHandles->Length, &shader, &errorBuffer );
		delete[] handles;
		GraphicsException::CheckHResult( hr );
		
		//marshal errors if necessary
		errors = BufferWrapper::ConvertToString( errorBuffer );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew VertexShader( shader );
	}

	PixelShader^ FragmentLinker::LinkPixelShader( String^ profile, ShaderFlags flags, array<EffectHandle^>^ fragmentHandles, [Out] String^% errors )
	{
		IDirect3DPixelShader9* shader;
		ID3DXBuffer* errorBuffer;
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<const Byte> pinnedProfile = &profileBytes[0];

		D3DXHANDLE* handles = new D3DXHANDLE[fragmentHandles->Length];
		for( int i = 0; i < fragmentHandles->Length; ++i )
		{
			handles[i] = fragmentHandles[i] != nullptr ? fragmentHandles[i]->InternalHandle : NULL;
		}

		HRESULT hr = m_Pointer->LinkPixelShader( (LPCSTR) pinnedProfile, (DWORD) flags, handles, fragmentHandles->Length, &shader, &errorBuffer );
		delete[] handles;
		GraphicsException::CheckHResult( hr );
		
		//marshal errors if necessary
		errors = BufferWrapper::ConvertToString( errorBuffer );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew PixelShader( shader );
	}

	int FragmentLinker::FragmentCount::get()
	{
		return m_Pointer->GetNumberOfFragments();
	}
}
}