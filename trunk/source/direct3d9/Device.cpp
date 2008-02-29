/*
* Copyright (c) 2007-2008 SlimDX Group
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
#include "../ComObject.h"
#include "../Utilities.h"
#include "../StackAlloc.h"
#include "../Viewport.h"

#include "Direct3D9NotInitializedException.h"

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

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

namespace SlimDX
{
namespace Direct3D9
{
	Device::Device( IDirect3DDevice9* pointer )
	{
		Construct( pointer );
	}

	Device::Device( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Device::Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParameters )
	{
		IDirect3DDevice9* device;
		D3DPRESENT_PARAMETERS d3dpp;

		if( Direct3D::InternalPointer == NULL )
			throw gcnew Direct3D9NotInitializedException();

		d3dpp = presentParameters->ToUnmanaged();
		HRESULT hr = Direct3D::InternalPointer->CreateDevice( adapter,
			static_cast<D3DDEVTYPE>( deviceType ),
			static_cast<HWND>( controlHandle.ToPointer() ), 
			static_cast<DWORD>( createFlags ),
			reinterpret_cast<D3DPRESENT_PARAMETERS*>( &d3dpp ),
			&device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(device);
	}

	Device^ Device::FromPointer( IDirect3DDevice9* pointer )
	{
		Device^ tableEntry = safe_cast<Device^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Device( pointer );
	}

	Device^ Device::FromPointer( IntPtr pointer )
	{
		Device^ tableEntry = safe_cast<Device^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Device( pointer );
	}

	void Device::VertexFormat::set( SlimDX::Direct3D9::VertexFormat value )
	{
		HRESULT hr = InternalPointer->SetFVF( static_cast<DWORD>( value ) );
		RECORD_D3D9( hr );
	}

	SlimDX::Direct3D9::VertexFormat Device::VertexFormat::get()
	{
		DWORD fvf = 0;
		HRESULT hr = InternalPointer->GetFVF( &fvf );
		RECORD_D3D9( hr );

		return static_cast<SlimDX::Direct3D9::VertexFormat>( fvf );
	}
	
	void Device::VertexDeclaration::set( SlimDX::Direct3D9::VertexDeclaration^ value )
	{
		HRESULT hr;
		if( value != nullptr )
			hr = InternalPointer->SetVertexDeclaration( value->InternalPointer );
		else
			hr = InternalPointer->SetVertexDeclaration( NULL );

		RECORD_D3D9( hr );
	}

	SlimDX::Direct3D9::VertexDeclaration^ Device::VertexDeclaration::get()
	{
		IDirect3DVertexDeclaration9* decl;
		HRESULT hr = InternalPointer->GetVertexDeclaration( &decl );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return SlimDX::Direct3D9::VertexDeclaration::FromPointer( decl );
	}

	Result Device::DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount )
	{
		HRESULT hr = InternalPointer->DrawPrimitive( static_cast<D3DPRIMITIVETYPE>( primitiveType ), startIndex, primitiveCount );
		return RECORD_D3D9( hr );
	}

	generic<typename T>
	Result Device::DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data )
	{
		pin_ptr<T> pinned_data = &data[startIndex];

		HRESULT hr = InternalPointer->DrawPrimitiveUP( static_cast<D3DPRIMITIVETYPE>( primitiveType ), primitiveCount,
			pinned_data, Marshal::SizeOf( T::typeid ) );
		return RECORD_D3D9( hr );
	}

	Result Device::DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
		int numVertices, int startIndex, int primCount )
	{
		HRESULT hr = InternalPointer->DrawIndexedPrimitive( static_cast<D3DPRIMITIVETYPE>( primitiveType ), baseVertexIndex,
			minVertexIndex, numVertices, startIndex, primCount );
		return RECORD_D3D9( hr );
	}

	generic<typename S, typename T>
	Result Device::DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minVertexIndex, int numVertices, int primitiveCount,
		array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride )
	{
		pin_ptr<S> pinnedIndices = &indexData[0];
		pin_ptr<T> pinnedVertices = &vertexData[0];

		HRESULT hr = InternalPointer->DrawIndexedPrimitiveUP( static_cast<D3DPRIMITIVETYPE>( primitiveType ), minVertexIndex, numVertices,
			primitiveCount, pinnedIndices, static_cast<D3DFORMAT>( indexDataFormat ), pinnedVertices, vertexStride );
		return RECORD_D3D9( hr );
	}

	Result Device::Clear( ClearFlags clearFlags, Color4 color, float zdepth, int stencil )
	{
		HRESULT hr = InternalPointer->Clear( 0, 0, static_cast<DWORD>( clearFlags ), static_cast<D3DCOLOR>( color.ToArgb() ), zdepth, stencil );
		return RECORD_D3D9( hr );
	}

	Result Device::BeginScene()
	{
		HRESULT hr = InternalPointer->BeginScene();
		return RECORD_D3D9( hr );
	}

	Result Device::EndScene()
	{
		HRESULT hr = InternalPointer->EndScene();
		return RECORD_D3D9( hr );
	}

	Result Device::Present()
	{
		HRESULT hr = InternalPointer->Present( 0, 0, 0, 0 );
		return RECORD_D3D9( hr );
	}

	Result Device::Present( SlimDX::Direct3D9::Present flags )
	{
		IDirect3DSwapChain9* swapChain;

		HRESULT hr = InternalPointer->GetSwapChain( 0, &swapChain );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return Result::Last;

		hr = swapChain->Present( 0, 0, 0, 0, static_cast<DWORD>( flags ) );
		RECORD_D3D9( hr );

		hr = swapChain->Release();
		RECORD_D3D9( hr );

		return Result::Last;
	}

	Result Device::SetRenderState( RenderState state, int value )
	{
		HRESULT hr = InternalPointer->SetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), value );
		return RECORD_D3D9( hr );
	}

	Result Device::SetRenderState( RenderState state, bool value )
	{
		BOOL boolValue = value ? TRUE : FALSE;
		HRESULT hr = InternalPointer->SetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), boolValue );
		return RECORD_D3D9( hr );
	}

	Result Device::SetRenderState( RenderState state, float value )
	{
		DWORD* dwValue = reinterpret_cast<DWORD*>( &value );
		HRESULT hr = InternalPointer->SetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), *dwValue );
		return RECORD_D3D9( hr );
	}

	generic<typename T>
	Result Device::SetRenderState( RenderState state, T value )
	{
		return SetRenderState( state, static_cast<int>( value ) );
	}

	Result Device::SetTextureStageState( int stage, TextureStage type, int value )
	{
		HRESULT hr = InternalPointer->SetTextureStageState( stage, static_cast<D3DTEXTURESTAGESTATETYPE>( type ), value );
		return RECORD_D3D9( hr );
	}

	Result Device::SetTextureStageState( int stage, TextureStage type, TextureOperation texOp )
	{
		return SetTextureStageState( stage, type, static_cast<int>( texOp ) );
	}

	Result Device::SetTextureStageState( int stage, TextureStage type, TextureArgument texArg )
	{
		return SetTextureStageState( stage, type, static_cast<int>( texArg ) );
	}

	Result Device::SetTextureStageState( int stage, TextureStage type, TextureTransform texTransform )
	{
		return SetTextureStageState( stage, type, static_cast<int>( texTransform ) );
	}

	Result Device::SetTextureStageState( int stage, TextureStage type, float value )
	{
		int* dwValue = reinterpret_cast<int*>( &value );
		return SetTextureStageState( stage, type, *dwValue );
	}

	Result Device::SetSamplerState( int sampler, SamplerState type, int value )
	{
		HRESULT hr = InternalPointer->SetSamplerState( sampler, static_cast<D3DSAMPLERSTATETYPE>( type ), value );
		return RECORD_D3D9( hr );
	}

	Result Device::SetSamplerState( int sampler, SamplerState type, float value )
	{
		DWORD* dwValue = reinterpret_cast<DWORD*>( &value );
		HRESULT hr = InternalPointer->SetSamplerState( sampler, static_cast<D3DSAMPLERSTATETYPE>( type ), *dwValue );
		return RECORD_D3D9( hr );
	}

	Result Device::SetSamplerState( int sampler, SamplerState type, TextureAddress textureAddress )
	{
		return SetSamplerState( sampler, type, static_cast<int>( textureAddress ) );
	}

	Result Device::SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter )
	{
		return SetSamplerState( sampler, type, static_cast<int>( texFilter ) );
	}

	Result Device::SetTransform( TransformState state, Matrix value )
	{
		HRESULT hr = InternalPointer->SetTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<const D3DMATRIX*>( &value ) );
		return RECORD_D3D9( hr );
	}
	
	Matrix Device::GetTransform( TransformState state )
	{
		Matrix result;
		HRESULT hr = InternalPointer->GetTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<D3DMATRIX*>( &result ) );
		RECORD_D3D9( hr );
		return result;
	}

	Result Device::SetTransform( int index, Matrix value )
	{
		return SetTransform( static_cast<TransformState>( index + 256 ), value );
	}

	Matrix Device::GetTransform( int index )
	{
		return GetTransform( static_cast<TransformState>( index + 256 ) );
	}

	Result Device::MultiplyTransform( TransformState state, Matrix value )
	{
		HRESULT hr = InternalPointer->MultiplyTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<const D3DMATRIX*>( &value ) );
		return RECORD_D3D9( hr );
	}

	Result Device::SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride )
	{
		IDirect3DVertexBuffer9* vbPointer = streamData != nullptr ? streamData->InternalPointer : NULL;
		HRESULT hr = InternalPointer->SetStreamSource( stream, vbPointer, offsetInBytes, stride );
		return RECORD_D3D9( hr );
	}

	Result Device::SetStreamSourceFrequency( int stream, int frequency )
	{
		HRESULT hr = InternalPointer->SetStreamSourceFreq( stream, frequency );
		return RECORD_D3D9( hr );
	}

	SlimDX::Direct3D9::Material Device::Material::get()
	{
		SlimDX::Direct3D9::Material material;

		HRESULT hr = InternalPointer->GetMaterial( reinterpret_cast<D3DMATERIAL9*>( &material ) );
		RECORD_D3D9( hr );

		return material;
	}

	void Device::Material::set( SlimDX::Direct3D9::Material material )
	{
		HRESULT hr = InternalPointer->SetMaterial( reinterpret_cast<const D3DMATERIAL9*>( &material ) );
		RECORD_D3D9( hr );
	}

	Result Device::TestCooperativeLevel()
	{
		HRESULT hr = InternalPointer->TestCooperativeLevel();
		return Result( hr );
	}

	Result Device::Reset( PresentParameters^ presentParameters )
	{
		D3DPRESENT_PARAMETERS d3dpp;

		d3dpp = presentParameters->ToUnmanaged();
		HRESULT hr = InternalPointer->Reset( &d3dpp );
		RECORD_D3D9( hr );

		presentParameters->BackBufferCount = d3dpp.BackBufferCount;
		presentParameters->BackBufferFormat = static_cast<Format>( d3dpp.BackBufferFormat );
		presentParameters->BackBufferWidth = d3dpp.BackBufferWidth;
		presentParameters->BackBufferHeight = d3dpp.BackBufferHeight;

		return Result::Last;
	}

	Result Device::SetTexture( int sampler, BaseTexture^ texture )
	{
		IDirect3DBaseTexture9* texturePointer = texture != nullptr ? texture->InternalPointer : NULL;
		HRESULT hr = InternalPointer->SetTexture( sampler, texturePointer );
		return RECORD_D3D9( hr );
	}

	Result Device::SetRenderTarget( int rtIndex, Surface^ target )
	{
		IDirect3DSurface9* surfacePointer = target != nullptr ? target->InternalPointer : NULL;
		HRESULT hr = InternalPointer->SetRenderTarget( rtIndex, surfacePointer );
		return RECORD_D3D9( hr );
	}
	
	Result Device::SetPixelShader( PixelShader^ shader )
	{
		IDirect3DPixelShader9 *ptr = shader != nullptr ? shader->InternalPointer : NULL; 
		HRESULT hr = InternalPointer->SetPixelShader( ptr );
		return RECORD_D3D9( hr );
	}
	
	Result Device::SetVertexShader( VertexShader^ shader )
	{
		IDirect3DVertexShader9 *ptr = shader != nullptr ? shader->InternalPointer : NULL; 
		HRESULT hr = InternalPointer->SetVertexShader( ptr );
		return RECORD_D3D9( hr );
	}
	
	Result Device::SetDepthStencilSurface( Surface^ target )
	{	
		IDirect3DSurface9* surface = target != nullptr ? target->InternalPointer : NULL;
		HRESULT hr = InternalPointer->SetDepthStencilSurface( surface );
		return RECORD_D3D9( hr );
	}

	Surface^ Device::GetBackBuffer( int swapChain, int backBuffer )
	{
		IDirect3DSurface9* buffer;

		HRESULT hr = InternalPointer->GetBackBuffer( swapChain, backBuffer, D3DBACKBUFFER_TYPE_MONO, &buffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Surface::FromPointer( buffer );
	}

	bool Device::IsQuerySupported( QueryType type )
	{
		HRESULT hr = InternalPointer->CreateQuery( static_cast<D3DQUERYTYPE>( type ), NULL );
		if( hr == D3DERR_NOTAVAILABLE )
			return false;
		
		if( RECORD_D3D9( hr ).IsFailure )
			return false;

		return true;
	}

	Capabilities Device::GetDeviceCaps()
	{
		D3DCAPS9 caps;
		HRESULT hr = InternalPointer->GetDeviceCaps( &caps );
		RECORD_D3D9( hr );

		return Capabilities( caps );
	}

	int Device::AvailableTextureMemory::get()
	{
		return InternalPointer->GetAvailableTextureMem();
	}

	int Device::ValidateDevice()
	{
		DWORD passCount = 0;

		HRESULT hr = InternalPointer->ValidateDevice( &passCount );
		RECORD_D3D9( hr );

		return passCount;
	}

	bool Device::ShowCursor::get()
	{
		BOOL prev = InternalPointer->ShowCursor( true );
		RECORD_D3D9( InternalPointer->ShowCursor( prev ) );

		return prev > 0;
	}

	void Device::ShowCursor::set( bool value )
	{
		RECORD_D3D9( InternalPointer->ShowCursor( value ) );
	}

	bool Device::SoftwareVertexProcessing::get()
	{
		return InternalPointer->GetSoftwareVertexProcessing() > 0;
	}

	void Device::SoftwareVertexProcessing::set( bool value )
	{
		HRESULT hr = InternalPointer->SetSoftwareVertexProcessing( value );
		RECORD_D3D9( hr );
	}

	Surface^ Device::GetDepthStencilSurface()
	{
		IDirect3DSurface9* surface;

		HRESULT hr = InternalPointer->GetDepthStencilSurface( &surface );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Surface::FromPointer( surface );
	}

	SlimDX::Viewport Device::Viewport::get()
	{
		SlimDX::Viewport viewport;
		HRESULT hr = InternalPointer->GetViewport( reinterpret_cast<D3DVIEWPORT9*>( &viewport ) );
		RECORD_D3D9( hr );

		return viewport;
	}

	void Device::Viewport::set( SlimDX::Viewport value )
	{
		HRESULT hr = InternalPointer->SetViewport( reinterpret_cast<const D3DVIEWPORT9*>( &value ) );
		RECORD_D3D9( hr );
	}

	void Device::ScissorRect::set(Drawing::Rectangle rect)
	{
		RECT scissorRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = InternalPointer->SetScissorRect(&scissorRect);
		RECORD_D3D9(hr);
	}

	Drawing::Rectangle Device::ScissorRect::get()
	{
		RECT scissorRect;		// Scissor rectangle.

		HRESULT hr = InternalPointer->GetScissorRect(&scissorRect);
		RECORD_D3D9(hr);

		return Utilities::ConvertRect(scissorRect);
	}

	Surface^ Device::GetRenderTarget( int index )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = InternalPointer->GetRenderTarget( index, &surface );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Surface::FromPointer( surface );
	}

	generic<typename T>
	T Device::GetRenderState( RenderState state )
	{
		DWORD value = 0;
		HRESULT hr = InternalPointer->GetRenderState( static_cast<D3DRENDERSTATETYPE>( state ), &value );
		RECORD_D3D9( hr );

		return (T) value;
	}
	
	int Device::GetRenderState( RenderState state )
	{
		return GetRenderState<int>( state );
	}

	Result Device::GetStreamSource( int stream, [Out] VertexBuffer^% streamData, [Out] int% offsetBytes, [Out] int% stride )
	{
		IDirect3DVertexBuffer9* localVb;
		UINT localOffset, localStride;

		HRESULT hr = InternalPointer->GetStreamSource( stream, &localVb, &localOffset, &localStride );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			streamData = nullptr;
			offsetBytes = 0;
			stride = 0;
			return Result::Last;
		}

		streamData = VertexBuffer::FromPointer( localVb );
		offsetBytes = localOffset;
		stride = localStride;

		return Result::Last;
	}

	int Device::GetStreamSourceFrequency( int stream )
	{
		UINT localFreq = 0;

		HRESULT hr = InternalPointer->GetStreamSourceFreq( stream, &localFreq );
		RECORD_D3D9( hr );
		
		return localFreq;
	}

	SwapChain^ Device::GetSwapChain( int swapChainIndex )
	{
		IDirect3DSwapChain9* swapChain;

		HRESULT hr = InternalPointer->GetSwapChain( swapChainIndex, &swapChain );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return SwapChain::FromPointer( swapChain );
	}

	IndexBuffer^ Device::GetIndices()
	{
		IDirect3DIndexBuffer9* indices;

		HRESULT hr = InternalPointer->GetIndices( &indices );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return IndexBuffer::FromPointer( indices );
	}

	Result Device::SetIndices( IndexBuffer^ indices )
	{
		HRESULT hr;
		if( indices != nullptr )
			hr = InternalPointer->SetIndices( indices->InternalPointer );
		else
			hr = InternalPointer->SetIndices( NULL );

		return RECORD_D3D9( hr );
	}

	Result Device::ProcessVertices( int sourceStartIndex, int destinationIndex, int vertexCount, VertexBuffer^ destinationBuffer,
		SlimDX::Direct3D9::VertexDeclaration^ vertexDeclaration, LockFlags flags )
	{
		IDirect3DVertexBuffer9* vb = destinationBuffer->InternalPointer;
		IDirect3DVertexDeclaration9* decl = vertexDeclaration != nullptr ? vertexDeclaration->InternalPointer : NULL;

		HRESULT hr = InternalPointer->ProcessVertices( sourceStartIndex, destinationIndex, vertexCount, vb, decl, static_cast<DWORD>( flags ) );
		return RECORD_D3D9( hr );
	}

	Result Device::SetVertexShaderConstant( int startRegister, array<bool>^ data, int offset, int count )
	{
		array<BOOL>^ boolData = gcnew array<BOOL>( data->Length );
		data->CopyTo( boolData, data->Length );
		pin_ptr<BOOL> pinnedData = &boolData[0];

		Utilities::CheckArrayBounds( data, offset, count );
		HRESULT hr = InternalPointer->SetVertexShaderConstantB( startRegister, pinnedData + offset, count );
		return RECORD_D3D9( hr );
	}

	Result Device::SetVertexShaderConstant( int startRegister, array<float>^ data, int offset, int count )
	{
		pin_ptr<float> pinnedData = &data[0];

		Utilities::CheckArrayBounds( data, offset, count );
		HRESULT hr = InternalPointer->SetVertexShaderConstantF( startRegister, pinnedData + offset, count );
		return RECORD_D3D9( hr );
	}

	Result Device::SetVertexShaderConstant( int startRegister, array<int>^ data, int offset, int count )
	{
		pin_ptr<int> pinnedData = &data[0];

		Utilities::CheckArrayBounds( data, offset, count );
		HRESULT hr = InternalPointer->SetVertexShaderConstantI( startRegister, pinnedData + offset, count );
		return RECORD_D3D9( hr );
	}

	Result Device::SetPixelShaderConstant( int startRegister, array<bool>^ data, int offset, int count )
	{
		array<BOOL>^ boolData = gcnew array<BOOL>( data->Length );
		data->CopyTo( boolData, data->Length );
		pin_ptr<BOOL> pinnedData = &boolData[0];

		Utilities::CheckArrayBounds( data, offset, count );
		HRESULT hr = InternalPointer->SetPixelShaderConstantB( startRegister, pinnedData + offset, count );
		return RECORD_D3D9( hr );
	}

	Result Device::SetPixelShaderConstant( int startRegister, array<float>^ data, int offset, int count )
	{
		pin_ptr<float> pinnedData = &data[0];

		Utilities::CheckArrayBounds( data, offset, count );
		HRESULT hr = InternalPointer->SetPixelShaderConstantF( startRegister, pinnedData + offset, count );
		return RECORD_D3D9( hr );
	}

	Result Device::SetPixelShaderConstant( int startRegister, array<int>^ data, int offset, int count )
	{
		pin_ptr<int> pinnedData = &data[0];

		Utilities::CheckArrayBounds( data, offset, count );
		HRESULT hr = InternalPointer->SetPixelShaderConstantI( startRegister, pinnedData + offset, count );
		return RECORD_D3D9( hr );
	}

	Result Device::StretchRectangle( Surface^ source, System::Drawing::Rectangle sourceRect, Surface^ destination,
		System::Drawing::Rectangle destRect, TextureFilter filter )
	{
		RECT nativeSourceRect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };
		RECT nativeDestRect = { destRect.Left, destRect.Top, destRect.Right, destRect.Bottom };

		HRESULT hr = InternalPointer->StretchRect( source->InternalPointer, &nativeSourceRect, destination->InternalPointer,
			&nativeDestRect, static_cast<D3DTEXTUREFILTERTYPE>( filter ) );
		return RECORD_D3D9( hr );
	}

	Result Device::UpdateSurface( Surface^ source, System::Drawing::Rectangle sourceRect,
		Surface^ destination, System::Drawing::Point destinationPoint )
	{
		RECT nativeSourceRect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };
		POINT nativeDestPoint = { destinationPoint.X, destinationPoint.Y };

		HRESULT hr = InternalPointer->UpdateSurface( source->InternalPointer, &nativeSourceRect,
			destination->InternalPointer, &nativeDestPoint );
		return RECORD_D3D9( hr );
	}

	Result Device::UpdateTexture( BaseTexture^ sourceTexture, BaseTexture^ destinationTexture )
	{
		HRESULT hr = InternalPointer->UpdateTexture( sourceTexture->InternalPointer, destinationTexture->InternalPointer );
		return RECORD_D3D9( hr );
	}

	Result Device::ColorFill( Surface^ destSurface, System::Drawing::Rectangle destRect, Color4 color )
	{
		RECT nativeDestRect = { destRect.Left, destRect.Top, destRect.Right, destRect.Bottom };

		HRESULT hr = InternalPointer->ColorFill( destSurface->InternalPointer, &nativeDestRect, static_cast<D3DCOLOR>( color.ToArgb() ) );
		return RECORD_D3D9( hr );
	}

	Result Device::BeginStateBlock()
	{
		HRESULT hr = InternalPointer->BeginStateBlock();
		return RECORD_D3D9( hr );
	}

	StateBlock^ Device::EndStateBlock()
	{
		IDirect3DStateBlock9* stateBlock;
		HRESULT hr = InternalPointer->EndStateBlock( &stateBlock );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return StateBlock::FromPointer( stateBlock );
	}

	int Device::SwapChainCount::get()
	{
		return InternalPointer->GetNumberOfSwapChains();
	}

	float Device::NPatchMode::get()
	{
		return InternalPointer->GetNPatchMode();
	}

	void Device::NPatchMode::set( float value )
	{
		HRESULT hr = InternalPointer->SetNPatchMode( value );
		RECORD_D3D9( hr );
	}

	Result Device::DrawTrianglePatch( int handle, array<float>^ numSegments, TrianglePatchInfo info )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = InternalPointer->DrawTriPatch( handle, pinnedSegments, reinterpret_cast<D3DTRIPATCH_INFO*>( &info ) );
		return RECORD_D3D9( hr );
	}

	Result Device::DrawTrianglePatch( int handle, array<float>^ numSegments )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = InternalPointer->DrawTriPatch( handle, pinnedSegments, NULL );
		return RECORD_D3D9( hr );
	}

	Result Device::DrawRectanglePatch( int handle, array<float>^ numSegments, RectanglePatchInfo info )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = InternalPointer->DrawRectPatch( handle, pinnedSegments, reinterpret_cast<D3DRECTPATCH_INFO*>( &info ) );
		return RECORD_D3D9( hr );
	}

	Result Device::DrawRectanglePatch( int handle, array<float>^ numSegments )
	{
		pin_ptr<float> pinnedSegments = &numSegments[0];

		HRESULT hr = InternalPointer->DrawRectPatch( handle, pinnedSegments, NULL );
		return RECORD_D3D9( hr );
	}

	Result Device::DeletePatch( int handle )
	{
		HRESULT hr = InternalPointer->DeletePatch( handle );
		return RECORD_D3D9( hr );
	}

	DisplayMode Device::GetDisplayMode( int swapChain )
	{
		DisplayMode displayMode;

		HRESULT hr = InternalPointer->GetDisplayMode( swapChain, reinterpret_cast<D3DDISPLAYMODE*>( &displayMode ) );
		RECORD_D3D9( hr );
		
		return displayMode;
	}

	Result Device::EvictManagedResources()
	{
		HRESULT hr = InternalPointer->EvictManagedResources();
		return RECORD_D3D9( hr );
	}

	Result Device::SetDialogBoxMode( bool enableDialogs )
	{
		HRESULT hr = InternalPointer->SetDialogBoxMode( enableDialogs );
		return RECORD_D3D9( hr );
	}

	Result Device::EnableLight( int lightIndex, bool enable )
	{
		HRESULT hr = InternalPointer->LightEnable( lightIndex, enable );
		return RECORD_D3D9( hr );
	}

	bool Device::IsLightEnabled( int lightIndex )
	{
		BOOL enabled = FALSE;
		HRESULT hr = InternalPointer->GetLightEnable( lightIndex, &enabled );
		RECORD_D3D9( hr );

		return enabled > 0;
	}

	Result Device::SetLight( int lightIndex, Light lightData )
	{
		HRESULT hr = InternalPointer->SetLight( lightIndex, reinterpret_cast<const D3DLIGHT9*>( &lightData ) );
		return RECORD_D3D9( hr );
	}

	Light Device::GetLight( int lightIndex )
	{
		Light light;
		HRESULT hr = InternalPointer->GetLight( lightIndex, reinterpret_cast<D3DLIGHT9*>( &light ) );
		RECORD_D3D9( hr );
		
		return light;
	}

	Result Device::SetCursor( Cursor^ cursor, bool addWatermark )
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
		stack_vector<COLORREF> arrayMask;
		stack_vector<COLORREF> arrayColor;
		COLORREF color;
		COLORREF mask;
		HDC hdcColor = NULL;
		HDC hdcScreen = NULL;
		HDC hdcMask = NULL;
		HGDIOBJ oldObject;
		DWORD *bitmap;

		if( !GetIconInfo( static_cast<HICON>( cursor->Handle.ToPointer() ), &iconInfo ) )
			return RECORD_D3D9( E_FAIL );

		if( GetObject( static_cast<HGDIOBJ>( iconInfo.hbmMask ), sizeof( BITMAP ), static_cast<LPVOID>( &bmp ) ) == 0 )
		{
			if( iconInfo.hbmMask != NULL )
				DeleteObject( iconInfo.hbmMask );
			if( iconInfo.hbmColor != NULL )
				DeleteObject( iconInfo.hbmColor );
			return RECORD_D3D9( E_FAIL );
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

		if( FAILED( hr = InternalPointer->CreateOffscreenPlainSurface( width, heightDest, D3DFMT_A8R8G8B8,
			D3DPOOL_SCRATCH, &cursorSurface, NULL ) ) )
		{
			if( iconInfo.hbmMask != NULL )
				DeleteObject( iconInfo.hbmMask );
			if( iconInfo.hbmColor != NULL )
				DeleteObject( iconInfo.hbmColor );
			return RECORD_D3D9( hr );
		}

		arrayMask.resize( width * heightSrc );

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
			if( cursorSurface != NULL )
				cursorSurface->Release();
			return RECORD_D3D9( E_FAIL );
		}

		oldObject = SelectObject( hdcMask, iconInfo.hbmMask );
		GetDIBits( hdcMask, iconInfo.hbmMask, 0, heightSrc, &arrayMask[0], &bmi, DIB_RGB_COLORS );
		SelectObject( hdcMask, oldObject );

		if( !bwCursor )
		{
			arrayColor.resize( width * heightDest );
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
				if( cursorSurface != NULL )
					cursorSurface->Release();
				return RECORD_D3D9( E_FAIL );
			}

			SelectObject( hdcColor, iconInfo.hbmColor );
			GetDIBits( hdcColor, iconInfo.hbmColor, 0, heightDest, &arrayColor[0], &bmi, DIB_RGB_COLORS );
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

				if( addWatermark && x < 12 && y < 5 )
				{
					const WORD wMask[5] = { 0xccc0, 0xa2a0, 0xa4a0, 0xa2a0, 0xccc0 };
					if( wMask[y] & ( 1 << ( 15 - x ) ) )
						bitmap[width * y + x] |= 0xff808080;
				}
			}
		}

		cursorSurface->UnlockRect();

		hr = InternalPointer->SetCursorProperties( iconInfo.xHotspot, iconInfo.yHotspot, cursorSurface );

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
		if( cursorSurface != NULL )
			cursorSurface->Release();
		return RECORD_D3D9( hr );
	}

	void Device::SetCursorPosition( int x, int y, bool immediateUpdate )
	{
		DWORD flags = immediateUpdate ? D3DCURSOR_IMMEDIATE_UPDATE : 0;
		InternalPointer->SetCursorPosition( x, y, flags );
	}

	Result Device::SetCursorProperties( int hotspotX, int hotspotY, Surface^ cursorBitmap )
	{
		IDirect3DSurface9* surface = cursorBitmap != nullptr ? cursorBitmap->InternalPointer : NULL;
		HRESULT hr = InternalPointer->SetCursorProperties( hotspotX, hotspotY, surface );
		return RECORD_D3D9( hr );
	}

	void Device::CurrentTexturePalette::set( int value )
	{
		HRESULT hr = InternalPointer->SetCurrentTexturePalette( value );
		RECORD_D3D9( hr );
	}

	int Device::CurrentTexturePalette::get()
	{
		unsigned int palette = 0;
		HRESULT hr = InternalPointer->GetCurrentTexturePalette( &palette );
		RECORD_D3D9( hr );

		return (int) palette;
	}

	VertexShader^ Device::GetVertexShader()
	{
		IDirect3DVertexShader9* vs;
		HRESULT hr = InternalPointer->GetVertexShader( &vs );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return VertexShader::FromPointer( vs );
	}

	PixelShader^ Device::GetPixelShader()
	{
		IDirect3DPixelShader9* ps;
		HRESULT hr = InternalPointer->GetPixelShader( &ps );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return PixelShader::FromPointer( ps );
	}

	DriverLevel Device::DriverLevel::get()
	{
		return static_cast<SlimDX::Direct3D9::DriverLevel>( D3DXGetDriverLevel( InternalPointer ) );
	}

	String^ Device::VertexShaderProfile::get()
	{
		LPCSTR profile = D3DXGetVertexShaderProfile( InternalPointer );
		return gcnew String( profile );
	}

	String^ Device::PixelShaderProfile::get()
	{
		LPCSTR profile = D3DXGetPixelShaderProfile( InternalPointer );
		return gcnew String( profile );
	}

	Result Device::SetR2VBMode( bool enableR2VB )
	{
		return SetRenderState( RenderState::PointSize, static_cast<int>( r2vbGlbEnable_Set( enableR2VB ) ) );
	}

	Result Device::BindRenderTargetToVertexStream( R2VBSampler sampler, Texture^ r2vbTarget, int stream, int stride, VertexBuffer^ dummyVb )
	{
		if( SetTexture( D3DDMAPSAMPLER, r2vbTarget ).IsFailure )
			return Result::Last;

		if( SetRenderState( RenderState::PointSize, static_cast<int>( r2vbVStrm2SmpMap_Set( stream, static_cast<int>( sampler ) ) ) ).IsFailure )
			return Result::Last;

		if( SetStreamSource( stream, dummyVb, 0, stride ).IsFailure )
			return Result::Last;

		return RECORD_D3D9( D3D_OK );
	}

	Result Device::RestoreVertexStream( int stream )
	{
		if( SetRenderState( RenderState::PointSize, static_cast<int>( r2vbVStrm2SmpMap_Set( stream, R2VB_VSMP_OVR_DIS ) ) ).IsFailure )
			return Result::Last;

		return SetTexture( D3DDMAPSAMPLER, nullptr );
	}

	Result Device::SetClipPlane( int index, Plane clipPlane )
	{
		HRESULT hr = InternalPointer->SetClipPlane( index, reinterpret_cast<const float*>( &clipPlane ) );
		return RECORD_D3D9( hr );
	}

	Plane Device::GetClipPlane( int index )
	{
		Plane plane;
		HRESULT hr = InternalPointer->GetClipPlane( index, reinterpret_cast<float*>( &plane ) );
		RECORD_D3D9( hr );

		return plane;
	}

	Result Device::GetFrontBufferData( int swapChain, Surface^ destinationSurface )
	{
		IDirect3DSurface9* surface = destinationSurface != nullptr ? destinationSurface->InternalPointer : NULL;
		HRESULT hr = InternalPointer->GetFrontBufferData( swapChain, surface );
		return RECORD_D3D9( hr );
	}

	Result Device::GetRenderTargetData( Surface^ renderTarget, Surface^ destinationSurface )
	{
		IDirect3DSurface9* target = renderTarget != nullptr	? renderTarget->InternalPointer : NULL;
		IDirect3DSurface9* destination = destinationSurface != nullptr ? destinationSurface->InternalPointer : NULL;
		HRESULT hr = InternalPointer->GetRenderTargetData( target, destination );
		return RECORD_D3D9( hr );
	}
}
}
