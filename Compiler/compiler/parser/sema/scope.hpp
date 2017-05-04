#pragma once

#include "../ast/decl.hpp"
#include "../lexer/symbol.hpp"

enum scope_kind
{
	module,
	function_param,
	function,
	block
};

class scope : public std::vector<decl *>
{
public:
	scope(scope_kind kind, scope * parent) : kind(kind), parent(parent) { }
	virtual ~scope() = default;

	scope_kind kind;
	scope * parent;

};
