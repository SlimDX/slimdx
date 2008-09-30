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
using SampleFramework;
using SlimDX;

namespace Asteroids
{
    abstract class Entity : IGameComponent
    {
        const float VelocityEpsilon = 0.0001f;

        public Asteroids Game
        {
            get;
            private set;
        }

        public VectorModel Model
        {
            get;
            set;
        }

        public Vector2 Position
        {
            get;
            set;
        }

        public Vector2 Velocity
        {
            get;
            set;
        }

        public float RotationalVelocity
        {
            get;
            set;
        }

        public float Rotation
        {
            get;
            set;
        }

        public float Alpha
        {
            get;
            set;
        }

        public float Friction
        {
            get;
            set;
        }

        public float MaxVelocity
        {
            get;
            set;
        }

        public bool Wrap
        {
            get;
            set;
        }

        public bool IsCollidable
        {
            get;
            set;
        }

        public bool IsDead
        {
            get;
            set;
        }

        protected Entity(Asteroids game)
        {
            Game = game;

            Alpha = 1.0f;
            MaxVelocity = float.MaxValue;
            Rotation = float.Epsilon;
            Wrap = true;
            IsCollidable = true;
        }

        /// <summary>
        /// Does cool things to the entity, if you know what I mean.
        /// </summary>
        /// <param name="gameTime">What do you think it is?</param>
        public virtual void Update(GameTime gameTime)
        {
            Velocity -= Vector2.Normalize(Velocity) * Friction;

            Velocity = new Vector2(
                Helpers.Clamp(Velocity.X, -MaxVelocity, MaxVelocity),
                Helpers.Clamp(Velocity.Y, -MaxVelocity, MaxVelocity));

            if (Velocity.X < VelocityEpsilon && Velocity.X > -VelocityEpsilon)
                Velocity = new Vector2(0, Velocity.Y);
            if (Velocity.Y < VelocityEpsilon && Velocity.Y > -VelocityEpsilon)
                Velocity = new Vector2(Velocity.X, 0);

            Position += Velocity;

            if (Wrap && Model != null)
            {
                float halfWidth = Model.Width / 2;
                float halfHeight = Model.Height / 2;
                if (Position.X + halfWidth < Game.WorldBounds.X)
                    Position = new Vector2(Game.WorldBounds.Z, Position.Y);
                if (Position.X - halfWidth > Game.WorldBounds.Z)
                    Position = new Vector2(Game.WorldBounds.X, Position.Y);
                if (Position.Y + halfHeight < Game.WorldBounds.Y)
                    Position = new Vector2(Position.X, Game.WorldBounds.W);
                if (Position.Y - halfHeight > Game.WorldBounds.W)
                    Position = new Vector2(Position.X, Game.WorldBounds.Y);
            }

            Rotation += RotationalVelocity;
        }

        /// <summary>
        /// Draws the entity. God you people are dumb.
        /// </summary>
        public virtual void Draw()
        {
            if (Model != null)
                Model.Draw(Position, Rotation, Alpha);
        }

        public virtual bool Collides(Type type, BoundingSphere boundingSphere)
        {
            if (Model == null)
                return false;

            if (type == GetType())
                return false;

            BoundingSphere local = new BoundingSphere(new Vector3(Position, 0), Model.Radius);
            if (IsCollidable && BoundingSphere.Intersects(local, boundingSphere))
                return true;
            else
                return false;
        }

        public virtual void OnDeath()
        {
        }
    }
}
