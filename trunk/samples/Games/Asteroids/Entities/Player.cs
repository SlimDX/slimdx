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
using System.Windows.Forms;
using SampleFramework;
using SlimDX;
using System.Drawing;

namespace Asteroids
{
    class Player : Entity
    {
        const float Acceleration = 0.5f;
        const float RespawnInterval = 3.0f;
        const float RespawnBuffer = 50.0f;
        static readonly float RotationDelta = Helpers.ToRadians(5.0f);
        static readonly Vector2 SpawnPoint = new Vector2(0.0f, 0.0f);

        Weapon currentWeapon;
        ParticleSystem engineTrail;
        ParticleEmitter engineTrailEmitter;

        public Player(Asteroids game)
            : base(game)
        {
            Friction = 0.1f;
            MaxVelocity = 25.0f;

            Model = VectorModel.FromFile("Content/Models/PlayerModel.xml");
            Game.Resources.Add(Model);

            currentWeapon = new PrimaryWeapon(Game);

            engineTrail = new ParticleSystem(1000);
            engineTrail.Duration = 1.5f;
            engineTrail.DurationRandomness = 1.5f;
            engineTrail.EmitterVelocitySensitivity = 0.1f;
            engineTrail.MinimumVelocity = new Vector2(0.0f, -1.0f);
            engineTrail.MaximumVelocity = new Vector2(1.0f, 1.0f);
            engineTrail.MinimumColor = Color.FromArgb(128, 255, 255, 255);
            engineTrail.MaximumColor = Color.FromArgb(64, 255, 255, 255);
            engineTrail.MinimumStartSize = 2.0f;
            engineTrail.MaximumStartSize = 5.0f;
            engineTrail.MinimumEndSize = 5.0f;
            engineTrail.MaximumEndSize = 7.0f;
            engineTrailEmitter = new ParticleEmitter(engineTrail, new Vector3(Position, 0.0f));
            Game.Resources.Add(engineTrail);
            Game.Components.Add(engineTrail);
        }

        /// <summary>
        /// Does cool things to the player.
        /// </summary>
        /// <param name="gameTime">What do you think it is?</param>
        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            if (Game.IsKeyPressed(Keys.Left) || Game.IsKeyPressed(Keys.A))
                Rotation -= RotationDelta;
            else if (Game.IsKeyPressed(Keys.Right) || Game.IsKeyPressed(Keys.D))
                Rotation += RotationDelta;

            // thruster input (hehe, thruster)
            if (Game.IsKeyPressed(Keys.Up) || Game.IsKeyPressed(Keys.W))
            {
                Velocity = new Vector2(
                    Velocity.X + Acceleration * (float)Math.Sin(Rotation),
                    Velocity.Y + Acceleration * (float)Math.Cos(Rotation));
            }

            engineTrailEmitter.ParticlesPerSecond = Velocity.Length() * 10;
            engineTrail.SetCamera(Game.Camera.ViewMatrix, Game.Camera.ProjectionMatrix);
            engineTrailEmitter.Update(gameTime, new Vector3(Position, 0.0f));

            currentWeapon.Update(gameTime);

            if (Game.IsKeyPressedThisFrame(Keys.Space))
            {
                // wait the next frame to avoid dual fire
                currentWeapon.Fire(Position, Rotation);
                currentWeapon.ResetCoolDown();
            }
            else if (Game.IsKeyPressed(Keys.Space))
                currentWeapon.AutoFire(Position, Rotation);

            if (Game.IsKeyPressedThisFrame(Keys.Down))
                Rotation += (float)Math.PI;
            
            BoundingSphere sphere = new BoundingSphere(new Vector3(Position, 0), Model.Radius);
            foreach (IGameComponent component in Game.Components)
            {
                Entity entity = component as Entity;
                if (entity == null)
                    continue;

                if (entity.Collides(GetType(), sphere))
                {
                    // player died, haha
                    IsDead = true;
                    break;
                }
            }
        }

        /// <summary>
        /// Draws the entity. God you people are dumb.
        /// </summary>
        public override void Draw()
        {
            base.Draw();

            currentWeapon.Draw();
        }

        public override void OnDeath()
        {
            // add a new trigger to happen when we need to respawn
            Game.Explosion.Activate(Position, 1000.0f);
            Trigger trigger = new Trigger(RespawnInterval) { Repeat = true };
            trigger.Activated += Respawn;
            Game.Triggers.Add(trigger);
        }

        public override bool Collides(Type type, BoundingSphere boundingSphere)
        {
            if (type == typeof(PrimaryWeapon) || type == typeof(Alien))
                return false;

            return base.Collides(type, boundingSphere);
        }

        void Respawn(object sender, EventArgs e)
        {
            // make sure there are no asteroids around that could kill us
            Trigger trigger = sender as Trigger;
            BoundingSphere sphere = new BoundingSphere(new Vector3(SpawnPoint, 0), Model.Radius * 5.0f);
            foreach (IGameComponent component in Game.Components)
            {
                Entity entity = component as Entity;
                if (entity == null)
                    continue;

                // check for a collision within the allowed buffer time
                if (entity.Collides(GetType(), sphere))
                {
                    // no good, wait a bit more
                    trigger.Duration = RespawnInterval / 2;
                    return;
                }
            }

            // otherwise, we can go ahead and respawn the player
            trigger.Repeat = false;
            IsDead = false;
            Position = SpawnPoint;
            Velocity = Vector2.Zero;
            Rotation = float.Epsilon;
            currentWeapon.Clear();
            Game.Components.Add(this);
        }
    }
}
