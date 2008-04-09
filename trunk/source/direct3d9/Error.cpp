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

#include "Error.h"

namespace SlimDX
{
namespace Direct3D9
{
	Error::Error()
	{
	}
	
	Result Error::NoneButNoAutomaticGeneration::get()
	{
		return Result( D3DOK_NOAUTOGEN );
	}
	
	Result Error::ConflictingRenderState::get()
	{
		return Result( D3DERR_CONFLICTINGRENDERSTATE );
	}
	
	Result Error::ConflictingTextureFilter::get()
	{
		return Result( D3DERR_CONFLICTINGTEXTUREFILTER );
	}
	
	Result Error::ConflictingTexturePalette::get()
	{
		return Result( D3DERR_CONFLICTINGTEXTUREPALETTE );
	}
	
	Result Error::DeviceLost::get()
	{
		return Result( D3DERR_DEVICELOST );
	}
	
	Result Error::DeviceNotReset::get()
	{
		return Result( D3DERR_DEVICENOTRESET );
	}
	
	Result Error::DriverInternalError::get()
	{
		return Result( D3DERR_DRIVERINTERNALERROR );
	}
	
	Result Error::InvalidCall::get()
	{
		return Result( D3DERR_INVALIDCALL );
	}
	
	Result Error::InvalidDevice::get()
	{
		return Result( D3DERR_INVALIDDEVICE );
	}
	
	Result Error::MoreData::get()
	{
		return Result( D3DERR_MOREDATA );
	}
	
	Result Error::NotAvailable::get()
	{
		return Result( D3DERR_NOTAVAILABLE );
	}
	
	Result Error::NotFound::get()
	{
		return Result( D3DERR_NOTFOUND );
	}
	
	Result Error::OutOfVideoMemory::get()
	{
		return Result( D3DERR_OUTOFVIDEOMEMORY );
	}
	
	Result Error::TooManyOperations::get()
	{
		return Result( D3DERR_TOOMANYOPERATIONS );
	}
	
	Result Error::UnsupportedAlphaArgument::get()
	{
		return Result( D3DERR_UNSUPPORTEDALPHAARG );
	}
	
	Result Error::UnsupportedAlphaOperation::get()
	{
		return Result( D3DERR_UNSUPPORTEDALPHAOPERATION );
	}
	
	Result Error::UnsupportedColorArgument::get()
	{
		return Result( D3DERR_UNSUPPORTEDCOLORARG );
	}
	
	Result Error::UnsupportedColorOperation::get()
	{
		return Result( D3DERR_UNSUPPORTEDCOLOROPERATION );
	}
	
	Result Error::UnsupportedFactorValue::get()
	{
		return Result( D3DERR_UNSUPPORTEDFACTORVALUE );
	}
	
	Result Error::UnsupportedTextureFilter::get()
	{
		return Result( D3DERR_UNSUPPORTEDTEXTUREFILTER );
	}

	Result Error::WasStillDrawing::get()
	{
		return Result( D3DERR_WASSTILLDRAWING );
	}
	
	Result Error::WrongTextureFormat::get()
	{
		return Result( D3DERR_WRONGTEXTUREFORMAT );
	}
}
}