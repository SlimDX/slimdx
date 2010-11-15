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
        public void MapDXGI()
        {
            // General mapping between include and Assembly/Namespace
            gen.MapIncludeToNamespace("dxgi", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("dxgiformat", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("dxgitype", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("d3dcommon", Global.Name + ".Direct3D", Global.Name, "Direct3D");

            // --------------------------------------------------------------------------------------------------------
            // DXGI Enumerations
            // --------------------------------------------------------------------------------------------------------
            // ReCreate enums from macro definitions

            group.Remove<CppTypedef>(@"^DXGI_USAGE$");

            group.CreateEnumFromMacros(@"^DXGI_PRESENT_.*", "DXGI_PRESENT_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_USAGE_.*", "DXGI_USAGE");
            group.CreateEnumFromMacros(@"^DXGI_RESOURCE_.*", "DXGI_RESOURCE_PRIORITY");
            group.CreateEnumFromMacros(@"^DXGI_MAP_.*", "DXGI_MAP_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_ENUM_MODES_.*", "DXGI_ENUM_MODES_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_MWA_.*", "DXGI_MWA_FLAGS");
            group.CreateEnumFromMacros(@"^DXGI_ERROR_.*", "DXGI_ERROR");
            group.CreateEnumFromMacros(@"^DXGI_STATUS_.*", "DXGI_STATUS");

            // Global rename
            group.TagName<CppEnum>(@"^DXGI(.+)", "$1", false);
            group.TagName<CppStruct>(@"^DXGI(.+)", "$1", false);

            // Special case, we need to keep underscore for DXGI_FORMAT
            gen.KeepUnderscoreForType(@"^DXGI_FORMAT_.*");
            group.TagName<CppEnum>(@"^DXGI_MODE_ROTATION$", "DisplayModeRotation");
            group.TagName<CppEnum>(@"^DXGI_MODE_SCALING$", "DisplayModeScaling");
            group.TagName<CppEnum>(@"^DXGI_MODE_SCANLINE_ORDER$", "DisplayModeScanlineOrder");

            group.TagName<CppEnum>("^DXGI_ERROR$", "DXGIError", true);
            group.TagName<CppEnum>("^DXGI_STATUS$", "DXGIStatus", true);

            group.TagName<CppEnum>(@"^DXGI_ENUM_MODES_FLAGS$", "DisplayModeEnumerationFlags");
            group.TagName<CppEnum>(@"^DXGI_MWA_FLAGS$", "WindowAssociationFlags");
            group.TagName<CppEnumItem>(@"^DXGI_MWA_NO_WINDOW_CHANGES$", "IgnoreAll");
            group.TagName<CppEnumItem>(@"^DXGI_MWA_NO_ALT_ENTER$", "IgnoreAltEnter");
            group.TagName<CppEnumItem>(@"^DXGI_MWA_NO_PRINT_SCREEN$", "IgnorePrintScreen");

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
            group.Remove<CppStruct>("DXGI_DISPLAY_COLOR_SPACE");

            // Update usage of enums
            group.TagTypeAndName<CppField>(@"^DXGI_SWAP_CHAIN_DESC::Flags", "DXGI_SWAP_CHAIN_FLAG");
            group.TagTypeAndName<CppField>(@"^DXGI_ADAPTER_DESC1::Flags", "DXGI_ADAPTER_FLAG");

            gen.MapCppTypeToCSharpType("DXGI_RGB", "SlimMath.Color3", 3 * 4, false, true);

            // --------------------------------------------------------------------------------------------------------
            // DXGI Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagTypeAndName<CppParameter>(@"^IDXGISwapChain::Present::Flags$", "DXGI_PRESENT_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^IDXGIFactory::MakeWindowAssociation::Flags$", "DXGI_MWA_FLAGS");

            group.TagName<CppInterface>(@"^IDXGI(.+)", "$1", false);
            group.TagName<CppInterface>(@"^IDXGIObject$", "DXGIObject");
            group.TagName<CppInterface>(@"^IDXGIObject$", "DXGIObject");

            // --------------------------------------------------------------------------------------------------------
            // DXGI Functions
            // --------------------------------------------------------------------------------------------------------
            CSharpFunctionGroup dxgiFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".DXGI", Global.Name + ".DXGI", "DXGI");
            group.TagFunction("^CreateDXGIFactory.*", "dxgi.dll", dxgiFunctionGroup);
            group.TagParameter("^CreateDXGIFactory.*?::ppFactory$", CppAttribute.Out);

            // gen.RenameTypePart("^DXGI", "");
        }
    }
}