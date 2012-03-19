using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;
using SlimMath;
using System.Drawing;

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
    public class SpriteBatch : IDisposable
    {
        const int MaxBatchSize = 2048;

        // these resource pools allow resources to be shared between sprite batches
        // the local copies in each sprite batch are wrapped in ref-counted containers
        static SharedResourcePool<Device, SpriteDeviceResources> sharedDeviceResources = new SharedResourcePool<Device, SpriteDeviceResources>();
        static SharedResourcePool<DeviceContext, SpriteContextResources> sharedContextResources = new SharedResourcePool<DeviceContext, SpriteContextResources>();

        bool started;
        Device device;
        DeviceContext context;
        SpriteSortMode sortMode = SpriteSortMode.Deferred;
        ISharedResource<SpriteDeviceResources> deviceResources;
        ISharedResource<SpriteContextResources> contextResources;

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
            device = context.Device;
            this.context = context;

            deviceResources = sharedDeviceResources.DemandCreate(device, () => new SpriteDeviceResources(device, MaxBatchSize));
            contextResources = sharedContextResources.DemandCreate(context, () => new SpriteContextResources(context, MaxBatchSize));
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (deviceResources != null)
                deviceResources.Dispose();
            if (contextResources != null)
                contextResources.Dispose();

            deviceResources = null;
            contextResources = null;
        }

        /// <summary>
        /// Begins a batch of sprite drawing operations.
        /// </summary>
        /// <param name="sortMode">The sorting mode to use when choosing when to render sprites.</param>
        /// <exception cref="InvalidOperationException">
        /// Thrown if Begin is called more than once without an intervening End call, or if <see cref="SpriteSortMode.Immediate"/>
        /// is specified and another SpriteBatch is already doing immediat rendering.
        /// </exception>
        public void Begin(SpriteSortMode sortMode = SpriteSortMode.Deferred)
        {
            if (started)
                throw new InvalidOperationException("Cannot nest Begin calls on a single SpriteBatch.");

            this.sortMode = sortMode;
            if (sortMode == SpriteSortMode.Immediate)
            {
                // only one sprite batch can be doing immediate rendering
                if (contextResources.Resource.InImmediateMode)
                    throw new InvalidOperationException("Only one SpriteBatch at a time can be using Immediate sorting.");

                PrepareForRendering();
                contextResources.Resource.InImmediateMode = true;
            }

            started = true;
        }

        /// <summary>
        /// Ends a batch of sprite drawing operations.
        /// </summary>
        /// <exception cref="InvalidOperationException">
        /// Thrown if End is called without first calling Begin, or if End is called while another SpriteBatch is using immediate rendering.
        /// </exception>
        public void End()
        {
            if (!started)
                throw new InvalidOperationException("Begin must be called before End.");

            // if we are in immediate mode, the sprites have already been drawn
            if (sortMode == SpriteSortMode.Immediate)
                contextResources.Resource.InImmediateMode = false;
            else
            {
                if (contextResources.Resource.InImmediateMode)
                    throw new InvalidOperationException("Cannot end one SpriteBatch while another is using immediate rendering.");

                PrepareForRendering();
                FlushBatch();
            }

            started = false;
        }

        #region Draw Overloads

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="position">The 2D position at which to draw the sprite.</param>
        public void Draw(ShaderResourceView texture, Vector2 position)
        {
            unsafe { Draw(texture, new Vector4(position, 1.0f, 1.0f), null, new Color4(1.0f), Vector4.Zero, SpriteEffects.None); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="position">The 2D position at which to draw the sprite.</param>
        /// <param name="color">The color used to tint the sprite.</param>
        public void Draw(ShaderResourceView texture, Vector2 position, Color4 color)
        {
            unsafe { Draw(texture, new Vector4(position, 1.0f, 1.0f), null, color, Vector4.Zero, SpriteEffects.None); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="position">The 2D position at which to draw the sprite.</param>
        /// <param name="color">The color used to tint the sprite.</param>
        /// <param name="sourceRectangle">The portion of the source texture containing the sprite's image.</param>
        /// <param name="rotation">An amount to rotate the sprite's image, in radians.</param>
        /// <param name="scale">An amount to scale the sprite during drawing.</param>
        /// <param name="origin">The origin point for position, scaling, and rotation effects.</param>
        /// <param name="effects">Various effects to apply to the rendered sprite.</param>
        /// <param name="layerDepth">The layer depth to use for sorting the sprite.</param>
        public void Draw(ShaderResourceView texture, Vector2 position, Color4 color, Rectangle sourceRectangle, float rotation = 0.0f, float scale = 1.0f, Vector2 origin = new Vector2(), SpriteEffects effects = SpriteEffects.None, float layerDepth = 0.0f)
        {
            unsafe { Draw(texture, new Vector4(position, scale, scale), &sourceRectangle, color, new Vector4(origin.X, origin.Y, rotation, layerDepth), effects); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="position">The 2D position at which to draw the sprite.</param>
        /// <param name="color">The color used to tint the sprite.</param>
        /// <param name="sourceRectangle">The portion of the source texture containing the sprite's image.</param>
        /// <param name="scale">An amount to scale the sprite during drawing.</param>
        /// <param name="rotation">An amount to rotate the sprite's image, in radians.</param>
        /// <param name="origin">The origin point for position, scaling, and rotation effects.</param>
        /// <param name="effects">Various effects to apply to the rendered sprite.</param>
        /// <param name="layerDepth">The layer depth to use for sorting the sprite.</param>
        public void Draw(ShaderResourceView texture, Vector2 position, Color4 color, Rectangle sourceRectangle, Vector2 scale, float rotation = 0.0f, Vector2 origin = new Vector2(), SpriteEffects effects = SpriteEffects.None, float layerDepth = 0.0f)
        {
            unsafe { Draw(texture, new Vector4(position, scale.X, scale.Y), &sourceRectangle, color, new Vector4(origin.X, origin.Y, rotation, layerDepth), effects); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="destinationRectangle">The destination position and size.</param>
        public void Draw(ShaderResourceView texture, Rectangle destinationRectangle)
        {
            unsafe { Draw(texture, new Vector4(destinationRectangle.X, destinationRectangle.Y, destinationRectangle.Width, destinationRectangle.Height), null, new Color4(1.0f), Vector4.Zero, SpriteEffects.None); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="destinationRectangle">The destination position and size.</param>
        /// <param name="color">The color used to tint the sprite.</param>
        public void Draw(ShaderResourceView texture, Rectangle destinationRectangle, Color4 color)
        {
            unsafe { Draw(texture, new Vector4(destinationRectangle.X, destinationRectangle.Y, destinationRectangle.Width, destinationRectangle.Height), null, color, Vector4.Zero, SpriteEffects.None); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="destinationRectangle">The destination position and size.</param>
        /// <param name="sourceRectangle">The portion of the source texture containing the sprite's image.</param>
        /// <param name="color">The color used to tint the sprite.</param>
        /// <param name="rotation">An amount to rotate the sprite's image, in radians.</param>
        /// <param name="origin">The origin point for position, scaling, and rotation effects.</param>
        /// <param name="effects">Various effects to apply to the rendered sprite.</param>
        /// <param name="layerDepth">The layer depth to use for sorting the sprite.</param>
        public void Draw(ShaderResourceView texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color4 color, float rotation = 0.0f, Vector2 origin = new Vector2(), SpriteEffects effects = SpriteEffects.None, float layerDepth = 0.0f)
        {
            unsafe { Draw(texture, new Vector4(destinationRectangle.X, destinationRectangle.Y, destinationRectangle.Width, destinationRectangle.Height), &sourceRectangle, color, new Vector4(origin.X, origin.Y, rotation, layerDepth), effects); }
        }

        #endregion

        unsafe void Draw(ShaderResourceView texture, Vector4 destination, Rectangle* source, Color4 color, Vector4 originRotationDepth, SpriteEffects flags)
        {
        }

        void PrepareForRendering()
        {

        }

        void FlushBatch()
        {
        }
    }
}
