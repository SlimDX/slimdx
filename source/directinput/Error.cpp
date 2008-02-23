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

#include <dinput.h>

#include "Error.h"

namespace SlimDX
{
namespace DirectInput
{
	Error::Error()
	{
	}

	Result Error::Acquired::get()
	{
		return Result( DIERR_ACQUIRED );
	}

	Result Error::AlreadyInitialized::get()
	{
		return Result( DIERR_ALREADYINITIALIZED );
	}

	Result Error::BadDriverVersion::get()
	{
		return Result( DIERR_BADDRIVERVER );
	}

	Result Error::BetaDirectInputVersion::get()
	{
		return Result( DIERR_BETADIRECTINPUTVERSION );
	}

	Result Error::BufferOverflow::get()
	{
		return Result( DI_BUFFEROVERFLOW );
	}

	Result Error::DeviceFull::get()
	{
		return Result( DIERR_DEVICEFULL );
	}

	Result Error::DeviceNotRegistered::get()
	{
		return Result( DIERR_DEVICENOTREG );
	}

	Result Error::DownloadSkipped::get()
	{
		return Result( DI_DOWNLOADSKIPPED );
	}

	Result Error::EffectPlaying::get()
	{
		return Result( DIERR_EFFECTPLAYING );
	}

	Result Error::EffectRestarted::get()
	{
		return Result( DI_EFFECTRESTARTED );
	}

	Result Error::Generic::get()
	{
		return Result( DIERR_GENERIC );
	}

	Result Error::HandleExists::get()
	{
		return Result( DIERR_HANDLEEXISTS );
	}

	Result Error::HasEffects::get()
	{
		return Result( DIERR_HASEFFECTS );
	}

	Result Error::IncompleteEffect::get()
	{
		return Result( DIERR_INCOMPLETEEFFECT );
	}

	Result Error::InputLost::get()
	{
		return Result( DIERR_INPUTLOST );
	}

	Result Error::InvalidParameter::get()
	{
		return Result( DIERR_INVALIDPARAM );
	}

	Result Error::MapFileFail::get()
	{
		return Result( DIERR_MAPFILEFAIL );
	}

	Result Error::MoreData::get()
	{
		return Result( DIERR_MOREDATA );
	}

	Result Error::NoAggregation::get()
	{
		return Result( DIERR_NOAGGREGATION );
	}

	Result Error::NoEffect::get()
	{
		return Result( DI_NOEFFECT );
	}

	Result Error::NoInterface::get()
	{
		return Result( DIERR_NOINTERFACE );
	}

	Result Error::NotAcquired::get()
	{
		return Result( DIERR_NOTACQUIRED );
	}

	Result Error::NotAttached::get()
	{
		return Result( DI_NOTATTACHED );
	}

	Result Error::NotBuffered::get()
	{
		return Result( DIERR_NOTBUFFERED );
	}

	Result Error::NotDownloaded::get()
	{
		return Result( DIERR_NOTDOWNLOADED );
	}

	Result Error::NotExclusivelyAcquired::get()
	{
		return Result( DIERR_NOTEXCLUSIVEACQUIRED );
	}

	Result Error::NotFound::get()
	{
		return Result( DIERR_NOTFOUND );
	}

	Result Error::NotInitialized::get()
	{
		return Result( DIERR_NOTINITIALIZED );
	}

	Result Error::ObjectNotFound::get()
	{
		return Result( DIERR_OBJECTNOTFOUND );
	}

	Result Error::OldDirectInputVersion::get()
	{
		return Result( DIERR_OLDDIRECTINPUTVERSION );
	}

	Result Error::OtherApplicationHasPriority::get()
	{
		return Result( DIERR_OTHERAPPHASPRIO );
	}

	Result Error::OutOfMemory::get()
	{
		return Result( DIERR_OUTOFMEMORY );
	}

	Result Error::PolledDevice::get()
	{
		return Result( DI_POLLEDDEVICE );
	}

	Result Error::PropertyHasNoEffect::get()
	{
		return Result( DI_PROPNOEFFECT );
	}

	Result Error::ReadOnly::get()
	{
		return Result( DIERR_READONLY );
	}

	Result Error::ReportFull::get()
	{
		return Result( DIERR_REPORTFULL );
	}

	Result Error::SettingsNotSaved::get()
	{
		return Result( DI_SETTINGSNOTSAVED );
	}

	Result Error::Truncated::get()
	{
		return Result( DI_TRUNCATED );
	}

	Result Error::TruncatedAndRestarted::get()
	{
		return Result( DI_TRUNCATEDANDRESTARTED );
	}

	Result Error::Unplugged::get()
	{
		return Result( DIERR_UNPLUGGED );
	}

	Result Error::Unsupported::get()
	{
		return Result( DIERR_UNSUPPORTED );
	}

	Result Error::WriteProtect::get()
	{
		return Result( DI_WRITEPROTECT );
	}
}
}
