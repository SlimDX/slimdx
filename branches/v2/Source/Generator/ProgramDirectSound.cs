// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    internal partial class Program
    {
        public unsafe void MapDirectSound()
        {
            gen.MapIncludeToNamespace("dsound", Global.Name + ".DirectSound");

            // Limit Find to "dsound" in this method (in order to be sure that we don't touch other includes)
            group.FindContext.Add("dsound");

            // --------------------------------------------------------------------------------------------------------
            // DirectSound Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.CreateEnumFromMacros(@"^DSCAPS_.*", "DSCAPS_FLAGS");
            group.CreateEnumFromMacros(@"^DSSPEAKER_[^G].*", "DSSPEAKER_ENUM");
            group.CreateEnumFromMacros(@"^DSSPEAKER_GEOMETRY.*", "DSSPEAKER_GEOMETRY_ENUM");
            group.CreateEnumFromMacros(@"^DSBCAPS_.*", "DSBCAPS_FLAGS");
            group.CreateEnumFromMacros(@"^DSBPLAY_.*", "DSBPLAY_FLAGS");
            group.CreateEnumFromMacros(@"^DSBSTATUS_.*", "DSBSTATUS_FLAGS");
            group.CreateEnumFromMacros(@"^DSCBCAPS_.*", "DSCBCAPS_FLAGS");
            group.CreateEnumFromMacros(@"^DSCCAPS_.*", "DSCCAPS_FLAGS");   
            
            group.CreateEnumFromMacros(@"^DSBLOCK_.*", "DSBLOCK_ENUM");
            group.CreateEnumFromMacros(@"^DSSCL_.*", "DSSCL_ENUM");
            group.CreateEnumFromMacros(@"^DS3DMODE_.*", "DS3DMODE");
            group.CreateEnumFromMacros(@"^DSCFX_LOC.*", "DSCFX_ENUM");       
            
            group.TagName<CppEnum>(@"^DSCAPS_FLAGS$", "CapabilitiesFlags");
            group.TagName<CppEnum>(@"^DSSPEAKER_ENUM$", "SpeakerConfiguration");
            group.TagName<CppEnum>(@"^DSSPEAKER_GEOMETRY_ENUM$", "SpeakerGeometry");
            group.TagName<CppEnum>(@"^DSBCAPS_FLAGS$", "BufferFlags");
            group.TagName<CppEnum>(@"^DSBPLAY_FLAGS$", "PlayFlags");
            group.TagName<CppEnum>(@"^DSBSTATUS_FLAGS$", "BufferStatus");
            group.TagName<CppEnum>(@"^DSBLOCK_ENUM$", "LockFlags");
            group.FindFirst<CppEnum>(@"^DSBLOCK_ENUM$").AddNone();
            group.TagName<CppEnum>(@"^DSSCL_ENUM$", "CooperativeLevel");
            group.TagName<CppEnum>(@"^DS3DMODE$", "Mode3D");
            group.TagName<CppEnum>(@"^DSOUND_ENUM_0$", "SoundEffectResult");
            group.TagName<CppEnum>(@"^DSOUND_ENUM_1$", "I3DL2MaterialPreset");
            group.TagName<CppEnum>(@"^DSOUND_ENUM_2$", "I3DL2ReverbPreset");
            group.TagName<CppEnum>(@"^DSCFX_ENUM$", "CaptureEffectResult");
            group.TagName<CppEnum>(@"^DSCBCAPS_FLAGS$", "CaptureBufferCapabilitiesFlags");
            group.TagName<CppEnum>(@"^DSCCAPS_FLAGS$", "CaptureCapabilitiesFlags");           
            
            group.TagName<CppEnumItem>(@"^DSCAPS_CERTIFIED$","Certified");
            group.TagName<CppEnumItem>(@"^DSCAPS_CONTINUOUSRATE$", "ContinousRate");
            group.TagName<CppEnumItem>(@"^DSCAPS_EMULDRIVER$", "EmulatedDriver");
            group.TagName<CppEnumItem>(@"^DSCAPS_PRIMARY16BIT$", "PrimaryBuffer16Bit");
            group.TagName<CppEnumItem>(@"^DSCAPS_PRIMARY8BIT$", "PrimaryBuffer8Bit");
            group.TagName<CppEnumItem>(@"^DSCAPS_PRIMARYMONO$", "PrimaryBufferMono");
            group.TagName<CppEnumItem>(@"^DSCAPS_PRIMARYSTEREO$", "PrimaryBufferStereo");
            group.TagName<CppEnumItem>(@"^DSCAPS_SECONDARY16BIT$", "SecondaryBufer16Bit");
            group.TagName<CppEnumItem>(@"^DSCAPS_SECONDARY8BIT$", "SecondaryBufer8Bit");
            group.TagName<CppEnumItem>(@"^DSCAPS_SECONDARYMONO$", "SecondaryBufferMono");
            group.TagName<CppEnumItem>(@"^DSCAPS_SECONDARYSTEREO$", "SecondaryBufferStereo");

            group.TagName<CppEnumItem>(@"^DSCCAPS_EMULDRIVER$", "EmulateDriver");
            group.FindFirst<CppEnumItem>(@"^DSCCAPS_EMULDRIVER$").Value = "CapabilitiesFlags.EmulatedDriver";
            group.TagName<CppEnumItem>(@"^DSCCAPS_CERTIFIED$", "Certified");
            group.FindFirst<CppEnumItem>(@"^DSCCAPS_CERTIFIED$").Value = "CapabilitiesFlags.Certified";
            group.TagName<CppEnumItem>(@"^DSCCAPS_MULTIPLECAPTURE$", "MultipleCapture");

            group.TagName<CppEnumItem>(@"^DSFXR_PRESENT$", "Present");
            group.TagName<CppEnumItem>(@"^DSFXR_LOCHARDWARE$", "LocatedInHardware");
            group.TagName<CppEnumItem>(@"^DSFXR_LOCSOFTWARE$", "LocatedInSoftware");
            group.TagName<CppEnumItem>(@"^DSFXR_UNALLOCATED$", "Unallocated");
            group.TagName<CppEnumItem>(@"^DSFXR_FAILED$", "Failed");
            group.TagName<CppEnumItem>(@"^DSFXR_UNKNOWN$", "Unknown");

            group.TagName<CppEnumItem>(@"^DSCFX_LOCHARDWARE$", "LocatedInHardware");
            group.TagName<CppEnumItem>(@"^DSCFX_LOCSOFTWARE$", "LocatedInSoftware");

            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT$", "Default");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_GENERIC$", "Generic");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL$", "PaddedCell");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_ROOM$", "Room");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_BATHROOM$", "Bathroom");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM$", "LivingRoom");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_STONEROOM$", "StoneRoom");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM$", "Auditorium");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL$", "ConcertHall");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_CAVE$", "Cave");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_ARENA$", "Arena");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_HANGAR$", "Hangar");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY$", "CarpetedHallway");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_HALLWAY$", "Hallway");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR$", "StoneCorridor");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_ALLEY$", "Alley");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_FOREST$", "Forest");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_CITY$", "City");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS$", "Mountains");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_QUARRY$", "Quarry");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_PLAIN$", "Plain");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT$", "ParkingLot");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE$", "SewerPipe");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_UNDERWATER$", "Underwater");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_SMALLROOM$", "SmallRoom");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM$", "MediumRoom");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEROOM$", "LargeRoom");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL$", "MediumHall");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEHALL$", "LargeHall");
            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE$", "Plate");

            group.TagName<CppEnumItem>(@"^DSFX_I3DL2_MATERIAL_PRESET_(.*)$", "$1",false);


            group.TagName<CppEnumItem>(@"^DSSPEAKER_DIRECTOUT$", "DirectOut");
            group.TagName<CppEnumItem>(@"^DSSPEAKER_QUAD$", "Quadrophonic");
            group.TagName<CppEnumItem>(@"^DSSPEAKER_5POINT1$", "FivePointOne");
            group.TagName<CppEnumItem>(@"^DSSPEAKER_7POINT1$", "SevenPointOne");
            group.TagName<CppEnumItem>(@"^DSSPEAKER_7POINT1_WIDE$", "SevenPointOneWide");
            group.FindFirst<CppEnumItem>(@"^DSSPEAKER_7POINT1_WIDE$").Value = "SevenPointOne";
            group.TagName<CppEnumItem>(@"^DSSPEAKER_5POINT1_BACK$", "FivePointOneBack");
            group.FindFirst<CppEnumItem>(@"^DSSPEAKER_5POINT1_BACK$").Value = "FivePointOne";
            group.TagName<CppEnumItem>(@"^DSSPEAKER_5POINT1_SURROUND$", "FivePointOneSurround");
            group.TagName<CppEnumItem>(@"^DSSPEAKER_7POINT1_SURROUND$", "SevenPointOneSurround");
            group.TagName<CppEnumItem>(@"^DSBCAPS_PRIMARYBUFFER$", "PrimaryBuffer");
            group.TagName<CppEnumItem>(@"^DSBCAPS_LOCHARDWARE$", "Hardware");
            group.TagName<CppEnumItem>(@"^DSBCAPS_LOCSOFTWARE$", "Software");
            group.TagName<CppEnumItem>(@"^DSBCAPS_CTRL3D$", "Control3D");
            group.TagName<CppEnumItem>(@"^DSBCAPS_CTRLFREQUENCY$", "ControlFrequency");
            group.TagName<CppEnumItem>(@"^DSBCAPS_CTRLPAN$", "ControlPan");
            group.TagName<CppEnumItem>(@"^DSBCAPS_CTRLVOLUME$", "ControlVolume");
            group.TagName<CppEnumItem>(@"^DSBCAPS_CTRLPOSITIONNOTIFY$", "ControlPositionNotify");
            group.TagName<CppEnumItem>(@"^DSBCAPS_CTRLFX$", "ControlEffects");
            group.TagName<CppEnumItem>(@"^DSBCAPS_STICKYFOCUS$", "StickyFocus");
            group.TagName<CppEnumItem>(@"^DSBCAPS_GLOBALFOCUS$", "GlobalFocus");
            group.TagName<CppEnumItem>(@"^DSBCAPS_GETCURRENTPOSITION2$", "GetCurrentPosition2");
            group.TagName<CppEnumItem>(@"^DSBCAPS_MUTE3DATMAXDISTANCE$", "Mute3DAtMaxDistance");
            group.TagName<CppEnumItem>(@"^DSBCAPS_LOCDEFER$", "Defer");
            group.TagName<CppEnumItem>(@"^DSBPLAY_LOCHARDWARE$", "Hardware");
            group.TagName<CppEnumItem>(@"^DSBPLAY_LOCSOFTWARE$", "Software");
            group.TagName<CppEnumItem>(@"^DSBPLAY_TERMINATEBY_TIME$", "TerminateByTime");
            group.TagName<CppEnumItem>(@"^DSBPLAY_TERMINATEBY_DISTANCE$", "TerminateByDistance");
            group.TagName<CppEnumItem>(@"^DSBPLAY_TERMINATEBY_PRIORITY$", "TerminateByPriority");
            group.TagName<CppEnumItem>(@"^DSBSTATUS_BUFFERLOST$", "BufferLost");
            group.TagName<CppEnumItem>(@"^DSBSTATUS_LOCHARDWARE$", "Hardware");
            group.TagName<CppEnumItem>(@"^DSBSTATUS_LOCSOFTWARE$", "Software");
            group.TagName<CppEnumItem>(@"^DSBLOCK_FROMWRITECURSOR$", "FromWriteCursor");
            group.TagName<CppEnumItem>(@"^DSBLOCK_ENTIREBUFFER$", "EntireBuffer");
            // Warning Enums [CooperativeLevel] have different Flags SlimDX [False] != SlimDX [True]
            group.TagName<CppEnumItem>(@"^DSSCL_WRITEPRIMARY$", "WritePrimary");
            group.TagName<CppEnumItem>(@"^DS3DMODE_HEADRELATIVE$", "HeadRelative");


            // --------------------------------------------------------------------------------------------------------
            // DirectSound Structures
            // --------------------------------------------------------------------------------------------------------
            // All field dwSize and dwReserved must be hidden for practical usage
            group.TagVisibility<CppField>(@"^DS.*::dwSize$", Visibility.Internal);
            group.TagVisibility<CppField>(@"^DS.*::dwReserved\d?$", Visibility.Internal);

            group.TagTypeAndName<CppField>(@"^DSCAPS::dwFlags", "DSCAPS_FLAGS");
            group.TagTypeAndName<CppField>(@"^DSBCAPS::dwFlags", "DSBCAPS_FLAGS");
            group.TagTypeAndName<CppField>(@"^DSCEFFECTDESC::dwFlags", "DSCFX_ENUM");
            group.TagTypeAndName<CppField>(@"^DSBUFFERDESC::dwFlags", "DSBCAPS_FLAGS");
            group.TagTypeAndName<CppField>(@"^DSCBCAPS::dwFlags", "DSCBCAPS_FLAGS");
            group.TagTypeAndName<CppField>(@"^DSCBUFFERDESC::dwFlags", "DSCBCAPS_FLAGS");

            // Suprress all prefix (dw , f, fl, l...etc.)
            group.TagName<CppField>(@"^DS.*::[a-w][a-w]?(.*)$", "$1");

            group.Remove<CppStruct>(@"^DSBUFFERDESC1$");
            group.Remove<CppStruct>(@"^DSCBUFFERDESC1$");
            
            group.TagName<CppStruct>(@"^DSCAPS$", "Capabilities");
            group.TagStructToNative(@"^DSCAPS$",true, true);
            group.TagName<CppField>(@"^DSCAPS::dw(.*)Hw(.*)$", "$1Hardware$2");            
            
            group.TagName<CppStruct>(@"^DSBCAPS$", "BufferCapabilities");
            group.TagStructToNative(@"^DSBCAPS$", true, true);
          
            group.TagName<CppStruct>(@"^DSEFFECTDESC$", "SoundBufferEffectDescription");
            group.TagStructToNative(@"^DSEFFECTDESC$", true, true);

            group.TagName<CppStruct>(@"^DSCEFFECTDESC$", "CaptureEffectDescription");
            group.TagStructToNative(@"^DSCEFFECTDESC$", true, true);

            group.TagName<CppStruct>(@"^DSBUFFERDESC$", "SoundBufferDescription");
            group.TagStructToNative(@"^DSBUFFERDESC$", true, true, true);
            group.TagVisibility<CppField>(@"^DSBUFFERDESC::lpwfxFormat", Visibility.Internal);
            group.TagName<CppField>(@"^DSBUFFERDESC::lpwfxFormat", "pFormat");                       
            group.TagName<CppField>(@"^DSBUFFERDESC::guid3DAlgorithm", "AlgorithmFor3D");           

            group.TagName<CppStruct>(@"^DS3DBUFFER$", "Buffer3DSettings");
            group.TagStructToNative(@"^DS3DBUFFER$", true, true);

            group.TagName<CppStruct>(@"^DS3DLISTENER$", "Listener3DSettings");
            group.TagStructToNative(@"^DS3DLISTENER$", true, true);

            group.TagName<CppStruct>(@"^DSCBUFFERDESC$", "CaptureBufferDescription");
            group.TagStructToNative(@"^DSCBUFFERDESC$", true, true);

            group.TagName<CppStruct>(@"^DSCBCAPS$", "CaptureBufferCapabilities");
            group.TagStructToNative(@"^DSCBCAPS$", true, true);

            group.TagName<CppStruct>(@"^DSCCAPS$", "CaptureCapabilities");
            group.TagStructToNative(@"^DSCCAPS$", true, true);

            group.TagName<CppStruct>(@"^DSBPOSITIONNOTIFY$", "NotificationPosition");
            group.TagName<CppStruct>(@"^DSFX(.*)$", "$1Settings");
            group.TagName<CppStruct>(@"^DSCFXAec$", "AcousticEchoCancelSettings");
            group.TagName<CppStruct>(@"^DSCFXNoiseSuppress$", "NoiseSuppressSettings");
            
            // --------------------------------------------------------------------------------------------------------
            // DirectSound Interfaces
            // --------------------------------------------------------------------------------------------------------
            // Remove interface
            group.Remove<CppInterface>(@"^IKsPropertySet");
            group.Remove<CppInterface>(@"^IReferenceClock");

            // Global naming
            group.TagName<CppInterface>(@"^IDirectSound(.+)", "$1", false);
            group.TagName<CppInterface>(@"^IDirectSoundFX(.*)$", "$1");
            group.TagName<CppInterface>(@"^IDirectSoundNotify$", "SoundBufferNotifier");
            group.TagName<CppInterface>(@"^IDirectSound$", "DirectSoundBase");
            group.TagName<CppInterface>(@"^IDirectSound8$", "DirectSound");
            group.TagName<CppInterface>(@"^IDirectSoundCaptureBuffer$", "CaptureBufferBase");
            group.TagName<CppInterface>(@"^IDirectSoundCaptureBuffer8$", "CaptureBuffer");
            group.TagName<CppInterface>(@"^IDirectSoundBuffer$", "SoundBuffer");
            group.TagName<CppInterface>(@"^IDirectSoundBuffer8$", "SecondarySoundBuffer");
            group.TagName<CppInterface>(@"^IDirectSound3DListener$", "SoundListener3D");
            group.TagName<CppInterface>(@"^IDirectSound3DBuffer$", "SoundBuffer3D");
            group.TagName<CppInterface>(@"^IDirectSoundCaptureFXAec$", "AcousticEchoCancel");
            group.TagName<CppInterface>(@"^IDirectSoundCaptureFXNoiseSuppress$", "NoiseSuppress");

            // Set the IDirectSoundNotify to be internal (used by direct methods)
            group.TagVisibility<CppInterface>(@"^IDirectSoundNotify$", Visibility.Internal);

            // Patch parameter names to be more .Net friendly
            group.TagName<CppParameter>(@"^IDirectSound.*::dw(.*)$", "$1", false);
            group.TagName<CppParameter>(@"^IDirectSound.*::pdw(.*)$", "$1", false);
            group.TagName<CppParameter>(@"^IDirectSound.*::fl(.*)$", "$1", false);
            group.TagName<CppParameter>(@"^IDirectSound.*::l(.*)$", "$1", false);
            //group.TagName<CppParameter>(@"^IDirectSound.*::pc(.*)$", "$1", false);
            
            // Make IDirectSoundBuffer abstract
            // We will provide a PrimarySoundBuffer and SecondarySoundBuffer
            group.TagVisibility<CppInterface>(@"^IDirectSoundBuffer$", Visibility.Public | Visibility.Abstract);
            group.TagVisibility<CppMethod>(@"^IDirectSoundBuffer::Play$", Visibility.Internal);
            group.TagTypeAndName<CppParameter>(@"^IDirectSoundBuffer::Play::dwFlags", "DSBPLAY_FLAGS");
            group.TagName<CppMethod>(@"^IDirectSoundBuffer8::SetFX$", "SetEffect");
            group.TagTypeAndName<CppParameter>(@"^IDirectSoundBuffer::Lock::dwFlags", "DSBLOCK_ENUM");

            // Lock
            group.TagVisibility<CppMethod>(@"^IDirectSoundBuffer::Lock", Visibility.Internal);
            group.TagParameter(@"^IDirectSoundBuffer::Lock::ppvAudioPtr1", CppAttribute.Out);
            group.TagParameter(@"^IDirectSoundBuffer::Lock::ppvAudioPtr2", CppAttribute.Out);
            group.TagName<CppParameter>(@"^IDirectSoundBuffer::Lock::ppvAudioPtr1", "audioPtr1");
            group.TagName<CppParameter>(@"^IDirectSoundBuffer::Lock::ppvAudioPtr2", "audioPtr2");

            // Unlock
            group.TagVisibility<CppMethod>(@"^IDirectSoundBuffer::Unlock", Visibility.Internal);

            // IDirectSound 
            // And make CreateSoundBuffer and DuplicateSoundBuffer methods using void* instead of IDirectSoundBuffer*
            group.TagTypeAndName<CppParameter>(@"^IDirectSound::CreateSoundBuffer::ppDSBuffer$", "void");
            group.TagTypeAndName<CppParameter>(@"^IDirectSound::DuplicateSoundBuffer::ppDSBufferDuplicate$", "void");
            group.TagVisibility<CppMethod>(@"^IDirectSound::CreateSoundBuffer$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^IDirectSound::DuplicateSoundBuffer$", Visibility.Internal);
            group.TagTypeAndName<CppParameter>(@"^IDirectSound::SetCooperativeLevel::dwLevel", "DSSCL_ENUM");
            group.TagName<CppMethod>(@"^IDirectSound.*::GetCaps$", "GetCapabilities");

            // IDirectSound8
            group.TagVisibility<CppMethod>(@"^IDirectSound8::VerifyCertification$", Visibility.Internal);
            // --------------------------------------------------------------------------------------------------------
            // DirectSound Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppFunction>(@"^DirectSound(.+)", "$1", false);
            CSharpFunctionGroup dsoundFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".DirectSound", Global.Name + ".DirectSound", "DSound");
            group.TagFunction("^DirectSound.*", "dsound.dll", dsoundFunctionGroup);
            group.TagFunction("^GetDeviceID.*", "dsound.dll", dsoundFunctionGroup);


            // Clear FindContext
            group.FindContext.Clear();
        }

    }
}
