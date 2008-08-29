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
using System.Collections.Generic;
using System.Text;
using SampleFramework;
using SlimDX.Direct3D9;
using SlimDX;

namespace Asteroids
{
    /// <summary>
    /// Represents a system of rendered particles.
    /// </summary>
    class ParticleSystem : IResource
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

        public string TextureName
        {
            get;
            set;
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

        public float MinimumRotationSpeed
        {
            get;
            set;
        }

        public float MaximumRotationSpeed
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

        /// <summary>
        /// Initializes a new instance of the <see cref="ParticleSystem"/> class.
        /// </summary>
        /// <param name="maxParticles">The maximum number of active particle.</param>
        public ParticleSystem(int maxParticles)
        {
            // create the array
            vertices = new ParticleVertex[maxParticles];
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
        }

        /// <summary>
        /// Allows the resource to load any short-term graphical content.
        /// </summary>
        public void LoadContent()
        {
            // reload the effect
            effect.OnResetDevice();

            // create the vertex declarations
            declaration = manager.Direct3D9.CreateVertexDeclaration(typeof(ParticleVertex));
            vertexBuffer = new VertexBuffer(Device, ParticleVertex.SizeInBytes * vertices.Length, Usage.Dynamic | Usage.WriteOnly | Usage.Points, VertexFormat.None, Pool.Default);
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
    }
}
