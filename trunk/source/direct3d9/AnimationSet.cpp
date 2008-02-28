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
#include "../Math/Vector3.h"
#include "../DataStream.h"
#include "../StackAlloc.h"

#include "Device.h"
#include "Mesh.h"
#include "ProgressiveMesh.h"
#include "PatchMesh.h"
#include "SkinInfo.h"
#include "AnimationFrame.h"
#include "AnimationSet.h"
#include "Direct3D9Exception.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	AnimationSet::AnimationSet( ID3DXAnimationSet* pointer )
	{
		Construct( pointer );
	}

	AnimationSet::AnimationSet( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	AnimationSet^ AnimationSet::FromPointer( ID3DXAnimationSet* pointer )
	{
		AnimationSet^ tableEntry = safe_cast<AnimationSet^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew AnimationSet( pointer );
	}

	AnimationSet^ AnimationSet::FromPointer( IntPtr pointer )
	{
		AnimationSet^ tableEntry = safe_cast<AnimationSet^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew AnimationSet( pointer );
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

	AnimationOutput^ AnimationSet::GetTransformation( double periodicPosition, int animation )
	{
		Vector3 scale;
		Vector3 translation;
		Quaternion rotation;

		HRESULT hr = InternalPointer->GetSRT( periodicPosition, animation, reinterpret_cast<D3DXVECTOR3*>( &scale ), 
			reinterpret_cast<D3DXQUATERNION*>( &rotation ), reinterpret_cast<D3DXVECTOR3*>( &translation ) );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		AnimationOutput^ output = gcnew AnimationOutput();
		output->Flags = AnimationOutputFlags::Rotation | AnimationOutputFlags::Scale | AnimationOutputFlags::Translation;
		output->Scaling = scale;
		output->Translation = translation;
		output->Rotation = rotation;

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

	CallbackKey::CallbackKey( const D3DXKEY_CALLBACK &key )
	{
		Time = key.Time;
		Data = IntPtr( key.pCallbackData );
	}

	bool CallbackKey::operator == ( CallbackKey left, CallbackKey right )
	{
		return CallbackKey::Equals( left, right );
	}

	bool CallbackKey::operator != ( CallbackKey left, CallbackKey right )
	{
		return !CallbackKey::Equals( left, right );
	}

	int CallbackKey::GetHashCode()
	{
		return Time.GetHashCode() + Data.GetHashCode();
	}

	bool CallbackKey::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<CallbackKey>( value ) );
	}

	bool CallbackKey::Equals( CallbackKey value )
	{
		return ( Time == value.Time && Data == value.Data );
	}

	bool CallbackKey::Equals( CallbackKey% value1, CallbackKey% value2 )
	{
		return ( value1.Time == value2.Time && value1.Data == value2.Data );
	}

	RotationKey::RotationKey( const D3DXKEY_QUATERNION &key )
	{
		Time = key.Time;
		Value = Quaternion( key.Value.x, key.Value.y, key.Value.z, key.Value.w );
	}

	bool RotationKey::operator == ( RotationKey left, RotationKey right )
	{
		return RotationKey::Equals( left, right );
	}

	bool RotationKey::operator != ( RotationKey left, RotationKey right )
	{
		return !RotationKey::Equals( left, right );
	}

	int RotationKey::GetHashCode()
	{
		return Time.GetHashCode() + Value.GetHashCode();
	}

	bool RotationKey::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<RotationKey>( value ) );
	}

	bool RotationKey::Equals( RotationKey value )
	{
		return ( Time == value.Time && Value == value.Value );
	}

	bool RotationKey::Equals( RotationKey% value1, RotationKey% value2 )
	{
		return ( value1.Time == value2.Time && value1.Value == value2.Value );
	}

	ScaleKey::ScaleKey( const D3DXKEY_VECTOR3 &key )
	{
		Time = key.Time;
		Value = Vector3( key.Value.x, key.Value.y, key.Value.z );
	}

	bool ScaleKey::operator == ( ScaleKey left, ScaleKey right )
	{
		return ScaleKey::Equals( left, right );
	}

	bool ScaleKey::operator != ( ScaleKey left, ScaleKey right )
	{
		return !ScaleKey::Equals( left, right );
	}

	int ScaleKey::GetHashCode()
	{
		return Time.GetHashCode() + Value.GetHashCode();
	}

	bool ScaleKey::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ScaleKey>( value ) );
	}

	bool ScaleKey::Equals( ScaleKey value )
	{
		return ( Time == value.Time && Value == value.Value );
	}

	bool ScaleKey::Equals( ScaleKey% value1, ScaleKey% value2 )
	{
		return ( value1.Time == value2.Time && value1.Value == value2.Value );
	}

	TranslationKey::TranslationKey( const D3DXKEY_VECTOR3 &key )
	{
		Time = key.Time;
		Value = Vector3( key.Value.x, key.Value.y, key.Value.z );
	}

	bool TranslationKey::operator == ( TranslationKey left, TranslationKey right )
	{
		return TranslationKey::Equals( left, right );
	}

	bool TranslationKey::operator != ( TranslationKey left, TranslationKey right )
	{
		return !TranslationKey::Equals( left, right );
	}

	int TranslationKey::GetHashCode()
	{
		return Time.GetHashCode() + Value.GetHashCode();
	}

	bool TranslationKey::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<TranslationKey>( value ) );
	}

	bool TranslationKey::Equals( TranslationKey value )
	{
		return ( Time == value.Time && Value == value.Value );
	}

	bool TranslationKey::Equals( TranslationKey% value1, TranslationKey% value2 )
	{
		return ( value1.Time == value2.Time && value1.Value == value2.Value );
	}

	CompressedAnimationSet::CompressedAnimationSet( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	CompressedAnimationSet::CompressedAnimationSet( String^ name, double ticksPerSecond,
		SlimDX::Direct3D9::PlaybackType playbackType, DataStream^ compressedData,
		array<CallbackKey>^ callbackKeys )
	{
		LPD3DXCOMPRESSEDANIMATIONSET pointer;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		int count = callbackKeys->Length;

		stack_vector<D3DXKEY_CALLBACK> keys( count );
		for( int i = 0; i < count; i++ )
		{
			keys[i].Time = callbackKeys[i].Time;
			keys[i].pCallbackData = callbackKeys[i].Data.ToPointer();
		}

		HRESULT hr = D3DXCreateCompressedAnimationSet( reinterpret_cast<LPCSTR>( pinnedName ), ticksPerSecond,
			static_cast<D3DXPLAYBACK_TYPE>( playbackType ), compressedData->GetD3DBuffer(), count,
			&keys[0], &pointer );

		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(pointer);
	}

	array<CallbackKey>^ CompressedAnimationSet::GetCallbackKeys()
	{
		int count = CallbackKeyCount;
		stack_vector<D3DXKEY_CALLBACK> keys( count );

		HRESULT hr = CASPointer->GetCallbackKeys( &keys[0] );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			return nullptr;
		}

		array<CallbackKey>^ results = gcnew array<CallbackKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = CallbackKey( keys[i] );

		return results;
	}

	DataStream^ CompressedAnimationSet::GetCompressedData()
	{
		LPD3DXBUFFER buffer;

		HRESULT hr = CASPointer->GetCompressedData( &buffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew DataStream( buffer );
	}

	int CompressedAnimationSet::CallbackKeyCount::get()
	{
		return CASPointer->GetNumCallbackKeys();
	}

	SlimDX::Direct3D9::PlaybackType CompressedAnimationSet::PlaybackType::get()
	{
		return static_cast<SlimDX::Direct3D9::PlaybackType>( CASPointer->GetPlaybackType() );
	}

	double CompressedAnimationSet::SourceTicksPerSecond::get()
	{
		return CASPointer->GetSourceTicksPerSecond();
	}

	KeyframedAnimationSet::KeyframedAnimationSet( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	KeyframedAnimationSet::KeyframedAnimationSet( String^ name, double ticksPerSecond, SlimDX::Direct3D9::PlaybackType playbackType,
		int animationCount, array<CallbackKey>^ callbackKeys )
	{
		LPD3DXKEYFRAMEDANIMATIONSET pointer;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		int count = callbackKeys->Length;

		stack_vector<D3DXKEY_CALLBACK> keys( count );
		for( int i = 0; i < count; i++ )
		{
			keys[i].Time = callbackKeys[i].Time;
			keys[i].pCallbackData = callbackKeys[i].Data.ToPointer();
		}

		HRESULT hr = D3DXCreateKeyframedAnimationSet( reinterpret_cast<LPCSTR>( pinnedName ), ticksPerSecond, static_cast<D3DXPLAYBACK_TYPE>( playbackType ),
			animationCount, count, &keys[0], &pointer );

		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(pointer);
	}

	DataStream^ KeyframedAnimationSet::Compress( float lossiness )
	{
		LPD3DXBUFFER data;

		HRESULT hr = KASPointer->Compress( D3DXCOMPRESS_DEFAULT, lossiness, NULL, &data);
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew DataStream( data );
	}

	DataStream^ KeyframedAnimationSet::Compress( float lossiness, Frame^ frame )
	{
		LPD3DXBUFFER data;

		HRESULT hr = KASPointer->Compress( D3DXCOMPRESS_DEFAULT, lossiness, frame->Pointer, &data);
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew DataStream( data );
	}

	CallbackKey KeyframedAnimationSet::GetCallbackKey( int animation )
	{
		D3DXKEY_CALLBACK key;

		HRESULT hr = KASPointer->GetCallbackKey( animation, &key );
		RECORD_D3D9( hr );

		return CallbackKey( key );
	}

	array<CallbackKey>^ KeyframedAnimationSet::GetCallbackKeys()
	{
		int count = CallbackKeyCount;
		stack_vector<D3DXKEY_CALLBACK> keys( count );

		HRESULT hr = KASPointer->GetCallbackKeys( &keys[0] );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			return nullptr;
		}

		array<CallbackKey>^ results = gcnew array<CallbackKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = CallbackKey( keys[i] );

		return results;
	}

	Result KeyframedAnimationSet::SetCallbackKey( int animation, CallbackKey callbackKey )
	{
		D3DXKEY_CALLBACK key;
		key.Time = callbackKey.Time;
		key.pCallbackData = callbackKey.Data.ToPointer();

		HRESULT hr = KASPointer->SetCallbackKey( animation, &key );
		return RECORD_D3D9( hr );
	}

	RotationKey KeyframedAnimationSet::GetRotationKey( int animation, int key )
	{
		D3DXKEY_QUATERNION qkey;

		HRESULT hr = KASPointer->GetRotationKey( animation, key, &qkey );
		RECORD_D3D9( hr );

		return RotationKey( qkey );
	}

	array<RotationKey>^ KeyframedAnimationSet::GetRotationKeys( int animation )
	{
		int count = GetRotationKeyCount( animation );
		stack_vector<D3DXKEY_QUATERNION> keys(count);

		HRESULT hr = KASPointer->GetRotationKeys( animation, &keys[0] );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			return nullptr;
		}

		array<RotationKey>^ results = gcnew array<RotationKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = RotationKey( keys[i] );

		return results;
	}

	Result KeyframedAnimationSet::SetRotationKey( int animation, int key, RotationKey callbackKey )
	{
		D3DXKEY_QUATERNION qkey;
		qkey.Time = callbackKey.Time;
		qkey.Value = D3DXQUATERNION( callbackKey.Value.X, callbackKey.Value.Y, callbackKey.Value.Z, callbackKey.Value.W );

		HRESULT hr = KASPointer->SetRotationKey( animation, key, &qkey );
		return RECORD_D3D9( hr );
	}

	Result KeyframedAnimationSet::UnregisterRotationKey( int animation, int key )
	{
		HRESULT hr = KASPointer->UnregisterRotationKey( animation, key );
		return RECORD_D3D9( hr );
	}

	int KeyframedAnimationSet::GetRotationKeyCount( int animation )
	{
		return KASPointer->GetNumRotationKeys( animation );
	}

	ScaleKey KeyframedAnimationSet::GetScaleKey( int animation, int key )
	{
		D3DXKEY_VECTOR3 qkey;

		HRESULT hr = KASPointer->GetScaleKey( animation, key, &qkey );
		RECORD_D3D9( hr );

		return ScaleKey( qkey );
	}

	array<ScaleKey>^ KeyframedAnimationSet::GetScaleKeys( int animation )
	{
		int count = GetScaleKeyCount( animation );
		stack_vector<D3DXKEY_VECTOR3> keys(count);

		HRESULT hr = KASPointer->GetScaleKeys( animation, &keys[0] );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			return nullptr;
	    }

		array<ScaleKey>^ results = gcnew array<ScaleKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = ScaleKey( keys[i] );

		return results;
	}

	Result KeyframedAnimationSet::SetScaleKey( int animation, int key, ScaleKey callbackKey )
	{
		D3DXKEY_VECTOR3 qkey;
		qkey.Time = callbackKey.Time;
		qkey.Value = D3DXVECTOR3( callbackKey.Value.X, callbackKey.Value.Y, callbackKey.Value.Z );

		HRESULT hr = KASPointer->SetScaleKey( animation, key, &qkey );
		return RECORD_D3D9( hr );
	}

	Result KeyframedAnimationSet::UnregisterScaleKey( int animation, int key )
	{
		HRESULT hr = KASPointer->UnregisterScaleKey( animation, key );
		return RECORD_D3D9( hr );
	}

	int KeyframedAnimationSet::GetScaleKeyCount( int animation )
	{
		return KASPointer->GetNumScaleKeys( animation );
	}

	TranslationKey KeyframedAnimationSet::GetTranslationKey( int animation, int key )
	{
		D3DXKEY_VECTOR3 qkey;

		HRESULT hr = KASPointer->GetTranslationKey( animation, key, &qkey );
		RECORD_D3D9( hr );

		return TranslationKey( qkey );
	}

	array<TranslationKey>^ KeyframedAnimationSet::GetTranslationKeys( int animation )
	{
		int count = GetTranslationKeyCount( animation );
		stack_vector<D3DXKEY_VECTOR3> keys(count);

		HRESULT hr = KASPointer->GetTranslationKeys( animation, &keys[0] );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			return nullptr;
		}

		array<TranslationKey>^ results = gcnew array<TranslationKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = TranslationKey( keys[i] );

		return results;
	}

	Result KeyframedAnimationSet::SetTranslationKey( int animation, int key, TranslationKey callbackKey )
	{
		D3DXKEY_VECTOR3 qkey;
		qkey.Time = callbackKey.Time;
		qkey.Value = D3DXVECTOR3( callbackKey.Value.X, callbackKey.Value.Y, callbackKey.Value.Z );

		HRESULT hr = KASPointer->SetTranslationKey( animation, key, &qkey );
		return RECORD_D3D9( hr );
	}

	Result KeyframedAnimationSet::UnregisterTranslationKey( int animation, int key )
	{
		HRESULT hr = KASPointer->UnregisterTranslationKey( animation, key );
		return RECORD_D3D9( hr );
	}

	int KeyframedAnimationSet::GetTranslationKeyCount( int animation )
	{
		return KASPointer->GetNumTranslationKeys( animation );
	}

	int KeyframedAnimationSet::RegisterAnimationKeys( String^ name, array<ScaleKey>^ scaleKeys,
		array<RotationKey>^ rotationKeys, array<TranslationKey>^ translationKeys )
	{
		DWORD result;
		int scaleCount = scaleKeys->Length;
		int rotateCount = rotationKeys->Length;
		int translateCount = translationKeys->Length;

		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		stack_vector<D3DXKEY_VECTOR3> scales( scaleCount );
		stack_vector<D3DXKEY_QUATERNION> rotations( rotateCount );
		stack_vector<D3DXKEY_VECTOR3> translations( translateCount );

		HRESULT hr = KASPointer->RegisterAnimationSRTKeys( reinterpret_cast<LPCSTR>( pinnedName ), scaleCount, rotateCount,
			translateCount, &scales[0], &rotations[0], &translations[0], &result );
		RECORD_D3D9( hr );

		if( Result::Last.IsFailure )
			return 0;

		return result;
	}

	Result KeyframedAnimationSet::UnregisterAnimation( int animation )
	{
		HRESULT hr = KASPointer->UnregisterAnimation( animation );
		return RECORD_D3D9( hr );
	}

	int KeyframedAnimationSet::CallbackKeyCount::get()
	{
		return KASPointer->GetNumCallbackKeys();
	}

	SlimDX::Direct3D9::PlaybackType KeyframedAnimationSet::PlaybackType::get()
	{
		return static_cast<SlimDX::Direct3D9::PlaybackType>( KASPointer->GetPlaybackType() );
	}

	double KeyframedAnimationSet::SourceTicksPerSecond::get()
	{
		return KASPointer->GetSourceTicksPerSecond();
	}
}
}