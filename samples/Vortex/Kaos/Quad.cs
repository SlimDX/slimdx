/*
* Copyright (c) 2007 SlimDX Group
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
using System.Text;
using SlimDX;
using SlimDX.Direct3D9;

namespace Demo.Kaos
{
	class Quad : Mesh
	{
		public Quad(Device device)
		{
			EnsureVertexBuffer(device);
		}
		public void PrepareRender(Device device)
		{
			device.VertexFormat = TexturedVertex.Format;
			device.SetStreamSource(0, mVertices, 0, TexturedVertex.SizeBytes);
		}

		public void Render(Device device)
		{
			device.DrawPrimitives(PrimitiveType.TriangleFan, 0, 2);
		}

		private static void EnsureVertexBuffer(Device device)
		{
			if(mVertices == null)
			{
				const int NumVertices = 4;
				TexturedVertex[] QuadVertices = new TexturedVertex[NumVertices];
				float halfSize = 0.5f;
				QuadVertices[0] = new TexturedVertex(new Vector3(-halfSize, halfSize, 0), new Vector2(0.0f, 0.0f));
				QuadVertices[1] = new TexturedVertex(new Vector3(-halfSize, -halfSize, 0), new Vector2(0.0f, 1.0f));
				QuadVertices[2] = new TexturedVertex(new Vector3(halfSize, -halfSize, 0), new Vector2(1.0f, 1.0f));
				QuadVertices[3] = new TexturedVertex(new Vector3(halfSize, halfSize, 0), new Vector2(1.0f, 0.0f));

				mVertices = new VertexBuffer(device, TexturedVertex.SizeBytes * NumVertices, Usage.None, 0, Pool.Managed);
				DataStream vertices = mVertices.Lock(0, 0, LockFlags.Discard);

				vertices.WriteRange(QuadVertices, 0, NumVertices);

				mVertices.Unlock();
			}
		}

		private static VertexBuffer mVertices;
	}
}
