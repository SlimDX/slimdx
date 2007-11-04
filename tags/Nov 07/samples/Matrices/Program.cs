//-----------------------------------------------------------------------------
// Tutorial 03: Matrices
//
// Desc: Now that we know how to create a device and render some 2D vertices,
//       this tutorial goes the next step and renders 3D geometry. To deal with
//       3D geometry we need to introduce the use of 4x4 Matrices to transform
//       the geometry with translations, rotations, scaling, and setting up our
//       camera.
//
//       Geometry is defined in model space. We can move it (translation),
//       rotate it (rotation), or stretch it (scaling) using a world transform.
//       The geometry is then said to be in world space. Next, we need to
//       position the camera, or eye point, somewhere to look at the geometry.
//       Another transform, via the view matrix, is used, to position and
//       rotate our view. With the geometry then in view space, our last
//       transform is the projection transform, which "projects" the 3D scene
//       into our 2D viewport.
//-----------------------------------------------------------------------------
// System
using System;
using System.Drawing;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Runtime.InteropServices;

// SlimDX
using SlimDX;
using SlimDX.Direct3D;
using SlimDX.Direct3D9;

namespace Matrices
{
    // Vertex structure.
    [StructLayout(LayoutKind.Sequential)]
    struct Vertex
    {
        public Vector3 Position;
        public int Color;

        public static int SizeBytes
        {
            get { return Marshal.SizeOf(typeof(Vertex)); }
        }

        public static VertexFormat Format
        {
            get { return VertexFormat.Position | VertexFormat.Diffuse; }
        }
    }

    static class Program
    {
        // Variables
        public static RenderForm Window;        // Window used for rendering.
        public static Device D3DDevice;         // Direct3D device.
        public static VertexBuffer Vertices;    // Vertex buffer object used to hold vertices.
        public static int time;               // Used for rotation caculations.
        public static float angle;              // Angle of rottaion.


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

            // Create the vertex buffer and fill with the triangle vertices.
            Vertices = new VertexBuffer(D3DDevice, 3 * Vertex.SizeBytes, Usage.WriteOnly, VertexFormat.None, Pool.Managed);
            DataStream stream = Vertices.Lock(0, 0, LockFlags.None);
            stream.WriteRange(BuildVertexData());
            Vertices.Unlock();

            // Turn off culling, so we see the front and back of the triangle
            D3DDevice.SetRenderState(RenderState.CullMode, Cull.None);

            // Turn off D3D lighting, since we are providing our own vertex colors
            D3DDevice.SetRenderState(RenderState.Lighting, false);

        }

        /// <summary>
        /// Renders all of our geometry each frame.
        /// </summary>
        public static void MainLoop()
        {
            // Clear the backbuffer to a black color.
            D3DDevice.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);

            // Begin the scene.
            D3DDevice.BeginScene();

            // Update the time and angle.
            time = Environment.TickCount % 1000;
            angle = (float)(time * (2.0f * Math.PI) / 1000.0f);

            // Setup the world, view and projection matrices.
            SetupMatrices();

            // Render the vertex buffer.
            D3DDevice.SetStreamSource(0, Vertices, 0, Vertex.SizeBytes);
            D3DDevice.VertexFormat = Vertex.Format;
            D3DDevice.DrawPrimitives(PrimitiveType.TriangleList, 0, 1);

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
            if (Vertices != null)
                Vertices.Dispose();

            if (D3DDevice != null)
                D3DDevice.Dispose();
        }

        /// <summary>
        /// Builds an array of vertices that can be written to a vertex buffer.
        /// </summary>
        /// <returns>An array of vertices.</returns>
        private static Vertex[] BuildVertexData()
        {
            Vertex[] vertexData = new Vertex[3];

            vertexData[0].Position = new Vector3(-1.0f, -1.0f, 0.0f);
            vertexData[0].Color = Color.Red.ToArgb();

            vertexData[1].Position = new Vector3(1.0f, -1.0f, 0.0f);
            vertexData[1].Color = Color.Blue.ToArgb();

            vertexData[2].Position = new Vector3(0.0f, 1.0f, 0.0f);
            vertexData[2].Color = Color.Green.ToArgb();

            return vertexData;
        }

        /// <summary>
        /// Sets up the world, view, and projection transform Matrices.
        /// </summary>
        public static void SetupMatrices()
        {
            // For our world matrix, we will just rotate the object about the y-axis.
            // Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
            // every 1000 ms. To avoid the loss of precision inherent in very high 
            // floating point numbers, the system time is modulated by the rotation 
            // period before conversion to a radian angle.
            Matrix world = Matrix.RotationY(angle);
            D3DDevice.SetTransform(TransformState.World, world);

            // Set up our view matrix. A view matrix can be defined given an eye point,
            // a point to lookat, and a direction for which way is up. Here, we set the
            // eye five units back along the z-axis and up three units, look at the
            // origin, and define "up" to be in the y-direction.
            Vector3 Eye = new Vector3(0.0f, 3.0f, -5.0f);
            Vector3 LookAt = new Vector3(0.0f, 0.0f, 0.0f);
            Vector3 Up = new Vector3(0.0f, 1.0f, 0.0f);
            Matrix view = Matrix.LookAtLH(Eye, LookAt, Up);
            D3DDevice.SetTransform(TransformState.View, view);

            // For the projection matrix, we set up a perspective transform (which
            // transforms geometry from 3D view space to 2D viewport space, with
            // a perspective divide making objects smaller in the distance). To build
            // a perpsective transform, we need the field of view (1/4 pi is common),
            // the aspect ratio, and the near and far clipping planes (which define at
            // what distances geometry should be no longer be rendered).
            float fov = (float)Math.PI / 4;
            float apsectRatio = (float)Window.ClientRectangle.Width / Window.ClientRectangle.Height;
            float nearPlane = 1.0f;
            float farPlane = 100.0f;
            Matrix projection = Matrix.PerspectiveFovLH(fov, apsectRatio, nearPlane, farPlane);
            D3DDevice.SetTransform(TransformState.Projection, projection);
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