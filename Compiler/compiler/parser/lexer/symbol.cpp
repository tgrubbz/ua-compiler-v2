
#include "symbol.hpp"

void symbol_table::add(std::string s)
{	
	if (!exists(s))
	{
		insert({ s, nullptr });
	}
}

bool symbol_table::exists(std::string s)
{
	return find(s) == end();
}
