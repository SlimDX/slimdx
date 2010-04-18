using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public enum ShaderFlags {
        None = 0,
        Debug = (1 << 0),
        SkipValidation = (1 << 1),
        SkipOptimization = (1 << 2),
        PackMatrixRowMajor = (1 << 3),
        PackMatrixColumnMajor = (1 << 4),
        PartialPrecision = (1 << 5),
        ForceVsSoftwareNoOpt = (1 << 6),
        ForcePsSoftwareNoOpt = (1 << 7),
        NoPreshader = (1 << 8),
        AvoidFlowControl = (1 << 9),
        PreferFlowControl = (1 << 10),
        EnableStrictness = (1 << 11),
        EnableBackwardsCompatibility = (1 << 12),
        IeeeStrictness = (1 << 13),
        WarningsAreErrors = (1 << 18),

        // optimization level flags
        OptimizationLevel0 = (1 << 14),
        OptimizationLevel1 = 0,
        OptimizationLevel2 = ((1 << 14) | (1 << 15)),
        OptimizationLevel3 = (1 << 15),
    }
}
