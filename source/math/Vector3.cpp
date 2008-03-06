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

#include <d3dx9.h>

#include "../Viewport.h"

#include "Quaternion.h"
#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"

using namespace System;
using namespace System::Globalization;

namespace SlimDX
{
	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector3"/> class.
	/// </summary>
	/// <param name="value">The value that will be assigned to all components.</param>
	Vector3::Vector3( float value )
	{
		X = value;
		Y = value;
		Z = value;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector3"/> class.
	/// </summary>
	/// <param name="value">A vector containing the values with which to initialize the X and Y components</param>
	/// <param name="z">Initial value for the Z component of the vector.</param>
	Vector3::Vector3( Vector2 value, float z )
	{
		X = value.X;
		Y = value.Y;
		Z = z;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector3"/> class.
	/// </summary>
	/// <param name="x">Initial value for the X component of the vector.</param>
	/// <param name="y">Initial value for the Y component of the vector.</param>
	/// <param name="z">Initial value for the Z component of the vector.</param>
	Vector3::Vector3( float x, float y, float z )
	{
		X = x;
		Y = y;
		Z = z;
	}

	/// <summary>
	/// Calculates the length of the vector.
	/// </summary>
	/// <returns>The length of the vector.</returns>
	float Vector3::Length()
	{
		return static_cast<float>( Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) ) );
	}

	/// <summary>
	/// Calculates the squared length of the vector.
	/// </summary>
	/// <returns>The squared length of the vector.</returns>
	float Vector3::LengthSquared()
	{
		return (X * X) + (Y * Y) + (Z * Z);
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	void Vector3::Normalize()
	{
		float length = Length();
		if( length == 0 )
			return;
		float num = 1 / length;
		X *= num;
		Y *= num;
		Z *= num;
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <returns>The sum of the two vectors.</returns>
	Vector3 Vector3::Add( Vector3 left, Vector3 right )
	{
		return Vector3( left.X + right.X, left.Y + right.Y, left.Z + right.Z );
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <param name="result">When the method completes, contains the sum of the two vectors.</param>
	void Vector3::Add( Vector3% left, Vector3% right, [Out] Vector3% result )
	{
		result = Vector3( left.X + right.X, left.Y + right.Y, left.Z + right.Z );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <returns>The difference of the two vectors.</returns>
	Vector3 Vector3::Subtract( Vector3 left, Vector3 right )
	{
		return Vector3( left.X - right.X, left.Y - right.Y, left.Z - right.Z );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <param name="result">When the method completes, contains the difference of the two vectors.</param>
	void Vector3::Subtract( Vector3% left, Vector3% right, [Out] Vector3% result )
	{
		result = Vector3( left.X - right.X, left.Y - right.Y, left.Z - right.Z );
	}


	/// <summary>
	/// Modulates a vector by another.
	/// </summary>
	/// <param name="left">The first vector to modulate.</param>
	/// <param name="right">The second vector to modulate.</param>
	/// <returns>The modulated vector.</returns>
	Vector3 Vector3::Modulate( Vector3 left, Vector3 right )
	{
		return Vector3( left.X * right.X, left.Y * right.Y, left.Z * right.Z );
	}

	/// <summary>
	/// Modulates a vector by another.
	/// </summary>
	/// <param name="left">The first vector to modulate.</param>
	/// <param name="right">The second vector to modulate.</param>
	/// <param name="result">When the moethod completes, contains the modulated vector.</param>
	void Vector3::Modulate( Vector3% left, Vector3% right, [Out] Vector3% result )
	{
		result = Vector3( left.X * right.X, left.Y * right.Y, left.Z * right.Z );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="value">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector3 Vector3::Multiply( Vector3 value, float scale )
	{
		return Vector3( value.X * scale, value.Y * scale, value.Z * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <param name="result">When the method completes, contains the scaled vector.</param>
	void Vector3::Multiply( Vector3% value, float scale, [Out] Vector3% result )
	{
		result = Vector3( value.X * scale, value.Y * scale, value.Z * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="value">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector3 Vector3::Divide( Vector3 value, float scale )
	{
		return Vector3( value.X / scale, value.Y / scale, value.Z / scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <param name="result">When the method completes, contains the scaled vector.</param>
	void Vector3::Divide( Vector3% value, float scale, [Out] Vector3% result )
	{
		result = Vector3( value.X / scale, value.Y / scale, value.Z / scale );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <returns>A vector facing in the opposite direction.</returns>
	Vector3 Vector3::Negate( Vector3 value )
	{
		return Vector3( -value.X, -value.Y, -value.Z );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <param name="result">When the method completes, contains a vector facing in the opposite direction.</param>
	void Vector3::Negate( Vector3% value, [Out] Vector3% result )
	{
		result = Vector3( -value.X, -value.Y, -value.Z );
	}

	/// <summary>
	/// Returns a <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 3D triangle.
	/// </summary>
	/// <param name="value1">A <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of vertex 1 of the triangle.</param>
	/// <param name="value2">A <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of vertex 2 of the triangle.</param>
	/// <param name="value3">A <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of vertex 3 of the triangle.</param>
	/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
	/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
	/// <returns>A new <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of the specified point.</returns>
	Vector3 Vector3::Barycentric( Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2 )
	{
		Vector3 vector;
		vector.X = (value1.X + (amount1 * (value2.X - value1.X))) + (amount2 * (value3.X - value1.X));
		vector.Y = (value1.Y + (amount1 * (value2.Y - value1.Y))) + (amount2 * (value3.Y - value1.Y));
		vector.Z = (value1.Z + (amount1 * (value2.Z - value1.Z))) + (amount2 * (value3.Z - value1.Z));
		return vector;
	}

	/// <summary>
	/// Returns a <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 3D triangle.
	/// </summary>
	/// <param name="value1">A <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of vertex 1 of the triangle.</param>
	/// <param name="value2">A <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of vertex 2 of the triangle.</param>
	/// <param name="value3">A <see cref="SlimDX::Vector3"/> containing the 3D Cartesian coordinates of vertex 3 of the triangle.</param>
	/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
	/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
	/// <param name="result">When the method completes, contains the 3D Cartesian coordinates of the specified point.</param>
	void Vector3::Barycentric( Vector3% value1, Vector3% value2, Vector3% value3, float amount1, float amount2, [Out] Vector3% result )
	{
		result = Vector3((value1.X + (amount1 * (value2.X - value1.X))) + (amount2 * (value3.X - value1.X)),
			(value1.Y + (amount1 * (value2.Y - value1.Y))) + (amount2 * (value3.Y - value1.Y)),
			(value1.Z + (amount1 * (value2.Z - value1.Z))) + (amount2 * (value3.Z - value1.Z)) );
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
	Vector3 Vector3::CatmullRom( Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount )
	{
		Vector3 vector;
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
	void Vector3::CatmullRom( Vector3% value1, Vector3% value2, Vector3% value3, Vector3% value4, float amount, [Out] Vector3% result )
	{
		float squared = amount * amount;
		float cubed = amount * squared;
		
		Vector3 r;

		r.X = 0.5f * ((((2.0f * value2.X) + ((-value1.X + value3.X) * amount)) + 
			(((((2.0f * value1.X) - (5.0f * value2.X)) + (4.0f * value3.X)) - value4.X) * squared)) + 
			((((-value1.X + (3.0f * value2.X)) - (3.0f * value3.X)) + value4.X) * cubed));

		r.Y = 0.5f * ((((2.0f * value2.Y) + ((-value1.Y + value3.Y) * amount)) + 
			(((((2.0f * value1.Y) - (5.0f * value2.Y)) + (4.0f * value3.Y)) - value4.Y) * squared)) + 
			((((-value1.Y + (3.0f * value2.Y)) - (3.0f * value3.Y)) + value4.Y) * cubed));

		r.Z = 0.5f * ((((2.0f * value2.Z) + ((-value1.Z + value3.Z) * amount)) + 
			(((((2.0f * value1.Z) - (5.0f * value2.Z)) + (4.0f * value3.Z)) - value4.Z) * squared)) + 
			((((-value1.Z + (3.0f * value2.Z)) - (3.0f * value3.Z)) + value4.Z) * cubed));

		result = r;
	}

	/// <summary>
	/// Restricts a value to be within a specified range.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <returns>The clamped value.</returns>
	Vector3 Vector3::Clamp( Vector3 value, Vector3 min, Vector3 max )
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

		return Vector3( x, y, z );
	}

	/// <summary>
	/// Restricts a value to be within a specified range.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <param name="result">When the method completes, contains the clamped value.</param>
	void Vector3::Clamp( Vector3% value, Vector3% min, Vector3% max, [Out] Vector3% result )
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

		result = Vector3( x, y, z );
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
	Vector3 Vector3::Hermite( Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount )
	{
		Vector3 vector;
		float squared = amount * amount;
		float cubed = amount * squared;
		float part1 = ((2.0f * cubed) - (3.0f * squared)) + 1.0f;
		float part2 = (-2.0f * cubed) + (3.0f * squared);
		float part3 = (cubed - (2.0f * squared)) + amount;
		float part4 = cubed - squared;

		vector.X = (((value1.X * part1) + (value2.X * part2)) + (tangent1.X * part3)) + (tangent2.X * part4);
		vector.Y = (((value1.Y * part1) + (value2.Y * part2)) + (tangent1.Y * part3)) + (tangent2.Y * part4);
		vector.Z = (((value1.Z * part1) + (value2.Z * part2)) + (tangent1.Z * part3)) + (tangent2.Z * part4);

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
	void Vector3::Hermite( Vector3% value1, Vector3% tangent1, Vector3% value2, Vector3% tangent2, float amount, [Out] Vector3% result )
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
	Vector3 Vector3::Lerp( Vector3 start, Vector3 end, float factor )
	{
		Vector3 vector;

		vector.X = start.X + ((end.X - start.X) * factor);
		vector.Y = start.Y + ((end.Y - start.Y) * factor);
		vector.Z = start.Z + ((end.Z - start.Z) * factor);

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
	void Vector3::Lerp( Vector3% start, Vector3% end, float factor, [Out] Vector3% result )
	{
		result.X = start.X + ((end.X - start.X) * factor);
		result.Y = start.Y + ((end.Y - start.Y) * factor);
		result.Z = start.Z + ((end.Z - start.Z) * factor);
	}

	/// <summary>
	/// Performs a cubic interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <returns>The cubic interpolation of the two vectors.</returns>
	Vector3 Vector3::SmoothStep( Vector3 start, Vector3 end, float amount )
	{
		Vector3 vector;

		amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
		amount = (amount * amount) * (3.0f - (.02f * amount));

		vector.X = start.X + ((end.X - start.X) * amount);
		vector.Y = start.Y + ((end.Y - start.Y) * amount);
		vector.Z = start.Z + ((end.Z - start.Z) * amount);

		return vector;
	}

	/// <summary>
	/// Performs a cubic interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <param name="result">When the method completes, contains the cubic interpolation of the two vectors.</param>
	void Vector3::SmoothStep( Vector3% start, Vector3% end, float amount, [Out] Vector3% result )
	{
		amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
		amount = (amount * amount) * (3.0f - (.02f * amount));

		result.X = start.X + ((end.X - start.X) * amount);
		result.Y = start.Y + ((end.Y - start.Y) * amount);
		result.Z = start.Z + ((end.Z - start.Z) * amount);
	}

	/// <summary>
	/// Calculates the distance between two vectors.
	/// </summary>
	/// <param name="value1">The first vector.</param>
	/// <param name="value2">The second vector.</param>
	/// <returns>The distance between the two vectors.</returns>
	float Vector3::Distance( Vector3 value1, Vector3 value2 )
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		float z = value1.Z - value2.Z;

		return static_cast<float>( Math::Sqrt( (x * x) + (y * y) + (z * z) ) );
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
	float Vector3::DistanceSquared( Vector3 value1, Vector3 value2 )
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		float z = value1.Z - value2.Z;

		return (x * x) + (y * y) + (z * z);
	}

	/// <summary>
	/// Calculates the dot product of two vectors.
	/// </summary>
	/// <param name="left">First source vector.</param>
	/// <param name="right">Second source vector.</param>
	/// <returns>The dot product of the two vectors.</returns>
	float Vector3::Dot( Vector3 left, Vector3 right )
	{
		return (left.X * right.X + left.Y * right.Y + left.Z * right.Z);
	}

	/// <summary>
	/// Calculates the cross product of two vectors.
	/// </summary>
	/// <param name="left">First source vector.</param>
	/// <param name="right">Second source vector.</param>
	/// <returns>The cross product of the two vectors.</returns>
	Vector3 Vector3::Cross( Vector3 left, Vector3 right )
	{
		Vector3 result;
		result.X = left.Y * right.Z - left.Z * right.Y;
		result.Y = left.Z * right.X - left.X * right.Z;
		result.Z = left.X * right.Y - left.Y * right.X;
		return result;
	}

	/// <summary>
	/// Calculates the cross product of two vectors.
	/// </summary>
	/// <param name="left">First source vector.</param>
	/// <param name="right">Second source vector.</param>
	/// <returns>The cross product of the two vectors.</returns>
	void Vector3::Cross( Vector3% left, Vector3% right, [Out] Vector3% result )
	{
		Vector3 r;
		r.X = left.Y * right.Z - left.Z * right.Y;
		r.Y = left.Z * right.X - left.X * right.Z;
		r.Z = left.X * right.Y - left.Y * right.X; 

		result = r;
	}

	/// <summary>
	/// Returns the reflection of a vector off a surface that has the specified normal. 
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="normal">Normal of the surface.</param>
	/// <returns>The reflected vector.</returns>
	/// <remarks>Reflect only gives the direction of a reflection off a surface, it does not determine 
	/// whether the original vector was close enough to the surface to hit it.</remarks>
	Vector3 Vector3::Reflect( Vector3 vector, Vector3 normal )
	{
		Vector3 result;
		float dot = ((vector.X * normal.X) + (vector.Y * normal.Y)) + (vector.Z * normal.Z);

		result.X = vector.X - ((2.0f * dot) * normal.X);
		result.Y = vector.Y - ((2.0f * dot) * normal.Y);
		result.Z = vector.Z - ((2.0f * dot) * normal.Z);

		return result;
	}

	/// <summary>
	/// Returns the reflection of a vector off a surface that has the specified normal. 
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="normal">Normal of the surface.</param>
	/// <param name="result">When the method completes, contains the reflected vector.</param>
	/// <remarks>Reflect only gives the direction of a reflection off a surface, it does not determine 
	/// whether the original vector was close enough to the surface to hit it.</remarks>
	void Vector3::Reflect( Vector3% vector, Vector3% normal, [Out] Vector3% result )
	{
		float dot = ((vector.X * normal.X) + (vector.Y * normal.Y)) + (vector.Z * normal.Z);

		result.X = vector.X - ((2.0f * dot) * normal.X);
		result.Y = vector.Y - ((2.0f * dot) * normal.Y);
		result.Z = vector.Z - ((2.0f * dot) * normal.Z);
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	/// <param name="vector">The vector to normalize.</param>
	/// <returns>The normalized vector.</returns>
	Vector3 Vector3::Normalize( Vector3 vector )
	{
		vector.Normalize();
		return vector;
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	/// <param name="vector">The vector to normalize.</param>
	/// <param name="result">When the method completes, contains the normalized vector.</param>
	void Vector3::Normalize( Vector3% vector, [Out] Vector3% result )
	{
		result = Vector3(vector);
		result.Normalize();
	}

	/// <summary>
	/// Transforms a 3D vector by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	Vector4 Vector3::Transform( Vector3 vector, Matrix transform )
	{
		Vector4 result;

		result.X = (((vector.X * transform.M11) + (vector.Y * transform.M21)) + (vector.Z * transform.M31)) + transform.M41;
		result.Y = (((vector.X * transform.M12) + (vector.Y * transform.M22)) + (vector.Z * transform.M32)) + transform.M42;
		result.Z = (((vector.X * transform.M13) + (vector.Y * transform.M23)) + (vector.Z * transform.M33)) + transform.M43;
		result.W = (((vector.X * transform.M14) + (vector.Y * transform.M24)) + (vector.Z * transform.M34)) + transform.M44;

		return result;
	}

	/// <summary>
	/// Transforms a 3D vector by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
	void Vector3::Transform( Vector3% vector, Matrix% transform, [Out] Vector4% result )
	{
		result = Vector4();
		result.X = (((vector.X * transform.M11) + (vector.Y * transform.M21)) + (vector.Z * transform.M31)) + transform.M41;
		result.Y = (((vector.X * transform.M12) + (vector.Y * transform.M22)) + (vector.Z * transform.M32)) + transform.M42;
		result.Z = (((vector.X * transform.M13) + (vector.Y * transform.M23)) + (vector.Z * transform.M33)) + transform.M43;
		result.W = (((vector.X * transform.M14) + (vector.Y * transform.M24)) + (vector.Z * transform.M34)) + transform.M44;
	}

	/// <summary>
	/// Transforms an array of 3D vectors by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vectors">The source vectors.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>s.</returns>
	array<Vector4>^ Vector3::Transform( array<Vector3>^ vectors, Matrix% transform )
	{
		if( vectors == nullptr )
			throw gcnew ArgumentNullException( "vectors" );

		int count = vectors->Length;
		array<Vector4>^ results = gcnew array<Vector4>( count );

		for( int i = 0; i < count; i++ )
		{
			Vector4 r;
			r.X = (((vectors[i].X * transform.M11) + (vectors[i].Y * transform.M21)) + (vectors[i].Z * transform.M31)) + transform.M41;
			r.Y = (((vectors[i].X * transform.M12) + (vectors[i].Y * transform.M22)) + (vectors[i].Z * transform.M32)) + transform.M42;
			r.Z = (((vectors[i].X * transform.M13) + (vectors[i].Y * transform.M23)) + (vectors[i].Z * transform.M33)) + transform.M43;
			r.W = (((vectors[i].X * transform.M14) + (vectors[i].Y * transform.M24)) + (vectors[i].Z * transform.M34)) + transform.M44;
		
			results[i] = r;
		}

		return results;
	}

	/// <summary>
	/// Transforms a 3D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vector">The vector to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	Vector4 Vector3::Transform( Vector3 value, Quaternion rotation )
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
		vector.W = 1.0f;

		return vector;
	}

	/// <summary>
	/// Transforms a 3D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vector">The vector to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
	void Vector3::Transform( Vector3% value, Quaternion% rotation, [Out] Vector4% result )
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

		result = Vector4();
		result.X = ((value.X * ((1.0f - yy) - zz)) + (value.Y * (xy - wz))) + (value.Z * (xz + wy));
		result.Y = ((value.X * (xy + wz)) + (value.Y * ((1.0f - xx) - zz))) + (value.Z * (yz - wx));
		result.Z = ((value.X * (xz - wy)) + (value.Y * (yz + wx))) + (value.Z * ((1.0f - xx) - yy));
		result.W = 1.0f;
	}

	/// <summary>
	/// Transforms an array of 3D vectors by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vectors">The vectors to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	array<Vector4>^ Vector3::Transform( array<Vector3>^ vectors, Quaternion% rotation )
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
			r.W = 1.0f;

			results[i] = r;
		}

		return results;
	}

	/// <summary>
	/// Performs a coordinate transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="coordinate">The coordinate vector to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed coordinates.</returns>
	Vector3 Vector3::TransformCoordinate( Vector3 coord, Matrix transform )
	{
		Vector4 vector;

		vector.X = (((coord.X * transform.M11) + (coord.Y * transform.M21)) + (coord.Z * transform.M31)) + transform.M41;
		vector.Y = (((coord.X * transform.M12) + (coord.Y * transform.M22)) + (coord.Z * transform.M32)) + transform.M42;
		vector.Z = (((coord.X * transform.M13) + (coord.Y * transform.M23)) + (coord.Z * transform.M33)) + transform.M43;
		vector.W = 1 / ((((coord.X * transform.M14) + (coord.Y * transform.M24)) + (coord.Z * transform.M34)) + transform.M44);

		return Vector3( vector.X * vector.W, vector.Y * vector.W, vector.Z * vector.W );
	}

	/// <summary>
	/// Performs a coordinate transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="coordinate">The coordinate vector to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <param name="result">When the method completes, contains the transformed coordinates.</param>
	void Vector3::TransformCoordinate( Vector3% coord, Matrix% transform, [Out] Vector3% result )
	{
		Vector4 vector;

		vector.X = (((coord.X * transform.M11) + (coord.Y * transform.M21)) + (coord.Z * transform.M31)) + transform.M41;
		vector.Y = (((coord.X * transform.M12) + (coord.Y * transform.M22)) + (coord.Z * transform.M32)) + transform.M42;
		vector.Z = (((coord.X * transform.M13) + (coord.Y * transform.M23)) + (coord.Z * transform.M33)) + transform.M43;
		vector.W = 1 / ((((coord.X * transform.M14) + (coord.Y * transform.M24)) + (coord.Z * transform.M34)) + transform.M44);

		result = Vector3( vector.X * vector.W, vector.Y * vector.W, vector.Z * vector.W );
	}

	/// <summary>
	/// Performs a coordinate transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="coordinates">The coordinate vectors to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed coordinates.</returns>
	array<Vector3>^ Vector3::TransformCoordinate( array<Vector3>^ coords, Matrix% transform )
	{
		if( coords == nullptr )
			throw gcnew ArgumentNullException( "coordinates" );

		Vector4 vector;
		int count = coords->Length;
		array<Vector3>^ results = gcnew array<Vector3>( count );

		for( int i = 0; i < count; i++ )
		{
			vector.X = (((coords[i].X * transform.M11) + (coords[i].Y * transform.M21)) + (coords[i].Z * transform.M31)) + transform.M41;
			vector.Y = (((coords[i].X * transform.M12) + (coords[i].Y * transform.M22)) + (coords[i].Z * transform.M32)) + transform.M42;
			vector.Z = (((coords[i].X * transform.M13) + (coords[i].Y * transform.M23)) + (coords[i].Z * transform.M33)) + transform.M43;
			vector.W = 1 / ((((coords[i].X * transform.M14) + (coords[i].Y * transform.M24)) + (coords[i].Z * transform.M34)) + transform.M44);
			results[i] = Vector3( vector.X * vector.W, vector.Y * vector.W, vector.Z * vector.W );
		}

		return results;
	}

	/// <summary>
	/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="normal">The normal vector to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed normal.</returns>
	Vector3 Vector3::TransformNormal( Vector3 normal, Matrix transform )
	{
		Vector3 vector;

		vector.X = ((normal.X * transform.M11) + (normal.Y * transform.M21)) + (normal.Z * transform.M31);
		vector.Y = ((normal.X * transform.M12) + (normal.Y * transform.M22)) + (normal.Z * transform.M32);
		vector.Z = ((normal.X * transform.M13) + (normal.Y * transform.M23)) + (normal.Z * transform.M33);

		return vector;
	}

	/// <summary>
	/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="normal">The normal vector to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <param name="result">When the method completes, contains the transformed normal.</param>
	void Vector3::TransformNormal( Vector3% normal, Matrix% transform, [Out] Vector3% result )
	{
		result.X = ((normal.X * transform.M11) + (normal.Y * transform.M21)) + (normal.Z * transform.M31);
		result.Y = ((normal.X * transform.M12) + (normal.Y * transform.M22)) + (normal.Z * transform.M32);
		result.Z = ((normal.X * transform.M13) + (normal.Y * transform.M23)) + (normal.Z * transform.M33);
	}

	/// <summary>
	/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="normals">The normal vectors to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed normals.</returns>
	array<Vector3>^ Vector3::TransformNormal( array<Vector3>^ normals, Matrix% transform )
	{
		if( normals == nullptr )
			throw gcnew ArgumentNullException( "normals" );

		int count = normals->Length;
		array<Vector3>^ results = gcnew array<Vector3>( count );

		for( int i = 0; i < count; i++ )
		{
			Vector3 r;
			r.X = ((normals[i].X * transform.M11) + (normals[i].Y * transform.M21)) + (normals[i].Z * transform.M31);
			r.Y = ((normals[i].X * transform.M12) + (normals[i].Y * transform.M22)) + (normals[i].Z * transform.M32);
			r.Z = ((normals[i].X * transform.M13) + (normals[i].Y * transform.M23)) + (normals[i].Z * transform.M33);
		
			results[i] = r;
		}

		return results;
	}

	/// <summary>
	/// Projects a 3D vector from object space into screen space. 
	/// </summary>
	/// <param name="vector">The vector to project.</param>
	/// <param name="viewport">The viewport representing screen space.</param>
	/// <param name="projection">The projection matrix.</param>
	/// <param name="view">The view matrix.</param>
	/// <param name="world">The world matrix.</param>
	/// <returns>The vector in screen space.</returns>
	Vector3 Vector3::Project( Vector3 vector, SlimDX::Viewport viewport, Matrix projection, Matrix view, Matrix world )
	{
		Vector3 result;

		D3DXVec3Project( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &vector, (D3DVIEWPORT9*) &viewport,
			(D3DXMATRIX*) &projection, (D3DXMATRIX*) &view, (D3DXMATRIX*) &world );

		return result;
	}

	/// <summary>
	/// Projects a 3D vector from object space into screen space. 
	/// </summary>
	/// <param name="vector">The vector to project.</param>
	/// <param name="viewport">The viewport representing screen space.</param>
	/// <param name="projection">The projection matrix.</param>
	/// <param name="view">The view matrix.</param>
	/// <param name="world">The world matrix.</param>
	/// <param name="result">When the method completes, contains the vector in screen space.</param>
	void Vector3::Project( Vector3% vector, SlimDX::Viewport% viewport, Matrix% projection, Matrix% view, Matrix% world, [Out] Vector3% result )
	{
		pin_ptr<Vector3> pinVector = &vector;
		pin_ptr<SlimDX::Viewport> pinViewport = &viewport;
		pin_ptr<Matrix> pinProjection = &projection;
		pin_ptr<Matrix> pinView = &view;
		pin_ptr<Matrix> pinWorld = &world;
		pin_ptr<Vector3> pinResult = &result;

		D3DXVec3Project( (D3DXVECTOR3*) &pinResult, (D3DXVECTOR3*) &pinVector, (D3DVIEWPORT9*) &pinViewport,
			(D3DXMATRIX*) &pinProjection, (D3DXMATRIX*) &pinView, (D3DXMATRIX*) &pinWorld ); 
	}

	/// <summary>
	/// Projects a 3D vector from screen space into object space. 
	/// </summary>
	/// <param name="vector">The vector to project.</param>
	/// <param name="viewport">The viewport representing screen space.</param>
	/// <param name="projection">The projection matrix.</param>
	/// <param name="view">The view matrix.</param>
	/// <param name="world">The world matrix.</param>
	/// <returns>The vector in object space.</returns>
	Vector3 Vector3::Unproject( Vector3 vector, SlimDX::Viewport viewport, Matrix projection, Matrix view, Matrix world )
	{
		Vector3 result;

		D3DXVec3Unproject( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &vector, (D3DVIEWPORT9*) &viewport,
			(D3DXMATRIX*) &projection, (D3DXMATRIX*) &view, (D3DXMATRIX*) &world );

		return result;
	}

	/// <summary>
	/// Projects a 3D vector from screen space into object space. 
	/// </summary>
	/// <param name="vector">The vector to project.</param>
	/// <param name="viewport">The viewport representing screen space.</param>
	/// <param name="projection">The projection matrix.</param>
	/// <param name="view">The view matrix.</param>
	/// <param name="world">The world matrix.</param>
	/// <param name="result">When the method completes, contains the vector in object space.</param>
	void Vector3::Unproject( Vector3% vector, SlimDX::Viewport% viewport, Matrix% projection, Matrix% view, Matrix% world, [Out] Vector3% result )
	{
		pin_ptr<Vector3> pinVector = &vector;
		pin_ptr<SlimDX::Viewport> pinViewport = &viewport;
		pin_ptr<Matrix> pinProjection = &projection;
		pin_ptr<Matrix> pinView = &view;
		pin_ptr<Matrix> pinWorld = &world;
		pin_ptr<Vector3> pinResult = &result;

		D3DXVec3Unproject( (D3DXVECTOR3*) &pinResult, (D3DXVECTOR3*) &pinVector, (D3DVIEWPORT9*) &pinViewport,
			(D3DXMATRIX*) &pinProjection, (D3DXMATRIX*) &pinView, (D3DXMATRIX*) &pinWorld ); 
	}
	
	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <returns>A vector containing the smallest components of the source vectors.</returns>
	Vector3 Vector3::Minimize( Vector3 left, Vector3 right )
	{
		Vector3 vector;
		vector.X = (left.X < right.X) ? left.X : right.X;
		vector.Y = (left.Y < right.Y) ? left.Y : right.Y;
		vector.Z = (left.Z < right.Z) ? left.Z : right.Z;
		return vector;
	}

	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <param name="result">When the method completes, contains an new vector composed of the smallest components of the source vectors.</param>
	void Vector3::Minimize( Vector3% left, Vector3% right, [Out] Vector3% result )
	{
		result.X = (left.X < right.X) ? left.X : right.X;
		result.Y = (left.Y < right.Y) ? left.Y : right.Y;
		result.Z = (left.Z < right.Z) ? left.Z : right.Z;
	}
	
	/// <summary>
	/// Returns a vector containing the largest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <returns>A vector containing the largest components of the source vectors.</returns>
	Vector3 Vector3::Maximize( Vector3 left, Vector3 right )
	{
		Vector3 vector;
		vector.X = (left.X > right.X) ? left.X : right.X;
		vector.Y = (left.Y > right.Y) ? left.Y : right.Y;
		vector.Z = (left.Z > right.Z) ? left.Z : right.Z;
		return vector;
	}

	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <param name="result">When the method completes, contains an new vector composed of the largest components of the source vectors.</param>
	void Vector3::Maximize( Vector3% left, Vector3% right, [Out] Vector3% result )
	{
		result.X = (left.X > right.X) ? left.X : right.X;
		result.Y = (left.Y > right.Y) ? left.Y : right.Y;
		result.Z = (left.Z > right.Z) ? left.Z : right.Z;
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <returns>The sum of the two vectors.</returns>
	Vector3 Vector3::operator + ( Vector3 left, Vector3 right )
	{
		return Vector3( left.X + right.X, left.Y + right.Y, left.Z + right.Z );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <returns>The difference of the two vectors.</returns>
	Vector3 Vector3::operator - ( Vector3 left, Vector3 right )
	{
		return Vector3( left.X - right.X, left.Y - right.Y, left.Z - right.Z );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <returns>A vector facing in the opposite direction.</returns>
	Vector3 Vector3::operator - ( Vector3 value )
	{
		return Vector3( -value.X, -value.Y, -value.Z );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector3 Vector3::operator * ( Vector3 value, float scale )
	{
		return Vector3( value.X * scale, value.Y * scale, value.Z * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector3 Vector3::operator * ( float scale, Vector3 vec )
	{
		return vec * scale;
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector3 Vector3::operator / ( Vector3 value, float scale )
	{
		return Vector3( value.X / scale, value.Y / scale, value.Z / scale );
	}

	/// <summary>
	/// Tests vectors for equality. 
	/// </summary>
	/// <param name="left">The first source vector.</param>
	/// <param name="right">The second source vector.</param>
	/// <returns><c>true</c> if the vectors are equal; <c>false</c> otherwise.</returns>
	bool Vector3::operator == ( Vector3 left, Vector3 right )
	{
		return Vector3::Equals( left, right );
	}

	/// <summary>
	/// Tests vectors for inequality. 
	/// </summary>
	/// <param name="left">The first source vector.</param>
	/// <param name="right">The second source vector.</param>
	/// <returns><c>true</c> if the vectors are not equal; <c>false</c> otherwise.</returns>
	bool Vector3::operator != ( Vector3 left, Vector3 right )
	{
		return !Vector3::Equals( left, right );
	}

	/// <summary>
	/// Retrieves a string representation of the current object. 
	/// </summary>
	/// <returns>A string that represents the object.</returns>
	String^ Vector3::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "X:{0} Y:{1} Z:{2}", X.ToString(CultureInfo::CurrentCulture), Y.ToString(CultureInfo::CurrentCulture), Z.ToString(CultureInfo::CurrentCulture) );
	}

	/// <summary>
	/// Gets the hash code of the vector object. 
	/// </summary>
	/// <returns>Hash code of the vector object.</returns>
	int Vector3::GetHashCode()
	{
		return X.GetHashCode() + Y.GetHashCode() + Z.GetHashCode();
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to a specified object. 
	/// </summary>
	/// <param name="obj">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Vector3::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<Vector3>( value ) );
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to the specified object. 
	/// </summary>
	/// <param name="other">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Vector3::Equals( Vector3 value )
	{
		return ( X == value.X && Y == value.Y && Z == value.Z );
	}

	/// <summary>
	/// Determines whether the specified Object instances are considered equal. 
	/// </summary>
	/// <param name="value1"></param>
	/// <param name="value2"></param>
	/// <returns><c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
	/// if both are <c>null</c> references or if <c>objA.Equals(objB)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
	bool Vector3::Equals( Vector3% value1, Vector3% value2 )
	{
		return ( value1.X == value2.X && value1.Y == value2.Y && value1.Z == value2.Z );
	}
}