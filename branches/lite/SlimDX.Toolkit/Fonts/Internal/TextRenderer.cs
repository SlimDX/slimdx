using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DirectWrite;
using System.Runtime.InteropServices;
using SlimMath;

namespace SlimDX.Toolkit
{
    // represents a glyph (index into an atlas) rendered at a specified position with a given color
    struct GlyphVertex
    {
        public Vector2 Position;
        public GlyphIndex GlyphIndex;
        public int Color;

        public GlyphVertex(GlyphIndex index, float x, float y, int color)
        {
            Position = new Vector2(x, y);
            GlyphIndex = index;
            Color = color;
        }
    }

    /// <summary>
    /// Converts formatted spans of text into a list of glyphs and positions to draw.
    /// </summary>
    class TextRenderer : ITextRenderer
    {
        GlyphProvider glyphProvider;
        List<GlyphVertex> vertices = new List<GlyphVertex>();
        TextOptions currentFlags;

        public TextRenderer(GlyphProvider glyphProvider)
        {
            this.glyphProvider = glyphProvider;
        }

        public void DrawTextLayout(TextLayout layout, float originX, float originY, int color, TextOptions flags)
        {
            vertices.Clear();

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
                var index = glyphProvider.RenderToAtlas(glyphRun.GlyphIndices[i], glyphRun.FontFace, glyphRun.FontSize, currentFlags);

                // check if we should draw the vertex or if we just want to cache the glyphs
                if ((currentFlags & TextOptions.CacheOnly) == 0)
                {
                    if ((glyphRun.BidiLevel & 0x1) != 0)
                        x -= glyphRun.GlyphAdvances[i];

                    vertices.Add(new GlyphVertex(index, x, y, color));

                    if ((glyphRun.BidiLevel & 0x1) == 0)
                        x += glyphRun.GlyphAdvances[i];
                }
            }

            return ResultCode.Success;
        }

        public IList<GlyphVertex> SortVertices()
        {
            // group vertices by the sheet they're in
            vertices.Sort((x, y) => x.GlyphIndex.SheetIndex.CompareTo(y.GlyphIndex.SheetIndex));
            return vertices;
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
