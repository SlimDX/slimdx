using System;
using System.Diagnostics;
using SlimMath;

namespace ConsoleTest {
	class Program {
		static void Main(string[] args) {
			var w = new Stopwatch();
			
			var batch = new Batch();
			var m1 = new Matrix() { M11 = 2.0f, M22 = 2.0f, M33 = 2.0f, M44 = 2.0f };
			
			var m2 = batch.Add(MatrixOps.Identity());
			
			var mult = batch.Add(MatrixOps.Multiply(m1, m2));
			var inv = batch.Add(MatrixOps.Inverse(mult));

			/*for (int i = 0; i < 1000; ++i )
				batch.Add(MatrixOps.Multiply(m1, m2));*/

			var v1 = new Vector() { X = 1, Y = 1, Z = 1, W = 0};
			var result3 = batch.Add(VectorOps.Transform(v1, inv.FirstResult));

			var trans = batch.Add(MatrixOps.TranslationFromVector(new Vector() {X = 2, Y = 2, Z = 2, W = 0}));
			var doubled = batch.Add(VectorOps.Transform(new Vector() {X = 1, Y = 1, Z = 1, W = 1}, trans));

			w.Start();
			batch.Process();
			w.Stop();

			Console.WriteLine("{0} ms elapsed.", w.ElapsedMilliseconds);

			var result1 = inv.FirstResult.GetData();
			var result2 = inv.SecondResult.GetData();

			Console.WriteLine(result1);
			Console.WriteLine(result2);
			Console.WriteLine(result3.GetData());
			Console.WriteLine(doubled.GetData());
		}
	}
}
