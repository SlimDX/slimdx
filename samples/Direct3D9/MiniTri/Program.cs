using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;

namespace MiniTri
{
    [StructLayout(LayoutKind.Sequential)]
    struct Message
    {
        public IntPtr hWnd;
        public uint msg;
        public IntPtr wParam;
        public IntPtr lParam;
        public uint time;
        public Point p;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct Vertex
    {
        public Vector4 PositionRhw;
        public int Color;
    }

    static class Program
    {
        static Form RenderForm;
        static Device Device;
        static VertexBuffer Vertices;

        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool PeekMessage(out Message msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax, uint flags);

        static bool AppStillIdle
        {
            get
            {
                Message msg;
                return !PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }

        [STAThread]
        static void Main()
        {
            RenderForm = new Form();
            RenderForm.ClientSize = new Size(800, 600);
            RenderForm.Text = "SlimDX - MiniTri Direct3D9 Sample";

            Direct3D.Initialize();

            PresentParameters presentParams = new PresentParameters();
            presentParams.BackBufferHeight = RenderForm.ClientRectangle.Height;
            presentParams.BackBufferWidth = RenderForm.ClientRectangle.Width;
            presentParams.DeviceWindowHandle = RenderForm.Handle;

            Device = new Device(0, DeviceType.Hardware, RenderForm.Handle, CreateFlags.HardwareVertexProcessing, presentParams);
            Vertices = new VertexBuffer(Device, 3 * 20, Usage.WriteOnly, VertexFormat.None, Pool.Managed);
            
            DataStream stream = Vertices.Lock(0, 0, LockFlags.None);
            Vertex[] vertexData = new Vertex[3];
            vertexData[0].PositionRhw = new Vector4(400.0f, 100.0f, 0.5f, 1.0f);
            vertexData[0].Color = Color.Red.ToArgb();
            vertexData[1].PositionRhw = new Vector4(650.0f, 500.0f, 0.5f, 1.0f);
            vertexData[1].Color = Color.Blue.ToArgb();
            vertexData[2].PositionRhw = new Vector4(150.0f, 500.0f, 0.5f, 1.0f);
            vertexData[2].Color = Color.Green.ToArgb();
            stream.WriteRange(vertexData);
            Vertices.Unlock();

            Application.Idle += new EventHandler(Application_Idle);
            Application.Run(RenderForm);

            if (Vertices != null)
                Vertices.Dispose();
            if (Device != null)
                Device.Dispose();

            RenderForm.Dispose();
        }

        static void Application_Idle(object sender, EventArgs e)
        {
            while (AppStillIdle)
            {
                Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);
                Device.BeginScene();
                Device.SetStreamSource(0, Vertices, 0, 20);
                Device.VertexFormat = VertexFormat.PositionRhw | VertexFormat.Diffuse;
                Device.DrawPrimitives(PrimitiveType.TriangleList, 0, 1);
                Device.EndScene();
                Device.Present();
            }
        }
    }
}