using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D;

namespace Engine
{
	public class Core
	{
		#region Members
		private Window window;
		private Input input;
		private EntityManager entityManager;
		#endregion
		#region Methods
		public Core()
		{
			window = new Window();
			input = new Input(window.Handle, window.D3DDevice);
			entityManager = new EntityManager();
			entityManager.Add(new Room(window.D3DDevice));
			entityManager.Add(new Fountain(window.D3DDevice));
			entityManager.Add(new Water(window.D3DDevice));

			window.D3DDevice.RenderState.DiffuseMaterialSource = ColorSource.Color1;
			window.D3DDevice.RenderState.SourceBlend = Blend.One;
			window.D3DDevice.RenderState.DestBlend = Blend.One;
		}
		private void Update()
		{
			input.UpdateCamera(window.D3DDevice);
			entityManager.Update(input.MatView, window.MatProj);
		}
		private void Render()
		{
			window.BeginRender(Color.Black);
			entityManager.Render(window.D3DDevice);
			window.FinishRender();
		}
		public void Run()
		{
			window.Show();
			while(window.Created)
			{
				Update();
				Render();
				Application.DoEvents();
			}
			window.DisposeDevice();
		}
		#endregion
	}
}