#pragma once

#include "expr.hpp"
#include "decl.hpp"

class stmt
{
public:
	stmt();
	virtual ~stmt() = default;

};

class block_stmt : public stmt
{
public:
	block_stmt() = default;
	block_stmt(std::vector<stmt *> stmts) : stmts(stmts) { }

	std::vector<stmt *> stmts;
};

class if_stmt : public stmt
{
public:
	if_stmt(expr * e, stmt * t, stmt * f) : cond(e), true_block(t), false_block(f) { }
	
	expr * cond;
	stmt * true_block;
	stmt * false_block;
};

class while_stmt : public stmt
{
public:
	while_stmt(expr * e, stmt * s) : cond(e), body(s) { }
	
	expr * cond;
	stmt * body;
};

class break_stmt : public stmt
{
public:
	using stmt::stmt;
};

class continue_stmt : public stmt
{
public:
	using stmt::stmt;
};

class return_stmt : public stmt
{
public:
	return_stmt(expr * e) : ret(e) { }

	expr * ret;
};

class expr_stmt : public stmt
{
public:
	expr_stmt(expr * e) : e(e) { }

	expr * e;
};

class decl_stmt : public stmt
{
public:
	decl_stmt(decl * d) : d(d) { }

	decl * d;
};
