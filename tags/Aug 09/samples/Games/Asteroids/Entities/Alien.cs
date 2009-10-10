using System;
using System.Collections.Generic;
using System.Text;
using SampleFramework;
using SlimDX;

namespace Asteroids
{
    class Alien : Entity
    {
        const float MaxAge = 10.0f;
        const float DirectionChangeTiming = 3.0f;
        const float Speed = 10.0f;
        const float FireInterval = 2.0f;

        Weapon weapon;
        float currentDirectionTime;
        float internalRotation;
        float age;
        float fireCounter;
        bool leaving;
        bool leftScreen;

        public Alien(Asteroids game)
            : base(game)
        {
            Model = VectorModel.FromFile("Content/Models/Alien.xml");
            if (!Game.Resources.Contains(Model))
                Game.Resources.Add(Model);

            currentDirectionTime = float.MaxValue;
            weapon = new AlienWeapon(Game);
        }

        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);

            weapon.Update(gameTime);
            fireCounter += gameTime.ElapsedGameTime;
            if (fireCounter > FireInterval)
            {
                fireCounter = 0;
                Player player = Game.Player;
                if (player != null)
                {
                    Vector2 bulletDirection = Vector2.Normalize(player.Position - Position);
                    float bulletRotation = (float)Math.Atan2(bulletDirection.X, bulletDirection.Y);
                    weapon.Fire(Position, bulletRotation);
                }
            }

            // alien needs to leave after he's been around too long
            age += gameTime.ElapsedGameTime;
            if (age > MaxAge)
            {
                Wrap = false;
                leaving = true;
            }

            if (leaving)
            {
                float halfWidth = Model.Width / 2;
                float halfHeight = Model.Height / 2;
                if (Position.X + halfWidth < Game.WorldBounds.X ||
                    Position.X - halfWidth > Game.WorldBounds.Z ||
                    Position.Y + halfHeight < Game.WorldBounds.Y ||
                    Position.Y - halfHeight > Game.WorldBounds.W)
                {
                    leftScreen = true;
                    IsDead = true;
                }
            }

            // pick a new heading every few seconds
            currentDirectionTime += gameTime.ElapsedGameTime;
            if (currentDirectionTime > DirectionChangeTiming && !leaving)
            {
                internalRotation = Helpers.RandomFloat(-2.0f * (float)Math.PI, 2.0f * (float)Math.PI);
                Velocity = new Vector2((float)Math.Sin(internalRotation) * Speed, (float)Math.Cos(internalRotation) * Speed);
                currentDirectionTime = 0;
            }

            BoundingSphere sphere = new BoundingSphere(new Vector3(Position, 0), Model.Radius);
            foreach (IGameComponent component in Game.Components)
            {
                Entity entity = component as Entity;
                if (entity == null)
                    continue;

                if (entity.Collides(GetType(), sphere))
                {
                    // alien died, haha
                    IsDead = true;
                    break;
                }
            }
        }

        public override void Draw()
        {
            base.Draw();

            weapon.Draw();
        }

        public override bool Collides(Type type, BoundingSphere boundingSphere)
        {
            if (base.Collides(type, boundingSphere))
            {
                if (type == typeof(Asteroid) || type == typeof(PrimaryWeapon) || type == typeof(Player))
                    return true;
            }

            return false;
        }

        public override void OnDeath()
        {
            if (!leftScreen)
            {
                Game.Explosion.Activate(Position, 1000.0f);
                Game.Score += 4000;
            }
        }
    }
}
