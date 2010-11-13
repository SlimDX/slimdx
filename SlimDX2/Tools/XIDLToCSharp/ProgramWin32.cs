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
        public CSharpStruct TypeSystemDrawingSizeF;
        public CSharpStruct TypeSystemDrawingSize;
        public CSharpStruct TypeSystemDrawingPointF;
        public CSharpStruct TypeSystemDrawingPoint;
        public CSharpStruct TypeSlimMathMatrix;
        public CSharpStruct TypeSlimMathVector2;
        public CSharpStruct TypeSlimMathVector3;
        public CSharpStruct TypeSlimMathVector4;
        public CSharpStruct TypeSlimMathColor3;
        public CSharpStruct TypeSlimMathColor4;
        public CSharpStruct TypeSlimMathQuaternion;
        public CSharpStruct TypeSlimMathPlane;
        public CSharpStruct TypeSlimDX2Rectangle;
        public CSharpStruct TypeSlimDX2RectangleF;
        public CSharpStruct TypeSlimDX2FunctionCallback;
        public CSharpInterface TypeIUnknown;

        /// <summary>
        /// Maps Win32 Global API
        /// </summary>
        public unsafe void MapWin32()
        {
            // Namespace mapping for win32_ext extension
            gen.MapIncludeToNamespace("win32_ext", Global.Name + ".Windows", Global.Name, "Windows");

            // --------------------------------------------------------------------------------------------------------
            // Global/Win32 Enumerations
            // --------------------------------------------------------------------------------------------------------
            // Remove all enums ending with _FORCE_DWORD, FORCE_UINT
            group.Remove<CppEnumItem>("^.*_FORCE_DWORD$");
            group.Remove<CppEnumItem>("^.*_FORCE_UINT$");

            // --------------------------------------------------------------------------------------------------------
            // Global/Win32 Structures
            // --------------------------------------------------------------------------------------------------------
            // System.Drawing.SizeF
            TypeSystemDrawingSizeF = new CSharpStruct();
            TypeSystemDrawingSizeF.Type = typeof(System.Drawing.SizeF);
            TypeSystemDrawingSizeF.Name = TypeSystemDrawingSizeF.Type.FullName;
            TypeSystemDrawingSizeF.SizeOf = sizeof(System.Drawing.SizeF);

            // System.Drawing.Size
            TypeSystemDrawingSize = new CSharpStruct();
            TypeSystemDrawingSize.Type = typeof(System.Drawing.Size);
            TypeSystemDrawingSize.Name = TypeSystemDrawingSize.Type.FullName;
            TypeSystemDrawingSize.SizeOf = sizeof(System.Drawing.Size);

            // Use System.Drawing.PointF struct
            TypeSystemDrawingPointF = new CSharpStruct();
            TypeSystemDrawingPointF.Type = typeof(System.Drawing.PointF);
            TypeSystemDrawingPointF.Name = TypeSystemDrawingPointF.Type.FullName;
            TypeSystemDrawingPointF.SizeOf = sizeof(System.Drawing.PointF);

            // Use System.Drawing.Point struct
            TypeSystemDrawingPoint = new CSharpStruct();
            TypeSystemDrawingPoint.Type = typeof(System.Drawing.Point);
            TypeSystemDrawingPoint.Name = TypeSystemDrawingPoint.Type.FullName;
            TypeSystemDrawingPoint.SizeOf = sizeof(System.Drawing.Point);

            // Use SlimMath.Matrix
            TypeSlimMathMatrix = new CSharpStruct();
            TypeSlimMathMatrix.Type = typeof(SlimMath.Matrix);
            TypeSlimMathMatrix.Name = TypeSlimMathMatrix.Type.FullName;
            TypeSlimMathMatrix.SizeOf = sizeof(SlimMath.Matrix);

            // Use SlimMath.Vector2
            TypeSlimMathVector2 = new CSharpStruct();
            TypeSlimMathVector2.Type = typeof(SlimMath.Vector2);
            TypeSlimMathVector2.Name = TypeSlimMathVector2.Type.FullName;
            TypeSlimMathVector2.SizeOf = sizeof(SlimMath.Vector2);

            // Use SlimMath.Vector3
            TypeSlimMathVector3 = new CSharpStruct();
            TypeSlimMathVector3.Type = typeof(SlimMath.Vector3);
            TypeSlimMathVector3.Name = TypeSlimMathVector3.Type.FullName;
            TypeSlimMathVector3.SizeOf = sizeof(SlimMath.Vector3);

            // Use SlimMath.Vector4
            TypeSlimMathVector4 = new CSharpStruct();
            TypeSlimMathVector4.Type = typeof(SlimMath.Vector4);
            TypeSlimMathVector4.Name = TypeSlimMathVector4.Type.FullName;
            TypeSlimMathVector4.SizeOf = sizeof(SlimMath.Vector4);

            // Use SlimMath.Color4
            TypeSlimMathColor4 = new CSharpStruct();
            TypeSlimMathColor4.Type = typeof(SlimMath.Color4);
            TypeSlimMathColor4.Name = TypeSlimMathColor4.Type.FullName;
            TypeSlimMathColor4.SizeOf = sizeof(SlimMath.Color4);

            // Use SlimMath.Quaternion
            TypeSlimMathQuaternion = new CSharpStruct();
            TypeSlimMathQuaternion.Type = typeof(SlimMath.Quaternion);
            TypeSlimMathQuaternion.Name = TypeSlimMathQuaternion.Type.FullName;
            TypeSlimMathQuaternion.SizeOf = sizeof(SlimMath.Quaternion);

            // Use SlimMath.Plane
            TypeSlimMathPlane = new CSharpStruct();
            TypeSlimMathPlane.Type = typeof(SlimMath.Plane);
            TypeSlimMathPlane.Name = TypeSlimMathPlane.Type.FullName;
            TypeSlimMathPlane.SizeOf = sizeof(SlimMath.Plane);

            // SlimDX2.Rectangle
            TypeSlimDX2Rectangle = new CSharpStruct();
            TypeSlimDX2Rectangle.Name = Global.Name + ".Rectangle";
            TypeSlimDX2Rectangle.SizeOf = 4 * 4;

            // Use SlimDX.RectangleF struct
            TypeSlimDX2RectangleF = new CSharpStruct();
            TypeSlimDX2RectangleF.Name = Global.Name + ".RectangleF";
            TypeSlimDX2RectangleF.SizeOf = 4 * 4;

            // Use SlimDX2.Windows.WaveFormat
            var waveFormatEx = new CSharpStruct();
            waveFormatEx.Name = Global.Name + ".Windows.WaveFormat";
            waveFormatEx.HasMarshalType = true;
            waveFormatEx.SizeOf = 18;
            gen.MapCppTypeToCSharpType("WAVEFORMATEX", waveFormatEx);

            // Use SlimDX2.Windows.WaveFormat
            var waveFormatExtensible = new CSharpStruct();
            waveFormatExtensible.Name = Global.Name + ".Windows.WaveFormatExtensible";
            waveFormatExtensible.HasMarshalType = true;
            waveFormatExtensible.SizeOf = 18;
            waveFormatExtensible.HasCustomNew = true;
            gen.MapCppTypeToCSharpType("WAVEFORMATEXTENSIBLE", waveFormatExtensible);

            gen.MoveStructToInner(@"^TEXTMETRIC\w$", "Win32");
            gen.MoveStructToInner(@"^LOGFONTW$", "Win32");

            gen.MapCppTypeToCSharpType("SLIMDX_COLOR4", TypeSlimMathColor4);
            gen.MapCppTypeToCSharpType("POINT", TypeSystemDrawingPoint);
            gen.MapCppTypeToCSharpType("RECT", TypeSlimDX2Rectangle); //Global.Name + ".Rectangle", 4 * 4, false, true);
            gen.MapCppTypeToCSharpType("HRESULT", typeof(int));
            gen.MapCppTypeToCSharpType("UINT64", typeof(long));
            gen.MapCppTypeToCSharpType("FILETIME", typeof(long));
            gen.MapCppTypeToCSharpType("COLORREF", typeof(int));  // TODO: use real ColorRGBA8
            gen.MapCppTypeToCSharpType("GUID", typeof(Guid));
            gen.MapCppTypeToCSharpType("CLSID", typeof(Guid));            
            gen.MapCppTypeToCSharpType("DWORD", typeof(int));

            // Setup FunctionCallback for __function__stdcall
            TypeSlimDX2FunctionCallback = new CSharpStruct();
            TypeSlimDX2FunctionCallback.Name = Global.Name + ".FunctionCallback";
            TypeSlimDX2FunctionCallback.SizeOf = 8;
            gen.MapCppTypeToCSharpType("__function__stdcall", TypeSlimDX2FunctionCallback);

            gen.MapCppTypeToCSharpType("SIZE", TypeSystemDrawingSize);
            group.TagVisibility<CppStruct>("^Win32$", Visibility.Internal);

            // --------------------------------------------------------------------------------------------------------
            // Global/Win32 Interfaces
            // --------------------------------------------------------------------------------------------------------
            TypeIUnknown = new CSharpInterface(new CppInterface { Name = "IUnknown" });
            TypeIUnknown.Name = Global.Name + ".ComObject";
            TypeIUnknown.Add(new CSharpMethod(new CppMethod { Name = "QueryInterface" }));
            TypeIUnknown.Add(new CSharpMethod(new CppMethod { Name = "AddRef" }));
            TypeIUnknown.Add(new CSharpMethod(new CppMethod { Name = "Release" }));

            // Global object
            gen.MapCppTypeToCSharpType(TypeIUnknown.CppElement.Name, TypeIUnknown);

            // --------------------------------------------------------------------------------------------------------
            // Global/Win32 Functions
            // --------------------------------------------------------------------------------------------------------

            // --------------------------------------------------------------------------------------------------------
            // Global Rename
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppField>(@"^.*::(.*)DescW?$", "$1Description");
            group.TagName<CppField>(@"^.*::(.*)Desc1$", "$1Description1");
            group.TagName<CppMethod>(@"^.*::(.*)DescW?$", "$1Description");
            group.TagName<CppMethod>(@"^.*::(.*)Desc1$", "$1Description1");
            group.TagName<CppMethod>(@"^.*GetType$", "GetTypeInfo");

            // Expand sub part between underscore
            gen.RenameTypePart("^DESC$", "Description");
            gen.RenameTypePart("^CBUFFER$", "ConstantBuffer");
            gen.RenameTypePart("^TBUFFER$", "TextureBuffer");
            gen.RenameTypePart("^BUFFEREX$", "ExtendedBuffer");
            gen.RenameTypePart("^FUNC$", "Function");
            gen.RenameTypePart("^FLAG$", "Flags");
            gen.RenameTypePart("^SRV$", "ShaderResourceView");
            gen.RenameTypePart("^DSV$", "DepthStencilView");
            gen.RenameTypePart("^RTV$", "RenderTargetView");
            gen.RenameTypePart("^UAV$", "UnorderedAccessView");
            gen.RenameTypePart("^TEXTURE1D$", "Texture1D");
            gen.RenameTypePart("^TEXTURE2D$", "Texture2D");
            gen.RenameTypePart("^TEXTURE3D$", "Texture3D");
            gen.RenameTypePart("^TEX1D$", "Texture1D");
            gen.RenameTypePart("^TEX2D$", "Texture2D");
            gen.RenameTypePart("^TEX3D$", "Texture3D");
            gen.RenameTypePart("^TEXCUBE$", "TextureCube");
            gen.RenameTypePart("^TEX2DMS$", "Texture2DMultisampled");
            gen.RenameTypePart("^RWTEXTURE1D$", "RWTexture1D");
            gen.RenameTypePart("^RWTEXTURE2D$", "RWTexture2D");
            gen.RenameTypePart("^RWTEXTURE3D$", "RWTexture3D");
            gen.RenameTypePart("^RWTEXTURE1DARRAY$", "RWTexture1DArray");
            gen.RenameTypePart("^RWTEXTURE2DARRAY$", "RWTexture2DArray");
            gen.RenameTypePart("^TEXTURE1DARRAY$", "Texture1DArray");
            gen.RenameTypePart("^TEXTURE2DARRAY$", "Texture2DArray");
            gen.RenameTypePart("^TEXTURE3DARRAY$", "Texture3DArray");
            gen.RenameTypePart("^TEXTURE2DMS$", "Texture2DMultisampled");
            gen.RenameTypePart("^TEXTURE2DMSARRAY$", "Texture2DMultisampledArray");
            gen.RenameTypePart("^RWBUFFER$", "RWBuffer");
            gen.RenameTypePart("^RWBYTEADDRESS$", "RWByteAddress");
            gen.RenameTypePart("^UINT8$", "UInt8");
            gen.RenameTypePart("^UINT$", "UInt");
            gen.RenameTypePart("^SINT$", "SInt");
            gen.RenameTypePart("^UNORM$", "UNorm");
            gen.RenameTypePart("^SNORM$", "SNorm");
            gen.RenameTypePart("^SRGB$", "SRgb");
            gen.RenameTypePart("^ADJ$", "WithAdjency");
            gen.RenameTypePart("^IA$", "InputAssembly");
            gen.RenameTypePart("^SO$", "StreamOutput");
            gen.RenameTypePart("^OP$", "Operation");
            gen.RenameTypePart("^INV$", "Inverse");
            gen.RenameTypePart("^SRC$", "Source");
            gen.RenameTypePart("^SRC1$", "SecondarySource");
            gen.RenameTypePart("^SAT$", "Saturate");
            gen.RenameTypePart("^DEST$", "Destination");
            gen.RenameTypePart("^REV$", "Reverse");
            gen.RenameTypePart("^MAX$", "Maximum");
            gen.RenameTypePart("^MIN$", "Minimum");
            gen.RenameTypePart("^INCR$", "Increment");
            gen.RenameTypePart("^DECR$", "Decrement");
            gen.RenameTypePart("^SRGB$", "StandardRgb");
            gen.RenameTypePart("^STENCILOP$", "StencilOperation");
            gen.RenameTypePart("^SUBRESOURCE$", "SubResource");
            gen.RenameTypePart("^CBF$", "ConstantBuffer");
            gen.RenameTypePart("^INFO$", "Information");
            gen.RenameTypePart("^DESC1$", "Description1");
            gen.RenameTypePart("^DISASM$", "Disassembly");
        }
    }
}