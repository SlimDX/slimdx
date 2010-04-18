using System.Runtime.InteropServices;
using SlimDX;
using SlimDX.Direct3D10;
using SlimDX.DXGI;
using System.Drawing;
using SlimDX.Windows;

namespace MiniTri10 {
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector4 {
        public Vector4(float x, float y, float z, float w) {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        public float X;
        public float Y;
        public float Z;
        public float W;
    }

    class Program {
        static void Main() {
            var window = new Window("SlimDX - MiniTri10");

            var api = Loader.LoadDirect3D10();
            var swapChainDescription = new SwapChainDescription() {
                BufferDescription = new DisplayModeDescription {
                    Format = Format.R8G8B8A8_UNORM,
                    Width = window.ClientSize.Width,
                    Height = window.ClientSize.Height,
                    RefreshRate = new Rational { Numerator = 60, Denominator = 1 },
                    Scaling = DisplayModeScale.Unspecified,
                    ScanlineOrdering = DisplayModeScanlineOrder.Unspecified
                },
                BufferCount = 1,
                BufferUsage = SlimDX.DXGI.Usage.RenderTargetOutput,
                IsWindowed = true,
                OutputWindow = window.Handle,
                SampleDescription = new SampleDescription { Count = 1, Quality = 0 },
                SwapEffect = SwapEffect.Discard
            };

            IDevice device;
            ISwapChain swapChain;
            api.CreateDeviceAndSwapChain(null, DriverType.Hardware, DeviceCreationFlags.None, swapChainDescription, out device, out swapChain);

            var backbuffer = swapChain.GetBuffer<ITexture2D>(0);
            var renderTargetView = device.CreateRenderTargetView(backbuffer);

            var buffer = device.CreateBuffer(new BufferDescription {
                    SizeInBytes = 3 * 32,
                    BindFlags = BindFlags.VertexBuffer,
                    CpuAccessFlags = CpuAccessFlags.None,
                    Usage = SlimDX.Direct3D10.Usage.Default,
                    OptionFlags = OptionFlags.None
                },
                new[] {
                    new Vector4(0.0f, 0.5f, 0.5f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),
				    new Vector4(0.5f, -0.5f, 0.5f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),
				    new Vector4(-0.5f, -0.5f, 0.5f, 1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f)
                }
            );

            var inputElements = new InputElement[] {
                new InputElement {Name = "POSITION", Index = 0, Format = Format.R32G32B32A32_Float, Slot = 0, AlignedByteOffset = 0, InputClassification = InputClassification.VertexData, InstanceDataStep = 0},
                new InputElement {Name = "COLOR", Index = 0, Format = Format.R32G32B32A32_Float, Slot = 0, AlignedByteOffset = 16, InputClassification = InputClassification.VertexData, InstanceDataStep = 0},
            };

            // At this point we have our render target, which holds a reference to the backbuffer, so we can release our reference to the backbuffer.
            backbuffer.Release();

            var effect = api.CreateEffect(device, "SimpleTriangle10.fx", "fx_4_0", ShaderFlags.None, EffectFlags.None);
            var pass = effect.GetTechniqueByIndex(0).GetPassByIndex(0);
            var desc = pass.GetDescription();

            var inputLayout = device.CreateInputLayout(inputElements, desc.ShaderSignature);

            device.OMSetRenderTarget(renderTargetView, null);
            device.IASetPrimitiveTopology(PrimitiveTopology.TriangleList);
            device.IASetVertexBuffer(0, new VertexBufferBinding(buffer, 32, 0));
            device.IASetInputLayout(inputLayout);

            MessagePump.Run(window, () => {
                device.RSSetViewport(new Viewport(0, 0, window.ClientWidth, window.ClientHeight, 0.0f, 1.0f));
                device.ClearRenderTargetView(renderTargetView, Color.Red);

                pass.Apply();

                device.Draw(3, 0);

                swapChain.Present(0, PresentFlags.None);
            });

            inputLayout.Release();
            effect.Release();
            device.Release();
            swapChain.Release();
            renderTargetView.Release();
            buffer.Release();
        }
    }
}
