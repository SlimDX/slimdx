using System;
using System.Drawing;
using System.Windows.Forms;

using SlimDX;
using SlimDX.Direct3D9;
using SampleFramework;

namespace SimpleLighting
{
    //We have abstracted the view and projection information along with the lighting information 
    //away in an object of this class.
    public class Camera
    {
        Vector3 cameraPosition, cameraTarget, cameraUpVector;
        Cull cullMode;
        bool lighting;
        float zFarPlane;
        float FOVAngle;
        Color color;
        int XRES, YRES;

        public Camera(int width, int height)
        {
            //Initializing with default values for parameters
            XRES = width;
            YRES = height;
            cameraPosition = new Vector3(0.0f, 7.0f, 20.0f);
            cameraTarget = new Vector3(0, 0, 0);
            cameraUpVector = new Vector3(0, 1.0f, 0);
            cullMode = Cull.Clockwise;
            lighting = true;
            color = Color.MidnightBlue;
            zFarPlane = 40.0f;
            FOVAngle = (float)Math.PI / 4;
        }

        //Called whenever mouse moved event occurs in order to alter the lighting state
        public void SetupCamera(Device device, GameWindow window, MouseEventArgs e)
        {
            //View and Projection Transform setup occurs here
            device.SetTransform(TransformState.Projection, Matrix.PerspectiveFovLH(FOVAngle,
                 window.Width / window.Height, 0, zFarPlane));
            device.SetTransform(TransformState.View, Matrix.LookAtLH(cameraPosition, cameraTarget,
                 cameraUpVector));
            device.SetRenderState(RenderState.Lighting, lighting);
            device.SetRenderState(RenderState.CullMode, cullMode);

            //Lighting and Material information
            Light light = new Light();
            Material material = new Material();

            if (SimpleLighting.pointLight)
            {
                light.Type = LightType.Point;
                light.Range = 100.0f;
                light.Attenuation0 = 0.05f;
                light.Attenuation1 = 0.05f;
                light.Attenuation2 = 0.03f;
                light.Diffuse = Color.ForestGreen;
                light.Ambient = Color.GhostWhite;
            }
            else
            {
                light.Type = LightType.Directional;
                light.Diffuse = Color.ForestGreen;
                light.Ambient = Color.GhostWhite;
            }

            Vector3 vecDirection = new Vector3(e.Location.X - XRES / 2, e.Location.Y - YRES / 2, -8.0f);
            vecDirection = vecDirection - new Vector3(SimpleLighting.x, SimpleLighting.y, SimpleLighting.z);
            vecDirection.Normalize();
            light.Direction = vecDirection;    // set the light direction
            device.SetLight(0, light);
            device.EnableLight(0, true);
            material.Diffuse = Color.FloralWhite;
            material.Ambient = color;
            device.Material = material;
        }
    }
}
