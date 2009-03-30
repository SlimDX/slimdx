/*
* Copyright (c) 2007-2009 SlimDX Group
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
using SlimDX.Direct2D;
using SlimDX.DirectWrite;
using System.Drawing;

namespace SimpleText
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            SlimDX.Direct2D.Factory d2dfactory = new SlimDX.Direct2D.Factory();
            SlimDX.DirectWrite.Factory dwriteFactory = new SlimDX.DirectWrite.Factory();

            FlickerFreeForm form = new FlickerFreeForm();
            form.ClientSize = new Size((int)(d2dfactory.DesktopDpi.Width * 800.0f / 96.0f), (int)(d2dfactory.DesktopDpi.Height * 600.0f / 96.0f));
            form.Text = "SlimDX - DirectWrite Simple Text";

            WindowRenderTarget renderTarget = new WindowRenderTarget(d2dfactory, new WindowRenderTargetProperties() { Handle = form.Handle, PixelSize = form.ClientSize });
            SolidColorBrush brush = new SolidColorBrush(renderTarget, Color.Black);

            TextFormat textFormat = new TextFormat(dwriteFactory, "Gabriola", FontWeight.Normal, SlimDX.DirectWrite.FontStyle.Normal, FontStretch.Normal, 72.0f, "en-us");
            textFormat.TextAlignment = TextAlignment.Center;
            textFormat.ParagraphAlignment = ParagraphAlignment.Center;

            form.ClientSizeChanged += (o, e) => { renderTarget.Resize(form.ClientSize); };
            form.Paint += (o, e) =>
            {
                if (!renderTarget.IsOccluded)
                {
                    renderTarget.BeginDraw();
                    renderTarget.Transform = Matrix3x2.Identity;
                    renderTarget.Clear(Color.White);

                    renderTarget.DrawText("Hello World using DirectWrite!", textFormat, form.ClientRectangle, brush);

                    renderTarget.EndDraw();
                }
            };

            Application.Run(form);

            textFormat.Dispose();
            brush.Dispose();
            renderTarget.Dispose();
            dwriteFactory.Dispose();
            d2dfactory.Dispose();
            form.Dispose();
        }
    }
}
