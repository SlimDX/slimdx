#include "stdafx.h"

#include "Buffer10.h"
#include "../SlimBuffer/MemoryBuffer.h"
using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Buffer10::Buffer10( ID3D10Buffer* native )
			: ComObject( native )
		{
		}

		Buffer10::Buffer10( IntPtr native )
			: ComObject( native )
		{
		}

		BufferDescription10 Buffer10::Description::get() {
			D3D10_BUFFER_DESC desc;
			NativePointer->GetDesc(&desc);

			BufferDescription10 result;

			result.SizeInBytes = desc.ByteWidth;
			result.Usage = (Usage10)desc.Usage;
			result.BindFlags = (BindFlags10)desc.BindFlags;
			result.CpuAccessFlags = (CpuAccessFlags10)desc.CPUAccessFlags;
			result.OptionFlags = (OptionFlags10)desc.MiscFlags;

			return result;
		}

		IMemoryBuffer^ Buffer10::Map(MapMode10 mapMode) {
			void* dataPtr;
			NativePointer->Map((D3D10_MAP)mapMode, 0, &dataPtr);
			return gcnew SlimBuffer::MemoryBuffer(reinterpret_cast<unsigned char*>(dataPtr));
		}

		void Buffer10::Unmap() {
			NativePointer->Unmap();
		}
	}
}