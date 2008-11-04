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

namespace SlimDXTests
{
    [TestFixture]
    public class Vector2Tests
    {
        // =========================================================================
        // Tests

        [Test]
        public void ConstructDefault()
        {
            Vector2 vector = new Vector2();

            Assert.AreEqual(0.0f, vector.X);
            Assert.AreEqual(0.0f, vector.Y);
        }

        [Test]
        public void ConstructFromScalar()
        {
            Vector2 vector = new Vector2(0.75f, 0.75f);

            Assert.AreEqual(0.75f, vector.X);
            Assert.AreEqual(0.75f, vector.Y);
        }

        [Test]
        public void ConstructFromXY()
        {
            Vector2 vector = new Vector2(0.5f, 1.5f);

            Assert.AreEqual(0.5f, vector.X);
            Assert.AreEqual(1.5f, vector.Y);
        }
				
				[Test]
				public void XIndexedGetter()
				{
            Vector2 vector = new Vector2();
						vector.X = 99.0f;

						Assert.AreEqual( 99.0f, vector[0] );
				}
				
				[Test]
				public void YIndexedGetter()
				{
            Vector2 vector = new Vector2();
						vector.Y = 99.0f;

						Assert.AreEqual( 99.0f, vector[1] );
				}
				
				[Test]
				public void XIndexedSetter()
				{
            Vector2 vector = new Vector2();
						vector[0] = 73.0f;

						Assert.AreEqual( 73.0f, vector.X );
				}
				
				[Test]
				public void YIndexedSetter()
				{
            Vector2 vector = new Vector2();
						vector[1] = 73.0f;

						Assert.AreEqual( 73.0f, vector.Y );
				}
				
        [Test]
        public void Length()
        {
            Vector2 vector = new Vector2(1.25f, 2.75f);

            Assert.AreEqual(3.02076149f, vector.Length());
        }

        [Test]
        public void LengthSquared()
        {
            Vector2 vector = new Vector2(1.25f, 2.75f);

            Assert.AreEqual(9.125f, vector.LengthSquared());
        }

        [Test]
        public void Normalize()
        {
            Vector2 vector = new Vector2(3.5f, 1.75f);
            vector.Normalize();

            Assert.AreEqual(0.89442719f, vector.X);
            Assert.AreEqual(0.44721359f, vector.Y);
        }

        [Test]
        public void NormalizeZeroVector()
        {
            Vector2 vector = new Vector2(0.0f, 0.0f);
            vector.Normalize();

            Assert.AreEqual(0.0f, vector.X);
            Assert.AreEqual(0.0f, vector.Y);
        }

        [Test]
        public void StaticNormalize()
        {
            Vector2 vector = new Vector2(3.5f, 1.75f);
            Vector2 result = Vector2.Normalize(vector);

            Assert.AreEqual(0.89442719f, result.X);
            Assert.AreEqual(0.44721359f, result.Y);
        }

        [Test]
        public void StaticNormalizeByRef()
        {
            Vector2 vector = new Vector2(3.5f, 1.75f);
            Vector2 result;
            Vector2.Normalize(ref vector, out result);

            Assert.AreEqual(0.89442719f, result.X);
            Assert.AreEqual(0.44721359f, result.Y);
        }

        [Test]
        public void ZeroStaticProperty()
        {
            Assert.AreEqual(0.0f, Vector2.Zero.X);
            Assert.AreEqual(0.0f, Vector2.Zero.Y);
        }

        [Test]
        public void UnitXStaticProperty()
        {
            Assert.AreEqual(1.0f, Vector2.UnitX.X);
            Assert.AreEqual(0.0f, Vector2.UnitX.Y);
        }

        [Test]
        public void UnitYStaticProperty()
        {
            Assert.AreEqual(0.0f, Vector2.UnitY.X);
            Assert.AreEqual(1.0f, Vector2.UnitY.Y);
        }

        [Test]
        public void SizeInBytesStaticProperty()
        {
            // We test this because it must match with what D3D expects.
            Assert.AreEqual(8, Vector2.SizeInBytes);
        }
    }
}