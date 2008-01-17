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
#include <vcclr.h>

#include "../BaseObject.h"

#include "Device.h"
#include "../DataStream.h"
#include "Volume.h"
#include "Texture.h"

namespace SlimDX
{
namespace Direct3D9
{
	Volume::Volume( IDirect3DVolume9* volume )
	{
		//D3D BUG WAR: IDirect3DVolume9 does not inherit from IDirect3DResource9 like it's supposed to
		Construct( volume );
	}

	Volume::Volume( IntPtr volume )
	{
		Construct( volume, IID_IDirect3DVolume9 );
		
		D3DRESOURCETYPE type = InternalPointer->GetType();
		if( type != D3DRTYPE_VOLUME )
			throw gcnew InvalidCastException( "Serious QueryInterface failure in Volume." );
	}

	VolumeDescription Volume::Description::get()
	{
		VolumeDescription desc;

		HRESULT hr = VolumePointer->GetDesc( reinterpret_cast<D3DVOLUME_DESC*>( &desc ) );
		GraphicsException::CheckHResult( hr );

		return desc;
	}

	LockedBox Volume::LockBox( LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;

		HRESULT hr = VolumePointer->LockBox( &lockedBox, NULL, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );

		int lockedSize = lockedBox.RowPitch * lockedBox.SlicePitch * Description.Height;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		LockedBox outBox( lockedBox.RowPitch, lockedBox.SlicePitch, gcnew DataStream( lockedBox.pBits, lockedSize, true, !readOnly, false ) );
		return outBox;
	}

	LockedBox Volume::LockBox( Box box, LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;

		HRESULT hr = VolumePointer->LockBox( &lockedBox, reinterpret_cast<D3DBOX*>( &box ), static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		
		int lockedSize = lockedBox.RowPitch * lockedBox.SlicePitch * Description.Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		LockedBox outBox( lockedBox.RowPitch, lockedBox.SlicePitch, gcnew DataStream( lockedBox.pBits, lockedSize, true, !readOnly, false ) );
		return outBox;
	}

	void Volume::UnlockBox()
	{
		HRESULT hr = VolumePointer->UnlockBox();
		GraphicsException::CheckHResult( hr );
	}

	Device^ Volume::GetDevice()
	{
		IDirect3DDevice9 *result;

		HRESULT hr = VolumePointer->GetDevice( &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( result );
	}

	void Volume::FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey, Box sourceBox,
		Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation )
	{
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadVolumeFromFileInMemory( volume->VolumePointer, 
			reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			reinterpret_cast<const D3DBOX*>( &destinationBox ), pinnedMemory, memory->Length,
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey, Box sourceBox,
		Box destinationBox, [Out] ImageInformation% imageInformation )
	{
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadVolumeFromFileInMemory( volume->VolumePointer, NULL,
			reinterpret_cast<const D3DBOX*>( &destinationBox ), pinnedMemory, memory->Length,
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey, Box sourceBox,
		Box destinationBox )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadVolumeFromFileInMemory( volume->VolumePointer, NULL,
			reinterpret_cast<const D3DBOX*>( &destinationBox ), pinnedMemory, memory->Length,
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadVolumeFromFileInMemory( volume->VolumePointer, NULL, NULL, pinnedMemory, 
			memory->Length, NULL, static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ), NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey, Box sourceBox, 
		Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Volume::FromMemory( volume, data, filter, colorKey, sourceBox, destinationBox,
			palette, imageInformation );
	}

	void Volume::FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey, Box sourceBox,
		Box destinationBox, [Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Volume::FromMemory( volume, data, filter, colorKey, sourceBox, destinationBox,
			imageInformation );
	}

	void Volume::FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey, Box sourceBox, 
		Box destinationBox )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Volume::FromMemory( volume, data, filter, colorKey, sourceBox, destinationBox );
	}

	void Volume::FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Volume::FromMemory( volume, data, filter, colorKey );
	}

	void Volume::FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey, 
		Box sourceBox, Box destinationBox,
		array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation )
	{
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadVolumeFromFile( volume->VolumePointer, 
			reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			reinterpret_cast<const D3DBOX*>( &destinationBox ), pinnedName,
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey, 
		Box sourceBox, Box destinationBox,
		[Out] ImageInformation% imageInformation )
	{
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadVolumeFromFile( volume->VolumePointer, NULL,
			reinterpret_cast<const D3DBOX*>( &destinationBox ), pinnedName,
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey, 
		Box sourceBox, Box destinationBox )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadVolumeFromFile( volume->VolumePointer, NULL,
			reinterpret_cast<const D3DBOX*>( &destinationBox ), pinnedName,
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ),
			static_cast<D3DCOLOR>( colorKey ), NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadVolumeFromFile( volume->VolumePointer, NULL, NULL, pinnedName,
			NULL, static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ), NULL );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey,
		Box sourceBox, Box destinationBox,
		array<PaletteEntry>^ destinationPalette, array<PaletteEntry>^ sourcePalette )
	{
		pin_ptr<PaletteEntry> pinnedSource = &sourcePalette[0];
		pin_ptr<PaletteEntry> pinnedDest = &destinationPalette[0];

		HRESULT hr = D3DXLoadVolumeFromVolume( destinationVolume->VolumePointer, 
			reinterpret_cast<const PALETTEENTRY*>( pinnedDest ), reinterpret_cast<const D3DBOX*>( &destinationBox ),
			sourceVolume->VolumePointer, reinterpret_cast<const PALETTEENTRY*>( pinnedSource ), 
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey,
		Box sourceBox, Box destinationBox )
	{
		HRESULT hr = D3DXLoadVolumeFromVolume( destinationVolume->VolumePointer, 
			NULL, reinterpret_cast<const D3DBOX*>( &destinationBox ), sourceVolume->VolumePointer, NULL, 
			reinterpret_cast<const D3DBOX*>( &sourceBox ), static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey )
	{
		HRESULT hr = D3DXLoadVolumeFromVolume( destinationVolume->VolumePointer, NULL, NULL, 
			sourceVolume->VolumePointer, NULL, NULL, static_cast<DWORD>( filter ), static_cast<D3DCOLOR>( colorKey ) );
		GraphicsException::CheckHResult( hr );
	}

	DataStream^ Volume::ToStream( Volume^ volume, ImageFileFormat format, Box box,
		array<PaletteEntry>^ palette )
	{
		ID3DXBuffer *result = NULL;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXSaveVolumeToFileInMemory( &result, static_cast<D3DXIMAGE_FILEFORMAT>( format ),
			volume->VolumePointer, reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ), reinterpret_cast<const D3DBOX*>( &box ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			if( result != NULL )
				result->Release();
			return nullptr;
		}

		return gcnew DataStream( result );
	}

	DataStream^ Volume::ToStream( Volume^ volume, ImageFileFormat format, Box box )
	{
		ID3DXBuffer *result = NULL;

		HRESULT hr = D3DXSaveVolumeToFileInMemory( &result, static_cast<D3DXIMAGE_FILEFORMAT>( format ),
			volume->VolumePointer, NULL, reinterpret_cast<const D3DBOX*>( &box ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			if( result != NULL )
				result->Release();
			return nullptr;
		}

		return gcnew DataStream( result );
	}

	DataStream^ Volume::ToStream( Volume^ volume, ImageFileFormat format )
	{
		ID3DXBuffer *result = NULL;

		HRESULT hr = D3DXSaveVolumeToFileInMemory( &result, static_cast<D3DXIMAGE_FILEFORMAT>( format ),
			volume->VolumePointer, NULL, NULL );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			if( result != NULL )
				result->Release();
			return nullptr;
		}

		return gcnew DataStream( result );
	}

	void Volume::ToFile( Volume^ volume, String^ fileName, ImageFileFormat format, 
		Box box, array<PaletteEntry>^ palette )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];
		
		HRESULT hr = D3DXSaveVolumeToFile( pinnedName, static_cast<D3DXIMAGE_FILEFORMAT>( format ), 
			volume->VolumePointer, reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			reinterpret_cast<const D3DBOX*>( &box ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::ToFile( Volume^ volume, String^ fileName, ImageFileFormat format, 
		Box box )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);
		
		HRESULT hr = D3DXSaveVolumeToFile( pinnedName, static_cast<D3DXIMAGE_FILEFORMAT>( format ), 
			volume->VolumePointer, NULL, reinterpret_cast<const D3DBOX*>( &box ) );
		GraphicsException::CheckHResult( hr );
	}

	void Volume::ToFile( Volume^ volume, String^ fileName, ImageFileFormat format )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);
		
		HRESULT hr = D3DXSaveVolumeToFile( pinnedName, static_cast<D3DXIMAGE_FILEFORMAT>( format ), 
			volume->VolumePointer, NULL, NULL );
		GraphicsException::CheckHResult( hr );
	}
}
}