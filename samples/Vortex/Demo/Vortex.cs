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
using Demo.Kaos;
using SlimDX.Direct3D9;

namespace Demo.Demo
{
	class Vortex : Entity
	{
		public Vortex(Device device)
		{
			mQuad = new Quad(device);
			if(DefaultSurfaceProperties == null)
				DefaultSurfaceProperties = new SurfaceProperties(device, null, "vortex.fx");

			SurfaceProperties = DefaultSurfaceProperties;
		}

		public override void Render(SlimDX.Direct3D9.Device device)
		{
			base.Render(device);

			if(SurfaceProperties != null)
			{
				if(SurfaceProperties.Effect != null)
					SetEffectParameters(SurfaceProperties.Effect);
				SurfaceProperties.RenderWith(device, mQuad);
			}
		}

		public SurfaceProperties SurfaceProperties;
		private Quad mQuad;

		private static SurfaceProperties DefaultSurfaceProperties;
	}
}
