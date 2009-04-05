using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimMath;

namespace ConsoleTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Batch batch = new Batch();
            Matrix m1 = new Matrix() { M11 = 2.0f, M22 = 2.0f, M33 = 2.0f, M44 = 2.0f };

            var m2 = batch.Add(MatrixOps.Identity());
            var mult = batch.Add(MatrixOps.Multiply(m1, m2));
            var inv = batch.Add(MatrixOps.Inverse(mult));
            batch.Process();

            Matrix result1 = inv.GetResult<Matrix>(0);
            float result2 = inv.GetResult<float>(1);
        }
    }
}
