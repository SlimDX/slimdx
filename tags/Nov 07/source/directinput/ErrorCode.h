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

#include <dinput.h>
#include "../ErrorCode.h"

namespace SlimDX
{
	namespace DirectInput
	{
		public ref class DIErrorCode : ErrorCode
		{
		internal:
			DIErrorCode() { }

		public:
			literal int BufferOverflow = DI_BUFFEROVERFLOW;
			literal int DownloadSkipped = DI_DOWNLOADSKIPPED;
			literal int EffectRestarted = DI_EFFECTRESTARTED;
			literal int NoEffect = DI_NOEFFECT;
			literal int NotAttached = DI_WRITEPROTECT;
			literal int PolledDevice = DI_POLLEDDEVICE;
			literal int PropertyNoEffect = DI_PROPNOEFFECT;
			literal int SettingsNotSaved = DI_SETTINGSNOTSAVED;
			literal int Truncated = DI_TRUNCATED;
			literal int TruncatedAndRestarted = DI_TRUNCATEDANDRESTARTED;
			literal int WriteProtect = DI_WRITEPROTECT;
			literal int Acquired = DIERR_ACQUIRED;
			literal int AlreadyInitialized = DIERR_ALREADYINITIALIZED;
			literal int BadDriverVersion = DIERR_BADDRIVERVER;
			literal int BetaDirectInputVersion = DIERR_BETADIRECTINPUTVERSION;
			literal int DeviceFull = DIERR_DEVICEFULL;
			literal int DeviceNotRegistered = DIERR_DEVICENOTREG;
			literal int EffectPlaying = DIERR_EFFECTPLAYING;
			literal int Generic = DIERR_GENERIC;
			literal int HandleExists = DIERR_HANDLEEXISTS;
			literal int HasEffects = DIERR_HASEFFECTS;
			literal int IncompleteEffect = DIERR_INCOMPLETEEFFECT;
			literal int InputLost = DIERR_INPUTLOST;
			literal int InvalidParameter = DIERR_INVALIDPARAM;
			literal int MapFileFail = DIERR_MAPFILEFAIL;
			literal int MoreData = DIERR_MOREDATA;
			literal int NoAggregation = DIERR_NOAGGREGATION;
			literal int NoInterface = DIERR_NOINTERFACE;
			literal int NotAcquired = DIERR_NOTACQUIRED;
			literal int NotBuffered = DIERR_NOTBUFFERED;
			literal int NotDownloaded = DIERR_NOTDOWNLOADED;
			literal int NotExclusiveAcquired = DIERR_NOTEXCLUSIVEACQUIRED;
			literal int NotFound = DIERR_NOTFOUND;
			literal int NotInitialized = DIERR_NOTINITIALIZED;
			literal int ObjectNotFound = DIERR_OBJECTNOTFOUND;
			literal int OldDirectInputVersion = DIERR_OLDDIRECTINPUTVERSION;
			literal int OtherApplicationHasPriority = DIERR_OTHERAPPHASPRIO;
			literal int ReadOnly = DIERR_READONLY;
			literal int ReportFull = DIERR_REPORTFULL;
			literal int Unplugged = DIERR_UNPLUGGED;
			literal int Unsupported = DIERR_UNSUPPORTED;
		};
	}
}