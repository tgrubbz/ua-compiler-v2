#include "conversion.hpp"
#include <exception>
#include "../ast/context.hpp"

expr * conversion::to_type(expr * e, type * t)
{
	if (e->ty == t)
	{
		return e;
	}

	e = from_ref(e);
	if (e->ty == t)
	{
		return e;
	}

	throw std::runtime_error("cannot convert expr to type");
}

expr * conversion::from_ref(expr * e)
{
	if (auto * ref = dynamic_cast<ref_type *>(e->ty))
	{
		return new deref_expr(ref->ty, e);
	}

	return e;
}

expr * conversion::to_bool(expr * e)
{
	return to_type(e, ctx->bool_ty);
}

std::pair<expr *, expr *> conversion::to_bool(expr * e1, expr * e2)
{
	return { to_bool(e1), to_bool(e2) };
}

std::pair<expr*, expr*> conversion::to_same(expr * e1, expr * e2)
{
	// TODO: check if the type of expr 1 and 2 is equal
	return { e1, e2 };
}

expr * conversion::to_arithmetic(expr * e)
{
	return to_type(e, ctx->int_ty);
}

std::pair<expr*, expr*> conversion::to_arithmetic(expr * e1, expr * e2)
{
	// TODO: check that the types are arithmetic
	// TODO: check if the type of expr 1 and 2 is equal
	return { e1, e2 };
}

expr * conversion::to_func(expr * e)
{
	e = from_ref(e);
	if (dynamic_cast<fn_type *>(e->ty))
	{
		return e;
	}

	throw std::runtime_error("expr could not be converted to a function");
}
