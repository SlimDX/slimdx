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
using SlimDX2.Tools.XIDL;
using System.Linq;

namespace SlimDX.Generator
{
    internal partial class Program
    {
        public unsafe void MapXAPO()
        {
            gen.MapIncludeToNamespace("xapo", Global.Name + ".XAPO");
            gen.MapIncludeToNamespace("xapofx", Global.Name + ".XAPO.Fx", Global.Name + ".XAPO", "Fx");

            // Limit Find to "dsound" in this method (in order to be sure that we don't touch other includes)
            group.FindContext.Add("xapo");
            group.FindContext.Add("xapofx");

            // --------------------------------------------------------------------------------------------------------
            // XAPO Enumerations
            // --------------------------------------------------------------------------------------------------------
            //var enumItem = group.CreateEnumFromMacros(@"^XAUDIO2_VOICE_(USEFILTER)$", "XAUDIO2_VOICE_SEND_FLAGS", "XAUDIO2_VOICE_SEND_$1").Items.FirstOrDefault();
            //group.CreateEnumFromMacros(@"^XAUDIO2_VOICE_.*", "XAUDIO2_VOICE_FLAGS");
            //group.CreateEnumFromMacros(@"^XAUDIO2_DEBUG_ENGINE$", "XAUDIO2_FLAGS");
            //group.CreateEnumFromMacros(@"^XAUDIO2_PLAY_.*$", "XAUDIO2_PLAY_FLAGS");
            //group.CreateEnumFromMacros(@"^XAUDIO2_LOG_.*", "XAUDIO2_LOG_TYPE");
            //group.CreateEnumFromMacros(@"^XAUDIO2_END_OF_STREAM", "XAUDIO2_BUFFER_FLAGS");

            group.CreateEnumFromMacros(@"^XAPO_FLAG_(.*)", "XAPO_PROPERTY_TYPE", "XAPO_PROPERTY_$1");
            group.TagName<CppEnum>(@"^XAPO_(.*)", "$1", false);            
            group.TagName<CppEnum>(@"^XAPO_PROPERTY_TYPE$", "PropertyFlags");
            group.TagEnumFlags(@"^XAPO_PROPERTY_TYPE$");

            group.FindFirst<CppEnum>(@"^XAPO_PROPERTY_TYPE$").Add(new CppEnumItem() { Name = "Default", Value = "ChannelsMustMatch|FramerateMustMatch|BitspersampleMustMatch|BuffercountMustMatch|InplaceSupported"});
            group.TagName<CppEnumItem>(@"^XAPO_PROPERTY_(.*)", "$1", false);

            // --------------------------------------------------------------------------------------------------------
            // XAPO Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppStruct>(@"^XAPO_(.*)", "$1", false);
            group.TagName<CppStruct>(@"^FX(.*)","$1", false);

            group.TagName<CppStruct>(@"^FXEQ_PARAMETERS$", "EqualizerParameters", false);            

            group.TagName<CppStruct>(@"^XAPO_PROCESS_BUFFER_PARAMETERS$", "BufferParameters");
            group.TagName<CppStruct>(@"^XAPO_LOCKFORPROCESS_PARAMETERS$","LockParameters");
            group.TagStructToNative(@"^XAPO_LOCKFORPROCESS_PARAMETERS$", false, false, true);
            group.TagVisibility<CppField>(@"^XAPO_LOCKFORPROCESS_PARAMETERS::pFormat$", Visibility.Internal);
            group.TagName<CppField>(@"^XAPO_LOCKFORPROCESS_PARAMETERS::pFormat$", "FormatPointer");

            group.TagName<CppField>(@"^XAPO_PROCESS_BUFFER_PARAMETERS::pBuffer$", "Buffer");
                        
            group.TagName<CppStruct>(@"^FXMASTERINGLIMITER_PARAMETERS$", "MasteringLimiterParameters");

            gen.AddConstantFromMacroToCSharpType(@"^FXMASTERINGLIMITER_(.*)", Global.Name + ".XAPO.Fx.MasteringLimiterParameters", "int", "$1");


            group.TagTypeAndName<CppField>(@"^XAPO_REGISTRATION_PROPERTIES::Flags", "XAPO_PROPERTY_TYPE");


            // --------------------------------------------------------------------------------------------------------
            // XAPO Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^IXAPO(.*)", "$1");
            group.TagName<CppInterface>(@"^IXAPO$", "AudioProcessor");
            group.TagName<CppInterface>(@"^IXAPOParameters$", "ParameterProvider");
            group.TagCallback(@"^IXAPO$", true, Visibility.Abstract | Visibility.Public);
            group.TagCallback(@"^IXAPOParameters$", true, Visibility.Internal);
            group.TagVisibility<CppInterface>(@"^IXAPOParameters$", Visibility.Internal);

            group.TagParameter(@"^IXAPO::LockForProcess::pInputLockedParameters$", CppAttribute.In | CppAttribute.Buffer);
            group.TagParameter(@"^IXAPO::LockForProcess::pOutputLockedParameters$", CppAttribute.In | CppAttribute.Buffer);

            // Make pOutputProcessParameters void parameters
            //group.TagTypeAndName<CppParameter>(@"IXAPO::Process::pOutputProcessParameters$", "void");
            group.TagParameter(@"IXAPO::Process::pOutputProcessParameters$", CppAttribute.In|CppAttribute.Buffer);

            // --------------------------------------------------------------------------------------------------------
            // XAPO Functions
            // --------------------------------------------------------------------------------------------------------
            CSharpFunctionGroup xapoFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".XAPO", Global.Name + ".XAPO.Fx", "XAPOFx");
            group.TagFunction("^CreateFX$", "XAPOFX1_5.dll", xapoFunctionGroup);

            // Add FX Guid
            var guidList = group.Find<CppGuid>(@".*FX.*");
            foreach (var cppGuid in guidList)
                gen.AddConstantToCSharpType(Global.Name + ".XAPO.Fx.XAPOFx", "System.Guid", cppGuid.Name, "new System.Guid(\"" + cppGuid.Guid + "\")").
                    Visibility = Visibility.Internal | Visibility.Static;

            // Clear FindContext
            group.FindContext.Clear();
        }

    }
}
