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
using SlimDX2.Direct3D;
using SlimDX2.Direct3D10;
using SlimDX2.DXGI;
using Device = SlimDX2.Direct3D10.Device;
using Device1 = SlimDX2.Direct3D10.Device1;
using DriverType = SlimDX2.Direct3D10.DriverType;


namespace SlimDX2.Samples
{
    /// <summary>
    /// Root class for Direct3D10(.1) Demo App
    /// </summary>
    public class Direct3D10DemoApp : DemoApp
    {
        Device1 _device;
        SwapChain _swapChain;
        Texture2D _backBuffer;

        /// <summary>
        /// Returns the device
        /// </summary>
        public Device1 Device
        {
            get
            {
                return _device;
            }
        }

        /// <summary>
        /// Returns the backbuffer used by the SwapChain
        /// </summary>
        public Texture2D BackBuffer
        {
            get
            {
                return _backBuffer;
            }
        }

        protected override void Initialize(DemoConfiguration demoConfiguration)
        {
            // SwapChain description
            var desc = new SwapChainDescription()
            {
                BufferCount = 1,
                BufferDescription =
                    new ModeDescription(demoConfiguration.Width, demoConfiguration.Height,
                                        new Rational(60, 1), Format.R8G8B8A8_UNorm),
                Windowed = true,
                OutputWindow = DisplayHandle,
                SampleDescription = new SampleDescription(1, 0),
                SwapEffect = SwapEffect.Discard,
                BufferUsage = Usage.RenderTargetOutput
            };

            // Create Device and SwapChain
            Device1.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.Debug | DeviceCreationFlags.BgraSupport, desc, FeatureLevel.Level_10_0, out _device, out _swapChain);

            // Ignore all windows events
            Factory factory = _swapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(DisplayHandle, WindowAssociationFlags.IgnoreAll);

            // New RenderTargetView from the backbuffer
            _backBuffer = Texture2D.FromSwapChain<Texture2D>(_swapChain, 0);

        }

        protected override void EndDraw()
        {
            _swapChain.Present(0, PresentFlags.None);
        }
    }
}