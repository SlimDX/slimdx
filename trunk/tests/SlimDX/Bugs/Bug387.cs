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
using System.Windows.Forms;

using NUnit.Framework;

using D3D10 = SlimDX.Direct3D10;
using DXGI = SlimDX.DXGI;

namespace SlimDXTests {
	[TestFixture]
	public class Bug387Tests {
		// =========================================================================
		// Tests

		[Test]
		public void Bug387() {
			Form form = new Form();
			
			D3D10.Device device = null;
			DXGI.SwapChain swapChain = null;
			
			DXGI.SwapChainDescription swapChainDescription = new SlimDX.DXGI.SwapChainDescription();
			DXGI.ModeDescription modeDescription = new DXGI.ModeDescription();
			DXGI.SampleDescription sampleDescription = new DXGI.SampleDescription();

			modeDescription.Format = DXGI.Format.R8G8B8A8_UNorm;
			modeDescription.RefreshRate = new SlimDX.Rational( 60, 1 );
			modeDescription.Scaling = DXGI.DisplayModeScaling.Unspecified;
			modeDescription.ScanlineOrdering = DXGI.DisplayModeScanlineOrdering.Unspecified;
			modeDescription.Width = form.ClientRectangle.Width;
			modeDescription.Height = form.ClientRectangle.Height;

			sampleDescription.Count = 1;
			sampleDescription.Quality = 0;

			swapChainDescription.ModeDescription = modeDescription;
			swapChainDescription.SampleDescription = sampleDescription;
			swapChainDescription.BufferCount = 1;
			swapChainDescription.Flags = DXGI.SwapChainFlags.None;
			swapChainDescription.IsWindowed = true;
			swapChainDescription.OutputHandle = form.Handle;
			swapChainDescription.SwapEffect = DXGI.SwapEffect.Discard;
			swapChainDescription.Usage = DXGI.Usage.RenderTargetOutput;

			D3D10.Device.CreateWithSwapChain( null, D3D10.DriverType.Hardware, D3D10.DeviceCreationFlags.Debug, swapChainDescription, out device, out swapChain );

			D3D10.EffectPool pool = D3D10.EffectPool.FromFile( device, "Test Resources/Bug387_Effect.fxh", "fx_4_0", D3D10.ShaderFlags.None, D3D10.EffectFlags.None );
			D3D10.Effect effect0 = pool.AsEffect();
			D3D10.Effect effect1 = pool.AsEffect();
			
			pool.Dispose();
			swapChain.Dispose();
			device.Dispose();
			form.Dispose();

			// Verify that all objects are now cleaned up, including the entry for the implicit surface.
			Assert.AreEqual( 0, SlimDX.ObjectTable.Objects.Count );
		}
	}
}