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
using System.Windows.Forms;

namespace Demo.Kaos
{
	class Camera
	{
		public Camera(float fov, float aspectRatio)
		{
			mProjection = Matrix.PerspectiveFovLH(fov, aspectRatio, 0.1f, 100.0f);
			mRebuildView = true;
		}

		public Vector3 Position
		{
			get { return mPosition; }
			set
			{
				mPosition = value;
				mRebuildView = true;
			}
		}
		public Vector3 LookAt
		{
			get { return mLookAt; }
			set
			{
				mLookAt = value;
				mRebuildView = true;
			}
		}

		public Matrix View
		{
			get
			{
				if(mRebuildView)
				{
					mView = Matrix.LookAtLH(mPosition, mLookAt, mUp);
					mRebuildView = false;
					mUp = Up;
				}
				return mView;
			}
		}

		public Matrix Projection
		{
			get
			{
				return mProjection;
			}
		}

		public Vector3 Side
		{
			get
			{
				return new Vector3(View.M11, View.M21, View.M31);
			}
		}

		public Vector3 Up
		{
			get
			{
				return new Vector3(View.M12, View.M22, View.M32);
			}
			set
			{
				mUp = value;
				mRebuildView = true;
			}
		}

		public Vector3 Forward
		{
			get
			{
				return new Vector3(View.M13, View.M23, View.M33);
			}
		}

		public void Update(float deltaTime)
		{
			deltaTime *= 1.5f;

			if(Program.Engine.Input.Keyboard[Keys.W].Down)
				Position += Forward * deltaTime;

			if(Program.Engine.Input.Keyboard[Keys.S].Down)
				Position -= Forward * deltaTime;

			if(Program.Engine.Input.Keyboard[Keys.D].Down)
				Position += Side * deltaTime;

			if(Program.Engine.Input.Keyboard[Keys.A].Down)
				Position -= Side * deltaTime;

			if(Program.Engine.Input.Keyboard[Keys.R].Down)
				Position += Up * deltaTime;

			if(Program.Engine.Input.Keyboard[Keys.F].Down)
				Position -= Up * deltaTime;
		}

		private Vector3 mPosition;
		private Vector3 mLookAt;
		private Vector3 mUp;
		private Matrix mProjection;
		private Matrix mView;
		private bool mRebuildView;
	}
}
