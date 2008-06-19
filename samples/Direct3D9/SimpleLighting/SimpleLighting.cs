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
    class SimpleLighting : Sample
    {
        public static float x, y, z;//Coordinates of teapot
        public static bool pointLight;
        //Defines the resolution of the screen
        const int XRES = 1024, YRES = 768;
        Mesh mesh;
        //This variable is used to keep track of the mesh movement and is 
        //incremented per frame
        float index;
        Camera camera;

        public SimpleLighting()
        {
            Initialize("Lighting and Mesh Animation Sample for SlimDX", true, XRES, YRES);
        }

        protected override void OnWindowCreated(EventArgs e)
        {
            Window.KeyDown += new KeyEventHandler(Window_KeyDown);
            Window.MouseMove += new MouseEventHandler(Window_MouseMove);
            Window.MouseClick += new MouseEventHandler(Window_MouseClick);
        }

        void Window_MouseClick(object sender, MouseEventArgs e)
        {
            pointLight = !pointLight;
        }

        void Window_KeyDown(object sender, KeyEventArgs e)
        {
            //Enables Escape Key Exit
            if (e.KeyCode == Keys.Escape)
            {
                Window.Close();
                OnDeviceDestroyed(EventArgs.Empty);
            }
        }

        void Window_MouseMove(object sender, MouseEventArgs e)
        {
            //We refresh the camera to align the light source with the mouse pointer
            if (camera == null) camera = new Camera(XRES, YRES);
            camera.SetupCamera(Device, Window, e);
        }

        protected override void OnDeviceLost(EventArgs e)
        {
            mesh.Dispose();
        }

        protected override void OnDeviceReset(EventArgs e)
        {
            camera = new Camera(XRES, YRES);
            mesh = Mesh.CreateTeapot(Device);
        }

        protected override void OnMainLoop(EventArgs e)
        {
            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);
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

            if (Device.Present() == ResultCode.DeviceLost)
                IsDeviceLost = true;
        }
    }
}
