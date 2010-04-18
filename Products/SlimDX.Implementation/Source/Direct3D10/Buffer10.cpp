#include "stdafx.h"

#include "Buffer10.h"
#include "../SlimBuffer/MemoryBuffer.h"
using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Buffer::Buffer( ID3D10Buffer* native )
			: ComObject( native )
		{
		}

		Buffer::Buffer( IntPtr native )
			: ComObject( native )
		{
		}

		BufferDescription Buffer::Description::get() {
			D3D10_BUFFER_DESC desc;
			NativePointer->GetDesc(&desc);

			BufferDescription result;

			result.SizeInBytes = desc.ByteWidth;
			result.Usage = (Usage)desc.Usage;
			result.BindFlags = (BindFlags)desc.BindFlags;
			result.CpuAccessFlags = (CpuAccessFlags)desc.CPUAccessFlags;
			result.OptionFlags = (OptionFlags)desc.MiscFlags;

			return result;
		}

		IMemoryBuffer^ Buffer::Map(MapMode mapMode) {
			void* dataPtr;
			NativePointer->Map((D3D10_MAP)mapMode, 0, &dataPtr);
			return gcnew SlimBuffer::MemoryBuffer(reinterpret_cast<unsigned char*>(dataPtr));
		}

		void Buffer::Unmap() {
			NativePointer->Unmap();
		}
	}
}