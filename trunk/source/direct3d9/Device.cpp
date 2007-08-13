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
	//quick utility function
	void ConvertPresentParams( PresentParameters^ presentParams, D3DPRESENT_PARAMETERS& d3dpp )
	{
		d3dpp.AutoDepthStencilFormat = (D3DFORMAT) presentParams->AutoDepthStencilFormat;
		d3dpp.BackBufferCount = presentParams->BackBufferCount;
		d3dpp.BackBufferFormat = (D3DFORMAT) presentParams->BackBufferFormat;
		d3dpp.BackBufferHeight = presentParams->BackBufferHeight;
		d3dpp.BackBufferWidth = presentParams->BackBufferWidth;
		d3dpp.EnableAutoDepthStencil = presentParams->EnableAutoDepthStencil;
		d3dpp.Flags = (DWORD) presentParams->PresentFlags;
		d3dpp.FullScreen_RefreshRateInHz = presentParams->FullScreenRefreshRateInHz;
		d3dpp.hDeviceWindow = (HWND) presentParams->DeviceWindowHandle.ToPointer();
		d3dpp.MultiSampleQuality = presentParams->MultiSampleQuality;
		d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE) presentParams->MultiSample;
		d3dpp.PresentationInterval = (UINT) presentParams->PresentationInterval;
		d3dpp.SwapEffect = (D3DSWAPEFFECT) presentParams->SwapEffect;
		d3dpp.Windowed = presentParams->Windowed;
	}

	PresentParameters::PresentParameters()
	{
		//set sane defaults
		BackBufferWidth = 640;
		BackBufferHeight = 480;
		BackBufferFormat = Format::X8R8G8B8;
		BackBufferCount = 1;

		MultiSample = MultiSampleType::None;
		MultiSampleQuality = 0;

		SwapEffect = SlimDX::Direct3D9::SwapEffect::Discard;
		DeviceWindowHandle = IntPtr::Zero;
		Windowed = true;
		EnableAutoDepthStencil = true;
		AutoDepthStencilFormat = Format::D24S8;
		PresentFlags = SlimDX::Direct3D9::PresentFlags::None;

		FullScreenRefreshRateInHz = 0;
		PresentationInterval = PresentInterval::Immediate;
	}

	Device::Device( IDirect3DDevice9* device ) : DirectXObject( device )
	{
		if( device == NULL )
			throw gcnew ArgumentNullException( "device" );
	}

	Device::Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParams )
	{
		IDirect3DDevice9* device;
		D3DPRESENT_PARAMETERS d3dpp;

		ConvertPresentParams( presentParams, d3dpp );
		HRESULT hr = Direct3D::InternalPointer->CreateDevice( adapter, (D3DDEVTYPE) deviceType, (HWND) controlHandle.ToPointer(), 
			(DWORD) createFlags, (D3DPRESENT_PARAMETERS*) &d3dpp, &device );
		GraphicsException::CheckHResult( hr );

		m_Pointer = device;
	}

	void Device::Indices::set( IndexBuffer^ value )
	{
		m_Indices = value;

		HRESULT hr;
		if( value != nullptr )
			 hr = m_Pointer->SetIndices( value->IbPointer );
		else
			hr = m_Pointer->SetIndices( NULL );

		GraphicsException::CheckHResult( hr );
	}

	void Device::VertexFormat::set( SlimDX::Direct3D9::VertexFormat value )
	{
		m_VertexFormat = value;
		HRESULT hr = m_Pointer->SetFVF( (DWORD) value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::VertexDeclaration::set( SlimDX::Direct3D9::VertexDeclaration^ value )
	{
		m_VertexDecl = value;

		HRESULT hr;
		if( value != nullptr )
			hr = m_Pointer->SetVertexDeclaration( value->InternalPointer );
		else
			hr = m_Pointer->SetVertexDeclaration( NULL );

		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount )
	{
		HRESULT hr = m_Pointer->DrawPrimitive( (D3DPRIMITIVETYPE) primitiveType, startIndex, primitiveCount );
		GraphicsException::CheckHResult( hr );
	}

	generic<typename T>
	void Device::DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data )
	{
		pin_ptr<T> pinned_data = &data[startIndex];

		HRESULT hr = m_Pointer->DrawPrimitiveUP( (D3DPRIMITIVETYPE) primitiveType, primitiveCount,
			pinned_data, Marshal::SizeOf( T::typeid ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
		int numVertices, int startIndex, int primCount )
	{
		HRESULT hr = m_Pointer->DrawIndexedPrimitive( (D3DPRIMITIVETYPE) primitiveType, baseVertexIndex,
			minVertexIndex, numVertices, startIndex, primCount );
		GraphicsException::CheckHResult( hr );
	}

	generic<typename S, typename T>
	void Device::DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minVertexIndex, int numVertices, int primitiveCount,
		array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride )
	{
		pin_ptr<S> pinnedIndices = &indexData[0];
		pin_ptr<T> pinnedVertices = &vertexData[0];

		HRESULT hr = m_Pointer->DrawIndexedPrimitiveUP( (D3DPRIMITIVETYPE) primitiveType, minVertexIndex, numVertices,
			primitiveCount, pinnedIndices, (D3DFORMAT) indexDataFormat, pinnedVertices, vertexStride );
		GraphicsException::CheckHResult( hr );
	}

	void Device::Clear( ClearFlags clearFlags, int color, float zdepth, int stencil )
	{
		HRESULT hr = m_Pointer->Clear( 0, 0, (DWORD) clearFlags, (D3DCOLOR) color, zdepth, stencil );
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

		hr = swapChain->Present( 0, 0, 0, 0, (DWORD) flags );
		GraphicsException::CheckHResult( hr );

		hr = swapChain->Release();
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderState( RenderState state, int value )
	{
		HRESULT hr = m_Pointer->SetRenderState( (D3DRENDERSTATETYPE) state, value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderState( RenderState state, bool value )
	{
		BOOL boolValue = value ? TRUE : FALSE;
		HRESULT hr = m_Pointer->SetRenderState( (D3DRENDERSTATETYPE) state, boolValue );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderState( RenderState state, float value )
	{
		HRESULT hr = m_Pointer->SetRenderState( (D3DRENDERSTATETYPE) state, *(DWORD*) &value );
		GraphicsException::CheckHResult( hr );
	}

	generic<typename T>
	void Device::SetRenderState( RenderState state, T value )
	{
		SetRenderState( state, (int) value );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, int value )
	{
		HRESULT hr = m_Pointer->SetTextureStageState( stage, (D3DTEXTURESTAGESTATETYPE) type, value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, TextureOperation texOp )
	{
		SetTextureStageState( stage, type, (int) texOp );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, TextureArgument texArg )
	{
		SetTextureStageState( stage, type, (int) texArg );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, TextureTransform texTransform )
	{
		SetTextureStageState( stage, type, (int) texTransform );
	}

	void Device::SetTextureStageState( int stage, TextureStage type, float value )
	{
		SetTextureStageState( stage, type, *(int*) &value );
	}

	void Device::SetSamplerState( int sampler, SamplerState type, int value )
	{
		HRESULT hr = m_Pointer->SetSamplerState( sampler, (D3DSAMPLERSTATETYPE) type, value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetSamplerState( int sampler, SamplerState type, TextureAddress texAddr )
	{
		SetSamplerState( sampler, type, (int) texAddr );
	}

	void Device::SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter )
	{
		SetSamplerState( sampler, type, (int) texFilter );
	}

	void Device::SetTransform( TransformState state, Matrix value )
	{
		HRESULT hr = m_Pointer->SetTransform( (D3DTRANSFORMSTATETYPE) state, (const D3DMATRIX*) &value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::MultiplyTransform( TransformState state, Matrix value )
	{
		HRESULT hr = m_Pointer->MultiplyTransform( (D3DTRANSFORMSTATETYPE) state, (const D3DMATRIX*) &value );
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

		HRESULT hr = m_Pointer->GetMaterial( (D3DMATERIAL9*) &material );
		GraphicsException::CheckHResult( hr );

		return material;
	}

	void Device::Material::set( SlimDX::Direct3D9::Material material )
	{
		HRESULT hr = m_Pointer->SetMaterial( (const D3DMATERIAL9*) &material );
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
		return (CooperativeLevel) hr;
	}

	void Device::Reset( PresentParameters^ presentParams )
	{
		D3DPRESENT_PARAMETERS d3dpp;

		ConvertPresentParams( presentParams, d3dpp );
		HRESULT hr = m_Pointer->Reset( &d3dpp );
		GraphicsException::CheckHResult( hr );
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
		HRESULT hr = m_Pointer->CreateQuery( (D3DQUERYTYPE) type, NULL );
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
		HRESULT hr = m_Pointer->GetViewport( (D3DVIEWPORT9*) &viewport );
		GraphicsException::CheckHResult( hr );

		return viewport;
	}

	void Device::Viewport::set( SlimDX::Direct3D::Viewport value )
	{
		HRESULT hr = m_Pointer->SetViewport( (const D3DVIEWPORT9*) &value );
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
		HRESULT hr = m_Pointer->GetRenderState( (D3DRENDERSTATETYPE) state, &value );
		GraphicsException::CheckHResult( hr );

		return (T) value;
	}
	
	int Device::GetRenderState( RenderState state )
	{
		return GetRenderState<int>( state );
	}

	bool Device::GetSoftwareVertexProcessing()
	{
		return m_Pointer->GetSoftwareVertexProcessing() > 0;
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

	void Device::ProcessVertices( int sourceStartIndex, int destIndex, int vertexCount, VertexBuffer^ destBuffer,
		SlimDX::Direct3D9::VertexDeclaration^ vertexDecl, LockFlags flags )
	{
		IDirect3DVertexBuffer9* vb = destBuffer->VbPointer;
		IDirect3DVertexDeclaration9* decl = vertexDecl != nullptr ? vertexDecl->InternalPointer : NULL;

		HRESULT hr = m_Pointer->ProcessVertices( sourceStartIndex, destIndex, vertexCount, vb, decl, (DWORD) flags );
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
			&nativeDestRect, (D3DTEXTUREFILTERTYPE) filter );
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

		HRESULT hr = m_Pointer->ColorFill( destSurface->SurfacePointer, &nativeDestRect, (D3DCOLOR) color );
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

		HRESULT hr = m_Pointer->DrawTriPatch( handle, pinnedSegments, (D3DTRIPATCH_INFO*) &info );
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

		HRESULT hr = m_Pointer->DrawRectPatch( handle, pinnedSegments, (D3DRECTPATCH_INFO*) &info );
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

		HRESULT hr = m_Pointer->GetDisplayMode( swapChain, (D3DDISPLAYMODE*) &displayMode );
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
		HRESULT hr = m_Pointer->SetLight( lightIndex, (D3DLIGHT9*) &lightData );
		GraphicsException::CheckHResult( hr );
	}

	Light Device::GetLight( int lightIndex )
	{
		Light light;
		HRESULT hr = m_Pointer->GetLight( lightIndex, (D3DLIGHT9*) &light );
		GraphicsException::CheckHResult( hr );
		
		return light;
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
}
}
