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
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;
using System.Drawing;

namespace Water
{
    class WaterSample : Sample
    {
        RoomEntity room;
        RoomEntity fountain;
        WaterEntity water;

        Matrix viewMatrix = Matrix.Identity;
        Matrix projectionMatrix = Matrix.Identity;
        Vector3 position = new Vector3(450, 350, 750);

        public WaterSample()
        {
            Initialize("SlimDX - Water Sample", true, 800, 600);
        }

        protected override void OnWindowCreated(EventArgs e)
        {
            Window.KeyDown += new KeyEventHandler(Window_KeyDown);
        }

        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.F1)
                ToggleFullScreen();
            else if (e.KeyCode == Keys.Up)
                position.Y += 10;
            else if (e.KeyCode == Keys.Down)
                position.Y -= 10;
            else if (e.KeyCode == Keys.Left)
                position.X += 10;
            else if (e.KeyCode == Keys.Right)
                position.X -= 10;
            else if (e.KeyCode == Keys.A)
                position.Z += 10;
            else if (e.KeyCode == Keys.Z)
                position.Z -= 10;
        }

        protected override void OnDeviceLost(EventArgs e)
        {
            if (room != null)
                room.Dispose();

            if (fountain != null)
                fountain.Dispose();

            if (water != null)
                water.Dispose();
        }

        protected override void OnDeviceReset(EventArgs e)
        {
            projectionMatrix = Matrix.PerspectiveFovLH((float)Math.PI / 4, 1.0f, 1.0f, 5000.0f);

            Device.SetTransform(TransformState.Projection, projectionMatrix);

            Device.SetRenderState(RenderState.DiffuseMaterialSource, ColorSource.Color1);
            Device.SetRenderState(RenderState.SourceBlend, Blend.One);
            Device.SetRenderState(RenderState.DestinationBlend, Blend.One);

            room = new RoomEntity(Device, "Resources/Models/room.x", "Resources/Shaders/bump.fx",
                "Resources/Textures/rockwall.dds", "Resources/Textures/rockwall_normal.dds");

            fountain = new RoomEntity(Device, "Resources/Models/fountain.x", "Resources/Shaders/bump.fx",
                "Resources/Textures/rockwall.dds", "Resources/Textures/rockwall_normal.dds");

            water = new WaterEntity(Device, "Resources/Models/water.x", "Resources/Shaders/water.fx",
                "Resources/Textures/water.dds", "Resources/Textures/bricks.dds");
        }

        protected override void OnMainLoop(EventArgs e)
        {
            viewMatrix = Matrix.LookAtLH(new Vector3(position.X, position.Y, position.Z),
                new Vector3(0.0f, 0.0f, 0.0f),
                new Vector3(0.0f, 1.0f, 0.0f));

            room.Update(new Vector3(0, 0, 0), viewMatrix, projectionMatrix);
            fountain.Update(new Vector3(0, -800, 0), viewMatrix, projectionMatrix);
            water.Update(new Vector3(0, -80, 0), viewMatrix, projectionMatrix);

            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);
            Device.BeginScene();

            room.Render(Device);
            fountain.Render(Device);
            water.Render(Device);

            Device.EndScene();

            if (Device.Present() == Error.DeviceLost)
                IsDeviceLost = true;
        }
    }
}
