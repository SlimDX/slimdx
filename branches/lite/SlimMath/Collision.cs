/*
* Copyright (c) 2007-2010 SlimDX Group
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
using System.Runtime.InteropServices;

namespace SlimMath
{
    /*
     * This class is organized so that the least complex objects come first so that the least
     * complex objects will have the most methods in most cases. Note that not all shapes exist
     * at this time and not all shapes have a corresponding struct. Only the objects that have
     * a corresponding struct should come first in naming and in parameter order. The order of
     * complexity is as follows:
     * 
     * 1. Point
     * 2. Ray
     * 3. Segment
     * 4. Plane
     * 5. Triangle
     * 6. Polygon (polygon that lies on a single plane)
     * 7. Tetrahedron
     * 8. Box
     * 9. AABox
     * 10. Sphere
     * 11. Ellipsoid
     * 12. Cylinder
     * 13. Cone
     * 14. Capsule
     * 15. Torus
     * 16. Polyhedron
     * 17. Frustum
    */

    /// <summary>
    /// Contains static methods to help in determining intersections, containment, etc.
    /// </summary>
    public static class Collision
    {
        /// <summary>
        /// Determines the closest point between a point and a segment.
        /// </summary>
        /// <param name="point">The point to test.</param>
        /// <param name="segment1">The starting point of the segment to test.</param>
        /// <param name="segment2">The ending point of the segment to test.</param>
        /// <param name="result">When the method completes, contains the closest point between the two objects.</param>
        public static void ClosestPointOnSegmentToPoint(ref Vector3 segment1, ref Vector3 segment2, ref Vector3 point, out Vector3 result)
        {
            Vector3 ab = segment2 - segment1;
            float t = Vector3.Dot(point - segment1, ab) / Vector3.Dot(ab, ab);

            if (t < 0.0f)
                t = 0.0f;

            if (t > 1.0f)
                t = 1.0f;

            result = segment1 + t * ab;
        }

        /// <summary>
        /// Determines the closest point between a <see cref="SlimMath.Plane"/> and a point.
        /// </summary>
        /// <param name="plane">The plane to test.</param>
        /// <param name="point">The point to test.</param>
        /// <param name="result">When the method completes, contains the closest point between the two objects.</param>
        public static void ClosestPointOnPlaneToPoint(ref Plane plane, ref Vector3 point, out Vector3 result)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 126

            float dot;
            Vector3.Dot(ref plane.Normal, ref point, out dot);
            float t = dot - plane.D;

            result = point - (t * plane.Normal);
        }

        /// <summary>
        /// Determines the closest point between a point and a triangle.
        /// </summary>
        /// <param name="point">The point to test.</param>
        /// <param name="vertex1">The first vertex to test.</param>
        /// <param name="vertex2">The second vertex to test.</param>
        /// <param name="vertex3">The third vertex to test.</param>
        /// <param name="result">When the method completes, contains the closest point between the two objects.</param>
        public static void ClosestPointOnTriangleToPoint(ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3, ref Vector3 point, out Vector3 result)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 136

            //Check if P in vertex region outside A
            Vector3 ab = vertex2 - vertex1;
            Vector3 ac = vertex3 - vertex1;
            Vector3 ap = point - vertex1;

            float d1 = Vector3.Dot(ab, ap);
            float d2 = Vector3.Dot(ac, ap);
            if (d1 <= 0.0f && d2 <= 0.0f)
            {
                result = vertex1; //Barycentric coordinates (1,0,0)
                return;
            }

            //Check if P in vertex region outside B
            Vector3 bp = point - vertex2;
            float d3 = Vector3.Dot(ab, bp);
            float d4 = Vector3.Dot(ac, bp);
            if (d3 >= 0.0f && d4 <= d3)
            {
                result = vertex2; // barycentric coordinates (0,1,0)
                return;
            }

            //Check if P in edge region of AB, if so return projection of P onto AB
            float vc = d1 * d4 - d3 * d2;
            if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
            {
                float v = d1 / (d1 - d3);
                result = vertex1 + v * ab; //Barycentric coordinates (1-v,v,0)
                return;
            }

            //Check if P in vertex region outside C
            Vector3 cp = point - vertex3;
            float d5 = Vector3.Dot(ab, cp);
            float d6 = Vector3.Dot(ac, cp);
            if (d6 >= 0.0f && d5 <= d6)
            {
                result = vertex3; //Barycentric coordinates (0,0,1)
                return;
            }

            //Check if P in edge region of AC, if so return projection of P onto AC
            float vb = d5 * d2 - d1 * d6;
            if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
            {
                float w = d2 / (d2 - d6);
                result = vertex1 + w * ac; //Barycentric coordinates (1-w,0,w)
                return;
            }

            //Check if P in edge region of BC, if so return projection of P onto BC
            float va = d3 * d6 - d5 * d4;
            if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
            {
                float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
                result = vertex2 + w * (vertex3 - vertex2); //Barycentric coordinates (0,1-w,w)
                return;
            }

            //P inside face region. Compute Q through its barycentric coordinates (u,v,w)
            float denom = 1.0f / (va + vb + vc);
            float v2 = vb * denom;
            float w2 = vc * denom;
            result = vertex1 + ab * v2 + ac * w2; //= u*vertex1 + v*vertex2 + w*vertex3, u = va * denom = 1.0f - v - w
        }

        /// <summary>
        /// Determines the closest point between a <see cref="SlimMath.BoundingBox"/> and a point.
        /// </summary>
        /// <param name="box">The box to test.</param>
        /// <param name="point">The point to test.</param>
        /// <param name="result">When the method completes, contains the closest point between the two objects.</param>
        public static void ClosestPointOnBoxToPoint(ref BoundingBox box, ref Vector3 point, out Vector3 result)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 130

            Vector3 temp;
            Vector3.Max(ref point, ref box.Minimum, out temp);
            Vector3.Min(ref temp, ref box.Maximum, out result);
        }

        /// <summary>
        /// Determines the closest point between a <see cref="SlimMath.BoundingSphere"/> and a point.
        /// </summary>
        /// <param name="sphere"></param>
        /// <param name="point">The point to test.</param>
        /// <param name="result">When the method completes, contains the closest point between the two objects;
        /// or, if the point is directly in the center of the sphere, contains <see cref="SlimMath.Vector3.Zero"/>.</param>
        public static void ClosestPointOnSphereToPoint(ref BoundingSphere sphere, ref Vector3 point, out Vector3 result)
        {
            //Source: Jorgy343
            //Reference: None

            //Get the unit direction from the sphere's center to the point.
            Vector3.Subtract(ref point, ref sphere.Center, out result);
            result.Normalize();

            //Multiply the unit direction by the sphere's radius to get a vector
            //the length of the sphere.
            result *= sphere.Radius;

            //Add the sphere's center to the direction to get a point on the sphere.
            result += sphere.Center;
        }

        /// <summary>
        /// Determines the closest point between a <see cref="SlimMath.BoundingSphere"/> and a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="sphere1">The first sphere to test.</param>
        /// <param name="sphere2">The second sphere to test.</param>
        /// <param name="result">When the method completes, contains the closest point between the two objects;
        /// or, if the point is directly in the center of the sphere, contains <see cref="SlimMath.Vector3.Zero"/>.</param>
        /// <remarks>
        /// If the two spheres are overlapping, but not directly ontop of each other, the closest point
        /// is the 'closest' point of intersection. This can also be considered is the deepest point of
        /// intersection.
        /// </remarks>
        public static void ClosestPointOnSphereToSphere(ref BoundingSphere sphere1, ref BoundingSphere sphere2, out Vector3 result)
        {
            //Source: Jorgy343
            //Reference: None

            //Get the unit direction from the first sphere's center to the second sphere's center.
            Vector3.Subtract(ref sphere2.Center, ref sphere1.Center, out result);
            result.Normalize();

            //Multiply the unit direction by the first sphere's radius to get a vector
            //the length of the first sphere.
            result *= sphere1.Radius;

            //Add the first sphere's center to the direction to get a point on the first sphere.
            result += sphere1.Center;
        }

        /// <summary>
        /// Determines the distance between a <see cref="SlimMath.Plane"/> and a point.
        /// </summary>
        /// <param name="plane">The plane to test.</param>
        /// <param name="point">The point to test.</param>
        /// <returns>The distance between the two objects.</returns>
        public static float DistancePlanePoint(ref Plane plane, ref Vector3 point)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 127

            float dot;
            Vector3.Dot(ref plane.Normal, ref point, out dot);
            return dot - plane.D;
        }

        /// <summary>
        /// Determines the distance between a <see cref="SlimMath.BoundingBox"/> and a point.
        /// </summary>
        /// <param name="box">The box to test.</param>
        /// <param name="point">The point to test.</param>
        /// <returns>The distance between the two objects.</returns>
        public static float DistanceBoxPoint(ref BoundingBox box, ref Vector3 point)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 131

            float distance = 0f;

            if (point.X < box.Minimum.X)
                distance += (box.Minimum.X - point.X) * (box.Minimum.X - point.X);
            if (point.X > box.Maximum.X)
                distance += (point.X - box.Maximum.X) * (point.X - box.Maximum.X);

            if (point.Y < box.Minimum.Y)
                distance += (box.Minimum.Y - point.Y) * (box.Minimum.Y - point.Y);
            if (point.Y > box.Maximum.Y)
                distance += (point.Y - box.Maximum.Y) * (point.Y - box.Maximum.Y);

            if (point.Z < box.Minimum.Z)
                distance += (box.Minimum.Z - point.Z) * (box.Minimum.Z - point.Z);
            if (point.Z > box.Maximum.Z)
                distance += (point.Z - box.Maximum.Z) * (point.Z - box.Maximum.Z);

            return (float)Math.Sqrt(distance);
        }

        /// <summary>
        /// Determines the distance between a <see cref="SlimMath.BoundingBox"/> and a <see cref="SlimMath.BoundingBox"/>.
        /// </summary>
        /// <param name="box1">The first box to test.</param>
        /// <param name="box2">The second box to test.</param>
        /// <returns>The distance between the two objects.</returns>
        public static float DistanceBoxBox(ref BoundingBox box1, ref BoundingBox box2)
        {
            float distance = 0f;

            //Distance for X.
            if (box1.Minimum.X > box2.Maximum.X)
            {
                float delta = box2.Maximum.X - box1.Minimum.X;
                distance += delta * delta;
            }
            else if (box2.Minimum.X > box1.Maximum.X)
            {
                float delta = box1.Maximum.X - box2.Minimum.X;
                distance += delta * delta;
            }

            //Distance for Y.
            if (box1.Minimum.Y > box2.Maximum.Y)
            {
                float delta = box2.Maximum.Y - box1.Minimum.Y;
                distance += delta * delta;
            }
            else if (box2.Minimum.Y > box1.Maximum.Y)
            {
                float delta = box1.Maximum.Y - box2.Minimum.Y;
                distance += delta * delta;
            }

            //Distance for Z.
            if (box1.Minimum.Z > box2.Maximum.Z)
            {
                float delta = box2.Maximum.Z - box1.Minimum.Z;
                distance += delta * delta;
            }
            else if (box2.Minimum.Z > box1.Maximum.Z)
            {
                float delta = box1.Maximum.Z - box2.Minimum.Z;
                distance += delta * delta;
            }

            return (float)Math.Sqrt(distance);
        }

        /// <summary>
        /// Determines the distance between a <see cref="SlimMath.BoundingSphere"/> and a point.
        /// </summary>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="point">The point to test.</param>
        /// <returns>The distance between the two objects.</returns>
        public static float DistanceSpherePoint(ref BoundingSphere sphere, ref Vector3 point)
        {
            //Source: Jorgy343
            //Reference: None

            float distance;
            Vector3.Distance(ref sphere.Center, ref point, out distance);
            distance -= sphere.Radius;

            return Math.Max(distance, 0f);
        }

        /// <summary>
        /// Determines the distance between a <see cref="SlimMath.BoundingSphere"/> and a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="sphere1">The first sphere to test.</param>
        /// <param name="sphere2">The second sphere to test.</param>
        /// <returns>The distance between the two objects.</returns>
        public static float DistanceSphereSphere(ref BoundingSphere sphere1, ref BoundingSphere sphere2)
        {
            //Source: Jorgy343
            //Reference: None

            float distance;
            Vector3.Distance(ref sphere1.Center, ref sphere2.Center, out distance);
            distance -= sphere1.Radius + sphere2.Radius;

            return Math.Max(distance, 0f);
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a point.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="point">The point to test.</param>
        /// <returns>Whether the two objects intersect.</returns>
        public static bool RayIntersectsPoint(ref Ray ray, ref Vector3 point)
        {
            //Source: RayIntersectsSphere
            //Reference: None

            Vector3 m;
            Vector3.Subtract(ref ray.Position, ref point, out m);

            //Same thing as RayIntersectsSphere except that the radius of the sphere (point)
            //is the epsilon for zero.
            float b = Vector3.Dot(m, ray.Direction);
            float c = Vector3.Dot(m, m) - Utilities.ZeroTolerance;

            if (c > 0f && b > 0f)
                return false;

            float discriminant = b * b - c;

            if (discriminant < 0f)
                return false;

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.Ray"/>.
        /// </summary>
        /// <param name="ray1">The first ray to test.</param>
        /// <param name="ray2">The second ray to test.</param>
        /// <param name="point">When the method completes, contains the point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <returns>Whether the two objects intersect.</returns>
        /// <remarks>
        /// This method performs a ray vs ray intersection test based on the following formula
        /// from Goldman.
        /// <code>s = det([o₂ − o₁, d₂, d₁ ⨯ d₂]) / ‖d₁ ⨯ d₂‖²</code>
        /// <code>t = det([o₂ − o₁, d₁, d₁ ⨯ d₂]) / ‖d₁ ⨯ d₂‖²</code>
        /// Where o₁ is the position of the first ray, o₂ is the position of the second ray,
        /// d₁ is the normalized direction of the first ray, d₂ is the normalized direction
        /// of the second ray, det denotes the determinant of a matrix, ⨯ denotes the cross
        /// product, [ ] denotes a matrix, and ‖ ‖ denotes the length or magnitude of a vector.
        /// </remarks>
        public static bool RayIntersectsRay(ref Ray ray1, ref Ray ray2, out Vector3 point)
        {
            //Source: Real-Time Rendering, Third Edition
            //Reference: Page 780
            
            Vector3 cross;

            Vector3.Cross(ref ray1.Direction, ref ray2.Direction, out cross);
            float denominator = cross.Length;
            
            //Lines are parallel.
            if (Math.Abs(denominator) < Utilities.ZeroTolerance)
            {
                //Lines are parallel and on top of each other.
                if (Math.Abs(ray2.Position.X - ray1.Position.X) < Utilities.ZeroTolerance &&
                    Math.Abs(ray2.Position.Y - ray1.Position.Y) < Utilities.ZeroTolerance &&
                    Math.Abs(ray2.Position.Z - ray1.Position.Z) < Utilities.ZeroTolerance)
                {
                    point = Vector3.Zero;
                    return true;
                }
            }

            denominator = denominator * denominator;

            //3x3 matrix for the first ray.
            float m11 = ray2.Position.X - ray1.Position.X;
            float m12 = ray2.Position.Y - ray1.Position.Y;
            float m13 = ray2.Position.Z - ray1.Position.Z;
            float m21 = ray2.Direction.X;
            float m22 = ray2.Direction.Y;
            float m23 = ray2.Direction.Z;
            float m31 = cross.X;
            float m32 = cross.Y;
            float m33 = cross.Z;

            //Determinant of first matrix.
            float dets =
                m11 * m22 * m33 +
                m12 * m23 * m31 +
                m13 * m21 * m32 -
                m11 * m23 * m32 -
                m12 * m21 * m33 -
                m13 * m22 * m31;

            //3x3 matrix for the second ray.
            m21 = ray1.Direction.X;
            m22 = ray1.Direction.Y;
            m23 = ray1.Direction.Z;

            //Determinant of the second matrix.
            float dett =
                m11 * m22 * m33 +
                m12 * m23 * m31 +
                m13 * m21 * m32 -
                m11 * m23 * m32 -
                m12 * m21 * m33 -
                m13 * m22 * m31;

            //t values of the point of intersection.
            float s = dets / denominator;
            float t = dett / denominator;

            //The points of intersection.
            Vector3 point1 = ray1.Position + (s * ray1.Direction);
            Vector3 point2 = ray2.Position + (t * ray2.Direction);

            //If the points are not equal, no intersection has occured.
            if (Math.Abs(point2.X - point1.X) > Utilities.ZeroTolerance ||
                Math.Abs(point2.Y - point1.Y) > Utilities.ZeroTolerance ||
                Math.Abs(point2.Z - point1.Z) > Utilities.ZeroTolerance)
            {
                point = Vector3.Zero;
                return false;
            }

            point = point1;
            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.Plane"/>.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="plane">The plane to test.</param>
        /// <param name="distance">When the method completes, contains the distance of the intersection,
        /// or 0 if there was no intersection.</param>
        /// <returns>Whether the two objects intersect.</returns>
        public static bool RayIntersectsPlane(ref Ray ray, ref Plane plane, out float distance)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 175

            float direction;
            Vector3.Dot(ref plane.Normal, ref ray.Direction, out direction);

            if (Math.Abs(direction) < Utilities.ZeroTolerance)
            {
                distance = 0f;
                return false;
            }

            float position;
            Vector3.Dot(ref plane.Normal, ref ray.Position, out position);
            distance = (-plane.D - position) / direction;

            if (distance < 0f)
            {
                if (distance < -Utilities.ZeroTolerance)
                {
                    distance = 0;
                    return false;
                }

                distance = 0f;
            }

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.Plane"/>.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="plane">The plane to test</param>
        /// <param name="point">When the method completes, contains the point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool RayIntersectsPlane(ref Ray ray, ref Plane plane, out Vector3 point)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 175

            float distance;
            if (!RayIntersectsPlane(ref ray, ref plane, out distance))
            {
                point = Vector3.Zero;
                return false;
            }

            point = ray.Position + (ray.Direction * distance);
            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a triangle.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="vertex1">The first vertex of the triangle to test.</param>
        /// <param name="vertex2">The second vertex of the triagnle to test.</param>
        /// <param name="vertex3">The third vertex of the triangle to test.</param>
        /// <param name="distance">When the method completes, contains the distance of the intersection,
        /// or 0 if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        /// <remarks>
        /// This method tests if the ray intersects either the front or back of the triangle.
        /// If the ray is parallel to the triangle's plane, no intersection is assumed to have
        /// happened. If the intersection of the ray and the triangle is behind the origin of
        /// the ray, no intersection is assumed to have happened. In both cases of assumptions,
        /// this method returns false.
        /// </remarks>
        public static bool RayIntersectsTriangle(ref Ray ray, ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3, out float distance)
        {
            //Source: Fast Minimum Storage Ray / Triangle Intersection
            //Reference: http://www.cs.virginia.edu/~gfx/Courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf

            //Compute vectors along two edges of the triangle.
            Vector3 edge1, edge2;

            //Edge 1
            edge1.X = vertex2.X - vertex1.X;
            edge1.Y = vertex2.Y - vertex1.Y;
            edge1.Z = vertex2.Z - vertex1.Z;

            //Edge2
            edge2.X = vertex3.X - vertex1.X;
            edge2.Y = vertex3.Y - vertex1.Y;
            edge2.Z = vertex3.Z - vertex1.Z;

            //Cross product of ray direction and edge2 - first part of determinant.
            Vector3 directioncrossedge2;
            directioncrossedge2.X = (ray.Direction.Y * edge2.Z) - (ray.Direction.Z * edge2.Y);
            directioncrossedge2.Y = (ray.Direction.Z * edge2.X) - (ray.Direction.X * edge2.Z);
            directioncrossedge2.Z = (ray.Direction.X * edge2.Y) - (ray.Direction.Y * edge2.X);

            //Compute the determinant.
            float determinant;
            //Dot product of edge1 and the first part of determinant.
            determinant = (edge1.X * directioncrossedge2.X) + (edge1.Y * directioncrossedge2.Y) + (edge1.Z * directioncrossedge2.Z);

            //If the ray is parallel to the triangle plane, there is no collision.
            //This also means that we are not culling, the ray may hit both the
            //back and the front of the triangle.
            if (determinant > -Utilities.ZeroTolerance && determinant < Utilities.ZeroTolerance)
            {
                distance = 0f;
                return false;
            }

            float inversedeterminant = 1.0f / determinant;

            //Calculate the U parameter of the intersection point.
            Vector3 distanceVector;
            distanceVector.X = ray.Position.X - vertex1.X;
            distanceVector.Y = ray.Position.Y - vertex1.Y;
            distanceVector.Z = ray.Position.Z - vertex1.Z;

            float triangleU;
            triangleU = (distanceVector.X * directioncrossedge2.X) + (distanceVector.Y * directioncrossedge2.Y) + (distanceVector.Z * directioncrossedge2.Z);
            triangleU *= inversedeterminant;

            //Make sure it is inside the triangle.
            if (triangleU < 0f || triangleU > 1f)
            {
                distance = 0f;
                return false;
            }

            //Calculate the V parameter of the intersection point.
            Vector3 distancecrossedge1;
            distancecrossedge1.X = (distanceVector.Y * edge1.Z) - (distanceVector.Z * edge1.Y);
            distancecrossedge1.Y = (distanceVector.Z * edge1.X) - (distanceVector.X * edge1.Z);
            distancecrossedge1.Z = (distanceVector.X * edge1.Y) - (distanceVector.Y * edge1.X);

            float triangleV;
            triangleV = ((ray.Direction.X * distancecrossedge1.X) + (ray.Direction.Y * distancecrossedge1.Y)) + (ray.Direction.Z * distancecrossedge1.Z);
            triangleV *= inversedeterminant;

            //Make sure it is inside the triangle.
            if (triangleV < 0f || triangleU + triangleV > 1f)
            {
                distance = 0f;
                return false;
            }

            //Compute the distance along the ray to the triangle.
            float raydistance;
            raydistance = (edge2.X * distancecrossedge1.X) + (edge2.Y * distancecrossedge1.Y) + (edge2.Z * distancecrossedge1.Z);
            raydistance *= inversedeterminant;

            //Is the triangle behind the ray origin?
            if (raydistance < 0f)
            {
                distance = 0f;
                return false;
            }

            distance = raydistance;
            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a triangle.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="vertex1">The first vertex of the triangle to test.</param>
        /// <param name="vertex2">The second vertex of the triagnle to test.</param>
        /// <param name="vertex3">The third vertex of the triangle to test.</param>
        /// <param name="point">When the method completes, contains the point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool RayIntersectsTriangle(ref Ray ray, ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3, out Vector3 point)
        {
            float distance;
            if (!RayIntersectsTriangle(ref ray, ref vertex1, ref vertex2, ref vertex3, out distance))
            {
                point = Vector3.Zero;
                return false;
            }

            point = ray.Position + (ray.Direction * distance);
            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.BoundingBox"/>.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="box">The box to test.</param>
        /// <param name="distance">When the method completes, contains the distance of the intersection,
        /// or 0 if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool RayIntersectsBox(ref Ray ray, ref BoundingBox box, out float distance)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 179

            distance = 0f;
            float tmax = float.MaxValue;

            if (Math.Abs(ray.Direction.X) < Utilities.ZeroTolerance)
            {
                if (ray.Position.X < box.Minimum.X || ray.Position.X > box.Maximum.X)
                {
                    distance = 0f;
                    return false;
                }
            }
            else
            {
                float inverse = 1.0f / ray.Direction.X;
                float t1 = (box.Minimum.X - ray.Position.X) * inverse;
                float t2 = (box.Maximum.X - ray.Position.X) * inverse;

                if (t1 > t2)
                {
                    float temp = t1;
                    t1 = t2;
                    t2 = temp;
                }

                distance = Math.Max(t1, distance);
                tmax = Math.Min(t2, tmax);

                if (distance > tmax)
                {
                    distance = 0f;
                    return false;
                }
            }

            if (Math.Abs(ray.Direction.Y) < Utilities.ZeroTolerance)
            {
                if (ray.Position.Y < box.Minimum.Y || ray.Position.Y > box.Maximum.Y)
                {
                    distance = 0f;
                    return false;
                }
            }
            else
            {
                float inverse = 1.0f / ray.Direction.Y;
                float t1 = (box.Minimum.Y - ray.Position.Y) * inverse;
                float t2 = (box.Maximum.Y - ray.Position.Y) * inverse;

                if (t1 > t2)
                {
                    float temp = t1;
                    t1 = t2;
                    t2 = temp;
                }

                distance = Math.Max(t1, distance);
                tmax = Math.Min(t2, tmax);

                if (distance > tmax)
                {
                    distance = 0f;
                    return false;
                }
            }

            if (Math.Abs(ray.Direction.Z) < Utilities.ZeroTolerance)
            {
                if (ray.Position.Z < box.Minimum.Z || ray.Position.Z > box.Maximum.Z)
                {
                    distance = 0f;
                    return false;
                }
            }
            else
            {
                float inverse = 1.0f / ray.Direction.Z;
                float t1 = (box.Minimum.Z - ray.Position.Z) * inverse;
                float t2 = (box.Maximum.Z - ray.Position.Z) * inverse;

                if (t1 > t2)
                {
                    float temp = t1;
                    t1 = t2;
                    t2 = temp;
                }

                distance = Math.Max(t1, distance);
                tmax = Math.Min(t2, tmax);

                if (distance > tmax)
                {
                    distance = 0f;
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.Plane"/>.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="box">The box to test.</param>
        /// <param name="point">When the method completes, contains the point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool RayIntersectsBox(ref Ray ray, ref BoundingBox box, out Vector3 point)
        {
            float distance;
            if (!RayIntersectsBox(ref ray, ref box, out distance))
            {
                point = Vector3.Zero;
                return false;
            }

            point = ray.Position + (ray.Direction * distance);
            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="distance">When the method completes, contains the distance of the intersection,
        /// or 0 if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        /// <remarks>
        /// <para>
        /// This method uses the following math to compute the intersection:
        /// ‖x − c‖² = r²           Equation of sphere
        /// x = s + td              Equation of ray
        /// 
        /// Solve for t
        /// ‖s + td − c‖² = r²      Substitute equation of ray into equation of sphere
        /// v ≝ s − c
        /// ‖v + td‖² = r²
        /// v² + 2v⋅td + t²d² = r²
        /// d²t² + (2v⋅d)t + (v² − r²) = 0
        /// t² + (2v⋅d)t + (v² − r²) = 0    If d is a normalized vector
        /// 
        /// Quadratic equation gives us
        /// t = (−(2v⋅d) ± √((2v⋅d)² − 4(v² − r)²)) / 2
        /// t = −(v⋅d) ± √((v⋅d)² − (v² − r)²)
        /// </para>
        /// <para>
        /// Entrance of intersection is given by the smaller t
        /// t = −(v⋅d) − √((v⋅d)² − (v² − r)²)
        /// 
        /// Exit of intersection is given by the larger t
        /// t = −(v⋅d) + √((v⋅d)² − (v² − r)²)
        /// 
        /// If the smaller t value is &lt; 0 than the ray started inside of the sphere.
        /// 
        /// If the descriminant (v⋅d)² − (v² − r)² is &lt; 0 than no intersection occured. If the
        /// descriminant (v⋅d)² − (v² − r)² is = 0 than the ray is tangential to the sphere. If
        /// the descriminant (v⋅d)² − (v² − r)² is > 0 than the ray passes through the sphere.
        /// </para>
        /// </remarks>
        public static bool RayIntersectsSphere(ref Ray ray, ref BoundingSphere sphere, out float distance)
        {
            Vector3 v;
            Vector3.Subtract(ref ray.Position, ref sphere.Center, out v);

            float b = Vector3.Dot(v, ray.Direction);
            float c = Vector3.Dot(v, v) - (sphere.Radius * sphere.Radius);

            if (c > 0f && b > 0f)
            {
                distance = 0f;
                return false;
            }

            float discriminant = b * b - c;

            if (discriminant < 0f)
            {
                distance = 0f;
                return false;
            }

            distance = -b - (float)Math.Sqrt(discriminant);

            if (distance < 0f)
                distance = 0f;

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.BoundingSphere"/>. 
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="point">When the method completes, contains the point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        /// <remarks>
        /// <para>
        /// This method uses the following math to compute the intersection:
        /// ‖x − c‖² = r²           Equation of sphere
        /// x = s + td              Equation of ray
        /// 
        /// Solve for t
        /// ‖s + td − c‖² = r²      Substitute equation of ray into equation of sphere
        /// v ≝ s − c
        /// ‖v + td‖² = r²
        /// v² + 2v⋅td + t²d² = r²
        /// d²t² + (2v⋅d)t + (v² − r²) = 0
        /// t² + (2v⋅d)t + (v² − r²) = 0    If d is a normalized vector
        /// 
        /// Quadratic equation gives us
        /// t = (−(2v⋅d) ± √((2v⋅d)² − 4(v² − r)²)) / 2
        /// t = −(v⋅d) ± √((v⋅d)² − (v² − r)²)
        /// </para>
        /// <para>
        /// Entrance of intersection is given by the smaller t
        /// t = −(v⋅d) − √((v⋅d)² − (v² − r)²)
        /// 
        /// Exit of intersection is given by the larger t
        /// t = −(v⋅d) + √((v⋅d)² − (v² − r)²)
        /// 
        /// If the smaller t value is &lt; 0 than the ray started inside of the sphere.
        /// 
        /// If the descriminant (v⋅d)² − (v² − r)² is &lt; 0 than no intersection occured. If the
        /// descriminant (v⋅d)² − (v² − r)² is = 0 than the ray is tangential to the sphere. If
        /// the descriminant (v⋅d)² − (v² − r)² is > 0 than the ray passes through the sphere.
        /// </para>
        /// </remarks>
        public static bool RayIntersectsSphere(ref Ray ray, ref BoundingSphere sphere, out Vector3 point)
        {
            float distance;
            if (!RayIntersectsSphere(ref ray, ref sphere, out distance))
            {
                point = Vector3.Zero;
                return false;
            }

            point = ray.Position + (ray.Direction * distance);
            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.BoundingSphere"/>. 
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="point">When the method completes, contains the point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <param name="normal">When the method completes, contains the normal vector on the
        /// sphere at the point of intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        /// <remarks>
        /// <para>
        /// This method uses the following math to compute the intersection:
        /// ‖x − c‖² = r²           Equation of sphere
        /// x = s + td              Equation of ray
        /// 
        /// Solve for t
        /// ‖s + td − c‖² = r²      Substitute equation of ray into equation of sphere
        /// v ≝ s − c
        /// ‖v + td‖² = r²
        /// v² + 2v⋅td + t²d² = r²
        /// d²t² + (2v⋅d)t + (v² − r²) = 0
        /// t² + (2v⋅d)t + (v² − r²) = 0    If d is a normalized vector
        /// 
        /// Quadratic equation gives us
        /// t = (−(2v⋅d) ± √((2v⋅d)² − 4(v² − r)²)) / 2
        /// t = −(v⋅d) ± √((v⋅d)² − (v² − r)²)
        /// </para>
        /// <para>
        /// Entrance of intersection is given by the smaller t
        /// t = −(v⋅d) − √((v⋅d)² − (v² − r)²)
        /// 
        /// Exit of intersection is given by the larger t
        /// t = −(v⋅d) + √((v⋅d)² − (v² − r)²)
        /// 
        /// If the smaller t value is &lt; 0 than the ray started inside of the sphere.
        /// 
        /// If the descriminant (v⋅d)² − (v² − r)² is &lt; 0 than no intersection occured. If the
        /// descriminant (v⋅d)² − (v² − r)² is = 0 than the ray is tangential to the sphere. If
        /// the descriminant (v⋅d)² − (v² − r)² is > 0 than the ray passes through the sphere.
        /// </para>
        /// </remarks>
        public static bool RayIntersectsSphere(ref Ray ray, ref BoundingSphere sphere, out Vector3 point, out Vector3 normal)
        {
            float distance;
            if (!RayIntersectsSphere(ref ray, ref sphere, out distance))
            {
                point = Vector3.Zero;
                normal = Vector3.Zero;
                return false;
            }

            point = ray.Position + (ray.Direction * distance);
            normal = point - sphere.Center;
            normal.Normalize();
            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Ray"/> and a <see cref="SlimMath.BoundingSphere"/>. 
        /// </summary>
        /// <param name="ray">The ray to test.</param>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="entrancePoint">When the method completes, contains the closest point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <param name="entranceNormal">When the method completes, contains the normal vector on the
        /// sphere at the point of closest intersection.</param>
        /// <param name="exitPoint">When the method completes, contains the farthest point of intersection,
        /// or <see cref="SlimMath.Vector3.Zero"/> if there was no intersection.</param>
        /// <param name="exitNormal">Whent he method completes, contains the normal vector on the
        /// sphere at the point of farthest intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        /// <remarks>
        /// <para>
        /// This method uses the following math to compute the intersection:
        /// ‖x − c‖² = r²           Equation of sphere
        /// x = s + td              Equation of ray
        /// 
        /// Solve for t
        /// ‖s + td − c‖² = r²      Substitute equation of ray into equation of sphere
        /// v ≝ s − c
        /// ‖v + td‖² = r²
        /// v² + 2v⋅td + t²d² = r²
        /// d²t² + (2v⋅d)t + (v² − r²) = 0
        /// t² + (2v⋅d)t + (v² − r²) = 0    If d is a normalized vector
        /// 
        /// Quadratic equation gives us
        /// t = (−(2v⋅d) ± √((2v⋅d)² − 4(v² − r)²)) / 2
        /// t = −(v⋅d) ± √((v⋅d)² − (v² − r)²)
        /// </para>
        /// <para>
        /// Entrance of intersection is given by the smaller t
        /// t = −(v⋅d) − √((v⋅d)² − (v² − r)²)
        /// 
        /// Exit of intersection is given by the larger t
        /// t = −(v⋅d) + √((v⋅d)² − (v² − r)²)
        /// 
        /// If the smaller t value is &lt; 0 than the ray started inside of the sphere.
        /// 
        /// If the descriminant (v⋅d)² − (v² − r)² is &lt; 0 than no intersection occured. If the
        /// descriminant (v⋅d)² − (v² − r)² is = 0 than the ray is tangential to the sphere. If
        /// the descriminant (v⋅d)² − (v² − r)² is > 0 than the ray passes through the sphere.
        /// </para>
        /// </remarks>
        public static bool RayIntersectsSphere(ref Ray ray, ref BoundingSphere sphere, out Vector3 entrancePoint, out Vector3 entranceNormal, out Vector3 exitPoint, out Vector3 exitNormal)
        {
            Vector3 v;
            Vector3.Subtract(ref ray.Position, ref sphere.Center, out v);

            float b = Vector3.Dot(v, ray.Direction);
            float c = Vector3.Dot(v, v) - (sphere.Radius * sphere.Radius);

            if (c > 0f && b > 0f)
            {
                entrancePoint = Vector3.Zero;
                entranceNormal = Vector3.Zero;
                exitPoint = Vector3.Zero;
                exitNormal = Vector3.Zero;
                return false;
            }

            float discriminant = b * b - c;

            if (discriminant < 0f)
            {
                entrancePoint = Vector3.Zero;
                entranceNormal = Vector3.Zero;
                exitPoint = Vector3.Zero;
                exitNormal = Vector3.Zero;
                return false;
            }

            float discriminantSquared = (float)Math.Sqrt(discriminant);
            float distance1 = -b - discriminantSquared;
            float distance2 = -b + discriminantSquared;

            if (distance1 < 0f)
            {
                distance1 = 0f;
                entrancePoint = Vector3.Zero;
                entranceNormal = Vector3.Zero;
            }
            else
            {
                entrancePoint = ray.Position + (ray.Direction * distance1);
                entranceNormal = entrancePoint - sphere.Center;
                entranceNormal.Normalize();
            }

            exitPoint = ray.Position + (ray.Direction * distance2);
            exitNormal = exitPoint - sphere.Center;
            exitNormal.Normalize();

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Plane"/> and a point.
        /// </summary>
        /// <param name="plane">The plane to test.</param>
        /// <param name="point">The point to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static PlaneIntersectionType PlaneIntersectsPoint(ref Plane plane, ref Vector3 point)
        {
            float distance;
            Vector3.Dot(ref plane.Normal, ref point, out distance);
            distance += plane.D;

            if (distance > 0f)
                return PlaneIntersectionType.Front;

            if (distance < 0f)
                return PlaneIntersectionType.Back;

            return PlaneIntersectionType.Intersecting;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Plane"/> and a <see cref="SlimMath.Plane"/>.
        /// </summary>
        /// <param name="plane1">The first plane to test.</param>
        /// <param name="plane2">The second plane to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool PlaneIntersectsPlane(ref Plane plane1, ref Plane plane2)
        {
            Vector3 direction;
            Vector3.Cross(ref plane1.Normal, ref plane2.Normal, out direction);

            //If direction is the zero vector, the planes are parallel and possibly
            //coincident. It is not an intersection. The dot product will tell us.
            float denominator;
            Vector3.Dot(ref direction, ref direction, out denominator);

            if (Math.Abs(denominator) < Utilities.ZeroTolerance)
                return false;

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Plane"/> and a <see cref="SlimMath.Plane"/>.
        /// </summary>
        /// <param name="plane1">The first plane to test.</param>
        /// <param name="plane2">The second plane to test.</param>
        /// <param name="line">When the method completes, contains the line of intersection
        /// as a <see cref="SlimMath.Ray"/>, or a zero ray if there was no intersection.</param>
        /// <returns>Whether the two objects intersected.</returns>
        /// <remarks>
        /// Although a ray is set to have an origin, the ray returned by this method is really
        /// a line in three dimensions which has no real origin. The ray is considered valid when
        /// both the positive direction is used and when the negative direction is used.
        /// </remarks>
        public static bool PlaneIntersectsPlane(ref Plane plane1, ref Plane plane2, out Ray line)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 207

            Vector3 direction;
            Vector3.Cross(ref plane1.Normal, ref plane2.Normal, out direction);

            //If direction is the zero vector, the planes are parallel and possibly
            //coincident. It is not an intersection. The dot product will tell us.
            float denominator;
            Vector3.Dot(ref direction, ref direction, out denominator);

            //We assume the planes are normalized, therefore the denominator
            //only serves as a parallel and coincident check. Otherwise we need
            //to deivide the point by the denominator.
            if (Math.Abs(denominator) < Utilities.ZeroTolerance)
            {
                line = new Ray();
                return false;
            }

            Vector3 point;
            Vector3 temp = plane1.D * plane2.Normal - plane2.D * plane1.Normal;
            Vector3.Cross(ref temp, ref direction, out point);

            line.Position = point;
            line.Direction = direction;
            line.Direction.Normalize();

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Plane"/> and a triangle.
        /// </summary>
        /// <param name="plane">The plane to test.</param>
        /// <param name="vertex1">The first vertex of the triangle to test.</param>
        /// <param name="vertex2">The second vertex of the triagnle to test.</param>
        /// <param name="vertex3">The third vertex of the triangle to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static PlaneIntersectionType PlaneIntersectsTriangle(ref Plane plane, ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 207

            PlaneIntersectionType test1 = PlaneIntersectsPoint(ref plane, ref vertex1);
            PlaneIntersectionType test2 = PlaneIntersectsPoint(ref plane, ref vertex2);
            PlaneIntersectionType test3 = PlaneIntersectsPoint(ref plane, ref vertex3);

            if (test1 == PlaneIntersectionType.Front && test2 == PlaneIntersectionType.Front && test3 == PlaneIntersectionType.Front)
                return PlaneIntersectionType.Front;

            if (test1 == PlaneIntersectionType.Back && test2 == PlaneIntersectionType.Back && test3 == PlaneIntersectionType.Back)
                return PlaneIntersectionType.Back;

            return PlaneIntersectionType.Intersecting;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Plane"/> and a <see cref="SlimMath.BoundingBox"/>.
        /// </summary>
        /// <param name="plane">The plane to test.</param>
        /// <param name="box">The box to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static PlaneIntersectionType PlaneIntersectsBox(ref Plane plane, ref BoundingBox box)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 161

            Vector3 min;
            Vector3 max;

            max.X = (plane.Normal.X >= 0.0f) ? box.Minimum.X : box.Maximum.X;
            max.Y = (plane.Normal.Y >= 0.0f) ? box.Minimum.Y : box.Maximum.Y;
            max.Z = (plane.Normal.Z >= 0.0f) ? box.Minimum.Z : box.Maximum.Z;
            min.X = (plane.Normal.X >= 0.0f) ? box.Maximum.X : box.Minimum.X;
            min.Y = (plane.Normal.Y >= 0.0f) ? box.Maximum.Y : box.Minimum.Y;
            min.Z = (plane.Normal.Z >= 0.0f) ? box.Maximum.Z : box.Minimum.Z;

            float distance;
            Vector3.Dot(ref plane.Normal, ref max, out distance);

            if (distance + plane.D > 0.0f)
                return PlaneIntersectionType.Front;

            distance = Vector3.Dot(plane.Normal, min);

            if (distance + plane.D < 0.0f)
                return PlaneIntersectionType.Back;

            return PlaneIntersectionType.Intersecting;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.Plane"/> and a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="plane">The plane to test.</param>
        /// <param name="sphere">The sphere to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static PlaneIntersectionType PlaneIntersectsSphere(ref Plane plane, ref BoundingSphere sphere)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 160

            float distance;
            Vector3.Dot(ref plane.Normal, ref sphere.Center, out distance);
            distance += plane.D;

            if (distance > sphere.Radius)
                return PlaneIntersectionType.Front;

            if (distance < -sphere.Radius)
                return PlaneIntersectionType.Back;

            return PlaneIntersectionType.Intersecting;
        }

        //THIS IMPLEMENTATION IS INCOMPLETE!
        //NEEDS TO BE COMPLETED SOON
        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.BoundingBox"/> and a triangle.
        /// </summary>
        /// <param name="box">The box to test.</param>
        /// <param name="vertex1">The first vertex of the triangle to test.</param>
        /// <param name="vertex2">The second vertex of the triagnle to test.</param>
        /// <param name="vertex3">The third vertex of the triangle to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool BoxIntersectsTriangle(ref BoundingBox box, ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 169

            float p0, p1, p2, r;

            //Compute box center and extents (if not already given in that format)
            Vector3 center = (box.Minimum + box.Maximum) * 0.5f;
            float e0 = (box.Maximum.X - box.Minimum.X) * 0.5f;
            float e1 = (box.Maximum.Y - box.Minimum.Y) * 0.5f;
            float e2 = (box.Maximum.Z - box.Minimum.Z) * 0.5f;

            //Translate triangle as conceptually moving AABB to origin
            vertex1 = vertex1 - center;
            vertex2 = vertex2 - center;
            vertex3 = vertex3 - center;

            //Compute edge vectors for triangle
            Vector3 f0 = vertex2 - vertex1;
            Vector3 f1 = vertex3 - vertex2;
            Vector3 f2 = vertex1 - vertex3;

            //Test axes a00..a22 (category 3)
            //Test axis a00
            p0 = vertex1.Z * vertex2.Y - vertex1.Y * vertex2.Z;
            p2 = vertex3.Z * (vertex2.Y - vertex1.Y) - vertex3.Z * (vertex2.Z - vertex1.Z);
            r = e1 * Math.Abs(f0.Z) + e2 * Math.Abs(f0.Y);

            if (Math.Max(-Math.Max(p0, p2), Math.Min(p0, p2)) > r)
                return false; //Axis is a separating axis

            //Repeat similar tests for remaining axes a01..a22
            //...

            //Test the three axes corresponding to the face normals of AABB b (category 1).
            //Exit if...
            // ... [-e0, e0] and [Math.Min(vertex1.X,vertex2.X,vertex3.X), Math.Max(vertex1.X,vertex2.X,vertex3.X)] do not overlap
            if (Math.Max(Math.Max(vertex1.X, vertex2.X), vertex3.X) < -e0 || Math.Min(Math.Min(vertex1.X, vertex2.X), vertex3.X) > e0)
                return false;

            // ... [-e1, e1] and [Math.Min(vertex1.Y,vertex2.Y,vertex3.Y), Math.Max(vertex1.Y,vertex2.Y,vertex3.Y)] do not overlap
            if (Math.Max(Math.Max(vertex1.Y, vertex2.Y), vertex3.Y) < -e1 || Math.Min(Math.Min(vertex1.Y, vertex2.Y), vertex3.Y) > e1)
                return false;

            // ... [-e2, e2] and [Math.Min(vertex1.Z,vertex2.Z,vertex3.Z), Math.Max(vertex1.Z,vertex2.Z,vertex3.Z)] do not overlap
            if (Math.Max(Math.Max(vertex1.Z, vertex2.Z), vertex3.Z) < -e2 || Math.Min(Math.Min(vertex1.Z, vertex2.Z), vertex3.Z) > e2)
                return false;

            //Test separating axis corresponding to triangle face normal (category 2)
            Plane plane;
            plane.Normal = Vector3.Cross(f0, f1);
            plane.D = Vector3.Dot(plane.Normal, vertex1);

            return PlaneIntersectsBox(ref plane, ref box) == PlaneIntersectionType.Intersecting;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.BoundingBox"/> and a <see cref="SlimMath.BoundingBox"/>.
        /// </summary>
        /// <param name="box1">The first box to test.</param>
        /// <param name="box2">The second box to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool BoxIntersectsBox(ref BoundingBox box1, ref BoundingBox box2)
        {
            if (box1.Minimum.X > box2.Maximum.X || box2.Minimum.X > box1.Maximum.X)
                return false;

            if (box1.Minimum.Y > box2.Maximum.Y || box2.Minimum.Y > box1.Maximum.Y)
                return false;

            if (box1.Minimum.Z > box2.Maximum.Z || box2.Minimum.Z > box1.Maximum.Z)
                return false;

            return true;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.BoundingBox"/> and a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="box">The box to test.</param>
        /// <param name="sphere">The sphere to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool BoxIntersectsSphere(ref BoundingBox box, ref BoundingSphere sphere)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 166

            Vector3 vector;
            Vector3.Clamp(ref sphere.Center, ref box.Minimum, ref box.Maximum, out vector);
            float distance = Vector3.DistanceSquared(sphere.Center, vector);

            return distance <= sphere.Radius * sphere.Radius;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.BoundingSphere"/> and a triangle.
        /// </summary>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="vertex1">The first vertex of the triangle to test.</param>
        /// <param name="vertex2">The second vertex of the triagnle to test.</param>
        /// <param name="vertex3">The third vertex of the triangle to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool SphereIntersectsTriangle(ref BoundingSphere sphere, ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3)
        {
            //Source: Real-Time Collision Detection by Christer Ericson
            //Reference: Page 167

            Vector3 point;
            ClosestPointOnTriangleToPoint(ref sphere.Center, ref vertex1, ref vertex2, ref vertex3, out point);
            Vector3 v = point - sphere.Center;

            float dot;
            Vector3.Dot(ref v, ref v, out dot);

            return dot <= sphere.Radius * sphere.Radius;
        }

        /// <summary>
        /// Determines whether there is an intersection between a <see cref="SlimMath.BoundingSphere"/> and a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="sphere1">First sphere to test.</param>
        /// <param name="sphere2">Second sphere to test.</param>
        /// <returns>Whether the two objects intersected.</returns>
        public static bool SphereIntersectsSphere(ref BoundingSphere sphere1, ref BoundingSphere sphere2)
        {
            float radiisum = sphere1.Radius + sphere2.Radius;
            return Vector3.DistanceSquared(sphere1.Center, sphere2.Center) <= radiisum * radiisum;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingBox"/> contains a point.
        /// </summary>
        /// <param name="box">The box to test.</param>
        /// <param name="point">The point to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType BoxContainsPoint(ref BoundingBox box, ref Vector3 point)
        {
            if (box.Minimum.X <= point.X && box.Maximum.X >= point.X &&
                box.Minimum.Y <= point.Y && box.Maximum.Y >= point.Y &&
                box.Minimum.Z <= point.Z && box.Maximum.Z >= point.Z)
            {
                return ContainmentType.Contains;
            }

            return ContainmentType.Disjoint;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingBox"/> contains a triangle.
        /// </summary>
        /// <param name="box">The box to test.</param>
        /// <param name="vertex1">The first vertex of the triangle to test.</param>
        /// <param name="vertex2">The second vertex of the triagnle to test.</param>
        /// <param name="vertex3">The third vertex of the triangle to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType BoxContainsTriangle(ref BoundingBox box, ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3)
        {
            ContainmentType test1 = BoxContainsPoint(ref box, ref vertex1);
            ContainmentType test2 = BoxContainsPoint(ref box, ref vertex2);
            ContainmentType test3 = BoxContainsPoint(ref box, ref vertex3);

            if (test1 == ContainmentType.Contains && test2 == ContainmentType.Contains && test3 == ContainmentType.Contains)
                return ContainmentType.Contains;

            if (BoxIntersectsTriangle(ref box, ref vertex1, ref vertex2, ref vertex3))
                return ContainmentType.Intersects;

            return ContainmentType.Disjoint;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingBox"/> contains a <see cref="SlimMath.BoundingBox"/>.
        /// </summary>
        /// <param name="box1">The first box to test.</param>
        /// <param name="box2">The second box to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType BoxContainsBox(ref BoundingBox box1, ref BoundingBox box2)
        {
            if (box1.Maximum.X < box2.Minimum.X || box1.Minimum.X > box2.Maximum.X)
                return ContainmentType.Disjoint;

            if (box1.Maximum.Y < box2.Minimum.Y || box1.Minimum.Y > box2.Maximum.Y)
                return ContainmentType.Disjoint;

            if (box1.Maximum.Z < box2.Minimum.Z || box1.Minimum.Z > box2.Maximum.Z)
                return ContainmentType.Disjoint;

            if (box1.Minimum.X <= box2.Minimum.X && (box2.Maximum.X <= box1.Maximum.X &&
                box1.Minimum.Y <= box2.Minimum.Y && box2.Maximum.Y <= box1.Maximum.Y) &&
                box1.Minimum.Z <= box2.Minimum.Z && box2.Maximum.Z <= box1.Maximum.Z)
            {
                return ContainmentType.Contains;
            }

            return ContainmentType.Intersects;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingBox"/> contains a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="box">The box to test.</param>
        /// <param name="sphere">The sphere to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType BoxContainsSphere(ref BoundingBox box, ref BoundingSphere sphere)
        {
            Vector3 vector;
            Vector3.Clamp(ref sphere.Center, ref box.Minimum, ref box.Maximum, out vector);
            float distance = Vector3.DistanceSquared(sphere.Center, vector);

            if (distance > sphere.Radius * sphere.Radius)
                return ContainmentType.Disjoint;

            if ((((box.Minimum.X + sphere.Radius <= sphere.Center.X) && (sphere.Center.X <= box.Maximum.X - sphere.Radius)) && ((box.Maximum.X - box.Minimum.X > sphere.Radius) &&
                (box.Minimum.Y + sphere.Radius <= sphere.Center.Y))) && (((sphere.Center.Y <= box.Maximum.Y - sphere.Radius) && (box.Maximum.Y - box.Minimum.Y > sphere.Radius)) &&
                (((box.Minimum.Z + sphere.Radius <= sphere.Center.Z) && (sphere.Center.Z <= box.Maximum.Z - sphere.Radius)) && (box.Maximum.X - box.Minimum.X > sphere.Radius))))
            {
                return ContainmentType.Contains;
            }

            return ContainmentType.Intersects;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingSphere"/> contains a point.
        /// </summary>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="point">The point to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType SphereContainsPoint(ref BoundingSphere sphere, ref Vector3 point)
        {
            if (Vector3.DistanceSquared(point, sphere.Center) <= sphere.Radius * sphere.Radius)
                return ContainmentType.Contains;

            return ContainmentType.Disjoint;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingSphere"/> contains a triangle.
        /// </summary>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="vertex1">The first vertex of the triangle to test.</param>
        /// <param name="vertex2">The second vertex of the triagnle to test.</param>
        /// <param name="vertex3">The third vertex of the triangle to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType SphereContainsTriangle(ref BoundingSphere sphere, ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3)
        {
            //Source: Jorgy343
            //Reference: None

            ContainmentType test1 = SphereContainsPoint(ref sphere, ref vertex1);
            ContainmentType test2 = SphereContainsPoint(ref sphere, ref vertex2);
            ContainmentType test3 = SphereContainsPoint(ref sphere, ref vertex3);

            if (test1 == ContainmentType.Contains && test2 == ContainmentType.Contains && test3 == ContainmentType.Contains)
                return ContainmentType.Contains;

            if (SphereIntersectsTriangle(ref sphere, ref vertex1, ref vertex2, ref vertex3))
                return ContainmentType.Intersects;

            return ContainmentType.Disjoint;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingSphere"/> contains a <see cref="SlimMath.BoundingBox"/>.
        /// </summary>
        /// <param name="sphere">The sphere to test.</param>
        /// <param name="box">The box to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType SphereContainsBox(ref BoundingSphere sphere, ref BoundingBox box)
        {
            Vector3 vector;

            if (!BoxIntersectsSphere(ref box, ref sphere))
                return ContainmentType.Disjoint;

            float radiussquared = sphere.Radius * sphere.Radius;
            vector.X = sphere.Center.X - box.Minimum.X;
            vector.Y = sphere.Center.Y - box.Maximum.Y;
            vector.Z = sphere.Center.Z - box.Maximum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            vector.X = sphere.Center.X - box.Maximum.X;
            vector.Y = sphere.Center.Y - box.Maximum.Y;
            vector.Z = sphere.Center.Z - box.Maximum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            vector.X = sphere.Center.X - box.Maximum.X;
            vector.Y = sphere.Center.Y - box.Minimum.Y;
            vector.Z = sphere.Center.Z - box.Maximum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            vector.X = sphere.Center.X - box.Minimum.X;
            vector.Y = sphere.Center.Y - box.Minimum.Y;
            vector.Z = sphere.Center.Z - box.Maximum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            vector.X = sphere.Center.X - box.Minimum.X;
            vector.Y = sphere.Center.Y - box.Maximum.Y;
            vector.Z = sphere.Center.Z - box.Minimum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            vector.X = sphere.Center.X - box.Maximum.X;
            vector.Y = sphere.Center.Y - box.Maximum.Y;
            vector.Z = sphere.Center.Z - box.Minimum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            vector.X = sphere.Center.X - box.Maximum.X;
            vector.Y = sphere.Center.Y - box.Minimum.Y;
            vector.Z = sphere.Center.Z - box.Minimum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            vector.X = sphere.Center.X - box.Minimum.X;
            vector.Y = sphere.Center.Y - box.Minimum.Y;
            vector.Z = sphere.Center.Z - box.Minimum.Z;

            if (vector.LengthSquared > radiussquared)
                return ContainmentType.Intersects;

            return ContainmentType.Contains;
        }

        /// <summary>
        /// Determines whether a <see cref="SlimMath.BoundingSphere"/> contains a <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="sphere1">The first sphere to test.</param>
        /// <param name="sphere2">The second sphere to test.</param>
        /// <returns>The type of containment the two objects have.</returns>
        public static ContainmentType SphereContainsSphere(ref BoundingSphere sphere1, ref BoundingSphere sphere2)
        {
            float distance = Vector3.Distance(sphere1.Center, sphere2.Center);

            if (sphere1.Radius + sphere2.Radius < distance)
                return ContainmentType.Disjoint;

            if (sphere1.Radius - sphere2.Radius < distance)
                return ContainmentType.Intersects;

            return ContainmentType.Contains;
        }

        /// <summary>
        /// Generates a supporting point from a specific triangle.
        /// </summary>
        /// <param name="vertex1">The first vertex of the triangle.</param>
        /// <param name="vertex2">The second vertex of the triangle.</param>
        /// <param name="vertex3">The third vertex of the triangle</param>
        /// <param name="direction">The direction for which to build the supporting point.</param>
        /// <param name="result">When the method completes, contains the supporting point.</param>
        public static void SupportPoint(ref Vector3 vertex1, ref Vector3 vertex2, ref Vector3 vertex3, ref Vector3 direction, out Vector3 result)
        {
            float dot1 = Vector3.Dot(vertex1, direction);
            float dot2 = Vector3.Dot(vertex2, direction);
            float dot3 = Vector3.Dot(vertex3, direction);

            if (dot1 > dot2 && dot1 > dot3)
                result = vertex1;
            else if (dot2 > dot1 && dot2 > dot3)
                result = vertex2;
            else
                result = vertex3;
        }

        /// <summary>
        /// Generates a supporting point from a specific <see cref="SlimMath.BoundingBox"/>.
        /// </summary>
        /// <param name="box">The box to generate the supporting point for.</param>
        /// <param name="direction">The direction for which to build the supporting point.</param>
        /// <param name="result">When the method completes, contains the supporting point.</param>
        public static void SupportPoint(ref BoundingBox box, ref Vector3 direction, out Vector3 result)
        {
            result.X = direction.X >= 0.0f ? box.Maximum.X : box.Minimum.X;
            result.Y = direction.Y >= 0.0f ? box.Maximum.Y : box.Minimum.Y;
            result.Z = direction.Z >= 0.0f ? box.Maximum.Z : box.Minimum.Z;
        }

        /// <summary>
        /// Generates a supporting point from a specific <see cref="SlimMath.BoundingSphere"/>.
        /// </summary>
        /// <param name="sphere">The sphere to generate the supporting point for.</param>
        /// <param name="direction">The direction for which to build the supporting point.</param>
        /// <param name="result">When the method completes, contains the supporting point.</param>
        public static void SupportPoint(ref BoundingSphere sphere, ref Vector3 direction, out Vector3 result)
        {
            result = (sphere.Radius / direction.Length) * direction + sphere.Center;
        }

        /// <summary>
        /// Generates a supporting point from a polyhedra.
        /// </summary>
        /// <param name="points">The points that make up the polyhedra.</param>
        /// <param name="direction">The direction for which to build the supporting point.</param>
        /// <param name="result">When the method completes, contains the supporting point.</param>
        public static void SupportPoint(IEnumerable<Vector3> points, ref Vector3 direction, out Vector3 result)
        {
            float maxdot = float.MinValue;
            result = Vector3.Zero;

            foreach (Vector3 point in points)
            {
                float tempdot = Vector3.Dot(direction, point);

                if (tempdot > maxdot)
                {
                    maxdot = tempdot;
                    result = point;
                }
            }
        }
    }
}
