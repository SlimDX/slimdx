using System;
using System.Collections.Generic;
using System.Windows.Forms;
using SampleFramework;
using System.Runtime.InteropServices;
using SlimDX;
using SlimDX.Direct3D9;
using System.Drawing;

namespace SimpleTriangle
{
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
        static Sample Sample;
        static VertexBuffer Vertices;

        [STAThread]
        static void Main()
        {
            Sample = new Sample("SlimDX - Simple Triangle Sample", true, 800, 600);
            Sample.MainLoop += new EventHandler(sample_MainLoop);

            Vertices = new VertexBuffer(Sample.Device, 3 * Vertex.SizeBytes, Usage.WriteOnly, VertexFormat.None, Pool.Managed);
            DataStream stream = Vertices.Lock(0, 0, LockFlags.None);
            stream.WriteRange(BuildVertexData());
            Vertices.Unlock();

            Sample.Run();

            Vertices.Dispose();
            Sample.Dispose();
        }

        static Vertex[] BuildVertexData()
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

        static void sample_MainLoop(object sender, EventArgs e)
        {
            Sample.Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);
            Sample.Device.BeginScene();

            Sample.Device.SetStreamSource(0, Vertices, 0, Vertex.SizeBytes);
            Sample.Device.VertexFormat = Vertex.Format;
            Sample.Device.DrawPrimitives(PrimitiveType.TriangleList, 0, 1);

            Sample.Device.EndScene();
            Sample.Device.Present();
        }
    }
}