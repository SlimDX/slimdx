using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;
using SlimMath;
using System.Drawing;
using SlimDX.Toolkit.VertexTypes;

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
        const int MinBatchSize = 128;
        const int InitialQueueSize = 64;
        const int SourceInTexels = 4;
        const int DestSizeInPixels = 8;
        internal const int VerticesPerSprite = 4;
        internal const int IndicesPerSprite = 6;

        static readonly Vector2[] CornerOffsets = {
            Vector2.Zero,
            Vector2.UnitX,
            Vector2.UnitY,
            Vector2.One
        };

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
        List<ShaderResourceView> textures;
        AlignedArray<SpriteInfo> sprites;
        List<int> sortedSprites;
        int spriteCount;

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

            sprites = new AlignedArray<SpriteInfo>(InitialQueueSize);
            textures = new List<ShaderResourceView>();
            sortedSprites = new List<int>();

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
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="texture"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown if Draw is called outside of a Begin/End pair.</exception>
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
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="texture"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown if Draw is called outside of a Begin/End pair.</exception>
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
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="texture"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown if Draw is called outside of a Begin/End pair.</exception>
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
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="texture"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown if Draw is called outside of a Begin/End pair.</exception>
        public void Draw(ShaderResourceView texture, Vector2 position, Color4 color, Rectangle sourceRectangle, Vector2 scale, float rotation = 0.0f, Vector2 origin = new Vector2(), SpriteEffects effects = SpriteEffects.None, float layerDepth = 0.0f)
        {
            unsafe { Draw(texture, new Vector4(position, scale.X, scale.Y), &sourceRectangle, color, new Vector4(origin.X, origin.Y, rotation, layerDepth), effects); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="destinationRectangle">The destination position and size.</param>
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="texture"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown if Draw is called outside of a Begin/End pair.</exception>
        public void Draw(ShaderResourceView texture, Rectangle destinationRectangle)
        {
            unsafe { Draw(texture, new Vector4(destinationRectangle.X, destinationRectangle.Y, destinationRectangle.Width, destinationRectangle.Height), null, new Color4(1.0f), Vector4.Zero, (SpriteEffects)DestSizeInPixels); }
        }

        /// <summary>
        /// Adds a sprite to the draw queue. Depending on the sorting mode, the sprite may be rendered immediately or deferred to be sorted and batched.
        /// </summary>
        /// <param name="texture">The sprite's texture.</param>
        /// <param name="destinationRectangle">The destination position and size.</param>
        /// <param name="color">The color used to tint the sprite.</param>
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="texture"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown if Draw is called outside of a Begin/End pair.</exception>
        public void Draw(ShaderResourceView texture, Rectangle destinationRectangle, Color4 color)
        {
            unsafe { Draw(texture, new Vector4(destinationRectangle.X, destinationRectangle.Y, destinationRectangle.Width, destinationRectangle.Height), null, color, Vector4.Zero, (SpriteEffects)DestSizeInPixels); }
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
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="texture"/> is <c>null</c>.</exception>
        /// <exception cref="InvalidOperationException">Thrown if Draw is called outside of a Begin/End pair.</exception>
        public void Draw(ShaderResourceView texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color4 color, float rotation = 0.0f, Vector2 origin = new Vector2(), SpriteEffects effects = SpriteEffects.None, float layerDepth = 0.0f)
        {
            unsafe { Draw(texture, new Vector4(destinationRectangle.X, destinationRectangle.Y, destinationRectangle.Width, destinationRectangle.Height), &sourceRectangle, color, new Vector4(origin.X, origin.Y, rotation, layerDepth), effects | (SpriteEffects)DestSizeInPixels); }
        }

        #endregion

        unsafe void Draw(ShaderResourceView texture, Vector4 destination, Rectangle* source, Color4 color, Vector4 originRotationDepth, SpriteEffects effects)
        {
            if (texture == null)
                throw new ArgumentNullException("texture");
            if (!started)
                throw new InvalidOperationException("Begin must be called before Draw.");

            if (spriteCount >= sprites.Length)
            {
                // double the size of the array if we've run out of room
                sprites.Realloc(sprites.Length * 2);
                sortedSprites.Clear();
            }

            int flags = (int)effects;
            var sprite = (SpriteInfo*)sprites[spriteCount];

            if (source != null)
            {
                var sourceVec = new Vector4(source->X, source->Y, source->Width, source->Height);
                sprite->Source = sourceVec;

                // if the destination size is relative to the source region, convert it to pixels
                if ((flags & DestSizeInPixels) == 0)
                {
                    destination.Z *= sourceVec.Z;
                    destination.W *= sourceVec.W;
                }

                flags |= SourceInTexels | DestSizeInPixels;
            }
            else
            {
                // no explicit source region, so use the entire texture
                sprite->Source = new Vector4(0, 0, 1, 1);
            }

            sprite->Destination = destination;
            sprite->Color = color;
            sprite->OriginRotationDepth = originRotationDepth;
            sprite->Flags = flags;

            // if we are in immediate mode, draw the sprite right away
            if (sortMode == SpriteSortMode.Immediate)
            {
                if (textures.Count == 0)
                    textures.Add(texture);
                else
                    textures[0] = texture;

                if (sortedSprites.Count == 0)
                    sortedSprites.Add(0);
                else
                    sortedSprites[0] = 0;

                RenderBatch(0, 0, 1);
            }
            else
            {
                // queue the sprite for later sorting and batched rendering
                spriteCount++;
                if (textures.Count == 0 || texture != textures[textures.Count - 1])
                    textures.Add(texture);

                sprite->Texture = textures.Count - 1;
            }
        }

        void PrepareForRendering()
        {
            var dr = deviceResources.Resource;
            var cr = contextResources.Resource;

            // set state objects
            var blendState = BlendState ?? dr.States.AlphaBlend;
            var depthStencilState = DepthStencilState ?? dr.States.DepthNone;
            var rasterizerState = RasterizerState ?? dr.States.CullCounterClockwise;
            var samplerState = SamplerState ?? dr.States.LinearClamp;

            context.OutputMerger.BlendState = blendState;
            context.OutputMerger.DepthStencilState = depthStencilState;
            context.Rasterizer.State = rasterizerState;
            context.PixelShader.SetSampler(samplerState, 0);

            // set shaders
            context.InputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;
            context.InputAssembler.InputLayout = dr.InputLayout;
            context.VertexShader.Set(dr.VertexShader);
            context.PixelShader.Set(dr.PixelShader);

            // set vertex and index buffers
            context.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(cr.VertexBuffer, VertexPositionColorTexture.SizeInBytes, 0));
            context.InputAssembler.SetIndexBuffer(dr.IndexBuffer, DXGI.Format.R16_UInt, 0);

            // set transform matrix
            var viewport = context.Rasterizer.GetViewport();
            var transform = TransformMatrix * Matrix.OrthoOffCenterLH(0.0f, viewport.Width, viewport.Height, 0.0f, 0.0f, 1.0f);
            cr.ConstantBuffer.SetData(context, ref transform);
            context.VertexShader.SetConstantBuffer(cr.ConstantBuffer.Buffer, 0);

            // if this is on a deferred device context, reset the position so that the first Map call can use Discard
            if (context.Type == DeviceContextType.Deferred)
                cr.VertexBufferPosition = 0;

            // let the user do any custom shader settings
            if (CustomShaderSetup != null)
                CustomShaderSetup();
        }

        unsafe void FlushBatch()
        {
            if (spriteCount == 0)
                return;

            SortSprites();

            // walk through the sorted sprite list, looking for adjacent entries that share a texture
            int currentTexture = -1;
            int batchStart = 0;

            for (int i = 0; i < spriteCount; i++)
            {
                var sprite = (SpriteInfo*)sprites[sortedSprites[i]];

                // flush whenever the texture changes
                if (sprite->Texture != currentTexture)
                {
                    if (i > batchStart)
                        RenderBatch(currentTexture, batchStart, i - batchStart);

                    currentTexture = sprite->Texture;
                    batchStart = i;
                }
            }

            // flush the final batch
            RenderBatch(currentTexture, batchStart, spriteCount - batchStart);

            // reset the queue
            spriteCount = 0;
            textures.Clear();

            // if we're using sorting, clear the sort array to avoid problems due to unstable sorts
            if (sortMode != SpriteSortMode.Deferred)
                sortedSprites.Clear();
        }

        unsafe void SortSprites()
        {
            // increase the size of the sort array if necessary
            if (sortedSprites.Count < spriteCount)
            {
                for (int i = sortedSprites.Count; i < spriteCount; i++)
                    sortedSprites.Add(i);
            }

            switch (sortMode)
            {
                // sort by texture
                case SpriteSortMode.Texture:
                    sortedSprites.Sort((x, y) => ((SpriteInfo*)sprites[x])->Texture.CompareTo(((SpriteInfo*)sprites[y])->Texture));
                    break;

                // sort by depth from back to front
                case SpriteSortMode.BackToFront:
                    sortedSprites.Sort((x, y) => ((SpriteInfo*)sprites[y])->OriginRotationDepth.W.CompareTo(((SpriteInfo*)sprites[x])->OriginRotationDepth.W));
                    break;

                // sort by depth from front to back
                case SpriteSortMode.FrontToBack:
                    sortedSprites.Sort((x, y) => ((SpriteInfo*)sprites[x])->OriginRotationDepth.W.CompareTo(((SpriteInfo*)sprites[y])->OriginRotationDepth.W));
                    break;
            }
        }

        unsafe void RenderBatch(int textureIndex, int start, int count)
        {
            var cr = contextResources.Resource;
            var texture = textures[textureIndex];
            context.PixelShader.SetShaderResource(texture, 0);

            Vector2 textureSize = GetTextureSize(texture);
            Vector2 inverseSize = Vector2.Reciprocal(textureSize);

            while (count > 0)
            {
                // figure out how many sprites we *want* to draw, and how many can fit in the vertex buffer
                int batchSize = count;
                int remainingSpace = MaxBatchSize - cr.VertexBufferPosition;

                if (batchSize > remainingSpace)
                {
                    if (remainingSpace < MinBatchSize)
                    {
                        // if we are out of room, or are about to submit an excessively small batch, wrap back to the start of the buffer
                        cr.VertexBufferPosition = 0;
                        batchSize = Math.Min(count, MaxBatchSize);
                    }
                    else
                        batchSize = remainingSpace;
                }

                // write sprites into the vertex buffer
                var box = context.MapSubresource(cr.VertexBuffer, cr.VertexBufferPosition == 0 ? MapMode.WriteDiscard : MapMode.WriteNoOverwrite, MapFlags.None);
                box.Data.Position += cr.VertexBufferPosition * VerticesPerSprite * VertexPositionColorTexture.SizeInBytes;

                for (int i = 0; i < batchSize; i++)
                    RenderSprite((SpriteInfo*)sprites[sortedSprites[i + start]], box.Data, textureSize, inverseSize);

                context.UnmapSubresource(cr.VertexBuffer, 0);

                // do the actual drawing
                context.DrawIndexed(batchSize * IndicesPerSprite, cr.VertexBufferPosition * IndicesPerSprite, 0);

                cr.VertexBufferPosition += batchSize;
                start += batchSize;
                count -= batchSize;
            }
        }

        unsafe void RenderSprite(SpriteInfo* sprite, DataStream vertices, Vector2 textureSize, Vector2 inverseTextureSize)
        {
            int flags = sprite->Flags;
            float rotation = sprite->OriginRotationDepth.Z;
            float depth = sprite->OriginRotationDepth.W;
            var sourcePos = sprite->Source.XY;
            var sourceSize = sprite->Source.ZW;
            var destPos = sprite->Destination.XY;
            var destSize = sprite->Destination.ZW;
            
            // compute the scaled origin
            var origin = sprite->OriginRotationDepth.XY;
            origin.X /= sourceSize.X == 0 ? float.Epsilon : sourceSize.X;
            origin.Y /= sourceSize.Y == 0 ? float.Epsilon : sourceSize.Y;            

            // convert the source region from texels to mod-1 texture coordinate format
            if ((flags & SourceInTexels) != 0)
            {
                Vector2.Modulate(ref sourcePos, ref inverseTextureSize, out sourcePos);
                Vector2.Modulate(ref sourceSize, ref inverseTextureSize, out sourceSize);
            }
            else
                Vector2.Modulate(ref origin, ref inverseTextureSize, out origin);

            // if the destination size is relative to the source region, convert it to pixels
            if ((flags & DestSizeInPixels) == 0)
                Vector2.Modulate(ref destSize, ref textureSize, out destSize);

            // compute a 2x2 rotation matrix
            var rotationMatrix = rotation == 0 ? Matrix.Identity : Matrix.RotationZ(rotation);

            // Tricksy alert! Texture coordinates are computed from the same cornerOffsets
            // table as vertex positions, but if the sprite is mirrored, this table
            // must be indexed in a different order. This is done as follows:
            //    position = cornerOffsets[i]
            //    texcoord = cornerOffsets[i ^ SpriteEffects]

            int mirrorBits = flags & 3;
            for (int i = 0; i < VerticesPerSprite; i++)
            {
                // calculate position
                Vector2 position;
                var offset = Vector2.Modulate(CornerOffsets[i] - origin, destSize);
                Vector2.TransformNormal(ref offset, ref rotationMatrix, out position);

                // calculate texture coordinates
                var texcoords = Vector2.Modulate(CornerOffsets[i ^ mirrorBits], sourceSize) + sourcePos;

                // write out the vertex into the stream
                vertices.Write(new VertexPositionColorTexture(new Vector3(position, depth), sprite->Color, texcoords));
            }
        }

        static Vector2 GetTextureSize(ShaderResourceView view)
        {
            var texture = view.Resource as Texture2D;
            if (texture == null)
                throw new InvalidOperationException("SpriteBatch can only draw 2D textures.");

            var desc = texture.Description;
            return new Vector2(desc.Width, desc.Height);
        }
    }
}
