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

#include "../DataStream.h"
#include "../BaseObject.h"
#include "../Math/Math.h"
#include "GraphicsException.h"
#include "AnimationSet.h"
#include "AnimationController.h"

namespace SlimDX
{
namespace Direct3D9
{
	AnimationController::AnimationController( ID3DXAnimationController *controller )
	{
		Construct(controller);
	}

	AnimationController::AnimationController( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	AnimationController::AnimationController( int maxAnimationOutputs, int maxAnimationSets, int maxTracks, int maxEvents )
	{
		HRESULT hr = D3DXCreateAnimationController( maxAnimationOutputs, maxAnimationSets, maxTracks, maxEvents,
			reinterpret_cast<LPD3DXANIMATIONCONTROLLER*>( InternalPointer ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			throw gcnew GraphicsException();
	}

	void AnimationController::AdvanceTime( double time, AnimationCallback^ handler )
	{
		HRESULT hr = InternalPointer->AdvanceTime( time, reinterpret_cast< LPD3DXANIMATIONCALLBACKHANDLER >(
			Marshal::GetFunctionPointerForDelegate( handler ).ToPointer() ) );
		GraphicsException::CheckHResult( hr );
	}

	AnimationController^ AnimationController::Clone( int maxAnimationOutputs, int maxAnimationSets, int maxTracks, int maxEvents )
	{
		LPD3DXANIMATIONCONTROLLER pointer;

		HRESULT hr = InternalPointer->CloneAnimationController( maxAnimationOutputs, maxAnimationSets, maxTracks, maxEvents, &pointer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew AnimationController( pointer );
	}

	AnimationSet^ AnimationController::GetAnimationSet( int index )
	{
		LPD3DXANIMATIONSET set;

		HRESULT hr = InternalPointer->GetAnimationSet( index, &set );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew AnimationSet( set );
	}

	AnimationSet^ AnimationController::GetAnimationSet( String^ name )
	{
		LPD3DXANIMATIONSET set;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		HRESULT hr = InternalPointer->GetAnimationSetByName( reinterpret_cast<LPCSTR>( pinnedName ), &set );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew AnimationSet( set );
	}

	int AnimationController::GetCurrentTrackEvent( int track, EventType eventType )
	{
		return InternalPointer->GetCurrentTrackEvent( track, static_cast<D3DXEVENT_TYPE>( eventType ) );
	}

	EventDescription AnimationController::GetEventDescription( int handle )
	{
		EventDescription result;

		HRESULT hr = InternalPointer->GetEventDesc( handle, reinterpret_cast<LPD3DXEVENT_DESC>( &result ) );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	AnimationSet^ AnimationController::GetTrackAnimationSet( int track )
	{
		LPD3DXANIMATIONSET set;

		HRESULT hr = InternalPointer->GetTrackAnimationSet( track, &set );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew AnimationSet( set );
	}

	TrackDescription AnimationController::GetTrackDescription( int track )
	{
		TrackDescription result;

		HRESULT hr = InternalPointer->GetTrackDesc( track, reinterpret_cast<LPD3DXTRACK_DESC>( &result ) );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	int AnimationController::GetUpcomingPriorityBlend( int handle )
	{
		return InternalPointer->GetUpcomingPriorityBlend( handle );
	}

	int AnimationController::GetUpcomingTrackEvent( int track, int handle )
	{
		return InternalPointer->GetUpcomingTrackEvent( track, handle );
	}

	int AnimationController::KeyPriorityBlend( float newBlendWeight, double startTime, double duration, TransitionType transition )
	{
		return InternalPointer->KeyPriorityBlend( newBlendWeight, startTime, duration, static_cast<D3DXTRANSITION_TYPE>( transition ) );
	}

	int AnimationController::KeyTrackEnable( int track, bool enable, double startTime )
	{
		return InternalPointer->KeyTrackEnable( track, enable, startTime );
	}

	int AnimationController::KeyTrackPosition( int track, double position, double startTime )
	{
		return InternalPointer->KeyTrackPosition( track, position, startTime );
	}

	int AnimationController::KeyTrackSpeed( int track, float newSpeed, double startTime, double duration, TransitionType transition )
	{
		return InternalPointer->KeyTrackSpeed( track, newSpeed, startTime, duration, static_cast<D3DXTRANSITION_TYPE>( transition ) );
	}

	int AnimationController::KeyTrackWeight( int track, float newWeight, double startTime, double duration, TransitionType transition )
	{
		return InternalPointer->KeyTrackWeight( track, newWeight, startTime, duration, static_cast<D3DXTRANSITION_TYPE>( transition ) );
	}

	void AnimationController::RegisterAnimationOutput( String^ name, AnimationOutput^ output )
	{
		D3DXMATRIX *matrix = NULL;
		D3DXVECTOR3 *scale = NULL;
		D3DXVECTOR3 *translation = NULL;
		D3DXQUATERNION *rotation = NULL;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		pin_ptr<Matrix> pinMatrix;
		pin_ptr<Vector3> pinScale;
		pin_ptr<Vector3> pinTranslation;
		pin_ptr<Quaternion> pinQuaternion;

		if( (output->Flags & AnimationOutputFlags::Transformation) == AnimationOutputFlags::Transformation )
		{
			pinMatrix = &output->Transformation;
			matrix = reinterpret_cast<D3DXMATRIX*>( pinMatrix );
		}

		if( (output->Flags & AnimationOutputFlags::Scale) == AnimationOutputFlags::Scale )
		{
			pinScale = &output->Scaling;
			scale = reinterpret_cast<D3DXVECTOR3*>( pinScale );
		}

		if( (output->Flags & AnimationOutputFlags::Translation) == AnimationOutputFlags::Translation )
		{
			pinTranslation = &output->Translation;
			translation = reinterpret_cast<D3DXVECTOR3*>( pinTranslation );
		}

		if( (output->Flags & AnimationOutputFlags::Rotation) == AnimationOutputFlags::Rotation )
		{
			pinQuaternion = &output->Rotation;
			rotation = reinterpret_cast<D3DXQUATERNION*>( pinQuaternion );
		}

		HRESULT hr = InternalPointer->RegisterAnimationOutput( reinterpret_cast<LPCSTR>( pinnedName ), matrix, scale, rotation, translation );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::RegisterAnimationSet( AnimationSet^ set )
	{
		HRESULT hr = InternalPointer->RegisterAnimationSet( reinterpret_cast<LPD3DXANIMATIONSET>( set->ComPointer.ToPointer() ) );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::ResetTime()
	{
		HRESULT hr = InternalPointer->ResetTime();
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::SetTrackAnimationSet( int track, AnimationSet^ set )
	{
		HRESULT hr = InternalPointer->SetTrackAnimationSet( track, reinterpret_cast<LPD3DXANIMATIONSET>( set->ComPointer.ToPointer() ) );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::SetTrackDescription( int track, TrackDescription description )
	{
		HRESULT hr = InternalPointer->SetTrackDesc( track, reinterpret_cast<LPD3DXTRACK_DESC>( &description ) );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::EnableTrack( int track )
	{
		HRESULT hr = InternalPointer->SetTrackEnable( track, true );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::DisableTrack( int track )
	{
		HRESULT hr = InternalPointer->SetTrackEnable( track, false );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::SetTrackPosition( int track, double position )
	{
		HRESULT hr = InternalPointer->SetTrackPosition( track, position );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::SetTrackPriority( int track, TrackPriority priority )
	{
		HRESULT hr = InternalPointer->SetTrackPriority( track, static_cast<D3DXPRIORITY_TYPE>( priority ) );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::SetTrackSpeed( int track, float speed )
	{
		HRESULT hr = InternalPointer->SetTrackSpeed( track, speed );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::SetTrackWeight( int track, float weight )
	{
		HRESULT hr = InternalPointer->SetTrackWeight( track, weight );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::UnkeyAllPriorityBlends()
	{
		HRESULT hr = InternalPointer->UnkeyAllPriorityBlends();
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::UnkeyAllTrackEvents( int track )
	{
		HRESULT hr = InternalPointer->UnkeyAllTrackEvents( track );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::UnkeyEvent( int handle )
	{
		HRESULT hr = InternalPointer->UnkeyEvent( handle );
		GraphicsException::CheckHResult( hr );
	}

	void AnimationController::UnregisterAnimationSet( AnimationSet^ set )
	{
		HRESULT hr = InternalPointer->UnregisterAnimationSet( reinterpret_cast<LPD3DXANIMATIONSET>( set->ComPointer.ToPointer() ) );
		GraphicsException::CheckHResult( hr );
	}

	bool AnimationController::ValidateEvent( int handle )
	{
		HRESULT hr = InternalPointer->ValidateEvent( handle );

		return (hr == S_OK);
	}

	double AnimationController::Time::get()
	{
		return InternalPointer->GetTime();
	}

	int AnimationController::CurrentPriorityBlend::get()
	{
		return InternalPointer->GetCurrentPriorityBlend();
	}

	float AnimationController::PriorityBlend::get()
	{
		return InternalPointer->GetPriorityBlend();
	}

	void AnimationController::PriorityBlend::set( float value )
	{
		InternalPointer->SetPriorityBlend( value );
	}

	int AnimationController::AnimationSetCount::get()
	{
		return InternalPointer->GetNumAnimationSets();
	}

	int AnimationController::MaxAnimationOutputs::get()
	{
		return InternalPointer->GetMaxNumAnimationOutputs();
	}

	int AnimationController::MaxAnimationSets::get()
	{
		return InternalPointer->GetMaxNumAnimationSets();
	}

	int AnimationController::MaxTracks::get()
	{
		return InternalPointer->GetMaxNumTracks();
	}

	int AnimationController::MaxEvents::get()
	{
		return InternalPointer->GetMaxNumEvents();
	}
}
}
