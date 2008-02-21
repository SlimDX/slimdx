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
using SlimDX.Direct3D;
using SlimDX.Direct3D9;
using Demo.Demo;
using Demo.Kaos;
using System.Drawing;

namespace Demo.Kaos
{
	class Engine
	{
		public Engine(System.Windows.Forms.Panel view)
		{
			Configuration.EnableObjectTracking = false;
			Direct3D.Initialize();

			PresentParameters presentParams = new PresentParameters();
			presentParams.BackBufferWidth = view.Width;
			presentParams.BackBufferHeight = view.Height;
			presentParams.DeviceWindowHandle = view.Handle;

			if(Direct3D.AdapterCount > 1)
			{
				// Enable support for NVPerfHUD, if we're using it.  ( You should :) )
				for(int i = 0; i < Direct3D.AdapterCount; i++)
				{
					AdapterDetails details = Direct3D.GetAdapterIdentifier(i);
					if(details.Description.ToLower().Contains("perfhud"))
					{
						mDevice = new Device(i, DeviceType.Reference, view.Handle, CreateFlags.HardwareVertexProcessing, presentParams);
						break;
					}
				}
			}
			if(mDevice == null)
			{
				// No NVPerfHUD, just standard initialization.
				mDevice = new Device(0, DeviceType.Hardware, view.Handle, CreateFlags.HardwareVertexProcessing, presentParams);
			}
			SetInitialStates(mDevice);

			mInput = new Input();

			mScreen = new ScreenTexture(mDevice, 1024, 1024);

			mCamera = new Camera(45.0f, view.Width / (float) view.Height);
			mCamera.Position = new Vector3(1.0f, 0, 1.0f);
			mCamera.LookAt = new Vector3(0, 0, 0);
			mCamera.Up = new Vector3(0, 1, 0);

			mVortex = new Vortex(mDevice);

			mBackground = new Tile(mDevice);
			mBackground.SurfaceProperties = new SurfaceProperties(mDevice, "sky.jpg", null);

			mBrick = new Tile(mDevice);
			mBrick.SurfaceProperties = new SurfaceProperties(mDevice, "brick.jpg", null);

			mTicker = new Ticker();
		}

		~Engine()
		{
			mDevice.Dispose();
		}

		public void Render()
		{
			mTicker.Update();

			mCamera.Update(mTicker.Delta);

			mDevice.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.LightSteelBlue, 1.0f, 0);
			mDevice.BeginScene();

			// Fill the background with a texture.
			mDevice.SetTransform(TransformState.View, Matrix.Translation(0, 0, 1));
			mDevice.SetTransform(TransformState.Projection, Matrix.Identity);
			mBackground.Scale = new Vector3(2, 2, 1);
			mBackground.Render(mDevice);

			mDevice.SetTransform(TransformState.View, mCamera.View);
			mDevice.SetTransform(TransformState.Projection, mCamera.Projection);
			mBrick.Render(mDevice);

			mScreen.Stretch(mDevice); // Copy back buffer into a texture so that our vortices can use it.

			mDevice.SetTransform(TransformState.View, mCamera.View);
			mDevice.SetTransform(TransformState.Projection, mCamera.Projection);
			RenderVortices(mDevice, mTicker.TotalTime);

			mDevice.EndScene();
			mDevice.Present();
		}

		public void SetSceneParameters(Effect effect)
		{
			if(effect.IsParameterUsed("ViewMatrix", effect.Technique))
				effect.SetValue("ViewMatrix", mCamera.View);
			if(effect.IsParameterUsed("ProjectionMatrix", effect.Technique))
				effect.SetValue("ProjectionMatrix", mCamera.Projection);

			if(effect.IsParameterUsed("Clock", effect.Technique))
				effect.SetValue("Clock", mTicker.TotalTime);

			if(effect.IsParameterUsed("ScreenTexture", effect.Technique))
				effect.SetValue("ScreenTexture", mScreen.Texture);
		}


		private void RenderVortices(Device device, float totalTime)
		{
			mVortex.Position = new Vector3(0, 0, (float) Math.Sin(totalTime * 1.5) / 2);
			mVortex.Render(device);

			mVortex.Position = new Vector3(0, 0, -(float) Math.Sin(totalTime * 1.5) / 2);
			mVortex.Render(device);
		}

		private void SetInitialStates(Device device)
		{
			device.SetTransform(TransformState.Projection, Matrix.Identity);
			device.SetTransform(TransformState.View, Matrix.Identity);
			device.SetTransform(TransformState.World, Matrix.Identity);

			device.SetRenderState(RenderState.Lighting, false);
			device.SetRenderState(RenderState.FogEnable, false);
			device.SetRenderState(RenderState.AlphaBlendEnable, false);
			device.SetRenderState(RenderState.AlphaTestEnable, false);
			device.SetRenderState(RenderState.CullMode, Cull.None);

			device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.SelectArg1);
			device.SetTextureStageState(0, TextureStage.ColorArg1, TextureArgument.Texture);
		}

		public Camera ActiveCamera
		{
			get { return mCamera; }
		}

		public Input Input
		{
			get { return mInput; }
		}

		public Device Device
		{
			get { return mDevice; }
		}

		private Device mDevice;
		private Vortex mVortex;
		private Tile mBackground;
		private Tile mBrick;
		private Camera mCamera;
		private Ticker mTicker;
		private ScreenTexture mScreen;
		private Input mInput;
	}
}
