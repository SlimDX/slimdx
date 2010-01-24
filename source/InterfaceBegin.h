/*
* Copyright (c) 2007-2010 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

// Note that this file intentionally lacks inclusion guards, because it is
// intended to be included during a preprocessor iteration phase.

// This header is intended to demarcate the beginning of SlimDX class
// interface definition. 

// Undefine all iteration-dependant macros to ensure a clean slate.
#undef IS_INTERFACE
#undef IS_CONCRETE
#undef SDX_CLASS
#undef SDX_COM_CLASS
#undef SDX_COM_SUBCLASS
#undef SDX_METHOD
#undef SDX_METHOD_CONCRETE

// C++/CLI keywords like "interface struct" are considered a single token
// in bare source code... so a macro redefining 'interface,' like the one that
// exists in the Win32 header basetyps.h, will not alter the keyword. However,
// when "interface struct" is emitted as a result of macro replacement, it is
// not a single token; the basetyps.h macro changes 'interface' to 'struct,'
// producing a compiler error. As a result we must push and undefine that
// macro for the duration of the scope of our own macros to avoid errors.
// The matching pop_macro is found in InterfaceEnd.h.
#pragma push_macro("interface")
#undef interface


//TODO: This is temporary until we finalize interfaces for release.
#if BOOST_PP_ITERATION() == 2
// Iteration one is the interface declaration iteration.
#define IS_INTERFACE

// The interface declaration iteration omits concrete methods.
// However, documentation comments for those methods still appear
// in the preprocessed output, causing warnings we want to suppress.
//#pragma warning(push)
//#pragma warning(disable:4633 4634 4638)

#define SDX_CLASS(n) public interface struct I##n
#define SDX_COM_CLASS(n) public interface struct I##n : System::IDisposable
#define SDX_COM_SUBCLASS(n,b) public interface struct I##n : System::IDisposable
#define SDX_METHOD(m) virtual m = 0
#define SDX_METHOD_CONCRETE(m) 

#elif BOOST_PP_ITERATION() == 1
// Iteration two is the implementation declaration iteration.
#define IS_CONCRETE

// Re-enable the warnings we disabled during the first phase.
//#pragma warning(pop)

#define SDX_CLASS(n) public ref class n //: public I##n
#define SDX_COM_CLASS(n) public ref class n : public ComObject //, public I##n
#define SDX_COM_SUBCLASS(n,b) public ref class n : public b //, public I##n
#define SDX_METHOD(m) virtual m
#define SDX_METHOD_CONCRETE(m) m

#endif
