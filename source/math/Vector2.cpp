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
	/// Initializes a new instance of the <see cref="SlimDX::Vector2"/> class.
	/// </summary>
	/// <param name="value">The value that will be assigned to all components.</param>
	Vector2::Vector2( float value )
	{
		X = value;
		Y = value;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Vector2"/> class.
	/// </summary>
	/// <param name="x">Initial value for the X component of the vector.</param>
	/// <param name="y">Initial value for the Y component of the vector.</param>
	Vector2::Vector2( float x, float y )
	{
		X = x;
		Y = y;
	}

	/// <summary>
	/// Calculates the length of the vector.
	/// </summary>
	/// <returns>The length of the vector.</returns>
	float Vector2::Length()
	{
		return static_cast<float>( Math::Sqrt( (X * X) + (Y * Y) ) );
	}

	/// <summary>
	/// Calculates the squared length of the vector.
	/// </summary>
	/// <returns>The squared length of the vector.</returns>
	float Vector2::LengthSquared()
	{
		return (X * X) + (Y * Y);
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	void Vector2::Normalize()
	{
		float length = Length();
		if( length == 0 )
			return;
		float num = 1 / length;
		X *= num;
		Y *= num;
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <returns>The sum of the two vectors.</returns>
	Vector2 Vector2::Add( Vector2 left, Vector2 right )
	{
		return Vector2( left.X + right.X, left.Y + right.Y );
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <param name="result">When the method completes, contains the sum of the two vectors.</param>
	void Vector2::Add( Vector2% left, Vector2% right, [Out] Vector2% result )
	{
		result = Vector2( left.X + right.X, left.Y + right.Y );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <returns>The difference of the two vectors.</returns>
	Vector2 Vector2::Subtract( Vector2 left, Vector2 right )
	{
		return Vector2( left.X - right.X, left.Y - right.Y );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <param name="result">When the method completes, contains the difference of the two vectors.</param>
	void Vector2::Subtract( Vector2% left, Vector2% right, [Out] Vector2% result )
	{
		result = Vector2( left.X - right.X, left.Y - right.Y );
	}


	/// <summary>
	/// Modulates a vector by another.
	/// </summary>
	/// <param name="left">The first vector to modulate.</param>
	/// <param name="right">The second vector to modulate.</param>
	/// <returns>The modulated vector.</returns>
	Vector2 Vector2::Modulate( Vector2 left, Vector2 right )
	{
		return Vector2( left.X * right.X, left.Y * right.Y );
	}

	/// <summary>
	/// Modulates a vector by another.
	/// </summary>
	/// <param name="left">The first vector to modulate.</param>
	/// <param name="right">The second vector to modulate.</param>
	/// <param name="result">When the moethod completes, contains the modulated vector.</param>
	void Vector2::Modulate( Vector2% left, Vector2% right, [Out] Vector2% result )
	{
		result = Vector2( left.X * right.X, left.Y * right.Y );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="value">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector2 Vector2::Multiply( Vector2 value, float scale )
	{
		return Vector2( value.X * scale, value.Y * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <param name="result">When the method completes, contains the scaled vector.</param>
	void Vector2::Multiply( Vector2% value, float scale, [Out] Vector2% result )
	{
		result = Vector2( value.X * scale, value.Y * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="value">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector2 Vector2::Divide( Vector2 value, float scale )
	{
		return Vector2( value.X / scale, value.Y / scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <param name="result">When the method completes, contains the scaled vector.</param>
	void Vector2::Divide( Vector2% value, float scale, [Out] Vector2% result )
	{
		result = Vector2( value.X / scale, value.Y / scale );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <returns>A vector facing in the opposite direction.</returns>
	Vector2 Vector2::Negate( Vector2 value )
	{
		return Vector2( -value.X, -value.Y );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <param name="result">When the method completes, contains a vector facing in the opposite direction.</param>
	void Vector2::Negate( Vector2% value, [Out] Vector2% result )
	{
		result = Vector2( -value.X, -value.Y );
	}

	/// <summary>
	/// Returns a <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 2D triangle.
	/// </summary>
	/// <param name="value1">A <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of vertex 1 of the triangle.</param>
	/// <param name="value2">A <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of vertex 2 of the triangle.</param>
	/// <param name="value3">A <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of vertex 3 of the triangle.</param>
	/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
	/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
	/// <returns>A new <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of the specified point.</returns>
	Vector2 Vector2::Barycentric( Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2 )
	{
		Vector2 vector;
		vector.X = (value1.X + (amount1 * (value2.X - value1.X))) + (amount2 * (value3.X - value1.X));
		vector.Y = (value1.Y + (amount1 * (value2.Y - value1.Y))) + (amount2 * (value3.Y - value1.Y));
		return vector;
	}

	/// <summary>
	/// Returns a <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 2D triangle.
	/// </summary>
	/// <param name="value1">A <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of vertex 1 of the triangle.</param>
	/// <param name="value2">A <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of vertex 2 of the triangle.</param>
	/// <param name="value3">A <see cref="SlimDX::Vector2"/> containing the 2D Cartesian coordinates of vertex 3 of the triangle.</param>
	/// <param name="amount1">Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in <paramref name="value2"/>).</param>
	/// <param name="amount2">Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in <paramref name="value3"/>).</param>
	/// <param name="result">When the method completes, contains the 2D Cartesian coordinates of the specified point.</param>
	void Vector2::Barycentric( Vector2% value1, Vector2% value2, Vector2% value3, float amount1, float amount2, [Out] Vector2% result )
	{
		result = Vector2((value1.X + (amount1 * (value2.X - value1.X))) + (amount2 * (value3.X - value1.X)),
			(value1.Y + (amount1 * (value2.Y - value1.Y))) + (amount2 * (value3.Y - value1.Y)) );
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
	Vector2 Vector2::CatmullRom( Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount )
	{
		Vector2 vector;
		float squared = amount * amount;
		float cubed = amount * squared;

		vector.X = 0.5f * ((((2.0f * value2.X) + ((-value1.X + value3.X) * amount)) + 
			(((((2.0f * value1.X) - (5.0f * value2.X)) + (4.0f * value3.X)) - value4.X) * squared)) + 
			((((-value1.X + (3.0f * value2.X)) - (3.0f * value3.X)) + value4.X) * cubed));

		vector.Y = 0.5f * ((((2.0f * value2.Y) + ((-value1.Y + value3.Y) * amount)) + 
			(((((2.0f * value1.Y) - (5.0f * value2.Y)) + (4.0f * value3.Y)) - value4.Y) * squared)) + 
			((((-value1.Y + (3.0f * value2.Y)) - (3.0f * value3.Y)) + value4.Y) * cubed));

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
	void Vector2::CatmullRom( Vector2% value1, Vector2% value2, Vector2% value3, Vector2% value4, float amount, [Out] Vector2% result )
	{
		float squared = amount * amount;
		float cubed = amount * squared;
		Vector2 r;

		r.X = 0.5f * ((((2.0f * value2.X) + ((-value1.X + value3.X) * amount)) + 
			(((((2.0f * value1.X) - (5.0f * value2.X)) + (4.0f * value3.X)) - value4.X) * squared)) + 
			((((-value1.X + (3.0f * value2.X)) - (3.0f * value3.X)) + value4.X) * cubed));

		r.Y = 0.5f * ((((2.0f * value2.Y) + ((-value1.Y + value3.Y) * amount)) + 
			(((((2.0f * value1.Y) - (5.0f * value2.Y)) + (4.0f * value3.Y)) - value4.Y) * squared)) + 
			((((-value1.Y + (3.0f * value2.Y)) - (3.0f * value3.Y)) + value4.Y) * cubed));

		result = r;
	}

	/// <summary>
	/// Restricts a value to be within a specified range.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <returns>The clamped value.</returns>
	Vector2 Vector2::Clamp( Vector2 value, Vector2 min, Vector2 max )
	{
		float x = value.X;
		x = (x > max.X) ? max.X : x;
		x = (x < min.X) ? min.X : x;

		float y = value.Y;
		y = (y > max.Y) ? max.Y : y;
		y = (y < min.Y) ? min.Y : y;

		return Vector2( x, y );
	}

	/// <summary>
	/// Restricts a value to be within a specified range.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <param name="result">When the method completes, contains the clamped value.</param>
	void Vector2::Clamp( Vector2% value, Vector2% min, Vector2% max, [Out] Vector2% result )
	{
		float x = value.X;
		x = (x > max.X) ? max.X : x;
		x = (x < min.X) ? min.X : x;

		float y = value.Y;
		y = (y > max.Y) ? max.Y : y;
		y = (y < min.Y) ? min.Y : y;

		result = Vector2( x, y );
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
	Vector2 Vector2::Hermite( Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount )
	{
		Vector2 vector;
		float squared = amount * amount;
		float cubed = amount * squared;
		float part1 = ((2.0f * cubed) - (3.0f * squared)) + 1.0f;
		float part2 = (-2.0f * cubed) + (3.0f * squared);
		float part3 = (cubed - (2.0f * squared)) + amount;
		float part4 = cubed - squared;

		vector.X = (((value1.X * part1) + (value2.X * part2)) + (tangent1.X * part3)) + (tangent2.X * part4);
		vector.Y = (((value1.Y * part1) + (value2.Y * part2)) + (tangent1.Y * part3)) + (tangent2.Y * part4);

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
	void Vector2::Hermite( Vector2% value1, Vector2% tangent1, Vector2% value2, Vector2% tangent2, float amount, [Out] Vector2% result )
	{
		float squared = amount * amount;
		float cubed = amount * squared;
		float part1 = ((2.0f * cubed) - (3.0f * squared)) + 1.0f;
		float part2 = (-2.0f * cubed) + (3.0f * squared);
		float part3 = (cubed - (2.0f * squared)) + amount;
		float part4 = cubed - squared;

		Vector2 r;
		r.X = (((value1.X * part1) + (value2.X * part2)) + (tangent1.X * part3)) + (tangent2.X * part4);
		r.Y = (((value1.Y * part1) + (value2.Y * part2)) + (tangent1.Y * part3)) + (tangent2.Y * part4);

		result = r;
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
	Vector2 Vector2::Lerp( Vector2 start, Vector2 end, float factor )
	{
		Vector2 vector;

		vector.X = start.X + ((end.X - start.X) * factor);
		vector.Y = start.Y + ((end.Y - start.Y) * factor);

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
	void Vector2::Lerp( Vector2% start, Vector2% end, float factor, [Out] Vector2% result )
	{
		Vector2 r;
		r.X = start.X + ((end.X - start.X) * factor);
		r.Y = start.Y + ((end.Y - start.Y) * factor);

		result = r;
	}

	/// <summary>
	/// Performs a cubic interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <returns>The cubic interpolation of the two vectors.</returns>
	Vector2 Vector2::SmoothStep( Vector2 start, Vector2 end, float amount )
	{
		Vector2 vector;

		amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
		amount = (amount * amount) * (3.0f - (.02f * amount));

		vector.X = start.X + ((end.X - start.X) * amount);
		vector.Y = start.Y + ((end.Y - start.Y) * amount);

		return vector;
	}

	/// <summary>
	/// Performs a cubic interpolation between two vectors.
	/// </summary>
	/// <param name="start">Start vector.</param>
	/// <param name="end">End vector.</param>
	/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
	/// <param name="result">When the method completes, contains the cubic interpolation of the two vectors.</param>
	void Vector2::SmoothStep( Vector2% start, Vector2% end, float amount, [Out] Vector2% result )
	{
		amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
		amount = (amount * amount) * (3.0f - (.02f * amount));

		Vector2 r;
		r.X = start.X + ((end.X - start.X) * amount);
		r.Y = start.Y + ((end.Y - start.Y) * amount);

		result = r;
	}

	/// <summary>
	/// Calculates the distance between two vectors.
	/// </summary>
	/// <param name="value1">The first vector.</param>
	/// <param name="value2">The second vector.</param>
	/// <returns>The distance between the two vectors.</returns>
	float Vector2::Distance( Vector2 value1, Vector2 value2 )
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;

		return static_cast<float>( Math::Sqrt( (x * x) + (y * y) ) );
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
	float Vector2::DistanceSquared( Vector2 value1, Vector2 value2 )
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;

		return (x * x) + (y * y);
	}

	/// <summary>
	/// Calculates the dot product of two vectors.
	/// </summary>
	/// <param name="left">First source vector.</param>
	/// <param name="right">Second source vector.</param>
	/// <returns>The dot product of the two vectors.</returns>
	float Vector2::Dot( Vector2 left, Vector2 right )
	{
		return (left.X * right.X + left.Y * right.Y);
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	/// <param name="vector">The vector to normalize.</param>
	/// <returns>The normalized vector.</returns>
	Vector2 Vector2::Normalize( Vector2 vector )
	{
		vector.Normalize();
		return vector;
	}

	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	/// <param name="vector">The vector to normalize.</param>
	/// <param name="result">When the method completes, contains the normalized vector.</param>
	void Vector2::Normalize( Vector2% vector, [Out] Vector2% result )
	{
		result = Vector2::Normalize(vector);
	}

	/// <summary>
	/// Transforms a 2D vector by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	Vector4 Vector2::Transform( Vector2 vector, Matrix transform )
	{
		Vector4 result;

		result.X = (vector.X * transform.M11) + (vector.Y * transform.M21) + transform.M41;
		result.Y = (vector.X * transform.M12) + (vector.Y * transform.M22) + transform.M42;
		result.Z = (vector.X * transform.M13) + (vector.Y * transform.M23) + transform.M43;
		result.W = (vector.X * transform.M14) + (vector.Y * transform.M24) + transform.M44;

		return result;
	}

	/// <summary>
	/// Transforms a 2D vector by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vector">The source vector.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
	void Vector2::Transform( Vector2% vector, Matrix% transform, [Out] Vector4% result )
	{
		Vector4 r;
		r.X = (vector.X * transform.M11) + (vector.Y * transform.M21) + transform.M41;
		r.Y = (vector.X * transform.M12) + (vector.Y * transform.M22) + transform.M42;
		r.Z = (vector.X * transform.M13) + (vector.Y * transform.M23) + transform.M43;
		r.W = (vector.X * transform.M14) + (vector.Y * transform.M24) + transform.M44;

		result = r;
	}

	/// <summary>
	/// Transforms an array of 2D vectors by the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="vectors">The source vectors.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>s.</returns>
	array<Vector4>^ Vector2::Transform( array<Vector2>^ vectors, Matrix% transform )
	{
		if( vectors == nullptr )
			throw gcnew ArgumentNullException( "vectors" );

		int count = vectors->Length;
		array<Vector4>^ results = gcnew array<Vector4>( count );

		for( int i = 0; i < count; i++ )
		{
			Vector4 r;
			r.X = (vectors[i].X * transform.M11) + (vectors[i].Y * transform.M21) + transform.M41;
			r.Y = (vectors[i].X * transform.M12) + (vectors[i].Y * transform.M22) + transform.M42;
			r.Z = (vectors[i].X * transform.M13) + (vectors[i].Y * transform.M23) + transform.M43;
			r.W = (vectors[i].X * transform.M14) + (vectors[i].Y * transform.M24) + transform.M44;

			results[i] = r;
		}

		return results;
	}

	/// <summary>
	/// Transforms a 2D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vector">The vector to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	Vector4 Vector2::Transform( Vector2 value, Quaternion rotation )
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

		vector.X = ((value.X * ((1.0f - yy) - zz)) + (value.Y * (xy - wz)));
		vector.Y = ((value.X * (xy + wz)) + (value.Y * ((1.0f - xx) - zz)));
		vector.Z = ((value.X * (xz - wy)) + (value.Y * (yz + wx)));
		vector.W = 1.0f;

		return vector;
	}

	/// <summary>
	/// Transforms a 2D vector by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vector">The vector to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <param name="result">When the method completes, contains the transformed <see cref="SlimDX::Vector4"/>.</param>
	void Vector2::Transform( Vector2% value, Quaternion% rotation, [Out] Vector4% result )
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
		r.X = ((value.X * ((1.0f - yy) - zz)) + (value.Y * (xy - wz)));
		r.Y = ((value.X * (xy + wz)) + (value.Y * ((1.0f - xx) - zz)));
		r.Z = ((value.X * (xz - wy)) + (value.Y * (yz + wx)));
		r.W = 1.0f;

		result = r;
	}

	/// <summary>
	/// Transforms an array of 2D vectors by the given <see cref="SlimDX::Quaternion"/> rotation.
	/// </summary>
	/// <param name="vectors">The vectors to rotate.</param>
	/// <param name="rotation">The <see cref="SlimDX::Quaternion"/> rotation to apply.</param>
	/// <returns>The transformed <see cref="SlimDX::Vector4"/>.</returns>
	array<Vector4>^ Vector2::Transform( array<Vector2>^ vectors, Quaternion% rotation )
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
			r.X = ((vectors[i].X * ((1.0f - yy) - zz)) + (vectors[i].Y * (xy - wz)));
			r.Y = ((vectors[i].X * (xy + wz)) + (vectors[i].Y * ((1.0f - xx) - zz)));
			r.Z = ((vectors[i].X * (xz - wy)) + (vectors[i].Y * (yz + wx)));
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
	Vector2 Vector2::TransformCoordinate( Vector2 coord, Matrix transform )
	{
		Vector4 vector;

		vector.X = (coord.X * transform.M11) + (coord.Y * transform.M21) + transform.M41;
		vector.Y = (coord.X * transform.M12) + (coord.Y * transform.M22) + transform.M42;
		vector.Z = (coord.X * transform.M13) + (coord.Y * transform.M23) + transform.M43;
		vector.W = 1 / ((coord.X * transform.M14) + (coord.Y * transform.M24) + transform.M44);

		return Vector2( vector.X * vector.W, vector.Y * vector.W );
	}

	/// <summary>
	/// Performs a coordinate transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="coordinate">The coordinate vector to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <param name="result">When the method completes, contains the transformed coordinates.</param>
	void Vector2::TransformCoordinate( Vector2% coord, Matrix% transform, [Out] Vector2% result )
	{
		Vector4 vector;

		vector.X = (coord.X * transform.M11) + (coord.Y * transform.M21) + transform.M41;
		vector.Y = (coord.X * transform.M12) + (coord.Y * transform.M22) + transform.M42;
		vector.Z = (coord.X * transform.M13) + (coord.Y * transform.M23) + transform.M43;
		vector.W = 1 / ((coord.X * transform.M14) + (coord.Y * transform.M24) + transform.M44);

		result = Vector2( vector.X * vector.W, vector.Y * vector.W );
	}

	/// <summary>
	/// Performs a coordinate transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="coordinates">The coordinate vectors to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed coordinates.</returns>
	array<Vector2>^ Vector2::TransformCoordinate( array<Vector2>^ coords, Matrix% transform )
	{
		if( coords == nullptr )
			throw gcnew ArgumentNullException( "coordinates" );

		Vector4 vector;
		int count = coords->Length;
		array<Vector2>^ results = gcnew array<Vector2>( count );

		for( int i = 0; i < count; i++ )
		{
			vector.X = (coords[i].X * transform.M11) + (coords[i].Y * transform.M21) + transform.M41;
			vector.Y = (coords[i].X * transform.M12) + (coords[i].Y * transform.M22) + transform.M42;
			vector.Z = (coords[i].X * transform.M13) + (coords[i].Y * transform.M23) + transform.M43;
			vector.W = 1 / ((coords[i].X * transform.M14) + (coords[i].Y * transform.M24) + transform.M44);
			results[i] = Vector2( vector.X * vector.W, vector.Y * vector.W );
		}

		return results;
	}

	/// <summary>
	/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="normal">The normal vector to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed normal.</returns>
	Vector2 Vector2::TransformNormal( Vector2 normal, Matrix transform )
	{
		Vector2 vector;

		vector.X = (normal.X * transform.M11) + (normal.Y * transform.M21);
		vector.Y = (normal.X * transform.M12) + (normal.Y * transform.M22);

		return vector;
	}

	/// <summary>
	/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="normal">The normal vector to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <param name="result">When the method completes, contains the transformed normal.</param>
	void Vector2::TransformNormal( Vector2% normal, Matrix% transform, [Out] Vector2% result )
	{
		Vector2 r;
		r.X = (normal.X * transform.M11) + (normal.Y * transform.M21);
		r.Y = (normal.X * transform.M12) + (normal.Y * transform.M22);

		result = r;
	}

	/// <summary>
	/// Performs a normal transformation using the given <see cref="SlimDX::Matrix"/>.
	/// </summary>
	/// <param name="normals">The normal vectors to transform.</param>
	/// <param name="transformation">The transformation <see cref="SlimDX::Matrix"/>.</param>
	/// <returns>The transformed normals.</returns>
	array<Vector2>^ Vector2::TransformNormal( array<Vector2>^ normals, Matrix% transform )
	{
		if( normals == nullptr )
			throw gcnew ArgumentNullException( "normals" );

		int count = normals->Length;
		array<Vector2>^ results = gcnew array<Vector2>( count );

		for( int i = 0; i < count; i++ )
		{
			Vector2 r;
			r.X = (normals[i].X * transform.M11) + (normals[i].Y * transform.M21);
			r.Y = (normals[i].X * transform.M12) + (normals[i].Y * transform.M22);

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
	Vector2 Vector2::Minimize( Vector2 left, Vector2 right )
	{
		Vector2 vector;
		vector.X = (left.X < right.X) ? left.X : right.X;
		vector.Y = (left.Y < right.Y) ? left.Y : right.Y;
		return vector;
	}

	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <param name="result">When the method completes, contains an new vector composed of the smallest components of the source vectors.</param>
	void Vector2::Minimize( Vector2% left, Vector2% right, [Out] Vector2% result )
	{
		Vector2 r;
		r.X = (left.X < right.X) ? left.X : right.X;
		r.Y = (left.Y < right.Y) ? left.Y : right.Y;

		result = r;
	}
	
	/// <summary>
	/// Returns a vector containing the largest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <returns>A vector containing the largest components of the source vectors.</returns>
	Vector2 Vector2::Maximize( Vector2 left, Vector2 right )
	{
		Vector2 vector;
		vector.X = (left.X > right.X) ? left.X : right.X;
		vector.Y = (left.Y > right.Y) ? left.Y : right.Y;
		return vector;
	}

	/// <summary>
	/// Returns a vector containing the smallest components of the specified vectors.
	/// </summary>
	/// <param name="value1">The first source vector.</param>
	/// <param name="value2">The second source vector.</param>
	/// <param name="result">When the method completes, contains an new vector composed of the largest components of the source vectors.</param>
	void Vector2::Maximize( Vector2% left, Vector2% right, [Out] Vector2% result )
	{
		Vector2 r;
		r.X = (left.X > right.X) ? left.X : right.X;
		r.Y = (left.Y > right.Y) ? left.Y : right.Y;

		result = r;
	}

	/// <summary>
	/// Adds two vectors.
	/// </summary>
	/// <param name="left">The first vector to add.</param>
	/// <param name="right">The second vector to add.</param>
	/// <returns>The sum of the two vectors.</returns>
	Vector2 Vector2::operator + ( Vector2 left, Vector2 right )
	{
		return Vector2( left.X + right.X, left.Y + right.Y );
	}

	/// <summary>
	/// Subtracts two vectors.
	/// </summary>
	/// <param name="left">The first vector to subtract.</param>
	/// <param name="right">The second vector to subtract.</param>
	/// <returns>The difference of the two vectors.</returns>
	Vector2 Vector2::operator - ( Vector2 left, Vector2 right )
	{
		return Vector2( left.X - right.X, left.Y - right.Y );
	}

	/// <summary>
	/// Reverses the direction of a given vector.
	/// </summary>
	/// <param name="value">The vector to negate.</param>
	/// <returns>A vector facing in the opposite direction.</returns>
	Vector2 Vector2::operator - ( Vector2 value )
	{
		return Vector2( -value.X, -value.Y );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector2 Vector2::operator * ( Vector2 value, float scale )
	{
		return Vector2( value.X * scale, value.Y * scale );
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector2 Vector2::operator * ( float scale, Vector2 vec )
	{
		return vec * scale;
	}

	/// <summary>
	/// Scales a vector by the given value.
	/// </summary>
	/// <param name="vector">The vector to scale.</param>
	/// <param name="scale">The amount by which to scale the vector.</param>
	/// <returns>The scaled vector.</returns>
	Vector2 Vector2::operator / ( Vector2 value, float scale )
	{
		return Vector2( value.X / scale, value.Y / scale );
	}

	/// <summary>
	/// Tests vectors for equality. 
	/// </summary>
	/// <param name="left">The first source vector.</param>
	/// <param name="right">The second source vector.</param>
	/// <returns><c>true</c> if the vectors are equal; <c>false</c> otherwise.</returns>
	bool Vector2::operator == ( Vector2 left, Vector2 right )
	{
		return Vector2::Equals( left, right );
	}

	/// <summary>
	/// Tests vectors for inequality. 
	/// </summary>
	/// <param name="left">The first source vector.</param>
	/// <param name="right">The second source vector.</param>
	/// <returns><c>true</c> if the vectors are not equal; <c>false</c> otherwise.</returns>
	bool Vector2::operator != ( Vector2 left, Vector2 right )
	{
		return !Vector2::Equals( left, right );
	}

	/// <summary>
	/// Retrieves a string representation of the current object. 
	/// </summary>
	/// <returns>A string that represents the object.</returns>
	String^ Vector2::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "X:{0} Y:{1}", X.ToString(CultureInfo::CurrentCulture), Y.ToString(CultureInfo::CurrentCulture) );
	}

	/// <summary>
	/// Gets the hash code of the vector object. 
	/// </summary>
	/// <returns>Hash code of the vector object.</returns>
	int Vector2::GetHashCode()
	{
		return X.GetHashCode() + Y.GetHashCode();
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to a specified object. 
	/// </summary>
	/// <param name="obj">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Vector2::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<Vector2>( value ) );
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to the specified object. 
	/// </summary>
	/// <param name="other">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Vector2::Equals( Vector2 value )
	{
		return ( X == value.X && Y == value.Y );
	}

	/// <summary>
	/// Determines whether the specified Object instances are considered equal. 
	/// </summary>
	/// <param name="value1"></param>
	/// <param name="value2"></param>
	/// <returns><c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
	/// if both are <c>null</c> references or if <c>objA.Equals(objB)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
	bool Vector2::Equals( Vector2% value1, Vector2% value2 )
	{
		return ( value1.X == value2.X && value1.Y == value2.Y );
	}
}