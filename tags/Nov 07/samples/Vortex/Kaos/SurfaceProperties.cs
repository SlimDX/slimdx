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
using System.Windows.Forms;
using System.Text;
using System.Diagnostics;
using System.IO;
using SlimDX.Direct3D9;

namespace Demo.Kaos
{
	class SurfaceProperties
	{
		public SurfaceProperties()
		{
			mNeedReloadDiffuseMap = false;
			mNeedReloadEffect = false;
		}

		~SurfaceProperties()
		{
			if(mEffect != null)
				mEffect.Dispose();
			if(mDiffuseMap != null)
				mDiffuseMap.Dispose();
		}

		public SurfaceProperties(Device device, string diffuseMapFile, string effectFile)
		{
			try
			{
				if(diffuseMapFile != null)
				{
					DiffuseMap = Texture.FromFile(device, diffuseMapFile);
					WatchFile(diffuseMapFile, new ReloadCallbackType(ReloadDiffuseMap));
				}
				if(effectFile != null)
				{
					mEffect = Effect.FromFile(device, effectFile, null, null, 0, null);
					WatchFile(effectFile, new ReloadCallbackType(ReloadEffect));
				}
			}
			catch(Exception ex)
			{
				StringBuilder builder = new StringBuilder();
				builder.Append("Failed to load required resources.  Make sure you have the following resources in your directory: ");
				if(diffuseMapFile != null)
				{
					builder.Append(" ");
					builder.Append(diffuseMapFile);
				}
				if(effectFile != null)
				{
					builder.Append(" ");
					builder.Append(effectFile);
				}
				builder.Append("; Exception: ");
				builder.Append(ex.Message);
				System.Windows.Forms.MessageBox.Show(builder.ToString());
			}
		}

		public Texture DiffuseMap
		{
			set { mDiffuseMap = value; }
			get
			{
				if(mNeedReloadDiffuseMap)
				{
					try
					{
						if(mDiffuseMap != null)
						{
							mDiffuseMap.Dispose();
							mDiffuseMap = null;
						}
						mDiffuseMap = Texture.FromFile(Program.Engine.Device, mDiffuseMapPath);
					}
					catch(GraphicsException)
					{
						mDiffuseMap = null;
					}
					mNeedReloadDiffuseMap = false;
				}

				return mDiffuseMap;
			}
		}

		public Effect Effect
		{
			set { mEffect = value; }
			get
			{
				if(mNeedReloadEffect)
				{
					mNeedReloadEffect = false;
					try
					{
						if(mEffect != null)
						{
							mEffect.Dispose();
							mEffect = null;
						}
						mEffect = Effect.FromFile(Program.Engine.Device, mEffectPath, null, null, 0, null);
					}
					catch(GraphicsException)
					{
						mEffect = null;
					}
				}
				return mEffect;
			}
		}

		public void RenderWith(Device device, Mesh mesh)
		{
			if(mEffect != null)
			{
				Program.Engine.SetSceneParameters(mEffect);

				mEffect.Technique = mEffect.FindNextValidTechnique(null);
				if(mEffect.IsParameterUsed("DiffuseMap", mEffect.Technique))
					mEffect.SetValue("DiffuseMap", DiffuseMap);

				mesh.PrepareRender(device);

				int numPasses = mEffect.Begin(FX.None);
				for(int i = 0; i < numPasses; i++)
				{
					mEffect.BeginPass(i);
					mesh.Render(device);
					mEffect.EndPass();
				}
				mEffect.End();
			}
			else
			{
				if(mDiffuseMap != null)
				{
					device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.SelectArg1);
					device.SetTextureStageState(0, TextureStage.ColorArg1, TextureArgument.Texture);
					device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.Disable);
					device.SetSamplerState(0, SamplerState.MinFilter, TextureFilter.Linear);
					device.SetSamplerState(0, SamplerState.MagFilter, TextureFilter.Linear);
				}
				else
				{
					device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.SelectArg1);
					device.SetTextureStageState(0, TextureStage.ColorArg1, TextureArgument.TFactor);
					device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.Disable);
					device.SetRenderState(RenderState.TextureFactor, 0);
				}
				device.SetTexture(0, mDiffuseMap);
				mesh.PrepareRender(device);
				mesh.Render(device);
			}
		}

		private void ReloadDiffuseMap(object obj, FileSystemEventArgs fileArgs)
		{
			mNeedReloadDiffuseMap = true;
			mDiffuseMapPath = fileArgs.FullPath;
		}

		private void ReloadEffect(object obj, FileSystemEventArgs fileArgs)
		{
			mNeedReloadEffect = true;
			mEffectPath = fileArgs.FullPath;
		}

		private void WatchFile(string filename, ReloadCallbackType callback)
		{
			// Create a new FileSystemWatcher and set its properties.
			FileSystemWatcher watcher = new FileSystemWatcher();
			watcher.Path = Environment.CurrentDirectory;

			/* Watch for changes in LastAccess and LastWrite times, and
			   the renaming of files or directories. */
			watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
			   | NotifyFilters.FileName | NotifyFilters.DirectoryName;
			// Only watch text files.
			watcher.Filter = filename;

			// Add event handlers.
			watcher.Changed += new FileSystemEventHandler(callback);
			watcher.Created += new FileSystemEventHandler(callback);

			// Begin watching.
			watcher.EnableRaisingEvents = true;
		}

		private delegate void ReloadCallbackType(object obj, FileSystemEventArgs fileArgs);

		private Texture mDiffuseMap;
		private string mDiffuseMapPath;
		private bool mNeedReloadDiffuseMap;

		private Effect mEffect;
		private string mEffectPath;
		private bool mNeedReloadEffect;
	}
}
