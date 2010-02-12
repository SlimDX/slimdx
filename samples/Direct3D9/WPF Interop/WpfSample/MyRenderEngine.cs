/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// This code is Copyright (c) 2009 LizardTech, a Celartem Company, 1008    //
// Western Avenue, Suite 200, Seattle, WA 98104.  Unauthorized use or      //
// distribution prohibited.  Access to and use of this code is permitted   //
// only under license from LizardTech.  Portions of the code are protected //
// by US and foreign patents and other filings. All Rights Reserved.       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

using System;
using System.Windows;
using System.Windows.Resources;
using SlimDX;
using SlimDX.Direct3D9;
using System.IO;
using System.Drawing;
using SlimDX.Wpf;

namespace WpfSample
{
	public class MyRenderEngine : IRenderEngine
	{
		private Sprite _sprite;
		private Texture _texture;
		private MyDataModel _dataModel;

		public MyRenderEngine(MyDataModel dataModel) :
			base()
		{
			_dataModel = dataModel;
		}

		public void OnDeviceCreated(object sender, EventArgs e)
		{
			return;
		}

		public void OnDeviceDestroyed(object sender, EventArgs e)
		{
			if(_sprite != null && !_sprite.Disposed)
			{
				_sprite.Dispose();
			}
			if(_texture != null && !_texture.Disposed)
			{
				_texture.Dispose();
				_texture = null;
			}
		}

		public void OnDeviceLost(object sender, EventArgs e)
		{
			if(_sprite != null && !_sprite.Disposed)
			{
				_sprite.Dispose();
			}
			if(_texture != null && !_texture.Disposed)
			{
				_texture.Dispose();
				_texture = null;
			}
		}

		public void OnDeviceReset(object sender, EventArgs e)
		{
			SlimDXControl control = sender as SlimDXControl;
			if(control == null)
				throw new ArgumentNullException("sender");

			if(_sprite != null)
			{
				_sprite.Dispose();
			}
			_sprite = new Sprite(control.Device);

			if(_texture == null)
				_texture = Texture.FromStream(control.Device, _dataModel.Stream, Usage.None, Pool.Default);

			return;
		}

		public void OnMainLoop(object sender, EventArgs e)
		{
			_sprite.Begin(SpriteFlags.AlphaBlend);
			_sprite.Draw(_texture, Vector3.Zero, Vector3.Zero, _dataModel.Color4);
			_sprite.End();
		}
	}
}
