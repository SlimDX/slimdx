#pragma once

#include "Utils.h"

namespace SlimDX
{
	public ref class DirectXObject abstract
	{
	internal:
		virtual property IUnknown* ComPointer
		{
			IUnknown* get() abstract;
			void set( IUnknown* value ) abstract;
		}

	protected:
		bool m_Disposed;

		//the destructor code
		void Destruct()
		{
			ComPointer->Release();
			ComPointer = NULL;
		}

		DirectXObject() : m_Disposed( false )
		{ }

	public:
		static property bool AutoReleaseEnabled;

		static DirectXObject()
		{
			AutoReleaseEnabled = true;
		}

		virtual ~DirectXObject()
		{
			Destruct();
		}

		!DirectXObject()
		{
			if( AutoReleaseEnabled )
			{
				Destruct();
			}
			else
			{
				Utils::ReportNotDisposed( this );
			}
		}
	};
}
