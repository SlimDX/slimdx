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

#include "Resource.h"
#include "../direct3d/LockedBox.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		[StructLayout( LayoutKind::Sequential )]
		public value class Box
		{
		public:
			int Left;
			int Top;
			int Right;
			int Bottom;
			int Front;
			int Back;
		};

		[StructLayout( LayoutKind::Sequential )]
		public value class VolumeDescription
		{
			Format Format;
			ResourceType Type;
			Usage Usage;
			Pool Pool;

			int Width;
			int Height;
			int Depth;
		};

		public ref class Volume : public Resource
		{
		internal:
			property IDirect3DVolume9* VolumePointer
			{
				IDirect3DVolume9* get() { return (IDirect3DVolume9*) m_Pointer; }
			}

		public:
			Volume( IDirect3DVolume9* volume );

			LockedBox LockBox( LockFlags flags );
			LockedBox LockBox( Box box, LockFlags flags );
			void UnlockBox();

			VolumeDescription GetDesc();
		};
	}
}
