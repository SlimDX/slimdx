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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../DataStream.h"
#include "../DirectXObject.h"
#include "../Utils.h"
#include "GraphicsException.h"

#include "Device.h"
#include "Direct3D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Query.h"
#include "SwapChain.h"
#include "StateBlock.h"
#include "D3DX.h"

namespace SlimDX
{
namespace Direct3D9
{
	//ATI R2VB functions

	//quick utility function
	void ConvertPresentParams( PresentParameters^ presentParams, D3DPRESENT_PARAMETERS& d3dpp )
	{
		d3dpp.AutoDepthStencilFormat = static_cast<D3DFORMAT>( presentParams->AutoDepthStencilFormat );
		d3dpp.BackBufferCount = presentParams->BackBufferCount;
		d3dpp.BackBufferFormat = static_cast<D3DFORMAT>( presentParams->BackBufferFormat );
		d3dpp.BackBufferHeight = presentParams->BackBufferHeight;
		d3dpp.BackBufferWidth = presentParams->BackBufferWidth;
		d3dpp.EnableAutoDepthStencil = presentParams->EnableAutoDepthStencil;
		d3dpp.Flags = static_cast<DWORD>( presentParams->PresentFlags );
		d3dpp.FullScreen_RefreshRateInHz = presentParams->FullScreenRefreshRateInHertz;
		d3dpp.hDeviceWindow = static_cast<HWND>( presentParams->DeviceWindowHandle.ToPointer() );
		d3dpp.MultiSampleQuality = presentParams->MultisampleQuality;
		d3dpp.MultiSampleType = static_cast<D3DMULTISAMPLE_TYPE>( presentParams->Multisample );
		d3dpp.PresentationInterval = static_cast<UINT>( presentParams->PresentationInterval );
		d3dpp.SwapEffect = static_cast<D3DSWAPEFFECT>( presentParams->SwapEffect );
		d3dpp.Windowed = presentParams->Windowed;
	}

	PresentParameters::PresentParameters()
	{
		//set sane defaults
		BackBufferWidth = 640;
		BackBufferHeight = 480;
		BackBufferFormat = Format::X8R8G8B8;
		BackBufferCount = 1;

		Multisample = MultisampleType::None;
		MultisampleQuality = 0;

		SwapEffect = SlimDX::Direct3D9::SwapEffect::Discard;
		DeviceWindowHandle = IntPtr::Zero;
		Windowed = true;
		EnableAutoDepthStencil = true;
		AutoDepthStencilFormat = Format::D24X8;
		PresentFlags = SlimDX::Direct3D9::PresentFlags::None;

		FullScreenRefreshRateInHertz = 0;
		PresentationInterval = PresentInterval::Immediate;
	}

	Device::Device( IDirect3DDevice9* device )
	{
		if( device == NULL )
			throw gcnew ArgumentNullException( "device" );

		m_Pointer = device;
		
		device->AddRef();
	}

	Device::Device( IntPtr device )
	{
		if( device == IntPtr::Zero )
			throw gcnew ArgumentNullException( "device" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( device.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DDevice9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDirect3DDevice9*>( pointer );
	}

	Device::Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParams )
	{
		IDirect3DDevice9* device;
		D3DPRESENT_PARAMETERS d3dpp;

		if( Direct3D::InternalPointer == NULL )
			throw gcnew Direct3DNotInitializedException();

		ConvertPresentParams( presentParams, d3dpp );
		HRESULT hr = Direct3D::InternalPointer->CreateDevice( adapter,
			static_cast<D3DDEVTYPE>( deviceType ),
			static_cast<HWND>( controlHandle.ToPointer() ), 
			static_cast<DWORD>( createFlags ),
			reinterpret_cast<D3DPRESENT_PARAMETERS*>( &d3dpp ),
			&device );
		GraphicsException::CheckHResult( hr );

		m_Pointer = device;
	}

	void Device::VertexFormat::set( SlimDX::Direct3D9::VertexFormat value )
	{
		HRESULT hr = m_Pointer->SetFVF( static_cast<DWORD>( value ) );
		GraphicsException::CheckHResult( hr );
	}

	SlimDX::Direct3D9::VertexFormat Device::VertexFormat::get()
	{
		DWORD fvf = 0;
		HRESULT hr = m_Pointer->GetFVF( &fvf );
		GraphicsException::CheckHResult( hr );

		return static_cast<SlimDX::Direct3D9::VertexFormat>( fvf );
	}
	
	void Device::VertexDeclaration::set( SlimDX::Direct3D9::VertexDeclaration^ value )
	{
		HRESULT hr;
		if( value != nullptr )
			hr = m_Pointer->SetVertexDeclaration( value->InternalPointer );
		else
			hr = m_Pointer->SetVertexDeclaration( NULL );

		GraphicsException::CheckHResult( hr );
	}

	SlimDX::Direct3D9::VertexDeclaration^ Device::VertexDeclaration::get()
	{
		IDirect3DVertexDeclaration9* decl;
		HRESULT hr = m_Pointer->GetVertexDeclaration( &decl );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew SlimDX::Direct3D9::VertexDeclaration( decl );
	}

	void Device::DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount )
	{
		HRESULT hr = m_Pointer->DrawPrimitive( static_cast<D3DPRIMITIVETYPE>( primitiveType ), startIndex, primitiveCount );
		GraphicsException::CheckHResult( hr );
	}

	generic<typename T>
	void Device::DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data )
	{
		pin_ptr<T> pinned_data = &data[startIndex];

		HRESULT hr = m_Pointer->DrawPrimitiveUP( static_cast<D3DPRIMITIVETYPE>( primitiveType ), primitiveCount,
			pinned_data, Marshal::SizeOf( T::typeid ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
		int numVertices, int startIndex, int primCount )
	{
		HRESULT hr = m_Pointer->DrawIndexedPrimitive( static_cast<D3DPRIMITIVETYPE>( primitiveType ), baseVertexIndex,
			minVertexIndex, numVertices, startIndex, primCount );
		GraphicsException::CheckHResult( hr );
	}

	generic<typename S, typename T>
	void Device::DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minVertexIndex, int numVertices, int primitiveCount,
		array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride )
	{
		pin_ptr<S> pinnedIndices = &indexData[0];
		pin_ptr<T> pinnedVertices = &vertexData[0];

		HRESULT hr = m_Pointer->DrawIndexedPrimitiveUP( static_cast<D3DPRIMITIVETYPE>( primitiveType ), minVertexIndex, numVertices,
			primitiveCount, pinnedIndices, static_cast<D3DFORMAT>( indexDataFormat ), pinnedVertices, vertexStride );
		GraphicsException::CheckHResult( hr );
	}

	void Device::Clear( ClearFlags clearFlags, int color, float zdepth, int stencil )
	{
		HRESULT hr = m_Pointer->Clear( 0, 0, static_cast<DWORD>( clearFlags ), static_cast<D3DCOLOR>( color ), zdepth, stencil );
		GraphicsException::CheckHResult( hr );
	}

	void Device::Clear( ClearFlags clearFlags, Color color, float zdepth, int stencil )
	{
		Clear( clearFlags, color.ToArgb(), zdepth, stencil );
	}

	void Device::BeginScene()
	{
		HRESULT hr = m_Pointer->BeginScene();
		GraphicsException::CheckHResult( hr );
	}

	void Device::EndScene()
	{
		HRESULT hr = m_Pointer->EndScene();
		GraphicsException::CheckHResult( hr );
	}

	void Device::Present()
	{
		HRESULT hr = m_Pointer->Present( 0, 0, 0, 0 );
		GraphicsException::CheckHResult( hr );
	}

	void Device::Present( SlimDX::Direct3D9::Present flags )
	{
		IDirect3DSwapChain9* swapChain;

		HRESULT hr = m_Pointer->GetSwapChain( 0, &swapChain );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return;

		hr = swapChain->Present( 0, 0, 0, 0, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );

		hr = swapChain->Release();
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderState( RenderState state, int value )
	{
		HRESULT hr = m_Pointer->SetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderState( RenderState state, bool value )
	{
		BOOL boolValue = value ? TRUE : FALSE;
		HRESULT hr = m_Pointer->SetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), boolValue );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderState( RenderState state, float value )
	{
		DWORD* dwValue = reinterpret_cast<DWORD*>( &value );
		HRESULT hr = m_Pointer->SetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), *dwValue );
		GraphicsException::CheckHResult( hr );
	}

	generic<typename T>
	void Device::SetRenderState( RenderState state, T value )
	{
		SetRenderState( state, static_cast<int>( value ) );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, int value )
	{
		HRESULT hr = m_Pointer->SetTextureStageState( stage, static_cast<D3DTEXTURESTAGESTATETYPE>( type ), value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, TextureOperation texOp )
	{
		SetTextureStageState( stage, type, static_cast<int>( texOp ) );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, TextureArgument texArg )
	{
		SetTextureStageState( stage, type, static_cast<int>( texArg ) );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, TextureTransform texTransform )
	{
		SetTextureStageState( stage, type, static_cast<int>( texTransform ) );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, float value )
	{
		int* dwValue = reinterpret_cast<int*>( &value );
		SetTextureStageState( stage, type, *dwValue );
	}

	void Device::SetSamplerState( int sampler, SamplerState type, int value )
	{
		HRESULT hr = m_Pointer->SetSamplerState( sampler, static_cast<D3DSAMPLERSTATETYPE>( type ), value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetSamplerState( int sampler, SamplerState type, float value )
	{
		DWORD* dwValue = reinterpret_cast<DWORD*>( &value );
		HRESULT hr = m_Pointer->SetSamplerState( sampler, static_cast<D3DSAMPLERSTATETYPE>( type ), *dwValue );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetSamplerState( int sampler, SamplerState type, TextureAddress texAddr )
	{
		SetSamplerState( sampler, type, static_cast<int>( texAddr ) );
	}

	void Device::SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter )
	{
		SetSamplerState( sampler, type, static_cast<int>( texFilter ) );
	}

	void Device::SetTransform( TransformState state, Matrix value )
	{
		HRESULT hr = m_Pointer->SetTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<const D3DMATRIX*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}
	
	Matrix Device::GetTransform( TransformState state )
	{
		Matrix result;
		HRESULT hr = m_Pointer->GetTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<D3DMATRIX*>( &result ) );
		GraphicsException::CheckHResult( hr );
		return result;
	}

	void Device::MultiplyTransform( TransformState state, Matrix value )
	{
		HRESULT hr = m_Pointer->MultiplyTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<const D3DMATRIX*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride )
	{
		IDirect3DVertexBuffer9* vbPointer = streamData != nullptr ? streamData->VbPointer : NULL;
		HRESULT hr = m_Pointer->SetStreamSource( stream, vbPointer, offsetInBytes, stride );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetStreamSourceFreq( int stream, int frequency )
	{
		HRESULT hr = m_Pointer->SetStreamSourceFreq( stream, frequency );
		GraphicsException::CheckHResult( hr );
	}

	SlimDX::Direct3D9::Material Device::Material::get()
	{
		SlimDX::Direct3D9::Material material;

		HRESULT hr = m_Pointer->GetMaterial( reinterpret_cast<D3DMATERIAL9*>( &material ) );
		GraphicsException::CheckHResult( hr );

		return material;
	}

	void Device::Material::set( SlimDX::Direct3D9::Material material )
	{
		HRESULT hr = m_Pointer->SetMaterial( reinterpret_cast<const D3DMATERIAL9*>( &material ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::TestCooperativeLevel()
	{
		HRESULT hr = m_Pointer->TestCooperativeLevel();
		GraphicsException::CheckHResult( hr );
	}

	CooperativeLevel Device::CheckCooperativeLevel()
	{
		HRESULT hr = m_Pointer->TestCooperativeLevel();
		return static_cast<CooperativeLevel>( hr );
	}

	void Device::Reset( PresentParameters^ presentParams )
	{
		D3DPRESENT_PARAMETERS d3dpp;

		ConvertPresentParams( presentParams, d3dpp );
		HRESULT hr = m_Pointer->Reset( &d3dpp );
		GraphicsException::CheckHResult( hr );

		presentParams->BackBufferCount = d3dpp.BackBufferCount;
		presentParams->BackBufferFormat = static_cast<Format>( d3dpp.BackBufferFormat );
		presentParams->BackBufferWidth = d3dpp.BackBufferWidth;
		presentParams->BackBufferHeight = d3dpp.BackBufferHeight;
	}

	void Device::SetTexture( int sampler, BaseTexture^ texture )
	{
		IDirect3DBaseTexture9* texturePointer = texture != nullptr ? texture->BaseTexturePointer : NULL;
		HRESULT hr = m_Pointer->SetTexture( sampler, texturePointer );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderTarget( int rtIndex, Surface^ target )
	{
		IDirect3DSurface9* surfacePointer = target != nullptr ? target->SurfacePointer : NULL;
		HRESULT hr = m_Pointer->SetRenderTarget( rtIndex, surfacePointer );
		GraphicsException::CheckHResult( hr );
	}
	
	void Device::SetPixelShader( PixelShader^ shader )
	{
		IDirect3DPixelShader9 *ptr = shader != nullptr ? shader->InternalPointer : NULL; 
		HRESULT hr = m_Pointer->SetPixelShader( ptr );
		GraphicsException::CheckHResult( hr );
	}
	
	void Device::SetVertexShader( VertexShader^ shader )
	{
		IDirect3DVertexShader9 *ptr = shader != nullptr ? shader->InternalPointer : NULL; 
		HRESULT hr = m_Pointer->SetVertexShader( ptr );
		GraphicsException::CheckHResult( hr );
	}
	
	void Device::SetDepthStencilSurface( Surface^ target )
	{	
		IDirect3DSurface9* surface = target != nullptr ? target->SurfacePointer : NULL;
		HRESULT hr = m_Pointer->SetDepthStencilSurface( surface );
		GraphicsException::CheckHResult( hr );
	}

	Surface^ Device::GetBackBuffer( int swapChain, int backBuffer )
	{
		IDirect3DSurface9* buffer;

		HRESULT hr = m_Pointer->GetBackBuffer( swapChain, backBuffer, D3DBACKBUFFER_TYPE_MONO, &buffer );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( buffer );
	}

	bool Device::IsQuerySupported( QueryType type )
	{
		HRESULT hr = m_Pointer->CreateQuery( static_cast<D3DQUERYTYPE>( type ), NULL );
		if( hr == D3DERR_NOTAVAILABLE )
			return false;
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return false;

		return true;
	}

	Capabilities Device::GetDeviceCaps()
	{
		D3DCAPS9 caps;
		HRESULT hr = m_Pointer->GetDeviceCaps( &caps );
		GraphicsException::CheckHResult( hr );

		return Capabilities( caps );
	}

	int Device::AvailableTextureMem::get()
	{
		return m_Pointer->GetAvailableTextureMem();
	}

	int Device::ValidateDevice()
	{
		DWORD passCount = 0;

		HRESULT hr = m_Pointer->ValidateDevice( &passCount );
		GraphicsException::CheckHResult( hr );

		return passCount;
	}

	bool Device::ShowCursor::get()
	{
		BOOL prev = m_Pointer->ShowCursor( true );
		m_Pointer->ShowCursor( prev );

		return prev > 0;
	}

	void Device::ShowCursor::set( bool value )
	{
		m_Pointer->ShowCursor( value );
	}

	bool Device::SoftwareVertexProcessing::get()
	{
		return m_Pointer->GetSoftwareVertexProcessing() > 0;
	}

	void Device::SoftwareVertexProcessing::set( bool value )
	{
		HRESULT hr = m_Pointer->SetSoftwareVertexProcessing( value );
		GraphicsException::CheckHResult( hr );
	}

	Surface^ Device::GetDepthStencilSurface()
	{
		IDirect3DSurface9* surface;

		HRESULT hr = m_Pointer->GetDepthStencilSurface( &surface );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( surface );
	}

	SlimDX::Direct3D::Viewport Device::Viewport::get()
	{
		SlimDX::Direct3D::Viewport viewport;
		HRESULT hr = m_Pointer->GetViewport( reinterpret_cast<D3DVIEWPORT9*>( &viewport ) );
		GraphicsException::CheckHResult( hr );

		return viewport;
	}

	void Device::Viewport::set( SlimDX::Direct3D::Viewport value )
	{
		HRESULT hr = m_Pointer->SetViewport( reinterpret_cast<const D3DVIEWPORT9*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::ScissorRect::set(Drawing::Rectangle rect)
	{
		RECT scissorRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = m_Pointer->SetScissorRect(&scissorRect);
		GraphicsException::CheckHResult(hr);
	}

	Drawing::Rectangle Device::ScissorRect::get()
	{
		RECT scissorRect;		// Scissor rectangle.

		HRESULT hr = m_Pointer->GetScissorRect(&scissorRect);
		GraphicsException::CheckHResult(hr);

		return Utils::ConvertRect(scissorRect);
	}

	Surface^ Device::GetRenderTarget( int index )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = m_Pointer->GetRenderTarget( index, &surface );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( surface );
	}

	generic<typename T>
	T Device::GetRenderState( RenderState state )
	{
		DWORD value = 0;
		HRESULT hr = m_Pointer->GetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), &value );
		GraphicsException::CheckHResult( hr );

		return (T) value;
	}
	
	int Device::GetRenderState( RenderState state )
	{
		return GetRenderState<int>( state );
	}

	void Device::GetStreamSource( int stream, [Out] VertexBuffer^% streamData, [Out] int% offsetBytes, [Out] int% stride )
	{
		IDirect3DVertexBuffer9* localVb;
		UINT localOffset, localStride;

		HRESULT hr = m_Pointer->GetStreamSource( stream, &localVb, &localOffset, &localStride );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			streamData = nullptr;
			offsetBytes = 0;
			stride = 0;
			return;
		}

		streamData = gcnew VertexBuffer( localVb );
		offsetBytes = localOffset;
		stride = localStride;
	}

	int Device::GetStreamSourceFreq( int stream )
	{
		UINT localFreq = 0;

		HRESULT hr = m_Pointer->GetStreamSourceFreq( stream, &localFreq );
		GraphicsException::CheckHResult( hr );
		
		return localFreq;
	}

	SwapChain^ Device::GetSwapChain( int swapChainIndex )
	{
		IDirect3DSwapChain9* swapChain;

		HRESULT hr = m_Pointer->GetSwapChain( swapChainIndex, &swapChain );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew SwapChain( swapChain );
	}

	IndexBuffer^ Device::GetIndices()
	{
		IDirect3DIndexBuffer9* indices;

		HRESULT hr = m_Pointer->GetIndices( &indices );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew IndexBuffer( indices );
	}

	void Device::SetIndices( IndexBuffer^ indices )
	{
		HRESULT hr;
		if( indices != nullptr )
			 hr = m_Pointer->SetIndices( indices->IbPointer );
		else
			hr = m_Pointer->SetIndices( NULL );

		GraphicsException::CheckHResult( hr );
	}

	void Device::ProcessVertices( int sourceStartIndex, int destIndex, int vertexCount, VertexBuffer^ destBuffer,
		SlimDX::Direct3D9::VertexDeclaration^ vertexDecl, LockFlags flags )
	{
		IDirect3DVertexBuffer9* vb = destBuffer->VbPointer;
		IDirect3DVertexDeclaration9* decl = vertexDecl != nullptr ? vertexDecl->InternalPointer : NULL;

		HRESULT hr = m_Pointer->ProcessVertices( sourceStartIndex, destIndex, vertexCount, vb, decl, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetVertexShaderConstant( int startRegister, array<bool>^ data, int offset, int count )
	{
		array<BOOL>^ boolData = gcnew array<BOOL>( data->Length );
		data->CopyTo( boolData, data->Length );
		pin_ptr<BOOL> pinnedData = &boolData[0];

		Utils::CheckArrayBounds( data, offset, count );
		HRESULT hr = m_Pointer->SetVertexShaderConstantB( startRegister, pinnedData + offset, count );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetVertexShaderConstant( int startRegister, array<float>^ data, int offset, int count )
	{
		pin_ptr<float> pinnedData = &data[0];

		Utils::CheckArrayBounds( data, offset, count );
		HRESULT hr = m_Pointer->SetVertexShaderConstantF( startRegister, pinnedData + offset, count );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetVertexShaderConstant( int startRegister, array<int>^ data, int offset, int count )
	{
		pin_ptr<int> pinnedData = &data[0];

		Utils::CheckArrayBounds( data, offset, count );
		HRESULT hr = m_Pointer->SetVertexShaderConstantI( startRegister, pinnedData + offset, count );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetPixelShaderConstant( int startRegister, array<bool>^ data, int offset, int count )
	{
		array<BOOL>^ boolData = gcnew array<BOOL>( data->Length );
		data->CopyTo( boolData, data->Length );
		pin_ptr<BOOL> pinnedData = &boolData[0];

		Utils::CheckArrayBounds( data, offset, count );
		HRESULT hr = m_Pointer->SetPixelShaderConstantB( startRegister, pinnedData + offset, count );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetPixelShaderConstant( int startRegister, array<float>^ data, int offset, int count )
	{
		pin_ptr<float> pinnedData = &data[0];

		Utils::CheckArrayBounds( data, offset, count );
		HRESULT hr = m_Pointer->SetPixelShaderConstantF( startRegister, pinnedData + offset, count );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetPixelShaderConstant( int startRegister, array<int>^ data, int offset, int count )
	{
		pin_ptr<int> pinnedData = &data[0];

		Utils::CheckArrayBounds( data, offset, count );
		HRESULT hr = m_Pointer->SetPixelShaderConstantI( startRegister, pinnedData + offset, count );
		GraphicsException::CheckHResult( hr );
	}

	void Device::StretchRect( Surface^ source, System::Drawing::Rectangle sourceRect, Surface^ dest,
		System::Drawing::Rectangle destRect, TextureFilter filter )
	{
		RECT nativeSourceRect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };
		RECT nativeDestRect = { destRect.Left, destRect.Top, destRect.Right, destRect.Bottom };

		HRESULT hr = m_Pointer->StretchRect( source->SurfacePointer, &nativeSourceRect, dest->SurfacePointer,
			&nativeDestRect, static_cast<D3DTEXTUREFILTERTYPE>( filter ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::UpdateSurface( Surface^ source, System::Drawing::Rectangle sourceRect,
		Surface^ dest, System::Drawing::Point destPoint )
	{
		RECT nativeSourceRect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };
		POINT nativeDestPoint = { destPoint.X, destPoint.Y };

		HRESULT hr = m_Pointer->UpdateSurface( source->SurfacePointer, &nativeSourceRect,
			dest->SurfacePointer, &nativeDestPoint );
		GraphicsException::CheckHResult( hr );
	}

	void Device::UpdateTexture( BaseTexture^ sourceTexture, BaseTexture^ destTexture )
	{
		HRESULT hr = m_Pointer->UpdateTexture( sourceTexture->BaseTexturePointer, destTexture->BaseTexturePointer );
		GraphicsException::CheckHResult( hr );
	}

	void Device::ColorFill( Surface^ destSurface, System::Drawing::Rectangle destRect, int color )
	{
		RECT nativeDestRect = { destRect.Left, destRect.Top, destRect.Right, destRect.Bottom };

		HRESULT hr = m_Pointer->ColorFill( destSurface->SurfacePointer, &nativeDestRect, static_cast<D3DCOLOR>( color ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::ColorFill( Surface^ destSurface, System::Drawing::Rectangle destRect, System::Drawing::Color color )
	{
		ColorFill( destSurface, destRect, color.ToArgb() );
	}

	void Device::BeginStateBlock()
	{
		HRESULT hr = m_Pointer->BeginStateBlock();
		GraphicsException::CheckHResult( hr );
	}

	StateBlock^ Device::EndStateBlock()
	{
		IDirect3DStateBlock9* stateBlock;
		HRESULT hr = m_Pointer->EndStateBlock( &stateBlock );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew StateBlock( stateBlock );
	}

	int Device::SwapChainCount::get()
	{
		return m_Pointer->GetNumberOfSwapChains();
	}

	float Device::NPatchMode::get()
	{
		return m_Pointer->GetNPatchMode();
	}

	void Device::NPatchMode::set( float value )
	{
		HRESULT hr = m_Pointer->SetNPatchMode( value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawTriPatch( int handle, array<float>^ numSegments, TriPatchInfo info )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = m_Pointer->DrawTriPatch( handle, pinnedSegments, reinterpret_cast<D3DTRIPATCH_INFO*>( &info ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawTriPatch( int handle, array<float>^ numSegments )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = m_Pointer->DrawTriPatch( handle, pinnedSegments, NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawRectPatch( int handle, array<float>^ numSegments, RectPatchInfo info )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = m_Pointer->DrawRectPatch( handle, pinnedSegments, reinterpret_cast<D3DRECTPATCH_INFO*>( &info ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawRectPatch( int handle, array<float>^ numSegments )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = m_Pointer->DrawRectPatch( handle, pinnedSegments, NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DeletePatch( int handle )
	{
		HRESULT hr = m_Pointer->DeletePatch( handle );
		GraphicsException::CheckHResult( hr );
	}

	DisplayMode Device::GetDisplayMode( int swapChain )
	{
		DisplayMode displayMode;

		HRESULT hr = m_Pointer->GetDisplayMode( swapChain, reinterpret_cast<D3DDISPLAYMODE*>( &displayMode ) );
		GraphicsException::CheckHResult( hr );
		
		return displayMode;
	}

	void Device::EvictManagedResources()
	{
		HRESULT hr = m_Pointer->EvictManagedResources();
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetDialogBoxMode( bool enableDialogs )
	{
		HRESULT hr = m_Pointer->SetDialogBoxMode( enableDialogs );
		GraphicsException::CheckHResult( hr );
	}

	void Device::LightEnable( int lightIndex, bool enable )
	{
		HRESULT hr = m_Pointer->LightEnable( lightIndex, enable );
		GraphicsException::CheckHResult( hr );
	}

	bool Device::GetLightEnable( int lightIndex )
	{
		BOOL enabled = FALSE;
		HRESULT hr = m_Pointer->GetLightEnable( lightIndex, &enabled );
		GraphicsException::CheckHResult( hr );

		return enabled > 0;
	}

	void Device::SetLight( int lightIndex, Light lightData )
	{
		HRESULT hr = m_Pointer->SetLight( lightIndex, reinterpret_cast<const D3DLIGHT9*>( &lightData ) );
		GraphicsException::CheckHResult( hr );
	}

	Light Device::GetLight( int lightIndex )
	{
		Light light;
		HRESULT hr = m_Pointer->GetLight( lightIndex, reinterpret_cast<D3DLIGHT9*>( &light ) );
		GraphicsException::CheckHResult( hr );
		
		return light;
	}

	void Device::SetCursor( Cursor^ cursor, bool addWaterMark )
	{
		IDirect3DSurface9 *cursorSurface = NULL;
		ICONINFO iconInfo = {0};
		HRESULT hr;
		BITMAP bmp;
		BITMAPINFO bmi = {0};
		bool bwCursor;
		int width = 0;
		int heightSrc = 0;
		int heightDest = 0;
		COLORREF *arrayMask = NULL;
		COLORREF *arrayColor = NULL;
		COLORREF color;
		COLORREF mask;
		HDC hdcColor = NULL;
		HDC hdcScreen = NULL;
		HDC hdcMask = NULL;
		HGDIOBJ oldObject;
		DWORD *bitmap;

		if( !GetIconInfo( static_cast<HICON>( cursor->Handle.ToPointer() ), &iconInfo ) )
			return;

		if( GetObject( static_cast<HGDIOBJ>( iconInfo.hbmMask ), sizeof( BITMAP ), static_cast<LPVOID>( &bmp ) ) == 0 )
		{
			if( iconInfo.hbmMask != NULL )
				DeleteObject( iconInfo.hbmMask );
			if( iconInfo.hbmColor != NULL )
				DeleteObject( iconInfo.hbmColor );
			return;
		}

		width = bmp.bmWidth;
		heightSrc = bmp.bmHeight;

		if( iconInfo.hbmColor == NULL )
		{
			bwCursor = true;
			heightDest = heightSrc / 2;
		}
		else
		{
			bwCursor = false;
			heightDest = heightSrc;
		}

		if( FAILED( hr = m_Pointer->CreateOffscreenPlainSurface( width, heightDest, D3DFMT_A8R8G8B8,
			D3DPOOL_SCRATCH, &cursorSurface, NULL ) ) )
		{
			if( iconInfo.hbmMask != NULL )
				DeleteObject( iconInfo.hbmMask );
			if( iconInfo.hbmColor != NULL )
				DeleteObject( iconInfo.hbmColor );
			GraphicsException::CheckHResult( hr );
			return;
		}

		arrayMask = new DWORD[width * heightSrc];

		bmi.bmiHeader.biSize = sizeof( bmi.bmiHeader );
		bmi.bmiHeader.biWidth = width;
		bmi.bmiHeader.biHeight = heightSrc;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;

		hdcScreen = GetDC( NULL );
		hdcMask = CreateCompatibleDC( hdcScreen );
		if( hdcMask == NULL )
		{
			if( iconInfo.hbmMask != NULL )
				DeleteObject( iconInfo.hbmMask );
			if( iconInfo.hbmColor != NULL )
				DeleteObject( iconInfo.hbmColor );
			if( hdcScreen != NULL )
				ReleaseDC( NULL, hdcScreen );
			if( arrayMask != NULL )
				delete[] arrayMask;
			if( cursorSurface != NULL )
				cursorSurface->Release();
			return;
		}

		oldObject = SelectObject( hdcMask, iconInfo.hbmMask );
		GetDIBits( hdcMask, iconInfo.hbmMask, 0, heightSrc, arrayMask, &bmi, DIB_RGB_COLORS );
		SelectObject( hdcMask, oldObject );

		if( !bwCursor )
		{
			arrayColor = new DWORD[width * heightDest];
			hdcColor = CreateCompatibleDC( hdcScreen );
			if( hdcColor == NULL )
			{
				if( iconInfo.hbmMask != NULL )
					DeleteObject( iconInfo.hbmMask );
				if( iconInfo.hbmColor != NULL )
					DeleteObject( iconInfo.hbmColor );
				if( hdcScreen != NULL )
					ReleaseDC( NULL, hdcScreen );
				if( hdcMask != NULL )
					DeleteDC( hdcMask );
				if( hdcColor != NULL )
					DeleteDC( hdcColor );
				if( arrayColor != NULL )
					delete[] arrayColor;
				if( arrayMask != NULL )
					delete[] arrayMask;
				if( cursorSurface != NULL )
					cursorSurface->Release();
				return;
			}

			SelectObject( hdcColor, iconInfo.hbmColor );
			GetDIBits( hdcColor, iconInfo.hbmColor, 0, heightDest, arrayColor, &bmi, DIB_RGB_COLORS );
		}

		D3DLOCKED_RECT lr;
		cursorSurface->LockRect( &lr, NULL, 0 );
		bitmap = static_cast<DWORD*>( lr.pBits );

		for( int y = 0; y < heightDest; y++ )
		{
			for( int x = 0; x < width; x++ )
			{
				if( bwCursor )
				{
					color = arrayMask[width * ( heightDest - 1 - y ) + x];
					mask = arrayMask[width * ( heightSrc - 1 - y ) + x];
				}
				else
				{
					color = arrayColor[width * ( heightDest - 1 - y ) + x];
					mask = arrayMask[width * ( heightDest - 1 - y ) + x];
				}

				if( mask == 0 )
					bitmap[width * y + x] = 0xff000000 | color;
				else
					bitmap[width * y + x] = 0x00000000;

				if( addWaterMark && x < 12 && y < 5 )
				{
					const WORD wMask[5] = { 0xccc0, 0xa2a0, 0xa4a0, 0xa2a0, 0xccc0 };
					if( wMask[y] & ( 1 << ( 15 - x ) ) )
						bitmap[width * y + x] |= 0xff808080;
				}
			}
		}

		cursorSurface->UnlockRect();

		hr = m_Pointer->SetCursorProperties( iconInfo.xHotspot, iconInfo.yHotspot, cursorSurface );

		if( iconInfo.hbmMask != NULL )
			DeleteObject( iconInfo.hbmMask );
		if( iconInfo.hbmColor != NULL )
			DeleteObject( iconInfo.hbmColor );
		if( hdcScreen != NULL )
			ReleaseDC( NULL, hdcScreen );
		if( hdcMask != NULL )
			DeleteDC( hdcMask );
		if( hdcColor != NULL )
			DeleteDC( hdcColor );
		if( arrayColor != NULL )
			delete[] arrayColor;
		if( arrayMask != NULL )
			delete[] arrayMask;
		if( cursorSurface != NULL )
			cursorSurface->Release();
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetCursorPosition( int x, int y, bool immediateUpdate )
	{
		DWORD flags = immediateUpdate ? D3DCURSOR_IMMEDIATE_UPDATE : 0;
		m_Pointer->SetCursorPosition( x, y, flags );
	}

	void Device::SetCursorProperties( int hotspotX, int hotspotY, Surface^ cursorBitmap )
	{
		IDirect3DSurface9* surface = cursorBitmap != nullptr ? cursorBitmap->SurfacePointer : NULL;
		HRESULT hr = m_Pointer->SetCursorProperties( hotspotX, hotspotY, surface );
		GraphicsException::CheckHResult( hr );
	}

	void Device::CurrentTexturePalette::set( int value )
	{
		HRESULT hr = m_Pointer->SetCurrentTexturePalette( value );
		GraphicsException::CheckHResult( hr );
	}

	int Device::CurrentTexturePalette::get()
	{
		unsigned int palette = 0;
		HRESULT hr = m_Pointer->GetCurrentTexturePalette( &palette );
		GraphicsException::CheckHResult( hr );

		return (int) palette;
	}

	VertexShader^ Device::GetVertexShader()
	{
		IDirect3DVertexShader9* vs;
		HRESULT hr = m_Pointer->GetVertexShader( &vs );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew VertexShader( vs );
	}

	PixelShader^ Device::GetPixelShader()
	{
		IDirect3DPixelShader9* ps;
		HRESULT hr = m_Pointer->GetPixelShader( &ps );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew PixelShader( ps );
	}

	DriverLevel Device::DriverLevel::get()
	{
		return static_cast<SlimDX::Direct3D9::DriverLevel>( D3DXGetDriverLevel( m_Pointer ) );
	}

	String^ Device::VertexShaderProfile::get()
	{
		LPCSTR profile = D3DXGetVertexShaderProfile( m_Pointer );
		return gcnew String( profile );
	}

	String^ Device::PixelShaderProfile::get()
	{
		LPCSTR profile = D3DXGetPixelShaderProfile( m_Pointer );
		return gcnew String( profile );
	}

	void Device::SetR2VBMode( bool enableR2VB )
	{
		SetRenderState( RenderState::PointSize, static_cast<int>( r2vbGlbEnable_Set( enableR2VB ) ) );
	}

	void Device::BindRenderTargetToVertexStream( R2VBSampler sampler, Texture^ r2vbTarget, int stream, int stride, VertexBuffer^ dummyVb )
	{
		SetTexture( D3DDMAPSAMPLER, r2vbTarget );
		if( FAILED( GraphicsException::LastError ) )
			return;

		SetRenderState( RenderState::PointSize, static_cast<int>( r2vbVStrm2SmpMap_Set( stream, static_cast<int>( sampler ) ) ) );
		if( FAILED( GraphicsException::LastError ) )
			return;

		SetStreamSource( stream, dummyVb, 0, stride );
		if( FAILED( GraphicsException::LastError ) )
			return;
	}

	void Device::RestoreVertexStream( int stream )
	{
		SetRenderState( RenderState::PointSize, static_cast<int>( r2vbVStrm2SmpMap_Set( stream, R2VB_VSMP_OVR_DIS ) ) );
		if( FAILED( GraphicsException::LastError ) )
			return;

		SetTexture( D3DDMAPSAMPLER, nullptr );
	}

	void Device::SetClipPlane( int index, Plane clipPlane )
	{
		HRESULT hr = m_Pointer->SetClipPlane( index, reinterpret_cast<const float*>( &clipPlane ) );
		GraphicsException::CheckHResult( hr );
	}

	Plane Device::GetClipPlane( int index )
	{
		Plane plane;
		HRESULT hr = m_Pointer->GetClipPlane( index, reinterpret_cast<float*>( &plane ) );
		GraphicsException::CheckHResult( hr );

		return plane;
	}

	void Device::GetFrontBufferData( int swapChain, Surface^ destSurface )
	{
		IDirect3DSurface9* surface = destSurface != nullptr ? destSurface->SurfacePointer : NULL;
		HRESULT hr = m_Pointer->GetFrontBufferData( swapChain, surface );
		GraphicsException::CheckHResult( hr );
	}

	void Device::GetRenderTargetData( Surface^ renderTarget, Surface^ destSurface )
	{
		IDirect3DSurface9* target = renderTarget != nullptr	? renderTarget->SurfacePointer : NULL;
		IDirect3DSurface9* dest = destSurface != nullptr ? destSurface->SurfacePointer : NULL;
		HRESULT hr = m_Pointer->GetRenderTargetData( target, dest );
		GraphicsException::CheckHResult( hr );
	}
}
}
