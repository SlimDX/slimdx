using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimMath;

namespace ConsoleTest {
	class Program {
		static void Main(string[] args) {
			var batch = new Batch();
			var m = new Matrix();
			m.M11 = m.M22 = m.M33 = m.M44 = 2.0f;
			var ident = batch.Add(new MatrixOps.Identity());
			var mult = batch.Add(new MatrixOps.Multiply(ident, new Matrix(), 0));
			var inverse = batch.Add(new MatrixOps.Inverse(mult, 0));
			batch.Process();
		}
	}
}
