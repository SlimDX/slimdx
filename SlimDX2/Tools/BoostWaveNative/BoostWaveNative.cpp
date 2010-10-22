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
#include "stdafx.h"
#include "BoostWaveNative.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <ostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
//  Include Wave itself
#include <boost/wave.hpp>

///////////////////////////////////////////////////////////////////////////////
// Include the lexer stuff
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class
#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/wave/token_ids.hpp>
#include <boost/wave/util/macro_helpers.hpp>
#include <boost/wave/preprocessing_hooks.hpp>

#include "WaveMacroHook.h"


struct myload_file_to_string 
{
    static ProcessCallback* callback;

    template <typename IterContextT>
    class inner 
    {
    public:

        template <typename PositionT>
        static void init_iterators(IterContextT &iter_ctx, 
            PositionT const &act_pos, boost::wave::language_support language)
        {
            typedef typename IterContextT::iterator_type iterator_type;

			const char* filename = iter_ctx.filename.c_str();
            const char* buffer = callback->IncludeFind(filename);

            //// read in the file
            //std::ifstream instream(iter_ctx.filename.c_str());
            //if (!instream.is_open()) {
            //	BOOST_WAVE_THROW_CTX(iter_ctx.ctx, preprocess_exception, 
            //		bad_include_file, iter_ctx.filename.c_str(), act_pos);
            //	return;
            //}
            //instream.unsetf(std::ios::skipws);

            iter_ctx.instring.assign(buffer);


			HGLOBAL test = GlobalFree((HGLOBAL)buffer);

            iter_ctx.first = iterator_type(
                iter_ctx.instring.begin(), iter_ctx.instring.end(), 
                PositionT(iter_ctx.filename), language);
            iter_ctx.last = iterator_type();
        }

    private:
        std::string instring;
    };
};

ProcessCallback* myload_file_to_string::callback;



typedef boost::wave::cpplexer::lex_token<> token_type;
    
typedef boost::wave::cpplexer::lex_iterator<token_type> lex_iterator_type;
        
typedef boost::wave::context<std::string::iterator, lex_iterator_type,
    myload_file_to_string,
    advanced_preprocessing_hooks
> context_type;

class PreProcesorImpl : PreProcessor {
private:
	context_type* ctx;
	ProcessCallback* callback;
	std::string instring;
	int refcount;

public:
	PreProcesorImpl(const char* header, const char* fileName, ProcessCallback* callback ) {
		refcount = 0;

		this->callback = callback;
		instring = header;

		// Set callback on hook
		advanced_preprocessing_hooks hook;
		hook.callback = callback;

		context_type::input_policy_type::callback = callback;

		// New context
		ctx = new context_type(instring.begin(), instring.end(), fileName, hook);
	}

	STDMETHODIMP QueryInterface(REFIID riid, void **ppv) {
		if (riid == IID_IUnknown || riid == __uuidof(PreProcessor) ) {
			AddRef();
			return (*ppv = this), S_OK;
		}
		return (*ppv = 0), E_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG) AddRef() {
		return ++refcount;
	}

	STDMETHODIMP_(ULONG) Release(){
		if (--refcount != 0) 
			return refcount; 
		if (ctx != 0) {
			delete ctx;
			ctx = 0;
		}
		return 0;
	}

	virtual void __stdcall Run() {

		// Remove emit_line_directives
		auto lang_support = ctx->get_language();
		auto lang_support_new = (int)lang_support & ~boost::wave::support_option_emit_line_directives;
		ctx->set_language( (boost::wave::language_support)(lang_support_new), false);

		//  Get the preprocessor iterators and use them to generate 
		//  the token sequence.
		context_type::iterator_type first = ctx->begin();
		context_type::iterator_type last = ctx->end();
        
		//  The input stream is preprocessed for you while iterating over the range
		//  [first, last)
		while (first != last) {
			token_type token = *first;
			boost::wave::token_id id = boost::wave::token_id(token);
			boost::wave::token_category tokenCategory = (boost::wave::token_category)CATEGORY_FROM_TOKEN(id);

			if ( tokenCategory != boost::wave::EOLTokenType ) {
				BOOST_WAVE_STRINGTYPE token_value = token.get_value();			
				callback->Token(id, token_value.c_str());
			}

			first++;
		}
	}

	virtual void __stdcall DefineMacro(const char* macroDef, bool isPredefined) {
		ctx->add_macro_definition(macroDef, isPredefined);
	}

	virtual void __stdcall AddIncludePath(const char* includePath) {
		ctx->add_include_path(includePath);
	}
};


extern "C" __declspec(dllexport)  PreProcessor* __cdecl WavePreprocess(const char* header, const char* fileName, ProcessCallback* callback ) {

	PreProcessor* preprocessor = (PreProcessor*)new PreProcesorImpl(header,fileName,callback);
	preprocessor->AddRef();
	return preprocessor;
}