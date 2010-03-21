using System;
using SlimDX;
using SlimDX.Direct3D10;
using SlimDX.DXGI;
using System.Windows.Forms;
using System.Drawing;
using System.Reflection;

namespace MiniTri10 {
    class Program {
        static void Main( string[] args ) {
            var form = new Form {
                Text = "SlimDX - MiniTri10",
                ClientSize = new Size( 800, 600 )
            };

            var api = Loader.LoadDirect3D10();
            IDevice10 device = null;
            ISwapChainDXGI swapChain = null;
            var swapChainDescription = new SwapChainDescription() {
                BufferDescription = new DisplayModeDescription {
                    Format = Format.R8G8B8A8_UNORM,
                    Width = form.ClientSize.Width,
                    Height = form.ClientSize.Height,
                    RefreshRate = new Rational { Numerator = 60, Denominator = 1 },
                    Scaling = DisplayModeScale.Unspecified,
                    ScanlineOrdering = DisplayModeScanlineOrder.Unspecified
                },
                BufferCount = 1,
                BufferUsage = Usage.RenderTargetOutput,
                IsWindowed = true,
                OutputWindow = form.Handle,
                SampleDescription = new SampleDescription { Count = 1, Quality = 0 },
                SwapEffect = SwapEffect.Discard
            };

            api.CreateDeviceAndSwapChain( null, DriverType.Hardware, DeviceCreationFlags.Debug, swapChainDescription, out device, out swapChain );
            var backbuffer = swapChain.GetBuffer<ITexture2D10>(0);
            
            backbuffer.Release();
        }
    }
}
