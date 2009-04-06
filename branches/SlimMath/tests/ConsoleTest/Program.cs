using System;
using System.Diagnostics;
using SlimMath;

namespace ConsoleTest
{
	class Program
	{
		static void Main(string[] args)
		{
			var w = new Stopwatch();

			w.Start();
			var batch = new Batch();
			
			var m1 = new Matrix() { M11 = 2.0f, M22 = 2.0f, M33 = 2.0f, M44 = 2.0f };
			
			var m2 = batch.Add(MatrixOps.Identity());
			
			var mult = batch.Add(MatrixOps.Multiply(m1, m2));
			
			for (int i = 0; i < 1000; ++i )
				batch.Add(MatrixOps.Multiply(m1, m2));

			var v1 = new Vector() { X = 1, Y = 1, Z = 1, W = 0};

			var trans = batch.Add(MatrixOps.Translation(new Vector() {X = 2, Y = 2, Z = 2, W = 0}));
			var doubled = batch.Add(VectorOps.Transform(new Vector() {X = 1, Y = 1, Z = 1, W = 1}, trans));
			
			
			batch.Process();
			w.Stop();

			Console.WriteLine("{0} ms", w.ElapsedMilliseconds);
			Console.WriteLine(doubled.GetData());
		}
	}
}
