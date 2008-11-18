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
    class ParticleSystem : IResource, IGameComponent
    {
        GraphicsDeviceManager manager;
        float currentTime;
        int drawCounter;

        Effect effect;
        EffectHandle viewParameter;
        EffectHandle projectionParameter;
        EffectHandle timeParameter;

        ParticleVertex[] vertices;
        VertexBuffer vertexBuffer;
        VertexDeclaration declaration;

        int firstActiveParticle;
        int firstNewParticle;
        int firstFreeParticle;
        int firstRetiredParticle;

        Device Device
        {
            get { return manager.Direct3D9.Device; }
        }

        public float Duration
        {
            get;
            set;
        }

        public float DurationRandomness
        {
            get;
            set;
        }

        public float EmitterVelocitySensitivity
        {
            get;
            set;
        }

        public Vector2 MinimumVelocity
        {
            get;
            set;
        }

        public Vector2 MaximumVelocity
        {
            get;
            set;
        }

        public Vector3 Gravity
        {
            get;
            set;
        }

        public float EndVelocity
        {
            get;
            set;
        }

        public Color4 MinimumColor
        {
            get;
            set;
        }

        public Color4 MaximumColor
        {
            get;
            set;
        }

        public float MinimumStartSize
        {
            get;
            set;
        }

        public float MaximumStartSize
        {
            get;
            set;
        }

        public float MinimumEndSize
        {
            get;
            set;
        }

        public float MaximumEndSize
        {
            get;
            set;
        }

        public Blend SourceBlend
        {
            get;
            set;
        }

        public Blend DestinationBlend
        {
            get;
            set;
        }

        public ParticleSystem(int maxParticles)
        {
            vertices = new ParticleVertex[maxParticles];

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

        public void Initialize(GraphicsDeviceManager graphicsDeviceManager)
        {
            manager = graphicsDeviceManager;

            effect = Effect.FromFile(Device, "Content/Shaders/ParticleEffect.fx", ShaderFlags.None);

            viewParameter = effect.GetParameter(null, "View");
            projectionParameter = effect.GetParameter(null, "Projection");
            timeParameter = effect.GetParameter(null, "CurrentTime");

            CommitSettings();
        }

        public void LoadContent()
        {
            effect.OnResetDevice();

            declaration = manager.Direct3D9.CreateVertexDeclaration(typeof(ParticleVertex));

            vertexBuffer = new VertexBuffer(Device, ParticleVertex.SizeInBytes * vertices.Length, Usage.Dynamic | Usage.WriteOnly | Usage.Points, VertexFormat.None, Pool.Default);
            vertexBuffer.Lock(0, 0, LockFlags.None).WriteRange(vertices);
            vertexBuffer.Unlock();
        }

        public void UnloadContent()
        {
            declaration.Dispose();
            vertexBuffer.Dispose();
            effect.OnLostDevice();
        }

        public void Dispose()
        {
            effect.Dispose();

            GC.SuppressFinalize(this);
        }

        public void CommitSettings()
        {
            effect.SetValue("Duration", Duration);
            effect.SetValue("DurationRandomness", DurationRandomness);
            effect.SetValue("Gravity", Gravity);
            effect.SetValue("EndVelocity", EndVelocity);
            effect.SetValue("MinColor", MinimumColor);
            effect.SetValue("MaxColor", MaximumColor);
            effect.SetValue("StartSize", new Vector2(MinimumStartSize, MinimumEndSize));
            effect.SetValue("EndSize", new Vector2(MinimumEndSize, MaximumEndSize));
            effect.Technique = "ParticleTechnique";
        }

        public void Update(GameTime gameTime)
        {
            currentTime += gameTime.ElapsedGameTime;

            while (firstActiveParticle != firstNewParticle)
            {
                if (currentTime - vertices[firstActiveParticle].Time < Duration)
                    break;

                vertices[firstActiveParticle].Time = drawCounter;

                firstActiveParticle++;
                if (firstActiveParticle >= vertices.Length)
                    firstActiveParticle = 0;
            }

            while (firstRetiredParticle != firstActiveParticle)
            {
                if (drawCounter - (int)vertices[firstRetiredParticle].Time < 3)
                    break;

                firstRetiredParticle++;
                if (firstRetiredParticle >= vertices.Length)
                    firstRetiredParticle = 0;
            }

            if (firstActiveParticle == firstFreeParticle)
                currentTime = 0;
            if (firstRetiredParticle == firstActiveParticle)
                drawCounter = 0;
        }

        public void Draw()
        {
            int stride = ParticleVertex.SizeInBytes;

            if (firstNewParticle != firstFreeParticle)
            {
                if (firstNewParticle < firstFreeParticle)
                {
                    int count = firstFreeParticle - firstNewParticle;
                    using (DataStream dataStream = vertexBuffer.Lock(firstNewParticle * stride, count * stride, LockFlags.NoOverwrite))
                        dataStream.WriteRange(vertices, firstNewParticle, count);
                    vertexBuffer.Unlock();
                }
                else
                {
                    int count = vertices.Length - firstNewParticle;
                    using (DataStream dataStream = vertexBuffer.Lock(firstNewParticle * stride, count * stride, LockFlags.NoOverwrite))
                        dataStream.WriteRange(vertices, firstNewParticle, count);
                    vertexBuffer.Unlock();

                    if (firstFreeParticle > 0)
                    {
                        using (DataStream dataStream = vertexBuffer.Lock(0, firstFreeParticle * stride, LockFlags.NoOverwrite))
                            dataStream.WriteRange(vertices, 0, firstFreeParticle);
                        vertexBuffer.Unlock();
                    }
                }

                firstNewParticle = firstFreeParticle;
            }

            if (firstActiveParticle != firstFreeParticle)
            {
                Device.SetRenderState(RenderState.PointSpriteEnable, true);
                Device.SetRenderState(RenderState.PointSizeMax, 256.0f);
                Device.SetRenderState(RenderState.AlphaBlendEnable, true);
                Device.SetRenderState(RenderState.BlendOperationAlpha, BlendOperation.Add);
                Device.SetRenderState(RenderState.SourceBlend, SourceBlend);
                Device.SetRenderState(RenderState.DestinationBlend, DestinationBlend);
                Device.SetRenderState(RenderState.AlphaTestEnable, true);
                Device.SetRenderState(RenderState.AlphaFunc, Compare.Greater);
                Device.SetRenderState(RenderState.AlphaRef, 0);
                Device.SetRenderState(RenderState.ZEnable, true);
                Device.SetRenderState(RenderState.ZWriteEnable, false);

                effect.SetValue(timeParameter, currentTime);

                Device.VertexDeclaration = declaration;
                Device.SetStreamSource(0, vertexBuffer, 0, stride);

                int count = effect.Begin();
                for (int i = 0; i < count; i++)
                {
                    effect.BeginPass(i);

                    if (firstActiveParticle < firstFreeParticle)
                        Device.DrawPrimitives(PrimitiveType.PointList, firstActiveParticle, firstFreeParticle - firstActiveParticle);
                    else
                    {
                        Device.DrawPrimitives(PrimitiveType.PointList, firstActiveParticle, vertices.Length - firstActiveParticle);
                        if (firstFreeParticle > 0)
                            Device.DrawPrimitives(PrimitiveType.PointList, 0, firstFreeParticle);
                    }

                    effect.EndPass();
                }

                effect.End();

                Device.SetRenderState(RenderState.PointSpriteEnable, false);
                Device.SetRenderState(RenderState.ZWriteEnable, true);
            }

            drawCounter++;
        }

        public void SetCamera(Matrix viewMatrix, Matrix projectionMatrix)
        {
            effect.SetValue(viewParameter, viewMatrix);
            effect.SetValue(projectionParameter, projectionMatrix);
        }

        public void SpawnParticle(Vector3 position, Vector3 velocity)
        {
            int nextFreeParticle = firstFreeParticle + 1;
            if (nextFreeParticle >= vertices.Length)
                nextFreeParticle = 0;
            if (nextFreeParticle == firstRetiredParticle)
                return;

            velocity *= EmitterVelocitySensitivity;

            float vel = Helpers.Lerp(MinimumVelocity.X, MaximumVelocity.X, (float)Asteroids.Random.NextDouble());
            double angle = Asteroids.Random.NextDouble() * Math.PI * 2;
            velocity.X += vel * (float)Math.Cos(angle);
            velocity.Z += vel * (float)Math.Sin(angle);
            velocity.Y += Helpers.Lerp(MinimumVelocity.Y, MaximumVelocity.Y, (float)Asteroids.Random.NextDouble());

            int appearance = Color.FromArgb(Asteroids.Random.Next(255), Asteroids.Random.Next(255), Asteroids.Random.Next(255), Asteroids.Random.Next(255)).ToArgb();

            vertices[firstFreeParticle].Position = position;
            vertices[firstFreeParticle].Velocity = velocity;
            vertices[firstFreeParticle].Appearance = appearance;
            vertices[firstFreeParticle].Time = currentTime;

            firstFreeParticle = nextFreeParticle;
        }
    }
}
