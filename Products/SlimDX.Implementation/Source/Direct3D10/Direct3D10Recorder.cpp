#include "stdafx.h"

#include "Direct3D10Recorder.h"

SlimDX::Result RecordResult( HRESULT result )
{
	SlimDX::Result translated = SlimDX::Result( result );
	SlimDX::Result::SetLast( translated );
	return translated;
}