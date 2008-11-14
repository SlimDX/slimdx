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
    abstract class Weapon
    {
        public Asteroids Game
        {
            get;
            private set;
        }

        public float CoolDownRate
        {
            get;
            protected set;
        }

        public float BulletSpeed
        {
            get;
            protected set;
        }

        public float BulletRotation
        {
            get;
            protected set;
        }

        public float BulletLife
        {
            get;
            protected set;
        }

        public VectorModel BulletModel
        {
            get;
            protected set;
        }

        protected List<Bullet> Bullets
        {
            get;
            private set;
        }

        protected float CoolDown
        {
            get;
            set;
        }

        protected Weapon(Asteroids game)
        {
            Bullets = new List<Bullet>();

            Game = game;
        }

        public void ResetCoolDown()
        {
            CoolDown = CoolDownRate;
        }

        public virtual void Update(GameTime gameTime)
        {
            CoolDown--;

            foreach (Bullet bullet in Bullets)
            {
                // decrease the life on the bullet
                // I feel old
                bullet.Life--;
                if (bullet.Life > 0.0f)
                {
                    bullet.Update(gameTime);

                    BoundingSphere sphere = new BoundingSphere(new Vector3(bullet.Position, 0), BulletModel.Radius);
                    foreach (IGameComponent component in Game.Components)
                    {
                        Entity entity = component as Entity;
                        if (entity == null)
                            continue;

                        if (entity.Collides(GetType(), sphere))
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

        public virtual void Draw()
        {
            foreach (Bullet bullet in Bullets)
                bullet.Draw();
        }

        public void Clear()
        {
            Bullets.Clear();
        }

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

        public virtual void AutoFire(Vector2 position, float rotation)
        {
            // make sure the weapon has cooled down enough to fire
            if (CoolDown > 0.0f)
                return;

            Fire(position, rotation);

            CoolDown = CoolDownRate;
        }
    }
}
