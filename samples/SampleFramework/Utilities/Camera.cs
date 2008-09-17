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
using SlimDX;

namespace SampleFramework
{
    /// <summary>
    /// Represents a view onto a 3D scene.
    /// </summary>
    public class Camera
    {
        // variables
        Vector3 location;
        Vector3 target;
        float fieldOfView;
        float aspectRatio;
        float nearPlane;
        float farPlane;
        Matrix viewMatrix;
        Matrix projectionMatrix;
        bool viewDirty = true;
        bool projectionDirty = true;

        /// <summary>
        /// Gets or sets the location of the camera eye point.
        /// </summary>
        /// <value>The location of the camera eye point.</value>
        public Vector3 Location
        {
            get { return location; }
            set
            {
                // avoid unecessary changes
                if (location == value)
                    return;

                // mark the view matrix as dirty
                location = value;
                viewDirty = true;
            }
        }

        /// <summary>
        /// Gets or sets the view target point.
        /// </summary>
        /// <value>The view target point.</value>
        public Vector3 Target
        {
            get { return target; }
            set
            {
                // avoid unecessary changes
                if (target == value)
                    return;

                // mark the view matrix as dirty
                target = value;
                viewDirty = true;
            }
        }

        /// <summary>
        /// Gets or sets the field of view.
        /// </summary>
        /// <value>The field of view.</value>
        public float FieldOfView
        {
            get { return fieldOfView; }
            set
            {
                // avoid unecessary changes
                if (fieldOfView == value)
                    return;

                // mark the projection matrix as dirty
                fieldOfView = value;
                projectionDirty = true;
            }
        }

        /// <summary>
        /// Gets or sets the aspect ratio.
        /// </summary>
        /// <value>The aspect ratio.</value>
        public float AspectRatio
        {
            get { return aspectRatio; }
            set
            {
                // avoid unecessary changes
                if (aspectRatio == value)
                    return;

                // mark the projection matrix as dirty
                aspectRatio = value;
                projectionDirty = true;
            }
        }

        /// <summary>
        /// Gets or sets the near plane.
        /// </summary>
        /// <value>The near plane.</value>
        public float NearPlane
        {
            get { return nearPlane; }
            set
            {
                // avoid unecessary changes
                if (nearPlane == value)
                    return;

                // mark the projection matrix as dirty
                nearPlane = value;
                projectionDirty = true;
            }
        }

        /// <summary>
        /// Gets or sets the far plane.
        /// </summary>
        /// <value>The far plane.</value>
        public float FarPlane
        {
            get { return farPlane; }
            set
            {
                // avoid unecessary changes
                if (farPlane == value)
                    return;

                // mark the projection matrix as dirty
                farPlane = value;
                projectionDirty = true;
            }
        }

        /// <summary>
        /// Gets the view matrix.
        /// </summary>
        /// <value>The view matrix.</value>
        public Matrix ViewMatrix
        {
            get
            {
                // if the matrix is dirty, rebuild it
                if (viewDirty)
                    RebuildViewMatrix();
                return viewMatrix;
            }
        }

        /// <summary>
        /// Gets the projection matrix.
        /// </summary>
        /// <value>The projection matrix.</value>
        public Matrix ProjectionMatrix
        {
            get
            {
                // if the matrix is dirty, rebuild it
                if (projectionDirty)
                    RebuildProjectionMatrix();
                return projectionMatrix;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Camera"/> class.
        /// </summary>
        public Camera()
        {
        }

        /// <summary>
        /// Rebuilds the view matrix.
        /// </summary>
        protected virtual void RebuildViewMatrix()
        {
            // rebuild the view matrix
            viewMatrix = Matrix.LookAtLH(Location, Target, Vector3.UnitY);
            viewDirty = false;
        }

        /// <summary>
        /// Rebuilds the projection matrix.
        /// </summary>
        protected virtual void RebuildProjectionMatrix()
        {
            // rebuild the projection matrix
            projectionMatrix = Matrix.PerspectiveFovLH(FieldOfView, AspectRatio, NearPlane, FarPlane);
            projectionDirty = false;
        }
    }
}
