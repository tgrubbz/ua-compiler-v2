#pragma once

#include "expr.hpp"
#include "decl.hpp"

class stmt
{
public:
	stmt();
	virtual ~stmt() = default;

};

class expr_stmt : public stmt
{
public:
	expr_stmt(expr * e);

	expr * e;

};

class decl_stmt : public stmt
{
public:
	decl_stmt(decl * d);

	decl * d;

};
