using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;
using SlimDX.Windows;

namespace MiniTri {
    struct Vertex {
        public Vector4 Position;
        public int Color;
    }

    static class Program {
        [STAThread]
        static void Main() {
            var form = new Form( "SlimDX - MiniTri Direct3D9 Sample" );
            var device = new Device( new Direct3D(), 0, DeviceType.Hardware, form.Handle, CreateFlags.HardwareVertexProcessing, new PresentParameters() {
                BackBufferWidth = form.ClientSize.Width,
                BackBufferHeight = form.ClientSize.Height
            } );

            var vertices = new VertexBuffer( device, 3 * 20, Usage.WriteOnly, VertexFormat.None, Pool.Managed );
            vertices.Lock( 0, 0, LockFlags.None ).WriteRange( new[] {
                new Vertex() { Color = Color.Red.ToArgb(), Position = new Vector4(400.0f, 100.0f, 0.5f, 1.0f) },
                new Vertex() { Color = Color.Blue.ToArgb(), Position = new Vector4(650.0f, 500.0f, 0.5f, 1.0f) },
                new Vertex() { Color = Color.Green.ToArgb(), Position = new Vector4(150.0f, 500.0f, 0.5f, 1.0f) }
            } );
            vertices.Unlock();

            MessagePump.Run( form, () => {
                device.Clear( ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0 );
                device.BeginScene();

                device.SetStreamSource( 0, vertices, 0, 20 );
                device.VertexFormat = VertexFormat.PositionRhw | VertexFormat.Diffuse;
                device.DrawPrimitives( PrimitiveType.TriangleList, 0, 1 );

                device.EndScene();
                device.Present();
            } );

            foreach( var item in ObjectTable.Objects )
                item.Dispose();
        }
    }
}