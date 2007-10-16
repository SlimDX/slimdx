using System;
using System.Windows.Forms;
using System.Drawing;
using System.Runtime.InteropServices;

using SlimDX;
using SlimDX.Direct3D;
using SlimDX.Direct3D9;

namespace SimpleTriangle
{
	[StructLayout( LayoutKind.Sequential )]
	struct Vertex
	{
		public Vector4 PositionRhw;
		public int Color;

		public static int SizeBytes
		{
			get { return Marshal.SizeOf( typeof( Vertex ) ); }
		}

		public static VertexFormat Format
		{
			get { return VertexFormat.PositionRhw | VertexFormat.Diffuse; }
		}
	}

	static class Program
	{
		public static bool RunLoop = true;
		public static RenderForm RenderForm;

		public static Device Device;
		public static VertexBuffer Vertices;

		/// <summary>
		/// Builds an array of vertices that can be written to a vertex buffer.
		/// </summary>
		/// <returns>An array of vertices.</returns>
		private static Vertex[] BuildVertexData()
		{
			Vertex[] vertexData = new Vertex[3];

			vertexData[0].PositionRhw = new Vector4( 400.0f, 100.0f, 0.5f, 1.0f );
			vertexData[0].Color = Color.Red.ToArgb();

			vertexData[1].PositionRhw = new Vector4( 650.0f, 500.0f, 0.5f, 1.0f );
			vertexData[1].Color = Color.Blue.ToArgb();

			vertexData[2].PositionRhw = new Vector4( 150.0f, 500.0f, 0.5f, 1.0f );
			vertexData[2].Color = Color.Green.ToArgb();

			return vertexData;
		}

		/// <summary>
		/// Initializes the various Direct3D objects we'll be using.
		/// </summary>
		public static void Initialize()
		{
			PresentParameters presentParams = new PresentParameters();
			presentParams.BackBufferHeight = RenderForm.ClientRectangle.Height;
			presentParams.BackBufferWidth = RenderForm.ClientRectangle.Width;
			presentParams.DeviceWindowHandle = RenderForm.Handle;

			Device = new Device( 0, DeviceType.Hardware, RenderForm.Handle, CreateFlags.HardwareVertexProcessing, presentParams );

			Vertices = new VertexBuffer( Device, 3 * Vertex.SizeBytes, Usage.WriteOnly, VertexFormat.None, Pool.Managed );
			DataStream stream = Vertices.Lock( 0, 0, LockFlags.None );
			stream.WriteRange( BuildVertexData() );
			Vertices.Unlock();
		}

		/// <summary>
		/// Disposes all of the Direct3D objects we created.
		/// </summary>
		public static void KillAll()
		{
			if( Vertices != null )
				Vertices.Dispose();

			if( Device != null )
				Device.Dispose();
		}

		/// <summary>
		/// Renders all of our geometry each frame.
		/// </summary>
		public static void MainLoop()
		{
			Device.Clear( ClearFlags.Target | ClearFlags.ZBuffer | ClearFlags.Stencil, Color.Black, 1.0f, 0 );
			Device.BeginScene();

			Device.SetStreamSource( 0, Vertices, 0, Vertex.SizeBytes );
			Device.VertexFormat = Vertex.Format;
			Device.DrawPrimitives( PrimitiveType.TriangleList, 0, 1 );

			Device.EndScene();
			Device.Present();
		}

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			try
			{
				//NOTE: This Initialize call is *required* in all SlimDX based D3D9 apps.
				Direct3D.Initialize();
			}
			catch( DirectXException ex )
			{
				MessageBox.Show( ex.Message );
				return;
			}

			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault( false );

			using( RenderForm = new RenderForm() )
			{
				Initialize();

				RenderForm.PrepareMainLoop();
				Application.Run( RenderForm );

				KillAll();
			}
		}
	}
}