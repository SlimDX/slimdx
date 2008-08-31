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
    /// <summary>
    /// Represents a game entity.
    /// </summary>
    abstract class Entity
    {
        // constants
        const float VelocityEpsilon = 0.0001f;

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
        /// Gets or sets the model.
        /// </summary>
        /// <value>The model.</value>
        public VectorModel Model
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the position.
        /// </summary>
        /// <value>The position.</value>
        public Vector2 Position
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the velocity.
        /// </summary>
        /// <value>The velocity.</value>
        public Vector2 Velocity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the rotational velocity.
        /// </summary>
        /// <value>The rotational velocity.</value>
        public float RotationalVelocity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the rotation.
        /// </summary>
        /// <value>The rotation.</value>
        public float Rotation
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the alpha.
        /// </summary>
        /// <value>The alpha.</value>
        public float Alpha
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the friction.
        /// </summary>
        /// <value>The friction.</value>
        public float Friction
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the maximum velocity.
        /// </summary>
        /// <value>The maximum velocity.</value>
        public float MaxVelocity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="Entity"/> should wrap around the screen.
        /// </summary>
        /// <value><c>true</c> if the entity should wrap around the screen; otherwise, <c>false</c>.</value>
        public bool Wrap
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is collidable.
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is collidable; otherwise, <c>false</c>.
        /// </value>
        public bool IsCollidable
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is dead.
        /// </summary>
        /// <value><c>true</c> if this instance is dead; otherwise, <c>false</c>.</value>
        public bool IsDead
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Entity"/> class.
        /// </summary>
        /// <param name="game">The game.</param>
        protected Entity(Asteroids game)
        {
            // store the game
            Game = game;

            // set initial values
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
            // update the velocity for friction
            Velocity -= Vector2.Normalize(Velocity) * Friction;

            // cap the Velocity
            Velocity = new Vector2(
                Clamp(Velocity.X, -MaxVelocity, MaxVelocity),
                Clamp(Velocity.Y, -MaxVelocity, MaxVelocity));

            // cut down on accuracy errors
            if (Velocity.X < VelocityEpsilon && Velocity.X > -VelocityEpsilon)
                Velocity = new Vector2(0, Velocity.Y);
            if (Velocity.Y < VelocityEpsilon && Velocity.Y > -VelocityEpsilon)
                Velocity = new Vector2(Velocity.X, 0);

            // update the position based upon the velocity
            Position += Velocity;

            // check if we should wrap
            if (Wrap)
            {
                // wrap the position for the edge of the screen
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

            // update the rotation based upon the velocity
            Rotation += RotationalVelocity;
        }

        /// <summary>
        /// Draws the entity. God you people are dumb.
        /// </summary>
        public virtual void Draw()
        {
            // draw the model
            Model.Draw(Position, Rotation, Alpha);
        }

        /// <summary>
        /// Determines whether the entity collides with the specified bounding sphere.
        /// </summary>
        /// <param name="boundingSphere">The bounding sphere.</param>
        /// <returns><c>true</c> if a collision occurs; otherwise, <c>false</c>.</returns>
        public virtual bool Collides(BoundingSphere boundingSphere)
        {
            // default behavior is to check the model's bounding volume
            BoundingSphere local = new BoundingSphere(new Vector3(Position, 0), Model.Radius);
            if (IsCollidable && BoundingSphere.Intersects(local, boundingSphere))
                return true;
            else
                return false;
        }

        /// <summary>
        /// Called when the entity dies.
        /// </summary>
        public virtual void OnDeath()
        {
        }

        /// <summary>
        /// Converts degrees to radians.
        /// </summary>
        /// <param name="degrees">The degrees.</param>
        /// <returns>The equivalent value in radians.</returns>
        static protected float ToRadians(float degrees)
        {
            // return the converted value
            return (degrees / 180) * (float)Math.PI;
        }

        /// <summary>
        /// Restricts a value to be within a specified range.
        /// </summary>
        /// <typeparam name="T">The type of the value.</typeparam>
        /// <param name="value">The value to clamp.</param>
        /// <param name="min">The minimum value.</param>
        /// <param name="max">The maximum value.</param>
        /// <returns>The clamped value.</returns>
        static protected T Clamp<T>(T value, T min, T max) where T : IComparable
        {
            // check if the value is over the bounds
            if (value.CompareTo(max) >= 0)
                return max;
            if (value.CompareTo(min) <= 0)
                return min;
            return value;
        }
    }
}
