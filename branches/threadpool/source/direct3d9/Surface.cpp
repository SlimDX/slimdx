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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>

#include "../ComObject.h"
#include "../DataStream.h"

#include "Direct3D9Exception.h"

#include "Device.h"
#include "Surface.h"
#include "Texture.h"

using namespace System;
using namespace System::IO;
using namespace System::Reflection;

namespace SlimDX
{
namespace Direct3D9
{
	Surface::Surface( IDirect3DSurface9* surface )
	{
		Construct(surface);
	}

	Surface::Surface( IntPtr surface )
	{
		Construct( surface, NativeInterface );
	}

	Surface^ Surface::FromPointer( IDirect3DSurface9* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Surface^ tableEntry = safe_cast<Surface^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Surface( pointer );
	}

	Surface^ Surface::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Surface^ tableEntry = safe_cast<Surface^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Surface( pointer );
	}

	Surface^ Surface::CreateRenderTarget( SlimDX::Direct3D9::Device^ device, int width, int height, Format format,
		MultisampleType multiSampleType, int multiSampleQuality, bool lockable )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = device->InternalPointer->CreateRenderTarget( width, height, static_cast<D3DFORMAT>( format ),
			static_cast<D3DMULTISAMPLE_TYPE>( multiSampleType ), multiSampleQuality, lockable, &surface, NULL );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Surface^ result = gcnew Surface( surface );
		result->IsDefaultPool = true;
		return result;
	}

	Surface^ Surface::CreateOffscreenPlain( SlimDX::Direct3D9::Device^ device, int width, int height, Format format, Pool pool )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = device->InternalPointer->CreateOffscreenPlainSurface( width, height,
			static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &surface, NULL );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Surface^ result = gcnew Surface( surface );
		if( pool == Pool::Default )
			result->IsDefaultPool = true;

		return result;
	}

	Surface^ Surface::CreateDepthStencil( SlimDX::Direct3D9::Device^ device, int width, int height, Format format,
		MultisampleType multiSampleType, int multiSampleQuality, bool discard )
	{
		IDirect3DSurface9* surface;

		HRESULT hr = device->InternalPointer->CreateDepthStencilSurface( width, height, static_cast<D3DFORMAT>( format ),
			static_cast<D3DMULTISAMPLE_TYPE>( multiSampleType ), multiSampleQuality, discard, &surface, NULL );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		Surface^ result = gcnew Surface( surface );
		result->IsDefaultPool = true;
		return result;
	}

	Result Surface::FromMemory( Surface^ surface, array<Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle,
		System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation )
	{
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadSurfaceFromFileInMemory( surface->InternalPointer, 
			reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			reinterpret_cast<const RECT*>( &destinationRectangle ), pinnedMemory, memory->Length,
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );
		
		return RECORD_D3D9( hr );
	}

	Result Surface::FromMemory( Surface^ surface, array<Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle,
		System::Drawing::Rectangle destinationRectangle, [Out] ImageInformation% imageInformation )
	{
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadSurfaceFromFileInMemory( surface->InternalPointer, NULL,
			reinterpret_cast<const RECT*>( &destinationRectangle ), pinnedMemory, memory->Length,
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );

		return RECORD_D3D9( hr );
	}

	Result Surface::FromMemory( Surface^ surface, array<Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle,
		System::Drawing::Rectangle destinationRectangle )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadSurfaceFromFileInMemory( surface->InternalPointer, NULL,
			reinterpret_cast<const RECT*>( &destinationRectangle ), pinnedMemory, memory->Length,
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), NULL );

		return RECORD_D3D9( hr );
	}

	Result Surface::FromMemory( Surface^ surface, array<Byte>^ memory, Filter filter, int colorKey )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadSurfaceFromFileInMemory( surface->InternalPointer, NULL, NULL, pinnedMemory, 
			memory->Length, NULL, static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ), NULL );

		return RECORD_D3D9( hr );
	}

	Result Surface::FromStream( Surface^ surface, Stream^ stream, Filter filter, int colorKey,
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle,
		array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Surface::FromMemory( surface, data, filter, colorKey, sourceRectangle, destinationRectangle,
			palette, imageInformation );
	}

	Result Surface::FromStream( Surface^ surface, Stream^ stream, Filter filter, int colorKey,
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle,
		[Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Surface::FromMemory( surface, data, filter, colorKey, sourceRectangle, destinationRectangle,
			imageInformation );
	}

	Result Surface::FromStream( Surface^ surface, Stream^ stream, Filter filter, int colorKey,
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Surface::FromMemory( surface, data, filter, colorKey, sourceRectangle, destinationRectangle );
	}

	Result Surface::FromStream( Surface^ surface, Stream^ stream, Filter filter, int colorKey )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Surface::FromMemory( surface, data, filter, colorKey );
	}

	Result Surface::FromFile( Surface^ surface, String^ fileName, Filter filter, int colorKey, 
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle,
		array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation )
	{
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadSurfaceFromFile( surface->InternalPointer, 
			reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			reinterpret_cast<const RECT*>( &destinationRectangle ), pinnedName,
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );
		return RECORD_D3D9( hr );
	}

	Result Surface::FromFile( Surface^ surface, String^ fileName, Filter filter, int colorKey, 
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle,
		[Out] ImageInformation% imageInformation )
	{
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadSurfaceFromFile( surface->InternalPointer, NULL,
			reinterpret_cast<const RECT*>( &destinationRectangle ), pinnedName,
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );
		return RECORD_D3D9( hr );
	}

	Result Surface::FromFile( Surface^ surface, String^ fileName, Filter filter, int colorKey, 
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadSurfaceFromFile( surface->InternalPointer, NULL,
			reinterpret_cast<const RECT*>( &destinationRectangle ), pinnedName,
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), NULL );
		return RECORD_D3D9( hr );
	}

	Result Surface::FromFile( Surface^ surface, String^ fileName, Filter filter, int colorKey )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadSurfaceFromFile( surface->InternalPointer, NULL, NULL, pinnedName,
			NULL, static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ), NULL );
		return RECORD_D3D9( hr );
	}

	Result Surface::FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey,
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle,
		array<PaletteEntry>^ destinationPalette, array<PaletteEntry>^ sourcePalette )
	{
		pin_ptr<PaletteEntry> pinnedSource = &sourcePalette[0];
		pin_ptr<PaletteEntry> pinnedDest = &destinationPalette[0];

		HRESULT hr = D3DXLoadSurfaceFromSurface( destinationSurface->InternalPointer, 
			reinterpret_cast<const PALETTEENTRY*>( pinnedDest ), reinterpret_cast<const RECT*>( &destinationRectangle ),
			sourceSurface->InternalPointer, reinterpret_cast<const PALETTEENTRY*>( pinnedSource ), 
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ) );
		return RECORD_D3D9( hr );
	}

	Result Surface::FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey,
		System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle )
	{
		HRESULT hr = D3DXLoadSurfaceFromSurface( destinationSurface->InternalPointer, 
			NULL, reinterpret_cast<const RECT*>( &destinationRectangle ), sourceSurface->InternalPointer, NULL, 
			reinterpret_cast<const RECT*>( &sourceRectangle ), static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ) );
		return RECORD_D3D9( hr );
	}

	Result Surface::FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey )
	{
		HRESULT hr = D3DXLoadSurfaceFromSurface( destinationSurface->InternalPointer, NULL, NULL, 
			sourceSurface->InternalPointer, NULL, NULL, static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ) );
		return RECORD_D3D9( hr );
	}

	DataStream^ Surface::ToStream( Surface^ surface, ImageFileFormat format, System::Drawing::Rectangle rectangle,
		array<PaletteEntry>^ palette )
	{
		ID3DXBuffer *result = NULL;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXSaveSurfaceToFileInMemory( &result, static_cast<D3DXIMAGE_FILEFORMAT>( format ),
			surface->InternalPointer, reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ), reinterpret_cast<const RECT*>( &rectangle ) );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew DataStream( result );
	}

	DataStream^ Surface::ToStream( Surface^ surface, ImageFileFormat format, System::Drawing::Rectangle rectangle )
	{
		ID3DXBuffer *result = NULL;

		HRESULT hr = D3DXSaveSurfaceToFileInMemory( &result, static_cast<D3DXIMAGE_FILEFORMAT>( format ),
			surface->InternalPointer, NULL, reinterpret_cast<const RECT*>( &rectangle ) );
	
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew DataStream( result );
	}

	DataStream^ Surface::ToStream( Surface^ surface, ImageFileFormat format )
	{
		ID3DXBuffer *result = NULL;

		HRESULT hr = D3DXSaveSurfaceToFileInMemory( &result, static_cast<D3DXIMAGE_FILEFORMAT>( format ),
			surface->InternalPointer, NULL, NULL );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew DataStream( result );
	}

	Result Surface::ToFile( Surface^ surface, String^ fileName, ImageFileFormat format, 
		System::Drawing::Rectangle rectangle, array<PaletteEntry>^ palette )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];
		
		HRESULT hr = D3DXSaveSurfaceToFile( pinnedName, static_cast<D3DXIMAGE_FILEFORMAT>( format ), 
			surface->InternalPointer, reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			reinterpret_cast<const RECT*>( &rectangle ) );
		return RECORD_D3D9( hr );
	}

	Result Surface::ToFile( Surface^ surface, String^ fileName, ImageFileFormat format, 
		System::Drawing::Rectangle rectangle )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);
		
		HRESULT hr = D3DXSaveSurfaceToFile( pinnedName, static_cast<D3DXIMAGE_FILEFORMAT>( format ), 
			surface->InternalPointer, NULL, reinterpret_cast<const RECT*>( &rectangle ) );
		return RECORD_D3D9( hr );
	}

	Result Surface::ToFile( Surface^ surface, String^ fileName, ImageFileFormat format )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);
		
		HRESULT hr = D3DXSaveSurfaceToFile( pinnedName, static_cast<D3DXIMAGE_FILEFORMAT>( format ), 
			surface->InternalPointer, NULL, NULL );
		return RECORD_D3D9( hr );
	}

	SurfaceDescription Surface::Description::get()
	{
		SurfaceDescription description;

		HRESULT hr = InternalPointer->GetDesc( reinterpret_cast<D3DSURFACE_DESC*>( &description ) );
		RECORD_D3D9( hr );

		return description;
	}

	DataRectangle^ Surface::LockRectangle( LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		
		HRESULT hr = InternalPointer->LockRect( &lockedRect, NULL, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		int lockedSize = lockedRect.Pitch * Description.Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataRectangle^ outRect = gcnew DataRectangle( lockedRect.Pitch, gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false ) );
		return outRect;
	}

	DataRectangle^ Surface::LockRectangle( System::Drawing::Rectangle rect, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };

		HRESULT hr = InternalPointer->LockRect( &lockedRect, &nativeRect, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		int lockedSize = lockedRect.Pitch * Description.Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataRectangle^ outRect = gcnew DataRectangle( lockedRect.Pitch, gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false ) );
		return outRect;
	}

	Result Surface::UnlockRectangle()
	{
		HRESULT hr = InternalPointer->UnlockRect();
		return RECORD_D3D9( hr );
	}

	IntPtr Surface::GetDC()
	{
		HDC hdc;
		
		HRESULT hr = InternalPointer->GetDC( &hdc );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return IntPtr::Zero;

		IntPtr ptr( hdc );
		return ptr;
	}

	Result Surface::ReleaseDC( IntPtr hdc )
	{
		HRESULT hr = InternalPointer->ReleaseDC( static_cast<HDC>( hdc.ToPointer() ) );
		return RECORD_D3D9( hr );
	}

	generic<typename TContainer>
	TContainer Surface::GetContainer()
	{
		GUID guid = Utilities::GetNativeGuidForType( TContainer::typeid );
		void *resultPointer;

		HRESULT hr = InternalPointer->GetContainer( guid, &resultPointer );
		if( RECORD_D3D9( hr ).IsFailure )
			return TContainer();

		MethodInfo^ method = TContainer::typeid->GetMethod( "FromPointer", BindingFlags::Public | BindingFlags::Static );
		return safe_cast<TContainer>( method->Invoke( nullptr, gcnew array<Object^> { IntPtr( resultPointer ) } ) );
	}
}
}
