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
using System.Drawing;
using SlimDX.Direct2D;

namespace RenderDemo
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Factory factory = new Factory();

            FlickerFreeForm form = new FlickerFreeForm();
            form.ClientSize = new Size((int)(factory.DesktopDpi.Width * 800.0f / 96.0f), (int)(factory.DesktopDpi.Height * 600.0f / 96.0f));
            form.Text = "SlimDX - Direct2D Render Demo";

            WindowRenderTarget renderTarget = new WindowRenderTarget(factory, new WindowRenderTargetProperties() { Handle = form.Handle, PixelSize = form.ClientSize });
            SolidColorBrush brush1 = new SolidColorBrush(renderTarget, Color.LightSlateGray);
            SolidColorBrush brush2 = new SolidColorBrush(renderTarget, Color.CornflowerBlue);

            form.ClientSizeChanged += (o, e) => { renderTarget.Resize(form.ClientSize); };
            form.Paint += (o, e) =>
            {
                if (!renderTarget.IsOccluded)
                {
                    renderTarget.BeginDraw();
                    renderTarget.Transform = Matrix3x2.Identity;
                    renderTarget.Clear(Color.White);

                    PointF startPoint = PointF.Empty;
                    PointF endPoint = new PointF(renderTarget.Size.Width, renderTarget.Size.Height);

                    while (startPoint.X < renderTarget.Size.Width)
                    {
                        endPoint.X = startPoint.X;
                        renderTarget.DrawLine(brush1, startPoint, endPoint, 0.5f);
                        startPoint.X += 10.0f;
                    }

                    startPoint = PointF.Empty;
                    endPoint.X = renderTarget.Size.Width;
                    endPoint.Y = 0.0f;

                    while (startPoint.Y < renderTarget.Size.Height)
                    {
                        endPoint.Y = startPoint.Y;
                        renderTarget.DrawLine(brush1, startPoint, endPoint, 0.5f);
                        startPoint.Y += 10.0f;
                    }

                    RectangleF rect1 = new RectangleF(renderTarget.Size.Width / 2 - 50.0f, renderTarget.Size.Height / 2 - 50.0f, 100.0f, 100.0f);
                    RectangleF rect2 = new RectangleF(renderTarget.Size.Width / 2 - 100.0f, renderTarget.Size.Height / 2 - 100.0f, 200.0f, 200.0f);

                    renderTarget.FillRectangle(brush1, rect1);
                    renderTarget.DrawRectangle(brush2, rect2);

                    renderTarget.EndDraw();
                }
            };

            Application.Run(form);

            brush1.Dispose();
            brush2.Dispose();
            renderTarget.Dispose();
            factory.Dispose();
            form.Dispose();
        }
    }
}
