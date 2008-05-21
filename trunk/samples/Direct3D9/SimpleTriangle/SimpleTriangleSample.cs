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
using System;
using System.Collections.Generic;
using System.Text;
using SampleFramework;
using SlimDX.Direct3D9;
using System.Drawing;
using SlimDX;
using System.Windows.Forms;

namespace SimpleTriangle
{
    class SimpleTriangleSample : Sample
    {
        VertexBuffer vertices;

        public SimpleTriangleSample()
        {
            Initialize("SlimDX - Simple Triangle Sample", true, 800, 600);
        }

        protected override void OnWindowCreated(EventArgs e)
        {
            Window.KeyDown += new KeyEventHandler(Window_KeyDown);
        }

        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.F1)
                ToggleFullScreen();
        }

        protected override void OnDeviceLost(EventArgs e)
        {
            if( vertices != null )
                vertices.Dispose();
        }

        protected override void OnDeviceReset(EventArgs e)
        {
            vertices = new VertexBuffer(Device, 3 * Vertex.SizeBytes, Usage.WriteOnly, VertexFormat.None, Pool.Managed);
            DataStream stream = vertices.Lock(0, 0, LockFlags.None);
            stream.WriteRange(BuildVertexData());
            vertices.Unlock();
        }

        protected override void OnMainLoop(EventArgs e)
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);
            Device.BeginScene();

            Device.SetStreamSource(0, vertices, 0, Vertex.SizeBytes);
            Device.VertexFormat = Vertex.Format;
            Device.DrawPrimitives(PrimitiveType.TriangleList, 0, 1);

            Device.EndScene();

            if (Device.Present() == ResultCode.DeviceLost)
                IsDeviceLost = true;
        }

        static Vertex[] BuildVertexData()
        {
            Vertex[] vertexData = new Vertex[3];

            vertexData[0].PositionRhw = new Vector4(400.0f, 100.0f, 0.5f, 1.0f);
            vertexData[0].Color = Color.Red.ToArgb();

            vertexData[1].PositionRhw = new Vector4(650.0f, 500.0f, 0.5f, 1.0f);
            vertexData[1].Color = Color.Blue.ToArgb();

            vertexData[2].PositionRhw = new Vector4(150.0f, 500.0f, 0.5f, 1.0f);
            vertexData[2].Color = Color.Green.ToArgb();

            return vertexData;
        }
    }
}
