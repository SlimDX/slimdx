using System;
using System.Collections.Generic;
using System.Text;

namespace Asteroids
{
    class AlienWeapon : Weapon
    {
        public AlienWeapon(Asteroids game)
            : base(game)
        {
            BulletModel = VectorModel.FromFile("Content/Models/AlienBullet.xml");

            if (!Game.Resources.Contains(BulletModel))
                Game.Resources.Add(BulletModel);

            CoolDownRate = 8.0f;
            BulletSpeed = 10.0f;
            BulletRotation = 4.0f;
            BulletLife = 100.0f;
        }
    }
}
