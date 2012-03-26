using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;
using System.Runtime.InteropServices;
using SlimMath;
using System.Drawing;

namespace SlimDX.Toolkit
{
    // represents a glyph (index into an atlas) rendered at a specified position with a given color
    struct Glyph
    {
        public Vector2 Position;
        public RectangleF PositionOffsets;
        public RectangleF TextureCoordinates;
        public int Color;
        public int SheetIndex;

        public Glyph(int sheetIndex)
            : this()
        {
            SheetIndex = sheetIndex;
        }
    }

    /// <summary>
    /// Converts formatted spans of text into a list of glyphs and positions to draw.
    /// </summary>
    class TextRenderer : ITextRenderer
    {
        GlyphProvider glyphProvider;
        List<Glyph> glyphs = new List<Glyph>(32);
        TextOptions currentFlags;

        public TextRenderer(GlyphProvider glyphProvider)
        {
            this.glyphProvider = glyphProvider;
        }

        public void DrawTextLayout(TextLayout layout, float originX, float originY, int color, TextOptions flags)
        {
            glyphs.Clear();

            currentFlags = flags;
            layout.Draw(new IntPtr(color), this, originX, originY);
        }

        public Result DrawGlyphRun(IntPtr drawingContext, float baselineOriginX, float baselineOriginY, MeasuringMode measuringMode, GlyphRun glyphRun, GlyphRunDescription glyphRunDescription, IntPtr clientDrawingEffect)
        {
            // skip if we're not interested in drawing
            if ((currentFlags & TextOptions.AnalyzeOnly) != 0)
                return ResultCode.Success;

            int color = drawingContext.ToInt32();
            float x = (float)Math.Floor(baselineOriginX + 0.5f);
            float y = (float)Math.Floor(baselineOriginY + 0.5f);

            // go through each glyph in the run and render it into the atlas
            for (int i = 0; i < glyphRun.GlyphCount; i++)
            {
                Glyph glyph;
                glyphProvider.GetGlyph(glyphRun.GlyphIndices[i], glyphRun.FontFace, glyphRun.FontSize, currentFlags, out glyph);

                // check if we should draw the vertex or if we just want to cache the glyphs
                if ((currentFlags & TextOptions.CacheOnly) == 0)
                {
                    if ((glyphRun.BidiLevel & 0x1) != 0)
                        x -= glyphRun.GlyphAdvances[i];

                    glyph.Position = new Vector2(x, y);
                    glyph.Color = color;
                    glyphs.Add(glyph);

                    if ((glyphRun.BidiLevel & 0x1) == 0)
                        x += glyphRun.GlyphAdvances[i];
                }
            }

            return ResultCode.Success;
        }

        public IList<Glyph> GetGlyphs()
        {
            // group vertices by the sheet they're in
            glyphs.Sort((x, y) => x.SheetIndex.CompareTo(y.SheetIndex));
            return glyphs;
        }

        #region Default Interface Implementation

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

        #endregion
    }
}
