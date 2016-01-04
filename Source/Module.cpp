#include "pch.hpp"

Address GetModuleSize ( const Address base )
{
	auto dos_header = reinterpret_cast< IMAGE_DOS_HEADER* >( base );
	auto nt_header = reinterpret_cast< IMAGE_NT_HEADERS* >( base + dos_header->e_lfanew );
	return nt_header->OptionalHeader.SizeOfImage;
}
