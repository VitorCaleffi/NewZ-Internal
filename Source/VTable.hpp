#pragma once

enum CallingConvention
{
	StdCall,
	FastCall,
	ThisCall
};

template <int index, CallingConvention conv, typename return_t, typename... forward_args_t>
class VTableHook
{
public:
	VTableHook ( Address _class, Address _new ) :
		mNewFunction ( _new ), mOldFunction ( *reinterpret_cast< Address** >( mClass )[index] ), mClass ( _class )
	{
	}

	~VTableHook ( )
	{
	}


	return_t CallOriginal ( forward_args_t... args ) const
	{
		if ( conv == CallingConvention::StdCall )
			return static_cast< return_t ( __stdcall* )( forward_args_t... ) >( mOldFunction )( args );
		if ( conv == CallingConvention::FastCall )
			return static_cast< return_t ( __fastcall* )( forward_args_t... ) >( mOldFunction )( args );
		if ( conv == CallingConvention::ThisCall )
			return static_cast< return_t ( __thiscall* )( Address _thisptr, forward_args_t... ) >( mOldFunction )( mClass, args );
		return return_t ( );
	}

	void Unhook ( )
	{
		auto vtable = *reinterpret_cast< Address** >( mClass );

		unsigned long old = 0;
		VirtualProtect ( &vtable [ index ], sizeof ( Address ), PAGE_EXECUTE_READWRITE, &old );

		vtable [ index ] = mOldFunction;

		unsigned long old2 = 0;
		VirtualProtect ( &vtable [ index ], sizeof ( Address ), old, &old2 );
	}

	void Hook ( )
	{
		auto vtable = *reinterpret_cast< Address** >( mClass );
		
		unsigned long old = 0;
		VirtualProtect ( &vtable [ index ], sizeof ( Address ), PAGE_EXECUTE_READWRITE, &old );

		vtable [ index ] = mNewFunction;

		unsigned long old2 = 0;
		VirtualProtect ( &vtable [ index ], sizeof ( Address ), old, &old2 );
	}


	attr_alwaysinline return_t operator () ( forward_args_t... args )
	{
		return CallOriginal ( );
	}

private:
	Address mNewFunction;
	Address mOldFunction;
	Address mClass;
};
