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

namespace SlimDX2.Tools.XIDLToCSharp
{
    internal partial class Program
    {
        public void MapDXGI()
        {
            CSharpFunctionGroup dxgiFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".DXGI", Global.Name + ".DXGI", "DXGI");

            // General mapping between include and Assembly/Namespace
            gen.MapIncludeToNamespace("dxgi", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("dxgiformat", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("dxgitype", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("d3dcommon", Global.Name + ".Direct3D", Global.Name, "Direct3D");

            // --------------------------------------------------------------------------------------------------------
            // DXGI Enumerations
            // --------------------------------------------------------------------------------------------------------
            // ReCreate enums from macro definitions

            group.Modify<CppTypedef>(@"^DXGI_USAGE", Modifiers.Remove);

            group.CreateEnumFromMacros(@"^DXGI_PRESENT_.*", "DXGI_PRESENT_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_USAGE_.*", "DXGI_USAGE");
            group.CreateEnumFromMacros(@"^DXGI_RESOURCE_.*", "DXGI_RESOURCE_PRIORITY");
            group.CreateEnumFromMacros(@"^DXGI_MAP_.*", "DXGI_MAP_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_ENUM_MODES_.*", "DXGI_ENUM_MODES_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_MWA_.*", "DXGI_MWA_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_ERROR_.*", "DXGI_ERROR");
            group.CreateEnumFromMacros(@"^DXGI_STATUS_.*", "DXGI_STATUS");

            gen.KeepUnderscoreForType(@"^DXGI_FORMAT_.*");
            gen.RenameType(@"^DXGI_MODE_ROTATION$", "DisplayModeRotation");
            gen.RenameType(@"^DXGI_MODE_SCALING$", "DisplayModeScaling");
            gen.RenameType(@"^DXGI_MODE_SCANLINE_ORDER$", "DisplayModeScanlineOrder");

            gen.RenameType("^DXGI_ERROR$", "DXGIError", true, TypeContext.Root);
            gen.RenameType("^DXGI_STATUS$", "DXGIStatus", true, TypeContext.Root);


            gen.RenameType(@"^DXGI_ENUM_MODES_FLAGS$", "DisplayModeEnumerationFlags");
            gen.RenameType(@"^DXGI_MWA_FLAGS$", "WindowAssociationFlags");
            gen.RenameType(@"^DXGI_MWA_NO_WINDOW_CHANGES$", "IgnoreAll");
            gen.RenameType(@"^DXGI_MWA_NO_ALT_ENTER$", "IgnoreAltEnter");
            gen.RenameType(@"^DXGI_MWA_NO_PRINT_SCREEN$", "IgnorePrintScreen");

            // For DXGI Format
            gen.RenameTypePart(@"^(R(\d).*)", "$1");
            gen.RenameTypePart(@"^(B(\d).*)", "$1");
            gen.RenameTypePart(@"^(G(\d).*)", "$1");
            gen.RenameTypePart(@"^(A(\d).*)", "$1");
            gen.RenameTypePart(@"^(X(\d).*)", "$1");
            gen.RenameTypePart(@"^(BC(\d).*)", "$1");

            // --------------------------------------------------------------------------------------------------------
            // DXGI Structures
            // --------------------------------------------------------------------------------------------------------

            // Remove DXGI_DISPLAY_COLOR_SPACE type and all typedefs (never used)
            group.Modify<CppStruct>("DXGI_DISPLAY_COLOR_SPACE", Modifiers.Remove);

            // Update usage of enums
            group.TagTypeName<CppField>(@"^DXGI_SWAP_CHAIN_DESC::Flags", "DXGI_SWAP_CHAIN_FLAG");
            group.TagTypeName<CppField>(@"^DXGI_ADAPTER_DESC1::Flags", "DXGI_ADAPTER_FLAG");

            gen.MapCppTypeToCSharpType("DXGI_RGB", "SlimMath.Color3", 3 * 4, false, true);

            // --------------------------------------------------------------------------------------------------------
            // DXGI Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagTypeName<CppParameter>(@"^IDXGISwapChain::Present::Flags$", "DXGI_PRESENT_FLAGS");
            group.TagTypeName<CppParameter>(@"^IDXGIFactory::MakeWindowAssociation::Flags$", "DXGI_MWA_FLAGS");

            gen.RenameType(@"^IDXGIObject$", "DXGIObject", true);

            // --------------------------------------------------------------------------------------------------------
            // DXGI Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagFunction("^CreateDXGIFactory.*", "dxgi.dll", dxgiFunctionGroup);
            group.Modify<CppParameter>("^CreateDXGIFactory.*?::ppFactory$", Modifiers.ParameterAttribute(CppAttribute.Out));


            gen.RenameType(@"^IDXGI(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^DXGI(.+)", "$1", false, TypeContext.Root);
            gen.RenameTypePart("^DXGI", "");


        }
    }
}