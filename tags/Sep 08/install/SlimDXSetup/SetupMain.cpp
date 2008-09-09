#include <windows.h>
#include "resource.h"

LPCWSTR FileTable[] =
{
	L"setup.exe",
#ifdef X64
	L"SlimDXRedist64.msi",
	L"vcredist_x64\\vcredist_x64.exe",
#else
	L"SlimDXRedist32.msi",
	L"vcredist_x86\\vcredist_x86.exe",
#endif
};

const wchar_t* dirSep = L"\\";

bool CreateFullPath(const wchar_t* path)
{
	wchar_t pathBuf[MAX_PATH];
	wchar_t dir[_MAX_DIR];

	_wsplitpath(path, pathBuf, dir, NULL, NULL);

	wchar_t* token = wcstok(dir, dirSep);
	while(token != NULL)
	{
		wcscat(pathBuf, dirSep);
		wcscat(pathBuf, token);
		token = wcstok(NULL, dirSep);

		DWORD attribs = GetFileAttributes(pathBuf);
		if(attribs == INVALID_FILE_ATTRIBUTES)
		{
			BOOL result = CreateDirectory(pathBuf, NULL);
			if(!result)
				return false;
		}
	}

	return true;
}

//based on http://syedgakbar.wordpress.com/2007/11/07/embedding-dll-and-binary-files-in-the-executable-applications/
bool ExtractResource(const HINSTANCE hInstance, WORD resourceId, LPCWSTR outputFilename)
{
	HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(resourceId), L"BINARY");
	if(hResource == NULL)
		return false;
	HGLOBAL hFileResource = LoadResource(hInstance, hResource);
	if(hFileResource == NULL)
		return false;

	void* lpFile = LockResource(hFileResource);
	if(lpFile == NULL)
		return false;
	DWORD resourceSize = SizeofResource(hInstance, hResource);
	if(resourceSize == 0)
		return false;

	//open and write the file
	if(!CreateFullPath(outputFilename))
		return false;
	HANDLE hFile = CreateFile(outputFilename, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, resourceSize, NULL );
	if(hFileMapping == NULL)
	{
		CloseHandle(hFile);
		return false;
	}

	void* baseAddress = MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);
	if(baseAddress == NULL )
	{
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	CopyMemory(baseAddress, lpFile, resourceSize);

	BOOL unmapResult = UnmapViewOfFile(baseAddress);
	if(unmapResult == 0)
	{
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFileMapping);
	CloseHandle(hFile);

	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCommandLine, int nCmdShow)
{
	wchar_t tempPath[MAX_PATH];
	wchar_t fileName[MAX_PATH];

	//look up the temp dir
	GetTempPath(MAX_PATH, tempPath);

	int fileCount = sizeof(FileTable) / sizeof(LPCWSTR);
	for(int f = 0; f < fileCount; ++f)
	{
		wcscpy_s(fileName, MAX_PATH, tempPath);
		wcscat_s(fileName, MAX_PATH, FileTable[f]);

		bool result = ExtractResource(hInstance, IDR_BASEVALUE + f, fileName);
		if(!result)
		{
			MessageBox(NULL, L"Failed to extract files.", L"Installation Failed", MB_ICONERROR);
			return E_FAIL;
		}
	}

	wcscpy_s(fileName, MAX_PATH, tempPath);
	wcscat_s(fileName, MAX_PATH, FileTable[0]);

	STARTUPINFO startInfo = {0};
	startInfo.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION procInfo = {0};

	BOOL result = CreateProcess(fileName, NULL, NULL, NULL, FALSE, 0, NULL, tempPath, &startInfo, &procInfo);
	if(!result)
	{
			MessageBox(NULL, L"Failed to launch installer.", L"Installation Failed", MB_ICONERROR);
			return E_FAIL;
	}
	WaitForSingleObject(procInfo.hProcess, INFINITE);
	CloseHandle(procInfo.hThread);
	CloseHandle(procInfo.hProcess);

	//sadly, we don't clean up the temp directory ourselves, because we have no way of waiting
	//for the installer to complete (it does another CreateProcess and hides from us).

	return 0;
}