#include "pch.hpp"

attr_inline Logger & End ( Logger & log )
{
	std::cout << std::endl;
	return log;
}

attr_inline Logger & Log ( )
{
	static auto log = Logger ( );
	return log;
}
