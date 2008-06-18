#ifndef UNICODE
#error This code is written for Unicode only.
#endif

#include <cstdio>
#include <windows.h>
#include <msiquery.h>

#include <dsetup.h>

#include "targetver.h"
#include "resource.h"

#define DLLEXPORT __declspec(dllexport)

#define VERSION_NUMBER L"38"
#define VERSION_NAME L"Jun2008"

#ifdef X64
#define PLATFORM L"x64"
#else
#define PLATFORM L"x86"
#endif

LPCWSTR FileTable[] =
{
	L"dsetup32.dll",
	L"dsetup.dll",
	L"dxdllreg_x86.cab",
	L"dxsetup.exe",
	L"dxupdate.cab",

	VERSION_NAME L"_d3dx9_" VERSION_NUMBER L"_" PLATFORM L".cab",
	VERSION_NAME L"_d3dx10_" VERSION_NUMBER L"_" PLATFORM L".cab",
	VERSION_NAME L"_X3DAudio_" VERSION_NUMBER L"_" PLATFORM L".cab",
	VERSION_NAME L"_XAudio_" VERSION_NUMBER L"_" PLATFORM L".cab"
};

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

bool RunDXSetup(LPCWSTR extractPath)
{
	wchar_t oldCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, oldCurrentDir);
	SetCurrentDirectory(extractPath);

	STARTUPINFO startupInfo = {0};
	PROCESS_INFORMATION processInfo = {0};

	startupInfo.cb = sizeof(STARTUPINFO);
	//can't use a read-only string with CreateProcessW
	wchar_t commandLine[] = L"dxsetup.exe /silent";
	if(!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo))
	{
		SetCurrentDirectory(oldCurrentDir);
		return false;
	}

	WaitForSingleObject(processInfo.hProcess, INFINITE);

	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);
	SetCurrentDirectory(oldCurrentDir);
	return true;
}

//From http://blogs.msdn.com/oldnewthing/archive/2004/10/25/247180.aspx
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THIS ((HINSTANCE)&__ImageBase)

EXTERN_C DLLEXPORT UINT DXSetupAction(MSIHANDLE session)
{
	HINSTANCE hInstance = HINST_THIS;

	wchar_t tempDir[MAX_PATH];
	DWORD tempDirLength = MAX_PATH;
	UINT x = MsiGetPropertyW(session, L"CustomActionData", tempDir, &tempDirLength);

	wchar_t fileName[MAX_PATH];

	int fileCount = sizeof(FileTable) / sizeof(LPCWSTR);
	for(int f = 0; f < fileCount; ++f)
	{
		wcscpy_s(fileName, MAX_PATH, tempDir);
		wcscat_s(fileName, MAX_PATH, FileTable[f]);

		bool result = ExtractResource(hInstance, IDR_BASEVALUE + f, fileName);
		if(!result)
		{
			return E_FAIL;
		}
	}

	bool setupResult = RunDXSetup(tempDir);

	//Delete all the temp files regardless
	for(int f = 0; f < fileCount; ++f)
	{
		wcscpy_s(fileName, MAX_PATH, tempDir);
		wcscat_s(fileName, MAX_PATH, FileTable[f]);

		DeleteFile(fileName);
	}

	return setupResult ? S_OK : E_FAIL;
}
