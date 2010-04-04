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
                BufferUsage = Usage.RenderTargetOutput,
                IsWindowed = true,
                OutputWindow = window.Handle,
                SampleDescription = new SampleDescription { Count = 1, Quality = 0 },
                SwapEffect = SwapEffect.Discard
            };

            IDevice10 device;
            ISwapChainDXGI swapChain;
            api.CreateDeviceAndSwapChain(null, DriverType10.Hardware, DeviceCreationFlags10.None, swapChainDescription, out device, out swapChain);

            var backbuffer = swapChain.GetBuffer<ITexture2D10>(0);
            var renderTargetView = device.CreateRenderTargetView(backbuffer);

            var buffer = device.CreateBuffer(new BufferDescription10 {
                    SizeInBytes = 3 * 32,
                    BindFlags = BindFlags10.VertexBuffer,
                    CpuAccessFlags = CpuAccessFlags10.None,
                    Usage = Usage10.Default,
                    OptionFlags = OptionFlags10.None
                },
                new[] {
                    new Vector4(0.0f, 0.5f, 0.5f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),
				    new Vector4(0.5f, -0.5f, 0.5f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),
				    new Vector4(-0.5f, -0.5f, 0.5f, 1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f)
                }
            );

            // At this point we have our render target, which holds a reference to the backbuffer, so we can release our reference to the backbuffer.
            backbuffer.Release();

            device.OMSetRenderTarget(renderTargetView, null);
            device.IASetPrimitiveTopology(PrimitiveTopology10.TriangleList);
            device.IASetVertexBuffer(0, new VertexBufferBinding10(buffer, 32, 0));

            MessagePump.Run(window, () => {
                device.RSSetViewport(new Viewport10(0, 0, window.ClientWidth, window.ClientHeight, 0.0f, 1.0f));
                device.ClearRenderTargetView(renderTargetView, Color.Red);
                swapChain.Present(0, PresentFlags.None);
            });

            device.Release();
            swapChain.Release();
            renderTargetView.Release();
            buffer.Release();
        }
    }
}
