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
using System.Drawing;
using System.Windows.Forms;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace Water
{
    class WaterSample : Game
    {
        const int InitialWidth = 800;
        const int InitialHeight = 600;

        RoomEntity room;
        RoomEntity fountain;
        WaterEntity water;

        Matrix viewMatrix = Matrix.Identity;
        Matrix projectionMatrix = Matrix.Identity;
        Vector3 position = new Vector3(450, 350, 750);

        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        public Color ClearColor
        {
            get;
            set;
        }

        public WaterSample()
        {
            ClearColor = Color.FromArgb(0, 45, 50, 170);

            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Water Sample";
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

        protected override void UnloadContent()
        {
            if (room != null)
                room.Dispose();

            if (fountain != null)
                fountain.Dispose();

            if (water != null)
                water.Dispose();

            room = null;
            fountain = null;
            water = null;
        }

        protected override void Draw(GameTime gameTime)
        {
            viewMatrix = Matrix.LookAtLH(new Vector3(position.X, position.Y, position.Z),
                new Vector3(0.0f, 0.0f, 0.0f),
                new Vector3(0.0f, 1.0f, 0.0f));

            room.Update(new Vector3(0, 0, 0), viewMatrix, projectionMatrix);
            fountain.Update(new Vector3(0, -800, 0), viewMatrix, projectionMatrix);
            water.Update(new Vector3(0, -80, 0), viewMatrix, projectionMatrix);

            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            room.Render(Device);
            fountain.Render(Device);
            water.Render(Device);

            Device.EndScene();
        }
    }
}
