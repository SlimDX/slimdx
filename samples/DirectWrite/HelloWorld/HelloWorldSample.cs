/*
* Copyright (c) 2007-2010 SlimDX Group
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

using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct2D;
using SlimDX.DirectWrite;
using SlimDX.SampleFramework;
using FontStyle=SlimDX.DirectWrite.FontStyle;

namespace HelloWorld
{
	/// <summary>
	/// Demonstrates how to render a simple colored triangle with Direct2D.
	/// </summary>
	class HelloWorldSample : Sample
	{
		private MainForm _mainForm;
		private SolidColorBrush _brush;

		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		/// <param name="disposeManagedResources">If true, managed resources should be
		/// disposed of in addition to unmanaged resources.</param>
		protected override void Dispose(bool disposeManagedResources)
		{
			if (disposeManagedResources)
			{
				_brush.Dispose();
			}

			base.Dispose(disposeManagedResources);
		}

		protected override Form CreateForm(SampleConfiguration configuration)
		{
			_mainForm = new MainForm();
			return _mainForm;
		}

		private SlimDX.DirectWrite.Factory _writeFactory;
		private TextFormat _textFormat;
		float _dpiY;
		float _dpiX;

		private WindowRenderTarget RenderTarget
		{
			get { return _mainForm.SimpleTextRenderPanel.Context2D.RenderTarget; }
		}

		/// <summary>
		/// In a derived class, implements logic to initialize the sample.
		/// </summary>
		protected override void OnInitialize()
		{
			DeviceSettings2D settings = new DeviceSettings2D
			{
				Width = WindowWidth,
				Height = WindowHeight
			};

			InitializeDevice(settings);
			_mainForm.SimpleTextRenderPanel.InitializeDevice(settings);
			_writeFactory = new SlimDX.DirectWrite.Factory(SlimDX.DirectWrite.FactoryType.Shared);
			_textFormat = _writeFactory.CreateTextFormat("Gabriola", FontWeight.Regular, FontStyle.Normal, FontStretch.Normal, 72.0f, "en-us");
			_textFormat.TextAlignment = TextAlignment.Center;
			_textFormat.ParagraphAlignment = ParagraphAlignment.Center;
			_brush = new SolidColorBrush(RenderTarget, new Color4(0.0f, 0.0f, 0.0f));
			using (Graphics graphics = Graphics.FromHwnd(_mainForm.SimpleTextRenderPanel.Handle))
			{
				_dpiY = graphics.DpiY/96.0f;
				_dpiX = graphics.DpiX/96.0f;
			}
		}

		/// <summary>
		/// In a derived class, implements logic that should occur before all
		/// other rendering.
		/// </summary>
		protected override void OnRenderBegin()
		{
			RenderTarget.BeginDraw();
			RenderTarget.Transform = Matrix3x2.Identity;
			RenderTarget.Clear(new Color4(0.3f, 0.3f, 0.3f));
		}

		/// <summary>
		/// In a derived class, implements logic to render the sample.
		/// </summary>
		protected override void OnRender()
		{
			RectangleF layoutRect = _mainForm.SimpleTextRenderPanel.ClientRectangle;
			layoutRect = new RectangleF(layoutRect.Left/_dpiX, layoutRect.Top/_dpiY, layoutRect.Width/_dpiX, layoutRect.Height/_dpiY);
			RenderTarget.DrawText("Hello World using  DirectWrite!", _textFormat, layoutRect, _brush);
		}

		/// <summary>
		/// In a derived class, implements logic that should occur after all
		/// other rendering.
		/// </summary>
		protected override void OnRenderEnd()
		{
			RenderTarget.EndDraw();
		}

	}
}
