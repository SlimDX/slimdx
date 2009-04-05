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

			var v1 = new Vector() { X = 1, Y = 1, Z = 1, W = 0};
			var result3 = batch.Add(VectorOps.Transform(v1, inv.FirstResult));

			var trans = batch.Add(MatrixOps.TranslationFromVector(new Vector() {X = 2, Y = 2, Z = 2, W = 0}));
			var doubled = batch.Add(VectorOps.Transform(new Vector() {X = 1, Y = 1, Z = 1, W = 1}, trans));

			var va = new Vector[] { new Vector() { X = 1, Y = 2, Z = 3, W = 0 }, new Vector() { X = 2, Y = 3, Z = 4, W = 0 }, new Vector() { X = 0, Y = 0, Z = 0, W = 0 } };
			var vd = new Vector[va.Length];

			batch.Add(VectorOps.TransformStream(vd, va, inv.FirstResult));
			batch.Process();

			var result1 = inv.FirstResult.GetData();
			var result2 = inv.SecondResult.GetData();

			Console.WriteLine(result1);
			Console.WriteLine(result2);
			Console.WriteLine(result3.GetData());
			Console.WriteLine(doubled.GetData());

			foreach(var v in vd) {
				Console.WriteLine(v);
			}
		}
	}
}
