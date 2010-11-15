// SizeofVerifier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <dsound.h>
#include <X3DAudio.h>
#include <xact3.h>
#include <xact3wb.h>
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <xapo.h>
#include <XAPOFX.h>
#include <XInput.h>
#include <DXGI.h>
#include <D3D10_1.h>
#include <D3D11.h>
#include <d3d9caps.h>
#include <d3dx9core.h>
#include <d3dx9mesh.h>
#include <d3dx9shader.h>
#include <d3dx9effect.h>
#include <d3dx9tex.h>
#include <d3dx9anim.h>
#include <d3dcommon.h>
#include <d3dx9effect.h>
#include <d3dx9tex.h>
#include <d3dx10core.h>
#include <d3dx10tex.h>
#include <d3d11shader.h>
#include <d3dx11tex.h>
#include <d3dcompiler.h>
#include <dwrite.h>
#include <d2d1.h>



#pragma pack(push,8)

struct T {
	char a;
	int b;
};

struct S {
   int a;
   char b;
   char c;
   char d;
   short e;
   double f;
   char g;
};
#pragma pack(pop)

int _tmain(int argc, _TCHAR* argv[])
{
	S s;

	printf("aling_of(S): %d\n", __alignof(S));
	printf("a: %d\n", (__int64)&s.a - (__int64)&s);
	printf("b: %d\n", (__int64)&s.b - (__int64)&s);
	printf("c: %d\n", (__int64)&s.c - (__int64)&s);
	printf("d: %d\n", (__int64)&s.d - (__int64)&s);
	printf("e: %d\n", (__int64)&s.e - (__int64)&s);
	printf("f: %d\n", (__int64)&s.f - (__int64)&s);
	printf("g: %d\n", (__int64)&s.g - (__int64)&s);


if ( sizeof(RGNDATAHEADER) != 32 ) printf("%s,%s,%d,%d\n","win32_ext", "RGNDATAHEADER",sizeof(RGNDATAHEADER), 32);
if ( sizeof(PALETTEENTRY) != 4 ) printf("%s,%s,%d,%d\n","win32_ext", "PALETTEENTRY",sizeof(PALETTEENTRY), 4);
if ( sizeof(TEXTMETRICW) != 57 ) printf("%s,%s,%d,%d\n","win32_ext", "TEXTMETRICW",sizeof(TEXTMETRICW), 57);
if ( sizeof(TEXTMETRICA) != 53 ) printf("%s,%s,%d,%d\n","win32_ext", "TEXTMETRICA",sizeof(TEXTMETRICA), 53);
if ( sizeof(LOGFONTW) != 92 ) printf("%s,%s,%d,%d\n","win32_ext", "LOGFONTW",sizeof(LOGFONTW), 92);
if ( sizeof(DSCAPS) != 96 ) printf("%s,%s,%d,%d\n","dsound", "DSCAPS",sizeof(DSCAPS), 96);
if ( sizeof(DSBCAPS) != 20 ) printf("%s,%s,%d,%d\n","dsound", "DSBCAPS",sizeof(DSBCAPS), 20);
if ( sizeof(DSEFFECTDESC) != 40 ) printf("%s,%s,%d,%d\n","dsound", "DSEFFECTDESC",sizeof(DSEFFECTDESC), 40);
if ( sizeof(DSCEFFECTDESC) != 48 ) printf("%s,%s,%d,%d\n","dsound", "DSCEFFECTDESC",sizeof(DSCEFFECTDESC), 48);
if ( sizeof(DSBUFFERDESC) != 40 ) printf("%s,%s,%d,%d\n","dsound", "DSBUFFERDESC",sizeof(DSBUFFERDESC), 40);
if ( sizeof(DS3DBUFFER) != 64 ) printf("%s,%s,%d,%d\n","dsound", "DS3DBUFFER",sizeof(DS3DBUFFER), 64);
if ( sizeof(DS3DLISTENER) != 64 ) printf("%s,%s,%d,%d\n","dsound", "DS3DLISTENER",sizeof(DS3DLISTENER), 64);
if ( sizeof(DSCCAPS) != 16 ) printf("%s,%s,%d,%d\n","dsound", "DSCCAPS",sizeof(DSCCAPS), 16);
if ( sizeof(DSCBUFFERDESC) != 36 ) printf("%s,%s,%d,%d\n","dsound", "DSCBUFFERDESC",sizeof(DSCBUFFERDESC), 36);
if ( sizeof(DSCBCAPS) != 16 ) printf("%s,%s,%d,%d\n","dsound", "DSCBCAPS",sizeof(DSCBCAPS), 16);
if ( sizeof(DSBPOSITIONNOTIFY) != 0 ) printf("%s,%s,%d,%d\n","dsound", "DSBPOSITIONNOTIFY",sizeof(DSBPOSITIONNOTIFY), 0);
if ( sizeof(DSFXGargle) != 8 ) printf("%s,%s,%d,%d\n","dsound", "DSFXGargle",sizeof(DSFXGargle), 8);
if ( sizeof(DSFXChorus) != 28 ) printf("%s,%s,%d,%d\n","dsound", "DSFXChorus",sizeof(DSFXChorus), 28);
if ( sizeof(DSFXFlanger) != 28 ) printf("%s,%s,%d,%d\n","dsound", "DSFXFlanger",sizeof(DSFXFlanger), 28);
if ( sizeof(DSFXEcho) != 20 ) printf("%s,%s,%d,%d\n","dsound", "DSFXEcho",sizeof(DSFXEcho), 20);
if ( sizeof(DSFXDistortion) != 20 ) printf("%s,%s,%d,%d\n","dsound", "DSFXDistortion",sizeof(DSFXDistortion), 20);
if ( sizeof(DSFXCompressor) != 24 ) printf("%s,%s,%d,%d\n","dsound", "DSFXCompressor",sizeof(DSFXCompressor), 24);
if ( sizeof(DSFXParamEq) != 12 ) printf("%s,%s,%d,%d\n","dsound", "DSFXParamEq",sizeof(DSFXParamEq), 12);
if ( sizeof(DSFXI3DL2Reverb) != 48 ) printf("%s,%s,%d,%d\n","dsound", "DSFXI3DL2Reverb",sizeof(DSFXI3DL2Reverb), 48);
if ( sizeof(DSFXWavesReverb) != 16 ) printf("%s,%s,%d,%d\n","dsound", "DSFXWavesReverb",sizeof(DSFXWavesReverb), 16);
if ( sizeof(DSCFXAec) != 12 ) printf("%s,%s,%d,%d\n","dsound", "DSCFXAec",sizeof(DSCFXAec), 12);
if ( sizeof(DSCFXNoiseSuppress) != 4 ) printf("%s,%s,%d,%d\n","dsound", "DSCFXNoiseSuppress",sizeof(DSCFXNoiseSuppress), 4);
if ( sizeof(X3DAUDIO_DISTANCE_CURVE_POINT) != 8 ) printf("%s,%s,%d,%d\n","x3daudio", "X3DAUDIO_DISTANCE_CURVE_POINT",sizeof(X3DAUDIO_DISTANCE_CURVE_POINT), 8);
if ( sizeof(X3DAUDIO_DISTANCE_CURVE) != 12 ) printf("%s,%s,%d,%d\n","x3daudio", "X3DAUDIO_DISTANCE_CURVE",sizeof(X3DAUDIO_DISTANCE_CURVE), 12);
if ( sizeof(X3DAUDIO_CONE) != 32 ) printf("%s,%s,%d,%d\n","x3daudio", "X3DAUDIO_CONE",sizeof(X3DAUDIO_CONE), 32);
if ( sizeof(X3DAUDIO_LISTENER) != 56 ) printf("%s,%s,%d,%d\n","x3daudio", "X3DAUDIO_LISTENER",sizeof(X3DAUDIO_LISTENER), 56);
if ( sizeof(X3DAUDIO_EMITTER) != 128 ) printf("%s,%s,%d,%d\n","x3daudio", "X3DAUDIO_EMITTER",sizeof(X3DAUDIO_EMITTER), 128);
if ( sizeof(X3DAUDIO_DSP_SETTINGS) != 0 ) printf("%s,%s,%d,%d\n","x3daudio", "X3DAUDIO_DSP_SETTINGS",sizeof(X3DAUDIO_DSP_SETTINGS), 0);
if ( sizeof(WAVEBANKREGION) != 8 ) printf("%s,%s,%d,%d\n","xact3wb", "WAVEBANKREGION",sizeof(WAVEBANKREGION), 8);
if ( sizeof(WAVEBANKSAMPLEREGION) != 8 ) printf("%s,%s,%d,%d\n","xact3wb", "WAVEBANKSAMPLEREGION",sizeof(WAVEBANKSAMPLEREGION), 8);
if ( sizeof(WAVEBANKHEADER) != 52 ) printf("%s,%s,%d,%d\n","xact3wb", "WAVEBANKHEADER",sizeof(WAVEBANKHEADER), 52);
if ( sizeof(WAVEBANKMINIWAVEFORMAT) != 0 ) printf("%s,%s,%d,%d\n","xact3wb", "WAVEBANKMINIWAVEFORMAT",sizeof(WAVEBANKMINIWAVEFORMAT), 0);
if ( sizeof(WAVEBANKENTRY) != 20 ) printf("%s,%s,%d,%d\n","xact3wb", "WAVEBANKENTRY",sizeof(WAVEBANKENTRY), 20);
if ( sizeof(WAVEBANKENTRYCOMPACT) != 0 ) printf("%s,%s,%d,%d\n","xact3wb", "WAVEBANKENTRYCOMPACT",sizeof(WAVEBANKENTRYCOMPACT), 0);
if ( sizeof(WAVEBANKDATA) != 92 ) printf("%s,%s,%d,%d\n","xact3wb", "WAVEBANKDATA",sizeof(WAVEBANKDATA), 92);
if ( sizeof(XACT_FILEIO_CALLBACKS) != 0 ) printf("%s,%s,%d,%d\n","xact3", "XACT_FILEIO_CALLBACKS",sizeof(XACT_FILEIO_CALLBACKS), 0);
if ( sizeof(XACT_RENDERER_DETAILS) != 1024 ) printf("%s,%s,%d,%d\n","xact3", "XACT_RENDERER_DETAILS",sizeof(XACT_RENDERER_DETAILS), 1024);
if ( sizeof(XACT_RUNTIME_PARAMETERS) != 56 ) printf("%s,%s,%d,%d\n","xact3", "XACT_RUNTIME_PARAMETERS",sizeof(XACT_RUNTIME_PARAMETERS), 56);
if ( sizeof(XACT_WAVEBANK_STREAMING_PARAMETERS) != 18 ) printf("%s,%s,%d,%d\n","xact3", "XACT_WAVEBANK_STREAMING_PARAMETERS",sizeof(XACT_WAVEBANK_STREAMING_PARAMETERS), 18);
if ( sizeof(XACT_CUE_PROPERTIES) != 265 ) printf("%s,%s,%d,%d\n","xact3", "XACT_CUE_PROPERTIES",sizeof(XACT_CUE_PROPERTIES), 265);
if ( sizeof(XACT_TRACK_PROPERTIES) != 10 ) printf("%s,%s,%d,%d\n","xact3", "XACT_TRACK_PROPERTIES",sizeof(XACT_TRACK_PROPERTIES), 10);
if ( sizeof(XACT_VARIATION_PROPERTIES) != 15 ) printf("%s,%s,%d,%d\n","xact3", "XACT_VARIATION_PROPERTIES",sizeof(XACT_VARIATION_PROPERTIES), 15);
if ( sizeof(XACT_SOUND_PROPERTIES) != 21 ) printf("%s,%s,%d,%d\n","xact3", "XACT_SOUND_PROPERTIES",sizeof(XACT_SOUND_PROPERTIES), 21);
if ( sizeof(XACT_SOUND_VARIATION_PROPERTIES) != 36 ) printf("%s,%s,%d,%d\n","xact3", "XACT_SOUND_VARIATION_PROPERTIES",sizeof(XACT_SOUND_VARIATION_PROPERTIES), 36);
if ( sizeof(XACT_CUE_INSTANCE_PROPERTIES) != 305 ) printf("%s,%s,%d,%d\n","xact3", "XACT_CUE_INSTANCE_PROPERTIES",sizeof(XACT_CUE_INSTANCE_PROPERTIES), 305);
if ( sizeof(XACT_WAVE_PROPERTIES) != 80 ) printf("%s,%s,%d,%d\n","xact3", "XACT_WAVE_PROPERTIES",sizeof(XACT_WAVE_PROPERTIES), 80);
if ( sizeof(XACT_WAVE_INSTANCE_PROPERTIES) != 84 ) printf("%s,%s,%d,%d\n","xact3", "XACT_WAVE_INSTANCE_PROPERTIES",sizeof(XACT_WAVE_INSTANCE_PROPERTIES), 84);
if ( sizeof(XACTCHANNELMAPENTRY) != 6 ) printf("%s,%s,%d,%d\n","xact3", "XACTCHANNELMAPENTRY",sizeof(XACTCHANNELMAPENTRY), 6);
if ( sizeof(XACTCHANNELMAP) != 9 ) printf("%s,%s,%d,%d\n","xact3", "XACTCHANNELMAP",sizeof(XACTCHANNELMAP), 9);
if ( sizeof(XACTCHANNELVOLUMEENTRY) != 5 ) printf("%s,%s,%d,%d\n","xact3", "XACTCHANNELVOLUMEENTRY",sizeof(XACTCHANNELVOLUMEENTRY), 5);
if ( sizeof(XACTCHANNELVOLUME) != 0 ) printf("%s,%s,%d,%d\n","xact3", "XACTCHANNELVOLUME",sizeof(XACTCHANNELVOLUME), 0);
if ( sizeof(XACT_NOTIFICATION_DESCRIPTION) != 46 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_DESCRIPTION",sizeof(XACT_NOTIFICATION_DESCRIPTION), 46);
if ( sizeof(XACT_NOTIFICATION_CUE) != 18 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_CUE",sizeof(XACT_NOTIFICATION_CUE), 18);
if ( sizeof(XACT_NOTIFICATION_MARKER) != 22 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_MARKER",sizeof(XACT_NOTIFICATION_MARKER), 22);
if ( sizeof(XACT_NOTIFICATION_SOUNDBANK) != 8 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_SOUNDBANK",sizeof(XACT_NOTIFICATION_SOUNDBANK), 8);
if ( sizeof(XACT_NOTIFICATION_WAVEBANK) != 8 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_WAVEBANK",sizeof(XACT_NOTIFICATION_WAVEBANK), 8);
if ( sizeof(XACT_NOTIFICATION_VARIABLE) != 28 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_VARIABLE",sizeof(XACT_NOTIFICATION_VARIABLE), 28);
if ( sizeof(XACT_NOTIFICATION_GUI) != 4 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_GUI",sizeof(XACT_NOTIFICATION_GUI), 4);
if ( sizeof(XACT_NOTIFICATION_WAVE) != 36 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION_WAVE",sizeof(XACT_NOTIFICATION_WAVE), 36);
if ( sizeof(XACT_NOTIFICATION) != 13 ) printf("%s,%s,%d,%d\n","xact3", "XACT_NOTIFICATION",sizeof(XACT_NOTIFICATION), 13);
if ( sizeof(XAUDIO2_DEVICE_DETAILS) != 1046 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_DEVICE_DETAILS",sizeof(XAUDIO2_DEVICE_DETAILS), 1046);
if ( sizeof(XAUDIO2_VOICE_DETAILS) != 12 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_VOICE_DETAILS",sizeof(XAUDIO2_VOICE_DETAILS), 12);
if ( sizeof(XAUDIO2_SEND_DESCRIPTOR) != 12 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_SEND_DESCRIPTOR",sizeof(XAUDIO2_SEND_DESCRIPTOR), 12);
if ( sizeof(XAUDIO2_VOICE_SENDS) != 12 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_VOICE_SENDS",sizeof(XAUDIO2_VOICE_SENDS), 12);
if ( sizeof(XAUDIO2_EFFECT_DESCRIPTOR) != 16 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_EFFECT_DESCRIPTOR",sizeof(XAUDIO2_EFFECT_DESCRIPTOR), 16);
if ( sizeof(XAUDIO2_EFFECT_CHAIN) != 12 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_EFFECT_CHAIN",sizeof(XAUDIO2_EFFECT_CHAIN), 12);
if ( sizeof(XAUDIO2_FILTER_PARAMETERS) != 12 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_FILTER_PARAMETERS",sizeof(XAUDIO2_FILTER_PARAMETERS), 12);
if ( sizeof(XAUDIO2_BUFFER) != 44 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_BUFFER",sizeof(XAUDIO2_BUFFER), 44);
if ( sizeof(XAUDIO2_BUFFER_WMA) != 12 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_BUFFER_WMA",sizeof(XAUDIO2_BUFFER_WMA), 12);
if ( sizeof(XAUDIO2_VOICE_STATE) != 20 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_VOICE_STATE",sizeof(XAUDIO2_VOICE_STATE), 20);
if ( sizeof(XAUDIO2_PERFORMANCE_DATA) != 64 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_PERFORMANCE_DATA",sizeof(XAUDIO2_PERFORMANCE_DATA), 64);
if ( sizeof(XAUDIO2_DEBUG_CONFIGURATION) != 24 ) printf("%s,%s,%d,%d\n","xaudio2", "XAUDIO2_DEBUG_CONFIGURATION",sizeof(XAUDIO2_DEBUG_CONFIGURATION), 24);
if ( sizeof(XAUDIO2FX_VOLUMEMETER_LEVELS) != 20 ) printf("%s,%s,%d,%d\n","xaudio2fx", "XAUDIO2FX_VOLUMEMETER_LEVELS",sizeof(XAUDIO2FX_VOLUMEMETER_LEVELS), 20);
if ( sizeof(XAUDIO2FX_REVERB_PARAMETERS) != 52 ) printf("%s,%s,%d,%d\n","xaudio2fx", "XAUDIO2FX_REVERB_PARAMETERS",sizeof(XAUDIO2FX_REVERB_PARAMETERS), 52);
if ( sizeof(XAUDIO2FX_REVERB_I3DL2_PARAMETERS) != 52 ) printf("%s,%s,%d,%d\n","xaudio2fx", "XAUDIO2FX_REVERB_I3DL2_PARAMETERS",sizeof(XAUDIO2FX_REVERB_I3DL2_PARAMETERS), 52);
if ( sizeof(XAPO_REGISTRATION_PROPERTIES) != 1068 ) printf("%s,%s,%d,%d\n","xapo", "XAPO_REGISTRATION_PROPERTIES",sizeof(XAPO_REGISTRATION_PROPERTIES), 1068);
if ( sizeof(XAPO_LOCKFORPROCESS_PARAMETERS) != 12 ) printf("%s,%s,%d,%d\n","xapo", "XAPO_LOCKFORPROCESS_PARAMETERS",sizeof(XAPO_LOCKFORPROCESS_PARAMETERS), 12);
if ( sizeof(XAPO_PROCESS_BUFFER_PARAMETERS) != 16 ) printf("%s,%s,%d,%d\n","xapo", "XAPO_PROCESS_BUFFER_PARAMETERS",sizeof(XAPO_PROCESS_BUFFER_PARAMETERS), 16);
if ( sizeof(FXEQ_PARAMETERS) != 48 ) printf("%s,%s,%d,%d\n","xapofx", "FXEQ_PARAMETERS",sizeof(FXEQ_PARAMETERS), 48);
if ( sizeof(FXMASTERINGLIMITER_PARAMETERS) != 8 ) printf("%s,%s,%d,%d\n","xapofx", "FXMASTERINGLIMITER_PARAMETERS",sizeof(FXMASTERINGLIMITER_PARAMETERS), 8);
if ( sizeof(FXREVERB_PARAMETERS) != 8 ) printf("%s,%s,%d,%d\n","xapofx", "FXREVERB_PARAMETERS",sizeof(FXREVERB_PARAMETERS), 8);
if ( sizeof(FXECHO_PARAMETERS) != 0 ) printf("%s,%s,%d,%d\n","xapofx", "FXECHO_PARAMETERS",sizeof(FXECHO_PARAMETERS), 0);
if ( sizeof(XINPUT_GAMEPAD) != 12 ) printf("%s,%s,%d,%d\n","xinput", "XINPUT_GAMEPAD",sizeof(XINPUT_GAMEPAD), 12);
if ( sizeof(XINPUT_STATE) != 16 ) printf("%s,%s,%d,%d\n","xinput", "XINPUT_STATE",sizeof(XINPUT_STATE), 16);
if ( sizeof(XINPUT_VIBRATION) != 4 ) printf("%s,%s,%d,%d\n","xinput", "XINPUT_VIBRATION",sizeof(XINPUT_VIBRATION), 4);
if ( sizeof(XINPUT_CAPABILITIES) != 20 ) printf("%s,%s,%d,%d\n","xinput", "XINPUT_CAPABILITIES",sizeof(XINPUT_CAPABILITIES), 20);
if ( sizeof(XINPUT_BATTERY_INFORMATION) != 2 ) printf("%s,%s,%d,%d\n","xinput", "XINPUT_BATTERY_INFORMATION",sizeof(XINPUT_BATTERY_INFORMATION), 2);
if ( sizeof(XINPUT_KEYSTROKE) != 8 ) printf("%s,%s,%d,%d\n","xinput", "XINPUT_KEYSTROKE",sizeof(XINPUT_KEYSTROKE), 8);
if ( sizeof(DXGI_FRAME_STATISTICS) != 28 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_FRAME_STATISTICS",sizeof(DXGI_FRAME_STATISTICS), 28);
if ( sizeof(DXGI_MAPPED_RECT) != 12 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_MAPPED_RECT",sizeof(DXGI_MAPPED_RECT), 12);
if ( sizeof(DXGI_ADAPTER_DESC) != 304 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_ADAPTER_DESC",sizeof(DXGI_ADAPTER_DESC), 304);
if ( sizeof(DXGI_OUTPUT_DESC) != 96 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_OUTPUT_DESC",sizeof(DXGI_OUTPUT_DESC), 96);
if ( sizeof(DXGI_SHARED_RESOURCE) != 8 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_SHARED_RESOURCE",sizeof(DXGI_SHARED_RESOURCE), 8);
if ( sizeof(DXGI_SAMPLE_DESC) != 8 ) printf("%s,%s,%d,%d\n","dxgitype", "DXGI_SAMPLE_DESC",sizeof(DXGI_SAMPLE_DESC), 8);
if ( sizeof(DXGI_SURFACE_DESC) != 20 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_SURFACE_DESC",sizeof(DXGI_SURFACE_DESC), 20);
if ( sizeof(DXGI_RATIONAL) != 8 ) printf("%s,%s,%d,%d\n","dxgitype", "DXGI_RATIONAL",sizeof(DXGI_RATIONAL), 8);
if ( sizeof(DXGI_MODE_DESC) != 28 ) printf("%s,%s,%d,%d\n","dxgitype", "DXGI_MODE_DESC",sizeof(DXGI_MODE_DESC), 28);
if ( sizeof(DXGI_SWAP_CHAIN_DESC) != 64 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_SWAP_CHAIN_DESC",sizeof(DXGI_SWAP_CHAIN_DESC), 64);
if ( sizeof(DXGI_ADAPTER_DESC1) != 308 ) printf("%s,%s,%d,%d\n","dxgi", "DXGI_ADAPTER_DESC1",sizeof(DXGI_ADAPTER_DESC1), 308);
if ( sizeof(DXGI_GAMMA_CONTROL) != 12324 ) printf("%s,%s,%d,%d\n","dxgitype", "DXGI_GAMMA_CONTROL",sizeof(DXGI_GAMMA_CONTROL), 12324);
if ( sizeof(DXGI_GAMMA_CONTROL_CAPABILITIES) != 4116 ) printf("%s,%s,%d,%d\n","dxgitype", "DXGI_GAMMA_CONTROL_CAPABILITIES",sizeof(DXGI_GAMMA_CONTROL_CAPABILITIES), 4116);
if ( sizeof(D3DVIEWPORT9) != 24 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DVIEWPORT9",sizeof(D3DVIEWPORT9), 24);
if ( sizeof(D3DCLIPSTATUS9) != 8 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DCLIPSTATUS9",sizeof(D3DCLIPSTATUS9), 8);
if ( sizeof(D3DMATERIAL9) != 68 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DMATERIAL9",sizeof(D3DMATERIAL9), 68);
if ( sizeof(D3DLIGHT9) != 104 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DLIGHT9",sizeof(D3DLIGHT9), 104);
if ( sizeof(D3DVERTEXELEMENT9) != 8 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DVERTEXELEMENT9",sizeof(D3DVERTEXELEMENT9), 8);
if ( sizeof(D3DDISPLAYMODE) != 16 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DDISPLAYMODE",sizeof(D3DDISPLAYMODE), 16);
if ( sizeof(D3DDEVICE_CREATION_PARAMETERS) != 20 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DDEVICE_CREATION_PARAMETERS",sizeof(D3DDEVICE_CREATION_PARAMETERS), 20);
if ( sizeof(D3DPRESENT_PARAMETERS) != 60 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DPRESENT_PARAMETERS",sizeof(D3DPRESENT_PARAMETERS), 60);
if ( sizeof(D3DGAMMARAMP) != 1536 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DGAMMARAMP",sizeof(D3DGAMMARAMP), 1536);
if ( sizeof(D3DVERTEXBUFFER_DESC) != 24 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DVERTEXBUFFER_DESC",sizeof(D3DVERTEXBUFFER_DESC), 24);
if ( sizeof(D3DINDEXBUFFER_DESC) != 20 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DINDEXBUFFER_DESC",sizeof(D3DINDEXBUFFER_DESC), 20);
if ( sizeof(D3DSURFACE_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DSURFACE_DESC",sizeof(D3DSURFACE_DESC), 32);
if ( sizeof(D3DVOLUME_DESC) != 28 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DVOLUME_DESC",sizeof(D3DVOLUME_DESC), 28);
if ( sizeof(D3DLOCKED_RECT) != 12 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DLOCKED_RECT",sizeof(D3DLOCKED_RECT), 12);
if ( sizeof(D3DBOX) != 24 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DBOX",sizeof(D3DBOX), 24);
if ( sizeof(D3DLOCKED_BOX) != 16 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DLOCKED_BOX",sizeof(D3DLOCKED_BOX), 16);
if ( sizeof(D3DRECTPATCH_INFO) != 28 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DRECTPATCH_INFO",sizeof(D3DRECTPATCH_INFO), 28);
if ( sizeof(D3DTRIPATCH_INFO) != 16 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DTRIPATCH_INFO",sizeof(D3DTRIPATCH_INFO), 16);
if ( sizeof(D3DADAPTER_IDENTIFIER9) != 1100 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DADAPTER_IDENTIFIER9",sizeof(D3DADAPTER_IDENTIFIER9), 1100);
if ( sizeof(D3DRASTER_STATUS) != 8 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DRASTER_STATUS",sizeof(D3DRASTER_STATUS), 8);
if ( sizeof(D3DPRESENTSTATS) != 28 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DPRESENTSTATS",sizeof(D3DPRESENTSTATS), 28);
if ( sizeof(D3DDISPLAYMODEEX) != 24 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DDISPLAYMODEEX",sizeof(D3DDISPLAYMODEEX), 24);
if ( sizeof(D3DDISPLAYMODEFILTER) != 12 ) printf("%s,%s,%d,%d\n","d3d9types", "D3DDISPLAYMODEFILTER",sizeof(D3DDISPLAYMODEFILTER), 12);
if ( sizeof(D3DVSHADERCAPS2_0) != 16 ) printf("%s,%s,%d,%d\n","d3d9caps", "D3DVSHADERCAPS2_0",sizeof(D3DVSHADERCAPS2_0), 16);
if ( sizeof(D3DPSHADERCAPS2_0) != 20 ) printf("%s,%s,%d,%d\n","d3d9caps", "D3DPSHADERCAPS2_0",sizeof(D3DPSHADERCAPS2_0), 20);
if ( sizeof(D3DCAPS9) != 0 ) printf("%s,%s,%d,%d\n","d3d9caps", "D3DCAPS9",sizeof(D3DCAPS9), 0);
if ( sizeof(D3DXFONT_DESCW) != 88 ) printf("%s,%s,%d,%d\n","d3dx9core", "D3DXFONT_DESCW",sizeof(D3DXFONT_DESCW), 88);
if ( sizeof(D3DXRTS_DESC) != 20 ) printf("%s,%s,%d,%d\n","d3dx9core", "D3DXRTS_DESC",sizeof(D3DXRTS_DESC), 20);
if ( sizeof(D3DXRTE_DESC) != 20 ) printf("%s,%s,%d,%d\n","d3dx9core", "D3DXRTE_DESC",sizeof(D3DXRTE_DESC), 20);
if ( sizeof(D3DXATTRIBUTERANGE) != 20 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXATTRIBUTERANGE",sizeof(D3DXATTRIBUTERANGE), 20);
if ( sizeof(D3DXMATERIAL) != 76 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXMATERIAL",sizeof(D3DXMATERIAL), 76);
if ( sizeof(D3DXEFFECTDEFAULT) != 24 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXEFFECTDEFAULT",sizeof(D3DXEFFECTDEFAULT), 24);
if ( sizeof(D3DXEFFECTINSTANCE) != 20 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXEFFECTINSTANCE",sizeof(D3DXEFFECTINSTANCE), 20);
if ( sizeof(D3DXATTRIBUTEWEIGHTS) != 60 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXATTRIBUTEWEIGHTS",sizeof(D3DXATTRIBUTEWEIGHTS), 60);
if ( sizeof(D3DXWELDEPSILONS) != 68 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXWELDEPSILONS",sizeof(D3DXWELDEPSILONS), 68);
if ( sizeof(D3DXBONECOMBINATION) != 28 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXBONECOMBINATION",sizeof(D3DXBONECOMBINATION), 28);
if ( sizeof(D3DXPATCHINFO) != 12 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "D3DXPATCHINFO",sizeof(D3DXPATCHINFO), 12);
if ( sizeof(XFILECOMPRESSEDANIMATIONSET) != 0 ) printf("%s,%s,%d,%d\n","d3dx9mesh", "XFILECOMPRESSEDANIMATIONSET",sizeof(XFILECOMPRESSEDANIMATIONSET), 0);
if ( sizeof(D3DXMACRO) != 16 ) printf("%s,%s,%d,%d\n","d3dx9shader", "D3DXMACRO",sizeof(D3DXMACRO), 16);
if ( sizeof(D3DXSEMANTIC) != 8 ) printf("%s,%s,%d,%d\n","d3dx9shader", "D3DXSEMANTIC",sizeof(D3DXSEMANTIC), 8);
if ( sizeof(D3DXCONSTANTTABLE_DESC) != 16 ) printf("%s,%s,%d,%d\n","d3dx9shader", "D3DXCONSTANTTABLE_DESC",sizeof(D3DXCONSTANTTABLE_DESC), 16);
if ( sizeof(D3DXCONSTANT_DESC) != 56 ) printf("%s,%s,%d,%d\n","d3dx9shader", "D3DXCONSTANT_DESC",sizeof(D3DXCONSTANT_DESC), 56);
if ( sizeof(D3DXSHADER_CONSTANTTABLE) != 28 ) printf("%s,%s,%d,%d\n","d3dx9shader", "D3DXSHADER_CONSTANTTABLE",sizeof(D3DXSHADER_CONSTANTTABLE), 28);
if ( sizeof(D3DXSHADER_CONSTANTINFO) != 20 ) printf("%s,%s,%d,%d\n","d3dx9shader", "D3DXSHADER_CONSTANTINFO",sizeof(D3DXSHADER_CONSTANTINFO), 20);
if ( sizeof(D3DXEFFECT_DESC) != 20 ) printf("%s,%s,%d,%d\n","d3dx9effect", "D3DXEFFECT_DESC",sizeof(D3DXEFFECT_DESC), 20);
if ( sizeof(D3DXPARAMETER_DESC) != 52 ) printf("%s,%s,%d,%d\n","d3dx9effect", "D3DXPARAMETER_DESC",sizeof(D3DXPARAMETER_DESC), 52);
if ( sizeof(D3DXTECHNIQUE_DESC) != 16 ) printf("%s,%s,%d,%d\n","d3dx9effect", "D3DXTECHNIQUE_DESC",sizeof(D3DXTECHNIQUE_DESC), 16);
if ( sizeof(D3DXPASS_DESC) != 28 ) printf("%s,%s,%d,%d\n","d3dx9effect", "D3DXPASS_DESC",sizeof(D3DXPASS_DESC), 28);
if ( sizeof(D3DXFUNCTION_DESC) != 12 ) printf("%s,%s,%d,%d\n","d3dx9effect", "D3DXFUNCTION_DESC",sizeof(D3DXFUNCTION_DESC), 12);
if ( sizeof(D3DXIMAGE_INFO) != 28 ) printf("%s,%s,%d,%d\n","d3dx9tex", "D3DXIMAGE_INFO",sizeof(D3DXIMAGE_INFO), 28);
if ( sizeof(D3DXMESHDATA) != 4 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXMESHDATA",sizeof(D3DXMESHDATA), 4);
if ( sizeof(D3DXMESHCONTAINER) != 56 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXMESHCONTAINER",sizeof(D3DXMESHCONTAINER), 56);
if ( sizeof(D3DXFRAME) != 96 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXFRAME",sizeof(D3DXFRAME), 96);
if ( sizeof(D3DXKEY_VECTOR3) != 16 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXKEY_VECTOR3",sizeof(D3DXKEY_VECTOR3), 16);
if ( sizeof(D3DXKEY_QUATERNION) != 20 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXKEY_QUATERNION",sizeof(D3DXKEY_QUATERNION), 20);
if ( sizeof(D3DXKEY_CALLBACK) != 12 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXKEY_CALLBACK",sizeof(D3DXKEY_CALLBACK), 12);
if ( sizeof(D3DXTRACK_DESC) != 24 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXTRACK_DESC",sizeof(D3DXTRACK_DESC), 24);
if ( sizeof(D3DXEVENT_DESC) != 28 ) printf("%s,%s,%d,%d\n","d3dx9anim", "D3DXEVENT_DESC",sizeof(D3DXEVENT_DESC), 28);
if ( sizeof(D3D_SHADER_MACRO) != 16 ) printf("%s,%s,%d,%d\n","d3dcommon", "D3D_SHADER_MACRO",sizeof(D3D_SHADER_MACRO), 16);
if ( sizeof(D3D10_INPUT_ELEMENT_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_INPUT_ELEMENT_DESC",sizeof(D3D10_INPUT_ELEMENT_DESC), 32);
if ( sizeof(D3D10_SO_DECLARATION_ENTRY) != 15 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_SO_DECLARATION_ENTRY",sizeof(D3D10_SO_DECLARATION_ENTRY), 15);
if ( sizeof(D3D10_VIEWPORT) != 24 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_VIEWPORT",sizeof(D3D10_VIEWPORT), 24);
if ( sizeof(D3D10_BOX) != 24 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_BOX",sizeof(D3D10_BOX), 24);
if ( sizeof(D3D10_DEPTH_STENCILOP_DESC) != 16 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_DEPTH_STENCILOP_DESC",sizeof(D3D10_DEPTH_STENCILOP_DESC), 16);
if ( sizeof(D3D10_DEPTH_STENCIL_DESC) != 56 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_DEPTH_STENCIL_DESC",sizeof(D3D10_DEPTH_STENCIL_DESC), 56);
if ( sizeof(D3D10_BLEND_DESC) != 92 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_BLEND_DESC",sizeof(D3D10_BLEND_DESC), 92);
if ( sizeof(D3D10_RASTERIZER_DESC) != 40 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_RASTERIZER_DESC",sizeof(D3D10_RASTERIZER_DESC), 40);
if ( sizeof(D3D10_SUBRESOURCE_DATA) != 16 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_SUBRESOURCE_DATA",sizeof(D3D10_SUBRESOURCE_DATA), 16);
if ( sizeof(D3D10_BUFFER_DESC) != 20 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_BUFFER_DESC",sizeof(D3D10_BUFFER_DESC), 20);
if ( sizeof(D3D10_TEXTURE1D_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEXTURE1D_DESC",sizeof(D3D10_TEXTURE1D_DESC), 32);
if ( sizeof(D3D10_TEXTURE2D_DESC) != 44 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEXTURE2D_DESC",sizeof(D3D10_TEXTURE2D_DESC), 44);
if ( sizeof(D3D10_MAPPED_TEXTURE2D) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_MAPPED_TEXTURE2D",sizeof(D3D10_MAPPED_TEXTURE2D), 12);
if ( sizeof(D3D10_TEXTURE3D_DESC) != 36 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEXTURE3D_DESC",sizeof(D3D10_TEXTURE3D_DESC), 36);
if ( sizeof(D3D10_MAPPED_TEXTURE3D) != 16 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_MAPPED_TEXTURE3D",sizeof(D3D10_MAPPED_TEXTURE3D), 16);
if ( sizeof(D3D10_BUFFER_SRV) != 0 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_BUFFER_SRV",sizeof(D3D10_BUFFER_SRV), 0);
if ( sizeof(D3D10_TEX1D_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX1D_SRV",sizeof(D3D10_TEX1D_SRV), 8);
if ( sizeof(D3D10_TEX1D_ARRAY_SRV) != 16 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX1D_ARRAY_SRV",sizeof(D3D10_TEX1D_ARRAY_SRV), 16);
if ( sizeof(D3D10_TEX2D_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2D_SRV",sizeof(D3D10_TEX2D_SRV), 8);
if ( sizeof(D3D10_TEX2D_ARRAY_SRV) != 16 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2D_ARRAY_SRV",sizeof(D3D10_TEX2D_ARRAY_SRV), 16);
if ( sizeof(D3D10_TEX3D_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX3D_SRV",sizeof(D3D10_TEX3D_SRV), 8);
if ( sizeof(D3D10_TEXCUBE_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEXCUBE_SRV",sizeof(D3D10_TEXCUBE_SRV), 8);
if ( sizeof(D3D10_TEX2DMS_SRV) != 4 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2DMS_SRV",sizeof(D3D10_TEX2DMS_SRV), 4);
if ( sizeof(D3D10_TEX2DMS_ARRAY_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2DMS_ARRAY_SRV",sizeof(D3D10_TEX2DMS_ARRAY_SRV), 8);
if ( sizeof(D3D10_SHADER_RESOURCE_VIEW_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_SHADER_RESOURCE_VIEW_DESC",sizeof(D3D10_SHADER_RESOURCE_VIEW_DESC), 8);
if ( sizeof(D3D10_BUFFER_RTV) != 0 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_BUFFER_RTV",sizeof(D3D10_BUFFER_RTV), 0);
if ( sizeof(D3D10_TEX1D_RTV) != 4 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX1D_RTV",sizeof(D3D10_TEX1D_RTV), 4);
if ( sizeof(D3D10_TEX1D_ARRAY_RTV) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX1D_ARRAY_RTV",sizeof(D3D10_TEX1D_ARRAY_RTV), 12);
if ( sizeof(D3D10_TEX2D_RTV) != 4 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2D_RTV",sizeof(D3D10_TEX2D_RTV), 4);
if ( sizeof(D3D10_TEX2DMS_RTV) != 4 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2DMS_RTV",sizeof(D3D10_TEX2DMS_RTV), 4);
if ( sizeof(D3D10_TEX2D_ARRAY_RTV) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2D_ARRAY_RTV",sizeof(D3D10_TEX2D_ARRAY_RTV), 12);
if ( sizeof(D3D10_TEX2DMS_ARRAY_RTV) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2DMS_ARRAY_RTV",sizeof(D3D10_TEX2DMS_ARRAY_RTV), 8);
if ( sizeof(D3D10_TEX3D_RTV) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX3D_RTV",sizeof(D3D10_TEX3D_RTV), 12);
if ( sizeof(D3D10_RENDER_TARGET_VIEW_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_RENDER_TARGET_VIEW_DESC",sizeof(D3D10_RENDER_TARGET_VIEW_DESC), 8);
if ( sizeof(D3D10_TEX1D_DSV) != 4 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX1D_DSV",sizeof(D3D10_TEX1D_DSV), 4);
if ( sizeof(D3D10_TEX1D_ARRAY_DSV) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX1D_ARRAY_DSV",sizeof(D3D10_TEX1D_ARRAY_DSV), 12);
if ( sizeof(D3D10_TEX2D_DSV) != 4 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2D_DSV",sizeof(D3D10_TEX2D_DSV), 4);
if ( sizeof(D3D10_TEX2D_ARRAY_DSV) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2D_ARRAY_DSV",sizeof(D3D10_TEX2D_ARRAY_DSV), 12);
if ( sizeof(D3D10_TEX2DMS_DSV) != 4 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2DMS_DSV",sizeof(D3D10_TEX2DMS_DSV), 4);
if ( sizeof(D3D10_TEX2DMS_ARRAY_DSV) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_TEX2DMS_ARRAY_DSV",sizeof(D3D10_TEX2DMS_ARRAY_DSV), 8);
if ( sizeof(D3D10_DEPTH_STENCIL_VIEW_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_DEPTH_STENCIL_VIEW_DESC",sizeof(D3D10_DEPTH_STENCIL_VIEW_DESC), 8);
if ( sizeof(D3D10_SAMPLER_DESC) != 52 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_SAMPLER_DESC",sizeof(D3D10_SAMPLER_DESC), 52);
if ( sizeof(D3D10_QUERY_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_QUERY_DESC",sizeof(D3D10_QUERY_DESC), 8);
if ( sizeof(D3D10_QUERY_DATA_TIMESTAMP_DISJOINT) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_QUERY_DATA_TIMESTAMP_DISJOINT",sizeof(D3D10_QUERY_DATA_TIMESTAMP_DISJOINT), 12);
if ( sizeof(D3D10_QUERY_DATA_PIPELINE_STATISTICS) != 64 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_QUERY_DATA_PIPELINE_STATISTICS",sizeof(D3D10_QUERY_DATA_PIPELINE_STATISTICS), 64);
if ( sizeof(D3D10_QUERY_DATA_SO_STATISTICS) != 16 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_QUERY_DATA_SO_STATISTICS",sizeof(D3D10_QUERY_DATA_SO_STATISTICS), 16);
if ( sizeof(D3D10_COUNTER_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_COUNTER_DESC",sizeof(D3D10_COUNTER_DESC), 8);
if ( sizeof(D3D10_COUNTER_INFO) != 12 ) printf("%s,%s,%d,%d\n","d3d10", "D3D10_COUNTER_INFO",sizeof(D3D10_COUNTER_INFO), 12);
if ( sizeof(D3D10_MESSAGE) != 28 ) printf("%s,%s,%d,%d\n","d3d10sdklayers", "D3D10_MESSAGE",sizeof(D3D10_MESSAGE), 28);
if ( sizeof(D3D10_INFO_QUEUE_FILTER_DESC) != 36 ) printf("%s,%s,%d,%d\n","d3d10sdklayers", "D3D10_INFO_QUEUE_FILTER_DESC",sizeof(D3D10_INFO_QUEUE_FILTER_DESC), 36);
if ( sizeof(D3D10_INFO_QUEUE_FILTER) != 72 ) printf("%s,%s,%d,%d\n","d3d10sdklayers", "D3D10_INFO_QUEUE_FILTER",sizeof(D3D10_INFO_QUEUE_FILTER), 72);
if ( sizeof(D3D10_SHADER_DESC) != 116 ) printf("%s,%s,%d,%d\n","d3d10shader", "D3D10_SHADER_DESC",sizeof(D3D10_SHADER_DESC), 116);
if ( sizeof(D3D10_SHADER_BUFFER_DESC) != 24 ) printf("%s,%s,%d,%d\n","d3d10shader", "D3D10_SHADER_BUFFER_DESC",sizeof(D3D10_SHADER_BUFFER_DESC), 24);
if ( sizeof(D3D10_SHADER_VARIABLE_DESC) != 28 ) printf("%s,%s,%d,%d\n","d3d10shader", "D3D10_SHADER_VARIABLE_DESC",sizeof(D3D10_SHADER_VARIABLE_DESC), 28);
if ( sizeof(D3D10_SHADER_TYPE_DESC) != 28 ) printf("%s,%s,%d,%d\n","d3d10shader", "D3D10_SHADER_TYPE_DESC",sizeof(D3D10_SHADER_TYPE_DESC), 28);
if ( sizeof(D3D10_SHADER_INPUT_BIND_DESC) != 36 ) printf("%s,%s,%d,%d\n","d3d10shader", "D3D10_SHADER_INPUT_BIND_DESC",sizeof(D3D10_SHADER_INPUT_BIND_DESC), 36);
if ( sizeof(D3D10_SIGNATURE_PARAMETER_DESC) != 26 ) printf("%s,%s,%d,%d\n","d3d10shader", "D3D10_SIGNATURE_PARAMETER_DESC",sizeof(D3D10_SIGNATURE_PARAMETER_DESC), 26);
if ( sizeof(D3D10_STATE_BLOCK_MASK) != 76 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_STATE_BLOCK_MASK",sizeof(D3D10_STATE_BLOCK_MASK), 76);
if ( sizeof(D3D10_EFFECT_TYPE_DESC) != 44 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_EFFECT_TYPE_DESC",sizeof(D3D10_EFFECT_TYPE_DESC), 44);
if ( sizeof(D3D10_EFFECT_VARIABLE_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_EFFECT_VARIABLE_DESC",sizeof(D3D10_EFFECT_VARIABLE_DESC), 32);
if ( sizeof(D3D10_EFFECT_SHADER_DESC) != 40 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_EFFECT_SHADER_DESC",sizeof(D3D10_EFFECT_SHADER_DESC), 40);
if ( sizeof(D3D10_PASS_DESC) != 52 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_PASS_DESC",sizeof(D3D10_PASS_DESC), 52);
if ( sizeof(D3D10_PASS_SHADER_DESC) != 12 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_PASS_SHADER_DESC",sizeof(D3D10_PASS_SHADER_DESC), 12);
if ( sizeof(D3D10_TECHNIQUE_DESC) != 16 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_TECHNIQUE_DESC",sizeof(D3D10_TECHNIQUE_DESC), 16);
if ( sizeof(D3D10_EFFECT_DESC) != 24 ) printf("%s,%s,%d,%d\n","d3d10effect", "D3D10_EFFECT_DESC",sizeof(D3D10_EFFECT_DESC), 24);
if ( sizeof(D3D10_RENDER_TARGET_BLEND_DESC1) != 32 ) printf("%s,%s,%d,%d\n","d3d10_1", "D3D10_RENDER_TARGET_BLEND_DESC1",sizeof(D3D10_RENDER_TARGET_BLEND_DESC1), 32);
if ( sizeof(D3D10_BLEND_DESC1) != 264 ) printf("%s,%s,%d,%d\n","d3d10_1", "D3D10_BLEND_DESC1",sizeof(D3D10_BLEND_DESC1), 264);
if ( sizeof(D3D10_TEXCUBE_ARRAY_SRV1) != 16 ) printf("%s,%s,%d,%d\n","d3d10_1", "D3D10_TEXCUBE_ARRAY_SRV1",sizeof(D3D10_TEXCUBE_ARRAY_SRV1), 16);
if ( sizeof(D3D10_SHADER_RESOURCE_VIEW_DESC1) != 8 ) printf("%s,%s,%d,%d\n","d3d10_1", "D3D10_SHADER_RESOURCE_VIEW_DESC1",sizeof(D3D10_SHADER_RESOURCE_VIEW_DESC1), 8);
if ( sizeof(D3DX10_SPRITE) != 108 ) printf("%s,%s,%d,%d\n","d3dx10core", "D3DX10_SPRITE",sizeof(D3DX10_SPRITE), 108);
if ( sizeof(D3DX10_FONT_DESCW) != 88 ) printf("%s,%s,%d,%d\n","d3dx10core", "D3DX10_FONT_DESCW",sizeof(D3DX10_FONT_DESCW), 88);
if ( sizeof(D3DX10_IMAGE_INFO) != 36 ) printf("%s,%s,%d,%d\n","d3dx10tex", "D3DX10_IMAGE_INFO",sizeof(D3DX10_IMAGE_INFO), 36);
if ( sizeof(D3DX10_IMAGE_LOAD_INFO) != 56 ) printf("%s,%s,%d,%d\n","d3dx10tex", "D3DX10_IMAGE_LOAD_INFO",sizeof(D3DX10_IMAGE_LOAD_INFO), 56);
if ( sizeof(D3DX10_TEXTURE_LOAD_INFO) != 48 ) printf("%s,%s,%d,%d\n","d3dx10tex", "D3DX10_TEXTURE_LOAD_INFO",sizeof(D3DX10_TEXTURE_LOAD_INFO), 48);
if ( sizeof(D3D11_INPUT_ELEMENT_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_INPUT_ELEMENT_DESC",sizeof(D3D11_INPUT_ELEMENT_DESC), 32);
if ( sizeof(D3D11_SO_DECLARATION_ENTRY) != 19 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_SO_DECLARATION_ENTRY",sizeof(D3D11_SO_DECLARATION_ENTRY), 19);
if ( sizeof(D3D11_VIEWPORT) != 24 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_VIEWPORT",sizeof(D3D11_VIEWPORT), 24);
if ( sizeof(D3D11_BOX) != 24 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_BOX",sizeof(D3D11_BOX), 24);
if ( sizeof(D3D11_DEPTH_STENCILOP_DESC) != 16 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_DEPTH_STENCILOP_DESC",sizeof(D3D11_DEPTH_STENCILOP_DESC), 16);
if ( sizeof(D3D11_DEPTH_STENCIL_DESC) != 56 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_DEPTH_STENCIL_DESC",sizeof(D3D11_DEPTH_STENCIL_DESC), 56);
if ( sizeof(D3D11_RENDER_TARGET_BLEND_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_RENDER_TARGET_BLEND_DESC",sizeof(D3D11_RENDER_TARGET_BLEND_DESC), 32);
if ( sizeof(D3D11_BLEND_DESC) != 264 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_BLEND_DESC",sizeof(D3D11_BLEND_DESC), 264);
if ( sizeof(D3D11_RASTERIZER_DESC) != 40 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_RASTERIZER_DESC",sizeof(D3D11_RASTERIZER_DESC), 40);
if ( sizeof(D3D11_SUBRESOURCE_DATA) != 16 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_SUBRESOURCE_DATA",sizeof(D3D11_SUBRESOURCE_DATA), 16);
if ( sizeof(D3D11_MAPPED_SUBRESOURCE) != 16 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_MAPPED_SUBRESOURCE",sizeof(D3D11_MAPPED_SUBRESOURCE), 16);
if ( sizeof(D3D11_BUFFER_DESC) != 24 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_BUFFER_DESC",sizeof(D3D11_BUFFER_DESC), 24);
if ( sizeof(D3D11_TEXTURE1D_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEXTURE1D_DESC",sizeof(D3D11_TEXTURE1D_DESC), 32);
if ( sizeof(D3D11_TEXTURE2D_DESC) != 44 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEXTURE2D_DESC",sizeof(D3D11_TEXTURE2D_DESC), 44);
if ( sizeof(D3D11_TEXTURE3D_DESC) != 36 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEXTURE3D_DESC",sizeof(D3D11_TEXTURE3D_DESC), 36);
if ( sizeof(D3D11_BUFFER_SRV) != 0 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_BUFFER_SRV",sizeof(D3D11_BUFFER_SRV), 0);
if ( sizeof(D3D11_BUFFEREX_SRV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_BUFFEREX_SRV",sizeof(D3D11_BUFFEREX_SRV), 12);
if ( sizeof(D3D11_TEX1D_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_SRV",sizeof(D3D11_TEX1D_SRV), 8);
if ( sizeof(D3D11_TEX1D_ARRAY_SRV) != 16 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_ARRAY_SRV",sizeof(D3D11_TEX1D_ARRAY_SRV), 16);
if ( sizeof(D3D11_TEX2D_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_SRV",sizeof(D3D11_TEX2D_SRV), 8);
if ( sizeof(D3D11_TEX2D_ARRAY_SRV) != 16 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_ARRAY_SRV",sizeof(D3D11_TEX2D_ARRAY_SRV), 16);
if ( sizeof(D3D11_TEX3D_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX3D_SRV",sizeof(D3D11_TEX3D_SRV), 8);
if ( sizeof(D3D11_TEXCUBE_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEXCUBE_SRV",sizeof(D3D11_TEXCUBE_SRV), 8);
if ( sizeof(D3D11_TEXCUBE_ARRAY_SRV) != 16 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEXCUBE_ARRAY_SRV",sizeof(D3D11_TEXCUBE_ARRAY_SRV), 16);
if ( sizeof(D3D11_TEX2DMS_SRV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2DMS_SRV",sizeof(D3D11_TEX2DMS_SRV), 4);
if ( sizeof(D3D11_TEX2DMS_ARRAY_SRV) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2DMS_ARRAY_SRV",sizeof(D3D11_TEX2DMS_ARRAY_SRV), 8);
if ( sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_SHADER_RESOURCE_VIEW_DESC",sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC), 8);
if ( sizeof(D3D11_BUFFER_RTV) != 0 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_BUFFER_RTV",sizeof(D3D11_BUFFER_RTV), 0);
if ( sizeof(D3D11_TEX1D_RTV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_RTV",sizeof(D3D11_TEX1D_RTV), 4);
if ( sizeof(D3D11_TEX1D_ARRAY_RTV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_ARRAY_RTV",sizeof(D3D11_TEX1D_ARRAY_RTV), 12);
if ( sizeof(D3D11_TEX2D_RTV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_RTV",sizeof(D3D11_TEX2D_RTV), 4);
if ( sizeof(D3D11_TEX2DMS_RTV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2DMS_RTV",sizeof(D3D11_TEX2DMS_RTV), 4);
if ( sizeof(D3D11_TEX2D_ARRAY_RTV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_ARRAY_RTV",sizeof(D3D11_TEX2D_ARRAY_RTV), 12);
if ( sizeof(D3D11_TEX2DMS_ARRAY_RTV) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2DMS_ARRAY_RTV",sizeof(D3D11_TEX2DMS_ARRAY_RTV), 8);
if ( sizeof(D3D11_TEX3D_RTV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX3D_RTV",sizeof(D3D11_TEX3D_RTV), 12);
if ( sizeof(D3D11_RENDER_TARGET_VIEW_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_RENDER_TARGET_VIEW_DESC",sizeof(D3D11_RENDER_TARGET_VIEW_DESC), 8);
if ( sizeof(D3D11_TEX1D_DSV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_DSV",sizeof(D3D11_TEX1D_DSV), 4);
if ( sizeof(D3D11_TEX1D_ARRAY_DSV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_ARRAY_DSV",sizeof(D3D11_TEX1D_ARRAY_DSV), 12);
if ( sizeof(D3D11_TEX2D_DSV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_DSV",sizeof(D3D11_TEX2D_DSV), 4);
if ( sizeof(D3D11_TEX2D_ARRAY_DSV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_ARRAY_DSV",sizeof(D3D11_TEX2D_ARRAY_DSV), 12);
if ( sizeof(D3D11_TEX2DMS_DSV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2DMS_DSV",sizeof(D3D11_TEX2DMS_DSV), 4);
if ( sizeof(D3D11_TEX2DMS_ARRAY_DSV) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2DMS_ARRAY_DSV",sizeof(D3D11_TEX2DMS_ARRAY_DSV), 8);
if ( sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_DEPTH_STENCIL_VIEW_DESC",sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC), 12);
if ( sizeof(D3D11_BUFFER_UAV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_BUFFER_UAV",sizeof(D3D11_BUFFER_UAV), 12);
if ( sizeof(D3D11_TEX1D_UAV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_UAV",sizeof(D3D11_TEX1D_UAV), 4);
if ( sizeof(D3D11_TEX1D_ARRAY_UAV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX1D_ARRAY_UAV",sizeof(D3D11_TEX1D_ARRAY_UAV), 12);
if ( sizeof(D3D11_TEX2D_UAV) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_UAV",sizeof(D3D11_TEX2D_UAV), 4);
if ( sizeof(D3D11_TEX2D_ARRAY_UAV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX2D_ARRAY_UAV",sizeof(D3D11_TEX2D_ARRAY_UAV), 12);
if ( sizeof(D3D11_TEX3D_UAV) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_TEX3D_UAV",sizeof(D3D11_TEX3D_UAV), 12);
if ( sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_UNORDERED_ACCESS_VIEW_DESC",sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC), 8);
if ( sizeof(D3D11_SAMPLER_DESC) != 52 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_SAMPLER_DESC",sizeof(D3D11_SAMPLER_DESC), 52);
if ( sizeof(D3D11_QUERY_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_QUERY_DESC",sizeof(D3D11_QUERY_DESC), 8);
if ( sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_QUERY_DATA_TIMESTAMP_DISJOINT",sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT), 12);
if ( sizeof(D3D11_QUERY_DATA_PIPELINE_STATISTICS) != 88 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_QUERY_DATA_PIPELINE_STATISTICS",sizeof(D3D11_QUERY_DATA_PIPELINE_STATISTICS), 88);
if ( sizeof(D3D11_QUERY_DATA_SO_STATISTICS) != 16 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_QUERY_DATA_SO_STATISTICS",sizeof(D3D11_QUERY_DATA_SO_STATISTICS), 16);
if ( sizeof(D3D11_COUNTER_DESC) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_COUNTER_DESC",sizeof(D3D11_COUNTER_DESC), 8);
if ( sizeof(D3D11_COUNTER_INFO) != 12 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_COUNTER_INFO",sizeof(D3D11_COUNTER_INFO), 12);
if ( sizeof(D3D11_CLASS_INSTANCE_DESC) != 32 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_CLASS_INSTANCE_DESC",sizeof(D3D11_CLASS_INSTANCE_DESC), 32);
if ( sizeof(D3D11_FEATURE_DATA_THREADING) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_FEATURE_DATA_THREADING",sizeof(D3D11_FEATURE_DATA_THREADING), 8);
if ( sizeof(D3D11_FEATURE_DATA_DOUBLES) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_FEATURE_DATA_DOUBLES",sizeof(D3D11_FEATURE_DATA_DOUBLES), 4);
if ( sizeof(D3D11_FEATURE_DATA_FORMAT_SUPPORT) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_FEATURE_DATA_FORMAT_SUPPORT",sizeof(D3D11_FEATURE_DATA_FORMAT_SUPPORT), 8);
if ( sizeof(D3D11_FEATURE_DATA_FORMAT_SUPPORT2) != 8 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_FEATURE_DATA_FORMAT_SUPPORT2",sizeof(D3D11_FEATURE_DATA_FORMAT_SUPPORT2), 8);
if ( sizeof(D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS) != 4 ) printf("%s,%s,%d,%d\n","d3d11", "D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS",sizeof(D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS), 4);
if ( sizeof(D3D11_SIGNATURE_PARAMETER_DESC) != 30 ) printf("%s,%s,%d,%d\n","d3d11shader", "D3D11_SIGNATURE_PARAMETER_DESC",sizeof(D3D11_SIGNATURE_PARAMETER_DESC), 30);
if ( sizeof(D3D11_SHADER_BUFFER_DESC) != 24 ) printf("%s,%s,%d,%d\n","d3d11shader", "D3D11_SHADER_BUFFER_DESC",sizeof(D3D11_SHADER_BUFFER_DESC), 24);
if ( sizeof(D3D11_SHADER_VARIABLE_DESC) != 44 ) printf("%s,%s,%d,%d\n","d3d11shader", "D3D11_SHADER_VARIABLE_DESC",sizeof(D3D11_SHADER_VARIABLE_DESC), 44);
if ( sizeof(D3D11_SHADER_TYPE_DESC) != 36 ) printf("%s,%s,%d,%d\n","d3d11shader", "D3D11_SHADER_TYPE_DESC",sizeof(D3D11_SHADER_TYPE_DESC), 36);
if ( sizeof(D3D11_SHADER_DESC) != 156 ) printf("%s,%s,%d,%d\n","d3d11shader", "D3D11_SHADER_DESC",sizeof(D3D11_SHADER_DESC), 156);
if ( sizeof(D3D11_SHADER_INPUT_BIND_DESC) != 36 ) printf("%s,%s,%d,%d\n","d3d11shader", "D3D11_SHADER_INPUT_BIND_DESC",sizeof(D3D11_SHADER_INPUT_BIND_DESC), 36);
if ( sizeof(D3DX11_IMAGE_INFO) != 36 ) printf("%s,%s,%d,%d\n","d3dx11tex", "D3DX11_IMAGE_INFO",sizeof(D3DX11_IMAGE_INFO), 36);
if ( sizeof(D3DX11_IMAGE_LOAD_INFO) != 56 ) printf("%s,%s,%d,%d\n","d3dx11tex", "D3DX11_IMAGE_LOAD_INFO",sizeof(D3DX11_IMAGE_LOAD_INFO), 56);
if ( sizeof(D3DX11_TEXTURE_LOAD_INFO) != 48 ) printf("%s,%s,%d,%d\n","d3dx11tex", "D3DX11_TEXTURE_LOAD_INFO",sizeof(D3DX11_TEXTURE_LOAD_INFO), 48);
if ( sizeof(D3D_SHADER_DATA) != 0 ) printf("%s,%s,%d,%d\n","d3dcompiler", "D3D_SHADER_DATA",sizeof(D3D_SHADER_DATA), 0);
if ( sizeof(DWRITE_FONT_METRICS) != 20 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_FONT_METRICS",sizeof(DWRITE_FONT_METRICS), 20);
if ( sizeof(DWRITE_GLYPH_METRICS) != 28 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_GLYPH_METRICS",sizeof(DWRITE_GLYPH_METRICS), 28);
if ( sizeof(DWRITE_GLYPH_OFFSET) != 8 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_GLYPH_OFFSET",sizeof(DWRITE_GLYPH_OFFSET), 8);
if ( sizeof(DWRITE_MATRIX) != 24 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_MATRIX",sizeof(DWRITE_MATRIX), 24);
if ( sizeof(DWRITE_TEXT_RANGE) != 8 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_TEXT_RANGE",sizeof(DWRITE_TEXT_RANGE), 8);
if ( sizeof(DWRITE_FONT_FEATURE) != 8 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_FONT_FEATURE",sizeof(DWRITE_FONT_FEATURE), 8);
if ( sizeof(DWRITE_TYPOGRAPHIC_FEATURES) != 12 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_TYPOGRAPHIC_FEATURES",sizeof(DWRITE_TYPOGRAPHIC_FEATURES), 12);
if ( sizeof(DWRITE_TRIMMING) != 12 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_TRIMMING",sizeof(DWRITE_TRIMMING), 12);
if ( sizeof(DWRITE_SCRIPT_ANALYSIS) != 6 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_SCRIPT_ANALYSIS",sizeof(DWRITE_SCRIPT_ANALYSIS), 6);
if ( sizeof(DWRITE_LINE_BREAKPOINT) != 0 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_LINE_BREAKPOINT",sizeof(DWRITE_LINE_BREAKPOINT), 0);
if ( sizeof(DWRITE_SHAPING_TEXT_PROPERTIES) != 0 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_SHAPING_TEXT_PROPERTIES",sizeof(DWRITE_SHAPING_TEXT_PROPERTIES), 0);
if ( sizeof(DWRITE_SHAPING_GLYPH_PROPERTIES) != 0 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_SHAPING_GLYPH_PROPERTIES",sizeof(DWRITE_SHAPING_GLYPH_PROPERTIES), 0);
if ( sizeof(DWRITE_GLYPH_RUN) != 48 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_GLYPH_RUN",sizeof(DWRITE_GLYPH_RUN), 48);
if ( sizeof(DWRITE_GLYPH_RUN_DESCRIPTION) != 32 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_GLYPH_RUN_DESCRIPTION",sizeof(DWRITE_GLYPH_RUN_DESCRIPTION), 32);
if ( sizeof(DWRITE_UNDERLINE) != 36 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_UNDERLINE",sizeof(DWRITE_UNDERLINE), 36);
if ( sizeof(DWRITE_STRIKETHROUGH) != 32 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_STRIKETHROUGH",sizeof(DWRITE_STRIKETHROUGH), 32);
if ( sizeof(DWRITE_LINE_METRICS) != 24 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_LINE_METRICS",sizeof(DWRITE_LINE_METRICS), 24);
if ( sizeof(DWRITE_CLUSTER_METRICS) != 6 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_CLUSTER_METRICS",sizeof(DWRITE_CLUSTER_METRICS), 6);
if ( sizeof(DWRITE_TEXT_METRICS) != 36 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_TEXT_METRICS",sizeof(DWRITE_TEXT_METRICS), 36);
if ( sizeof(DWRITE_INLINE_OBJECT_METRICS) != 16 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_INLINE_OBJECT_METRICS",sizeof(DWRITE_INLINE_OBJECT_METRICS), 16);
if ( sizeof(DWRITE_OVERHANG_METRICS) != 16 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_OVERHANG_METRICS",sizeof(DWRITE_OVERHANG_METRICS), 16);
if ( sizeof(DWRITE_HIT_TEST_METRICS) != 36 ) printf("%s,%s,%d,%d\n","dwrite", "DWRITE_HIT_TEST_METRICS",sizeof(DWRITE_HIT_TEST_METRICS), 36);
if ( sizeof(D2D1_PIXEL_FORMAT) != 8 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_PIXEL_FORMAT",sizeof(D2D1_PIXEL_FORMAT), 8);
if ( sizeof(D2D1_BITMAP_PROPERTIES) != 16 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_BITMAP_PROPERTIES",sizeof(D2D1_BITMAP_PROPERTIES), 16);
if ( sizeof(D2D1_GRADIENT_STOP) != 20 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_GRADIENT_STOP",sizeof(D2D1_GRADIENT_STOP), 20);
if ( sizeof(D2D1_BRUSH_PROPERTIES) != 28 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_BRUSH_PROPERTIES",sizeof(D2D1_BRUSH_PROPERTIES), 28);
if ( sizeof(D2D1_BITMAP_BRUSH_PROPERTIES) != 12 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_BITMAP_BRUSH_PROPERTIES",sizeof(D2D1_BITMAP_BRUSH_PROPERTIES), 12);
if ( sizeof(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES) != 16 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES",sizeof(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES), 16);
if ( sizeof(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES) != 24 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES",sizeof(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES), 24);
if ( sizeof(D2D1_BEZIER_SEGMENT) != 24 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_BEZIER_SEGMENT",sizeof(D2D1_BEZIER_SEGMENT), 24);
if ( sizeof(D2D1_TRIANGLE) != 24 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_TRIANGLE",sizeof(D2D1_TRIANGLE), 24);
if ( sizeof(D2D1_ARC_SEGMENT) != 28 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_ARC_SEGMENT",sizeof(D2D1_ARC_SEGMENT), 28);
if ( sizeof(D2D1_QUADRATIC_BEZIER_SEGMENT) != 16 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_QUADRATIC_BEZIER_SEGMENT",sizeof(D2D1_QUADRATIC_BEZIER_SEGMENT), 16);
if ( sizeof(D2D1_ELLIPSE) != 16 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_ELLIPSE",sizeof(D2D1_ELLIPSE), 16);
if ( sizeof(D2D1_ROUNDED_RECT) != 24 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_ROUNDED_RECT",sizeof(D2D1_ROUNDED_RECT), 24);
if ( sizeof(D2D1_STROKE_STYLE_PROPERTIES) != 28 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_STROKE_STYLE_PROPERTIES",sizeof(D2D1_STROKE_STYLE_PROPERTIES), 28);
if ( sizeof(D2D1_LAYER_PARAMETERS) != 68 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_LAYER_PARAMETERS",sizeof(D2D1_LAYER_PARAMETERS), 68);
if ( sizeof(D2D1_RENDER_TARGET_PROPERTIES) != 28 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_RENDER_TARGET_PROPERTIES",sizeof(D2D1_RENDER_TARGET_PROPERTIES), 28);
if ( sizeof(D2D1_HWND_RENDER_TARGET_PROPERTIES) != 20 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_HWND_RENDER_TARGET_PROPERTIES",sizeof(D2D1_HWND_RENDER_TARGET_PROPERTIES), 20);
if ( sizeof(D2D1_DRAWING_STATE_DESCRIPTION) != 48 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_DRAWING_STATE_DESCRIPTION",sizeof(D2D1_DRAWING_STATE_DESCRIPTION), 48);
if ( sizeof(D2D1_FACTORY_OPTIONS) != 4 ) printf("%s,%s,%d,%d\n","d2d1", "D2D1_FACTORY_OPTIONS",sizeof(D2D1_FACTORY_OPTIONS), 4);



	return 0;
}

