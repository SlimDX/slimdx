using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;
using SlimMath;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Specifies various sorting methods for sprite rendering.
    /// </summary>
    public enum SpriteSortMode
    {
        /// <summary>
        /// Batch all sprites and submit to GPU when <see cref="SpriteBatch.End"/> is called. Use this sorting mode
        /// for best performance when manually drawing in texture order.
        /// </summary>
        Deferred,

        /// <summary>
        /// Disables all batching. Each sprite is rendered with its own draw call.
        /// </summary>
        Immediate,

        /// <summary>
        /// Batch all sprites and sort by texture first before rendering.
        /// </summary>
        Texture,

        /// <summary>
        /// When drawing with multiple depth layers, sort by layer depth from back to front.
        /// </summary>
        BackToFront,

        /// <summary>
        /// When drawing with multiple depth layers, sort by layer depth from front to back.
        /// </summary>
        FrontToBack
    }

    /// <summary>
    /// Specifies various effects that can be applied to sprites.
    /// </summary>
    [Flags]
    public enum SpriteEffects
    {
        /// <summary>
        /// No effects specified.
        /// </summary>
        None,

        /// <summary>
        /// Flip the sprite horizontally.
        /// </summary>
        FlipHorizontally,

        /// <summary>
        /// Flip the sprite vertically.
        /// </summary>
        FlipVertically,

        /// <summary>
        /// Flip the sprite both horizontally and vertically.
        /// </summary>
        FlipBoth = FlipHorizontally | FlipVertically
    }

    /// <summary>
    /// Provides efficient rendering of batches of sprites.
    /// </summary>
    /// <remarks>
    /// Sprite batches are lightweight, and several can be created
    /// and rendered to simultaneously to form several batches that can then be submitted to the device in the desired
    /// order by calling <see cref="SpriteBatch.End"/>.
    /// </remarks>
    public class SpriteBatch
    {
        bool started;
        SpriteSortMode sortMode = SpriteSortMode.Deferred;

        /// <summary>
        /// The custom blend state to apply to sprites rendered in the current batch. Set it to <c>null</c> to use the default settings,
        /// which is to use premultiplied alpha blending.
        /// </summary>
        public BlendState BlendState
        {
            get;
            set;
        }

        /// <summary>
        /// The custom sampler state to apply to sprites rendered in the current batch. Set it to <c>null</c> to use the default settings,
        /// which are linear filtering with clamp addressing.
        /// </summary>
        public SamplerState SamplerState
        {
            get;
            set;
        }

        /// <summary>
        /// The custom depth-stencil state to apply to sprites rendered in the current batch. Set it to <c>null</c> to use the default settings,
        /// which is to not use the depth-buffer.
        /// </summary>
        public DepthStencilState DepthStencilState
        {
            get;
            set;
        }

        /// <summary>
        /// The custom sampler state to apply to sprites rendered in the current batch. Set it to <c>null</c> to use the default settings,
        /// which is to use counter-clockwise culling.
        /// </summary>
        public RasterizerState RasterizerState
        {
            get;
            set;
        }

        /// <summary>
        /// The transformation matrix to apply to all sprites rendered in the batch. This allows for global transforms
        /// such as scaling or translation that apply to an entire scene.
        /// </summary>
        public Matrix TransformMatrix
        {
            get;
            set;
        }

        /// <summary>
        /// A callback method that can be to set to allow the application to use custom shaders (which can be handy
        /// for 2D postprocessing effects such as bloom or blur).
        /// </summary>
        public Action CustomShaderSetup
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SpriteBatch"/> class.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        public SpriteBatch(DeviceContext context)
        {
            TransformMatrix = Matrix.Identity;
        }

        public void Begin(SpriteSortMode sortMode)
        {
        }

        public void End()
        {
        }
    }
}
