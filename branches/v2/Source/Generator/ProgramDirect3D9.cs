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

namespace SlimDX.Generator
{
    internal partial class Program
    {

        public unsafe void MapDirect3D9()
        {
            CSharpFunctionGroup d3d9FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D9", Global.Name + ".Direct3D9", "D3D9");
            CSharpFunctionGroup d3dx9FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D9", Global.Name + ".Direct3D9", "D3DX9");


            string[] includes = new string[]
                                    {
                                        "d3d9",
                                        "d3d9caps",
                                        "d3d9types",
                                        "d3dx9",
                                        "d3dx9anim",
                                        "d3dx9core",
                                        "d3dx9effect",
                                        "d3dx9mesh",
                                        "d3dx9shader",
                                        "d3dx9shape",
                                        "d3dx9tex",
                                        "d3dx9xof",
                                    };
            foreach (var include in includes)
                gen.MapIncludeToNamespace(include, Global.Name + ".Direct3D9");

            // Force all grou.Find/Modify request to limit their search to the Direct3D9 includes
            group.FindContext.AddRange(includes);

            // Remove Video & AuthenticatedChannel. Not part of SlimDX, Is it still used?
            group.Remove<CppElement>(@"^_?D3DAUTHENTICATEDCHANNEL.*");
            group.Remove<CppInterface>(@"^IDirect3DDevice9Video$");
            group.Remove<CppInterface>(@"^IDirect3DAuthenticatedChannel9$");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Enumerations
            // --------------------------------------------------------------------------------------------------------
            // Create Create Flags from Macros D3DCREATE_.*
            group.CreateEnumFromMacros(@"^D3DCREATE_.*", "D3DCREATE_FLAGS");
            group.CreateEnumFromMacros(@"^D3DPRESENT_INTERVAL_.*", "D3DPRESENT_INTERVAL");
            group.CreateEnumFromMacros(@"^D3DPRESENT_[^I][^N].*", "D3DPRESENT");
            group.CreateEnumFromMacros(@"^D3DPRESENTFLAG.*", "D3DPRESENT_FLAGS");
            group.CreateEnumFromMacros(@"^D3DCLEAR_.*", "D3DCLEAR_FLAGS");
            group.CreateEnumFromMacros(@"^D3DLOCK_.*", "D3DLOCK").Add(new CppEnumItem() { Name = "D3DLOCK_NONE", Value = "0" });
            var d3dFVF = group.CreateEnumFromMacros(@"^D3DFVF_.*", "D3DFVF");
            d3dFVF.Add(new CppEnumItem() { Name = "D3DFVF_NONE", Value = "0" });
            d3dFVF.Remove<CppEnumItem>(@"^D3DFVF_TEXTUREFORMAT.*");
            d3dFVF.Remove<CppEnumItem>(@"^D3DFVF_RESERVED2$");
            group.CreateEnumFromMacros(@"^D3DUSAGE_.*", "D3DUSAGE");

            group.Remove<CppEnum>(@"^_MAX_FVF_DECL_SIZE$");
            group.Remove<CppEnum>(@"^_D3DXERR$");
            group.Remove<CppEnum>(@"^_D3DXPATCHMESH$");
            group.Remove<CppEnum>(@"^D3DXIMT$");
            group.Remove<CppEnum>(@"^D3DXUVATLAS$");
            group.Remove<CppEnum>(@"^D3DXIMT$");
            group.Remove<CppEnum>(@"^D3DXIMT$");
            group.Remove<CppEnum>(@"^D3DXIMT$");
            group.Remove<CppEnum>(@"^D3DXIMT$");
            group.Remove<CppEnum>(@"^D3DXSHGPUSIMOPT$");
            group.Remove<CppEnum>(@"^D3DSHADER_COMPARISON$");
            group.Remove<CppEnum>(@"^D3DSHADER_INSTRUCTION_OPCODE_TYPE$");
            group.Remove<CppEnum>(@"^D3DSHADER_PARAM_REGISTER_TYPE$");
            group.Remove<CppEnum>(@"^D3DVS_RASTOUT_OFFSETS$");
            group.Remove<CppEnum>(@"^D3DVS_ADDRESSMODE_TYPE$");
            group.Remove<CppEnum>(@"^D3DSHADER_ADDRESSMODE_TYPE$");
            group.Remove<CppEnum>(@"^D3DSHADER_PARAM_SRCMOD_TYPE$");
            group.Remove<CppEnum>(@"^D3DXSHCOMPRESSQUALITYTYPE$");

            group.TagName<CppEnum>(@"^D3DLOCK$", "LockFlags");
            group.TagEnumFlags(@"^D3DLOCK$");
            group.TagName<CppEnum>(@"^D3DUSAGE$", "Usage");
            group.TagName<CppEnum>(@"^D3DFVF$", "VertexFormat");
            group.TagEnumFlags(@"^D3DFVF$");
            group.TagName<CppEnum>(@"^D3DPRESENT_INTERVAL$", "PresentInterval");
            group.TagName<CppEnum>(@"^D3DPRESENT$", "Present");
            group.TagEnumFlags(@"^D3DPRESENT$");
            group.TagName<CppEnum>(@"^D3DPRESENT_FLAGS$", "PresentFlags");
            group.TagName<CppEnum>(@"^D3DCREATE_FLAGS$", "CreateFlags");
            group.TagName<CppEnum>(@"^D3DCLEAR_FLAGS$", "ClearFlags");
            group.TagName<CppEnum>(@"^_D3DXMESHSIMP$", "MeshSimplification");
            group.TagName<CppEnum>(@"^_D3DXMESH$", "MeshFlags");
            group.TagEnumFlags(@"^_D3DXMESH$");
            group.TagName<CppEnum>(@"^D3DXMESHOPT$", "MeshOptimizeFlags");
            group.TagName<CppEnum>(@"^_D3DXWELDEPSILONSFLAGS$", "WeldFlags");
            group.TagName<CppEnum>(@"^D3DBASISTYPE$", "Basis");
            group.TagName<CppEnum>(@"^D3DBLENDOP$", "BlendOperation");
            group.TagName<CppEnum>(@"^D3DCMPFUNC$", "Compare");
            group.TagName<CppEnum>(@"^D3DCOMPOSERECTSOP$", "ComposeRectOperation");
            group.TagName<CppEnum>(@"^D3DCUBEMAP_FACES$", "CubeMapFace");
            group.TagName<CppEnum>(@"^D3DDEBUGMONITORTOKENS$", "DebugMonitorTokens");
            group.TagTypeAndName<CppEnum>(@"^D3DDECLMETHOD$", "byte", "DeclarationMethod");
            group.TagTypeAndName<CppEnum>(@"^D3DDECLTYPE$", "byte", "DeclarationType");
            group.TagTypeAndName<CppEnum>(@"^D3DDECLUSAGE$", "byte", "DeclarationUsage");
            group.TagName<CppEnum>(@"^D3DDEGREETYPE$", "Degree");
            group.TagName<CppEnum>(@"^D3DDEVTYPE$", "DeviceType");
            group.TagName<CppEnum>(@"^D3DDISPLAYROTATION$", "DisplayRotation");
            group.TagName<CppEnum>(@"^D3DFILLMODE$", "FillMode");
            group.TagName<CppEnum>(@"^D3DFOGMODE$", "FogMode");
            group.TagName<CppEnum>(@"^D3DLIGHTTYPE$", "LightType");
            group.TagName<CppEnum>(@"^D3DMATERIALCOLORSOURCE$", "ColorSource");
            group.TagName<CppEnum>(@"^D3DPATCHEDGESTYLE$", "PatchEdgeStyle");
            group.TagName<CppEnum>(@"^D3DPRIMITIVETYPE$", "PrimitiveType");
            group.TagName<CppEnum>(@"^D3DQUERYTYPE$", "QueryType");
            group.TagName<CppEnum>(@"^D3DRENDERSTATETYPE$", "RenderState");
            group.TagName<CppEnum>(@"^D3DRESOURCETYPE$", "ResourceType");
            group.TagName<CppEnum>(@"^D3DSAMPLERSTATETYPE$", "SamplerState");
            group.TagName<CppEnum>(@"^D3DSCANLINEORDERING$", "ScanlineOrdering");
            group.TagName<CppEnum>(@"^D3DSHADEMODE$", "ShadeMode");
            group.TagName<CppEnum>(@"^D3DSTATEBLOCKTYPE$", "StateBlockType");
            group.TagName<CppEnum>(@"^D3DSWAPEFFECT$", "SwapEffect");
            group.TagName<CppEnum>(@"^D3DTEXTUREADDRESS$", "TextureAddress");
            group.TagName<CppEnum>(@"^D3DTEXTUREFILTERTYPE$", "TextureFilter");
            group.TagName<CppEnum>(@"^D3DTEXTUREOP$", "TextureOperation");
            group.TagName<CppEnum>(@"^D3DTEXTURESTAGESTATETYPE$", "TextureStage");
            group.TagName<CppEnum>(@"^D3DTEXTURETRANSFORMFLAGS$", "TextureTransform");
            group.TagName<CppEnum>(@"^D3DTRANSFORMSTATETYPE$", "TransformState");
            group.TagName<CppEnum>(@"^D3DVERTEXBLENDFLAGS$", "VertexBlend");
            group.TagName<CppEnum>(@"^D3DXCLEANTYPE$", "CleanType");
            group.TagName<CppEnum>(@"^D3DXEFFECTDEFAULTTYPE$", "EffectDefaultType");
            group.TagName<CppEnum>(@"^D3DXIMAGE_FILEFORMAT$", "ImageFileFormat");
            group.TagName<CppEnum>(@"^D3DXMESHDATATYPE$", "MeshDataType");
            group.TagName<CppEnum>(@"^D3DXPATCHMESHTYPE$", "PatchMeshType");
            group.TagName<CppEnum>(@"^D3DXPRIORITY_TYPE$", "TrackPriority");
            group.TagName<CppEnum>(@"^D3DXTANGENT$", "TangentOptions");
            group.TagName<CppEnum>(@"^D3DZBUFFERTYPE$", "ZBufferType");

            group.TagName<CppEnumItem>(@"^D3DLIGHT_POINT$", "Point");
            group.TagName<CppEnumItem>(@"^D3DLIGHT_SPOT$", "Spot");
            group.TagName<CppEnumItem>(@"^D3DLIGHT_DIRECTIONAL$", "Directional");
            group.TagName<CppEnumItem>(@"^D3DSHADE_FLAT$", "Flat");
            group.TagName<CppEnumItem>(@"^D3DSHADE_GOURAUD$", "Gouraud");
            group.TagName<CppEnumItem>(@"^D3DSHADE_PHONG$", "Phong");
            group.TagName<CppEnumItem>(@"^D3DFILL_POINT$", "Point");
            group.TagName<CppEnumItem>(@"^D3DFILL_WIREFRAME$", "Wireframe");
            group.TagName<CppEnumItem>(@"^D3DFILL_SOLID$", "Solid");
            group.TagName<CppEnumItem>(@"^D3DBLEND_ZERO$", "Zero");
            group.TagName<CppEnumItem>(@"^D3DBLEND_ONE$", "One");
            group.TagName<CppEnumItem>(@"^D3DBLEND_SRCCOLOR$", "SourceColor");
            group.TagName<CppEnumItem>(@"^D3DBLEND_INVSRCCOLOR$", "InverseSourceColor");
            group.TagName<CppEnumItem>(@"^D3DBLEND_SRCALPHA$", "SourceAlpha");
            group.TagName<CppEnumItem>(@"^D3DBLEND_INVSRCALPHA$", "InverseSourceAlpha");
            group.TagName<CppEnumItem>(@"^D3DBLEND_DESTALPHA$", "DestinationAlpha");
            group.TagName<CppEnumItem>(@"^D3DBLEND_INVDESTALPHA$", "InverseDestinationAlpha");
            group.TagName<CppEnumItem>(@"^D3DBLEND_DESTCOLOR$", "DestinationColor");
            group.TagName<CppEnumItem>(@"^D3DBLEND_INVDESTCOLOR$", "InverseDestinationColor");
            group.TagName<CppEnumItem>(@"^D3DBLEND_SRCALPHASAT$", "SourceAlphaSaturated");
            group.TagName<CppEnumItem>(@"^D3DBLEND_BOTHSRCALPHA$", "BothSourceAlpha");
            group.TagName<CppEnumItem>(@"^D3DBLEND_BOTHINVSRCALPHA$", "BothInverseSourceAlpha");
            group.TagName<CppEnumItem>(@"^D3DBLEND_BLENDFACTOR$", "BlendFactor");
            group.TagName<CppEnumItem>(@"^D3DBLEND_INVBLENDFACTOR$", "InverseBlendFactor");
            group.TagName<CppEnumItem>(@"^D3DBLEND_SRCCOLOR2$", "SourceColor2");
            group.TagName<CppEnumItem>(@"^D3DBLEND_INVSRCCOLOR2$", "InverseSourceColor2");
            group.TagName<CppEnumItem>(@"^D3DBLENDOP_ADD$", "Add");
            group.TagName<CppEnumItem>(@"^D3DBLENDOP_SUBTRACT$", "Subtract");
            group.TagName<CppEnumItem>(@"^D3DBLENDOP_REVSUBTRACT$", "ReverseSubtract");
            group.TagName<CppEnumItem>(@"^D3DBLENDOP_MIN$", "Minimum");
            group.TagName<CppEnumItem>(@"^D3DBLENDOP_MAX$", "Maximum");
            group.TagName<CppEnumItem>(@"^D3DTADDRESS_WRAP$", "Wrap");
            group.TagName<CppEnumItem>(@"^D3DTADDRESS_MIRROR$", "Mirror");
            group.TagName<CppEnumItem>(@"^D3DTADDRESS_CLAMP$", "Clamp");
            group.TagName<CppEnumItem>(@"^D3DTADDRESS_BORDER$", "Border");
            group.TagName<CppEnumItem>(@"^D3DTADDRESS_MIRRORONCE$", "MirrorOnce");
            group.TagName<CppEnumItem>(@"^D3DCULL_NONE$", "None");
            group.TagName<CppEnumItem>(@"^D3DCULL_CW$", "Clockwise");
            group.TagName<CppEnumItem>(@"^D3DCULL_CCW$", "Counterclockwise");
            group.TagName<CppEnumItem>(@"^D3DCMP_NEVER$", "Never");
            group.TagName<CppEnumItem>(@"^D3DCMP_LESS$", "Less");
            group.TagName<CppEnumItem>(@"^D3DCMP_EQUAL$", "Equal");
            group.TagName<CppEnumItem>(@"^D3DCMP_LESSEQUAL$", "LessEqual");
            group.TagName<CppEnumItem>(@"^D3DCMP_GREATER$", "Greater");
            group.TagName<CppEnumItem>(@"^D3DCMP_NOTEQUAL$", "NotEqual");
            group.TagName<CppEnumItem>(@"^D3DCMP_GREATEREQUAL$", "GreaterEqual");
            group.TagName<CppEnumItem>(@"^D3DCMP_ALWAYS$", "Always");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_KEEP$", "Keep");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_ZERO$", "Zero");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_REPLACE$", "Replace");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_INCRSAT$", "IncrementSaturate");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_DECRSAT$", "DecrementSaturate");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_INVERT$", "Invert");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_INCR$", "Increment");
            group.TagName<CppEnumItem>(@"^D3DSTENCILOP_DECR$", "Decrement");
            group.TagName<CppEnumItem>(@"^D3DFOG_NONE$", "None");
            group.TagName<CppEnumItem>(@"^D3DFOG_EXP$", "Exponential");
            group.TagName<CppEnumItem>(@"^D3DFOG_EXP2$", "ExponentialSquared");
            group.TagName<CppEnumItem>(@"^D3DFOG_LINEAR$", "Linear");
            group.TagName<CppEnumItem>(@"^D3DZB_FALSE$", "DontUseZBuffer");
            group.TagName<CppEnumItem>(@"^D3DZB_TRUE$", "UseZBuffer");
            group.TagName<CppEnumItem>(@"^D3DZB_USEW$", "UseWBuffer");
            group.TagName<CppEnumItem>(@"^D3DPT_POINTLIST$", "PointList");
            group.TagName<CppEnumItem>(@"^D3DPT_LINELIST$", "LineList");
            group.TagName<CppEnumItem>(@"^D3DPT_LINESTRIP$", "LineStrip");
            group.TagName<CppEnumItem>(@"^D3DPT_TRIANGLELIST$", "TriangleList");
            group.TagName<CppEnumItem>(@"^D3DPT_TRIANGLESTRIP$", "TriangleStrip");
            group.TagName<CppEnumItem>(@"^D3DPT_TRIANGLEFAN$", "TriangleFan");
            group.TagName<CppEnumItem>(@"^D3DTS_VIEW$", "View");
            group.TagName<CppEnumItem>(@"^D3DTS_PROJECTION$", "Projection");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE0$", "Texture0");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE1$", "Texture1");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE2$", "Texture2");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE3$", "Texture3");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE4$", "Texture4");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE5$", "Texture5");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE6$", "Texture6");
            group.TagName<CppEnumItem>(@"^D3DTS_TEXTURE7$", "Texture7");
            group.TagName<CppEnumItem>(@"^D3DRS_ZENABLE$", "ZEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_FILLMODE$", "FillMode");
            group.TagName<CppEnumItem>(@"^D3DRS_SHADEMODE$", "ShadeMode");
            group.TagName<CppEnumItem>(@"^D3DRS_ZWRITEENABLE$", "ZWriteEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_ALPHATESTENABLE$", "AlphaTestEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_LASTPIXEL$", "LastPixel");
            group.TagName<CppEnumItem>(@"^D3DRS_SRCBLEND$", "SourceBlend");
            group.TagName<CppEnumItem>(@"^D3DRS_DESTBLEND$", "DestinationBlend");
            group.TagName<CppEnumItem>(@"^D3DRS_CULLMODE$", "CullMode");
            group.TagName<CppEnumItem>(@"^D3DRS_ZFUNC$", "ZFunc");
            group.TagName<CppEnumItem>(@"^D3DRS_ALPHAREF$", "AlphaRef");
            group.TagName<CppEnumItem>(@"^D3DRS_ALPHAFUNC$", "AlphaFunc");
            group.TagName<CppEnumItem>(@"^D3DRS_DITHERENABLE$", "DitherEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_ALPHABLENDENABLE$", "AlphaBlendEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_FOGENABLE$", "FogEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_SPECULARENABLE$", "SpecularEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_FOGCOLOR$", "FogColor");
            group.TagName<CppEnumItem>(@"^D3DRS_FOGTABLEMODE$", "FogTableMode");
            group.TagName<CppEnumItem>(@"^D3DRS_FOGSTART$", "FogStart");
            group.TagName<CppEnumItem>(@"^D3DRS_FOGEND$", "FogEnd");
            group.TagName<CppEnumItem>(@"^D3DRS_FOGDENSITY$", "FogDensity");
            group.TagName<CppEnumItem>(@"^D3DRS_RANGEFOGENABLE$", "RangeFogEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILENABLE$", "StencilEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILFAIL$", "StencilFail");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILZFAIL$", "StencilZFail");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILPASS$", "StencilPass");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILFUNC$", "StencilFunc");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILREF$", "StencilRef");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILMASK$", "StencilMask");
            group.TagName<CppEnumItem>(@"^D3DRS_STENCILWRITEMASK$", "StencilWriteMask");
            group.TagName<CppEnumItem>(@"^D3DRS_TEXTUREFACTOR$", "TextureFactor");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP0$", "Wrap0");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP1$", "Wrap1");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP2$", "Wrap2");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP3$", "Wrap3");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP4$", "Wrap4");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP5$", "Wrap5");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP6$", "Wrap6");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP7$", "Wrap7");
            group.TagName<CppEnumItem>(@"^D3DRS_CLIPPING$", "Clipping");
            group.TagName<CppEnumItem>(@"^D3DRS_LIGHTING$", "Lighting");
            group.TagName<CppEnumItem>(@"^D3DRS_AMBIENT$", "Ambient");
            group.TagName<CppEnumItem>(@"^D3DRS_FOGVERTEXMODE$", "FogVertexMode");
            group.TagName<CppEnumItem>(@"^D3DRS_COLORVERTEX$", "ColorVertex");
            group.TagName<CppEnumItem>(@"^D3DRS_LOCALVIEWER$", "LocalViewer");
            group.TagName<CppEnumItem>(@"^D3DRS_NORMALIZENORMALS$", "NormalizeNormals");
            group.TagName<CppEnumItem>(@"^D3DRS_DIFFUSEMATERIALSOURCE$", "DiffuseMaterialSource");
            group.TagName<CppEnumItem>(@"^D3DRS_SPECULARMATERIALSOURCE$", "SpecularMaterialSource");
            group.TagName<CppEnumItem>(@"^D3DRS_AMBIENTMATERIALSOURCE$", "AmbientMaterialSource");
            group.TagName<CppEnumItem>(@"^D3DRS_EMISSIVEMATERIALSOURCE$", "EmissiveMaterialSource");
            group.TagName<CppEnumItem>(@"^D3DRS_VERTEXBLEND$", "VertexBlend");
            group.TagName<CppEnumItem>(@"^D3DRS_CLIPPLANEENABLE$", "ClipPlaneEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSIZE$", "PointSize");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSIZE_MIN$", "PointSizeMin");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSPRITEENABLE$", "PointSpriteEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSCALEENABLE$", "PointScaleEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSCALE_A$", "PointScaleA");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSCALE_B$", "PointScaleB");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSCALE_C$", "PointScaleC");
            group.TagName<CppEnumItem>(@"^D3DRS_MULTISAMPLEANTIALIAS$", "MultisampleAntialias");
            group.TagName<CppEnumItem>(@"^D3DRS_MULTISAMPLEMASK$", "MultisampleMask");
            group.TagName<CppEnumItem>(@"^D3DRS_PATCHEDGESTYLE$", "PatchEdgeStyle");
            group.TagName<CppEnumItem>(@"^D3DRS_DEBUGMONITORTOKEN$", "DebugMonitorToken");
            group.TagName<CppEnumItem>(@"^D3DRS_POINTSIZE_MAX$", "PointSizeMax");
            group.TagName<CppEnumItem>(@"^D3DRS_INDEXEDVERTEXBLENDENABLE$", "IndexedVertexBlendEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_COLORWRITEENABLE$", "ColorWriteEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_TWEENFACTOR$", "TweenFactor");
            group.TagName<CppEnumItem>(@"^D3DRS_BLENDOP$", "BlendOperation");
            group.TagName<CppEnumItem>(@"^D3DRS_POSITIONDEGREE$", "PositionDegree");
            group.TagName<CppEnumItem>(@"^D3DRS_NORMALDEGREE$", "NormalDegree");
            group.TagName<CppEnumItem>(@"^D3DRS_SCISSORTESTENABLE$", "ScissorTestEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_SLOPESCALEDEPTHBIAS$", "SlopeScaleDepthBias");
            group.TagName<CppEnumItem>(@"^D3DRS_ANTIALIASEDLINEENABLE$", "AntialiasedLineEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_MINTESSELLATIONLEVEL$", "MinTessellationLevel");
            group.TagName<CppEnumItem>(@"^D3DRS_MAXTESSELLATIONLEVEL$", "MaxTessellationLevel");
            group.TagName<CppEnumItem>(@"^D3DRS_ADAPTIVETESS_X$", "AdaptiveTessX");
            group.TagName<CppEnumItem>(@"^D3DRS_ADAPTIVETESS_Y$", "AdaptiveTessY");
            group.TagName<CppEnumItem>(@"^D3DRS_ADAPTIVETESS_Z$", "AdaptiveTessZ");
            group.TagName<CppEnumItem>(@"^D3DRS_ADAPTIVETESS_W$", "AdaptiveTessW");
            group.TagName<CppEnumItem>(@"^D3DRS_ENABLEADAPTIVETESSELLATION$", "EnableAdaptiveTessellation");
            group.TagName<CppEnumItem>(@"^D3DRS_TWOSIDEDSTENCILMODE$", "TwoSidedStencilMode");
            group.TagName<CppEnumItem>(@"^D3DRS_CCW_STENCILFAIL$", "CcwStencilFail");
            group.TagName<CppEnumItem>(@"^D3DRS_CCW_STENCILZFAIL$", "CcwStencilZFail");
            group.TagName<CppEnumItem>(@"^D3DRS_CCW_STENCILPASS$", "CcwStencilPass");
            group.TagName<CppEnumItem>(@"^D3DRS_CCW_STENCILFUNC$", "CcwStencilFunc");
            group.TagName<CppEnumItem>(@"^D3DRS_COLORWRITEENABLE1$", "ColorWriteEnable1");
            group.TagName<CppEnumItem>(@"^D3DRS_COLORWRITEENABLE2$", "ColorWriteEnable2");
            group.TagName<CppEnumItem>(@"^D3DRS_COLORWRITEENABLE3$", "ColorWriteEnable3");
            group.TagName<CppEnumItem>(@"^D3DRS_BLENDFACTOR$", "BlendFactor");
            group.TagName<CppEnumItem>(@"^D3DRS_SRGBWRITEENABLE$", "SrgbWriteEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_DEPTHBIAS$", "DepthBias");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP8$", "Wrap8");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP9$", "Wrap9");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP10$", "Wrap10");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP11$", "Wrap11");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP12$", "Wrap12");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP13$", "Wrap13");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP14$", "Wrap14");
            group.TagName<CppEnumItem>(@"^D3DRS_WRAP15$", "Wrap15");
            group.TagName<CppEnumItem>(@"^D3DRS_SEPARATEALPHABLENDENABLE$", "SeparateAlphaBlendEnable");
            group.TagName<CppEnumItem>(@"^D3DRS_SRCBLENDALPHA$", "SourceBlendAlpha");
            group.TagName<CppEnumItem>(@"^D3DRS_DESTBLENDALPHA$", "DestinationBlendAlpha");
            group.TagName<CppEnumItem>(@"^D3DRS_BLENDOPALPHA$", "BlendOperationAlpha");
            group.TagName<CppEnumItem>(@"^D3DMCS_MATERIAL$", "Material");
            group.TagName<CppEnumItem>(@"^D3DMCS_COLOR1$", "Color1");
            group.TagName<CppEnumItem>(@"^D3DMCS_COLOR2$", "Color2");
            group.TagName<CppEnumItem>(@"^D3DTSS_COLOROP$", "ColorOperation");
            group.TagName<CppEnumItem>(@"^D3DTSS_COLORARG1$", "ColorArg1");
            group.TagName<CppEnumItem>(@"^D3DTSS_COLORARG2$", "ColorArg2");
            group.TagName<CppEnumItem>(@"^D3DTSS_ALPHAOP$", "AlphaOperation");
            group.TagName<CppEnumItem>(@"^D3DTSS_ALPHAARG1$", "AlphaArg1");
            group.TagName<CppEnumItem>(@"^D3DTSS_ALPHAARG2$", "AlphaArg2");
            group.TagName<CppEnumItem>(@"^D3DTSS_BUMPENVMAT00$", "BumpEnvironmentMat00");
            group.TagName<CppEnumItem>(@"^D3DTSS_BUMPENVMAT01$", "BumpEnvironmentMat01");
            group.TagName<CppEnumItem>(@"^D3DTSS_BUMPENVMAT10$", "BumpEnvironmentMat10");
            group.TagName<CppEnumItem>(@"^D3DTSS_BUMPENVMAT11$", "BumpEnvironmentMat11");
            group.TagName<CppEnumItem>(@"^D3DTSS_TEXCOORDINDEX$", "TexCoordIndex");
            group.TagName<CppEnumItem>(@"^D3DTSS_BUMPENVLSCALE$", "BumpEnvironmentLScale");
            group.TagName<CppEnumItem>(@"^D3DTSS_BUMPENVLOFFSET$", "BumpEnvironmentLOffset");
            group.TagName<CppEnumItem>(@"^D3DTSS_TEXTURETRANSFORMFLAGS$", "TextureTransformFlags");
            group.TagName<CppEnumItem>(@"^D3DTSS_COLORARG0$", "ColorArg0");
            group.TagName<CppEnumItem>(@"^D3DTSS_ALPHAARG0$", "AlphaArg0");
            group.TagName<CppEnumItem>(@"^D3DTSS_RESULTARG$", "ResultArg");
            group.TagName<CppEnumItem>(@"^D3DTSS_CONSTANT$", "Constant");
            group.TagName<CppEnumItem>(@"^D3DSAMP_ADDRESSU$", "AddressU");
            group.TagName<CppEnumItem>(@"^D3DSAMP_ADDRESSV$", "AddressV");
            group.TagName<CppEnumItem>(@"^D3DSAMP_ADDRESSW$", "AddressW");
            group.TagName<CppEnumItem>(@"^D3DSAMP_BORDERCOLOR$", "BorderColor");
            group.TagName<CppEnumItem>(@"^D3DSAMP_MAGFILTER$", "MagFilter");
            group.TagName<CppEnumItem>(@"^D3DSAMP_MINFILTER$", "MinFilter");
            group.TagName<CppEnumItem>(@"^D3DSAMP_MIPFILTER$", "MipFilter");
            group.TagName<CppEnumItem>(@"^D3DSAMP_MIPMAPLODBIAS$", "MipMapLodBias");
            group.TagName<CppEnumItem>(@"^D3DSAMP_MAXMIPLEVEL$", "MaxMipLevel");
            group.TagName<CppEnumItem>(@"^D3DSAMP_MAXANISOTROPY$", "MaxAnisotropy");
            group.TagName<CppEnumItem>(@"^D3DSAMP_SRGBTEXTURE$", "SrgbTexture");
            group.TagName<CppEnumItem>(@"^D3DSAMP_ELEMENTINDEX$", "ElementIndex");
            group.TagName<CppEnumItem>(@"^D3DSAMP_DMAPOFFSET$", "DisplacementMapOffset");
            group.TagName<CppEnumItem>(@"^D3DSTT_UNKNOWN$", "Unknown");
            group.TagName<CppEnumItem>(@"^D3DSTT_2D$", "Texture2D");
            group.TagName<CppEnumItem>(@"^D3DSTT_CUBE$", "TextureCube");
            group.TagName<CppEnumItem>(@"^D3DSTT_VOLUME$", "TextureVolume");
            group.TagName<CppEnumItem>(@"^D3DTOP_DISABLE$", "Disable");
            group.TagName<CppEnumItem>(@"^D3DTOP_SELECTARG1$", "SelectArg1");
            group.TagName<CppEnumItem>(@"^D3DTOP_SELECTARG2$", "SelectArg2");
            group.TagName<CppEnumItem>(@"^D3DTOP_MODULATE$", "Modulate");
            group.TagName<CppEnumItem>(@"^D3DTOP_MODULATE2X$", "Modulate2X");
            group.TagName<CppEnumItem>(@"^D3DTOP_MODULATE4X$", "Modulate4X");
            group.TagName<CppEnumItem>(@"^D3DTOP_ADD$", "Add");
            group.TagName<CppEnumItem>(@"^D3DTOP_ADDSIGNED$", "AddSigned");
            group.TagName<CppEnumItem>(@"^D3DTOP_ADDSIGNED2X$", "AddSigned2X");
            group.TagName<CppEnumItem>(@"^D3DTOP_SUBTRACT$", "Subtract");
            group.TagName<CppEnumItem>(@"^D3DTOP_ADDSMOOTH$", "AddSmooth");
            group.TagName<CppEnumItem>(@"^D3DTOP_BLENDDIFFUSEALPHA$", "BlendDiffuseAlpha");
            group.TagName<CppEnumItem>(@"^D3DTOP_BLENDTEXTUREALPHA$", "BlendTextureAlpha");
            group.TagName<CppEnumItem>(@"^D3DTOP_BLENDFACTORALPHA$", "BlendFactorAlpha");
            group.TagName<CppEnumItem>(@"^D3DTOP_BLENDTEXTUREALPHAPM$", "BlendTextureAlphaPM");
            group.TagName<CppEnumItem>(@"^D3DTOP_BLENDCURRENTALPHA$", "BlendCurrentAlpha");
            group.TagName<CppEnumItem>(@"^D3DTOP_PREMODULATE$", "Premodulate");
            group.TagName<CppEnumItem>(@"^D3DTOP_MODULATEALPHA_ADDCOLOR$", "ModulateAlphaAddColor");
            group.TagName<CppEnumItem>(@"^D3DTOP_MODULATECOLOR_ADDALPHA$", "ModulateColorAddAlpha");
            group.TagName<CppEnumItem>(@"^D3DTOP_MODULATEINVALPHA_ADDCOLOR$", "ModulateInvAlphaAddColor");
            group.TagName<CppEnumItem>(@"^D3DTOP_MODULATEINVCOLOR_ADDALPHA$", "ModulateInvColorAddAlpha");
            group.TagName<CppEnumItem>(@"^D3DTOP_BUMPENVMAP$", "BumpEnvironmentMap");
            group.TagName<CppEnumItem>(@"^D3DTOP_BUMPENVMAPLUMINANCE$", "BumpEnvironmentMapLuminance");
            group.TagName<CppEnumItem>(@"^D3DTOP_DOTPRODUCT3$", "DotProduct3");
            group.TagName<CppEnumItem>(@"^D3DTOP_MULTIPLYADD$", "MultiplyAdd");
            group.TagName<CppEnumItem>(@"^D3DTOP_LERP$", "Lerp");
            group.TagName<CppEnumItem>(@"^D3DTEXF_NONE$", "None");
            group.TagName<CppEnumItem>(@"^D3DTEXF_POINT$", "Point");
            group.TagName<CppEnumItem>(@"^D3DTEXF_LINEAR$", "Linear");
            group.TagName<CppEnumItem>(@"^D3DTEXF_ANISOTROPIC$", "Anisotropic");
            group.TagName<CppEnumItem>(@"^D3DTEXF_PYRAMIDALQUAD$", "PyramidalQuad");
            group.TagName<CppEnumItem>(@"^D3DTEXF_GAUSSIANQUAD$", "GaussianQuad");
            group.TagName<CppEnumItem>(@"^D3DTEXF_CONVOLUTIONMONO$", "ConvolutionMono");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_POSITION$", "Position");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_BLENDWEIGHT$", "BlendWeight");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_BLENDINDICES$", "BlendIndices");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_NORMAL$", "Normal");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_PSIZE$", "PointSize");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_TEXCOORD$", "TextureCoordinate");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_TANGENT$", "Tangent");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_BINORMAL$", "Binormal");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_TESSFACTOR$", "TessellateFactor");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_POSITIONT$", "PositionTransformed");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_COLOR$", "Color");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_FOG$", "Fog");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_DEPTH$", "Depth");
            group.TagName<CppEnumItem>(@"^D3DDECLUSAGE_SAMPLE$", "Sample");
            group.TagName<CppEnumItem>(@"^D3DDECLMETHOD_DEFAULT$", "Default");
            group.TagName<CppEnumItem>(@"^D3DDECLMETHOD_PARTIALU$", "PartialU");
            group.TagName<CppEnumItem>(@"^D3DDECLMETHOD_PARTIALV$", "PartialV");
            group.TagName<CppEnumItem>(@"^D3DDECLMETHOD_CROSSUV$", "CrossUV");
            group.TagName<CppEnumItem>(@"^D3DDECLMETHOD_UV$", "UV");
            group.TagName<CppEnumItem>(@"^D3DDECLMETHOD_LOOKUP$", "Lookup");
            group.TagName<CppEnumItem>(@"^D3DDECLMETHOD_LOOKUPPRESAMPLED$", "LookupPresampled");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_FLOAT1$", "Float1");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_FLOAT2$", "Float2");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_FLOAT3$", "Float3");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_FLOAT4$", "Float4");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_D3DCOLOR$", "Color");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_UBYTE4$", "Ubyte4");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_SHORT2$", "Short2");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_SHORT4$", "Short4");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_UBYTE4N$", "UByte4N");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_SHORT2N$", "Short2N");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_SHORT4N$", "Short4N");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_USHORT2N$", "UShort2N");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_USHORT4N$", "UShort4N");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_UDEC3$", "UDec3");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_DEC3N$", "Dec3N");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_FLOAT16_2$", "HalfTwo");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_FLOAT16_4$", "HalfFour");
            group.TagName<CppEnumItem>(@"^D3DDECLTYPE_UNUSED$", "Unused");
            group.TagName<CppEnumItem>(@"^D3DBASIS_BEZIER$", "Bezier");
            group.TagName<CppEnumItem>(@"^D3DBASIS_BSPLINE$", "BSpline");
            group.TagName<CppEnumItem>(@"^D3DBASIS_CATMULL_ROM$", "CatmullRom");
            group.TagName<CppEnumItem>(@"^D3DDEGREE_LINEAR$", "Linear");
            group.TagName<CppEnumItem>(@"^D3DDEGREE_QUADRATIC$", "Quadratic");
            group.TagName<CppEnumItem>(@"^D3DDEGREE_CUBIC$", "Cubic");
            group.TagName<CppEnumItem>(@"^D3DDEGREE_QUINTIC$", "Quintic");
            group.TagName<CppEnumItem>(@"^D3DPATCHEDGE_DISCRETE$", "Discrete");
            group.TagName<CppEnumItem>(@"^D3DPATCHEDGE_CONTINUOUS$", "Continuous");
            group.TagName<CppEnumItem>(@"^D3DSBT_ALL$", "All");
            group.TagName<CppEnumItem>(@"^D3DSBT_PIXELSTATE$", "PixelState");
            group.TagName<CppEnumItem>(@"^D3DSBT_VERTEXSTATE$", "VertexState");
            group.TagName<CppEnumItem>(@"^D3DVBF_DISABLE$", "Disable");
            group.TagName<CppEnumItem>(@"^D3DVBF_1WEIGHTS$", "Weights1");
            group.TagName<CppEnumItem>(@"^D3DVBF_2WEIGHTS$", "Weights2");
            group.TagName<CppEnumItem>(@"^D3DVBF_3WEIGHTS$", "Weights3");
            group.TagName<CppEnumItem>(@"^D3DVBF_TWEENING$", "Tweening");
            group.TagName<CppEnumItem>(@"^D3DVBF_0WEIGHTS$", "Weights0");
            group.TagName<CppEnumItem>(@"^None$", "Disable");
            group.TagName<CppEnumItem>(@"^D3DTTFF_DISABLE$", "Disable");
            group.TagName<CppEnumItem>(@"^D3DTTFF_COUNT1$", "Count1");
            group.TagName<CppEnumItem>(@"^D3DTTFF_COUNT2$", "Count2");
            group.TagName<CppEnumItem>(@"^D3DTTFF_COUNT3$", "Count3");
            group.TagName<CppEnumItem>(@"^D3DTTFF_COUNT4$", "Count4");
            group.TagName<CppEnumItem>(@"^D3DTTFF_PROJECTED$", "Projected");
            group.TagName<CppEnumItem>(@"^None$", "Disable");
            group.TagName<CppEnumItem>(@"^D3DDEVTYPE_HAL$", "Hardware");
            group.TagName<CppEnumItem>(@"^D3DDEVTYPE_REF$", "Reference");
            group.TagName<CppEnumItem>(@"^D3DDEVTYPE_SW$", "Software");
            group.TagName<CppEnumItem>(@"^D3DDEVTYPE_NULLREF$", "NullReference");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_NONE$", "None");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_NONMASKABLE$", "NonMaskable");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_2_SAMPLES$", "TwoSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_3_SAMPLES$", "ThreeSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_4_SAMPLES$", "FourSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_5_SAMPLES$", "FiveSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_6_SAMPLES$", "SixSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_7_SAMPLES$", "SevenSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_8_SAMPLES$", "EightSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_9_SAMPLES$", "NineSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_10_SAMPLES$", "TenSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_11_SAMPLES$", "ElevenSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_12_SAMPLES$", "TwelveSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_13_SAMPLES$", "ThirteenSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_14_SAMPLES$", "FourteenSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_15_SAMPLES$", "FifteenSamples");
            group.TagName<CppEnumItem>(@"^D3DMULTISAMPLE_16_SAMPLES$", "SixteenSamples");
            group.TagName<CppEnumItem>(@"^D3DFMT_UNKNOWN$", "Unknown");
            group.TagName<CppEnumItem>(@"^D3DFMT_R8G8B8$", "R8G8B8");
            group.TagName<CppEnumItem>(@"^D3DFMT_A8R8G8B8$", "A8R8G8B8");
            group.TagName<CppEnumItem>(@"^D3DFMT_X8R8G8B8$", "X8R8G8B8");
            group.TagName<CppEnumItem>(@"^D3DFMT_R5G6B5$", "R5G6B5");
            group.TagName<CppEnumItem>(@"^D3DFMT_X1R5G5B5$", "X1R5G5B5");
            group.TagName<CppEnumItem>(@"^D3DFMT_A1R5G5B5$", "A1R5G5B5");
            group.TagName<CppEnumItem>(@"^D3DFMT_A4R4G4B4$", "A4R4G4B4");
            group.TagName<CppEnumItem>(@"^D3DFMT_R3G3B2$", "R3G3B2");
            group.TagName<CppEnumItem>(@"^D3DFMT_A8$", "A8");
            group.TagName<CppEnumItem>(@"^D3DFMT_A8R3G3B2$", "A8R3G3B2");
            group.TagName<CppEnumItem>(@"^D3DFMT_X4R4G4B4$", "X4R4G4B4");
            group.TagName<CppEnumItem>(@"^D3DFMT_A2B10G10R10$", "A2B10G10R10");
            group.TagName<CppEnumItem>(@"^D3DFMT_A8B8G8R8$", "A8B8G8R8");
            group.TagName<CppEnumItem>(@"^D3DFMT_X8B8G8R8$", "X8B8G8R8");
            group.TagName<CppEnumItem>(@"^D3DFMT_G16R16$", "G16R16");
            group.TagName<CppEnumItem>(@"^D3DFMT_A2R10G10B10$", "A2R10G10B10");
            group.TagName<CppEnumItem>(@"^D3DFMT_A16B16G16R16$", "A16B16G16R16");
            group.TagName<CppEnumItem>(@"^D3DFMT_A8P8$", "A8P8");
            group.TagName<CppEnumItem>(@"^D3DFMT_P8$", "P8");
            group.TagName<CppEnumItem>(@"^D3DFMT_L8$", "L8");
            group.TagName<CppEnumItem>(@"^D3DFMT_A8L8$", "A8L8");
            group.TagName<CppEnumItem>(@"^D3DFMT_A4L4$", "A4L4");
            group.TagName<CppEnumItem>(@"^D3DFMT_V8U8$", "V8U8");
            group.TagName<CppEnumItem>(@"^D3DFMT_L6V5U5$", "L6V5U5");
            group.TagName<CppEnumItem>(@"^D3DFMT_X8L8V8U8$", "X8L8V8U8");
            group.TagName<CppEnumItem>(@"^D3DFMT_Q8W8V8U8$", "Q8W8V8U8");
            group.TagName<CppEnumItem>(@"^D3DFMT_V16U16$", "V16U16");
            group.TagName<CppEnumItem>(@"^D3DFMT_A2W10V10U10$", "A2W10V10U10");
            group.TagName<CppEnumItem>(@"^D3DFMT_D16_LOCKABLE$", "D16Lockable");
            group.TagName<CppEnumItem>(@"^D3DFMT_D32$", "D32");
            group.TagName<CppEnumItem>(@"^D3DFMT_D15S1$", "D15S1");
            group.TagName<CppEnumItem>(@"^D3DFMT_D24S8$", "D24S8");
            group.TagName<CppEnumItem>(@"^D3DFMT_D24X8$", "D24X8");
            group.TagName<CppEnumItem>(@"^D3DFMT_D24X4S4$", "D24X4S4");
            group.TagName<CppEnumItem>(@"^D3DFMT_D16$", "D16");
            group.TagName<CppEnumItem>(@"^D3DFMT_D32F_LOCKABLE$", "D32SingleLockable");
            group.TagName<CppEnumItem>(@"^D3DFMT_D24FS8$", "D24SingleS8");
            group.TagName<CppEnumItem>(@"^D3DFMT_D32_LOCKABLE$", "D32Lockable");
            group.TagName<CppEnumItem>(@"^D3DFMT_S8_LOCKABLE$", "S8Lockable");
            group.TagName<CppEnumItem>(@"^D3DFMT_L16$", "L16");
            group.TagName<CppEnumItem>(@"^D3DFMT_VERTEXDATA$", "VertexData");
            group.TagName<CppEnumItem>(@"^D3DFMT_INDEX16$", "Index16");
            group.TagName<CppEnumItem>(@"^D3DFMT_INDEX32$", "Index32");
            group.TagName<CppEnumItem>(@"^D3DFMT_Q16W16V16U16$", "Q16W16V16U16");
            group.TagName<CppEnumItem>(@"^D3DFMT_R16F$", "R16F");
            group.TagName<CppEnumItem>(@"^D3DFMT_G16R16F$", "G16R16F");
            group.TagName<CppEnumItem>(@"^D3DFMT_A16B16G16R16F$", "A16B16G16R16F");
            group.TagName<CppEnumItem>(@"^D3DFMT_R32F$", "R32F");
            group.TagName<CppEnumItem>(@"^D3DFMT_G32R32F$", "G32R32F");
            group.TagName<CppEnumItem>(@"^D3DFMT_A32B32G32R32F$", "A32B32G32R32F");
            group.TagName<CppEnumItem>(@"^D3DFMT_CxV8U8$", "CxV8U8");
            group.TagName<CppEnumItem>(@"^D3DFMT_A1$", "A1");
            group.TagName<CppEnumItem>(@"^D3DFMT_A2B10G10R10_XR_BIAS$", "A2B10G10R10_XR_BIAS");
            group.TagName<CppEnumItem>(@"^D3DFMT_BINARYBUFFER$", "BinaryBuffer");
            group.TagName<CppEnumItem>(@"^D3DSWAPEFFECT_DISCARD$", "Discard");
            group.TagName<CppEnumItem>(@"^D3DSWAPEFFECT_FLIP$", "Flip");
            group.TagName<CppEnumItem>(@"^D3DSWAPEFFECT_COPY$", "Copy");
            group.TagName<CppEnumItem>(@"^D3DSWAPEFFECT_OVERLAY$", "Overlay");
            group.TagName<CppEnumItem>(@"^D3DSWAPEFFECT_FLIPEX$", "FlipEx");
            group.TagName<CppEnumItem>(@"^D3DPOOL_DEFAULT$", "Default");
            group.TagName<CppEnumItem>(@"^D3DPOOL_MANAGED$", "Managed");
            group.TagName<CppEnumItem>(@"^D3DPOOL_SYSTEMMEM$", "SystemMemory");
            group.TagName<CppEnumItem>(@"^D3DPOOL_SCRATCH$", "Scratch");
            group.TagName<CppEnumItem>(@"^D3DRTYPE_SURFACE$", "Surface");
            group.TagName<CppEnumItem>(@"^D3DRTYPE_VOLUME$", "Volume");
            group.TagName<CppEnumItem>(@"^D3DRTYPE_TEXTURE$", "Texture");
            group.TagName<CppEnumItem>(@"^D3DRTYPE_VOLUMETEXTURE$", "VolumeTexture");
            group.TagName<CppEnumItem>(@"^D3DRTYPE_CUBETEXTURE$", "CubeTexture");
            group.TagName<CppEnumItem>(@"^D3DRTYPE_VERTEXBUFFER$", "VertexBuffer");
            group.TagName<CppEnumItem>(@"^D3DRTYPE_INDEXBUFFER$", "IndexBuffer");
            group.TagName<CppEnumItem>(@"^D3DCUBEMAP_FACE_POSITIVE_X$", "PositiveX");
            group.TagName<CppEnumItem>(@"^D3DCUBEMAP_FACE_NEGATIVE_X$", "NegativeX");
            group.TagName<CppEnumItem>(@"^D3DCUBEMAP_FACE_POSITIVE_Y$", "PositiveY");
            group.TagName<CppEnumItem>(@"^D3DCUBEMAP_FACE_NEGATIVE_Y$", "NegativeY");
            group.TagName<CppEnumItem>(@"^D3DCUBEMAP_FACE_POSITIVE_Z$", "PositiveZ");
            group.TagName<CppEnumItem>(@"^D3DCUBEMAP_FACE_NEGATIVE_Z$", "NegativeZ");
            group.TagName<CppEnumItem>(@"^D3DDMT_ENABLE$", "Enable");
            group.TagName<CppEnumItem>(@"^D3DDMT_DISABLE$", "Disable");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_VCACHE$", "VCache");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_RESOURCEMANAGER$", "ResourceManager");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_VERTEXSTATS$", "VertexStats");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_EVENT$", "Event");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_OCCLUSION$", "Occlusion");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_TIMESTAMP$", "Timestamp");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_TIMESTAMPDISJOINT$", "TimestampDisjoint");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_TIMESTAMPFREQ$", "TimestampFreq");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_PIPELINETIMINGS$", "PipelineTimings");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_INTERFACETIMINGS$", "InterfaceTimings");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_VERTEXTIMINGS$", "VertexTimings");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_PIXELTIMINGS$", "PixelTimings");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_BANDWIDTHTIMINGS$", "BandwidthTimings");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_CACHEUTILIZATION$", "CacheUtilization");
            group.TagName<CppEnumItem>(@"^D3DQUERYTYPE_MEMORYPRESSURE$", "MemoryPressure");
            group.TagName<CppEnumItem>(@"^D3DCOMPOSERECTS_COPY$", "Copy");
            group.TagName<CppEnumItem>(@"^D3DCOMPOSERECTS_OR$", "Or");
            group.TagName<CppEnumItem>(@"^D3DCOMPOSERECTS_AND$", "And");
            group.TagName<CppEnumItem>(@"^D3DCOMPOSERECTS_NEG$", "Negate");
            group.TagName<CppEnumItem>(@"^D3DSCANLINEORDERING_UNKNOWN$", "Unknown");
            group.TagName<CppEnumItem>(@"^D3DSCANLINEORDERING_PROGRESSIVE$", "Progressive");
            group.TagName<CppEnumItem>(@"^D3DSCANLINEORDERING_INTERLACED$", "Interlaced");
            group.TagName<CppEnumItem>(@"^D3DDISPLAYROTATION_IDENTITY$", "Identity");
            group.TagName<CppEnumItem>(@"^D3DDISPLAYROTATION_90$", "Rotation90");
            group.TagName<CppEnumItem>(@"^D3DDISPLAYROTATION_180$", "Rotation180");
            group.TagName<CppEnumItem>(@"^D3DDISPLAYROTATION_270$", "Rotation270");
            group.TagName<CppEnumItem>(@"^D3DXPATCHMESH_RECT$", "Rectangle");
            group.TagName<CppEnumItem>(@"^D3DXPATCHMESH_TRI$", "Triangle");
            group.TagName<CppEnumItem>(@"^D3DXPATCHMESH_NPATCH$", "NPatch");
            group.TagName<CppEnumItem>(@"^D3DXMESH_32BIT$", "Use32Bit");
            group.TagName<CppEnumItem>(@"^D3DXMESH_DONOTCLIP$", "DoNotClip");
            group.TagName<CppEnumItem>(@"^D3DXMESH_POINTS$", "Points");
            group.TagName<CppEnumItem>(@"^D3DXMESH_RTPATCHES$", "RTPatches");
            group.TagName<CppEnumItem>(@"^D3DXMESH_NPATCHES$", "NPatches");
            group.TagName<CppEnumItem>(@"^D3DXMESH_VB_SYSTEMMEM$", "VertexBufferSystemMemory");
            group.TagName<CppEnumItem>(@"^D3DXMESH_VB_MANAGED$", "VertexBufferManaged");
            group.TagName<CppEnumItem>(@"^D3DXMESH_VB_WRITEONLY$", "VertexBufferWriteOnly");
            group.TagName<CppEnumItem>(@"^D3DXMESH_VB_DYNAMIC$", "VertexBufferDynamic");
            group.TagName<CppEnumItem>(@"^D3DXMESH_VB_SOFTWAREPROCESSING$", "VertexBufferSoftware");
            group.TagName<CppEnumItem>(@"^D3DXMESH_IB_SYSTEMMEM$", "IndexBufferSystemMemory");
            group.TagName<CppEnumItem>(@"^D3DXMESH_IB_MANAGED$", "IndexBufferManaged");
            group.TagName<CppEnumItem>(@"^D3DXMESH_IB_WRITEONLY$", "IndexBufferWriteOnly");
            group.TagName<CppEnumItem>(@"^D3DXMESH_IB_DYNAMIC$", "IndexBufferDynamic");
            group.TagName<CppEnumItem>(@"^D3DXMESH_IB_SOFTWAREPROCESSING$", "IndexBufferSoftware");
            group.TagName<CppEnumItem>(@"^D3DXMESH_VB_SHARE$", "VertexBufferShare");
            group.TagName<CppEnumItem>(@"^D3DXMESH_USEHWONLY$", "UseHardwareOnly");
            group.TagName<CppEnumItem>(@"^D3DXMESH_SYSTEMMEM$", "SystemMemory");
            group.TagName<CppEnumItem>(@"^D3DXMESH_MANAGED$", "Managed");
            group.TagName<CppEnumItem>(@"^D3DXMESH_WRITEONLY$", "WriteOnly");
            group.TagName<CppEnumItem>(@"^D3DXMESH_DYNAMIC$", "Dynamic");
            group.TagName<CppEnumItem>(@"^D3DXMESH_SOFTWAREPROCESSING$", "Software");
            group.TagName<CppEnumItem>(@"^D3DXCLEAN_BACKFACING$", "BackFacing");
            group.TagName<CppEnumItem>(@"^D3DXCLEAN_BOWTIES$", "Bowties");
            group.TagName<CppEnumItem>(@"^D3DXCLEAN_SKINNING$", "Skinning");
            group.TagName<CppEnumItem>(@"^D3DXCLEAN_OPTIMIZATION$", "Optimization");
            group.TagName<CppEnumItem>(@"^D3DXCLEAN_SIMPLIFICATION$", "Simplification");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_WRAP_U$", "WrapU");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_WRAP_V$", "WrapV");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_WRAP_UV$", "WrapUV");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_DONT_NORMALIZE_PARTIALS$", "DontNormalizePartials");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_DONT_ORTHOGONALIZE$", "DontOrthogonalize");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_ORTHOGONALIZE_FROM_V$", "OrthogonalizeFromV");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_ORTHOGONALIZE_FROM_U$", "OrthogonalizeFromU");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_WEIGHT_BY_AREA$", "WeightByArea");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_WEIGHT_EQUAL$", "WeightEqual");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_WIND_CW$", "WindCW");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_CALCULATE_NORMALS$", "CalculateNormals");
            group.TagName<CppEnumItem>(@"^D3DXTANGENT_GENERATE_IN_PLACE$", "GenerateInPlace");
            group.TagName<CppEnumItem>(@"^D3DXEDT_STRING$", "String");
            group.TagName<CppEnumItem>(@"^D3DXEDT_FLOATS$", "Floats");
            group.TagName<CppEnumItem>(@"^D3DXEDT_DWORD$", "Dword");
            group.TagName<CppEnumItem>(@"^D3DXWELDEPSILONS_WELDALL$", "WeldAll");
            group.TagName<CppEnumItem>(@"^D3DXWELDEPSILONS_WELDPARTIALMATCHES$", "WeldPartialMatches");
            group.TagName<CppEnumItem>(@"^D3DXWELDEPSILONS_DONOTREMOVEVERTICES$", "DoNotRemoveVertices");
            group.TagName<CppEnumItem>(@"^D3DXWELDEPSILONS_DONOTSPLIT$", "DoNotSplit");
            group.TagName<CppEnumItem>(@"^D3DXRS_BOOL$", "Bool");
            group.TagName<CppEnumItem>(@"^D3DXRS_INT4$", "Int4");
            group.TagName<CppEnumItem>(@"^D3DXRS_FLOAT4$", "Float4");
            group.TagName<CppEnumItem>(@"^D3DXRS_SAMPLER$", "Sampler");
            group.TagName<CppEnumItem>(@"^D3DXPC_SCALAR$", "Scalar");
            group.TagName<CppEnumItem>(@"^D3DXPC_VECTOR$", "Vector");
            group.TagName<CppEnumItem>(@"^D3DXPC_MATRIX_ROWS$", "MatrixRows");
            group.TagName<CppEnumItem>(@"^D3DXPC_MATRIX_COLUMNS$", "MatrixColumns");
            group.TagName<CppEnumItem>(@"^D3DXPC_OBJECT$", "Object");
            group.TagName<CppEnumItem>(@"^D3DXPC_STRUCT$", "Struct");
            group.TagName<CppEnumItem>(@"^D3DXPT_VOID$", "Void");
            group.TagName<CppEnumItem>(@"^D3DXPT_BOOL$", "Bool");
            group.TagName<CppEnumItem>(@"^D3DXPT_INT$", "Int");
            group.TagName<CppEnumItem>(@"^D3DXPT_FLOAT$", "Float");
            group.TagName<CppEnumItem>(@"^D3DXPT_STRING$", "String");
            group.TagName<CppEnumItem>(@"^D3DXPT_TEXTURE$", "Texture");
            group.TagName<CppEnumItem>(@"^D3DXPT_TEXTURE1D$", "Texture1D");
            group.TagName<CppEnumItem>(@"^D3DXPT_TEXTURE2D$", "Texture2D");
            group.TagName<CppEnumItem>(@"^D3DXPT_TEXTURE3D$", "Texture3D");
            group.TagName<CppEnumItem>(@"^D3DXPT_TEXTURECUBE$", "TextureCube");
            group.TagName<CppEnumItem>(@"^D3DXPT_SAMPLER$", "Sampler");
            group.TagName<CppEnumItem>(@"^D3DXPT_SAMPLER1D$", "Sampler1D");
            group.TagName<CppEnumItem>(@"^D3DXPT_SAMPLER2D$", "Sampler2D");
            group.TagName<CppEnumItem>(@"^D3DXPT_SAMPLER3D$", "Sampler3D");
            group.TagName<CppEnumItem>(@"^D3DXPT_SAMPLERCUBE$", "SamplerCube");
            group.TagName<CppEnumItem>(@"^D3DXPT_PIXELSHADER$", "PixelShader");
            group.TagName<CppEnumItem>(@"^D3DXPT_VERTEXSHADER$", "VertexShader");
            group.TagName<CppEnumItem>(@"^D3DXPT_PIXELFRAGMENT$", "PixelFragment");
            group.TagName<CppEnumItem>(@"^D3DXPT_VERTEXFRAGMENT$", "VertexFragment");
            group.TagName<CppEnumItem>(@"^D3DXPT_UNSUPPORTED$", "Unsupported");
            group.TagName<CppEnumItem>(@"^D3DXINC_LOCAL$", "Local");
            group.TagName<CppEnumItem>(@"^D3DXINC_SYSTEM$", "System");
            group.TagName<CppEnumItem>(@"^D3DXIFF_BMP$", "Bmp");
            group.TagName<CppEnumItem>(@"^D3DXIFF_JPG$", "Jpg");
            group.TagName<CppEnumItem>(@"^D3DXIFF_TGA$", "Tga");
            group.TagName<CppEnumItem>(@"^D3DXIFF_PNG$", "Png");
            group.TagName<CppEnumItem>(@"^D3DXIFF_DDS$", "Dds");
            group.TagName<CppEnumItem>(@"^D3DXIFF_PPM$", "Ppm");
            group.TagName<CppEnumItem>(@"^D3DXIFF_DIB$", "Dib");
            group.TagName<CppEnumItem>(@"^D3DXIFF_HDR$", "Hdr");
            group.TagName<CppEnumItem>(@"^D3DXIFF_PFM$", "Pfm");
            group.TagName<CppEnumItem>(@"^D3DXMESHSIMP_VERTEX$", "Vertex");
            group.TagName<CppEnumItem>(@"^D3DXMESHSIMP_FACE$", "Face");
            group.TagName<CppEnumItem>(@"^D3DXMESHTYPE_MESH$", "Mesh");
            group.TagName<CppEnumItem>(@"^D3DXMESHTYPE_PMESH$", "ProgressiveMesh");
            group.TagName<CppEnumItem>(@"^D3DXMESHTYPE_PATCHMESH$", "PatchMesh");
            group.TagName<CppEnumItem>(@"^D3DXCALLBACK_SEARCH_EXCLUDING_INITIAL_POSITION$", "SearchExcludingInitialPosition");
            group.TagName<CppEnumItem>(@"^D3DXCALLBACK_SEARCH_BEHIND_INITIAL_POSITION$", "SearchBehindInitialPosition");
            group.TagName<CppEnumItem>(@"^D3DXPLAY_LOOP$", "Loop");
            group.TagName<CppEnumItem>(@"^D3DXPLAY_ONCE$", "Once");
            group.TagName<CppEnumItem>(@"^D3DXPLAY_PINGPONG$", "PingPong");
            group.TagName<CppEnumItem>(@"^D3DXPRIORITY_LOW$", "Low");
            group.TagName<CppEnumItem>(@"^D3DXPRIORITY_HIGH$", "High");
            group.TagName<CppEnumItem>(@"^D3DXEVENT_TRACKSPEED$", "TrackSpeed");
            group.TagName<CppEnumItem>(@"^D3DXEVENT_TRACKWEIGHT$", "TrackWeight");
            group.TagName<CppEnumItem>(@"^D3DXEVENT_TRACKPOSITION$", "TrackPosition");
            group.TagName<CppEnumItem>(@"^D3DXEVENT_TRACKENABLE$", "TrackEnable");
            group.TagName<CppEnumItem>(@"^D3DXEVENT_PRIORITYBLEND$", "PriorityBlend");
            group.TagName<CppEnumItem>(@"^D3DXTRANSITION_LINEAR$", "Linear");
            group.TagName<CppEnumItem>(@"^D3DXTRANSITION_EASEINEASEOUT$", "EaseInEaseOut");

            group.TagName<CppEnumItem>(@"^D3DCREATE_PUREDEVICE$", "PureDevice");
            group.TagName<CppEnumItem>(@"^D3DCREATE_SOFTWARE_VERTEXPROCESSING$", "SoftwareVertexProcessing");
            group.TagName<CppEnumItem>(@"^D3DCREATE_HARDWARE_VERTEXPROCESSING$", "HardwareVertexProcessing");
            group.TagName<CppEnumItem>(@"^D3DCREATE_MIXED_VERTEXPROCESSING$", "MixedVertexProcessing");
            group.TagName<CppEnumItem>(@"^D3DCREATE_ADAPTERGROUP_DEVICE$", "AdapterGroupDevice");
            group.TagName<CppEnumItem>(@"^D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX$", "DisableExtendedDriverManagement");
            group.TagName<CppEnumItem>(@"^D3DCREATE_NOWINDOWCHANGES$", "NoWindowChanges");
            group.TagName<CppEnumItem>(@"^D3DCREATE_ENABLE_PRESENTSTATS$", "EnablePresentStatistics");
            group.TagName<CppEnumItem>(@"^D3DCREATE_DISABLE_PRINTSCREEN$", "DisablePrintScreen");
            group.TagName<CppEnumItem>(@"^D3DCREATE_SCREENSAVER$", "AllowScreensavers");

            group.TagName<CppEnumItem>(@"^D3DPRESENT_DONOTWAIT$", "DoNotWait");
            group.TagName<CppEnumItem>(@"^D3DPRESENT_DONOTFLIP$", "DoNotFlip");
            group.TagName<CppEnumItem>(@"^D3DPRESENT_FLIPRESTART$", "FlipRestart");
            group.TagName<CppEnumItem>(@"^D3DPRESENT_UPDATEOVERLAYONLY$", "UpdateOverlayOnly");
            group.TagName<CppEnumItem>(@"^D3DPRESENT_HIDEOVERLAY$", "HideOverlay");
            group.TagName<CppEnumItem>(@"^D3DPRESENT_UPDATECOLORKEY$", "UpdateColorKey");
            group.TagName<CppEnumItem>(@"^D3DPRESENT_FORCEIMMEDIATE$", "ForceImmediate");
            group.TagName<CppEnumItem>(@"^D3DPRESENT_RATE_DEFAULT$", "None");

            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_LOCKABLE_BACKBUFFER$", "LockableBackBuffer");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL$", "DiscardDepthStencil");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_DEVICECLIP$", "DeviceClip");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_VIDEO$", "Video");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_NOAUTOROTATE$", "NoAutoRotate");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_UNPRUNEDMODE$", "UnprunedMode");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_OVERLAY_LIMITEDRGB$", "OverlayLimitedRgb");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_OVERLAY_YCbCr_BT709$", "OverlayYCbCr_BT709");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_OVERLAY_YCbCr_xvYCC$", "OverlayYCbCr_xvYCC");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_RESTRICTED_CONTENT$", "RestrictedContent");
            group.TagName<CppEnumItem>(@"^D3DPRESENTFLAG_RESTRICT_SHARED_RESOURCE_DRIVER$", "RestrictSharedResourceDriver");

            group.TagName<CppEnumItem>(@"^D3DFVF_XYZ$", "Position");
            group.TagName<CppEnumItem>(@"^D3DFVF_XYZRHW$", "PositionRhw");
            group.TagName<CppEnumItem>(@"^D3DFVF_XYZB1$", "PositionBlend1");
            group.TagName<CppEnumItem>(@"^D3DFVF_XYZB2$", "PositionBlend2");
            group.TagName<CppEnumItem>(@"^D3DFVF_XYZB3$", "PositionBlend3");
            group.TagName<CppEnumItem>(@"^D3DFVF_XYZB4$", "PositionBlend4");
            group.TagName<CppEnumItem>(@"^D3DFVF_XYZB5$", "PositionBlend5");
            group.TagName<CppEnumItem>(@"^D3DFVF_XYZW$", "PositionW");
            group.TagName<CppEnumItem>(@"^D3DFVF_PSIZE$", "PointSize");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEXCOUNT_MASK$", "TextureCountMask");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEXCOUNT_SHIFT$", "TextureCountShift");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX0$", "Texture0");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX1$", "Texture1");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX2$", "Texture2");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX3$", "Texture3");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX4$", "Texture4");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX5$", "Texture5");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX6$", "Texture6");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX7$", "Texture7");
            group.TagName<CppEnumItem>(@"^D3DFVF_TEX8$", "Texture8");
            group.TagName<CppEnumItem>(@"^D3DFVF_LASTBETA_UBYTE4$", "LastBetaUByte4");
            group.TagName<CppEnumItem>(@"^D3DFVF_LASTBETA_D3DCOLOR$", "LastBetaColor");
            group.TagName<CppEnumItem>(@"^D3DFVF_NONE$", "None");

            group.TagName<CppEnumItem>(@"^D3DUSAGE_RENDERTARGET$", "RenderTarget");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_DEPTHSTENCIL$", "DepthStencil");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_NONSECURE$", "NonSecure");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_AUTOGENMIPMAP$", "AutoGenerateMipMap");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_DMAP$", "DisplacementMap");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_QUERY_LEGACYBUMPMAP$", "QueryLegacyBumpMap");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_QUERY_SRGBREAD$", "QuerySrgbRead");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_QUERY_SRGBWRITE$", "QuerySrgbWrite");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING$", "QueryPostPixelShaderBlending");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_QUERY_VERTEXTEXTURE$", "QueryVertexTexture");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_QUERY_WRAPANDMIP$", "QueryWrapAndMip");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_WRITEONLY$", "WriteOnly");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_SOFTWAREPROCESSING$", "SoftwareProcessing");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_DONOTCLIP$", "DoNotClip");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_RTPATCHES$", "RTPatches");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_NPATCHES$", "NPatches");
            group.TagName<CppEnumItem>(@"^D3DUSAGE_TEXTAPI$", "TextApi");

            group.TagName<CppEnumItem>(@"^D3DXCLEAN_BACKFACING$", "BackFacing");
            group.TagName<CppEnumItem>(@"^D3DXCLEAN_SKINNING$", "Skinning");
            group.TagName<CppEnumItem>(@"^D3DXCLEAN_OPTIMIZATION$", "Optimization");

            group.TagName<CppEnumItem>(@"^D3DLOCK_READONLY$", "ReadOnly");
            group.TagName<CppEnumItem>(@"^D3DLOCK_NOOVERWRITE$", "NoOverwrite");
            group.TagName<CppEnumItem>(@"^D3DLOCK_NOSYSLOCK$", "NoSystemLock");
            group.TagName<CppEnumItem>(@"^D3DLOCK_DONOTWAIT$", "DoNotWait");

            group.TagName<CppEnumItem>(@"^D3DCLEAR_ZBUFFER$", "ZBuffer");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Structures
            // --------------------------------------------------------------------------------------------------------
            gen.MapCppTypeToCSharpType("D3DCOLORVALUE", TypeSlimMathColor4);
            gen.MapCppTypeToCSharpType("D3DXCOLOR", TypeSlimMathColor4);
            gen.MapCppTypeToCSharpType("D3DXMATRIX", TypeSlimMathMatrix);
            gen.MapCppTypeToCSharpType("D3DMATRIX", TypeSlimMathMatrix);
            gen.MapCppTypeToCSharpType("D3DXVECTOR2", TypeSlimMathVector2);
            gen.MapCppTypeToCSharpType("D3DVECTOR", TypeSlimMathVector3);
            gen.MapCppTypeToCSharpType("D3DXVECTOR3", TypeSlimMathVector3);
            gen.MapCppTypeToCSharpType("D3DXVECTOR4", TypeSlimMathVector4);
            gen.MapCppTypeToCSharpType("D3DXQUATERNION", TypeSlimMathQuaternion);
            gen.MapCppTypeToCSharpType("D3DXPLANE", TypeSlimMathPlane);

            gen.MapCppTypeToCSharpType("D3DCOLOR", TypeSlimMathColor4);   // TODO: use real ColorRGBA8
            gen.MapCppTypeToCSharpType("D3DXFLOAT16", typeof(int)); // TODO TEMP!!!!!!
            gen.MapCppTypeToCSharpType("D3DXVECTOR2_16F", typeof(int)); // TODO TEMP!!!!!!
            gen.MapCppTypeToCSharpType("D3DXVECTOR3_16F", typeof(int)); // TODO TEMP!!!!!!
            gen.MapCppTypeToCSharpType("D3DXVECTOR4_16F", typeof(int)); // TODO TEMP!!!!!!

            group.Remove<CppStruct>(@"^D3D_OMAC$");
            group.Remove<CppStruct>(@"^D3DDEVINFO_.*$");
            group.Remove<CppStruct>(@"^D3DAES_CTR_IV$");
            group.Remove<CppStruct>(@"^D3DENCRYPTED_BLOCK_INFO$");
            group.Remove<CppStruct>(@"^D3DRANGE$");
            group.Remove<CppStruct>(@"^D3DRESOURCESTATS$");
            group.Remove<CppStruct>(@"^D3DMEMORYPRESSURE$");
            group.Remove<CppStruct>(@"^D3DCOMPOSERECTDESC$");
            group.Remove<CppStruct>(@"^D3DCOMPOSERECTDESTINATION$");
            group.Remove<CppStruct>(@"^D3DOVERLAYCAPS$");
            group.Remove<CppStruct>(@"^D3DCONTENTPROTECTIONCAPS$");
            group.Remove<CppStruct>(@"^D3DXFONT_DESCA$");
            group.Remove<CppStruct>(@"^D3DXF_FILELOADRESOURCE$");
            group.Remove<CppStruct>(@"^D3DXF_FILELOADMEMORY$");
            group.Remove<CppStruct>(@"^D3DXINTERSECTINFO$");
            group.Remove<CppStruct>(@"^D3DXSHMATERIAL$");
            group.Remove<CppStruct>(@"^D3DXSHPRTSPLITMESHVERTDATA$");
            group.Remove<CppStruct>(@"^D3DXSHPRTSPLITMESHCLUSTERDATA$");
            group.Remove<CppStruct>(@"^D3DXSHADER_TYPEINFO$");
            group.Remove<CppStruct>(@"^D3DXSHADER_STRUCTMEMBERINFO$");
            group.Remove<CppStruct>(@"^D3DXSHCOMPRESSQUALITYTYPE$");
            group.Remove<CppStruct>(@"^D3DXSHGPUSIMOPT$");

            group.TagName<CppStruct>(@"^D3DPRESENTSTATS$", "PresentationStatistics");
            group.TagName<CppStruct>(@"^D3D(.*)9", "$1", false);

            gen.MapCppTypeToCSharpType("LPGLYPHMETRICSFLOAT", typeof(IntPtr));
            gen.MapCppTypeToCSharpType("D3D_OMAC", typeof(Guid));
            gen.MapCppTypeToCSharpType("D3DRECT", TypeSlimDX2Rectangle);

            group.TagName<CppStruct>(@"^D3DXMATERIAL", "ExtendedMaterial");
            group.TagName<CppStruct>(@"^D3DXMESHCONTAINER$", "MeshContainer");
            group.TagName<CppStruct>(@"^D3DXMESHDATA$", "MeshData");
            group.TagName<CppStruct>(@"^D3DXWELDEPSILONS$", "WeldEpsilons");
            group.TagName<CppStruct>(@"^D3DXEFFECTINSTANCE$", "EffectInstance");
            group.TagName<CppStruct>(@"^D3DXFONT_DESCW$", "FontDescription");
            group.TagName<CppStruct>(@"^D3DADAPTER_IDENTIFIER9$", "AdapterDetails");
            group.TagName<CppStruct>(@"^D3DCAPS9$", "Capabilities");
            group.TagName<CppStruct>(@"^D3DCLIPSTATUS9$", "ClipStatus");
            group.TagName<CppStruct>(@"^D3DDEVICE_CREATION_PARAMETERS$", "CreationParameters");
            group.TagName<CppStruct>(@"^D3DDISPLAYMODE$", "DisplayMode");
            group.TagName<CppStruct>(@"^D3DDISPLAYMODEEX$", "DisplayModeEx");
            group.TagName<CppStruct>(@"^D3DDISPLAYMODEFILTER$", "DisplayModeFilter");
            group.TagName<CppStruct>(@"^D3DGAMMARAMP$", "GammaRamp");
            group.TagName<CppStruct>(@"^D3DINDEXBUFFER_DESC$", "IndexBufferDescription");
            group.TagName<CppStruct>(@"^D3DPSHADERCAPS2_0$", "PixelShader20Caps");
            group.TagName<CppStruct>(@"^D3DRECTPATCH_INFO$", "RectanglePatchInfo");
            group.TagName<CppStruct>(@"^D3DTRIPATCH_INFO$", "TrianglePatchInfo");
            group.TagName<CppStruct>(@"^D3DVERTEXBUFFER_DESC$", "VertexBufferDescription");
            group.TagName<CppStruct>(@"^D3DVERTEXELEMENT9$", "VertexElement");
            group.TagName<CppStruct>(@"^D3DVSHADERCAPS2_0$", "VertexShader20Caps");
            group.TagName<CppStruct>(@"^D3DXATTRIBUTERANGE$", "AttributeRange");
            group.TagName<CppStruct>(@"^D3DXATTRIBUTEWEIGHTS$", "AttributeWeights");
            group.TagName<CppStruct>(@"^D3DXBONECOMBINATION$", "BoneCombination");
            group.TagName<CppStruct>(@"^D3DXCONSTANTTABLE_DESC$", "ConstantTableDescription");
            group.TagName<CppStruct>(@"^D3DXEFFECTDEFAULT$", "EffectDefault");
            group.TagName<CppStruct>(@"^D3DXKEY_CALLBACK$", "CallbackKey");
            group.TagName<CppStruct>(@"^D3DXKEY_QUATERNION$", "RotationKey");
            group.TagName<CppStruct>(@"^D3DXKEY_VECTOR3$", "ScaleKey");
            group.TagName<CppStruct>(@"^D3DXPATCHINFO$", "PatchInfo");
            group.TagName<CppStruct>(@"^D3DXRTE_DESC$", "RenderToEnvironmentMapDescription");
            group.TagName<CppStruct>(@"^D3DXRTS_DESC$", "RenderToSurfaceDescription");
            group.TagName<CppStruct>(@"^D3DXSEMANTIC$", "ShaderSemantic");

            group.TagTypeAndName<CppField>(@"^D3DPRESENT_PARAMETERS::Flags$", "D3DPRESENT_FLAGS", "PresentFlags");
            group.TagName<CppField>(@"^D3DPRESENT_PARAMETERS::hDeviceWindow$", "DeviceWindowHandle");
            group.TagTypeAndName<CppField>(@"^D3DPRESENT_PARAMETERS::PresentationInterval$", "D3DPRESENT_INTERVAL");
            group.TagTypeAndName<CppField>(@"^D3DVERTEXBUFFER_DESC::FVF$", "D3DFVF");

            group.TagTypeAndName<CppField>(@"^D3DVERTEXELEMENT9::Type$", "D3DDECLTYPE");
            group.TagTypeAndName<CppField>(@"^D3DVERTEXELEMENT9::Method$", "D3DDECLMETHOD");
            group.TagTypeAndName<CppField>(@"^D3DVERTEXELEMENT9::Usage$", "D3DDECLUSAGE");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^IDirect3D(.+)", "$1", false);
            group.TagName<CppInterface>(@"^IDirect3D(.+)9$", "$1", false);
            group.TagName<CppInterface>(@"^IDirect3D9Ex(.+)", "$1", false);
            group.TagName<CppInterface>(@"^IDirect3D9Ex$", "Direct3D9Ex");
            group.TagName<CppMethod>(@"^GetDC$", "GetDisplayDeviceContext");

            group.Remove<CppInterface>(@"^IDirect3DCryptoSession9$");
            group.Remove<CppInterface>(@"^IDirect3D9ExOverlayExtension$");
            group.Remove<CppInterface>(@"^ID3DXPRTBuffer$");
            group.Remove<CppInterface>(@"^ID3DXPRTEngine$");
            group.Remove<CppInterface>(@"^ID3DXPRTCompBuffer$");
            group.Remove<CppInterface>(@"^ID3DXTextureGutterHelper$");

            group.TagName<CppInterface>(@"^ID3DXAllocateHierarchy$", "IAllocateHierarchy");
            group.TagName<CppInterface>(@"^ID3DXBuffer$", "ShaderBytecode");
            group.TagName<CppInterface>(@"^ID3DXLoadUserData$", "ILoadUserData");
            group.TagName<CppInterface>(@"^ID3DXRenderToEnvMap$", "RenderToEnvironmentMap");
            group.TagName<CppInterface>(@"^ID3DXSaveUserData$", "ISaveUserData");
            group.TagName<CppInterface>(@"^IDirect3D9$", "Direct3D");
            group.TagName<CppInterface>(@"^IDirect3DDevice9Ex$", "DeviceEx");
            group.TagName<CppInterface>(@"^ID3DXSPMesh$", "SimplificationMesh");

            group.Remove<CppMethod>(@"^ID3DXFont::GetDescA$");

            // Modify methods on IDirect3D9
            group.TagVisibility<CppMethod>(@"^IDirect3D9::CreateDevice$", Visibility.Internal);
            group.TagTypeAndName<CppParameter>(@"^IDirect3D9::CreateDevice::BehaviorFlags$", "D3DCREATE_FLAGS");
            group.TagParameter(@"^IDirect3D9::CreateDevice::pPresentationParameters$", CppAttribute.In | CppAttribute.Buffer);

            // Modify methods on IDirect3DDevice9
            group.TagTypeAndName<CppParameter>(@"^IDirect3DDevice9::Clear::Flags$", "D3DCLEAR_FLAGS");
            group.TagParameter(@"^IDirect3DDevice9::Clear::pRects$", CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional);
            group.TagVisibility<CppMethod>(@"^IDirect3DDevice9::Clear$", Visibility.Internal, null, "Clear_");
            group.TagParameter(@"^IDirect3DDevice9::ColorFill::pRect$", CppAttribute.In | CppAttribute.Optional);

            group.TagVisibility<CppMethod>(@"^IDirect3DDevice9::Create.*$", Visibility.Internal);

            group.TagTypeAndName<CppParameter>(@"^IDirect3DDevice9::CreateVertexBuffer::FVF$", "D3DFVF", "vertexFormat");
            group.TagTypeAndName<CppParameter>(@"^IDirect3DDevice9::CreateVertexBuffer::Usage$", "D3DUSAGE");
            group.TagParameter(@"^IDirect3DDevice9::CreateVertexDeclaration::pVertexElements$", CppAttribute.In | CppAttribute.Buffer);

            group.TagName<CppMethod>(@"^IDirect3DDevice9::GetFVF$", "GetVertexFormat");
            group.TagName<CppMethod>(@"^IDirect3DDevice9::SetFVF$", "SetVertexFormat");
            group.TagTypeAndName<CppParameter>(@"^IDirect3DDevice9::SetFVF::FVF$", "D3DFVF", "vertexFormat");
            group.TagTypeAndName<CppParameter>(@"^IDirect3DDevice9::GetFVF::pFVF$", "D3DFVF", "vertexFormat");

            group.TagName<CppMethod>(@"^IDirect3DDevice9::DrawPrimitive$", "DrawPrimitives");

            /// <unmanaged>HRESULT IDirect3DDevice9::Present([None] const RECT* pSourceRect,[None] const RECT* pDestRect,[None] HWND hDestWindowOverride,[None] const RGNDATA* pDirtyRegion)</unmanaged>
            group.TagParameter(@"^IDirect3DDevice9::Present::pSourceRect$", CppAttribute.In | CppAttribute.Optional);
            group.TagParameter(@"^IDirect3DDevice9::Present::pDestRect$", CppAttribute.InOut | CppAttribute.Optional);
            group.TagParameter(@"^IDirect3DDevice9::Present::pDirtyRegion$", CppAttribute.In | CppAttribute.Optional);
            group.TagVisibility<CppMethod>(@"^IDirect3DDevice9::Present$", Visibility.Internal);

            // Modify methods on IDirect3DVertexBuffer9
            // IDirect3DVertexBuffer9::Lock([None] UINT OffsetToLock,[None] UINT SizeToLock,[None] void** ppbData,[None] int Flags)</
            group.TagVisibility<CppMethod>(@"^IDirect3DVertexBuffer9::Lock$", Visibility.Internal, null, "Lock_");
            group.TagParameter(@"^IDirect3DVertexBuffer9::Lock::ppbData$", CppAttribute.Out);
            group.TagTypeAndName<CppParameter>(@"^IDirect3DVertexBuffer9::Lock::Flags$", "D3DLOCK", "lockFlags");

            // Modify methods on ID3DXEffectStateManager
            group.TagTypeAndName<CppParameter>(@"^ID3DXEffectStateManager::SetFVF::FVF$", "D3DFVF", "vertexFormat");
            group.TagName<CppMethod>(@"^ID3DXEffectStateManager::SetFVF$", "SetVertexFormat");


            // Patch methods (generated by group.DumpGetMethods)
            group.TagParameter(@"^IDirect3D9::GetAdapterIdentifier::pIdentifier$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3D9::GetAdapterDisplayMode::pMode$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3D9::GetDeviceCaps::pCaps$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetDirect3D::ppD3D9$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetDeviceCaps::pCaps$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetDisplayMode::pMode$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetCreationParameters::pParameters$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetSwapChain::pSwapChain$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetBackBuffer::ppBackBuffer$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetRasterStatus::pRasterStatus$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetGammaRamp::pRamp$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetRenderTargetData::pRenderTarget$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetRenderTargetData::pDestSurface$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetFrontBufferData::pDestSurface$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetRenderTarget::ppRenderTarget$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetDepthStencilSurface::ppZStencilSurface$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetTransform::pMatrix$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetViewport::pViewport$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetMaterial::pMaterial$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetLight::arg1$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetLightEnable::pEnable$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetClipPlane::pPlane$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetRenderState::pValue$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetClipStatus::pClipStatus$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetTexture::ppTexture$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetTextureStageState::pValue$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetSamplerState::pValue$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetPaletteEntries::pEntries$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetCurrentTexturePalette::PaletteNumber$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetScissorRect::pRect$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetVertexDeclaration::ppDecl$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetFVF::pFVF$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetVertexShader::ppShader$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetVertexShaderConstantF::pConstantData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetVertexShaderConstantI::pConstantData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetVertexShaderConstantB::pConstantData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetStreamSource::ppStreamData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetStreamSource::pOffsetInBytes$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetStreamSource::pStride$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetStreamSourceFreq::pSetting$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetIndices::ppIndexData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetPixelShader::ppShader$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetPixelShaderConstantF::pConstantData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetPixelShaderConstantI::pConstantData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9::GetPixelShaderConstantB::pConstantData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DStateBlock9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DResource9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DResource9::GetPrivateData::pSizeOfData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVertexDeclaration9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVertexDeclaration9::GetDeclaration::pElement$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVertexDeclaration9::GetDeclaration::pNumElements$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVertexShader9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVertexShader9::GetFunction::pSizeOfData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DPixelShader9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DPixelShader9::GetFunction::pSizeOfData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DTexture9::GetLevelDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DTexture9::GetSurfaceLevel::ppSurfaceLevel$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVolumeTexture9::GetLevelDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVolumeTexture9::GetVolumeLevel::ppVolumeLevel$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DCubeTexture9::GetLevelDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DCubeTexture9::GetCubeMapSurface::ppCubeMapSurface$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVertexBuffer9::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DIndexBuffer9::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSurface9::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSurface9::GetDC::phdc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVolume9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVolume9::GetPrivateData::pSizeOfData$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DVolume9::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9::GetFrontBufferData::pDestSurface$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9::GetBackBuffer::ppBackBuffer$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9::GetRasterStatus::pRasterStatus$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9::GetDisplayMode::pMode$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9::GetPresentParameters::pPresentationParameters$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DQuery9::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3D9Ex::GetAdapterModeCountEx::pFilter$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3D9Ex::GetAdapterDisplayModeEx::pMode$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3D9Ex::GetAdapterDisplayModeEx::pRotation$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3D9Ex::GetAdapterLUID::pLUID$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9Ex::GetGPUThreadPriority::pPriority$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9Ex::GetMaximumFrameLatency::pMaxLatency$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9Ex::GetDisplayModeEx::pMode$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9Ex::GetDisplayModeEx::pRotation$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9Ex::GetLastPresentCount::pLastPresentCount$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9Ex::GetPresentStats::pPresentationStatistics$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9Ex::GetDisplayModeEx::pMode$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DSwapChain9Ex::GetDisplayModeEx::pRotation$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9Video::GetContentProtectionCaps::pCryptoType$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9Video::GetContentProtectionCaps::pDecodeProfile$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DDevice9Video::GetContentProtectionCaps::pCaps$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DAuthenticatedChannel9::GetCertificateSize::pCertificateSize$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DAuthenticatedChannel9::GetCertificate::ppCertificate$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DCryptoSession9::GetCertificateSize::pCertificateSize$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DCryptoSession9::GetCertificate::ppCertificate$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DCryptoSession9::GetSurfacePitch::pSrcSurface$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DCryptoSession9::GetSurfacePitch::pSurfacePitch$", CppAttribute.Out);
            group.TagParameter(@"^IDirect3DCryptoSession9::GetEncryptionBltKey::pReadbackKey$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSprite::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSprite::GetTransform::pTransform$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetDescA::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetDescW::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetTextMetricsA::pTextMetrics$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetTextMetricsW::pTextMetrics$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetGlyphData::ppTexture$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetGlyphData::pBlackBox$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFont::GetGlyphData::pCellInc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXRenderToSurface::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXRenderToSurface::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXRenderToEnvMap::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXRenderToEnvMap::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXLine::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileSaveObject::GetFile::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileSaveData::GetSave::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileSaveData::GetName::arg1$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileSaveData::GetType::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileEnumObject::GetFile::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileEnumObject::GetChildren::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileEnumObject::GetChild::arg1$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileData::GetEnum::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileData::GetName::arg1$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileData::GetType::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileData::GetChildren::arg0$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXFileData::GetChild::arg1$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseMesh::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseMesh::GetVertexBuffer::ppVB$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseMesh::GetIndexBuffer::ppIB$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseMesh::GetAttributeTable::pAttribTable$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseMesh::GetAttributeTable::pAttribTableSize$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPMesh::GetAdjacency::pAdjacency$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSPMesh::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSPMesh::GetVertexWeights::pVertexWeights$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetVertexBuffer::ppVB$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetIndexBuffer::ppIB$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetTessSize::NumTriangles$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetTessSize::NumVertices$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetDisplaceParam::Texture$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetDisplaceParam::MinFilter$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetDisplaceParam::MagFilter$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetDisplaceParam::MipFilter$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetDisplaceParam::Wrap$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPatchMesh::GetDisplaceParam::dwLODBias$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSkinInfo::GetBoneInfluence::vertices$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSkinInfo::GetBoneInfluence::weights$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSkinInfo::GetBoneVertexInfluence::pWeight$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSkinInfo::GetBoneVertexInfluence::pVertexNum$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSkinInfo::GetMaxVertexInfluences::maxVertexInfluences$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXSkinInfo::GetMaxFaceInfluences::maxFaceInfluences$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureGutterHelper::GetFaceMap::pFaceData$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureGutterHelper::GetBaryMap::pBaryData$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureGutterHelper::GetTexelMap::pTexelData$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureGutterHelper::GetGutterMap::pGutterData$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPRTEngine::GetVertexAlbedo::pVertColors$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPRTEngine::GetAdaptedMesh::pFaceRemap$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPRTEngine::GetAdaptedMesh::pVertRemap$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPRTEngine::GetAdaptedMesh::pfVertWeights$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXPRTEngine::GetAdaptedMesh::ppMesh$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXConstantTable::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXConstantTable::GetConstantDesc::pConstantDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXConstantTable::GetConstantDesc::pCount$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureShader::GetFunction::ppFunction$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureShader::GetConstantBuffer::ppConstantBuffer$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureShader::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureShader::GetConstantDesc::pConstantDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXTextureShader::GetConstantDesc::pCount$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetParameterDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetTechniqueDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetPassDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetFunctionDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetBool::pb$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetBoolArray::pb$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetInt::pn$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetIntArray::pn$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetFloat::pf$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetFloatArray::pf$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetVector::pVector$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetVectorArray::pVector$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetMatrix::pMatrix$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetMatrixArray::pMatrix$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetMatrixPointerArray::ppMatrix$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetMatrixTranspose::pMatrix$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetMatrixTransposeArray::pMatrix$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetMatrixTransposePointerArray::ppMatrix$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetString::ppString$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetTexture::ppTexture$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetPixelShader::ppPShader$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXBaseEffect::GetVertexShader::ppVShader$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXEffect::GetPool::ppPool$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXEffect::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXEffect::GetStateManager::ppManager$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXEffectCompiler::GetLiteral::pLiteral$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXAnimationSet::GetSRT::pScale$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXAnimationSet::GetSRT::pRotation$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXAnimationSet::GetSRT::pTranslation$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXAnimationSet::GetCallback::pCallbackPosition$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXCompressedAnimationSet::GetCompressedData::ppCompressedData$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXAnimationController::GetAnimationSet::ppAnimationSet$", CppAttribute.Out);
            group.TagParameter(@"^ID3DXAnimationController::GetTrackAnimationSet::ppAnimSet$", CppAttribute.Out);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Functions
            // --------------------------------------------------------------------------------------------------------
            group.Remove<CppFunction>(@"^D3DX.*PRT.*$");
            group.Remove<CppFunction>(@"^D3DXCreateFontIndirectA$");
            group.Remove<CppFunction>(@"^D3DXSHPRTCompSplitMeshSC$");
            group.Remove<CppFunction>(@"^D3DXCreateTextureGutterHelper$");

            group.TagName<CppFunction>(@"^D3DXCreateFontIndirectW$", "CreateFontIndirect");

            string d3dx9DLLName = string.Format("d3dx9_{0}.dll", group.FindFirst<CppMacroDefinition>("D3DX_SDK_VERSION").StripStringValue);
            group.TagFunction("^D3D9.*", "d3d9.dll", d3d9FunctionGroup);
            group.TagFunction("^Direct3D.*", "d3d9.dll", d3d9FunctionGroup);
            group.TagFunction("^D3DX9.*", d3dx9DLLName, d3dx9FunctionGroup);
            group.TagFunction("^D3DX[^0-9].*", d3dx9DLLName, d3dx9FunctionGroup);
            group.TagFunction("^D3DPERF.*", d3dx9DLLName, d3dx9FunctionGroup);

            // Add constant from macro definitions
            gen.AddConstantFromMacroToCSharpType("D3D_SDK_VERSION", Global.Name + ".Direct3D9.D3D9", "int", "SdkVersion");

            // Clear FindContext
            group.FindContext.Clear();
        }
    }
}