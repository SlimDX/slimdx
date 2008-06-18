using System;
using System.Collections.Generic;
using System.Text;
using SlimDX;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    public class Camera
    {
        public Camera()
        {
            this.fov = (float)(Math.PI / 4);
            this.aspect = 1.3f;
            this.zNear = 1;
            this.zFar = 1000;

            this.eye = new Vector3(0, 0, -100);
            this.target = new Vector3(0, 0, 0);
            this.up = new Vector3(0, 1, 0);

            UpdateProjection();
            UpdateView();
        }

        #region View

        Vector3 eye;

        public Vector3 Eye
        {
            get
            {
                return eye;
            }
            set
            {
                eye = value;
                UpdateView();
            }
        }

        Vector3 target;

        public Vector3 Target
        {
            get
            {
                return target;
            }
            set
            {
                target = value;
                UpdateView();
            }
        }

        Vector3 up;

        public Vector3 UpVector
        {
            get
            {
                return up;
            }
            set
            {
                up = value;
                UpdateView();
            }
        }

        Matrix view;

        public Matrix View
        {
            get
            {
                return view;
            }
        }

        protected void UpdateView()
        {
            Matrix.LookAtLH(ref this.eye, ref this.target, ref this.up, out this.view);
        }

        #endregion

        #region Projection

        float fov;

        public float FoV
        {
            get
            {
                return fov;
            }
            set
            {
                fov = value;
                UpdateProjection();
            }
        }

        float aspect;

        public float Aspect
        {
            get
            {
                return aspect;
            }
            set
            {
                aspect = value;
                UpdateProjection();
            }
        }

        float zNear;

        public float ZNear
        {
            get
            {
                return zNear;
            }
            set
            {
                zNear = value;
                UpdateProjection();
            }
        }

        float zFar;

        public float ZFar
        {
            get
            {
                return zFar;
            }
            set
            {
                zFar = value;
                UpdateProjection();
            }
        }

        Matrix projection;

        public Matrix Projection
        {
            get
            {
                return projection;
            }
        }

        private void UpdateProjection()
        {
            Matrix.PerspectiveFovLH(this.fov, this.aspect, this.zNear, this.zFar, out this.projection);
        }

        #endregion

        public void Apply(Device device)
        {
            device.SetTransform(TransformState.View, this.view);
            device.SetTransform(TransformState.Projection, this.projection);
        }
    }
}
