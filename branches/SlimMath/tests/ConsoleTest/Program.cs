using System;
using SlimMath;

namespace ConsoleTest {
	class Program {
		static void Main(string[] args) {
			var batch = new Batch();
			var m1 = new Matrix() { M11 = 2.0f, M22 = 2.0f, M33 = 2.0f, M44 = 2.0f };

			var m2 = batch.Add(MatrixOps.Identity());
			var mult = batch.Add(MatrixOps.Multiply(m1, m2));
			var inv = batch.Add(MatrixOps.Inverse(mult));
			batch.Process();

			var result1 = inv.FirstResult.GetData();
			var result2 = inv.SecondResult.GetData();

			var v1 = new Vector() { X = 1, Y = 1, Z = 1, W = 0};
			var result3 = batch.Add(VectorOps.Transform4(v1, result1));
			batch.Process();

			Console.WriteLine(result1);
			Console.WriteLine(result2);
			Console.WriteLine(result3.GetData());
		}
	}
}
