using System;
using System.Collections.Generic;
using System.Text;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    static class BitExtractor
    {
        #region Methods

        public static int GetDepthBits(Format format)
        {
            switch (format)
            {
                case Format.D32SingleLockable:
                case Format.D32:
                    return 32;

                case Format.D24X8:
                case Format.D24S8:
                case Format.D24X4S4:
                case Format.D24FS8:
                    return 24;

                case Format.D16Lockable:
                case Format.D16:
                    return 16;

                case Format.D15S1:
                    return 15;

                default:
                    return 0;
            }
        }

        public static int GetStencilBits(Format format)
        {
            switch (format)
            {
                case Format.D15S1:
                    return 1;

                case Format.D24X4S4:
                    return 4;

                case Format.D24S8:
                case Format.D24FS8:
                    return 8;

                default:
                    return 0;
            }
        }

        public static int GetColorBits(Format format)
        {
            switch (format)
            {
                case Format.R8G8B8:
                case Format.A8R8G8B8:
                case Format.A8B8G8R8:
                case Format.X8R8G8B8:
                    return 8;

                case Format.R5G6B5:
                case Format.X1R5G5B5:
                case Format.A1R5G5B5:
                    return 5;

                case Format.A4R4G4B4:
                case Format.X4R4G4B4:
                    return 4;

                case Format.R3G3B2:
                case Format.A8R3G3B2:
                    return 2;

                case Format.A2R10G10B10:
                case Format.A2B10G10R10:
                    return 10;

                case Format.A16B16G16R16:
                    return 16;

                default:
                    return 0;
            }
        }

        public static int GetAlphaBits(Format format)
        {
            switch (format)
            {
                case Format.A1R5G5B5:
                    return 1;

                case Format.A2R10G10B10:
                case Format.A2B10G10R10:
                    return 2;

                case Format.A4R4G4B4:
                    return 4;

                case Format.A8R8G8B8:
                case Format.A8R3G3B2:
                case Format.A8B8G8R8:
                    return 8;

                case Format.A16B16G16R16:
                    return 16;

                default:
                    return 0;
            }
        }

        #endregion
    }
}
