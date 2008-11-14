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
using System.Drawing;
using System.Windows.Forms;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace SimpleTriangle
{
    class SimpleTriangleSample : Game
    {
        const int InitialWidth = 800;
        const int InitialHeight = 600;

        VertexBuffer vertices;

        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        public Color ClearColor
        {
            get;
            set;
        }

        public SimpleTriangleSample()
        {
            ClearColor = Color.Black;

            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Simple Triangle Sample";
            Window.KeyDown += Window_KeyDown;

            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D9, true, InitialWidth, InitialHeight);
        }

        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            // F1 toggles between full screen and windowed mode
            // Escape quits the application
            if (e.KeyCode == Keys.F1)
                GraphicsDeviceManager.ToggleFullScreen();
            else if (e.KeyCode == Keys.Escape)
                Exit();
        }

        protected override void LoadContent()
        {
            vertices = new VertexBuffer(Device, 3 * TransformedColoredVertex.SizeInBytes, Usage.WriteOnly, VertexFormat.None, Pool.Managed);
            DataStream stream = vertices.Lock(0, 0, LockFlags.None);
            stream.WriteRange(BuildVertexData());
            vertices.Unlock();
        }

        protected override void UnloadContent()
        {
            if (vertices != null)
                vertices.Dispose();
            vertices = null;
        }

        protected override void Draw(GameTime gameTime)
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            Device.SetStreamSource(0, vertices, 0, TransformedColoredVertex.SizeInBytes);
            Device.VertexFormat = TransformedColoredVertex.Format;
            Device.DrawPrimitives(PrimitiveType.TriangleList, 0, 1);

            Device.EndScene();
        }

        static TransformedColoredVertex[] BuildVertexData()
        {
            return new TransformedColoredVertex[3] {
                new TransformedColoredVertex(new Vector4(400.0f, 100.0f, 0.5f, 1.0f), Color.Red.ToArgb()),
                new TransformedColoredVertex(new Vector4(650.0f, 500.0f, 0.5f, 1.0f), Color.Blue.ToArgb()),
                new TransformedColoredVertex(new Vector4(150.0f, 500.0f, 0.5f, 1.0f), Color.Green.ToArgb()) };
        }
    }
}
