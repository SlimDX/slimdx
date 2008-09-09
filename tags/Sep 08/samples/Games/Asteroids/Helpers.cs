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
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;

namespace Asteroids
{
    /// <summary>
    /// Contains various helper methods.
    /// </summary>
    static class Helpers
    {
        /// <summary>
        /// Interpolates between the two provided values.
        /// </summary>
        /// <param name="start">The start value.</param>
        /// <param name="end">The end value.</param>
        /// <param name="amount">The amount.</param>
        /// <returns>The interpolated value.</returns>
        public static float Lerp(float start, float end, float amount)
        {
            // interpolate the values
            return start + ((end - start) * amount);
        }

        /// <summary>
        /// Makes a generic list based upong the specified type.
        /// </summary>
        /// <typeparam name="T">The type of the data contained in the list.</typeparam>
        /// <param name="type">The data type.</param>
        /// <returns>The newly created list.</returns>
        public static List<T> MakeList<T>(T type)
        {
            // create the list
            return new List<T>();
        }

        /// <summary>
        /// Parses an object using its registered type converter.
        /// </summary>
        /// <typeparam name="T">The type of the object.</typeparam>
        /// <param name="value">The object value.</param>
        /// <returns>The new object.</returns>
        public static T Parse<T>(string value)
        {
            // look up the type converter to convert the value
            TypeConverter converter = TypeDescriptor.GetConverter(typeof(T));
            return (T)converter.ConvertFromString(null, CultureInfo.InvariantCulture, value);
        }

        /// <summary>
        /// Calculates a random floating point value.
        /// </summary>
        /// <param name="minValue">The minimum value.</param>
        /// <param name="maxValue">The maximum value.</param>
        /// <returns>The random floating point value.</returns>
        public static float RandomFloat(float minValue, float maxValue)
        {
            // calculate the value
            return (float)(Asteroids.Random.NextDouble() * (maxValue - minValue)) + minValue;
        }

        /// <summary>
        /// Converts degrees to radians.
        /// </summary>
        /// <param name="degrees">The degrees.</param>
        /// <returns>The equivalent value in radians.</returns>
        public static float ToRadians(float degrees)
        {
            // return the converted value
            return (degrees / 180) * (float)Math.PI;
        }

        /// <summary>
        /// Restricts a value to be within a specified range.
        /// </summary>
        /// <typeparam name="T">The type of the value.</typeparam>
        /// <param name="value">The value to clamp.</param>
        /// <param name="min">The minimum value.</param>
        /// <param name="max">The maximum value.</param>
        /// <returns>The clamped value.</returns>
        public static T Clamp<T>(T value, T min, T max) where T : IComparable
        {
            // check if the value is over the bounds
            if (value.CompareTo(max) >= 0)
                return max;
            if (value.CompareTo(min) <= 0)
                return min;
            return value;
        }
    }
}
