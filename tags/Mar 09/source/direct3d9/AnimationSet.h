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
#pragma once

#include "../math/Quaternion.h"
#include "../math/Matrix.h"
#include "../math/Vector4.h"

#include "CallbackKey.h"
#include "Enums.h"
#include "AnimationOutput.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class Frame;
		ref class AnimationSet;

		class AnimationShim : public ID3DXAnimationSet
		{
		private:
			int refCount;
			gcroot<AnimationSet^> animationSet;
			gcroot<System::Collections::Generic::Dictionary<System::String^, System::Runtime::InteropServices::GCHandle>^> nameHandles;

		public:
			AnimationShim( AnimationSet^ animationSet );
			virtual ~AnimationShim();
			AnimationSet^ GetAnimationSet();

			HRESULT WINAPI QueryInterface( const IID &iid, LPVOID *ppv );
			ULONG   WINAPI AddRef();
			ULONG   WINAPI Release();

			HRESULT WINAPI GetAnimationIndexByName( LPCSTR Name, UINT *pIndex );
			HRESULT WINAPI GetAnimationNameByIndex( UINT Index, LPCSTR *ppName );
			HRESULT WINAPI GetCallback( DOUBLE Position, DWORD Flags, DOUBLE *pCallbackPosition, LPVOID *ppCallbackData );
			LPCSTR	WINAPI GetName();
			UINT	WINAPI GetNumAnimations();
			DOUBLE	WINAPI GetPeriod();
			DOUBLE	WINAPI GetPeriodicPosition( DOUBLE Position );
			HRESULT WINAPI GetSRT( DOUBLE PeriodicPosition, UINT Animation, D3DXVECTOR3 *pScale, D3DXQUATERNION *pRotation, D3DXVECTOR3 *pTranslation );
		};

		/// <summary>
		/// This interface encapsulates the minimum functionality required of an animation set by an animation
		/// controller. Advanced users might want to implement this interface themselves to suit their
		/// specialized needs; for most users, however, the derived CompressedAnimationSet and
		/// KeyframedAnimationSet interfaces should suffice.
		/// </summary>
		/// <unmanaged>ID3DXAnimationSet</unmanaged>
		public ref class AnimationSet abstract : public ComObject
		{
			COMOBJECT_BASE(ID3DXAnimationSet);

		private:
			void Free();

		internal:
			AnimationShim *shim;

		protected:
			AnimationSet();

		public:
			virtual ~AnimationSet();
			!AnimationSet();

			virtual int GetAnimationIndex( System::String^ name );
			virtual System::String^ GetAnimationName( int index );
			virtual System::IntPtr GetCallback( double position, CallbackSearchFlags flags, [Out] double% callbackPosition );
			virtual AnimationOutput GetTransformation( double periodicPosition, int animation );
			virtual double GetPeriodicPosition( double position );

			virtual property System::String^ Name { System::String^ get(); }
			virtual property int AnimationCount { int get(); }
			virtual property double Period { double get(); }
		};
	}
}