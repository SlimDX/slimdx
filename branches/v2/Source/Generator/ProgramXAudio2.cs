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
using System.Linq;

namespace SlimDX.Generator
{
    internal partial class Program
    {
        /// <summary>
        /// Map XAudio2 API
        /// </summary>
        public void MapXAudio2()
        {
            // Global namespace for XAudio2
            string assemblyName = Global.Name + ".XAudio2";
            string namespaceName = assemblyName;
            string namespaceNameFx = assemblyName + ".Fx";

            gen.MapIncludeToNamespace("xaudio2", assemblyName, namespaceName);
            gen.MapIncludeToNamespace("xaudio2fx", assemblyName, namespaceNameFx, "Fx");

            // Limit Find to "dsound" in this method (in order to be sure that we don't touch other includes)
            group.FindContext.Add("xaudio2");
            group.FindContext.Add("xaudio2fx");

            // --------------------------------------------------------------------------------------------------------
            // XAudio2 Enumerations
            // --------------------------------------------------------------------------------------------------------
            var enumItem = group.CreateEnumFromMacros(@"^XAUDIO2_VOICE_(USEFILTER)$", "XAUDIO2_VOICE_SEND_FLAGS","XAUDIO2_VOICE_SEND_$1").Items.FirstOrDefault();
            group.CreateEnumFromMacros(@"^XAUDIO2_VOICE_.*", "XAUDIO2_VOICE_FLAGS");
            group.CreateEnumFromMacros(@"^XAUDIO2_DEBUG_ENGINE$", "XAUDIO2_FLAGS");
            group.CreateEnumFromMacros(@"^XAUDIO2_PLAY_.*$", "XAUDIO2_PLAY_FLAGS");
            group.CreateEnumFromMacros(@"^XAUDIO2_LOG_.*", "XAUDIO2_LOG_TYPE");
            group.CreateEnumFromMacros(@"^XAUDIO2_END_OF_STREAM", "XAUDIO2_BUFFER_FLAGS");

            group.TagName<CppEnumItem>(@"^XAUDIO2_ANY_PROCESSOR$","AnyProcessor");
            group.TagName<CppEnumItem>(@"^XAUDIO2_DEFAULT_PROCESSOR$", "DefaultProcessor");

            // --------------------------------------------------------------------------------------------------------
            // XAudio2 Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppEnum>(@"^XAUDIO2_(.*)", "$1", false);
            group.TagName<CppEnum>(@"^XAUDIO2_FLAGS$", "XAudio2Flags");
            group.TagName<CppStruct>(@"^XAUDIO2FX_(.*)", "$1", false);
            group.TagName<CppStruct>(@"^XAUDIO2_(.*)", "$1", false);



            group.TagEnumFlags(@"^XAUDIO2_LOG_TYPE$");

            group.TagVisibility<CppStruct>(@"^XAUDIO2_EFFECT_CHAIN$", Visibility.Internal);

            group.TagName<CppStruct>(@"^XAUDIO2_BUFFER$", "AudioBuffer");
            group.TagTypeAndName<CppField>(@"^XAUDIO2_BUFFER::Flags$", "XAUDIO2_BUFFER_FLAGS");
            group.TagName<CppField>(@"^XAUDIO2_BUFFER::pContext$", "Context");
            group.TagStructToNative(@"^XAUDIO2_BUFFER$", true);
            group.TagName<CppField>(@"^XAUDIO2_BUFFER::pAudioData$", "AudioDataPointer");
            group.TagVisibility<CppField>(@"^XAUDIO2_BUFFER::pAudioData$", Visibility.Internal);
            //group.TagVisibility<CppField>(@"^XAUDIO2_BUFFER::AudioBytes$", Visibility.Internal);

            group.TagName<CppStruct>(@"^XAUDIO2_SEND_DESCRIPTOR$", "VoiceSendDescriptor");
            group.TagTypeAndName<CppField>(@"^XAUDIO2_SEND_DESCRIPTOR::Flags$", "XAUDIO2_VOICE_SEND_FLAGS");
            group.TagName<CppField>(@"^XAUDIO2_SEND_DESCRIPTOR::pOutputVoice$", "OutputVoicePointer");
            group.TagVisibility<CppField>(@"^XAUDIO2_SEND_DESCRIPTOR::pOutputVoice$", Visibility.Internal);

            group.TagVisibility<CppStruct>(@"^XAUDIO2_VOICE_SENDS$", Visibility.Internal);
            group.TagName<CppStruct>(@"^XAUDIO2_VOICE_SENDS$", "VoiceSendDescriptors");            

            group.TagName<CppField>(@"^XAUDIO2_VOICE_SENDS::pSends$", "SendPointer");
            group.TagVisibility<CppField>(@"^XAUDIO2_VOICE_SENDS::pSends$", Visibility.Internal);
            group.TagName<CppField>(@"^XAUDIO2_EFFECT_CHAIN::pEffectDescriptors$", "EffectDescriptorPointer");
            group.TagVisibility<CppField>(@"^XAUDIO2_EFFECT_CHAIN::pEffectDescriptors$", Visibility.Internal);


            group.TagName<CppField>(@"^XAUDIO2_BUFFER_WMA::pDecodedPacketCumulativeBytes$", "DecodedPacketCumulativeBytesPointer");

            group.TagName<CppField>(@"^XAUDIO2_VOICE_STATE::pCurrentBufferContext$", "Context");           

            group.TagName<CppField>(@"^XAUDIO2_VOICE_DETAILS::InputChannels$", "InputChanneCount");
            group.TagName<CppField>(@"^XAUDIO2_EFFECT_DESCRIPTOR::OutputChannels$", "OutputChannelCount");
            group.TagName<CppField>(@"^XAUDIO2_EFFECT_DESCRIPTOR::pEffect$", "EffectPointer");
            group.TagVisibility<CppField>(@"^XAUDIO2_EFFECT_DESCRIPTOR::pEffect$", Visibility.Internal);

            group.TagName<CppField>(@"^XAUDIO2FX_VOLUMEMETER_LEVELS::pPeakLevels$", "PeakLevelPointer");
            group.TagVisibility<CppField>(@"^XAUDIO2FX_VOLUMEMETER_LEVELS::pPeakLevels$", Visibility.Internal);

            group.TagName<CppField>(@"^XAUDIO2FX_VOLUMEMETER_LEVELS::pRMSLevels$", "RmsLevelsPointer");
            group.TagVisibility<CppField>(@"^XAUDIO2FX_VOLUMEMETER_LEVELS::pRMSLevels$", Visibility.Internal);

            group.TagStructToNative(@"^XAUDIO2_EFFECT_DESCRIPTOR$",true, forceMarshalToToBeGenerated: true);

            gen.AddConstantFromMacroToCSharpType(@"^XAUDIO2_LOOP_INFINITE$", Global.Name + ".XAudio2.AudioBuffer", "int", "LoopInfinite");

            
            // --------------------------------------------------------------------------------------------------------
            // XAudio2 Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^IXAudio2(.+)", "$1", false);
            group.TagName<CppInterface>(@"^IXAudio2$", "XAudio2");

            group.TagVisibility<CppMethod>(@"^IXAudio2::Initialize$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^IXAudio2::GetDeviceDetails$", Visibility.Internal);

            group.TagVisibility<CppInterface>(@"^IXAudio2EngineCallback$", Visibility.Internal);

            group.TagVisibility<CppMethod>(@"^IXAudio2Voice::SetOutputVoices$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^IXAudio2Voice::GetEffectParameters$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^IXAudio2Voice::SetEffectParameters$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^IXAudio2Voice::GetEffectState$", Visibility.Internal);

            group.TagVisibility<CppMethod>(@"^IXAudio2SourceVoice::Start$", Visibility.Internal);

            group.TagCallback(@"^IXAudio2.*Callback$");

            // --------------------------------------------------------------------------------------------------------
            // XAudio2 Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagVisibility<CppMethod>(@"^IXAudio2::Create.*", Visibility.Internal);
            group.TagTypeAndName<CppParameter>(@"^IXAudio2::CreateSourceVoice::Flags$", "XAUDIO2_VOICE_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^IXAudio2::CreateSubmixVoice::Flags$", "XAUDIO2_VOICE_SEND_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^IXAudio2SourceVoice::Stop::Flags$", "XAUDIO2_PLAY_FLAGS");
            group.TagVisibility<CppMethod>(@"^IXAudio2Voice::SetEffectChain$", Visibility.Internal, true);

            // Add Fx contants
            CSharpFunctionGroup xaudio2ContantGroup = gen.CreateFunctionGroup(assemblyName, namespaceNameFx, "XAudio2FxContants");
            var guidList = group.Find<CppGuid>(@"CLSID_Audio.*");
            foreach (var cppGuid in guidList)
                gen.AddConstantToCSharpType(Global.Name + ".XAudio2.Fx.XAudio2FxContants", "System.Guid", cppGuid.Name, "new System.Guid(\"" + cppGuid.Guid + "\")").
                    Visibility = Visibility.Internal | Visibility.Static;

            // Add Guid to 
            guidList = group.Find<CppGuid>(@".*XAudio2.*");
            foreach (var cppGuid in guidList)
                gen.AddConstantToCSharpType(Global.Name + ".XAudio2.XAudio2", "System.Guid", cppGuid.Name, "new System.Guid(\"" + cppGuid.Guid + "\")").
                    Visibility = Visibility.Internal | Visibility.Static;

            // Clear FindContext
            group.FindContext.Clear();
        }

    }
}
