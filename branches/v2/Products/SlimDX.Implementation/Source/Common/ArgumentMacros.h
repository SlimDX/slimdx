
#define SDX_THROW_IF_NULL( x ) ThrowIfNull( x, #x )

#define SDX_RECORD_HR( x ) Record( x )

#define SDX_RETURN( t, x ) return x == 0 ? nullptr : gcnew t( x )

inline SlimDX::Result Record( HRESULT hr ) 
{
	return SlimDX::Result( hr );
}

template< typename T >
void ThrowIfNull( T^ argument, const char* argumentName )
{
	if( argument == nullptr )
	{
		throw gcnew System::ArgumentNullException( gcnew System::String( argumentName ) );
	}
}

inline void ThrowIfNull( System::IntPtr argument, const char* argumentName ) 
{
	if( argument == System::IntPtr::Zero )
	{
		throw gcnew System::ArgumentNullException( gcnew System::String( argumentName ) );
	}
}