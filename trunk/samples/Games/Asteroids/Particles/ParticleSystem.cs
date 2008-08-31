/*
* Copyright (c) 2007-2008 SlimDX Group
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
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace Asteroids
{
    /// <summary>
    /// Represents a system of rendered particles.
    /// </summary>
    class ParticleSystem : IResource, IGameComponent
    {
        // variables
        GraphicsDeviceManager manager;
        float currentTime;
        int drawCounter;

        // effect stuff
        Effect effect;
        EffectHandle viewParameter;
        EffectHandle projectionParameter;
        EffectHandle viewportHeightParameter;
        EffectHandle timeParameter;

        // vertex stuff
        ParticleVertex[] vertices;
        VertexBuffer vertexBuffer;
        VertexDeclaration declaration;

        // pointers into the circular vertex array
        int firstActiveParticle;
        int firstNewParticle;
        int firstFreeParticle;
        int firstRetiredParticle;

        /// <summary>
        /// Gets the device.
        /// </summary>
        /// <value>The device.</value>
        Device Device
        {
            get { return manager.Direct3D9.Device; }
        }

        /// <summary>
        /// Gets or sets the name of the texture.
        /// </summary>
        /// <value>The name of the texture.</value>
        public string TextureName
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the particle's duration.
        /// </summary>
        /// <value>The particle's duration.</value>
        public float Duration
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the random offset for each particle's duration.
        /// </summary>
        /// <value>The random duration offset for each particle.</value>
        public float DurationRandomness
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets how sensitive each particle is to an emitter's velocity.
        /// </summary>
        /// <value>The emitter velocity sensitivity.</value>
        public float EmitterVelocitySensitivity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum velocity.
        /// </summary>
        /// <value>The minimum velocity.</value>
        public Vector2 MinimumVelocity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum velocity.
        /// </summary>
        /// <value>The maximum velocity.</value>
        public Vector2 MaximumVelocity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the gravity.
        /// </summary>
        /// <value>The gravity.</value>
        public Vector3 Gravity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the end velocity.
        /// </summary>
        /// <value>The end velocity.</value>
        public float EndVelocity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum color.
        /// </summary>
        /// <value>The minimum color.</value>
        public Color4 MinimumColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum color.
        /// </summary>
        /// <value>The maximum color.</value>
        public Color4 MaximumColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum rotation speed.
        /// </summary>
        /// <value>The minimum rotation speed.</value>
        public float MinimumRotationSpeed
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum rotation speed.
        /// </summary>
        /// <value>The maximum rotation speed.</value>
        public float MaximumRotationSpeed
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum start size.
        /// </summary>
        /// <value>The minimum start size.</value>
        public float MinimumStartSize
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum start size.
        /// </summary>
        /// <value>The maximum start size.</value>
        public float MaximumStartSize
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the minimum end size.
        /// </summary>
        /// <value>The minimum end size.</value>
        public float MinimumEndSize
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum end size.
        /// </summary>
        /// <value>The maximum end size.</value>
        public float MaximumEndSize
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the source blend.
        /// </summary>
        /// <value>The source blend.</value>
        public Blend SourceBlend
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the destination blend.
        /// </summary>
        /// <value>The destination blend.</value>
        public Blend DestinationBlend
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ParticleSystem"/> class.
        /// </summary>
        /// <param name="maxParticles">The maximum number of active particle.</param>
        public ParticleSystem(int maxParticles)
        {
            // create the array
            vertices = new ParticleVertex[maxParticles];

            // set default settings
            EmitterVelocitySensitivity = 1.0f;
            EndVelocity = 1.0f;
            MinimumColor = Color.White;
            MaximumColor = Color.White;
            MinimumStartSize = 100.0f;
            MaximumStartSize = 100.0f;
            MinimumEndSize = 100.0f;
            MaximumEndSize = 100.0f;
            SourceBlend = Blend.SourceAlpha;
            DestinationBlend = Blend.InverseSourceAlpha;
        }

        /// <summary>
        /// Initializes the resource.
        /// </summary>
        /// <param name="graphicsDeviceManager">The graphics device manager.</param>
        public void Initialize(GraphicsDeviceManager graphicsDeviceManager)
        {
            // store the manager
            manager = graphicsDeviceManager;

            // load the effect
            effect = Effect.FromFile(Device, "Content/Shaders/ParticleEffect.fx", ShaderFlags.None);

            // store the effect parameters
            viewParameter = effect.GetParameter(null, "View");
            projectionParameter = effect.GetParameter(null, "Projection");
            viewportHeightParameter = effect.GetParameter(null, "ViewportHeight");
            timeParameter = effect.GetParameter(null, "CurrentTime");

            // set constant values
            CommitSettings();
        }

        /// <summary>
        /// Allows the resource to load any short-term graphical content.
        /// </summary>
        public void LoadContent()
        {
            // reload the effect
            effect.OnResetDevice();

            // create the vertex declaration
            declaration = manager.Direct3D9.CreateVertexDeclaration(typeof(ParticleVertex));

            // recreate the vertex buffer
            vertexBuffer = new VertexBuffer(Device, ParticleVertex.SizeInBytes * vertices.Length, Usage.Dynamic | Usage.WriteOnly | Usage.Points, VertexFormat.None, Pool.Default);
            vertexBuffer.Lock(0, 0, LockFlags.None).WriteRange(vertices);
            vertexBuffer.Unlock();
        }

        /// <summary>
        /// Allows the resource to unload any short-term graphical content.
        /// </summary>
        public void UnloadContent()
        {
            // release the resources
            declaration.Dispose();
            vertexBuffer.Dispose();
            effect.OnLostDevice();
        }

        /// <summary>
        /// Releases the resource.
        /// </summary>
        public void Release()
        {
            // release the effect
            effect.Dispose();
        }

        /// <summary>
        /// Commits queued settings changes.
        /// </summary>
        public void CommitSettings()
        {
            // upload effect settings
            effect.SetValue("Duration", Duration);
            effect.SetValue("DurationRandomness", DurationRandomness);
            effect.SetValue("Gravity", Gravity);
            effect.SetValue("EndVelocity", EndVelocity);
            effect.SetValue("MinColor", MinimumColor);
            effect.SetValue("MaxColor", MaximumColor);
            effect.SetValue("RotateSpeed", new Vector2(MinimumRotationSpeed, MaximumRotationSpeed));
            effect.SetValue("StartSize", new Vector2(MinimumStartSize, MinimumEndSize));
            effect.SetValue("EndSize", new Vector2(MinimumEndSize, MaximumEndSize));

            // set the texture
            Texture texture = Texture.FromFile(Device, TextureName);
            effect.SetValue("Texture", texture);
            texture.Dispose();

            // set the appropriate technique
            if (MinimumRotationSpeed == 0 && MaximumRotationSpeed == 0)
                effect.Technique = "NonRotatingParticles";
            else
                effect.Technique = "RotatingParticles";
        }

        /// <summary>
        /// Updates the component.
        /// </summary>
        /// <param name="gameTime">The game's timing information.</param>
        public void Update(GameTime gameTime)
        {
            // update the current time
            currentTime += gameTime.ElapsedGameTime;

            // retire any old particles
            while (firstActiveParticle != firstNewParticle)
            {
                // check if this particle is old
                if (currentTime - vertices[firstActiveParticle].Time < Duration)
                    break;

                // remember the time at which we retired the particle
                vertices[firstActiveParticle].Time = drawCounter;

                // update the pointer
                firstActiveParticle++;
                if (firstActiveParticle >= vertices.Length)
                    firstActiveParticle = 0;
            }

            // free any retired particles
            while (firstRetiredParticle != firstActiveParticle)
            {
                // only let particles become three frames old
                if (drawCounter - (int)vertices[firstRetiredParticle].Time < 3)
                    break;

                // update the pointer
                firstRetiredParticle++;
                if (firstRetiredParticle >= vertices.Length)
                    firstRetiredParticle = 0;
            }

            // reset the counter to zero whenever we don't have any particles to draw
            if (firstActiveParticle == firstFreeParticle)
                currentTime = 0;
            if (firstRetiredParticle == firstActiveParticle)
                drawCounter = 0;
        }

        /// <summary>
        /// Draws the component.
        /// </summary>
        public void Draw()
        {
            // save the stride (SizeInBytes uses Marshal.SizeOf to calculate the size)
            int stride = ParticleVertex.SizeInBytes;

            // upload any new particles waiting in the queue
            if (firstNewParticle != firstFreeParticle)
            {
                // check whether the range of new particles is consecutive of if it wraps around
                if (firstNewParticle < firstFreeParticle)
                {
                    // upload the vertices
                    int count = firstFreeParticle - firstNewParticle;
                    using (DataStream dataStream = vertexBuffer.Lock(firstNewParticle * stride, count * stride, LockFlags.NoOverwrite))
                        dataStream.WriteRange(vertices, firstNewParticle, count);
                    vertexBuffer.Unlock();
                }
                else
                {
                    // we need to split into two upload calls to get each end of the buffer
                    int count = vertices.Length - firstNewParticle;
                    using (DataStream dataStream = vertexBuffer.Lock(firstNewParticle * stride, count * stride, LockFlags.NoOverwrite))
                        dataStream.WriteRange(vertices, firstNewParticle, count);
                    vertexBuffer.Unlock();

                    // check if we need to make the second call
                    if (firstFreeParticle > 0)
                    {
                        // upload the vertices
                        using (DataStream dataStream = vertexBuffer.Lock(0, firstFreeParticle * stride, LockFlags.NoOverwrite))
                            dataStream.WriteRange(vertices, 0, firstFreeParticle);
                        vertexBuffer.Unlock();
                    }
                }

                // update the pointer
                firstNewParticle = firstFreeParticle;
            }

            // draw any active particles
            if (firstActiveParticle != firstFreeParticle)
            {
                // set render states
                Device.SetRenderState(RenderState.PointSpriteEnable, true);
                Device.SetRenderState(RenderState.PointSizeMax, 256);
                Device.SetRenderState(RenderState.AlphaBlendEnable, true);
                Device.SetRenderState(RenderState.BlendOperationAlpha, BlendOperation.Add);
                Device.SetRenderState(RenderState.SourceBlend, SourceBlend);
                Device.SetRenderState(RenderState.DestinationBlend, DestinationBlend);
                Device.SetRenderState(RenderState.AlphaTestEnable, true);
                Device.SetRenderState(RenderState.AlphaFunc, Compare.Greater);
                Device.SetRenderState(RenderState.AlphaRef, 0);
                Device.SetRenderState(RenderState.ZEnable, true);
                Device.SetRenderState(RenderState.ZWriteEnable, false);

                // set effect parameters
                effect.SetValue(viewportHeightParameter, Device.Viewport.Height);
                effect.SetValue(timeParameter, currentTime);

                // set vertex information
                Device.VertexDeclaration = declaration;
                Device.SetStreamSource(0, vertexBuffer, 0, stride);

                // start the effect
                int count = effect.Begin();
                for (int i = 0; i < count; i++)
                {
                    // start the pass
                    effect.BeginPass(i);

                    // check whether the range of new particles is consecutive of if it wraps around
                    if (firstActiveParticle < firstFreeParticle)
                        Device.DrawPrimitives(PrimitiveType.PointList, firstActiveParticle, firstFreeParticle - firstActiveParticle);
                    else
                    {
                        // we need to split into two draw calls to get each end of the buffer
                        Device.DrawPrimitives(PrimitiveType.PointList, firstActiveParticle, vertices.Length - firstActiveParticle);
                        if (firstFreeParticle > 0)
                            Device.DrawPrimitives(PrimitiveType.PointList, 0, firstFreeParticle);
                    }

                    // end the pass
                    effect.EndPass();
                }

                // end the effect
                effect.End();

                // reset render states
                Device.SetRenderState(RenderState.PointSpriteEnable, false);
                Device.SetRenderState(RenderState.ZWriteEnable, true);
            }

            // update the draw counter
            drawCounter++;
        }

        /// <summary>
        /// Sets the camera matrices for rendering.
        /// </summary>
        /// <param name="viewMatrix">The view matrix.</param>
        /// <param name="projectionMatrix">The projection matrix.</param>
        public void SetCamera(Matrix viewMatrix, Matrix projectionMatrix)
        {
            // set the effect parameters
            effect.SetValue(viewParameter, viewMatrix);
            effect.SetValue(projectionParameter, projectionMatrix);
        }

        /// <summary>
        /// Spawns a single new particle.
        /// </summary>
        /// <param name="position">The position.</param>
        /// <param name="velocity">The velocity.</param>
        public void SpawnParticle(Vector3 position, Vector3 velocity)
        {
            // figure out the position of the new particle
            int nextFreeParticle = firstFreeParticle + 1;
            if (nextFreeParticle >= vertices.Length)
                nextFreeParticle = 0;
            if (nextFreeParticle == firstRetiredParticle)
                return;

            // adjust the velocity based upon the sensitivity
            velocity *= EmitterVelocitySensitivity;

            // add in some randomness
            float vel = Helpers.Lerp(MinimumVelocity.X, MaximumVelocity.X, (float)Asteroids.Random.NextDouble());
            double angle = Asteroids.Random.NextDouble() * Math.PI * 2;
            velocity.X += vel * (float)Math.Cos(angle);
            velocity.Z += vel * (float)Math.Sin(angle);
            velocity.Y += Helpers.Lerp(MinimumVelocity.Y, MaximumVelocity.Y, (float)Asteroids.Random.NextDouble());

            // choose some random appearance values
            int appearance = Color.FromArgb(Asteroids.Random.Next(255), Asteroids.Random.Next(255), Asteroids.Random.Next(255), Asteroids.Random.Next(255)).ToArgb();

            // create the particle
            vertices[firstFreeParticle].Position = position;
            vertices[firstFreeParticle].Velocity = velocity;
            vertices[firstFreeParticle].Appearance = appearance;
            vertices[firstFreeParticle].Time = currentTime;

            // update the pointer
            firstFreeParticle = nextFreeParticle;
        }
    }
}
