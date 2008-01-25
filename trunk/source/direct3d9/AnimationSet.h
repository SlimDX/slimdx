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

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class Frame;

		[Flags]
		public enum class AnimationOutputFlags : Int32
		{
			None,
			Transformation,
			Translation,
			Scale,
			Rotation
		};

		public enum class CallbackSearchFlags : Int32
		{
			SearchExcludingInitialPosition = D3DXCALLBACK_SEARCH_EXCLUDING_INITIAL_POSITION,
			SearchBehindInitialPosition = D3DXCALLBACK_SEARCH_BEHIND_INITIAL_POSITION
		};

		public enum class PlaybackType : Int32
		{
			Loop = D3DXPLAY_LOOP,
			Once = D3DXPLAY_ONCE,
			PingPong = D3DXPLAY_PINGPONG
		};

		public ref class AnimationOutput
		{
		public:
			AnimationOutput() { }

			property AnimationOutputFlags Flags;
			property Matrix Transformation;
			property Vector3 Scaling;
			property Vector3 Translation;
			property Quaternion Rotation;
		};

		public value class CallbackKey
		{
		internal:
			CallbackKey( const D3DXKEY_CALLBACK &key );

		public:
			property float Time;
			property IntPtr Data;
		};

		public value class RotationKey
		{
		internal:
			RotationKey( const D3DXKEY_QUATERNION &key );

		public:
			property float Time;
			property Quaternion Value;
		};

		public value class ScaleKey
		{
		internal:
			ScaleKey( const D3DXKEY_VECTOR3 &key );

		public:
			property float Time;
			property Vector3 Value;
		};

		public value class TranslationKey
		{
		internal:
			TranslationKey( const D3DXKEY_VECTOR3 &key );

		public:
			property float Time;
			property Vector3 Value;
		};

		public ref class AnimationSet : public ComObject
		{
			COMOBJECT(ID3DXAnimationSet);

		protected:
			AnimationSet() { }

		internal:
			AnimationSet( ID3DXAnimationSet* set );

		public:
			AnimationSet( IntPtr pointer );
			virtual ~AnimationSet() { Destruct(); }

			int GetAnimationIndex( String^ name );
			String^ GetAnimationName( int index );
			IntPtr GetCallback( double position, CallbackSearchFlags flags, [Out] double% callbackPosition );
			AnimationOutput^ GetTransformation( double periodicPosition, int animation );
			double GetPeriodicPosition( double position );

			property String^ Name { String^ get(); }
			property int AnimationCount { int get(); }
			property double Period { double get(); }
		};

		public ref class CompressedAnimationSet : public AnimationSet
		{
		internal:
			property ID3DXCompressedAnimationSet* CASPointer
			{
				ID3DXCompressedAnimationSet* get() { return static_cast<ID3DXCompressedAnimationSet*>( InternalPointer ); }
			}

		public:
			CompressedAnimationSet( IntPtr pointer );
			CompressedAnimationSet( String^ name, double ticksPerSecond, PlaybackType playbackType, 
				DataStream^ compressedData, array<CallbackKey>^ callbackKeys );
			virtual ~CompressedAnimationSet() { }

			array<CallbackKey>^ GetCallbackKeys();
			DataStream^ GetCompressedData();

			property int CallbackKeyCount { int get(); }
			property PlaybackType PlaybackType { SlimDX::Direct3D9::PlaybackType get(); }
			property double SourceTicksPerSecond { double get(); }
		};

		public ref class KeyframedAnimationSet : public AnimationSet
		{
		internal:
			property ID3DXKeyframedAnimationSet* KASPointer
			{
				ID3DXKeyframedAnimationSet* get() { return static_cast<ID3DXKeyframedAnimationSet*>( InternalPointer ); }
			}

		public:
			KeyframedAnimationSet( IntPtr pointer );
			KeyframedAnimationSet( String^ name, double ticksPerSecond, PlaybackType playbackType,
				int animationCount, array<CallbackKey>^ callbackKeys );
			virtual ~KeyframedAnimationSet() { }

			DataStream^ Compress( float lossiness );
			DataStream^ Compress( float lossiness, Frame^ frameHierarchy );

			CallbackKey GetCallbackKey( int animation );
			array<CallbackKey>^ GetCallbackKeys();
			void SetCallbackKey( int animation, CallbackKey callbackKey );

			RotationKey GetRotationKey( int animation, int key );
			array<RotationKey>^ GetRotationKeys( int animation );
			void SetRotationKey( int animation, int key, RotationKey rotationKey );
			void UnregisterRotationKey( int animation, int key );
			int GetRotationKeyCount( int animation );

			ScaleKey GetScaleKey( int animation, int key );
			array<ScaleKey>^ GetScaleKeys( int animation );
			void SetScaleKey( int animation, int key, ScaleKey scaleKey );
			void UnregisterScaleKey( int animation, int key );
			int GetScaleKeyCount( int animation );

			TranslationKey GetTranslationKey( int animation, int key );
			array<TranslationKey>^ GetTranslationKeys( int animation );
			void SetTranslationKey( int animation, int key, TranslationKey translationKey );
			void UnregisterTranslationKey( int animation, int key );
			int GetTranslationKeyCount( int animation );

			int RegisterAnimationKeys( String^ name, array<ScaleKey>^ scaleKeys, 
				array<RotationKey>^ rotationKeys, array<TranslationKey>^ translationKeys );
			void UnregisterAnimation( int animation );

			property int CallbackKeyCount { int get(); }
			property PlaybackType PlaybackType { SlimDX::Direct3D9::PlaybackType get(); }
			property double SourceTicksPerSecond { double get(); }
		};
	}
}