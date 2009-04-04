using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimMath;

namespace ConsoleTest {
	class Program {
		static void Main(string[] args) {
			var batch = new Batch();
			batch.Add(new MatrixOps.Identity());
			batch.Add(new MatrixOps.Multiply(new Matrix(), new Matrix()));
			batch.Add(new MatrixOps.Inverse(new Matrix()));
			float[] results = batch.Process();
		}
	}
}
