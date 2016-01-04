#pragma once

#include <string>
#include <stdint.h>

#include <iostream>

#include "macro.hpp"

class Logger
{
public:
	Logger ( ){}
	~Logger ( ){}

	attr_alwaysinline Logger& operator << ( const char* text )
	{
#ifdef DOLOG
		std::cout << text;
#endif
		return *this;
	}

	attr_alwaysinline Logger& operator << ( const std::string& text )
	{
#ifdef DOLOG
		std::cout << text;
#endif
		return *this;
	}

	attr_alwaysinline Logger& operator << ( const int8_t num )
	{
#ifdef DOLOG
		std::cout << num;
#endif
		return *this;
	}

	attr_alwaysinline Logger& operator << ( const int16_t num )
	{
#ifdef DOLOG
		std::cout << num;
#endif
		return *this;
	}

	attr_alwaysinline Logger& operator << ( const int32_t num )
	{
#ifdef DOLOG
		std::cout << num;
#endif
		return *this;
	}

	attr_alwaysinline Logger& operator << ( const uint8_t num )
	{
#ifdef DOLOG
		auto flags = std::cout.flags ( );
		std::cout.setf ( std::ios::hex | std::ios::uppercase | std::ios::showbase );
		std::cout << num;
		std::cout.setf ( flags );
#endif
		return *this;			
	}							
								
	attr_alwaysinline Logger& operator << ( const uint16_t num )
	{
#ifdef DOLOG
		auto flags = std::cout.flags ( );
		std::cout.setf ( std::ios::hex | std::ios::uppercase | std::ios::showbase );
		std::cout << num;
		std::cout.setf ( flags );
#endif
		return *this;			
	}							
								
	attr_alwaysinline Logger& operator << ( const uint32_t num )
	{
#ifdef DOLOG
		auto flags = std::cout.flags ( );
		std::cout.setf ( std::ios::hex | std::ios::uppercase | std::ios::showbase );
		std::cout << num;
		std::cout.setf ( flags );
#endif
		return *this;
	}

	attr_alwaysinline Logger& operator << ( const void* uptr )
	{
#ifdef DOLOG
		auto flags = std::cout.flags ( );
		std::cout.setf ( std::ios::hex | std::ios::uppercase | std::ios::showbase );
		std::cout << uptr;
		std::cout.setf ( flags );
#endif
		return *this;
	}

	attr_alwaysinline Logger& operator << ( const nullptr_t )
	{
#ifdef DOLOG
		std::cout << std::endl;
#endif
		return *this;
	}
};

extern attr_inline Logger& End ( Logger& log );
extern attr_inline Logger& Log ( );
