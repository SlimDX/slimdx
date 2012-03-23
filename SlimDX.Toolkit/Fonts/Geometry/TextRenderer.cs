using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;
using System.Runtime.InteropServices;
using SlimMath;

namespace SlimDX.Toolkit.Fonts
{
    /// <summary>
    /// Converts formatted spans of text into geometry.
    /// </summary>
    class TextRenderer : ITextRenderer
    {
        GlyphProvider glyphProvider;
        FontFace cachedFontFace;
        float cachedFontSize;
        GlyphMap cachedGlyphMap;
        TextOptions currentFlags;
        int currentColor;

        public TextRenderer(GlyphProvider glyphProvider)
        {
            this.glyphProvider = glyphProvider;
            currentColor = unchecked((int)0xff000000);
        }

        public void DrawTextLayout(TextLayout layout, float originX, float originY, int color, TextOptions flags, TextGeometry geometry)
        {
            currentColor = color;
            currentFlags = flags;
            cachedGlyphMap = null;
            cachedFontFace = null;
            cachedFontSize = 0.0f;

            var handle = GCHandle.Alloc(geometry);

            try
            {
                layout.Draw(GCHandle.ToIntPtr(handle), this, originX, originY);
            }
            finally
            {
                handle.Free();
            }
        }

        public Result DrawGlyphRun(IntPtr drawingContext, float baselineOriginX, float baselineOriginY, MeasuringMode measuringMode, GlyphRun glyphRun, GlyphRunDescription glyphRunDescription, IntPtr clientDrawingEffect)
        {
            GlyphMap glyphMap;
            if (glyphRun.FontFace == cachedFontFace && glyphRun.FontSize == cachedFontSize)
                glyphMap = cachedGlyphMap;
            else
            {
                glyphMap = glyphProvider.GetGlyphMapFromFont(glyphRun.FontFace, glyphRun.FontSize, currentFlags);

                // cache the glyph map as it's likely to be used in subsequent glyph runs
                cachedGlyphMap = glyphMap;
                cachedFontFace = glyphRun.FontFace;
                cachedFontSize = glyphRun.FontSize;
            }

            // skip if we're not interested in drawing
            if ((currentFlags & TextOptions.AnalyzeOnly) != 0)
                return ResultCode.Success;

            // check if we should draw or if we should just cache the glyphs
            if ((currentFlags & TextOptions.CacheOnly) != 0)
            {
                for (int i = 0; i < glyphRun.GlyphCount; i++)
                    glyphProvider.GetAtlasIdFromGlyphIndex(glyphMap, glyphRun.GlyphIndices[i], glyphRun.FontFace, currentFlags);
            }
            else
            {
                var vertex = new GlyphVertex();
                vertex.Position.Y = (float)Math.Floor(baselineOriginY + 0.5f);
                vertex.Color = currentColor;

                // add a vertex for each glyph in the run
                var geometry = (TextGeometry)GCHandle.FromIntPtr(drawingContext).Target;
                if (geometry != null)
                {
                    float x = (float)Math.Floor(baselineOriginX + 0.5f);
                    for (int i = 0; i < glyphRun.GlyphCount; i++)
                    {
                        vertex.GlyphIndex = glyphProvider.GetAtlasIdFromGlyphIndex(glyphMap, glyphRun.GlyphIndices[i], glyphRun.FontFace, currentFlags);
                        if ((glyphRun.BidiLevel & 0x1) != 0)
                            x -= glyphRun.GlyphAdvances[i];

                        vertex.Position.X = (float)Math.Floor(x + 0.5f);
                        geometry.AddVertex(vertex);

                        if ((glyphRun.BidiLevel & 0x1) == 0)
                            x += glyphRun.GlyphAdvances[i];
                    }
                }
            }

            return ResultCode.Success;
        }

        public Result DrawInlineObject(IntPtr drawingContext, float baselineOriginX, float baselineOriginY, InlineObject inlineObject, bool isSideways, bool isRightToLeft, IntPtr clientDrawingEffect)
        {
            throw new NotImplementedException();
        }

        public Result DrawStrikethrough(IntPtr drawingContext, float baselineOriginX, float baselineOriginY, Strikethrough strikethrough, IntPtr clientDrawingEffect)
        {
            throw new NotImplementedException();
        }

        public Result DrawUnderline(IntPtr drawingContext, float baselineOriginX, float baselineOriginY, Underline underline, IntPtr clientDrawingEffect)
        {
            throw new NotImplementedException();
        }

        public Matrix3x2 GetCurrentTransform(IntPtr drawingContext)
        {
            return Matrix3x2.Identity;
        }

        public float GetPixelsPerDip(IntPtr drawingContext)
        {
            return 96.0f;
        }

        public bool IsPixelSnappingDisabled(IntPtr drawingContext)
        {
            return false;
        }
    }
}
