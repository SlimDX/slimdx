#include "stdafx.h"

#include "Utilities.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;

namespace SlimDX
{
	static Utilities::Utilities()
	{
		m_Implementations = gcnew Dictionary<Type^,Type^>();
		m_IIDs = gcnew Dictionary<Type^,Guid>();
		
		Type^ attributeType = Type::GetType( Assembly::CreateQualifiedName( "SlimDX", "SlimDX.InterfaceIDAttribute" ) );
		Assembly^ publicAssembly = Assembly::GetAssembly( attributeType );
		Assembly^ privateAssembly = Assembly::GetExecutingAssembly();
		
		for each( Type^ type in publicAssembly->GetTypes() )
		{		
			for each( Object^ attribute in type->GetCustomAttributes(false) )
			{
				if( attribute->GetType() == attributeType )
				{
					InterfaceIDAttribute^ interfaceID = safe_cast<InterfaceIDAttribute^>( attribute );
					if( interfaceID->Value != Guid::Empty )
					{
						// Strip the leading 'I' off the interface name, then find that type.
						String^ implementationName = type->Name->Substring( 1 );
						Type^ implementation = privateAssembly->GetType( String::Format("{0}.{1}", type->Namespace, implementationName ) );
						if( implementation != nullptr )
						{
							m_Implementations->Add( type, implementation );
							m_IIDs->Add( type, interfaceID->Value ); 
						}
					}
				}
			}
		}
	}

	generic< typename T >
	Guid Utilities::GetInterfaceID()
	{
		Guid result = Guid::Empty;
		if( m_IIDs->TryGetValue( T::typeid, result ) )
			return result;
	
		throw gcnew NotImplementedException();	
	}
	
	generic< typename T >
	Type^ Utilities::GetInterfaceImplementation()
	{
		Type^ result = nullptr;
		if( m_Implementations->TryGetValue( T::typeid, result ) )
			return result;
	
		throw gcnew NotImplementedException();	
	}
	
	IUnknown* Utilities::ToUnknown( IComObject^ source )
	{
		return static_cast<IUnknown*>( source->UnknownPointer.ToPointer() );
	}
	
	DXGI_MODE_DESC Utilities::ToNative( SlimDX::DXGI::DisplayModeDescription^ source )
	{
		DXGI_MODE_DESC result;
		result.Width = source->Width;
		result.Height = source->Height;
		result.RefreshRate = ToNative( source->RefreshRate );
		result.Format = static_cast<DXGI_FORMAT>( source->Format );
		result.ScanlineOrdering = static_cast<DXGI_MODE_SCANLINE_ORDER>( source->ScanlineOrdering );
		result.Scaling = static_cast<DXGI_MODE_SCALING>( source->Scaling );
		return result;
	}
	
	DXGI_RATIONAL Utilities::ToNative( SlimDX::DXGI::Rational source )
	{
		DXGI_RATIONAL result;
		result.Numerator = source.Numerator;
		result.Denominator = source.Denominator;
		return result;
	}
	
	DXGI_SAMPLE_DESC Utilities::ToNative( SlimDX::DXGI::SampleDescription^ source )
	{
		DXGI_SAMPLE_DESC result;
		result.Count = source->Count;
		result.Quality = source->Quality;
		return result;
	}
	
	DXGI_SWAP_CHAIN_DESC Utilities::ToNative( SlimDX::DXGI::SwapChainDescription^ source )
	{
		DXGI_SWAP_CHAIN_DESC result;
		result.BufferDesc = ToNative( source->BufferDescription );
		result.SampleDesc = ToNative( source->SampleDescription );
		result.BufferUsage = static_cast<DXGI_USAGE>( source->BufferUsage );
		result.BufferCount = source->BufferCount;
		result.OutputWindow = static_cast<HWND>( source->OutputWindow.ToPointer() );
		result.Windowed = source->IsWindowed;
		result.SwapEffect = static_cast<DXGI_SWAP_EFFECT>( source->SwapEffect );
		result.Flags = static_cast<UINT>( source->Flags );
		return result;
	}	
	
	Guid Utilities::ToManaged( const GUID& guid )
	{
		if( guid == GUID_NULL )
			return Guid::Empty;

		Guid result(
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0],
			guid.Data4[1],
			guid.Data4[2], 
			guid.Data4[3],
			guid.Data4[4],
			guid.Data4[5],
			guid.Data4[6],
			guid.Data4[7]
		);

		return result;
	}

	GUID Utilities::ToNative( Guid guid )
	{
		if( guid == Guid::Empty )
			return GUID_NULL;

		GUID result;
		array<Byte>^ bytes = guid.ToByteArray();
		pin_ptr<unsigned char> pinned_bytes = &bytes[0];
		memcpy( &result, pinned_bytes, sizeof(GUID) );

		return result;
	}
}