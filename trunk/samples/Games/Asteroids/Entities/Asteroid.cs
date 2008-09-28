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
    enum AsteroidSize
    {
        Small = 100,
        Medium = 500,
        Large = 1000,
        Huge = 2000
    }

    class Asteroid : Entity
    {
        const float MaxAsteroidSpeed = 8.0f;
        const float MinAsteroidSpeed = -8.0f;
        const float MaxAsteroidSpin = 0.05f;
        const float MinAsteroidSpin = -0.05f;

        public static int AsteroidCount
        {
            get;
            private set;
        }

        public AsteroidSize Size
        {
            get;
            set;
        }

        public Asteroid(Asteroids game, AsteroidSize size)
            : base(game)
        {
            int asteroidType = Asteroids.Random.Next(1, 3);
            string modelFile = "Content/Models/";

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

            modelFile += "Asteroid";
            if (size != AsteroidSize.Huge)
                modelFile += asteroidType.ToString(CultureInfo.InvariantCulture);
            modelFile += ".xml";
            Model = VectorModel.FromFile(modelFile);
            if (!game.Resources.Contains(Model))
                game.Resources.Add(Model);

            Position = new Vector2(Helpers.RandomFloat(Game.WorldBounds.X, Game.WorldBounds.Z), Helpers.RandomFloat(Game.WorldBounds.Y, Game.WorldBounds.W));
            Velocity = new Vector2(Helpers.RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed), Helpers.RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed));
            RotationalVelocity = Helpers.RandomFloat(MinAsteroidSpin, MaxAsteroidSpin);

            AsteroidCount++;
        }

        public override void OnDeath()
        {
            // we died :(
            Game.Explosion.Activate(Position, 100.0f);
            AsteroidCount--;
            Game.Score += (int)Size;

            AsteroidSize newSize;
            if (Size == AsteroidSize.Huge)
                newSize = AsteroidSize.Large;
            else if (Size == AsteroidSize.Large)
                newSize = AsteroidSize.Medium;
            else if (Size == AsteroidSize.Medium)
                newSize = AsteroidSize.Small;
            else
                return;

            CreateNewAsteroid(newSize);
            CreateNewAsteroid(newSize);
        }

        void CreateNewAsteroid(AsteroidSize size)
        {
            Asteroid asteroid = new Asteroid(Game, size);

            asteroid.Position = Position;
            asteroid.Velocity = new Vector2(Helpers.RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed), Helpers.RandomFloat(MinAsteroidSpeed, MaxAsteroidSpeed));
            asteroid.RotationalVelocity = Helpers.RandomFloat(MinAsteroidSpin, MaxAsteroidSpin);

            Game.Components.Add(asteroid);
        }
    }
}
