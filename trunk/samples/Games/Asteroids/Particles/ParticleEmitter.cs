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
using SampleFramework;
using SlimDX;

namespace Asteroids
{
    /// <summary>
    /// Handles automatic generation of particles for a moving object.
    /// </summary>
    class ParticleEmitter
    {
        // variables
        ParticleSystem particleSystem;
        float timeBetweenParticles;
        Vector3 previousPosition;
        float timeLeftOver;

        /// <summary>
        /// Initializes a new instance of the <see cref="ParticleEmitter"/> class.
        /// </summary>
        /// <param name="particleSystem">The particle system.</param>
        /// <param name="particlesPerSecond">The amount of particles that should be generated each second.</param>
        /// <param name="initialPosition">The initial position.</param>
        public ParticleEmitter(ParticleSystem particleSystem, float particlesPerSecond, Vector3 initialPosition)
        {
            // set up variables
            this.particleSystem = particleSystem;
            timeBetweenParticles = 1.0f / particlesPerSecond;
            previousPosition = initialPosition;
        }

        /// <summary>
        /// Updates the emitter.
        /// </summary>
        /// <param name="gameTime">The game time.</param>
        /// <param name="newPosition">The new position.</param>
        public void Update(GameTime gameTime, Vector3 newPosition)
        {
            // make sure time has passed
            if (gameTime.ElapsedGameTime > 0.0f)
            {
                // calculate the velocity
                Vector3 velocity = (newPosition - previousPosition) / gameTime.ElapsedGameTime;

                // take into account any time left over from the last update
                float totalTime = timeLeftOver + gameTime.ElapsedGameTime;
                float currentTime = -timeLeftOver;

                // create particles as long as we have time to spare
                while (totalTime > timeBetweenParticles)
                {
                    // update the times
                    currentTime += timeBetweenParticles;
                    totalTime -= timeBetweenParticles;

                    // figure out the correct particle position
                    Vector3 position = Vector3.Lerp(previousPosition, newPosition, currentTime / gameTime.ElapsedGameTime);

                    // create the particle
                    particleSystem.SpawnParticle(position, velocity);
                }

                // store any time we didn't use
                timeLeftOver = totalTime;
            }

            // update the position
            previousPosition = newPosition;
        }
    }
}
