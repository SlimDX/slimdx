using System;
using SlimDX;
using SlimDX.Direct3D9;
using System.Runtime.InteropServices;

namespace Engine
{
	public class Fountain : Entity
	{
		#region Members
		private const string meshFilename = "Resources/Models/fountain.x";
		private const string textureFilename = "Resources/Textures/rockwall.dds";
		private const string textureFilename1 = "Resources/Textures/rockwall_normal.dds";
		private const string effectFilename = "Resources/Shaders/bump.fx";
		private Texture texBump;
		#endregion
		#region Methods
		public Fountain(Device device) : base(device, meshFilename, effectFilename)
		{
			//load the texture
			texture = Texture.FromFile(device, textureFilename);
			texBump = Texture.FromFile(device, textureFilename1);
		}
		public override void Update(Matrix matView, Matrix matProj)
		{
			matWorld = Matrix.Translation(0.0f, -800.0f, 0.0f);
			this.matView = matView;
			this.matProj = matProj;
		}
		public override void Render(Device device)
		{
			//Calculate the matrices
			Matrix modelViewProj = matWorld * matView * matProj;
			Matrix modelViewIT = matWorld * matView * matProj;

			modelViewIT = Matrix.Invert(modelViewIT);
			modelViewIT = Matrix.Transpose(modelViewIT);

			//set the technique
			effect.Technique = "bump";
			//set the texturs
			effect.SetValue("texture0", texture);
			effect.SetValue("texture1", texBump);
			//set the matrices
			effect.SetValue("ModelViewProj", modelViewProj);
			effect.SetValue("ModelViewIT", modelViewIT);
			effect.SetValue("ModelWorld", matWorld);
			//set the light position
			float time = (float)(Environment.TickCount * 0.001);
			effect.SetValue("lightPos", new Vector4((float)(300 * Math.Sin(time)), 40.0f, (float)(300 * Math.Cos(time)), 1.0f));

			//render the effect
			effect.Begin(0);
			effect.BeginPass(0);
			mesh.DrawSubset(0);
			effect.EndPass();
			effect.End();
		}
		#endregion
	}
}