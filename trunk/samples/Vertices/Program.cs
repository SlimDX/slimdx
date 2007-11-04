//-----------------------------------------------------------------------------
// Tutorial 02: Vertices
//
// Desc: In this tutorial, we are rendering some Vertices. This introduces the
//       concept of the vertex buffer, a Direct3D object used to store
//       Vertices. Vertices can be defined any way we want by defining a
//       custom structure and a custom FVF (flexible vertex format). In this
//       tutorial, we are using Vertices that are transformed (meaning they
//       are already in 2D window coordinates) and lit (meaning we are not
//       using Direct3D lighting, but are supplying our own colors).
//
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

namespace Vertices
{
    // Our custom vertex
    [StructLayout(LayoutKind.Sequential)]
    struct Vertex
    {
        public Vector4 PositionRhw;
        public int Color;

        public static int SizeBytes
        {
            get { return Marshal.SizeOf(typeof(Vertex)); }
        }

        public static VertexFormat Format
        {
            get { return VertexFormat.PositionRhw | VertexFormat.Diffuse; }
        }
    }

    static class Program
    {
        public static RenderForm Window;        // Window used for rendering.
        public static Device D3DDevice;         // Direct3D device.
        public static VertexBuffer Vertices;    // Vertex buffer object used to hold vertices.

        /// <summary>
        /// Builds an array of vertices that can be written to a vertex buffer.
        /// </summary>
        /// <returns>An array of vertices.</returns>
        private static Vertex[] BuildVertexData()
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

        /// <summary>
        /// Initializes the various Direct3D objects we'll be using.
        /// </summary>
        public static void Initialize()
        {
            // Create a new PresentParameters object and fill in the necessary fields.
            PresentParameters presentParams = new PresentParameters();

            // Below are the required bare mininum, needed to initialize the D3D device.
            presentParams.BackBufferHeight = Window.ClientRectangle.Height;         // BackBufferHeight, set to  the Window's height.
            presentParams.BackBufferWidth = Window.ClientRectangle.Width;           // BackBufferWidth, set to  the Window's width.
            presentParams.DeviceWindowHandle = Window.Handle;                       // DeviceWindowHandle, set to  the Window's handle.

            // Create the device.
            D3DDevice = new Device(0, DeviceType.Hardware, Window.Handle, CreateFlags.HardwareVertexProcessing, presentParams);

            // Create the vertex buffer and fill with the triangle vertices. (Transformed)
            Vertices = new VertexBuffer(D3DDevice, 3 * Vertex.SizeBytes, Usage.WriteOnly, VertexFormat.None, Pool.Managed);
            DataStream stream = Vertices.Lock(0, 0, LockFlags.None);
            stream.WriteRange(BuildVertexData());
            Vertices.Unlock();
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
        /// Renders all of our geometry each frame.
        /// </summary>
        public static void MainLoop()
        {
            // Clear the backbuffer to a black color.
            D3DDevice.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);

            // Begin the scene.
            D3DDevice.BeginScene();

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
                Initialize();

                Window.PrepareMainLoop();
                Application.Run(Window);

                Cleanup();
            }
        }
    }
}