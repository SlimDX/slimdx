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
	class Entity
	{
		public Entity()
		{
			Scale = new Vector3(1, 1, 1);
		}

		virtual public void Render(Device device)
		{
			device.SetTransform(TransformState.World, Matrix.Scaling(Scale) * Matrix.Translation(Position));
		}

		virtual public void SetEffectParameters(Effect effect)
		{
			Matrix worldMatrix = Matrix.Translation(Position);

			if(effect.IsParameterUsed("WorldMatrix", effect.Technique))
				effect.SetValue("WorldMatrix", worldMatrix);
			if(effect.IsParameterUsed("WorldViewProjectionMatrix", effect.Technique))
				effect.SetValue("WorldViewProjectionMatrix", worldMatrix * Program.Engine.ActiveCamera.View * Program.Engine.ActiveCamera.Projection);
		}

		public Vector3 Position;
		public Vector3 Scale;
	}
}
