#pragma once

#include "../ast/expr.hpp"

class context;

class conversion
{
public:
	conversion(context * ctx) : ctx(ctx) { }
	context * ctx;
	expr * to_type(expr *, type *);
	expr * from_ref(expr *);
	expr * to_bool(expr *);
	std::pair<expr *, expr *> to_bool(expr *, expr *);
	std::pair<expr *, expr *> to_same(expr *, expr *);
	expr * to_arithmetic(expr *);
	std::pair<expr *, expr *> to_arithmetic(expr *, expr *);
	expr * to_func(expr *);
};
