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
    public class MatrixTests
    {
        // =========================================================================
        // Tests

        [Test]
        public void ConstructDefault()
        {
            Matrix matrix = new Matrix();

            Assert.AreEqual(0.0f, matrix.M11);
            Assert.AreEqual(0.0f, matrix.M12);
            Assert.AreEqual(0.0f, matrix.M13);
            Assert.AreEqual(0.0f, matrix.M14);
            Assert.AreEqual(0.0f, matrix.M21);
            Assert.AreEqual(0.0f, matrix.M22);
            Assert.AreEqual(0.0f, matrix.M23);
            Assert.AreEqual(0.0f, matrix.M24);
            Assert.AreEqual(0.0f, matrix.M31);
            Assert.AreEqual(0.0f, matrix.M32);
            Assert.AreEqual(0.0f, matrix.M33);
            Assert.AreEqual(0.0f, matrix.M34);
            Assert.AreEqual(0.0f, matrix.M41);
            Assert.AreEqual(0.0f, matrix.M42);
            Assert.AreEqual(0.0f, matrix.M43);
            Assert.AreEqual(0.0f, matrix.M44);
        }

        [Test]
        public void M11Property()
        {
            Matrix matrix = new Matrix();
            matrix.M11 = 1.0f;

            Assert.AreEqual(1.0f, matrix.M11);
        }

        [Test]
        public void M12Property()
        {
            Matrix matrix = new Matrix();
            matrix.M12 = 2.0f;

            Assert.AreEqual(2.0f, matrix.M12);
        }

        [Test]
        public void M13Property()
        {
            Matrix matrix = new Matrix();
            matrix.M13 = 3.0f;

            Assert.AreEqual(3.0f, matrix.M13);
        }

        [Test]
        public void M14Property()
        {
            Matrix matrix = new Matrix();
            matrix.M14 = 4.0f;

            Assert.AreEqual(4.0f, matrix.M14);
        }

        [Test]
        public void M21Property()
        {
            Matrix matrix = new Matrix();
            matrix.M21 = 1.0f;

            Assert.AreEqual(1.0f, matrix.M21);
        }

        [Test]
        public void M22Property()
        {
            Matrix matrix = new Matrix();
            matrix.M22 = 2.0f;

            Assert.AreEqual(2.0f, matrix.M22);
        }

        [Test]
        public void M23Property()
        {
            Matrix matrix = new Matrix();
            matrix.M23 = 3.0f;

            Assert.AreEqual(3.0f, matrix.M23);
        }

        [Test]
        public void M24Property()
        {
            Matrix matrix = new Matrix();
            matrix.M24 = 4.0f;

            Assert.AreEqual(4.0f, matrix.M24);
        }

        [Test]
        public void M31Property()
        {
            Matrix matrix = new Matrix();
            matrix.M31 = 1.0f;

            Assert.AreEqual(1.0f, matrix.M31);
        }

        [Test]
        public void M32Property()
        {
            Matrix matrix = new Matrix();
            matrix.M32 = 2.0f;

            Assert.AreEqual(2.0f, matrix.M32);
        }

        [Test]
        public void M33Property()
        {
            Matrix matrix = new Matrix();
            matrix.M33 = 3.0f;

            Assert.AreEqual(3.0f, matrix.M33);
        }

        [Test]
        public void M34Property()
        {
            Matrix matrix = new Matrix();
            matrix.M34 = 4.0f;

            Assert.AreEqual(4.0f, matrix.M34);
        }

        [Test]
        public void M41Property()
        {
            Matrix matrix = new Matrix();
            matrix.M41 = 1.0f;

            Assert.AreEqual(1.0f, matrix.M41);
        }

        [Test]
        public void M42Property()
        {
            Matrix matrix = new Matrix();
            matrix.M42 = 2.0f;

            Assert.AreEqual(2.0f, matrix.M42);
        }

        [Test]
        public void M43Property()
        {
            Matrix matrix = new Matrix();
            matrix.M43 = 3.0f;

            Assert.AreEqual(3.0f, matrix.M43);
        }

        [Test]
        public void M44Property()
        {
            Matrix matrix = new Matrix();
            matrix.M44 = 4.0f;

            Assert.AreEqual(4.0f, matrix.M44);
        }

        [Test]
        public void M11IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M11 = 128.0f;

            Assert.AreEqual(128.0f, matrix[0, 0]);
        }

        [Test]
        public void M12IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M12 = 128.0f;

            Assert.AreEqual(128.0f, matrix[0, 1]);
        }

        [Test]
        public void M13IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M13 = 128.0f;

            Assert.AreEqual(128.0f, matrix[0, 2]);
        }

        [Test]
        public void M14IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M14 = 128.0f;

            Assert.AreEqual(128.0f, matrix[0, 3]);
        }

        [Test]
        public void M21IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M21 = 228.0f;

            Assert.AreEqual(228.0f, matrix[1, 0]);
        }

        [Test]
        public void M22IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M22 = 228.0f;

            Assert.AreEqual(228.0f, matrix[1, 1]);
        }

        [Test]
        public void M23IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M23 = 228.0f;

            Assert.AreEqual(228.0f, matrix[1, 2]);
        }

        [Test]
        public void M24IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M24 = 228.0f;

            Assert.AreEqual(228.0f, matrix[1, 3]);
        }

        [Test]
        public void M31IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M31 = 328.0f;

            Assert.AreEqual(328.0f, matrix[2, 0]);
        }

        [Test]
        public void M32IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M32 = 328.0f;

            Assert.AreEqual(328.0f, matrix[2, 1]);
        }

        [Test]
        public void M33IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M33 = 328.0f;

            Assert.AreEqual(328.0f, matrix[2, 2]);
        }

        [Test]
        public void M34IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M34 = 328.0f;

            Assert.AreEqual(328.0f, matrix[2, 3]);
        }

        [Test]
        public void M41IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M41 = 448.0f;

            Assert.AreEqual(448.0f, matrix[3, 0]);
        }

        [Test]
        public void M42IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M42 = 448.0f;

            Assert.AreEqual(448.0f, matrix[3, 1]);
        }

        [Test]
        public void M43IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M43 = 448.0f;

            Assert.AreEqual(448.0f, matrix[3, 2]);
        }

        [Test]
        public void M44IndexedGetter()
        {
            Matrix matrix = new Matrix();
            matrix.M44 = 448.0f;

            Assert.AreEqual(448.0f, matrix[3, 3]);
        }

        [Test]
        public void M11IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[0, 0] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M11);
        }

        [Test]
        public void M12IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[0, 1] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M12);
        }

        [Test]
        public void M13IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[0, 2] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M13);
        }

        [Test]
        public void M14IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[0, 3] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M14);
        }

        [Test]
        public void M21IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[1, 0] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M21);
        }

        [Test]
        public void M22IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[1, 1] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M22);
        }

        [Test]
        public void M23IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[1, 2] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M23);
        }

        [Test]
        public void M24IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[1, 3] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M24);
        }

        [Test]
        public void M31IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[2, 0] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M31);
        }

        [Test]
        public void M32IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[2, 1] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M32);
        }

        [Test]
        public void M33IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[2, 2] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M33);
        }

        [Test]
        public void M34IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[2, 3] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M34);
        }

        [Test]
        public void M41IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[3, 0] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M41);
        }

        [Test]
        public void M42IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[3, 1] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M42);
        }

        [Test]
        public void M43IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[3, 2] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M43);
        }

        [Test]
        public void M44IndexedSetter()
        {
            Matrix matrix = new Matrix();
            matrix[3, 3] = 99.0f;

            Assert.AreEqual(99.0f, matrix.M44);
        }
    }
}