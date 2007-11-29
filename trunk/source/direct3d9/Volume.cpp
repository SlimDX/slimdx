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
#include "Volume.h"

namespace SlimDX
{
namespace Direct3D9
{
	Volume::Volume( IDirect3DVolume9* volume )
	{
		if( volume == NULL )
			throw gcnew ArgumentNullException( "volume" );

		//D3D BUG WAR: IDirect3DVolume9 does not inherit from IDirect3DResource9 like it's supposed to
		m_Pointer = reinterpret_cast<IDirect3DResource9*>( volume );
	}

	Volume::Volume( IntPtr volume )
	{
		if( volume == IntPtr::Zero )
			throw gcnew ArgumentNullException( "vertexShader" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( volume.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DVolume9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDirect3DResource9*>( pointer );
		
		D3DRESOURCETYPE type = m_Pointer->GetType();
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
		LockedBox outBox;
		outBox.Data = gcnew DataStream( lockedBox.pBits, lockedSize, true, !readOnly, false );
		outBox.RowPitch = lockedBox.RowPitch;
		outBox.SlicePitch = lockedBox.SlicePitch;
		return outBox;
	}

	LockedBox Volume::LockBox( Box box, LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;

		HRESULT hr = VolumePointer->LockBox( &lockedBox, reinterpret_cast<D3DBOX*>( &box ), static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		
		int lockedSize = lockedBox.RowPitch * lockedBox.SlicePitch * Description.Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		LockedBox outBox;
		outBox.Data = gcnew DataStream( lockedBox.pBits, lockedSize, true, !readOnly, false );
		outBox.RowPitch = lockedBox.RowPitch;
		outBox.SlicePitch = lockedBox.SlicePitch;
		return outBox;
	}

	void Volume::UnlockBox()
	{
		HRESULT hr = VolumePointer->UnlockBox();
		GraphicsException::CheckHResult( hr );
	}
}
}