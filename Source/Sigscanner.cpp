#include "pch.hpp"

void *PatternScanner::FindPattern ( const std::string &ModuleName, const Pattern &pattern )
{
	auto base = GetModuleHandle ( ModuleName.c_str ( ) );
	return PatternScanner::FindPattern ( base, GetModuleSize ( Address ( base ) ), pattern );
}

std::vector<void*> PatternScanner::FindPatterns ( const std::string &ModuleName, const Pattern &pattern )
{
	auto base = GetModuleHandle ( ModuleName.c_str ( ) );
	return PatternScanner::FindPatterns ( base, GetModuleSize ( Address ( base ) ), pattern );
}

std::vector<void*> PatternScanner::FindPatterns ( void *startAddress, DWORD searchSize, const Pattern &pattern )
{
	std::vector<void*> ret;

	auto base = startAddress;
	auto size = searchSize;
	auto addr = base;
	do
	{
		addr = PatternScanner::FindPattern ( reinterpret_cast< void* >( Address ( addr ) + 1 ), 
											 size - ( Address ( addr ) - Address ( base ) + 1 ), pattern );
		if ( addr )
			ret.push_back ( addr );
	} while ( addr != nullptr );

	return ret;
}

void *PatternScanner::FindPattern ( void *startAddress, DWORD searchSize, const Pattern &pattern )
{
	auto len = strlen ( pattern.pattern );
	if ( len == 0 )
		return nullptr;

	Address pos = 0;

	auto byteCount = 1;

	for ( Address i = 0, max = len - 1; i < max; i++ )
	{
		if ( pattern.pattern [ i ] == ' ' )
			byteCount++;
	}

	auto patt = new uint8_t [ byteCount + 1 ];
	auto mask = new uint8_t [ byteCount + 1 ];

	auto offset = 0, bytesCounted = 0;
	for ( auto i = 0, max = static_cast< int >( len - 1 ); i < max; i++ )
	{
		if ( pattern.pattern [ i ] == '[' )
		{
			i++;
			offset = bytesCounted;
		}

		if ( pattern.pattern [ i ] == '\0' )
			break;

		if ( pattern.pattern [ i ] == '?' && pattern.pattern [ i + 1 ] == '?' )
		{
			mask [ bytesCounted ] = '?';
			patt [ bytesCounted ] = '\0';
		}
		else
		{
			byte hn = pattern.pattern [ i ] > '9' ? pattern.pattern [ i ] - 'A' + 10 : pattern.pattern [ i ] - '0';
			byte ln = pattern.pattern [ i + 1 ] > '9' ? pattern.pattern [ i + 1 ] - 'A' + 10 : pattern.pattern [ i + 1 ] - '0';
			byte n = ( hn << 4 ) | ln;

			mask [ bytesCounted ] = 'x';
			patt [ bytesCounted ] = n;
		}

		bytesCounted++;

		for ( i += 2; i < len && (
			pattern.pattern [ i ] == ' ' ||
			pattern.pattern [ i ] == '\t' ||
			pattern.pattern [ i ] == '\r' ||
			pattern.pattern [ i ] == '\n'
			); i++ );
	}

	mask [ bytesCounted ] = '\0';

	auto searchLen = strlen ( reinterpret_cast<char* >(&mask [ 0 ]) ) - 1;

	void *ret = nullptr;

	for ( auto retAddress = Address ( startAddress ); retAddress < 
		  Address ( startAddress ) + searchSize; retAddress++ )
	{
		__try
		{
			if ( *reinterpret_cast<byte* >(retAddress) == patt [ pos ] || mask [ pos ] == '?' )
			{
				if ( mask [ pos + 1 ] == '\0' )
				{
					ret = reinterpret_cast<void* >(retAddress - searchLen + offset);
					break;
				}

				pos++;
			}
			else
				pos = 0;
		}
		__except ( EXCEPTION_EXECUTE_HANDLER )
		{
			pos = 0;
		}
	}

	free ( patt );
	free ( mask );

	switch ( pattern.type )
	{
		case PatternType::Pointer:
			ret = ResolvePtr<Address> ( ret );
			break;

		case PatternType::Pointer8:
			ret = ResolvePtr<uint8_t> ( ret );
			break;

		case PatternType::Pointer16:
			ret = ResolvePtr<uint16_t> ( ret );
			break;

		case PatternType::Pointer32:
			ret = ResolvePtr<uint32_t> ( ret );
			break;

		case PatternType::Pointer64:
			ret = ResolvePtr<uint64_t> ( ret );
			break;

		case PatternType::RelativePointer:
			ret = ResolveRelativePtr<uint32_t> ( ret );
			break;

		case PatternType::RelativePointer8:
			ret = ResolveRelativePtr<uint8_t> ( ret );
			break;

		case PatternType::RelativePointer16:
			ret = ResolveRelativePtr<uint16_t> ( ret );
			break;

		case PatternType::RelativePointer32:
			ret = ResolveRelativePtr<uint32_t> ( ret );
			break;

		case PatternType::RelativePointer64:
			ret = ResolveRelativePtr<uint64_t> ( ret );
			break;
		case PatternType::Offset:
			break;
		case PatternType::Address:
			break;

		default:
			break;
	}

	return ret;
}

void *PatternScanner::FindPattern ( void *startAddress, DWORD searchSize, Pattern *patterns, float *ratio )
{
	auto totalCount = 0;
	typedef struct
	{
		void *addr;
		int count;
	} result;
	std::list<result> results;

	auto bestCount = 0;
	void *ret = nullptr;

	while ( true )
	{
		auto pattern = patterns [ totalCount ];

		totalCount++;

		auto addr = PatternScanner::FindPattern ( startAddress, searchSize, pattern );

		if ( !addr )
			continue;

		auto found = false;
		for ( auto &res : results )
		{
			if ( res.addr == addr )
			{
				res.count++;
				if ( res.count > bestCount )
				{
					ret = addr;
					bestCount = res.count;
				}
				found = true;
				break;
			}
		}

		if ( !found )
		{
			result res =
			{
				addr,
				1
			};
			results.push_back ( res );
			if ( bestCount == 0 )
			{
				bestCount = 1;
				ret = addr;
			}
		}
	}

	if ( ratio )
		*ratio = static_cast<float >(bestCount) / totalCount;

	return ret;
}

void *PatternScanner::FindPattern ( const std::string &ModuleName, Pattern *patterns, float *ratio )
{
	auto base = GetModuleHandle ( ModuleName.c_str ( ) );
	return PatternScanner::FindPattern ( base, GetModuleSize ( Address ( base ) ), patterns, ratio );
}

attr_alwaysinline Pattern DoNotContinue ( )
{
	static Pattern pat = { nullptr, PatternType::Address };
	return pat;
}
