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
using System.Globalization;
using SlimDX;

namespace Asteroids
{
    /// <summary>
    /// Specifies possible asteroid sizes.
    /// </summary>
    enum AsteroidSize
    {
        /// <summary>
        /// Small asteroids.
        /// </summary>
        Small,

        /// <summary>
        /// Medium asteroids.
        /// </summary>
        Medium,

        /// <summary>
        /// Large asteroids.
        /// </summary>
        Large,

        /// <summary>
        /// Absolutely, rediculously huge asteroids.
        /// </summary>
        Huge
    }

    /// <summary>
    /// Represents an asteroid.
    /// </summary>
    class Asteroid : Entity
    {
        // constants
        const float MaxAsteroidSpeed = 8.0f;
        const float MinAsteroidSpeed = -8.0f;
        const float MaxAsteroidSpin = 0.05f;
        const float MinAsteroidSpin = -0.05f;

        /// <summary>
        /// Gets the asteroid count.
        /// </summary>
        /// <value>The asteroid count.</value>
        public static int AsteroidCount
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the size.
        /// </summary>
        /// <value>The size.</value>
        public AsteroidSize Size
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Asteroid"/> class.
        /// </summary>
        /// <param name="game">The game.</param>
        /// <param name="size">The size.</param>
        public Asteroid(Asteroids game, AsteroidSize size)
            : base(game)
        {
            // load the model
            int asteroidType = Asteroids.Random.Next(1, 3);
            string modelFile = "Content/Models/";

            // which model we load depends on the size
            Size = size;
            if (size == AsteroidSize.Small)
                modelFile += "Small";
            else if (size == AsteroidSize.Medium)
                modelFile += "Medium";
            else if (size == AsteroidSize.Large)
                modelFile += "Large";
            else if (size == AsteroidSize.Huge)
                modelFile += "Huge";
            else
                throw new InvalidOperationException("Oh my gosh, you are retarded!");

            // load the final model
            modelFile += "Asteroid";
            if (size != AsteroidSize.Huge)
                modelFile += asteroidType.ToString(CultureInfo.InvariantCulture);
            modelFile += ".xml";
            Model = VectorModel.FromFile(modelFile);
            if (!game.Resources.Contains(Model))
                game.Resources.Add(Model);

            // set properties
            Velocity = new Vector2(RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed), RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed));
            RotationalVelocity = RandomFloat(MinAsteroidSpin, MaxAsteroidSpin);

            // update the statistics
            AsteroidCount++;
        }

        /// <summary>
        /// Called when the entity dies.
        /// </summary>
        public override void OnDeath()
        {
            // we died :(
            AsteroidCount--;

            // if we are large, break into smaller pieces
            AsteroidSize newSize;
            if (Size == AsteroidSize.Huge)
                newSize = AsteroidSize.Large;
            else if (Size == AsteroidSize.Large)
                newSize = AsteroidSize.Medium;
            else if (Size == AsteroidSize.Medium)
                newSize = AsteroidSize.Small;
            else
                return;

            // create the new asteroids
            CreateNewAsteroid(newSize);
            CreateNewAsteroid(newSize);
        }

        /// <summary>
        /// Creates a new asteroid.
        /// </summary>
        void CreateNewAsteroid(AsteroidSize size)
        {
            // create the asteroid
            Asteroid asteroid = new Asteroid(Game, size);

            // set properties
            asteroid.Position = Position;
            asteroid.Velocity = new Vector2(RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed), RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed));
            asteroid.RotationalVelocity = RandomFloat(MinAsteroidSpin, MaxAsteroidSpin);

            // add the item to the list
            Game.Entities.Add(asteroid);
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
