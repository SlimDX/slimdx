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

namespace SimpleLighting
{
    class SimpleLighting : Game
    {
        const int InitialWidth = 1024;
        const int InitialHeight = 768;

        Camera camera = new Camera();
        Mesh mesh;
        bool pointLight;
        Light light;
        Vector3 position;

        public Device Device
        {
            get { return GraphicsDeviceManager.Direct3D9.Device; }
        }

        public Color ClearColor
        {
            get;
            set;
        }

        public SimpleLighting()
        {
            ClearColor = Color.Black;

            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Simple Lighting Sample";
            Window.KeyDown += Window_KeyDown;
            Window.MouseClick += Window_MouseClick;

            CreateLight();

            camera.FieldOfView = (float)(Math.PI / 4);
            camera.NearPlane = 0.0f;
            camera.FarPlane = 40.0f;
            camera.Location = new Vector3(0.0f, 7.0f, 20.0f);
            camera.Target = Vector3.Zero;

            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D9, true, InitialWidth, InitialHeight);
        }

        void Window_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                pointLight = !pointLight;

            CreateLight();
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
            mesh = Mesh.CreateTeapot(Device);
            mesh.ComputeNormals();

            camera.AspectRatio = (float)Window.Width / Window.Height;

            Device.SetRenderState(RenderState.Lighting, true);
            Device.SetLight(0, light);
            Device.EnableLight(0, true);

            Material material = new Material();
            material.Diffuse = Color.FloralWhite;
            material.Ambient = Color.MidnightBlue;
            Device.Material = material;
        }

        protected override void UnloadContent()
        {
            mesh.Dispose();
        }

        protected override void Draw(GameTime gameTime)
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            position = new Vector3((float)Math.Sin(0.4f * gameTime.TotalGameTime), (float)Math.Sin(0.8f * gameTime.TotalGameTime), (float)Math.Cos(0.16f * gameTime.TotalGameTime));

            Point cursorPosition = Window.PointToClient(Cursor.Position);
            light.Direction = Vector3.Normalize(new Vector3(cursorPosition.X - (Window.Width / 2), cursorPosition.Y - (Window.Height / 2), -10.0f) - position);
            Device.SetLight(0, light);

            Device.SetTransform(TransformState.World, Matrix.Translation(position));
            Device.SetTransform(TransformState.View, camera.ViewMatrix);
            Device.SetTransform(TransformState.Projection, camera.ProjectionMatrix);

            mesh.DrawSubset(0);

            Device.EndScene();
        }

        void CreateLight()
        {
            // yes yes, icky fixed-function pipeline stuff
            light = new Light();
            light.Type = LightType.Directional;
            light.Diffuse = Color.ForestGreen;
            light.Ambient = Color.GhostWhite;
            light.Direction = new Vector3(0.0f, 0.0f, 1.0f);

            if (pointLight)
            {
                light.Type = LightType.Point;
                light.Range = 100.0f;
                light.Attenuation0 = 0.05f;
                light.Attenuation1 = 0.05f;
                light.Attenuation2 = 0.03f;
                light.Diffuse = Color.ForestGreen;
                light.Ambient = Color.GhostWhite;
            }
        }
    }
}
