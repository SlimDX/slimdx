/*
* Copyright (c) 2007-2008 SlimDX Group
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
#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

#include "InternalHelpers.h"

struct stackalloc_t { };
extern const stackalloc_t stackalloc;

void* operator new(std::size_t size, stackalloc_t stackalloc);
void operator delete(void* p, stackalloc_t stackalloc);

namespace SlimDX
{
	template<typename T> class stack_ptr
	{
	public:
		typedef T element_type;

		explicit stack_ptr(T* p = 0) throw() : pointer(p)
		{ }
		stack_ptr(stack_ptr<T>& other) throw() : pointer(other.release())
		{ }

		~stack_ptr()
		{
			_freea(pointer);
		}

		T* get()
		{
			return pointer;
		}

		T* release()
		{
			T* temp = pointer;
			pointer = 0;
			return temp;
		}

		void reset(T* p)
		{
			if(p != pointer)
				_freea(pointer);

			pointer = p;
		}

	private:
		T* pointer;
	};

	template<typename T> inline void destroy(T* p)
	{
		//Why the hell does -W4 demand this?
		SLIMDX_UNREFERENCED_PARAMETER(p);

		p->~T();
	}

	template<> inline void destroy(char* p) { SLIMDX_UNREFERENCED_PARAMETER(p); }
	template<> inline void destroy(wchar_t* p) { SLIMDX_UNREFERENCED_PARAMETER(p); }

	template<typename T> struct StackAllocator;

	template<> struct StackAllocator<void>
	{
		typedef void*			pointer;
		typedef const void*		const_pointer;
		typedef void			value_type;

		template<typename U> struct rebind { typedef StackAllocator<U> other; };
	};

	template<typename T> struct StackAllocator
	{
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef T				value_type;

		template<typename U> struct rebind { typedef StackAllocator<U> other; };

		StackAllocator() throw() { }
		StackAllocator(const StackAllocator<T>& other) throw() { SLIMDX_UNREFERENCED_PARAMETER(other); }
		template<typename U> StackAllocator(const StackAllocator<U>& other ) throw() { SLIMDX_UNREFERENCED_PARAMETER(other); }

		template<typename U> StackAllocator<T>& operator=(const StackAllocator<U>& other)
		{
			return *this;
		}

		pointer address(reference x) const { return &x; }
		const_pointer address(const_reference x) const { return &x; }

		pointer allocate(size_type size, StackAllocator<void>::const_pointer hint = 0)
		{
			SLIMDX_UNREFERENCED_PARAMETER(hint);

			pointer p = static_cast<pointer>( _malloca(size * sizeof(value_type)) );
			if(!p)
				throw std::bad_alloc();
			return p;
		}

		void deallocate(pointer p, size_type size)
		{
			SLIMDX_UNREFERENCED_PARAMETER(size);
			_freea(p);
		}

		size_type max_size() const throw()
		{
			size_type count = (size_type) -1 / sizeof(T);
			return 0 < count ? count : 1;
		}

		void construct(pointer p, const T& value)
		{
			new (static_cast<void*>(p)) T(value);
		}

		void destroy(pointer p)
		{
			SlimDX::destroy(p);
		}
	};

	template<typename T, typename U>
	inline bool operator==(const StackAllocator<T>&, const StackAllocator<U>&)
	{
		return true;
	}

	template<typename T, typename U>
	inline bool operator!=(const StackAllocator<T>&, const StackAllocator<U>&)
	{
		return false;
	}

	template<typename T>
	struct stack_vector
	{
		typedef std::vector<T, StackAllocator<T> > vector_type;
		typedef typename vector_type::size_type size_type;
		typedef typename vector_type::value_type value_type;

		vector_type vector;

		stack_vector()
		{ }
		stack_vector(size_type size) : vector(size)
		{ }
		stack_vector(size_type size, const T& t) : vector(size, t)
		{ }

		T& operator[](size_type n)
		{
			return vector[n];
		}

		const T& operator[](size_type n) const
		{
			return vector[n];
		}

		void reserve(std::size_t size)
		{
			vector.reserve(size);
		}

		void resize(std::size_t size, const T& t = T())
		{
			vector.resize(size, t);
		}

		size_type size()
		{
			return vector.size();
		}
	};
}
