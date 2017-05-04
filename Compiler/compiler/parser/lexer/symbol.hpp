#pragma once

#include <unordered_map>

class symbol_table : public std::unordered_map<std::string, void *>
{
public:
	// Add a symbol
	void add(std::string);

	// Check if symbol exists
	bool exists(std::string);
};
