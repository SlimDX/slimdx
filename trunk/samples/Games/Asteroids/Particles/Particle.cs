using System;
using System.Collections.Generic;
using System.Text;
using SlimDX;
using SampleFramework;

namespace Asteroids
{
    class Particle
    {
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

        public float Life
        {
            get;
            set;
        }

        public Color4 Color
        {
            get;
            set;
        }

        public float ElapsedTime
        {
            get;
            set;
        }

        public bool Active
        {
            get { return ElapsedTime < Life; }
        }

        public void Update(GameTime gameTime)
        {
            ElapsedTime += gameTime.ElapsedGameTime;

            Position += Velocity;
        }
    }
}
