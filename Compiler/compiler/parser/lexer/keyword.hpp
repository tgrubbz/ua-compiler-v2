#pragma once

#include "token.hpp"
#include <unordered_map>

class keyword_table : public std::unordered_map<std::string, token_kind>
{
public:
	keyword_table();

};
