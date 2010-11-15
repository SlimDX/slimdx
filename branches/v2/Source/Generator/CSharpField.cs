using SlimDX2.Tools.XIDL;

namespace SlimDX.Generator
{
    public class CSharpField : CSharpMapType
    {
        public CSharpField(CppField cppField, CSharpType publicType, CSharpType marshalType,
                     string name) : base(cppField, publicType, marshalType, name)
        {
        }
    }
}