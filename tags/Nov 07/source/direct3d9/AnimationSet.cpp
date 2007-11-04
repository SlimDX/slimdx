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

#include "../DirectXObject.h"
#include "../Math/Math.h"
#include "GraphicsException.h"
#include "Device.h"
#include "Mesh.h"
#include "SkinInfo.h"
#include "AnimationFrame.h"
#include "AnimationSet.h"

namespace SlimDX
{
namespace Direct3D9
{
	AnimationSet::AnimationSet(ID3DXAnimationSet *set) : DirectXObject( set )
	{
	}

	int AnimationSet::GetAnimationIndex( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		int result;

		HRESULT hr = m_Pointer->GetAnimationIndexByName( (LPCSTR) pinnedName, (UINT*) &result );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	String^ AnimationSet::GetAnimationName( int index )
	{
		LPCSTR result;
		HRESULT hr = m_Pointer->GetAnimationNameByIndex( index, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew String( result );
	}

	IntPtr AnimationSet::GetCallback( double position, CallbackSearchFlags flags, [Out] double% callbackPosition )
	{
		pin_ptr<double> pinPosition = &callbackPosition;
		LPVOID data;

		HRESULT hr = m_Pointer->GetCallback( position, ( DWORD )flags, pinPosition, &data );
		GraphicsException::CheckHResult( hr );

		return IntPtr( data );
	}

	AnimationOutput^ AnimationSet::GetTransformation( double periodicPosition, int animation )
	{
		Vector3 scale;
		Vector3 translation;
		Quaternion rotation;

		HRESULT hr = m_Pointer->GetSRT( periodicPosition, animation, (D3DXVECTOR3*) &scale, 
			(D3DXQUATERNION*) &rotation, (D3DXVECTOR3*) &translation );
		GraphicsException::CheckHResult( hr );

		AnimationOutput^ output = gcnew AnimationOutput();
		output->Flags = AnimationOutputFlags::Rotation | AnimationOutputFlags::Scale | AnimationOutputFlags::Translation;
		output->Scaling = scale;
		output->Translation = translation;
		output->Rotation = rotation;

		return output;
	}

	String^ AnimationSet::Name::get()
	{
		return gcnew String( m_Pointer->GetName() );
	}

	int AnimationSet::AnimationCount::get()
	{
		return m_Pointer->GetNumAnimations();
	}

	double AnimationSet::Period::get()
	{
		return m_Pointer->GetPeriod();
	}

	double AnimationSet::GetPeriodicPosition( double position )
	{
		return m_Pointer->GetPeriodicPosition( position );
	}

	CallbackKey::CallbackKey( const D3DXKEY_CALLBACK &key )
	{
		Time = key.Time;
		Data = IntPtr( key.pCallbackData );
	}

	RotationKey::RotationKey( const D3DXKEY_QUATERNION &key )
	{
		Time = key.Time;
		Value = Quaternion( key.Value.x, key.Value.y, key.Value.z, key.Value.w );
	}

	ScaleKey::ScaleKey( const D3DXKEY_VECTOR3 &key )
	{
		Time = key.Time;
		Value = Vector3( key.Value.x, key.Value.y, key.Value.z );
	}

	TranslationKey::TranslationKey( const D3DXKEY_VECTOR3 &key )
	{
		Time = key.Time;
		Value = Vector3( key.Value.x, key.Value.y, key.Value.z );
	}

	CompressedAnimationSet::CompressedAnimationSet( String^ name, double ticksPerSecond,
		SlimDX::Direct3D9::PlaybackType playbackType, BufferWrapper^ compressedData,
		array<CallbackKey>^ callbackKeys )
	{
		LPD3DXCOMPRESSEDANIMATIONSET pointer;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		int count = callbackKeys->Length;

		D3DXKEY_CALLBACK *keys = new D3DXKEY_CALLBACK[count];
		for( int i = 0; i < count; i++ )
		{
			keys[i].Time = callbackKeys[i].Time;
			keys[i].pCallbackData = callbackKeys[i].Data.ToPointer();
		}

		HRESULT hr = D3DXCreateCompressedAnimationSet( (LPCSTR) pinnedName, ticksPerSecond,
			(D3DXPLAYBACK_TYPE) playbackType, (LPD3DXBUFFER) compressedData->ComPointer.ToPointer(), count,
			keys, &pointer );
		GraphicsException::CheckHResult( hr );

		delete[] keys;

		m_Pointer = pointer;
	}

	array<CallbackKey>^ CompressedAnimationSet::GetCallbackKeys()
	{
		int count = CallbackKeyCount;
		D3DXKEY_CALLBACK *keys = new D3DXKEY_CALLBACK[count];

		HRESULT hr = CASPointer->GetCallbackKeys( keys );
		GraphicsException::CheckHResult( hr );

		array<CallbackKey>^ results = gcnew array<CallbackKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = CallbackKey( keys[i] );

		delete[] keys;

		return results;
	}

	BufferWrapper^ CompressedAnimationSet::GetCompressedData()
	{
		LPD3DXBUFFER buffer;

		HRESULT hr = CASPointer->GetCompressedData( &buffer );
		GraphicsException::CheckHResult( hr );

		return gcnew BufferWrapper( buffer );
	}

	int CompressedAnimationSet::CallbackKeyCount::get()
	{
		return CASPointer->GetNumCallbackKeys();
	}

	SlimDX::Direct3D9::PlaybackType CompressedAnimationSet::PlaybackType::get()
	{
		return (SlimDX::Direct3D9::PlaybackType) CASPointer->GetPlaybackType();
	}

	double CompressedAnimationSet::SourceTicksPerSecond::get()
	{
		return CASPointer->GetSourceTicksPerSecond();
	}

	KeyframedAnimationSet::KeyframedAnimationSet( String^ name, double ticksPerSecond, SlimDX::Direct3D9::PlaybackType playbackType,
		int animationCount, array<CallbackKey>^ callbackKeys )
	{
		LPD3DXKEYFRAMEDANIMATIONSET pointer;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		int count = callbackKeys->Length;

		D3DXKEY_CALLBACK *keys = new D3DXKEY_CALLBACK[count];
		for( int i = 0; i < count; i++ )
		{
			keys[i].Time = callbackKeys[i].Time;
			keys[i].pCallbackData = callbackKeys[i].Data.ToPointer();
		}

		HRESULT hr = D3DXCreateKeyframedAnimationSet( (LPCSTR) pinnedName, ticksPerSecond, (D3DXPLAYBACK_TYPE) playbackType,
			animationCount, count, keys, &pointer );
		GraphicsException::CheckHResult( hr );

		delete[] keys;

		m_Pointer = pointer;
	}

	BufferWrapper^ KeyframedAnimationSet::Compress( float lossiness )
	{
		LPD3DXBUFFER data;

		HRESULT hr = KASPointer->Compress( D3DXCOMPRESS_DEFAULT, lossiness, NULL, &data);
		GraphicsException::CheckHResult( hr );

		return gcnew BufferWrapper( data );
	}

	BufferWrapper^ KeyframedAnimationSet::Compress( float lossiness, Frame^ frame )
	{
		LPD3DXBUFFER data;

		HRESULT hr = KASPointer->Compress( D3DXCOMPRESS_DEFAULT, lossiness, frame->Pointer, &data);
		GraphicsException::CheckHResult( hr );

		return gcnew BufferWrapper( data );
	}

	CallbackKey KeyframedAnimationSet::GetCallbackKey( int animation )
	{
		D3DXKEY_CALLBACK key;

		HRESULT hr = KASPointer->GetCallbackKey( animation, &key );
		GraphicsException::CheckHResult( hr );

		return CallbackKey( key );
	}

	array<CallbackKey>^ KeyframedAnimationSet::GetCallbackKeys()
	{
		int count = CallbackKeyCount;
		D3DXKEY_CALLBACK *keys = new D3DXKEY_CALLBACK[count];

		HRESULT hr = KASPointer->GetCallbackKeys( keys );
		GraphicsException::CheckHResult( hr );

		array<CallbackKey>^ results = gcnew array<CallbackKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = CallbackKey( keys[i] );

		delete[] keys;

		return results;
	}

	void KeyframedAnimationSet::SetCallbackKey( int animation, CallbackKey callbackKey )
	{
		D3DXKEY_CALLBACK key;
		key.Time = callbackKey.Time;
		key.pCallbackData = callbackKey.Data.ToPointer();

		HRESULT hr = KASPointer->SetCallbackKey( animation, &key );
		GraphicsException::CheckHResult( hr );
	}

	RotationKey KeyframedAnimationSet::GetRotationKey( int animation, int key )
	{
		D3DXKEY_QUATERNION qkey;

		HRESULT hr = KASPointer->GetRotationKey( animation, key, &qkey );
		GraphicsException::CheckHResult( hr );

		return RotationKey( qkey );
	}

	array<RotationKey>^ KeyframedAnimationSet::GetRotationKeys( int animation )
	{
		int count = GetRotationKeyCount( animation );
		D3DXKEY_QUATERNION *keys = new D3DXKEY_QUATERNION[count];

		HRESULT hr = KASPointer->GetRotationKeys( animation, keys );
		GraphicsException::CheckHResult( hr );

		array<RotationKey>^ results = gcnew array<RotationKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = RotationKey( keys[i] );

		delete[] keys;

		return results;
	}

	void KeyframedAnimationSet::SetRotationKey( int animation, int key, RotationKey callbackKey )
	{
		D3DXKEY_QUATERNION qkey;
		qkey.Time = callbackKey.Time;
		qkey.Value = D3DXQUATERNION( callbackKey.Value.X, callbackKey.Value.Y, callbackKey.Value.Z, callbackKey.Value.W );

		HRESULT hr = KASPointer->SetRotationKey( animation, key, &qkey );
		GraphicsException::CheckHResult( hr );
	}

	void KeyframedAnimationSet::UnregisterRotationKey( int animation, int key )
	{
		HRESULT hr = KASPointer->UnregisterRotationKey( animation, key );
		GraphicsException::CheckHResult( hr );
	}

	int KeyframedAnimationSet::GetRotationKeyCount( int animation )
	{
		return KASPointer->GetNumRotationKeys( animation );
	}

	ScaleKey KeyframedAnimationSet::GetScaleKey( int animation, int key )
	{
		D3DXKEY_VECTOR3 qkey;

		HRESULT hr = KASPointer->GetScaleKey( animation, key, &qkey );
		GraphicsException::CheckHResult( hr );

		return ScaleKey( qkey );
	}

	array<ScaleKey>^ KeyframedAnimationSet::GetScaleKeys( int animation )
	{
		int count = GetScaleKeyCount( animation );
		D3DXKEY_VECTOR3 *keys = new D3DXKEY_VECTOR3[count];

		HRESULT hr = KASPointer->GetScaleKeys( animation, keys );
		GraphicsException::CheckHResult( hr );

		array<ScaleKey>^ results = gcnew array<ScaleKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = ScaleKey( keys[i] );

		delete[] keys;

		return results;
	}

	void KeyframedAnimationSet::SetScaleKey( int animation, int key, ScaleKey callbackKey )
	{
		D3DXKEY_VECTOR3 qkey;
		qkey.Time = callbackKey.Time;
		qkey.Value = D3DXVECTOR3( callbackKey.Value.X, callbackKey.Value.Y, callbackKey.Value.Z );

		HRESULT hr = KASPointer->SetScaleKey( animation, key, &qkey );
		GraphicsException::CheckHResult( hr );
	}

	void KeyframedAnimationSet::UnregisterScaleKey( int animation, int key )
	{
		HRESULT hr = KASPointer->UnregisterScaleKey( animation, key );
		GraphicsException::CheckHResult( hr );
	}

	int KeyframedAnimationSet::GetScaleKeyCount( int animation )
	{
		return KASPointer->GetNumScaleKeys( animation );
	}

	TranslationKey KeyframedAnimationSet::GetTranslationKey( int animation, int key )
	{
		D3DXKEY_VECTOR3 qkey;

		HRESULT hr = KASPointer->GetTranslationKey( animation, key, &qkey );
		GraphicsException::CheckHResult( hr );

		return TranslationKey( qkey );
	}

	array<TranslationKey>^ KeyframedAnimationSet::GetTranslationKeys( int animation )
	{
		int count = GetTranslationKeyCount( animation );
		D3DXKEY_VECTOR3 *keys = new D3DXKEY_VECTOR3[count];

		HRESULT hr = KASPointer->GetTranslationKeys( animation, keys );
		GraphicsException::CheckHResult( hr );

		array<TranslationKey>^ results = gcnew array<TranslationKey>( count );
		for( int i = 0; i < count; i++ )
			results[i] = TranslationKey( keys[i] );

		delete[] keys;

		return results;
	}

	void KeyframedAnimationSet::SetTranslationKey( int animation, int key, TranslationKey callbackKey )
	{
		D3DXKEY_VECTOR3 qkey;
		qkey.Time = callbackKey.Time;
		qkey.Value = D3DXVECTOR3( callbackKey.Value.X, callbackKey.Value.Y, callbackKey.Value.Z );

		HRESULT hr = KASPointer->SetTranslationKey( animation, key, &qkey );
		GraphicsException::CheckHResult( hr );
	}

	void KeyframedAnimationSet::UnregisterTranslationKey( int animation, int key )
	{
		HRESULT hr = KASPointer->UnregisterTranslationKey( animation, key );
		GraphicsException::CheckHResult( hr );
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

		D3DXKEY_VECTOR3* scales = new D3DXKEY_VECTOR3[scaleCount];
		D3DXKEY_QUATERNION* rotations = new D3DXKEY_QUATERNION[rotateCount];
		D3DXKEY_VECTOR3* translations = new D3DXKEY_VECTOR3[translateCount];

		HRESULT hr = KASPointer->RegisterAnimationSRTKeys( (LPCSTR) pinnedName, scaleCount, rotateCount,
			translateCount, scales, rotations, translations, &result );
		GraphicsException::CheckHResult( hr );

		delete[] scales;
		delete[] rotations;
		delete[] translations;

		return result;
	}

	void KeyframedAnimationSet::UnregisterAnimation( int animation )
	{
		HRESULT hr = KASPointer->UnregisterAnimation( animation );
		GraphicsException::CheckHResult( hr );
	}

	int KeyframedAnimationSet::CallbackKeyCount::get()
	{
		return KASPointer->GetNumCallbackKeys();
	}

	SlimDX::Direct3D9::PlaybackType KeyframedAnimationSet::PlaybackType::get()
	{
		return (SlimDX::Direct3D9::PlaybackType) KASPointer->GetPlaybackType();
	}

	double KeyframedAnimationSet::SourceTicksPerSecond::get()
	{
		return KASPointer->GetSourceTicksPerSecond();
	}
}
}