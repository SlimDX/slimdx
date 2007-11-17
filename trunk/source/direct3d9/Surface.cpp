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
#include "../Direct3D/..\DataStream.h"
#include "Surface.h"

namespace SlimDX
{
namespace Direct3D9
{
	Surface::Surface( IDirect3DSurface9* surface )
	{
		if( surface == NULL )
			throw gcnew ArgumentNullException( "surface" );

		m_Pointer = surface;
	}

	Surface::Surface( IntPtr surface )
	{
		if( surface == IntPtr::Zero )
			throw gcnew ArgumentNullException( "vertexShader" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( surface.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DSurface9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDirect3DSurface9*>( pointer );
	}

	Surface^ Surface::CreateRenderTarget( Device^ device, int width, int height, Format format,
		MultisampleType multiSampleType, int multiSampleQuality, bool lockable )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = device->InternalPointer->CreateRenderTarget( width, height, static_cast<D3DFORMAT>( format ),
			static_cast<D3DMULTISAMPLE_TYPE>( multiSampleType ), multiSampleQuality, lockable, &surface, NULL );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( surface );
	}

	Surface^ Surface::CreateOffscreenPlain( Device^ device, int width, int height, Format format, Pool pool )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = device->InternalPointer->CreateOffscreenPlainSurface( width, height,
			static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &surface, NULL );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( surface );
	}

	Surface^ Surface::CreateDepthStencil( Device^ device, int width, int height, Format format,
		MultisampleType multiSampleType, int multiSampleQuality, bool discard )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = device->InternalPointer->CreateDepthStencilSurface( width, height, static_cast<D3DFORMAT>( format ),
			static_cast<D3DMULTISAMPLE_TYPE>( multiSampleType ), multiSampleQuality, discard, &surface, NULL );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( surface );
	}

	SurfaceDescription Surface::Description::get()
	{
		SurfaceDescription desc;

		HRESULT hr = SurfacePointer->GetDesc( reinterpret_cast<D3DSURFACE_DESC*>( &desc ) );
		GraphicsException::CheckHResult( hr );

		return desc;
	}

	LockedRect Surface::LockRectangle( LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;

		HRESULT hr = SurfacePointer->LockRect( &lockedRect, NULL, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		LockedRect outRect;
		outRect.Data = gcnew DataStream( lockedRect.pBits, 0, true, !readOnly, false );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	LockedRect Surface::LockRectangle( System::Drawing::Rectangle rect, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };

		HRESULT hr = SurfacePointer->LockRect( &lockedRect, &nativeRect, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		LockedRect outRect;
		outRect.Data = gcnew DataStream( lockedRect.pBits, 0, true, !readOnly, false );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	void Surface::UnlockRectangle()
	{
		HRESULT hr = SurfacePointer->UnlockRect();
		GraphicsException::CheckHResult( hr );
	}

	IntPtr Surface::GetDC()
	{
		HDC hdc;
		
		HRESULT hr = SurfacePointer->GetDC( &hdc );
		GraphicsException::CheckHResult( hr );

		IntPtr ptr( hdc );
		return ptr;
	}

	void Surface::ReleaseDC( IntPtr hdc )
	{
		HRESULT hr = SurfacePointer->ReleaseDC( static_cast<HDC>( hdc.ToPointer() ) );
		GraphicsException::CheckHResult( hr );
	}
}
}
