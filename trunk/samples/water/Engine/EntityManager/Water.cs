using System;
using SlimDX;
using SlimDX.Direct3D;
using SlimDX.Direct3D9;
using System.Runtime.InteropServices;

namespace Engine
{
	public class Water : Entity
	{
		#region Members
		private const string meshFilename = "../../Resources/Models/water.x";
		private const string textureFilename = "../../Resources/Textures/bricks.dds";
		private const string textureFilename1 = "../../Resources/Textures/water.dds";
		private const string effectFilename = "../../Resources/Shaders/water.fx";
		private CubeTexture texCube;
		private static float waterTime = 0;
		#endregion
		#region Methods
		public Water(Device device) : base(device, meshFilename, effectFilename)
		{
			//load the texture
			texCube = CubeTexture.FromFile(device, textureFilename);
			texture = Texture.FromFile(device, textureFilename1);
		}
		public override void Update(Matrix matView, Matrix matProj)
		{
			matWorld = Matrix.Translation(0.0f, -80.0f, 0.0f);
			this.matView = matView;
			this.matProj = matProj;
		}
		public override void Render(Device device)
		{
			float time = (float)(Environment.TickCount * 0.001);
			waterTime += 0.002f;
			//Calculate the matrices
			Matrix modelViewProj = matWorld * matView * matProj;
			Matrix modelViewIT = matWorld * matView * matProj;
			modelViewIT.Invert();
			modelViewIT = Matrix.Transpose(modelViewIT);
			//set the technique
			effect.Technique = "water";
			//set the texturs
			effect.SetValue("texture0", texture);
			effect.SetValue("texture1", texCube);
			//set the matrices
			effect.SetValue("ModelViewProj", modelViewProj);
			effect.SetValue("ModelWorld", matWorld);
			//set eye position
			effect.SetValue("eyePos", new Vector4(450.0f, 250.0f, 750.0f, 1.0f));
			//set the light position
			effect.SetValue("lightPos", new Vector4((float)(300 * Math.Sin(time)), 40.0f, (float)(300 * Math.Cos(time)), 1.0f));
			//set the time
			effect.SetValue("time", waterTime);

			//render the effect
			device.SetRenderState(RenderState.AlphaBlendEnable, true);
			effect.Begin(0);
			effect.BeginPass(0);
			mesh.DrawSubset(0);
			effect.EndPass();
			effect.End();
			device.SetRenderState(RenderState.AlphaBlendEnable, false);
		}
		public void Render(Device device, Texture waterTexture)
		{
			float time = (float)(Environment.TickCount * 0.001);
			waterTime += 0.002f;
			//Calculate the matrices
			Matrix modelViewProj = matWorld * matView * matProj;
			Matrix modelViewIT = matWorld * matView * matProj;
			modelViewIT.Invert();
			modelViewIT = Matrix.Transpose(modelViewIT);
			//set the technique
			effect.Technique = "water";
			//set the texturs
			effect.SetValue("texture0", waterTexture);
			effect.SetValue("texture1", texCube);
			//set the matrices
			effect.SetValue("ModelViewProj", modelViewProj);
			effect.SetValue("ModelWorld", matWorld);
			//set eye position
			effect.SetValue("eyePos", new Vector4(450.0f, 250.0f, 750.0f, 1.0f));
			//set the light position
			effect.SetValue("lightPos", new Vector4((float)(300 * Math.Sin(time)), 40.0f, (float)(300 * Math.Cos(time)), 1.0f));
			//set the time
			effect.SetValue("time", waterTime);

			//render the effect
			//device.RenderState.AlphaBlendEnable = true;
			effect.Begin(0);
			effect.BeginPass(0);
			mesh.DrawSubset(0);
			effect.EndPass();
			effect.End();
			//device.RenderState.AlphaBlendEnable = false;
		}
		#endregion
	}
}