// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace SlimDX.Direct2D1
{
    public partial interface GeometrySink
    {
        /// <summary>	
        /// Creates a line segment between the current point and the specified end point and adds it to the geometry sink. 	
        /// </summary>	
        /// <param name="point">The end point of the line to draw.</param>
        /// <unmanaged>void AddLine([None] D2D1_POINT_2F point)</unmanaged>
        void AddLine(System.Drawing.PointF point);


        /// <summary>	
        ///  Creates  a cubic Bezier curve between the current point and the specified endpoint.	
        /// </summary>	
        /// <param name="bezier">A structure that describes the control points and endpoint of the Bezier curve to add. </param>
        /// <unmanaged>void AddBezier([In] const D2D1_BEZIER_SEGMENT* bezier)</unmanaged>
        void AddBezier(SlimDX.Direct2D1.BezierSegment bezier);


        /// <summary>	
        /// Creates  a quadratic Bezier curve between the current point and the specified endpoint.	
        /// </summary>	
        /// <param name="bezier">A structure that describes the control point and the endpoint of the quadratic Bezier curve to add.</param>
        /// <unmanaged>void AddQuadraticBezier([In] const D2D1_QUADRATIC_BEZIER_SEGMENT* bezier)</unmanaged>
        void AddQuadraticBezier(SlimDX.Direct2D1.QuadraticBezierSegment bezier);


        /// <summary>	
        /// Adds a sequence of quadratic Bezier segments as an array in a single call.	
        /// </summary>	
        /// <param name="beziers">An array of a sequence of quadratic Bezier segments.</param>
        /// <unmanaged>void AddQuadraticBeziers([In, Buffer] const D2D1_QUADRATIC_BEZIER_SEGMENT* beziers,[None] UINT beziersCount)</unmanaged>
        void AddQuadraticBeziers(SlimDX.Direct2D1.QuadraticBezierSegment[] beziers);

        /// <summary>	
        /// Adds a single arc to the path geometry.	
        /// </summary>	
        /// <param name="arc">The arc segment to add to the figure.</param>
        /// <unmanaged>void AddArc([In] const D2D1_ARC_SEGMENT* arc)</unmanaged>
        void AddArc(ref SlimDX.Direct2D1.ArcSegment arc);

        /// <summary>	
        /// Adds a single arc to the path geometry.	
        /// </summary>	
        /// <param name="arc">The arc segment to add to the figure.</param>
        /// <unmanaged>void AddArc([In] const D2D1_ARC_SEGMENT* arc)</unmanaged>
        void AddArc(SlimDX.Direct2D1.ArcSegment arc);
    }

    internal partial class GeometrySinkNative
    {

        ~GeometrySinkNative()
        {
            Release();
        }

        public void AddLine(PointF point)
        {
            AddLine_(point);
        }

        public void AddBezier(BezierSegment bezier)
        {
            AddBezier_(ref bezier);
        }

        public void AddQuadraticBezier(QuadraticBezierSegment bezier)
        {
            AddQuadraticBezier_(bezier);
        }

        public void AddQuadraticBeziers(QuadraticBezierSegment[] beziers)
        {
            AddQuadraticBeziers_(beziers, beziers.Length);
        }

        public void AddArc(ref ArcSegment arc)
        {
            AddArc_(ref arc);
        }

        public void AddArc(ArcSegment arc)
        {
            AddArc_(ref arc);
        }
    }

    /// <summary>
    /// Internal GeometrySink Callback
    /// </summary>
    internal partial class GeometrySinkCallback : SimplifiedGeometrySinkCallback
    {
        GeometrySink Callback { get; set; }

        public GeometrySinkCallback(GeometrySink callback) : base(callback, 5)
        {
            Callback = callback;
            AddMethod(new AddLineDelegate(AddLineImpl));
            AddMethod(new AddBezierDelegate(AddBezierImpl));
            AddMethod(new AddQuadraticBezierDelegate(AddQuadraticBezierImpl));
            AddMethod(new AddQuadraticBeziersDelegate(AddQuadraticBeziersImpl));
            AddMethod(new AddArcDelegate(AddArcImpl));
        }
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void AddLineDelegate(System.Drawing.PointF point);
        private unsafe void AddLineImpl(System.Drawing.PointF point)
        {
            Callback.AddLine(point);
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void AddBezierDelegate(IntPtr bezier);
        private unsafe void AddBezierImpl(IntPtr bezier)
        {
            Callback.AddBezier(*((SlimDX.Direct2D1.BezierSegment*)bezier));
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void AddQuadraticBezierDelegate(IntPtr bezier);
        private unsafe void AddQuadraticBezierImpl(IntPtr bezier)
        {
            Callback.AddQuadraticBezier(*((SlimDX.Direct2D1.QuadraticBezierSegment*)bezier));
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void AddQuadraticBeziersDelegate(IntPtr beziers, int beziersCount);
        private unsafe void AddQuadraticBeziersImpl(IntPtr beziers, int beziersCount)
        {
            SlimDX.Direct2D1.QuadraticBezierSegment[] managedBeziers = new SlimDX.Direct2D1.QuadraticBezierSegment[beziersCount];
            Utilities.Read(beziers, managedBeziers, 0, beziersCount);
            Callback.AddQuadraticBeziers(managedBeziers);
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void AddArcDelegate(IntPtr arc);
        private unsafe void AddArcImpl(IntPtr arc)
        {
            Callback.AddArc(*((ArcSegment*) arc));
        }
    }
}
