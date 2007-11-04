//-----------------------------------------------------------------------------
// Tutorial 01: CreateDevice
//
// Desc: This is the first tutorial for using SlimDX. 
//       In this tutorial, all we are doing is creating a Direct3D9
//       device and using it to clear the window.
//-----------------------------------------------------------------------------
// System
using System;
using System.Drawing;
using System.Collections.Generic;
using System.Windows.Forms;

// Be sure to add a reference to the SlimDX library in VS Express and Studio versions.
using SlimDX;
using SlimDX.Direct3D;
using SlimDX.Direct3D9;

namespace CreateDevice
{
    static class Program
    {
        // Variables
        public static RenderForm Window;    // Window used for rendering.
        public static Device D3DDevice;     // Direct3D device.


        /// <summary>
        /// Initializes the various Direct3D objects we'll be using.
        /// </summary>
        public static void InitializeD3D()
        {
            // Create a new PresentParameters object and fill in the necessary fields.
            PresentParameters presentParams = new PresentParameters();

            // Below are the required bare mininum, needed to initialize the D3D device.
            presentParams.BackBufferHeight = Window.ClientRectangle.Height;         // BackBufferHeight, set to  the Window's height.
            presentParams.BackBufferWidth = Window.ClientRectangle.Width;           // BackBufferWidth, set to  the Window's width.
            presentParams.DeviceWindowHandle = Window.Handle;                       // DeviceWindowHandle, set to  the Window's handle.

            // Create the device.
            D3DDevice = new Device(0, DeviceType.Hardware, Window.Handle, CreateFlags.HardwareVertexProcessing, presentParams);
        }

        /// <summary>
        /// Renders all of our geometry each frame.
        /// </summary>
        public static void MainLoop()
        {
            // Clear the backbuffer to a black color.
            D3DDevice.Clear(ClearFlags.Target, Color.Black, 1.0f, 0);

            // Begin the scene.
            D3DDevice.BeginScene();

            // TODO : Perform some scene rendering.

            // End the scene.
            D3DDevice.EndScene();

            // Present the backbuffer contents to the screen.
            D3DDevice.Present();
        }

		/// <summary>
		/// Disposes all of the Direct3D objects we created.
		/// </summary>
        public static void Cleanup()
        {
            if (D3DDevice != null)
                D3DDevice.Dispose();
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //NOTE: This Initialize call is *required* in all SlimDX based D3D9 apps.
            Direct3D.Initialize();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            using (Window = new RenderForm())
            {
                // Initialize Direct3D
                InitializeD3D();

                // Initialize app. messaging events.
                Window.PrepareMainLoop();

                // Run the app.
                Application.Run(Window);

                // Cleanup app.
                Cleanup();
            }
        }
    }
}