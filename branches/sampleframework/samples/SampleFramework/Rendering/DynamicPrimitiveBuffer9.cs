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

using SlimDX.Direct3D9;

namespace SlimDX.SampleFramework
{
	/// <summary>
	/// An automatically-resizing buffer of primitive data, implemented using Direct3D 9.
	/// </summary>
	public class DynamicPrimitiveBuffer9 : IDisposable
	{
		#region Public Interface

		/// <summary>
		/// Initializes a new instance of the <see cref="DynamicPrimitiveBuffer9"/> class.
		/// </summary>
		/// <param name="device">The device.</param>
		/// <param name="topology">The primitive topology.</param>
		public DynamicPrimitiveBuffer9(Device device, PrimitiveTopology topology)
		{
			if( device == null )
				throw new ArgumentNullException("device");
				
			switch (topology)
			{
				case PrimitiveTopology.PointList:
					primitiveType = PrimitiveType.PointList;
					verticesPerPrimitive = 1;
					break;
				case PrimitiveTopology.LineList:
					primitiveType = PrimitiveType.LineList;
					verticesPerPrimitive = 2;
					break;
				case PrimitiveTopology.TriangleList:
					primitiveType = PrimitiveType.TriangleList;
					verticesPerPrimitive = 3;
					break;
				default:
					throw new ArgumentException(string.Format("'{0}' is not a valid primitive topology for a primitive buffer.", topology), "topology");
			}

			buffer = CreateBuffer(device, bufferSize);
		}

		/// <summary>
		/// Performs object finalization.
		/// </summary>
		~DynamicPrimitiveBuffer9()
		{
			Dispose(false);
		}
		
		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		/// <summary>
		/// Adds a vertex to the buffer.
		/// </summary>
		/// <param name="vertex">The vertex.</param>
		public void Add(ColoredVertex vertex)
		{
			vertices.Add(vertex);
			if (vertices.Count > bufferSize)
			{
				bufferSize *= 2;
				buffer = CreateBuffer(buffer.Device, bufferSize);
			}

			needsCommit = true;
		}

		/// <summary>
		/// Clears the buffer of all primitive data.
		/// </summary>
		public void Clear()
		{
			// Note that we do not require a recommit here, since trying to render an
			// empty buffer will just no-op. It doesn't matter what's in the real buffer
			// on the card at this point, so there's no sense in locking it.
			vertices.Clear();
		}

		/// <summary>
		/// Renders the buffer.
		/// </summary>
		public void Render()
		{
			if (needsCommit)
			{
				DataStream data = buffer.Lock(0, 0, LockFlags.Discard);

				for (int vertexIndex = 0; vertexIndex < vertices.Count; ++vertexIndex)
				{
					data.Write(vertices[vertexIndex].Position);
					data.Write(vertices[vertexIndex].Color);
				}

				buffer.Unlock();
				needsCommit = false;
			}

			if (vertices.Count > 0)
			{
				buffer.Device.VertexFormat = VertexFormat.Position | VertexFormat.Diffuse;
				buffer.Device.SetStreamSource(0, buffer, 0, ColoredVertex.SizeInBytes);
				buffer.Device.DrawPrimitives(primitiveType, 0, vertices.Count / verticesPerPrimitive);
			}
		}

		#endregion
		#region Implementation Detail

		const int initialSize = 32;

		PrimitiveType primitiveType;
		int verticesPerPrimitive;

		VertexBuffer buffer;
		int bufferSize = initialSize;
		List<ColoredVertex> vertices = new List<ColoredVertex>();

		bool needsCommit = false;
		
		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		/// <param name="disposeManagedResources">If true, managed resources should be
		/// disposed of in addition to unmanaged resources.</param>
		void Dispose(bool disposeManagedResources)
		{
			if (disposeManagedResources)
			{
				buffer.Dispose();
			}
		}
		/// <summary>
		/// Creates the buffer.
		/// </summary>
		/// <param name="device">The device.</param>
		/// <param name="size">The size (in vertices).</param>
		/// <returns>The created buffer.</returns>
		static VertexBuffer CreateBuffer(Device device, int size)
		{
			return new VertexBuffer(device, size * ColoredVertex.SizeInBytes, Usage.Dynamic, VertexFormat.Position | VertexFormat.Diffuse, Pool.Default);
		}

		#endregion
	}
}
