/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using NUnit.Framework;
using SlimDX;

namespace SlimDXTests {
	[TestFixture]
	public class Vector3Tests {
		// =========================================================================
		// Tests

		[Test]
		public void ConstructDefault() {
			Vector3 vector = new Vector3();

			Assert.AreEqual( 0.0f, vector.X );
			Assert.AreEqual( 0.0f, vector.Y );
			Assert.AreEqual( 0.0f, vector.Z );
		}

		[Test]
		public void ConstructFromScalar() {
			Vector3 vector = new Vector3( 99.0f );

			Assert.AreEqual( 99.0f, vector.X );
			Assert.AreEqual( 99.0f, vector.Y );
			Assert.AreEqual( 99.0f, vector.Z );
		}
		
		[Test]
		public void ConstructFromXYZ() {
			Vector3 vector = new Vector3( 0.5f, 1.5f, 2.0f );

			Assert.AreEqual( 0.5f, vector.X );
			Assert.AreEqual( 1.5f, vector.Y );
			Assert.AreEqual( 2.0f, vector.Z );
		}

		[Test]
		public void XIndexedGetter() {
			Vector3 vector = new Vector3();
			vector.X = 99.0f;

			Assert.AreEqual( 99.0f, vector[0] );
		}

		[Test]
		public void YIndexedGetter() {
			Vector3 vector = new Vector3();
			vector.Y = 99.0f;

			Assert.AreEqual( 99.0f, vector[1] );
		}

		[Test]
		public void ZIndexedGetter() {
			Vector3 vector = new Vector3();
			vector.Z = 99.0f;

			Assert.AreEqual( 99.0f, vector[2] );
		}

		[Test]
		public void XIndexedSetter() {
			Vector3 vector = new Vector3();
			vector[0] = 73.0f;

			Assert.AreEqual( 73.0f, vector.X );
		}

		[Test]
		public void YIndexedSetter() {
			Vector3 vector = new Vector3();
			vector[1] = 73.0f;

			Assert.AreEqual( 73.0f, vector.Y );
		}

		[Test]
		public void ZIndexedSetter() {
			Vector3 vector = new Vector3();
			vector[2] = 73.0f;

			Assert.AreEqual( 73.0f, vector.Z );
		}
	}
}