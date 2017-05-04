#pragma once

#include <iostream>
#include <string>
#include "parser\parser.hpp"

int main(int argc, char * argv[])
{
	std::string s;
	keyword_table * kw_tbl = new keyword_table();
	symbol_table * sym_tbl = new symbol_table();
	context * ctx = new context();
	parser prsr(kw_tbl, sym_tbl, ctx);

	while (getline(std::cin, s))
	{		
		prsr.parse(s);
	}

	return 0;
}
