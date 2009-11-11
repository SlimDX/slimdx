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

using System;
using System.Collections.Generic;
using System.Reflection;

using SlimDX;
using SlimDX.Direct3D9;

namespace SlimDX.SampleFramework
{
	/// <summary>
	/// Provides functionality to render a user interface using Direct3D9.
	/// </summary>
	public class UserInterfaceRenderer9 : UserInterfaceRenderer
	{
		#region Public Interface

		/// <summary>
		/// Initializes a new instance of the <see cref="UserInterfaceRenderer9"/> class.
		/// </summary>
		/// <param name="device">The device.</param>
		/// <param name="width">The width of the renderable area.</param>
		/// <param name="height">The height of the renderable area.</param>
		public UserInterfaceRenderer9( Device device, int width, int height )
		{
			if( device == null ) 
				throw new ArgumentNullException( "device" );
			if( width < 0 )
				throw new ArgumentException("Value must be positive.","width");
			if (height < 0)
				throw new ArgumentException("Value must be positive.", "height");
			
			this.device = device;
			halfWidth = width / 2;
			halfHeight = height / 2;
			
			lineBuffer = new DynamicPrimitiveBuffer9(device, PrimitiveTopology.LineList);
		}
		
		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		/// <param name="disposeManagedResources">If true, managed resources should be
		/// disposed of in addition to unmanaged resources.</param>
		protected override void Dispose(bool disposeManagedResources)
		{
			if (disposeManagedResources)
			{
				lineBuffer.Dispose();
			}

			base.Dispose(disposeManagedResources);
		}
		
		/// <summary>
		/// In a derived class, implements logic to flush all pending rendering commands.
		/// </summary>
		protected override void Flush()
		{
			Matrix offset = Matrix.Translation(-1.0f, 1.0f, 0.0f);
			Matrix scale = Matrix.Scaling(1.0f / halfWidth, -1.0f / halfHeight, 1.0f);

			device.SetTransform(TransformState.World, scale * offset);
			device.SetTransform(TransformState.View, Matrix.Identity);
			device.SetTransform(TransformState.Projection, Matrix.Identity);

			device.SetRenderState(RenderState.Lighting, false);
			
			lineBuffer.Render();
			lineBuffer.Clear();
		}

		/// <summary>
		/// Renders a line.
		/// </summary>
		/// <param name="x0">The X coordinate of the first point.</param>
		/// <param name="y0">The Y coordinate of the first point.</param>
		/// <param name="color0">The color of the first point.</param>
		/// <param name="x1">The X coordinate of the second point.</param>
		/// <param name="y1">The Y coordinate of the second point.</param>
		/// <param name="color1">The color of the second point.</param>
		internal override void RenderLine(int x0, int y0, Color4 color0, int x1, int y1, Color4 color1)
		{
			lineBuffer.Add(new ColoredVertex(
				new Vector3(x0, y0, 0.0f),
				color0.ToArgb()
			));

			lineBuffer.Add(new ColoredVertex(
				new Vector3(x1, y1, 0.0f),
				color1.ToArgb()
			));
		}

		#endregion
		#region Implementation Detail

		Device device;
		int halfWidth;
		int halfHeight;
		
		DynamicPrimitiveBuffer9 lineBuffer;	
		
		#endregion
	}
}
