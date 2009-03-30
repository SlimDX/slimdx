/*
* Copyright (c) 2007-2009 SlimDX Group
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
	public class Vector4Tests {
		// =========================================================================
		// Tests

		[Test]
		public void ConstructDefault() {
			Vector4 vector = new Vector4();

			Assert.AreEqual( 0.0f, vector.X );
			Assert.AreEqual( 0.0f, vector.Y );
			Assert.AreEqual( 0.0f, vector.Z );
			Assert.AreEqual( 0.0f, vector.W );
		}

		[Test]
		public void ConstructFromScalar() {
			Vector4 vector = new Vector4( 99.0f );

			Assert.AreEqual( 99.0f, vector.X );
			Assert.AreEqual( 99.0f, vector.Y );
			Assert.AreEqual( 99.0f, vector.Z );
			Assert.AreEqual( 99.0f, vector.W );
		}

		[Test]
		public void ConstructFromXYZ() {
			Vector4 vector = new Vector4( 0.5f, 1.5f, 2.0f, 4.0f );

			Assert.AreEqual( 0.5f, vector.X );
			Assert.AreEqual( 1.5f, vector.Y );
			Assert.AreEqual( 2.0f, vector.Z );
			Assert.AreEqual( 4.0f, vector.W );
		}

		[Test]
		public void XIndexedGetter() {
			Vector4 vector = new Vector4();
			vector.X = 99.0f;

			Assert.AreEqual( 99.0f, vector[0] );
		}

		[Test]
		public void YIndexedGetter() {
			Vector4 vector = new Vector4();
			vector.Y = 99.0f;

			Assert.AreEqual( 99.0f, vector[1] );
		}

		[Test]
		public void ZIndexedGetter() {
			Vector4 vector = new Vector4();
			vector.Z = 99.0f;

			Assert.AreEqual( 99.0f, vector[2] );
		}

		[Test]
		public void WIndexedGetter() {
			Vector4 vector = new Vector4();
			vector.W = 99.0f;

			Assert.AreEqual( 99.0f, vector[3] );
		}

		[Test]
		public void XIndexedSetter() {
			Vector4 vector = new Vector4();
			vector[0] = 73.0f;

			Assert.AreEqual( 73.0f, vector.X );
		}

		[Test]
		public void YIndexedSetter() {
			Vector4 vector = new Vector4();
			vector[1] = 73.0f;

			Assert.AreEqual( 73.0f, vector.Y );
		}

		[Test]
		public void ZIndexedSetter() {
			Vector4 vector = new Vector4();
			vector[2] = 73.0f;

			Assert.AreEqual( 73.0f, vector.Z );
		}

		[Test]
		public void WIndexedSetter() {
			Vector4 vector = new Vector4();
			vector[3] = 73.0f;

			Assert.AreEqual( 73.0f, vector.W );
		}
	}
}