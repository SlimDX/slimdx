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
using System.Drawing;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct2D;
using SlimDX.DirectWrite;
using SlimDX.Windows;

namespace MultiformattedText
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            var d2dFactory = new SlimDX.Direct2D.Factory();
            var dwriteFactory = new SlimDX.DirectWrite.Factory();

            var form = new RenderForm("SlimDX - DirectWrite Multiformatted Text");
            var renderTarget = new WindowRenderTarget(d2dFactory, new WindowRenderTargetProperties()
            {
                Handle = form.Handle,
                PixelSize = form.ClientSize
            });

            var brush = new SolidColorBrush(renderTarget, Color.Black);
            var textFormat = new TextFormat(dwriteFactory, "Gabriola", FontWeight.Normal, SlimDX.DirectWrite.FontStyle.Normal, FontStretch.Normal, 72.0f, "en-us")
            {
                TextAlignment = TextAlignment.Center,
                ParagraphAlignment = ParagraphAlignment.Center
            };

            var textLayout = new TextLayout(dwriteFactory, "Hello World using DirectWrite!", textFormat, form.ClientSize.Width, form.ClientSize.Height);
            textLayout.SetFontSize(100.0f, new TextRange(18, 2));
            textLayout.SetUnderline(true, new TextRange(18, 11));
            textLayout.SetFontWeight(FontWeight.Bold, new TextRange(18, 11));

            var typography = new Typography(dwriteFactory);
            typography.AddFeature(new FontFeature(FontFeatureTag.StylisticSet7, 1));
            textLayout.SetTypography(typography, new TextRange(0, 30));

            form.ClientSizeChanged += (o, e) => { renderTarget.Resize(form.ClientSize); };
            form.Paint += (o, e) =>
            {
                if (!renderTarget.IsOccluded)
                {
                    renderTarget.BeginDraw();
                    renderTarget.Transform = Matrix3x2.Identity;
                    renderTarget.Clear(Color.White);

                    renderTarget.DrawTextLayout(Point.Empty, textLayout, brush);

                    renderTarget.EndDraw();
                }
            };

            Application.Run(form);

            foreach (var item in ObjectTable.Objects)
                item.Dispose();
        }
    }
}
