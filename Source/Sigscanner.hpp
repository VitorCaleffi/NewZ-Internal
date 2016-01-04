#pragma once

/* @Credits
 *  - ChaosLeader
 */

#include <vector>

#include "types.hpp"

enum class PatternType
{
	Offset,
	Address,
	Pointer,
	Pointer8,
	Pointer16,
	Pointer32,
	Pointer64,
	RelativePointer,
	RelativePointer8,
	RelativePointer16,
	RelativePointer32,
	RelativePointer64,
};

typedef struct
{
	char *pattern;
	PatternType type;
} Pattern;

class PatternScanner
{
private:
	template <typename T, typename ret> static ret ResolveRelativePtr ( void *addr )
	{
		if ( addr == nullptr )
			return nullptr;

		T offset = *static_cast< T* >( addr );
		if ( offset == 0 )
			return nullptr;

		return ret ( reinterpret_cast<Address>( addr ) + offset + sizeof ( T ) );
	}

	template <typename T> static void *ResolveRelativePtr ( void *Address )
	{
		return ResolveRelativePtr<T, void*> ( Address );
	}

	template <typename T, typename ret> static ret ResolvePtr ( void *Address )
	{
		if ( Address == nullptr )
			return nullptr;

		return reinterpret_cast<ret >( *static_cast<T* >( Address ) );
	}

	template <typename T> static void *ResolvePtr ( void *Address )
	{
		return ResolvePtr<T, void*> ( Address );
	}

public:
	static void *FindPattern ( void *startAddress, DWORD searchSize, const Pattern &pattern );
	static void *FindPattern ( const std::string &ModuleName, const Pattern &pattern );
	static std::vector<void*> FindPatterns ( const std::string &ModuleName, const Pattern &pattern );
	static std::vector<void*> FindPatterns ( void *startAddress, DWORD searchSize, const Pattern &pattern );
	static void *FindPattern ( void *startAddress, DWORD searchSize, Pattern *patterns, float *ratio = nullptr );
	static void *FindPattern ( const std::string &ModuleName, Pattern *patterns, float *ratio = nullptr );
};

extern attr_alwaysinline Pattern DoNotContinue ( );