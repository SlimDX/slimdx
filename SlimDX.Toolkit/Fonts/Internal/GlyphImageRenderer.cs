using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;
using System.Drawing;
using SlimMath;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Handles drawing of glyphs as images. Shared between all fonts.
    /// </summary>
    class GlyphImageRenderer : IDisposable
    {
        Dictionary<RenderingMode, RenderingParameters> parameterMap = new Dictionary<RenderingMode, RenderingParameters>();
        IntPtr blackBrush;
        BitmapRenderTarget renderTarget;
        int maxWidth = 384;
        int maxHeight = 384;
        IntPtr hdc;
        IntPtr bits;
        int rowPitch;
        int stride;

        public GlyphImageRenderer(Factory factory, int renderTargetWidth, int renderTargetHeight)
        {
            if (renderTargetWidth > 0)
                maxWidth = renderTargetWidth;
            if (renderTargetHeight > 0)
                maxHeight = renderTargetHeight;

            using (var interop = factory.GetGdiInterop())
            {
                renderTarget = interop.CreateBitmapRenderTarget(IntPtr.Zero, maxWidth, maxHeight);
                renderTarget.PixelsPerDip = 1.0f;

                hdc = renderTarget.MemoryDC;
                blackBrush = NativeMethods.CreateSolidBrush(0);

                var hbitmap = NativeMethods.GetCurrentObject(hdc, NativeMethods.OBJ_BITMAP);
                var bitmap = NativeMethods.GetBitmap(hbitmap);
                bits = bitmap.bmBits;
                rowPitch = bitmap.bmWidthBytes;
                stride = bitmap.bmBitsPixel / 8;
            }

            var modes = new[] { RenderingMode.Default, RenderingMode.Aliased };
            foreach (var mode in modes)
            {
                var renderingParams = factory.CreateCustomRenderingParameters(1.0f, 0.0f, 0.0f, PixelGeometry.Flat, mode);
                parameterMap.Add(mode, renderingParams);
            }
        }

        public void Dispose()
        {
            foreach (var value in parameterMap.Values)
                value.Dispose();
            parameterMap.Clear();

            if (blackBrush != IntPtr.Zero)
                NativeMethods.DeleteObject(blackBrush);

            if (renderTarget != null)
                renderTarget.Dispose();

            blackBrush = IntPtr.Zero;
            renderTarget = null;
        }

        public GlyphImageData DrawGlyph(FontFace fontFace, int index, float fontSize, RenderingMode renderingMode, MeasuringMode measuringMode)
        {
            // calculate pixel measurements
            var indices = new[] { (short)index };
            var fontMetrics = fontFace.Metrics;
            var glyphMetrics = fontFace.GetDesignGlyphMetrics(indices, false);
            var data = InitGlyphData(fontMetrics, glyphMetrics[0], fontSize);

            // set up drawing
            var run = new GlyphRun()
            {
                FontFace = fontFace,
                FontSize = fontSize,
                GlyphCount = 1,
                GlyphIndices = indices,
                GlyphAdvances = new[] { 0.0f },
                GlyphOffsets = new[] { new GlyphOffset() }
            };

            // clear the background
            var br = new NativeMethods.RECT();
            br.left = br.top = 0;
            br.right = 2 + data.Width + 5;
            br.bottom = 2 + data.Height + 5;
            NativeMethods.FillRect(hdc, ref br, blackBrush);

            RenderingParameters renderingParams;
            if (!parameterMap.TryGetValue(renderingMode, out renderingParams))
                renderingParams = parameterMap[RenderingMode.Default];

            // draw the glyph
            Rectangle rect;
            renderTarget.DrawGlyphRun(2.0f - data.X, 2.0f - data.Y, measuringMode, run, renderingParams, new Color4(1.0f, 1.0f, 1.0f), out rect);

            // clip to valid render target to avoid buffer overruns in case the glyph was too large
            rect.X = Math.Max(rect.X, 0);
            rect.Y = Math.Max(rect.Y, 0);
            rect.Width = Math.Min(rect.Width, maxWidth);
            rect.Height = Math.Min(rect.Height, maxHeight);

            // return the glyph data
            data.X += rect.Left - 2.0f;
            data.Y += rect.Top - 2.0f;
            data.Width = rect.Width;
            data.Height = rect.Height;

            var result = new GlyphImageData()
            {
                Metrics = data,
                GlyphPixels = bits + (rect.Y * rowPitch) + (rect.X * stride),
                RowPitch = rowPitch,
                PixelStride = stride
            };

            return result;
        }

        GlyphBounds InitGlyphData(FontMetrics fontMetrics, GlyphMetrics glyphMetrics, float fontSize)
        {
            // calculate pixel-space coordinates
            float fscale = fontSize / fontMetrics.DesignUnitsPerEm;
            float l = glyphMetrics.LeftSideBearing * fscale;
            float t = glyphMetrics.TopSideBearing * fscale;
            float r = glyphMetrics.RightSideBearing * fscale;
            float b = glyphMetrics.BottomSideBearing * fscale;
            float v = glyphMetrics.VerticalOrigin * fscale;
            float aw = glyphMetrics.AdvanceWidth * fscale;
            float ah = glyphMetrics.AdvanceHeight * fscale;

            var result = new GlyphBounds();
            result.X = (float)Math.Floor(l);
            result.Y = (float)(Math.Floor(t) - Math.Floor(v));
            result.Width = (int)(aw - r - l + 2.0f);
            result.Height = (int)(ah - b - t + 2.0f);

            return result;
        }
    }
}
