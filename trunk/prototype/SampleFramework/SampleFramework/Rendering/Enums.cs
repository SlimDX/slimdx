using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SampleFramework
{
    /// <summary>
    /// Specifies possible Direct3D API versions.
    /// </summary>
    public enum DeviceVersion
    {
        /// <summary>
        /// The device is a Direct3D9 device.
        /// </summary>
        Direct3D9,

        /// <summary>
        /// The deviec is a Direct3D10 device.
        /// </summary>
        Direct3D10
    }

    /// <summary>
    /// Defines vertex and pixel shader versions.
    /// </summary>
    public enum ShaderProfile
    {
        /// <summary>
        /// Pixel Shader 1.1.
        /// </summary>
        PS_1_1,

        /// <summary>
        /// Pixel Shader 1.2.
        /// </summary>
        PS_1_2,

        /// <summary>
        /// Pixel Shader 1.3.
        /// </summary>
        PS_1_3,

        /// <summary>
        /// Pixel Shader 1.4.
        /// </summary>
        PS_1_4,

        /// <summary>
        /// Pixel Shader 2.0.
        /// </summary>
        PS_2_0,

        /// <summary>
        /// Pixel Shader 2.0a.
        /// </summary>
        PS_2_A,

        /// <summary>
        /// Pixel Shader 2.0b.
        /// </summary>
        PS_2_B,

        /// <summary>
        /// Pixel Shader 2.0sw.
        /// </summary>
        PS_2_SW,

        /// <summary>
        /// Pixel Shader 3.0.
        /// </summary>
        PS_3_0,

        /// <summary>
        /// Pixel Shader 3.0X.
        /// </summary>
        XPS_3_0,

        /// <summary>
        /// Vertex Shader 1.1.
        /// </summary>
        VS_1_1,

        /// <summary>
        /// Vertex Shader 2.0.
        /// </summary>
        VS_2_0,

        /// <summary>
        /// Vertex Shader 2.0a.
        /// </summary>
        VS_2_A,

        /// <summary>
        /// Vertex Shader 2.0sw.
        /// </summary>
        VS_2_SW,

        /// <summary>
        /// Vertex Shader 3.0.
        /// </summary>
        VS_3_0,

        /// <summary>
        /// Vertex Shader 3.0X.
        /// </summary>
        XVS_3_0
    }
}
