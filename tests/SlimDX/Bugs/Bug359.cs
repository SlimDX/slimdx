/*
* Copyright (c) 2007-2008 SlimDX Group
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

namespace SlimDXTests
{
    [TestFixture]
    public class Bug359Tests
    {
        // =========================================================================
        // Tests

        [Test]
        public void SlimDXOnlyCase()
        {
            Form form = new Form();
            Direct3D direct3d = new Direct3D();
            Device device;
            PresentParameters presentParameters;

            presentParameters = new PresentParameters();
            presentParameters.DeviceWindowHandle = form.Handle;

            CreateFlags createFlags = CreateFlags.SoftwareVertexProcessing;
            device = new Device(direct3d, 0, DeviceType.Reference, form.Handle, createFlags, presentParameters);

            // The device and the "D3D" object should be the only allocated COM objects.
            Assert.AreEqual(2, ObjectTable.Objects.Count);

            // This will create an entry in the SlimDX object table for a COM object that was created
            // implicitly by the device. Since the user did not explicitly create it, the user should
            // not have to explicitly Dispose() of it, according to the Dispose() idiom.
            Surface surface = device.GetBackBuffer(0, 0);

            // Verify that we actually ended up with the surface in the table.
            Assert.AreEqual(3, ObjectTable.Objects.Count);

            device.Dispose();
            direct3d.Dispose();
            form.Dispose();

            // Verify that all objects are now cleaned up, including the entry for the implicit surface.
            //Assert.AreEqual( 0, ObjectTable.Objects.Count );
        }
    }
}