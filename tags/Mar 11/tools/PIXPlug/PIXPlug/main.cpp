#include <mscoree.h>
#include <corerror.h>
#include <iostream>
#include <string>

template<typename from, typename to>
from lexical_cast(const to& arg);

template<>
inline std::wstring lexical_cast<std::wstring, std::string>(const std::string& arg)
{
	std::wstring result;
	std::locale loc;

	for(unsigned int i= 0; i < arg.size(); ++i)
		result += std::use_facet<std::ctype<wchar_t> >(loc).widen(arg[i]);

	return result;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return -1;

	ICLRRuntimeHost *host = 0;
	HRESULT hr = CorBindToRuntimeEx(L"v2.0.50727", L"svr", STARTUP_CONCURRENT_GC, CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost, reinterpret_cast<LPVOID*>(&host));
	if (FAILED(hr))
		return -2;

	hr = host->Start();
	if (FAILED(hr))
		return -3;

	WCHAR cdPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, cdPath);
	std::wstring path = cdPath;
	path += L"\\PIXPlug.Shim.dll";

	DWORD ret;
	hr = host->ExecuteInDefaultAppDomain(path.c_str(), L"PIXPlug.Shim.AppRunner", L"Start", lexical_cast<std::wstring, std::string>(argv[1]).c_str(), &ret);
	if (FAILED(hr))
		return -4;

	host->Stop();
	host->Release();
}