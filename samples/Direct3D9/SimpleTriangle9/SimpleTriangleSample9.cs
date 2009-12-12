/*
* Copyright (c) 2007-2009 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

using System.Drawing;
using System.Runtime.InteropServices;

using SlimDX;
using SlimDX.Direct3D9;

using SlimDX.SampleFramework;

namespace SimpleTriangle9 {
	/// <summary>
	/// Demonstrates how to render a simple colored triangle with Direct3D9.
	/// </summary>
	class SimpleTriangle9Sample : Sample {
		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		/// <param name="disposeManagedResources">If true, managed resources should be
		/// disposed of in addition to unmanaged resources.</param>
		protected override void Dispose( bool disposeManagedResources ) {
			if( disposeManagedResources ) {
				vertexBuffer.Dispose();
			}

			base.Dispose( disposeManagedResources );
		}

		protected override void OnInitialize() {
			DeviceSettings9 settings = new DeviceSettings9 {
				AdapterOrdinal = 0,
				CreationFlags = CreateFlags.HardwareVertexProcessing,
				Width = WindowWidth,
				Height = WindowHeight
			};

			context = InitializeDevice( settings );

			vertexBuffer = new VertexBuffer(
				context.Device,
				3 * Marshal.SizeOf( typeof( ColoredVertex ) ),
				Usage.WriteOnly,
				VertexFormat.None,
				Pool.Managed
			);

			DataStream stream = vertexBuffer.Lock( 0, 0, LockFlags.None );
			stream.WriteRange( new[] {
				new ColoredVertex( new Vector3(0.0f, 0.5f, 0.5f), Color.Red.ToArgb() ),
				new ColoredVertex( new Vector3(0.5f, -0.5f, 0.5f), Color.Blue.ToArgb() ),
				new ColoredVertex( new Vector3(-0.5f, -0.5f, 0.5f), Color.Green.ToArgb() ),
			} );

			vertexBuffer.Unlock();

			// Since this sample does not use any lights, disable lighting (otherwise the
			// triangle will appear flat black).
			context.Device.SetRenderState( RenderState.Lighting, false );
		}

		protected override void OnRenderBegin() {
			context.Device.Clear( ClearFlags.Target | ClearFlags.ZBuffer, new Color4( 0.3f, 0.3f, 0.3f ), 1.0f, 0 );
			context.Device.BeginScene();
		}

		protected override void OnRender() {
			context.Device.SetStreamSource( 0, vertexBuffer, 0, Marshal.SizeOf( typeof( ColoredVertex ) ) );
			context.Device.VertexFormat = VertexFormat.Position | VertexFormat.Diffuse;
			context.Device.DrawPrimitives( PrimitiveType.TriangleList, 0, 1 );
		}

		protected override void OnRenderEnd() {
			context.Device.EndScene();
			context.Device.Present();
		}

		#region Implementation Detail

		DeviceContext9 context;
		VertexBuffer vertexBuffer;

		#endregion
	}
}
