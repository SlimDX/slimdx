#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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
#include "../Math/Vector3.h"
#include "../DataStream.h"

#include "Device.h"
#include "Mesh.h"
#include "ProgressiveMesh.h"
#include "PatchMesh.h"
#include "SkinInfo.h"
#include "AnimationFrame.h"
#include "AnimationSet.h"
#include "Direct3D9Exception.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	AnimationShim::AnimationShim( AnimationSet^ animationSet )
	{
		nameHandles = gcnew Dictionary<String^, GCHandle>();
		this->animationSet = animationSet;
		refCount = 1;
	}

	AnimationShim::~AnimationShim()
	{
		for each( GCHandle handle in nameHandles->Values )
			handle.Free();
		nameHandles->Clear();
	}

	AnimationSet^ AnimationShim::GetAnimationSet()
	{
		return animationSet;
	}

	HRESULT AnimationShim::QueryInterface( const IID &iid, LPVOID *ppv )
	{
		if( iid == IID_ID3DXAnimationSet )
		{
			AddRef();
			*reinterpret_cast<ID3DXAnimationSet**>( ppv ) = this;
			return S_OK;
		}

		return E_NOTIMPL;
	}

	ULONG AnimationShim::AddRef()
	{
		return ++refCount;
	}

	ULONG AnimationShim::Release()
	{
		if( --refCount == 0 )
			delete this;
		return refCount;
	}

	HRESULT AnimationShim::GetAnimationIndexByName( LPCSTR Name, UINT *pIndex )
	{
		try
		{
			*pIndex = animationSet->GetAnimationIndex( gcnew String( Name ) );
		}
		catch(Exception^)
		{
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT AnimationShim::GetAnimationNameByIndex( UINT Index, LPCSTR *ppName )
	{
		try
		{
			String^ name = animationSet->GetAnimationName( Index );
			
			GCHandle handle;
			if( !nameHandles->TryGetValue( name, handle ) )
			{
				array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
				handle = GCHandle::Alloc( nameBytes, GCHandleType::Pinned );

				nameHandles->Add( name, handle );
			}

			*ppName = reinterpret_cast<LPCSTR>( handle.AddrOfPinnedObject().ToPointer() );
		}
		catch(Exception^)
		{
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT AnimationShim::GetCallback( DOUBLE Position, DWORD Flags, DOUBLE *pCallbackPosition, LPVOID *ppCallbackData )
	{
		try
		{
			double outPosition = *pCallbackPosition;
			IntPtr result = animationSet->GetCallback( Position, static_cast<CallbackSearchFlags>( Flags ), outPosition );

			*pCallbackPosition = outPosition;
			*ppCallbackData = result.ToPointer();
		}
		catch(Exception^)
		{
			return E_FAIL;
		}

		return S_OK;
	}

	LPCSTR AnimationShim::GetName()
	{
		String^ name = animationSet->Name;

		GCHandle handle;
		if( !nameHandles->TryGetValue( name, handle ) )
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			handle = GCHandle::Alloc( nameBytes, GCHandleType::Pinned );

			nameHandles->Add( name, handle );
		}

		return reinterpret_cast<LPCSTR>( handle.AddrOfPinnedObject().ToPointer() );
	}

	UINT AnimationShim::GetNumAnimations()
	{
		try
		{
			return animationSet->AnimationCount;
		}
		catch(Exception^)
		{
		}

		return 0;
	}

	DOUBLE AnimationShim::GetPeriod()
	{
		try
		{
			return animationSet->Period;
		}
		catch(Exception^)
		{
		}

		return 0.0;
	}

	DOUBLE AnimationShim::GetPeriodicPosition( DOUBLE Position )
	{
		try
		{
			return animationSet->GetPeriodicPosition( Position );
		}
		catch(Exception^)
		{
		}

		return 0.0;
	}

	HRESULT AnimationShim::GetSRT( DOUBLE PeriodicPosition, UINT Animation, D3DXVECTOR3 *pScale, D3DXQUATERNION *pRotation, D3DXVECTOR3 *pTranslation )
	{
		try
		{
			AnimationOutput output = animationSet->GetTransformation( PeriodicPosition, Animation );

			*pRotation = D3DXQUATERNION( output.Rotation.X, output.Rotation.Y, output.Rotation.Z, output.Rotation.W );
			*pScale = D3DXVECTOR3( output.Scaling.X, output.Scaling.Y, output.Scaling.Z );
			*pTranslation = D3DXVECTOR3( output.Translation.X, output.Translation.Y, output.Translation.Z );
		}
		catch(Exception^)
		{
			return E_FAIL;
		}

		return S_OK;
	}

	AnimationSet::AnimationSet()
	{
		// Manual Allocation: released in the destructor
		// the pointer is never stored elsewhere
		shim = new AnimationShim( this );

		Construct( shim );
	}

	AnimationSet::~AnimationSet()
	{
		Free();
	}

	AnimationSet::!AnimationSet()
	{
		Free();
	}

	void AnimationSet::Free()
	{
		if( shim != NULL )
		{
			delete shim;
			shim = NULL;
		}
	}

	AnimationSet^ AnimationSet::FromPointer( ID3DXAnimationSet *pointer, ComObject^ owner )
	{
		AnimationSet^ tableEntry = safe_cast<AnimationSet^>( SlimDX::ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
			return tableEntry;

		return InternalAnimationSet::FromPointer( pointer, owner );
	}

	int AnimationSet::GetAnimationIndex( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<const unsigned char> pinnedName = &nameBytes[0];
		unsigned int result;

		HRESULT hr = InternalPointer->GetAnimationIndexByName( reinterpret_cast<LPCSTR>( pinnedName ), &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return 0;

		return static_cast<int>( result );
	}

	String^ AnimationSet::GetAnimationName( int index )
	{
		LPCSTR result;
		HRESULT hr = InternalPointer->GetAnimationNameByIndex( index, &result );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew String( result );
	}

	IntPtr AnimationSet::GetCallback( double position, CallbackSearchFlags flags, [Out] double% callbackPosition )
	{
		pin_ptr<double> pinPosition = &callbackPosition;
		LPVOID data;

		HRESULT hr = InternalPointer->GetCallback( position, static_cast<DWORD>( flags ), pinPosition, &data );

		if( RECORD_D3D9( hr ).IsFailure )
			return IntPtr::Zero;

		return IntPtr( data );
	}

	AnimationOutput AnimationSet::GetTransformation( double periodicPosition, int animation )
	{
		Vector3 scale;
		Vector3 translation;
		Quaternion rotation;

		HRESULT hr = InternalPointer->GetSRT( periodicPosition, animation, reinterpret_cast<D3DXVECTOR3*>( &scale ), 
			reinterpret_cast<D3DXQUATERNION*>( &rotation ), reinterpret_cast<D3DXVECTOR3*>( &translation ) );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return AnimationOutput();

		AnimationOutput output;
		output.Flags = AnimationOutputFlags::Rotation | AnimationOutputFlags::Scale | AnimationOutputFlags::Translation;
		output.Scaling = scale;
		output.Translation = translation;
		output.Rotation = rotation;

		return output;
	}

	String^ AnimationSet::Name::get()
	{
		return gcnew String( InternalPointer->GetName() );
	}

	int AnimationSet::AnimationCount::get()
	{
		return InternalPointer->GetNumAnimations();
	}

	double AnimationSet::Period::get()
	{
		return InternalPointer->GetPeriod();
	}

	double AnimationSet::GetPeriodicPosition( double position )
	{
		return InternalPointer->GetPeriodicPosition( position );
	}
}
}