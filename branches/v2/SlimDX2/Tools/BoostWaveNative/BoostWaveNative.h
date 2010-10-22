// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#pragma once

#include <windows.h>
#include <Unknwn.h>


struct  __declspec(uuid("F9606B8C-35FC-4485-9E20-C14231A143E6")) __declspec(novtable) PreProcessor : public IUnknown {
public:
    virtual void __stdcall Run();
	virtual void __stdcall DefineMacro(const char* macroDef, bool isPredefined);
	virtual void __stdcall AddIncludePath(const char* includePath);
};


struct __declspec(novtable) ProcessCallback : public IUnknown {
public:
    virtual void __stdcall Token(int tokenId, const char* value);

	virtual void __stdcall IncludeBegin(const char* name);
	virtual char* __stdcall IncludeFind(const char* name);
	virtual void __stdcall IncludeEnd();

	virtual void __stdcall MacroDefBegin(const char *name, int nbArgs);
	virtual void __stdcall MacroDefBody();
	virtual void __stdcall MacroDefEnd();
	virtual void __stdcall MacroUnDef(const char* name);

	virtual void __stdcall MacroArg();

	virtual void __stdcall MacroFunctionCall(const char* name);
	virtual void __stdcall MacroFunctionEnd();


	virtual void __stdcall LogException(unsigned int severity, unsigned int errorcode, const char* name);
};

extern "C" __declspec(dllexport)  PreProcessor* __cdecl WavePreprocess(const char* header, const char* fileName, ProcessCallback* callback );
