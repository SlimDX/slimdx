using System.Linq;
using System.Text.RegularExpressions;
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    public class MacroParser
    {
        private CppIncludeGroup _group;

        public MacroParser(CppIncludeGroup group)
        {
            _group = group;
        }

        private static Regex regexRemoveIntLitteral = new Regex("([0-9]U?)L");
        private static Regex regexMakeDXGIResult = new Regex(@"MAKE_DXGI_HRESULT\(([0-9]+)\)");
        private static Regex regexMakeDXGIStatus = new Regex(@"MAKE_DXGI_STATUS\(([0-9]+)\)");


        private static string _FACDXGIMacroValue = null;


        private string MakeHResult(string sev, string fac, string code)
        {
            return string.Format("((({0})<<31) | (({1})<<16) | ({2}))", sev, fac, code);
        }

        private void InitDXGIEnum()
        {
            if (_FACDXGIMacroValue == null)
                _FACDXGIMacroValue = _group.Find<CppMacroDefinition>("_FACDXGI").FirstOrDefault().Value;
        }

        private string MakeDXGIResult(Match match)
        {
            InitDXGIEnum();
            return MakeHResult("" + 1, _FACDXGIMacroValue, match.Groups[1].Value);
        }

        private string MakeDXGIStatus(Match match)
        {
            InitDXGIEnum();
            return MakeHResult("" + 0, _FACDXGIMacroValue, match.Groups[1].Value);
        }

        public string Parse(string value)
        {
            value = regexRemoveIntLitteral.Replace(value, "$1");
            value = regexMakeDXGIResult.Replace(value, MakeDXGIResult);
            value = regexMakeDXGIStatus.Replace(value, MakeDXGIStatus);
            return value;
        }

    }
}
