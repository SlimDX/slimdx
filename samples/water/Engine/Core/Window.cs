using System;
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;

namespace Engine
{
	class Window : Form
	{
		#region Members
		private PresentParameters presentParams;
		private Device device;
		private Matrix matProj;
		private Matrix matView;
		private bool fullScreen = false;
		private bool deviceLost = false;
		#endregion
		#region properties
		public Device D3DDevice
		{
			get { if(device != null) { return device; }
					else { return null; } }
		}
		public Matrix MatView { get { return matView; }
								set { matView = value; }}
		public Matrix MatProj { get { return matProj; } }
		#endregion
		#region Methods
		public Window()
		{
			Width = 800;
			Height = 600;
			Text = "Tutorial 1 - Creating the Device";

			if(MessageBox.Show("Fullscreen?", "Fullscreen", MessageBoxButtons.YesNo) == DialogResult.Yes)
				fullScreen = true;
			AdapterInformation adapterInfo = Direct3D.Adapters[0]; //Helper class to gain access to information about the display adapter
			Capabilities caps = Direct3D.GetDeviceCaps( 0, DeviceType.Hardware );
			presentParams = new PresentParameters();
			presentParams.BackBufferCount = 1; //Number of backbuffers to create
			presentParams.BackBufferFormat = adapterInfo.CurrentDisplayMode.Format; //The current format of the display device
			presentParams.BackBufferHeight = this.Height;
			presentParams.BackBufferWidth = this.Width;
			presentParams.SwapEffect = SwapEffect.Discard; //How the backbuffer and the current display will be swapped
			presentParams.AutoDepthStencilFormat = Format.D24S8; //24 bits for the depth and 8 bits for the stencil
			presentParams.EnableAutoDepthStencil = true; //Let direct3d handle the depth buffers for the application
			presentParams.Windowed = true;
			if(fullScreen == true)
			{
				Cursor.Hide();
				presentParams.Windowed = false; //is the application windowed or fullscreen
				presentParams.BackBufferWidth = this.Width;
				presentParams.BackBufferHeight = this.Height;
				presentParams.PresentationInterval = PresentInterval.Immediate;
			}
			device = new Device(0, DeviceType.Hardware, this.Handle, CreateFlags.HardwareVertexProcessing, presentParams);

			matProj = Matrix.PerspectiveFovLH((float)Math.PI/4, 1.0f, 1.0f, 5000.0f);
			matView = Matrix.LookAtLH(new Vector3(450.0f, 350.0f, 750.0f), 
				new Vector3(0.0f, 0.0f, 0.0f),
				new Vector3(0.0f, 1.0f, 0.0f));

			device.SetTransform( TransformState.Projection, matProj );
			//device.Transform.View = matView;

			//TODO: Figure out how to replace this correctly
			//device.DeviceResizing += new System.ComponentModel.CancelEventHandler(this.CancelResize);
		}
		private void CancelResize(object sender, System.ComponentModel.CancelEventArgs e)
		{
			e.Cancel = true;
		}
		private void Recover()
		{
			//try
			//{
		    //TODO :Fix this
				device.TestCooperativeLevel();
				device.Reset(presentParams);
        deviceLost = false;
      //}
      //catch(DeviceLostException)
      //{
      //}
      //catch(DeviceNotResetException)
      //{
      //  try
      //  {
      //    device.Reset(presentParams);
      //    deviceLost = false;
      //  }
      //  catch(DeviceLostException)
      //  {
      //  }
      //}
		}
		public void BeginRender(Color bgColor)
		{
			if(deviceLost)
				Recover();
			if(deviceLost)
				return;
			if(device != null)
			{
				device.Clear(ClearFlags.Target | ClearFlags.ZBuffer | ClearFlags.Stencil, bgColor, 1.0f, 0);
				device.BeginScene();
			}
		}
		public void FinishRender()
		{
			if(deviceLost)
				return;
			device.EndScene();
		//	try
			//{
				device.Present();
			//}
			//catch(DeviceLostException)
		//	{
				deviceLost = true;
		//	}
		  //TODO: Fix above.
		}
		public void DisposeDevice()
		{
			if(device != null)
			{
				device.Dispose();
			}
		}
		#endregion
	}
}