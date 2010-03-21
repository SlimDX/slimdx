using System;

namespace SlimDX {
    public interface IComObject {
        IntPtr UnknownPointer { get; }
    
        void AddReference();
        void Release();
    }
}