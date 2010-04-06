using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public interface IEffect10 : IComObject {
        IEffectTechnique10 GetTechniqueByIndex(int index);
    }

    public interface IEffectTechnique10 {
        IEffectPass10 GetPassByIndex(int index);
    }

    public interface IEffectPass10 {
        EffectPassDescription10 GetDescription();
        void Apply();
    }
}
