using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX {
    public interface IMemoryBuffer {
        long WriteOffset { get; set; }
        long ReadOffset { get; set; }
        void Write<T>(T value) where T : struct;
        T Read<T>() where T : struct;
    }
}
