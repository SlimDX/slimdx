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
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class AnimationSet;
		ref class AnimationOutput;

		public delegate void AnimationCallback( int track, Object^ data );

		public enum class TransitionType : Int32
		{
			Linear = D3DXTRANSITION_LINEAR,
			EaseInEaseOut = D3DXTRANSITION_EASEINEASEOUT
		};

		public enum class TrackPriority : Int32
		{
			Low = D3DXPRIORITY_LOW,
			High = D3DXPRIORITY_HIGH
		};

		public enum class EventType : Int32
		{
			TrackSpeed = D3DXEVENT_TRACKSPEED,
			TrackWeight = D3DXEVENT_TRACKWEIGHT,
			TrackPosition = D3DXEVENT_TRACKPOSITION,
			TrackEnable = D3DXEVENT_TRACKENABLE,
			PriorityBlend = D3DXEVENT_PRIORITYBLEND
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class EventDescription
		{
		public:
			property EventType Type;
			property int Track;
			property double StartTime;
			property double Duration;
			property TransitionType Transition;
			property float Weight;
			property float Speed;
			property double Position;
			property bool Enabled;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class TrackDescription
		{
		public:
			property TrackPriority Priority;
			property float Weight;
			property float Speed;
			property double Position;
			property bool Enabled;
		};		

		public ref class AnimationController : public DirectXBase
		{
			DXOBJECT(ID3DXAnimationController);

		internal:
			AnimationController( ID3DXAnimationController *controller );

		public:
			AnimationController( IntPtr pointer );
			AnimationController( int maxAnimationOutputs, int maxAnimationSets, int maxTracks, int maxEvents );
			virtual ~AnimationController() { Destruct(); }

			void AdvanceTime( double time, AnimationCallback^ handler );
			AnimationController^ Clone( int maxAnimationOutputs, int maxAnimationSets, int maxTracks, int maxEvents );
			
			AnimationSet^ GetAnimationSet( int index );
			AnimationSet^ GetAnimationSet( String^ name );
			int GetCurrentTrackEvent( int track, EventType eventType );

			EventDescription GetEventDescription( int handle );
			AnimationSet^ GetTrackAnimationSet( int track );
			TrackDescription GetTrackDescription( int track );

			int GetUpcomingPriorityBlend( int handle );
			int GetUpcomingTrackEvent( int track, int handle );

			int KeyPriorityBlend( float newBlendWeight, double startTime, double duration, TransitionType transition );
			int KeyTrackEnable( int track, bool enable, double startTime );
			int KeyTrackPosition( int track, double position, double startTime );
			int KeyTrackSpeed( int track, float newSpeed, double startTime, double duration, TransitionType transition );
			int KeyTrackWeight( int track, float newWeight, double startTime, double duration, TransitionType transition );

			void RegisterAnimationOutput( String^ name, AnimationOutput^ output );
			void RegisterAnimationSet( AnimationSet^ set );
			void ResetTime();

			void SetTrackAnimationSet( int track, AnimationSet^ set );
			void SetTrackDescription( int track, TrackDescription description );
			void EnableTrack( int track );
			void DisableTrack( int track );
			void SetTrackPosition( int track, double position );
			void SetTrackPriority( int track, TrackPriority priority );
			void SetTrackSpeed( int track, float speed );
			void SetTrackWeight( int track, float weight );

			void UnkeyAllPriorityBlends();
			void UnkeyAllTrackEvents( int track );
			void UnkeyEvent( int handle );
			void UnregisterAnimationSet( AnimationSet^ set );

			bool ValidateEvent( int handle );

			property double Time { double get(); }
			property int CurrentPriorityBlend { int get(); }
			property float PriorityBlend { float get(); void set( float value ); }
			property int AnimationSetCount { int get(); }
			property int MaxAnimationOutputs { int get(); }
			property int MaxAnimationSets { int get(); }
			property int MaxTracks { int get(); }
			property int MaxEvents { int get(); }
		};
	}
}
