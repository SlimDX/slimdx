using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public interface IEffect : IComObject {
        IEffectTechnique GetTechniqueByIndex(int index);
    }

    public interface IEffectTechnique {
        IEffectPass GetPassByIndex(int index);
    }

    public interface IEffectPass {
        EffectPassDescription GetDescription();
        void Apply();
    }
}
