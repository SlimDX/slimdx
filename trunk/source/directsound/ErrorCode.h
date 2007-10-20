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

#include <dsound.h>
#include "../ErrorCode.h"

namespace SlimDX
{
	namespace DirectSound
	{
		public ref class DSErrorCode : ErrorCode
		{
		internal:
			DSErrorCode() { };

		public:
			literal int NoVirtualization = DS_NO_VIRTUALIZATION;
			literal int AccessDenied = DSERR_ACCESSDENIED;
			literal int Allocated = DSERR_ALLOCATED;
			literal int AlreadyInitialized = DSERR_ALREADYINITIALIZED;
			literal int BadFormat = DSERR_BADFORMAT;
			literal int BadSendBufferGuid = DSERR_BADSENDBUFFERGUID;
			literal int BufferLost = DSERR_BUFFERLOST;
			literal int BufferTooSmall = DSERR_BUFFERTOOSMALL;
			literal int ControlUnavailable = DSERR_CONTROLUNAVAIL;
			literal int DirectSound8Required = DSERR_DS8_REQUIRED;
			literal int EffectsUnavailable = DSERR_FXUNAVAILABLE;
			literal int Generic = DSERR_GENERIC;
			literal int InvalidCall = DSERR_INVALIDCALL;
			literal int InvalidParameter = DSERR_INVALIDPARAM;
			literal int NoAggregation = DSERR_NOAGGREGATION;
			literal int NoDriver = DSERR_NODRIVER;
			literal int NoInterface = DSERR_NOINTERFACE;
			literal int ObjectNotFound = DSERR_OBJECTNOTFOUND;
			literal int OtherApplicationHasPriority = DSERR_OTHERAPPHASPRIO;
			literal int PriorityLevelNeeded = DSERR_PRIOLEVELNEEDED;
			literal int SendLoop = DSERR_SENDLOOP;
			literal int Uninitialized = DSERR_UNINITIALIZED;
			literal int Unsupported = DSERR_UNSUPPORTED;
		};
	}
}