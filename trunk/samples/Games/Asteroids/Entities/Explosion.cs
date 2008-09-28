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
using System.Drawing;
using SlimDX;

namespace Asteroids
{
    class Explosion : Entity
    {
        const int ParticleCount = 360;
        const int MaxInstances = 10;
        float speed = 100.0f;

        ParticleSystem particleSystem;

        public Explosion(Asteroids game)
            : base(game)
        {
            particleSystem = new ParticleSystem(ParticleCount * MaxInstances);
            Game.Resources.Add(particleSystem);
            Game.Components.Add(particleSystem);

            particleSystem.Duration = 2.0f;
            particleSystem.DurationRandomness = 1.5f;
            particleSystem.MinimumVelocity = new Vector2(0.0f, -1.0f);
            particleSystem.MaximumVelocity = new Vector2(1.0f, 1.0f);
            particleSystem.MinimumColor = Color.FromArgb(200, 255, 255, 255);
            particleSystem.MaximumColor = Color.FromArgb(100, 255, 255, 255);
            particleSystem.MinimumStartSize = 2.0f;
            particleSystem.MaximumStartSize = 5.0f;
            particleSystem.MinimumEndSize = 5.0f;
            particleSystem.MaximumEndSize = 7.0f;
        }

        public void Activate(Vector2 position, float speed)
        {
            this.speed = speed;
            Position = position;
            Activate();
        }

        void Activate()
        {
            float angleIncrement = (float)(2.0f * Math.PI / (double)ParticleCount);
            float angle = 0.0f;

            for (int i = 0; i < ParticleCount; i++)
            {
                Vector3 velocity = new Vector3((float)Math.Cos(angle) * speed, (float)Math.Sin(angle) * speed, 0.0f);
                particleSystem.SpawnParticle(new Vector3(Position, 0.0f), velocity);

                angle += angleIncrement;
            }
        }

        /// <summary>
        /// Does cool things to the entity, if you know what I mean.
        /// </summary>
        /// <param name="gameTime">What do you think it is?</param>
        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            particleSystem.SetCamera(Game.Camera.ViewMatrix, Game.Camera.ProjectionMatrix);
        }
    }
}
