using System;
using System.Drawing;
using SlimDX;
using SlimDX.DirectInput;

namespace Engine
{
	public class Input
	{
		#region Members
		private SlimDX.DirectInput.Device<KeyboardState> kbDevice;
		private SlimDX.DirectInput.Device<MouseState> mouseDevice;
		private MouseState mouse;
		private bool[] keyStates = {false, false, false, false, false, false};
		private bool[] mouseStates = {false, false, false, false};
		private Vector3 vecPos;
		//private static float angle = 0.0f;
		private Matrix matView;
		public Matrix MatView
		{
			get { return matView; }
		}
		#endregion
		#region Properties
		public bool[] KeyStates
		{
			get { return keyStates; }
		}
		#endregion
		#region Methods
		public Input(System.IntPtr handle, SlimDX.Direct3D9.Device device)
		{
			vecPos = new Vector3(450.0f, 350.0f, 750.0f);
			kbDevice = new SlimDX.DirectInput.Device<KeyboardState>(SystemGuid.Keyboard);
			mouseDevice = new SlimDX.DirectInput.Device<MouseState>(SystemGuid.Mouse);
			//mouseDevice.Properties.AxisModeAbsolute = false;
			kbDevice.SetCooperativeLevel(handle, CooperativeLevel.Nonexclusive | CooperativeLevel.Background);
			mouseDevice.SetCooperativeLevel(handle, CooperativeLevel.Nonexclusive | CooperativeLevel.Background);
			kbDevice.Acquire();
			mouseDevice.Acquire();
		}
		private void PollKeyboard()
		{
			for (int i = 0; i < 6; i++)
				keyStates[i] = false;
			/*foreach (Key k in kbDevice.GetPressedKeys())
			{
				switch (k.ToString())
				{
					case "Up" : keyStates[0] = true;
						break;
					case "Down" :
					case "DownArrow" : keyStates[1] = true;
						break;
					case "Left" :
					case "LeftArrow" : keyStates[2] = true;
						break;
					case "Right" : keyStates[3] = true;
						break;
					case "A": keyStates[4] = true;
						break;
					case "Z": keyStates[5] = true;
						break;
				}
			}*/
		}
		private void PollMouse()
		{
			for(int i = 0; i < 4; i++)
				mouseStates[i] = false;

            mouse = mouseDevice.GetCurrentState();
			if(mouse.X > 0)
				mouseStates[0] = true;
			if(mouse.X < 0)
				mouseStates[1] = true;
			if(mouse.Y > 0)
				mouseStates[2] = true;
			if(mouse.Y < 0)
				mouseStates[3] = true;
		}
		public void UpdateCamera(SlimDX.Direct3D9.Device device)
		{
			PollMouse();
			PollKeyboard();
			if(keyStates[0])
			{
				vecPos.Y+=5;
			}
			if(keyStates[1])
			{
				vecPos.Y-=5;
			}
			if(keyStates[2])
			{
				vecPos.X+=5;
			}
			if(keyStates[3])
			{
				vecPos.X-=5;
			}
			if(keyStates[4])
			{
				vecPos.Z+=5;
			}
			if(keyStates[5])
			{
				vecPos.Z-=5;
			}
			matView = Matrix.LookAtLH(new Vector3(vecPos.X, vecPos.Y, vecPos.Z), 
									  new Vector3(0.0f, 0.0f, 0.0f),
									  new Vector3(0.0f, 1.0f, 0.0f));
			device.SetTransform(SlimDX.Direct3D9.TransformState.View, matView);
		}
		public void Dispose()
		{
			kbDevice.Unacquire();
			kbDevice.Dispose();
			mouseDevice.Unacquire();
			mouseDevice.Dispose();
		}
		#endregion
	}
}
