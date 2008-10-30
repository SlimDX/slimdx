using System;

using SlimDX;

namespace SlimDXTests
{
    static class TestUtils
    {
        public const int RandomSeed = 50;

        public static Plane MakeRandomPlane()
        {
            Random rand = new Random(RandomSeed);
            Plane plane = new Plane();

            plane.Normal = new Vector3(
                (float)rand.NextDouble(),
                (float)rand.NextDouble(),
                (float)rand.NextDouble()
            );
            plane.D = (float)rand.NextDouble();

            return plane;
        }

        public static Matrix MakeRandomMatrix()
        {
            Random rand = new Random(RandomSeed);
            Matrix matrix = new Matrix();

            matrix.M11 = (float)rand.NextDouble();
            matrix.M12 = (float)rand.NextDouble();
            matrix.M13 = (float)rand.NextDouble();
            matrix.M14 = (float)rand.NextDouble();
            matrix.M21 = (float)rand.NextDouble();
            matrix.M22 = (float)rand.NextDouble();
            matrix.M23 = (float)rand.NextDouble();
            matrix.M24 = (float)rand.NextDouble();
            matrix.M31 = (float)rand.NextDouble();
            matrix.M32 = (float)rand.NextDouble();
            matrix.M33 = (float)rand.NextDouble();
            matrix.M34 = (float)rand.NextDouble();
            matrix.M41 = (float)rand.NextDouble();
            matrix.M42 = (float)rand.NextDouble();
            matrix.M43 = (float)rand.NextDouble();
            matrix.M44 = (float)rand.NextDouble();

            return matrix;
        }
    }
}
