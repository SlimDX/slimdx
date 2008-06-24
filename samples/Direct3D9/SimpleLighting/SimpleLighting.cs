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
        // constants
        const int InitialWidth = 1024;
        const int InitialHeight = 768;

        // variables
        Camera camera = new Camera();
        Mesh mesh;
        bool pointLight;
        Light light;
        Vector3 position;

        /// <summary>
        /// Gets the Direct3D device.
        /// </summary>
        /// <value>The Direct3D device.</value>
        public Device Device
        {
            get { return GraphicsDeviceManager.Device9; }
        }

        /// <summary>
        /// Gets or sets the clear color.
        /// </summary>
        /// <value>The clear color.</value>
        public Color ClearColor
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SimpleLighting"/> class.
        /// </summary>
        public SimpleLighting()
        {
            // initialize the clear color
            ClearColor = Color.Black;

            // set up the window
            Window.ClientSize = new Size(InitialWidth, InitialHeight);
            Window.Text = "SlimDX - Simple Lighting Sample";
            Window.KeyDown += Window_KeyDown;
            Window.MouseClick += Window_MouseClick;

            // create the light
            CreateLight();

            // initialize the camera
            camera.FieldOfView = (float)(Math.PI / 4);
            camera.NearPlane = 0.0f;
            camera.FarPlane = 40.0f;
            camera.Location = new Vector3(0.0f, 7.0f, 20.0f);
            camera.Target = Vector3.Zero;

            // create the Direct3D device
            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D9, true, InitialWidth, InitialHeight);
        }

        /// <summary>
        /// Handles the MouseClick event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        void Window_MouseClick(object sender, MouseEventArgs e)
        {
            // toggle the point light setting each time the mouse is clicked
            if (e.Button == MouseButtons.Left)
                pointLight = !pointLight;

            // recreate the light structure
            CreateLight();
        }

        /// <summary>
        /// Handles the KeyDown event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            // F1 toggles between full screen and windowed mode
            // Escape quits the application
            if (e.KeyCode == Keys.F1)
                GraphicsDeviceManager.ToggleFullScreen();
            else if (e.KeyCode == Keys.Escape)
                Exit();
        }

        /// <summary>
        /// Loads graphical resources.
        /// </summary>
        protected override void LoadContent()
        {
            // create the mesh
            mesh = Mesh.CreateTeapot(Device);
            mesh.ComputeNormals();

            // update the camera
            camera.AspectRatio = (float)Window.Width / Window.Height;

            // enable lighting
            Device.SetRenderState(RenderState.Lighting, true);
            Device.SetLight(0, light);
            Device.EnableLight(0, true);

            // set the material
            Material material = new Material();
            material.Diffuse = Color.FloralWhite;
            material.Ambient = Color.MidnightBlue;
            Device.Material = material;
        }

        /// <summary>
        /// Unloads graphical resources.
        /// </summary>
        protected override void UnloadContent()
        {
            // release the mesh
            mesh.Dispose();
        }

        /// <summary>
        /// Called when a frame is ready to be drawn.
        /// </summary>
        /// <param name="gameTime">The time passed since the last frame.</param>
        protected override void Draw(GameTime gameTime)
        {
            // start the scene
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();

            // calculate the position
            position = new Vector3((float)Math.Sin(0.4f * gameTime.TotalGameTime), (float)Math.Sin(0.8f * gameTime.TotalGameTime), (float)Math.Cos(0.16f * gameTime.TotalGameTime));

            // set the light direction
            Point cursorPosition = Window.PointToClient(Cursor.Position);
            light.Direction = Vector3.Normalize(new Vector3(cursorPosition.X - (Window.Width / 2), cursorPosition.Y - (Window.Height / 2), -10.0f) - position);
            Device.SetLight(0, light);

            // set the transforms
            Device.SetTransform(TransformState.World, Matrix.Translation(position));
            Device.SetTransform(TransformState.View, camera.ViewMatrix);
            Device.SetTransform(TransformState.Projection, camera.ProjectionMatrix);

            // draw the mesh
            mesh.DrawSubset(0);

            // end the scene
            Device.EndScene();
        }

        /// <summary>
        /// Creates the light.
        /// </summary>
        void CreateLight()
        {
            // create the light as a directional light first
            light = new Light();
            light.Type = LightType.Directional;
            light.Diffuse = Color.ForestGreen;
            light.Ambient = Color.GhostWhite;
            light.Direction = new Vector3(0.0f, 0.0f, 1.0f);

            // if the light is a point light, specialize it as such
            if (pointLight)
            {
                // create a point light
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
