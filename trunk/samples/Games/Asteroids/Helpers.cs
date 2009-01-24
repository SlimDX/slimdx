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
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;

namespace Asteroids
{
    static class Helpers
    {
        public static float Lerp(float start, float end, float amount)
        {
            return start + ((end - start) * amount);
        }

        public static List<T> MakeList<T>(T type)
        {
            return new List<T>();
        }

        public static T Parse<T>(string value)
        {
            TypeConverter converter = TypeDescriptor.GetConverter(typeof(T));
            return (T)converter.ConvertFromString(null, CultureInfo.InvariantCulture, value);
        }

        public static float RandomFloat(float minValue, float maxValue)
        {
            return (float)(Asteroids.Random.NextDouble() * (maxValue - minValue)) + minValue;
        }

        public static float ToRadians(float degrees)
        {
            return (degrees / 180) * (float)Math.PI;
        }

        public static T Clamp<T>(T value, T min, T max) where T : IComparable
        {
            if (value.CompareTo(max) >= 0)
                return max;
            if (value.CompareTo(min) <= 0)
                return min;
            return value;
        }
    }
}
