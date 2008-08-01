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

namespace SlimDX.Tests
{
    [TestFixture]
    public class Color3Tests
    {
        [Test]
        public void ConstructDefault()
        {
            Color3 color = new Color3();

            Assert.AreEqual(color.Red, 0.0f);
            Assert.AreEqual(color.Green, 0.0f);
            Assert.AreEqual(color.Blue, 0.0f);
        }

        [Test]
        public void ConstructFromRgb()
        {
            Color3 color = new Color3(1.0f, 0.5f, 0.25f);

            Assert.AreEqual(color.Red, 1.0f);
            Assert.AreEqual(color.Green, 0.5f);
            Assert.AreEqual(color.Blue, 0.25f);
        }
    }
}