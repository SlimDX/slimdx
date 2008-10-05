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
	public class DataRectangleTests {
		// =========================================================================
		// Tests
		
		[Test]
		public void ConstructFromValues() {
			DataRectangle rectangle = new DataRectangle( 1, m_stream );

			Assert.AreSame( m_stream, rectangle.Data );
			Assert.AreEqual( 1, rectangle.Pitch );
		}

		[Test]
		[ExpectedException(typeof(ArgumentNullException))]
		public void ConstructFromValuesWithNullData() {
			DataRectangle rectangle = new DataRectangle( 1, null );
		}

		[Test]
		[ExpectedException( typeof( ArgumentOutOfRangeException ) )]
		public void ConstructFromValuesWithNegativePitch() {
			DataRectangle rectangle = new DataRectangle( -1, m_stream );
		}

		[Test]
		public void SetPitch() {
			DataRectangle rectangle = new DataRectangle( 1, m_stream );
		
			rectangle.Pitch = 100;
			Assert.AreEqual( 100, rectangle.Pitch );
		}

		[Test]
		[ExpectedException( typeof( ArgumentOutOfRangeException ) )]
		public void SetPitchToNegative() {
			DataRectangle rectangle = new DataRectangle( 1, m_stream );

			rectangle.Pitch = -100;
		}

		// =========================================================================
		// Implementation Detail
		
		DataStream m_stream;
		
		[TestFixtureSetUp]
		public void SetUp() {
			m_stream = new DataStream( 8, true, true );
		}

		[TestFixtureTearDown]
		public void TearDown() {
			m_stream.Dispose();
		}
	}
}