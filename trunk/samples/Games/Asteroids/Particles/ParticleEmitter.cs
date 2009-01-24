/*
* Copyright (c) 2007-2009 SlimDX Group
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
using SampleFramework;
using SlimDX;

namespace Asteroids
{
    class ParticleEmitter
    {
        ParticleSystem particleSystem;
        float timeBetweenParticles;
        float particlesPerSecond;
        Vector3 previousPosition;
        float timeLeftOver;

        public float ParticlesPerSecond
        {
            get { return particlesPerSecond; }
            set
            {
                particlesPerSecond = value;
                timeBetweenParticles = 1.0f / particlesPerSecond;
            }
        }

        public ParticleEmitter(ParticleSystem particleSystem, Vector3 initialPosition)
        {
            this.particleSystem = particleSystem;
            previousPosition = initialPosition;
            ParticlesPerSecond = 100.0f;
        }

        public void Update(GameTime gameTime, Vector3 newPosition)
        {
            if (gameTime.ElapsedGameTime > 0.0f && !float.IsInfinity(timeBetweenParticles))
            {
                Vector3 velocity = (newPosition - previousPosition) / gameTime.ElapsedGameTime;

                float totalTime = timeLeftOver + gameTime.ElapsedGameTime;
                float currentTime = -timeLeftOver;

                while (totalTime > timeBetweenParticles)
                {
                    currentTime += timeBetweenParticles;
                    totalTime -= timeBetweenParticles;

                    Vector3 position = Vector3.Lerp(previousPosition, newPosition, currentTime / gameTime.ElapsedGameTime);

                    particleSystem.SpawnParticle(position, velocity);
                }

                timeLeftOver = totalTime;
            }

            previousPosition = newPosition;
        }
    }
}
