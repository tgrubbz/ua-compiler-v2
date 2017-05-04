#include "stmt.hpp"

stmt::stmt()
{
}

expr_stmt::expr_stmt(expr * e)
	:e(e)
{
}

decl_stmt::decl_stmt(decl * d)
	:d(d)
{
}
