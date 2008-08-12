using System;
using System.Collections.Generic;
using System.Text;
using SlimDX;
using SampleFramework;
using SlimDX.Direct3D9;

namespace Asteroids
{
    class ParticleSystem
    {
        Particle[] particles;
        VertexBuffer vertexBuffer;

        public Vector2 Position
        {
            get;
            set;
        }

        public float ParticleOffset
        {
            get;
            set;
        }

        public float ParticleVelocity
        {
            get;
            set;
        }

        public float ParticleLife
        {
            get;
            set;
        }

        public Color4 ParticleColor
        {
            get;
            set;
        }

        public ParticleSystem(int maxParticles)
        {
            particles = new Particle[maxParticles];
        }

        public void Spawn(int count)
        {
            for (int i = 0; i < particles.Length; i++)
            {
                if (!particles[i].Active)
                {
                    SpawnParticle(i);
                    count--;
                    if (count == 0)
                        break;
                }
            }
        }

        public void Update(GameTime gameTime)
        {
            foreach (Particle particle in particles)
                if (particle.Active)
                    particle.Update(gameTime);
        }

        public void SpawnParticle(int index)
        {
            particles[index].Position = new Vector2(RandomFloat(-ParticleOffset, ParticleOffset), RandomFloat(-ParticleOffset, ParticleOffset));
            particles[index].Velocity = new Vector2(RandomFloat(-ParticleVelocity, ParticleVelocity), RandomFloat(-ParticleOffset, ParticleOffset));
            particles[index].Life = ParticleLife;
            particles[index].ElapsedTime = 0.0f;
            particles[index].Color = ParticleColor;
        }

        /// <summary>
        /// Calculates a random floating point value.
        /// </summary>
        /// <param name="minValue">The minimum value.</param>
        /// <param name="maxValue">The maximum value.</param>
        /// <returns>The random floating point value.</returns>
        static float RandomFloat(float minValue, float maxValue)
        {
            // calculate the value
            return (float)(Asteroids.Random.NextDouble() * (maxValue - minValue)) + minValue;
        }
    }
}
