using System;
using System.Collections.Generic;
using System.Text;
using SampleFramework;
using SlimDX.Direct3D9;
using System.Drawing;
using SlimDX;
using System.Windows.Forms;

/***********************************************************************************
 * Program: Lighting and Mesh Animation Sample for SlimDX                          *
 * Desc:    This program displays a moving mesh (the teapot) with the mouse pointer*
 *          acting as a light source.                                              *
 * Author:  Rohit Jain                                                             *
 * Dated:   6/3/2008                                                               *
 * *********************************************************************************/


namespace SimpleLighting
{
    class SimpleLighting : Game
    {
        public static float x, y, z;//Coordinates of teapot
        public static bool pointLight;
        Mesh mesh;
        //This variable is used to keep track of the mesh movement and is 
        //incremented per frame
        float index;
        Camera camera;

        // constants
        const int InitialWidth = 1024;
        const int InitialHeight = 768;

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

        public SimpleLighting()
        {
            // initialize the clear color
            ClearColor = Color.Black;

            Window.Text = "SlimDX - Simple Lighting Sample";
            Window.ClientSize = new Size(InitialWidth, InitialHeight);

            Window.KeyDown += new KeyEventHandler(Window_KeyDown);
            Window.MouseMove += new MouseEventHandler(Window_MouseMove);
            Window.MouseClick += new MouseEventHandler(Window_MouseClick);

            // create the Direct3D device
            GraphicsDeviceManager.ChangeDevice(DeviceVersion.Direct3D9, true, InitialWidth, InitialHeight);
        }

        void Window_MouseClick(object sender, MouseEventArgs e)
        {
            pointLight = !pointLight;
        }

        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            //Enables Escape Key Exit
            if (e.KeyCode == Keys.Escape)
                Exit();
        }

        void Window_MouseMove(object sender, MouseEventArgs e)
        {
            //We refresh the camera to align the light source with the mouse pointer
            if (camera == null) camera = new Camera(Window.ClientSize.Width, Window.ClientSize.Height);
            camera.SetupCamera(Device, Window, e);
        }

        protected override void UnloadContent()
        {
            mesh.Dispose();
        }

        protected override void LoadContent()
        {
            camera = new Camera(Window.ClientSize.Width, Window.ClientSize.Height);
            mesh = Mesh.CreateTeapot(Device);
        }

        protected override void Draw(GameTime gameTime)
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, ClearColor, 1.0f, 0);
            Device.BeginScene();
            mesh.ComputeNormals();
            //Setting up world transformation matrix
            Matrix matTranslate;
            matTranslate = Matrix.Identity;
            //Can change speed of teapot from here
            index += 0.05f;
            //Putting in place some complicated movements
            x = 5.0f * (float)Math.Sin(0.4f * index);
            y = 3.0f * (float)Math.Sin(0.8f * index);
            z = 3.0f * (float)Math.Cos(0.16f * index);
            matTranslate.M41 = x;
            matTranslate.M42 = y;
            matTranslate.M43 = z;
            Device.SetTransform(TransformState.World, matTranslate);

            mesh.DrawSubset(0);
            Device.EndScene();
        }
    }
}
