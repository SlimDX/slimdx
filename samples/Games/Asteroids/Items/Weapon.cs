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
using SampleFramework;
using SlimDX;

namespace Asteroids
{
    /// <summary>
    /// Represents a weapon.
    /// </summary>
    abstract class Weapon
    {
        /// <summary>
        /// Gets the game.
        /// </summary>
        /// <value>The game.</value>
        public Asteroids Game
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the cool down rate.
        /// </summary>
        /// <value>The cool down rate.</value>
        public float CoolDownRate
        {
            get;
            protected set;
        }

        /// <summary>
        /// Gets or sets the bullet speed.
        /// </summary>
        /// <value>The bullet speed.</value>
        public float BulletSpeed
        {
            get;
            protected set;
        }

        /// <summary>
        /// Gets or sets the bullet rotation.
        /// </summary>
        /// <value>The bullet rotation.</value>
        public float BulletRotation
        {
            get;
            protected set;
        }

        /// <summary>
        /// Gets or sets the bullet life.
        /// </summary>
        /// <value>The bullet life.</value>
        public float BulletLife
        {
            get;
            protected set;
        }

        /// <summary>
        /// Gets or sets the damage.
        /// </summary>
        /// <value>The damage.</value>
        public float Damage
        {
            get;
            protected set;
        }

        /// <summary>
        /// Gets or sets the bullet model.
        /// </summary>
        /// <value>The bullet model.</value>
        public VectorModel BulletModel
        {
            get;
            protected set;
        }

        /// <summary>
        /// Gets the bullet count.
        /// </summary>
        /// <value>The bullet count.</value>
        public int BulletCount
        {
            get { return Bullets.Count; }
        }

        /// <summary>
        /// Gets the bullets.
        /// </summary>
        /// <value>The bullets.</value>
        protected List<Bullet> Bullets
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the cool down.
        /// </summary>
        /// <value>The cool down.</value>
        protected float CoolDown
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Weapon"/> class.
        /// </summary>
        /// <param name="game">The game.</param>
        public Weapon(Asteroids game)
        {
            // create the list of bullets
            Bullets = new List<Bullet>();

            // store the reference
            Game = game;
        }

        /// <summary>
        /// Resets the cool down.
        /// </summary>
        public void ResetCoolDown()
        {
            // reset the timer
            CoolDown = CoolDownRate;
        }

        /// <summary>
        /// Updates the bullets being managed by the weapon.
        /// </summary>
        /// <param name="gameTime">The game time.</param>
        public virtual void Update(GameTime gameTime)
        {
            // update the cool down rate
            CoolDown -= gameTime.ElapsedGameTime / Asteroids.TargetFrameRate;

            // update the active bullets
            foreach (Bullet bullet in Bullets)
            {
                // decrease the life on the bullet
                // I feel old
                bullet.Life -= gameTime.ElapsedGameTime / Asteroids.TargetFrameRate;
                if (bullet.Life > 0.0f)
                {
                    // update the bullet
                    bullet.Update(gameTime);

                    // check against each entity
                    BoundingSphere sphere = new BoundingSphere(new Vector3(bullet.Position, 0), BulletModel.Radius);
                    foreach (Entity entity in Game.Entities)
                    {
                        // player can't shoot himself (well...)
                        if (entity is Player)
                            continue;

                        // check for enemy objects to collide with
                        if (entity.Collides(sphere))
                        {
                            // entity suicide! when will it end?
                            entity.IsDead = true;
                            bullet.IsDead = true;
                            break;
                        }
                    }
                }
                else
                    bullet.IsDead = true;
            }

            // clear out the dead bullets
            // no graves for you, muahaha!
            for (int i = Bullets.Count - 1; i >= 0; i--)
                if (Bullets[i].IsDead)
                    Bullets.RemoveAt(i);
        }

        /// <summary>
        /// Draws the bullets.
        /// </summary>
        public virtual void Draw()
        {
            // draw the active bullets
            foreach (Bullet bullet in Bullets)
                bullet.Draw();
        }

        /// <summary>
        /// Fires the weapon instantaneously.
        /// </summary>
        /// <param name="position">The position of the player.</param>
        /// <param name="rotation">The rotation of the player.</param>
        public virtual void Fire(Vector2 position, float rotation)
        {
            // fire the bullet
            // FIRE I SAID!
            Bullet bullet = new Bullet(Game, BulletModel);
            bullet.Speed = BulletSpeed;
            bullet.RotationalVelocity = BulletRotation;
            bullet.Direction = new Vector2((float)Math.Sin(rotation), (float)Math.Cos(rotation));
            bullet.Position = position;
            bullet.Life = BulletLife;
            Bullets.Add(bullet);
        }

        /// <summary>
        /// Performs a shot of the weapon when in auto-fire mode. A shot may or may not
        /// occur depending on the cool down rate.
        /// </summary>
        /// <param name="position">The position of the player.</param>
        /// <param name="rotation">The rotation of the player.</param>
        public virtual void AutoFire(Vector2 position, float rotation)
        {
            // make sure the weapon has cooled down enough to fire
            if (CoolDown > 0.0f)
                return;

            // fire the bullet
            Fire(position, rotation);

            // reset the timer
            CoolDown = CoolDownRate;
        }
    }
}
