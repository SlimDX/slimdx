//-----------------------------------------------------------------------------
// Tutorial 05: Textures
//
// Desc: So far we've rendered our geometry using just lights and materials.
//       3D objects look much more realistic when texture-mapped. 
//       Textures can be thought of as a sort of wallpaper, 
//       that is shrinkwrapped to fit a texture. Textures are
//       typically loaded from image files. SlimDX's Texture class provides 
//       a function to load Like a vertex buffer, Textures have
//       Lock() and Unlock() functions to access (read or write) the image
//       data. Textures have a width, height, miplevel, and pixel format. The
//       miplevel is for "mipmapped" Textures, an advanced performance-
//       enhancing feature which uses lower resolutions of the texture for
//       objects in the distance where detail is less noticeable. The pixel
//       format determines how the colors are stored in a texel. The most
//       common formats are the 16-bit R5G6B5 format (5 bits of red, 6-bits of
//       green and 5 bits of blue) and the 32-bit A8R8G8B8 format (8 bits each
//       of alpha, red, green, and blue).
//
//       Textures are associated with geometry through texture coordinates.
//       Each vertex has one or more sets of texture coordinates, which are
//       named tu and tv and range from 0.0 to 1.0. Texture coordinates can be
//       supplied by the geometry, or can be automatically generated using
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

namespace Textures
{
    // Vertex structure.
    [StructLayout(LayoutKind.Sequential)]
    struct Vertex
    {
        public Vector3 Position;
        public float Tu;
        public float Tv;

        public static int SizeBytes
        {
            get { return Marshal.SizeOf(typeof(Vertex)); }
        }

        public static VertexFormat Format
        {
            get { return VertexFormat.Position | VertexFormat.Texture1; }
        }
    }

    static class Program
    {
        // Variables
        public static RenderForm Window;        // Window used for rendering.
        public static Device D3DDevice;         // Direct3D device.
        public static VertexBuffer Vertices;    // Vertex buffer object used to hold vertices.
        public static Texture Image;            // Texture object to hold the image loaded from a file.
        public static int time;                 // Used for rotation caculations.
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

            // Create the vertex buffer and fill with the triangle vertices. (Non-indexed)
            // Remember 3 vetices for a triangle, 2 tris per quad = 6.
            Vertices = new VertexBuffer(D3DDevice, 6 * Vertex.SizeBytes, Usage.WriteOnly, VertexFormat.None, Pool.Managed);
            DataStream stream = Vertices.Lock(0, 0, LockFlags.None);
            stream.WriteRange(BuildVertexData());
            Vertices.Unlock();

            // Create the texture.
            // Be sure to either use the full path, or place the texture in the app's root dir.
            // If DX can't find the file you will get an InvalidDataException.
            Image = Texture.FromFile(D3DDevice, "earth.bmp");

            // Turn off culling, so we see the front and back of the triangle
            D3DDevice.SetRenderState(RenderState.CullMode, Cull.None);

            // Turn off lighting
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
            UpdateMatrices();

            // Render the vertex buffer.
            D3DDevice.SetStreamSource(0, Vertices, 0, Vertex.SizeBytes);
            D3DDevice.VertexFormat = Vertex.Format;
            
            // Setup our texture. Using Textures introduces the texture stage states,
            // which govern how Textures get blended together (in the case of multiple
            // Textures) and lighting information.
            D3DDevice.SetTexture(0, Image);

            // The sampler states govern how smooth the texture is displayed.
            D3DDevice.SetSamplerState(0, SamplerState.MinFilter, TextureFilter.Linear);
            D3DDevice.SetSamplerState(0, SamplerState.MagFilter, TextureFilter.Linear);
            D3DDevice.SetSamplerState(0, SamplerState.MipFilter, TextureFilter.Linear);

            // Now drawing 2 triangles, for a quad.
            D3DDevice.DrawPrimitives(PrimitiveType.TriangleList, 0, 2);

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
            if (Image != null)
                Image.Dispose();

            if (Vertices != null)
                Vertices.Dispose();

            if (D3DDevice != null)
                D3DDevice.Dispose();
        }

        /// <summary>
        /// Builds an array of vertices that can be written to a vertex buffer.
        /// This time we will be creating 6 vertices for a textured quad.
        /// </summary>
        /// <returns>An array of vertices.</returns>
        private static Vertex[] BuildVertexData()
        {
            Vertex[] vertexData = new Vertex[6];

            vertexData[0].Position = new Vector3(-1.0f, 1.0f, 0.0f);   
            vertexData[0].Tu = 0.0f;
            vertexData[0].Tv = 0.0f;
                
            vertexData[1].Position = new Vector3(-1.0f, -1.0f, 0.0f);   
            vertexData[1].Tu = 0.0f;
            vertexData[1].Tv = 1.0f;

            vertexData[2].Position = new Vector3(1.0f, 1.0f, 0.0f);     
            vertexData[2].Tu = 1.0f;
            vertexData[2].Tv = 0.0f;

            vertexData[3].Position = new Vector3(-1.0f, -1.0f, 0.0f);    
            vertexData[3].Tu = 0.0f;
            vertexData[3].Tv = 1.0f;

            vertexData[4].Position = new Vector3(1.0f, -1.0f, 0.0f);
            vertexData[4].Tu = 1.0f;
            vertexData[4].Tv = 1.0f;

            vertexData[5].Position = new Vector3(1.0f, 1.0f, 0.0f);
            vertexData[5].Tu = 1.0f;
            vertexData[5].Tv = 0.0f;

            return vertexData;
        }

        /// <summary>
        /// Sets up the world, view, and projection transform Matrices.
        /// </summary>
        public static void UpdateMatrices()
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