using System;

namespace SlimDX2.Direct2D1
{
    public partial class Geometry
    {
        /// <summary>	
        /// Creates a simplified version of the geometry that contains only lines and (optionally) cubic Bezier curves and writes the result to an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/>.	
        /// </summary>	
        /// <param name="simplificationOption">A value that specifies whether the simplified geometry should contain curves.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="geometrySink"> The <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> to which the simplified geometry is appended. </param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Simplify([None] D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,[In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result Simplify(SlimDX2.Direct2D1.GeometrySimplificationOption simplificationOption, float flatteningTolerance, GeometrySink geometrySink)
        {
            return Simplify(simplificationOption, null, flatteningTolerance, geometrySink);
        }

        /// <summary>	
        /// Creates a simplified version of the geometry that contains only lines and (optionally) cubic Bezier curves and writes the result to an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/>.	
        /// </summary>	
        /// <param name="simplificationOption">A value that specifies whether the simplified geometry should contain curves.</param>
        /// <param name="worldTransform">The transform to apply to the simplified geometry, or NULL.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="geometrySink"> The <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> to which the simplified geometry is appended. </param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Simplify([None] D2D1_GEOMETRY_SIMPLIFICATION_OPTION simplificationOption,[In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result Simplify(SlimDX2.Direct2D1.GeometrySimplificationOption simplificationOption, SlimDX2.Direct2D1.Matrix3x2? worldTransform, float flatteningTolerance, GeometrySink geometrySink)
        {
            GeometrySinkCallback _callback = null;
            IntPtr ptr;
            if (geometrySink.GetType() == typeof(DefaultGeometrySink))
                ptr = (geometrySink as DefaultGeometrySink).NativePointer;
            else
            {
                _callback = new GeometrySinkCallback(geometrySink);
                ptr = _callback.NativePointer;
            }
            return this.Simplify_(simplificationOption, worldTransform, flatteningTolerance, ptr);
        }

        /// <summary>	
        /// Creates a set of clockwise-wound triangles that cover the geometry after it has been transformed using the specified matrix and flattened using the specified tolerance	
        /// </summary>	
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="tessellationSink">The <see cref="SlimDX2.Direct2D1.TessellationSink"/> to which the tessellated is appended.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Tessellate([In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1TessellationSink* tessellationSink)</unmanaged>
        public SlimDX2.Result Tessellate(float flatteningTolerance, TessellationSink tessellationSink)
        {
            return Tessellate(null, flatteningTolerance, tessellationSink);
        }

        /// <summary>	
        /// Creates a set of clockwise-wound triangles that cover the geometry after it has been transformed using the specified matrix and flattened using the specified tolerance	
        /// </summary>	
        /// <param name="worldTransform">The transform to apply to this geometry, or NULL.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="tessellationSink">The <see cref="SlimDX2.Direct2D1.TessellationSink"/> to which the tessellated is appended.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Tessellate([In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1TessellationSink* tessellationSink)</unmanaged>
        public SlimDX2.Result Tessellate(SlimDX2.Direct2D1.Matrix3x2? worldTransform, float flatteningTolerance, TessellationSink tessellationSink)
        {
            TessellationSinkCallback _callback = null;
            IntPtr ptr;
            if (tessellationSink.GetType() == typeof(DefaultTessellationSink))
                ptr = (tessellationSink as DefaultTessellationSink).NativePointer;
            else
            {
                _callback = new TessellationSinkCallback(tessellationSink);
                ptr = _callback.NativePointer;
            }
            return this.Tessellate_(worldTransform, flatteningTolerance, ptr);
        }

        /// <summary>	
        /// Combines this geometry with the specified geometry and stores the result in an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/>.  	
        /// </summary>	
        /// <param name="inputGeometry">The geometry to combine with this instance.</param>
        /// <param name="combineMode">The type of combine operation to perform.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometries. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="geometrySink">The result of the combine operation.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT CombineWithGeometry([In] ID2D1Geometry* inputGeometry,[None] D2D1_COMBINE_MODE combineMode,[In, Optional] const D2D1_MATRIX_3X2_F* inputGeometryTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result CombineWithGeometry(SlimDX2.Direct2D1.Geometry inputGeometry, SlimDX2.Direct2D1.CombineMode combineMode, float flatteningTolerance, GeometrySink geometrySink)
        {
            return this.CombineWithGeometry(inputGeometry, combineMode, null, flatteningTolerance, geometrySink);
        }

        /// <summary>	
        /// Combines this geometry with the specified geometry and stores the result in an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/>.  	
        /// </summary>	
        /// <param name="inputGeometry">The geometry to combine with this instance.</param>
        /// <param name="combineMode">The type of combine operation to perform.</param>
        /// <param name="inputGeometryTransform">The transform to apply to inputGeometry before combining, or NULL.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometries. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="geometrySink">The result of the combine operation.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT CombineWithGeometry([In] ID2D1Geometry* inputGeometry,[None] D2D1_COMBINE_MODE combineMode,[In, Optional] const D2D1_MATRIX_3X2_F* inputGeometryTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result CombineWithGeometry(SlimDX2.Direct2D1.Geometry inputGeometry, SlimDX2.Direct2D1.CombineMode combineMode, SlimDX2.Direct2D1.Matrix3x2? inputGeometryTransform, float flatteningTolerance, GeometrySink geometrySink)
        {
            unsafe
            {
                GeometrySinkCallback _callback = null;
                IntPtr ptr;
                if (geometrySink.GetType() == typeof(DefaultGeometrySink))
                    ptr = (geometrySink as DefaultGeometrySink).NativePointer;
                else
                {
                    _callback = new GeometrySinkCallback(geometrySink);
                    ptr = _callback.NativePointer;
                }
                return this.CombineWithGeometry_(inputGeometry, combineMode, inputGeometryTransform, flatteningTolerance, ptr);
            }
        }

        /// <summary>	
        /// Computes the outline of the geometry and writes the result to an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/>.	
        /// </summary>	
        /// <remarks>	
        /// The {{Outline}} method allows the caller to produce a geometry with an equivalent fill to the input geometry, with the following additional properties: The output geometry contains no transverse intersections; that is, segments may touch, but they never cross.The outermost figures in the output geometry are all oriented counterclockwise. The output geometry is fill-mode invariant; that is, the fill of the geometry does not depend on the choice of the fill mode. For more information about the fill mode, see <see cref="SlimDX2.Direct2D1.FillMode"/>.Additionally, the  {{Outline}} method can be useful in removing redundant portions of said geometries to simplify complex geometries. It can also be useful in combination with <see cref="SlimDX2.Direct2D1.GeometryGroup"/> to create unions among several geometries simultaneously.	
        /// </remarks>	
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="geometrySink">The <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> to which the geometry's transformed outline is appended. </param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Outline([In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result Outline(float flatteningTolerance, GeometrySink geometrySink)
        {
            return this.Outline(null, flatteningTolerance, geometrySink);
        }

        /// <summary>	
        /// Computes the outline of the geometry and writes the result to an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/>.	
        /// </summary>	
        /// <remarks>	
        /// The {{Outline}} method allows the caller to produce a geometry with an equivalent fill to the input geometry, with the following additional properties: The output geometry contains no transverse intersections; that is, segments may touch, but they never cross.The outermost figures in the output geometry are all oriented counterclockwise. The output geometry is fill-mode invariant; that is, the fill of the geometry does not depend on the choice of the fill mode. For more information about the fill mode, see <see cref="SlimDX2.Direct2D1.FillMode"/>.Additionally, the  {{Outline}} method can be useful in removing redundant portions of said geometries to simplify complex geometries. It can also be useful in combination with <see cref="SlimDX2.Direct2D1.GeometryGroup"/> to create unions among several geometries simultaneously.	
        /// </remarks>	
        /// <param name="worldTransform">The transform to apply to the geometry outline, or NULL.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution. </param>
        /// <param name="geometrySink">The <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> to which the geometry's transformed outline is appended. </param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Outline([In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result Outline(SlimDX2.Direct2D1.Matrix3x2? worldTransform, float flatteningTolerance, GeometrySink geometrySink)
        {
            GeometrySinkCallback _callback = null;
            IntPtr ptr;
            if (geometrySink.GetType() == typeof(DefaultGeometrySink))
                ptr = (geometrySink as DefaultGeometrySink).NativePointer;
            else
            {
                _callback = new GeometrySinkCallback(geometrySink);
                ptr = _callback.NativePointer;
            }
            return this.Outline_(worldTransform, flatteningTolerance, ptr);
        }

        /// <summary>	
        /// Widens the geometry by the specified stroke and writes the result to an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> after it has been transformed by the specified matrix and flattened using the specified tolerance.	
        /// </summary>	
        /// <param name="strokeWidth">The amount by which to widen the geometry.</param>
        /// <param name="strokeStyle">The style of stroke to apply to the geometry, or NULL.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution.</param>
        /// <param name="geometrySink">The <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> to which the widened geometry is appended.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Widen([None] FLOAT strokeWidth,[In, Optional] ID2D1StrokeStyle* strokeStyle,[In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result Widen(float strokeWidth, SlimDX2.Direct2D1.StrokeStyle strokeStyle, float flatteningTolerance, GeometrySink geometrySink)
        {
            return this.Widen(strokeWidth, strokeStyle, null, flatteningTolerance, geometrySink);
        }

        /// <summary>	
        /// Widens the geometry by the specified stroke and writes the result to an <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> after it has been transformed by the specified matrix and flattened using the specified tolerance.	
        /// </summary>	
        /// <param name="strokeWidth">The amount by which to widen the geometry.</param>
        /// <param name="strokeStyle">The style of stroke to apply to the geometry, or NULL.</param>
        /// <param name="worldTransform">The transform to apply to the geometry after widening it, or NULL.</param>
        /// <param name="flatteningTolerance">The maximum bounds on the distance between points in the polygonal approximation of the geometry. Smaller values produce more accurate results but cause slower execution.</param>
        /// <param name="geometrySink">The <see cref="SlimDX2.Direct2D1.SimplifiedGeometrySink"/> to which the widened geometry is appended.</param>
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.</returns>
        /// <unmanaged>HRESULT Widen([None] FLOAT strokeWidth,[In, Optional] ID2D1StrokeStyle* strokeStyle,[In, Optional] const D2D1_MATRIX_3X2_F* worldTransform,[None] FLOAT flatteningTolerance,[In] ID2D1SimplifiedGeometrySink* geometrySink)</unmanaged>
        public SlimDX2.Result Widen(float strokeWidth, SlimDX2.Direct2D1.StrokeStyle strokeStyle, SlimDX2.Direct2D1.Matrix3x2? worldTransform, float flatteningTolerance, GeometrySink geometrySink)
        {
            GeometrySinkCallback _callback = null;
            IntPtr ptr;
            if (geometrySink.GetType() == typeof(DefaultGeometrySink))
                ptr = (geometrySink as DefaultGeometrySink).NativePointer;
            else
            {
                _callback = new GeometrySinkCallback(geometrySink);
                ptr = _callback.NativePointer;
            }
            return this.Widen_(strokeWidth, strokeStyle, worldTransform, flatteningTolerance, ptr);
        }
    }
}
