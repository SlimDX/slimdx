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
using NUnit.Framework;
using SlimDX;
using SlimDX.Direct3D9;
using System.Windows.Forms;

namespace SlimDXTests {
	[TestFixture]
	public class Bug420Tests {
		// =========================================================================
		// Tests

		[Test]
		public void Bug420() {
			Form form = new Form();
			Direct3D direct3d = new Direct3D();
			Device device;
			PresentParameters presentParameters;

			presentParameters = new PresentParameters();
			presentParameters.DeviceWindowHandle = form.Handle;

			CreateFlags createFlags = CreateFlags.SoftwareVertexProcessing;
			device = new Device( direct3d, 0, DeviceType.Reference, form.Handle, createFlags, presentParameters );

			// The device and the "D3D" object should be the only allocated COM objects.
			Assert.AreEqual( 2, ObjectTable.Objects.Count );

			// Create render target               
			Texture renderTarget = new Texture( device, 256, 256, 1, Usage.RenderTarget, Format.A8B8G8R8, Pool.Default );
			Surface depthSurface = Surface.CreateDepthStencil( device, 256, 256, Format.D24X8, MultisampleType.None, 0, true );
		
			// Get surface level. This should be an ancillary object to the render target.
			Surface surface = renderTarget.GetSurfaceLevel(0);

			// Dispose all data
			renderTarget.Dispose();
			depthSurface.Dispose();

			device.Dispose();
			direct3d.Dispose();
			form.Dispose();

			// Verify that all objects are now cleaned up, including the entry for the implicit surface.
			Assert.AreEqual( 0, ObjectTable.Objects.Count );
		}
	}
}