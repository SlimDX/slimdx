/*
* Copyright (c) 2007-2009 SlimDX Group
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

using System;
using System.Windows.Forms;
using DXGI = SlimDX.DXGI;
using D3D9 = SlimDX.Direct3D9;
using SlimDX.Direct3D10;

namespace SimpleModel10
{
    class XLoader : IDisposable
    {
        public XLoader()
        {
            CreateNullDevice();
        }

        #region IDisposable
        ~XLoader()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
        }

        private void Dispose(bool disposeManagedObjects)
        {
            if (disposeManagedObjects)
            {
                device9.Dispose();
                form.Dispose();
            }
        }
        #endregion

        public Mesh CreateMesh(Device device, D3D9.Mesh mesh9, out InputElement[] outDecls)
        {
            var inDecls = mesh9.GetDeclaration();
            outDecls = new InputElement[inDecls.Length - 1];
            ConvertDecleration(inDecls, outDecls);

            var flags = MeshFlags.None;
            if ((mesh9.CreationOptions & D3D9.MeshFlags.Use32Bit) != 0)
                flags = MeshFlags.Has32BitIndices;

            var mesh = new Mesh(device, outDecls, D3D9.DeclarationUsage.Position.ToString().ToUpper(), mesh9.VertexCount, mesh9.FaceCount, flags);

            ConvertIndexBuffer(mesh9, mesh);
            ConvertVertexBuffer(mesh9, mesh);
            ConfigureAttributeTable(mesh9, mesh);

            mesh.GenerateAdjacencyAndPointRepresentation(0);
            mesh.Optimize(MeshOptimizeFlags.Compact | MeshOptimizeFlags.AttributeSort | MeshOptimizeFlags.VertexCache);

            mesh.Commit();
            return mesh;
        }

        public Mesh LoadFile(Device device, string filename, out InputElement[] outDecls)
        {
            using (var mesh9 = D3D9.Mesh.FromFile(device9, filename, D3D9.MeshFlags.SystemMemory))
            {
                return CreateMesh(device, mesh9, out outDecls);
            }
        }

        #region Implementation Details
        private static void ConfigureAttributeTable(D3D9.BaseMesh inMesh, Mesh outMesh)
        {
            var inAttribTable = inMesh.GetAttributeTable();

            if (inAttribTable == null || inAttribTable.Length == 0)
            {
                outMesh.SetAttributeTable(new[] {new MeshAttributeRange {
                    FaceCount = outMesh.FaceCount,
                    FaceStart = 0,
                    Id = 0,
                    VertexCount = outMesh.VertexCount,
                    VertexStart = 0
                }});
            }
            else
            {
                var outAttribTable = new MeshAttributeRange[inAttribTable.Length];
                for (var i = 0; i < inAttribTable.Length; ++i)
                {
                    outAttribTable[i].Id = inAttribTable[i].AttribId;
                    outAttribTable[i].FaceCount = inAttribTable[i].FaceCount;
                    outAttribTable[i].FaceStart = inAttribTable[i].FaceStart;
                    outAttribTable[i].VertexCount = inAttribTable[i].VertexCount;
                    outAttribTable[i].VertexStart = inAttribTable[i].VertexStart;
                }
                outMesh.SetAttributeTable(outAttribTable);
            }

            outMesh.GenerateAttributeBufferFromTable();
        }

        private static void ConvertIndexBuffer(D3D9.BaseMesh inMesh, Mesh outMesh)
        {
            using (var inStream = inMesh.LockIndexBuffer(D3D9.LockFlags.None))
            using (var outBuffer = outMesh.GetIndexBuffer())
            {
                using (var outStream = outBuffer.Map())
                {
                    if ((outMesh.Flags & MeshFlags.Has32BitIndices) != 0)
                        outStream.WriteRange(inStream.ReadRange<int>(inMesh.FaceCount * 3));
                    else
                        outStream.WriteRange(inStream.ReadRange<short>(inMesh.FaceCount * 3));
                }
                outBuffer.Unmap();
            }
            inMesh.UnlockIndexBuffer();
        }

        private static void ConvertVertexBuffer(D3D9.BaseMesh inMesh, Mesh outMesh)
        {
            using (var inStream = inMesh.LockVertexBuffer(D3D9.LockFlags.None))
            using (var outBuffer = outMesh.GetVertexBuffer(0))
            {
                using (var outStream = outBuffer.Map())
                {
                    outStream.WriteRange(inStream.ReadRange<byte>(inMesh.VertexCount * inMesh.BytesPerVertex));
                }
                outBuffer.Unmap();
            }
            inMesh.UnlockIndexBuffer();
        }

        private static void ConvertDecleration(D3D9.VertexElement[] inDecls, InputElement[] outDecls)
        {
            for (var i = 0; i < inDecls.Length - 1; ++i)
            {
                outDecls[i].SemanticName = ConvertSemanticName(inDecls[i].Usage);
                outDecls[i].SemanticIndex = inDecls[i].UsageIndex;
                outDecls[i].AlignedByteOffset = inDecls[i].Offset;
                outDecls[i].Slot = inDecls[i].Stream;
                outDecls[i].Classification = InputClassification.PerVertexData;
                outDecls[i].InstanceDataStepRate = 0;
                outDecls[i].Format = ConvertFormat(inDecls[i].Type);
            }
        }

        private static string ConvertSemanticName(D3D9.DeclarationUsage usage)
        {
            switch (usage)
            {
                case D3D9.DeclarationUsage.TextureCoordinate:
                    return "TEXCOORD";
                case D3D9.DeclarationUsage.PositionTransformed:
                    return "POSITIONT";
                case D3D9.DeclarationUsage.TessellateFactor:
                    return "TESSFACTOR";
                case D3D9.DeclarationUsage.PointSize:
                    return "PSIZE";
                default:
                    return usage.ToString().ToUpper();
            }
        }

        private static DXGI.Format ConvertFormat(D3D9.DeclarationType type)
        {
            switch (type)
            {
                case D3D9.DeclarationType.Float1: return DXGI.Format.R32_Float;
                case D3D9.DeclarationType.Float2: return DXGI.Format.R32G32_Float;
                case D3D9.DeclarationType.Float3: return DXGI.Format.R32G32B32_Float;
                case D3D9.DeclarationType.Float4: return DXGI.Format.R32G32B32A32_Float;
                case D3D9.DeclarationType.Color: return DXGI.Format.R8G8B8A8_UNorm;
                case D3D9.DeclarationType.Ubyte4: return DXGI.Format.R8G8B8A8_UInt;
                case D3D9.DeclarationType.Short2: return DXGI.Format.R16G16_SInt;
                case D3D9.DeclarationType.Short4: return DXGI.Format.R16G16B16A16_SInt;
                case D3D9.DeclarationType.UByte4N: return DXGI.Format.R8G8B8A8_UNorm;
                case D3D9.DeclarationType.Short2N: return DXGI.Format.R16G16_SNorm;
                case D3D9.DeclarationType.Short4N: return DXGI.Format.R16G16B16A16_SNorm;
                case D3D9.DeclarationType.UShort2N: return DXGI.Format.R16G16_UNorm;
                case D3D9.DeclarationType.UShort4N: return DXGI.Format.R16G16B16A16_UNorm;
                case D3D9.DeclarationType.UDec3: return DXGI.Format.R10G10B10A2_UInt;
                case D3D9.DeclarationType.Dec3N: return DXGI.Format.R10G10B10A2_UNorm;
                case D3D9.DeclarationType.HalfTwo: return DXGI.Format.R16G16_Float;
                case D3D9.DeclarationType.HalfFour: return DXGI.Format.R16G16B16A16_Float;
                default: return DXGI.Format.Unknown;
            }
        }

        private void CreateNullDevice()
        {
            form = new Form();
            using (var direct3D = new D3D9.Direct3D())
            {
                var displayMode = direct3D.GetAdapterDisplayMode(0);
                device9 = new D3D9.Device(direct3D, 0, D3D9.DeviceType.NullReference, form.Handle, D3D9.CreateFlags.HardwareVertexProcessing, new D3D9.PresentParameters
                {
                    BackBufferCount = 1,
                    BackBufferFormat = displayMode.Format,
                    BackBufferHeight = 1,
                    BackBufferWidth = 1,
                    SwapEffect = D3D9.SwapEffect.Copy,
                    Windowed = true
                });
            }
        }

        private Form form;
        private D3D9.Device device9;
        #endregion
    }
}