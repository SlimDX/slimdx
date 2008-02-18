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
#include <windows.h>
#include <d3dx9.h>

#include "Math.h"

using namespace System;
using namespace System::Globalization;

namespace SlimDX
{
	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector4"/> class.
	/// </summary>
	/// <param name="value">The value that will be assigned to all components.</param>
	Vector4::Vector4( float value )
	{
		X = value;
		Y = value;
		Z = value;
		W = value;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector4"/> class.
	/// </summary>
	/// <param name="value">A vector containing the values with which to initialize the X and Y components</param>
	/// <param name="z">Initial value for the Z component of the vector.</param>
	/// <param name="w">Initial value for the W component of the vector.</param>
	Vector4::Vector4( Vector2 value, float z, float w )
	{
		X = value.X;
		Y = value.Y;
		Z = z;
		W = w;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector4"/> class.
	/// </summary>
	/// <param name="value">A vector containing the values with which to initialize the X, Y, and Z components</param>
	/// <param name="w">Initial value for the W component of the vector.</param>
	Vector4::Vector4( Vector3 value, float w )
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = w;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector4"/> class.
	/// </summary>
	/// <param name="x">Initial value for the X component of the vector.</param>
	/// <param name="y">Initial value for the Y component of the vector.</param>
	/// <param name="z">Initial value for the Z component of the vector.</param>
	/// <param name="w">Initial value for the W component of the vector.</param>
	Vector4::Vector4( float x, float y, float z, float w )
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	/// <summary>
	/// Calculates the length of the vector.
	/// </summary>
	/// <returns>The length of the vector.</returns>
	float Vector4::Length()
	{
		return static_cast<float>( Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) + (W * W) ) );
	}

	/// <summary>
	/// Calculates the squared length of the vector.
	/// </summary>
	/// <returns>The squared length of the vector.</returns>
	float Vector4::LengthSquared()
	{
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	void Vector4::Normalize()
	{
		float length = Length();
		if( length == 0 )
			return;
		float num = 1 / length;
		X *= num;
		Y *= num;
		Z *= num;
		W *= num;
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <returns>The sum of the two vectors.</returns>
	Vector4 Vector4::Add( Vector4 left, Vector4 right )
	{
		return Vector4( left.X + right.X, left.Y + right.Y, left.Z + right.Z, left.W + right.W );
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <param name="result">When the method completes, contains the sum of the two vectors.</param>
	void Vector4::Add( Vector4% left, Vector4% right, [Out] Vector4% result )
	{
		result = Vector4( left.X + right.X, left.Y + right.Y, left.Z + right.Z, left.W + right.W );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <returns>The difference of the two vectors.</returns>
	Vector4 Vector4::Subtract( Vector4 left, Vector4 right )
	{
		return Vector4( left.X - right.X, left.Y - right.Y, left.Z - right.Z, left.W - right.W );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <param name="result">When the method completes, contains the difference of the two vectors.</param>
	void Vector4::Subtract( Vector4% left, Vector4% right, [Out] Vector4% result )
	{
		result = Vector4( left.X - right.X, left.Y - right.Y, left.Z - right.Z, left.W - right.W );
	}


	/// <summary>
	/// Modulates a vector by another.
	/// </summary>
	/// <param name="left">The first vector to modulate.</param>
	/// <param name="right">The second vector to modulate.</param>
	/// <returns>The modulated vector.</returns>
	Vector4 Vector4::Modulate( Vector4 left, Vector4 right )
	{
		return Vector4( left.X * right.X, left.Y * right.Y, left.Z * right.Z, left.W * right.W );
	}

	/// <summary>
	/// Modulates a vector by another.
	/// </summary>
	/// <param name="left">The first vector to modulate.</param>
	/// <param name="right">The second vector to modulate.</param>
	/// <param name="result">When the moethod completes, contains the modulated vector.</param>
	void Vector4::Modulate( Vector4% left, Vector4% right, [Out] Vector4% result )
	{
		result = Vector4( left.X * right.X, left.Y * right.Y, left.Z * right.Z, left.W * right.W );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="value">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector4 Vector4::Multiply( Vector4 value, float scale )
	{
		return Vector4( value.X * scale, value.Y * scale, value.Z * scale, value.W * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <param name="result">When the method completes, contains the scaled vector.</param>
	void Vector4::Multiply( Vector4% value, float scale, [Out] Vector4% result )
	{
		result = Vector4( value.X * scale, value.Y * scale, value.Z * scale, value.W * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="value">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector4 Vector4::Divide( Vector4 value, float scale )
	{
		return Vector4( value.X / scale, value.Y / scale, value.Z / scale, value.W / scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <param name="result">When the method completes, contains the scaled vector.</param>
	void Vector4::Divide( Vector4% value, float scale, [Out] Vector4% result )
	{
		result = Vector4( value.X / scale, value.Y / scale, value.Z / scale, value.W / scale );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <returns>A vector facing in the opposite direction.</returns>
	Vector4 Vector4::Negate( Vector4 value )
	{
		return Vector4( -value.X, -value.Y, -value.Z, -value.W );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <param name="result">When the method completes, contains a vector facing in the opposite direction.</param>
	void Vector4::Negate( Vector4% value, [Out] Vector4% result )
	{
		result = Vector4( -value.X, -value.Y, -value.Z, -value.W );
	}

	/// <summary>
	/// Returns a <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 4D triangle.
	/// </summary>
	/// <param name="value1">A <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of vertex 1 of the triangle.</param>
	/// <param name="value2">A <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of vertex 2 of the triangle.</param>
	/// <param name="value3">A <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of vertex 3 of the triangle.</param>
	/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
	/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
	/// <returns>A new <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of the specified point.</returns>
	Vector4 Vector4::Barycentric( Vector4 value1, Vector4 value2, Vector4 value3, float amount1, float amount2 )
	{
		Vector4 vector;
		vector.X = (value1.X + (amount1 * (value2.X - value1.X))) + (amount2 * (value3.X - value1.X));
		vector.Y = (value1.Y + (amount1 * (value2.Y - value1.Y))) + (amount2 * (value3.Y - value1.Y));
		vector.Z = (value1.Z + (amount1 * (value2.Z - value1.Z))) + (amount2 * (value3.Z - value1.Z));
		vector.W = (value1.W + (amount1 * (value2.W - value1.W))) + (amount2 * (value3.W - value1.W));
		return vector;
	}

	/// <summary>
	/// Returns a <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 4D triangle.
	/// </summary>
	/// <param name="value1">A <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of vertex 1 of the triangle.</param>
	/// <param name="value2">A <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of vertex 2 of the triangle.</param>
	/// <param name="value3">A <see cref="SlimDX::Vector4"/> containing the 4D Cartesian coordinates of vertex 3 of the triangle.</param>
	/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
	/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
	/// <param name="result">When the method completes, contains the 4D Cartesian coordinates of the specified point.</param>
	void Vector4::Barycentric( Vector4% value1, Vector4% value2, Vector4% value3, float amount1, float amount2, [Out] Vector4% result )
	{
		result = Vector4((value1.X + (amount1 * (value2.X - value1.X))) + (amount2 * (value3.X - value1.X)),
			(value1.Y + (amount1 * (value2.Y - value1.Y))) + (amount2 * (value3.Y - value1.Y)),
			(value1.Z + (amount1 * (value2.Z - value1.Z))) + (amount2 * (value3.Z - value1.Z)),
			(value1.W + (amount1 * (value2.W - value1.W))) + (amount2 * (value3.W - value1.W)) );
	}

	/// <summary>
	/// Performs a Catmull-Rom interpolation using the specified positions.
	/// </summary>
	/// <param name="value1">The first position in the interpolation.</param>
	/// <param name="value2">The second position in the interpolation.</param>
	/// <param name="value3">The third position in the interpolation.</param>
	/// <param name="value4">The fourth position in the interpolation.</param>
	/// <param name="amount">Weighting factor.</param>
	/// <returns>A vector that is the result of the Catmull-Rom interpolation.</returns>
	Vector4 Vector4::CatmullRom( Vector4 value1, Vector4 value2, Vector4 value3, Vector4 value4, float amount )
	{
		Vector4 vector;
		float squared = amount * amount;
		float cubed = amount * squared;

		vector.X = 0.5f * ((((2.0f * value2.X) + ((-value1.X + value3.X) * amount)) + 
			(((((2.0f * value1.X) - (5.0f * value2.X)) + (4.0f * value3.X)) - value4.X) * squared)) + 
			((((-value1.X + (3.0f * value2.X)) - (3.0f * value3.X)) + value4.X) * cubed));

		vector.Y = 0.5f * ((((2.0f * value2.Y) + ((-value1.Y + value3.Y) * amount)) + 
			(((((2.0f * value1.Y) - (5.0f * value2.Y)) + (4.0f * value3.Y)) - value4.Y) * squared)) + 
			((((-value1.Y + (3.0f * value2.Y)) - (3.0f * value3.Y)) + value4.Y) * cubed));

		vector.Z = 0.5f * ((((2.0f * value2.Z) + ((-value1.Z + value3.Z) * amount)) + 
			(((((2.0f * value1.Z) - (5.0f * value2.Z)) + (4.0f * value3.Z)) - value4.Z) * squared)) + 
			((((-value1.Z + (3.0f * value2.Z)) - (3.0f * value3.Z)) + value4.Z) * cubed));

		vector.W = 0.5f * ((((2.0f * value2.W) + ((-value1.W + value3.W) * amount)) + 
			(((((2.0f * value1.W) - (5.0f * value2.W)) + (4.0f * value3.W)) - value4.W) * squared)) + 
			((((-value1.W + (3.0f * value2.W)) - (3.0f * value3.W)) + value4.W) * cubed));

		return vector;
	}

	/// <summary>
	/// Performs a Catmull-Rom interpolation using the specified positions.
	/// </summary>
	/// <param name="value1">The first position in the interpolation.</param>
	/// <param name="value2">The second position in the interpolation.</param>
	/// <param name="value3">The third position in the interpolation.</param>
	/// <param name="value4">The fourth position in the interpolation.</param>
	/// <param name="amount">Weighting factor.</param>
	/// <param name="result">When the method completes, contains the result of the Catmull-Rom interpolation.</param>
	void Vector4::CatmullRom( Vector4% value1, Vector4% value2, Vector4% value3, Vector4% value4, float amount, [Out] Vector4% result )
	{
		float squared = amount * amount;
		float cubed = amount * squared;
		
		Vector4 r;

		r.X = 0.5f * ((((2.0f * value2.X) + ((-value1.X + value3.X) * amount)) + 
			(((((2.0f * value1.X) - (5.0f * value2.X)) + (4.0f * value3.X)) - value4.X) * squared)) + 
			((((-value1.X + (3.0f * value2.X)) - (3.0f * value3.X)) + value4.X) * cubed));

		r.Y = 0.5f * ((((2.0f * value2.Y) + ((-value1.Y + value3.Y) * amount)) + 
			(((((2.0f * value1.Y) - (5.0f * value2.Y)) + (4.0f * value3.Y)) - value4.Y) * squared)) + 
			((((-value1.Y + (3.0f * value2.Y)) - (3.0f * value3.Y)) + value4.Y) * cubed));

		r.Z = 0.5f * ((((2.0f * value2.Z) + ((-value1.Z + value3.Z) * amount)) + 
			(((((2.0f * value1.Z) - (5.0f * value2.Z)) + (4.0f * value3.Z)) - value4.Z) * squared)) + 
			((((-value1.Z + (3.0f * value2.Z)) - (3.0f * value3.Z)) + value4.Z) * cubed));

		r.W = 0.5f * ((((2.0f * value2.W) + ((-value1.W + value3.W) * amount)) + 
			(((((2.0f * value1.W) - (5.0f * value2.W)) + (4.0f * value3.W)) - value4.W) * squared)) + 
			((((-value1.W + (3.0f * value2.W)) - (3.0f * value3.W)) + value4.W) * cubed));

		result = r;
	}

	/// <summary>
	/// Restricts a value to be within a specified range.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <returns>The clamped value.</returns>
	Vector4 Vector4::Clamp( Vector4 value, Vector4 min, Vector4 max )
	{
		float x = value.X;
		x = (x > max.X) ? max.X : x;
		x = (x < min.X) ? min.X : x;

		float y = value.Y;
		y = (y > max.Y) ? max.Y : y;
		y = (y < min.Y) ? min.Y : y;

		float z = value.Z;
		z = (z > max.Z) ? max.Z : z;
		z = (z < min.Z) ? min.Z : z;

		float w = value.W;
		w = (w > max.W) ? max.W : w;
		w = (w < min.W) ? min.W : w;

		return Vector4( x, y, z, w );
	}

	/// <summary>
	/// Restricts a value to be within a specified range.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <param name="result">When the method completes, contains the clamped value.</param>
	void Vector4::Clamp( Vector4% value, Vector4% min, Vector4% max, [Out] Vector4% result )
	{
		float x = value.X;
		x = (x > max.X) ? max.X : x;
		x = (x < min.X) ? min.X : x;

		float y = value.Y;
		y = (y > max.Y) ? max.Y : y;
		y = (y < min.Y) ? min.Y : y;

		float z = value.Z;
		z = (z > max.Z) ? max.Z : z;
		z = (z < min.Z) ? min.Z : z;

		float w = value.W;
		w = (w > max.W) ? max.W : w;
		w = (w < min.W) ? min.W : w;

		result = Vector4( x, y, z, w );
	}

	/// <summary>
	/// Performs a Hermite spline interpolation.
	/// </summary>
	/// <param name="value1">First source position vector.</param>
	/// <param name="tangent1">First source tangent vector.</param>
	/// <param name="value2">Second source position vector.</param>
	/// <param name="tangent2">Second source tangent vector.</param>
	/// <param name="amount">Weighting factor.</param>
	/// <returns>The result of the Hermite spline interpolation.</returns>
	Vector4 Vector4::Hermite( Vector4 value1, Vector4 tangent1, Vector4 value2, Vector4 tangent2, float amount )
	{
		Vector4 vector;
		float squared = amount * amount;
		float cubed = amount * squared;
		float part1 = ((2.0f * cubed) - (3.0f * squared)) + 1.0f;
		float part2 = (-2.0f * cubed) + (3.0f * squared);
		float part3 = (cubed - (2.0f * squared)) + amount;
		float part4 = cubed - squared;

		vector.X = (((value1.X * part1) + (value2.X * part2)) + (tangent1.X * part3)) + (tangent2.X * part4);
		vector.Y = (((value1.Y * part1) + (value2.Y * part2)) + (tangent1.Y * part3)) + (tangent2.Y * part4);
		vector.Z = (((value1.Z * part1) + (value2.Z * part2)) + (tangent1.Z * part3)) + (tangent2.Z * part4);
		vector.W = (((value1.W * part1) + (value2.W * part2)) + (tangent1.W * part3)) + (tangent2.W * part4);

		return vector;
	}

	
	/// <summary>
	/// Performs a Hermite spline interpolation.
	/// </summary>
	/// <param name="value1">First source position vector.</param>
	/// <param name="tangent1">First source tangent vector.</param>
	/// <param name="value2">Second source position vector.</param>
	/// <param name="tangent2">Second source tangent vector.</param>
	/// <param name="amount">Weighting factor.</param>
	/// <param name="result">When the method completes, contains the result of the Hermite spline interpolation.</param>
	void Vector4::Hermite( Vector4% value1, Vector4% tangent1, Vector4% value2, Vector4% tangent2, float amount, [Out] Vector4% result )
	{
		float squared = amount * amount;
		float cubed = amount * squared;
		float part1 = ((2.0f * cubed) - (3.0f * squared)) + 1.0f;
		float part2 = (-2.0f * cubed) + (3.0f * squared);
		float part3 = (cubed - (2.0f * squared)) + amount;
		float part4 = cubed - squared;

		result.X = (((value1.X * part1) + (value2.X * part2)) + (tangent1.X * part3)) + (tangent2.X * part4);
		result.Y = (((value1.Y * part1) + (value2.Y * part2)) + (tangent1.Y * part3)) + (tangent2.Y * part4);
		result.Z = (((value1.Z * part1) + (value2.Z * part2)) + (tangent1.Z * part3)) + (tangent2.Z * part4);
		result.W = (((value1.W * part1) + (value2.W * part2)) + (tangent1.W * part3)) + (tangent2.W * part4);
	}

	/// <summary>
	/// Performs a linear interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <returns>The linear interpolation of the two vectors.</returns>
	/// <remarks>
	/// This method performs the linear interpolation based on the following formula.
	/// <code>start + (end - start) * amount</code>
	/// Passing <paramref name="amount"/> a value of 0 will cause <paramref name="start"/> to be returned; a value of 1 will cause <paramref name="end"/> to be returned. 
	/// </remarks>
	Vector4 Vector4::Lerp( Vector4 start, Vector4 end, float factor )
	{
		Vector4 vector;

		vector.X = start.X + ((end.X - start.X) * factor);
		vector.Y = start.Y + ((end.Y - start.Y) * factor);
		vector.Z = start.Z + ((end.Z - start.Z) * factor);
		vector.W = start.W + ((end.W - start.W) * factor);

		return vector;
	}

	/// <summary>
	/// Performs a linear interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <param name="result">When the method completes, contains the linear interpolation of the two vectors.</param>
	/// <remarks>
	/// This method performs the linear interpolation based on the following formula.
	/// <code>start + (end - start) * amount</code>
	/// Passing <paramref name="amount"/> a value of 0 will cause <paramref name="start"/> to be returned; a value of 1 will cause <paramref name="end"/> to be returned. 
	/// </remarks>
	void Vector4::Lerp( Vector4% start, Vector4% end, float factor, [Out] Vector4% result )
	{
		result.X = start.X + ((end.X - start.X) * factor);
		result.Y = start.Y + ((end.Y - start.Y) * factor);
		result.Z = start.Z + ((end.Z - start.Z) * factor);
		result.W = start.W + ((end.W - start.W) * factor);
	}

	/// <summary>
	/// Performs a cubic interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <returns>The cubic interpolation of the two vectors.</returns>
	Vector4 Vector4::SmoothStep( Vector4 start, Vector4 end, float amount )
	{
		Vector4 vector;

		amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
		amount = (amount * amount) * (3.0f - (.02f * amount));

		vector.X = start.X + ((end.X - start.X) * amount);
		vector.Y = start.Y + ((end.Y - start.Y) * amount);
		vector.Z = start.Z + ((end.Z - start.Z) * amount);
		vector.W = start.W + ((end.W - start.W) * amount);

		return vector;
	}

	/// <summary>
	/// Performs a cubic interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <param name="result">When the method completes, contains the cubic interpolation of the two vectors.</param>
	void Vector4::SmoothStep( Vector4% start, Vector4% end, float amount, [Out] Vector4% result )
	{
		amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
		amount = (amount * amount) * (3.0f - (.02f * amount));

		result.X = start.X + ((end.X - start.X) * amount);
		result.Y = start.Y + ((end.Y - start.Y) * amount);
		result.Z = start.Z + ((end.Z - start.Z) * amount);
		result.W = start.W + ((end.W - start.W) * amount);
	}

	/// <summary>
	/// Calculates the distance between two vectors.
	/// </summary>
	/// <param name="value1">The first vector.</param>
	/// <param name="value2">The second vector.</param>
	/// <returns>The distance between the two vectors.</returns>
	float Vector4::Distance( Vector4 value1, Vector4 value2 )
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		float z = value1.Z - value2.Z;
		float w = value1.W - value2.W;

		return static_cast<float>( Math::Sqrt( (x * x) + (y * y) + (z * z) + (w * w) ) );
	}

	/// <summary>
	/// Calculates the squared distance between two vectors.
	/// </summary>
	/// <param name="value1">The first vector.</param>
	/// <param name="value2">The second vector.</param>
	/// <returns>The squared distance between the two vectors.</returns>
	/// <remarks>Distance squared is the value before taking the square root. 
	/// Distance squared can often be used in place of distance if relative comparisons are being made. 
	/// For example, consider three points A, B, and C. To determine whether B or C is further from A, 
	/// compare the distance between A and B to the distance between A and C. Calculating the two distances 
	/// involves two square roots, which are computationally expensive. However, using distance squared 
	/// provides the same information and avoids calculating two square roots.
	/// </remarks>
	float Vector4::DistanceSquared( Vector4 value1, Vector4 value2 )
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		float z = value1.Z - value2.Z;
		float w = value1.W - value2.W;

		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	/// <summary>
	/// Calculates the dot product of two vectors.
	/// </summary>
	/// <param name="left">First source vector.</param>
	/// <param name="right">Second source vector.</param>
	/// <returns>The dot product of the two vectors.</returns>
	float Vector4::Dot( Vector4 left, Vector4 right )
	{
		return (left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W);
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	/// <param name="vector">The vector to normalize.</param>
	/// <returns>The normalized vector.</returns>
	Vector4 Vector4::Normalize( Vector4 vector )
	{
		vector.Normalize();
		return vector;
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	/// <param name="vector">The vector to normalize.</param>
	/// <param name="result">When the method completes, contains the normalized vector.</param>
	void Vector4::Normalize( Vector4% vector, [Out] Vector4% result )
	{
		result = Vector4(vector);
		result.Normalize();
	}

	/// <summary>
	/// Transforms a 4D vector by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	Vector4 Vector4::Transform( Vector4 vector, Matrix transform )
	{
		Vector4 result;

		result.X = (vector.X * transform.M11) + (vector.Y * transform.M21) + (vector.Z * transform.M31) + (vector.W * transform.M41);
		result.Y = (vector.X * transform.M12) + (vector.Y * transform.M22) + (vector.Z * transform.M32) + (vector.W * transform.M42);
		result.Z = (vector.X * transform.M13) + (vector.Y * transform.M23) + (vector.Z * transform.M33) + (vector.W * transform.M43);
		result.W = (vector.X * transform.M14) + (vector.Y * transform.M24) + (vector.Z * transform.M34) + (vector.W * transform.M44);

		return result;
	}

	/// <summary>
	/// Transforms a 4D vector by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
	void Vector4::Transform( Vector4% vector, Matrix% transform, [Out] Vector4% result )
	{
		Vector4 r;
		r.X = (vector.X * transform.M11) + (vector.Y * transform.M21) + (vector.Z * transform.M31) + (vector.W * transform.M41);
		r.Y = (vector.X * transform.M12) + (vector.Y * transform.M22) + (vector.Z * transform.M32) + (vector.W * transform.M42);
		r.Z = (vector.X * transform.M13) + (vector.Y * transform.M23) + (vector.Z * transform.M33) + (vector.W * transform.M43);
		r.W = (vector.X * transform.M14) + (vector.Y * transform.M24) + (vector.Z * transform.M34) + (vector.W * transform.M44);
	
		result = r;
	}

	/// <summary>
	/// Transforms an array of 4D vectors by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vectors">The source vectors.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>s.</returns>
	array<Vector4>^ Vector4::Transform( array<Vector4>^ vectors, Matrix% transform )
	{
		if( vectors == nullptr )
			throw gcnew ArgumentNullException( "vectors" );

		int count = vectors->Length;
		array<Vector4>^ results = gcnew array<Vector4>( count );

		for( int i = 0; i < count; i++ )
		{
			Vector4 r;
			r.X = (vectors[i].X * transform.M11) + (vectors[i].Y * transform.M21) + (vectors[i].Z * transform.M31) + (vectors[i].W * transform.M41);
			r.Y = (vectors[i].X * transform.M12) + (vectors[i].Y * transform.M22) + (vectors[i].Z * transform.M32) + (vectors[i].W * transform.M42);
			r.Z = (vectors[i].X * transform.M13) + (vectors[i].Y * transform.M23) + (vectors[i].Z * transform.M33) + (vectors[i].W * transform.M43);
			r.W = (vectors[i].X * transform.M14) + (vectors[i].Y * transform.M24) + (vectors[i].Z * transform.M34) + (vectors[i].W * transform.M44);
		
			results[i] = r;
		}

		return results;
	}

	/// <summary>
	/// Transforms a 4D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vector">The vector to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	Vector4 Vector4::Transform( Vector4 value, Quaternion rotation )
	{
		Vector4 vector;
		float x = rotation.X + rotation.X;
		float y = rotation.Y + rotation.Y;
		float z = rotation.Z + rotation.Z;
		float wx = rotation.W * x;
		float wy = rotation.W * y;
		float wz = rotation.W * z;
		float xx = rotation.X * x;
		float xy = rotation.X * y;
		float xz = rotation.X * z;
		float yy = rotation.Y * y;
		float yz = rotation.Y * z;
		float zz = rotation.Z * z;

		vector.X = ((value.X * ((1.0f - yy) - zz)) + (value.Y * (xy - wz))) + (value.Z * (xz + wy));
		vector.Y = ((value.X * (xy + wz)) + (value.Y * ((1.0f - xx) - zz))) + (value.Z * (yz - wx));
		vector.Z = ((value.X * (xz - wy)) + (value.Y * (yz + wx))) + (value.Z * ((1.0f - xx) - yy));
		vector.W = value.W;

		return vector;
	}

	/// <summary>
	/// Transforms a 4D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vector">The vector to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
	void Vector4::Transform( Vector4% value, Quaternion% rotation, [Out] Vector4% result )
	{
		float x = rotation.X + rotation.X;
		float y = rotation.Y + rotation.Y;
		float z = rotation.Z + rotation.Z;
		float wx = rotation.W * x;
		float wy = rotation.W * y;
		float wz = rotation.W * z;
		float xx = rotation.X * x;
		float xy = rotation.X * y;
		float xz = rotation.X * z;
		float yy = rotation.Y * y;
		float yz = rotation.Y * z;
		float zz = rotation.Z * z;

		Vector4 r;
		r.X = ((value.X * ((1.0f - yy) - zz)) + (value.Y * (xy - wz))) + (value.Z * (xz + wy));
		r.Y = ((value.X * (xy + wz)) + (value.Y * ((1.0f - xx) - zz))) + (value.Z * (yz - wx));
		r.Z = ((value.X * (xz - wy)) + (value.Y * (yz + wx))) + (value.Z * ((1.0f - xx) - yy));
		r.W = value.W;

		result = r;
	}

	/// <summary>
	/// Transforms an array of 4D vectors by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vectors">The vectors to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	array<Vector4>^ Vector4::Transform( array<Vector4>^ vectors, Quaternion% rotation )
	{
		if( vectors == nullptr )
			throw gcnew ArgumentNullException( "vectors" );

		int count = vectors->Length;
		array<Vector4>^ results = gcnew array<Vector4>( count );

		float x = rotation.X + rotation.X;
		float y = rotation.Y + rotation.Y;
		float z = rotation.Z + rotation.Z;
		float wx = rotation.W * x;
		float wy = rotation.W * y;
		float wz = rotation.W * z;
		float xx = rotation.X * x;
		float xy = rotation.X * y;
		float xz = rotation.X * z;
		float yy = rotation.Y * y;
		float yz = rotation.Y * z;
		float zz = rotation.Z * z;

		for( int i = 0; i < count; i++ )
		{
			Vector4 r;
			r.X = ((vectors[i].X * ((1.0f - yy) - zz)) + (vectors[i].Y * (xy - wz))) + (vectors[i].Z * (xz + wy));
			r.Y = ((vectors[i].X * (xy + wz)) + (vectors[i].Y * ((1.0f - xx) - zz))) + (vectors[i].Z * (yz - wx));
			r.Z = ((vectors[i].X * (xz - wy)) + (vectors[i].Y * (yz + wx))) + (vectors[i].Z * ((1.0f - xx) - yy));
			r.W = vectors[i].W;

			results[i] = r;
		}

		return results;
	}
	
	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <returns>A vector containing the smallest components of the source vectors.</returns>
	Vector4 Vector4::Minimize( Vector4 left, Vector4 right )
	{
		Vector4 vector;
		vector.X = (left.X < right.X) ? left.X : right.X;
		vector.Y = (left.Y < right.Y) ? left.Y : right.Y;
		vector.Z = (left.Z < right.Z) ? left.Z : right.Z;
		vector.W = (left.W < right.W) ? left.W : right.W;
		return vector;
	}

	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <param name="result">When the method completes, contains an new vector composed of the smallest components of the source vectors.</param>
	void Vector4::Minimize( Vector4% left, Vector4% right, [Out] Vector4% result )
	{
		result.X = (left.X < right.X) ? left.X : right.X;
		result.Y = (left.Y < right.Y) ? left.Y : right.Y;
		result.Z = (left.Z < right.Z) ? left.Z : right.Z;
		result.W = (left.W < right.W) ? left.W : right.W;
	}
	
	/// <summary>
	/// Returns a vector containing the largest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <returns>A vector containing the largest components of the source vectors.</returns>
	Vector4 Vector4::Maximize( Vector4 left, Vector4 right )
	{
		Vector4 vector;
		vector.X = (left.X > right.X) ? left.X : right.X;
		vector.Y = (left.Y > right.Y) ? left.Y : right.Y;
		vector.Z = (left.Z > right.Z) ? left.Z : right.Z;
		vector.W = (left.W > right.W) ? left.W : right.W;
		return vector;
	}

	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <param name="result">When the method completes, contains an new vector composed of the largest components of the source vectors.</param>
	void Vector4::Maximize( Vector4% left, Vector4% right, [Out] Vector4% result )
	{
		result.X = (left.X > right.X) ? left.X : right.X;
		result.Y = (left.Y > right.Y) ? left.Y : right.Y;
		result.Z = (left.Z > right.Z) ? left.Z : right.Z;
		result.W = (left.W > right.W) ? left.W : right.W;
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <returns>The sum of the two vectors.</returns>
	Vector4 Vector4::operator + ( Vector4 left, Vector4 right )
	{
		return Vector4( left.X + right.X, left.Y + right.Y, left.Z + right.Z, left.W + right.W );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <returns>The difference of the two vectors.</returns>
	Vector4 Vector4::operator - ( Vector4 left, Vector4 right )
	{
		return Vector4( left.X - right.X, left.Y - right.Y, left.Z - right.Z, left.W - right.W );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <returns>A vector facing in the opposite direction.</returns>
	Vector4 Vector4::operator - ( Vector4 value )
	{
		return Vector4( -value.X, -value.Y, -value.Z, -value.W );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector4 Vector4::operator * ( Vector4 value, float scale )
	{
		return Vector4( value.X * scale, value.Y * scale, value.Z * scale, value.W * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector4 Vector4::operator * ( float scale, Vector4 vec )
	{
		return vec * scale;
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector4 Vector4::operator / ( Vector4 value, float scale )
	{
		return Vector4( value.X / scale, value.Y / scale, value.Z / scale, value.W / scale );
	}

	/// <summary>
	/// Tests vectors for equality. 
	/// </summary>
	/// <param name="left">The first source vector.</param>
	/// <param name="right">The second source vector.</param>
	/// <returns><c>true</c> if the vectors are equal; <c>false</c> otherwise.</returns>
	bool Vector4::operator == ( Vector4 left, Vector4 right )
	{
		return Vector4::Equals( left, right );
	}

	/// <summary>
	/// Tests vectors for inequality. 
	/// </summary>
	/// <param name="left">The first source vector.</param>
	/// <param name="right">The second source vector.</param>
	/// <returns><c>true</c> if the vectors are not equal; <c>false</c> otherwise.</returns>
	bool Vector4::operator != ( Vector4 left, Vector4 right )
	{
		return !Vector4::Equals( left, right );
	}

	/// <summary>
	/// Retrieves a string representation of the current object. 
	/// </summary>
	/// <returns>A string that represents the object.</returns>
	String^ Vector4::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "X:{0} Y:{1} Z:{2} W:{3}", X.ToString(CultureInfo::CurrentCulture), 
			Y.ToString(CultureInfo::CurrentCulture), Z.ToString(CultureInfo::CurrentCulture),
			W.ToString(CultureInfo::CurrentCulture) );
	}

	/// <summary>
	/// Gets the hash code of the vector object. 
	/// </summary>
	/// <returns>Hash code of the vector object.</returns>
	int Vector4::GetHashCode()
	{
		return X.GetHashCode() + Y.GetHashCode() + Z.GetHashCode() + W.GetHashCode();
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to a specified object. 
	/// </summary>
	/// <param name="obj">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Vector4::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<Vector4>( value ) );
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to the specified object. 
	/// </summary>
	/// <param name="other">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Vector4::Equals( Vector4 value )
	{
		return ( X == value.X && Y == value.Y && Z == value.Z && W == value.W );
	}

	/// <summary>
	/// Determines whether the specified Object instances are considered equal. 
	/// </summary>
	/// <param name="value1"></param>
	/// <param name="value2"></param>
	/// <returns><c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
	/// if both are <c>null</c> references or if <c>objA.Equals(objB)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
	bool Vector4::Equals( Vector4% value1, Vector4% value2 )
	{
		return ( value1.X == value2.X && value1.Y == value2.Y && value1.Z == value2.Z && value1.W == value2.W );
	}
}