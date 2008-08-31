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

namespace Asteroids
{
    /// <summary>
    /// Represents the player.
    /// </summary>
    class Player : Entity
    {
        // constants
        const float Acceleration = 0.5f;
        const float RespawnInterval = 1.0f;
        const float RespawnBuffer = 50.0f;
        static readonly float RotationDelta = ToRadians(5.0f);
        static readonly Vector2 SpawnPoint = new Vector2(0.0f, 0.0f);

        // variables
        Weapon currentWeapon;

        /// <summary>
        /// Initializes a new instance of the <see cref="Player"/> class.
        /// </summary>
        /// <param name="game">The game.</param>
        public Player(Asteroids game)
            : base(game)
        {
            // set player settings
            Friction = 0.1f;
            MaxVelocity = 25.0f;

            // load the player model
            Model = VectorModel.FromFile("Content/Models/PlayerModel.xml");
            Game.Resources.Add(Model);

            // set the default weapon
            currentWeapon = new PrimaryWeapon(Game);
        }

        /// <summary>
        /// Does cool things to the player.
        /// </summary>
        /// <param name="gameTime">What do you think it is?</param>
        public override void Update(GameTime gameTime)
        {
            // call the base method
            base.Update(gameTime);

            // check current input for rotation
            if (Game.IsKeyPressed(Keys.Left) || Game.IsKeyPressed(Keys.A))
                Rotation -= RotationDelta;
            else if (Game.IsKeyPressed(Keys.Right) || Game.IsKeyPressed(Keys.D))
                Rotation += RotationDelta;

            // thruster input (hehe, thruster)
            if (Game.IsKeyPressed(Keys.Up) || Game.IsKeyPressed(Keys.W))
            {
                // update the velocity
                Velocity = new Vector2(
                    Velocity.X + Acceleration * (float)Math.Sin(Rotation),
                    Velocity.Y + Acceleration * (float)Math.Cos(Rotation));
            }

            // update the weapon
            currentWeapon.Update(gameTime);

            // fire button
            if (Game.IsKeyPressedThisFrame(Keys.Space))
            {
                // wait the next frame to avoid dual fire
                currentWeapon.Fire(Position, Rotation);
                currentWeapon.ResetCoolDown();
            }
            else if (Game.IsKeyPressed(Keys.Space))
                currentWeapon.AutoFire(Position, Rotation);

            // check for collisions
            BoundingSphere sphere = new BoundingSphere(new Vector3(Position, 0), Model.Radius);
            foreach (Entity entity in Game.Entities)
            {
                // player can't collide with himself
                if (entity == this)
                    continue;

                // check for a collision
                if (entity.Collides(sphere))
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
            // call the base method
            base.Draw();

            // render the weapon
            currentWeapon.Draw();
        }

        /// <summary>
        /// Called when the entity dies.
        /// </summary>
        public override void OnDeath()
        {
            // add a new trigger to happen when we need to respawn
            Trigger trigger = new Trigger(RespawnInterval) { Repeat = true };
            trigger.Activated += Respawn;
            Game.Triggers.Add(trigger);
        }

        /// <summary>
        /// Occurs when the player needs to respawn.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Respawn(object sender, EventArgs e)
        {
            // make sure there are no asteroids around that could kill us
            Trigger trigger = sender as Trigger;
            BoundingSphere sphere = new BoundingSphere(new Vector3(SpawnPoint, 0), Model.Radius);
            foreach (Entity entity in Game.Entities)
            {
                // only care about asteroids
                if (!(entity is Asteroid))
                    continue;

                // check for a collision within the allowed buffer time
                if (entity.Collides(sphere))
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
            Game.Entities.Add(this);
        }
    }
}
