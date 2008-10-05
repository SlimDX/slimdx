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
using System;
using NUnit.Framework;
using SlimDX;

namespace SlimDXTests {
	[TestFixture]
	public class DataBoxTests {
		// =========================================================================
		// Tests

		[Test]
		public void ConstructFromValues() {
			DataBox box = new DataBox( 1, 2, m_stream );

			Assert.AreSame( m_stream, box.Data );
			Assert.AreEqual( 1, box.RowPitch );
			Assert.AreEqual( 2, box.SlicePitch );
		}

		[Test]
		[ExpectedException( typeof( ArgumentNullException ) )]
		public void ConstructFromValuesWithNullData() {
			DataBox box = new DataBox( 1, 2, null );
		}

		[Test]
		[ExpectedException( typeof( ArgumentOutOfRangeException ) )]
		public void ConstructFromValuesWithNegativeRowPitch() {
			DataBox box = new DataBox( -1, 2, m_stream );
		}

		[Test]
		[ExpectedException( typeof( ArgumentOutOfRangeException ) )]
		public void ConstructFromValuesWithNegativeSlicePitch() {
			DataBox box = new DataBox( 1, -2, m_stream );
		}

		[Test]
		public void SetRowPitch() {
			DataBox box = new DataBox( 1, 2, m_stream );
		
			box.RowPitch = 100;
			Assert.AreEqual( 100, box.RowPitch );
		}

		[Test]
		[ExpectedException( typeof( ArgumentOutOfRangeException ) )]
		public void SetRowPitchToNegative() {
			DataBox box = new DataBox( 1, 2, m_stream );

			box.RowPitch = -100;
		}

		[Test]
		public void SetSlicePitch() {
			DataBox box = new DataBox( 1, 2, m_stream );

			box.SlicePitch = 200;
			Assert.AreEqual( 200, box.SlicePitch );
		}

		[Test]
		[ExpectedException( typeof( ArgumentOutOfRangeException ) )]
		public void SetSlicePitchToNegative() {
			DataBox box = new DataBox( 1, 2, m_stream );

			box.SlicePitch = -200;
		}

		// =========================================================================
		// Implementation Detail

		DataStream m_stream;

		[TestFixtureSetUp]
		public void SetUp() {
			m_stream = new DataStream( 100, true, true );
		}

		[TestFixtureTearDown]
		public void TearDown() {
			m_stream.Dispose();
		}
	}
}