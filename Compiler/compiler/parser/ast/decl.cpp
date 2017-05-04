#include "decl.hpp"

decl::decl(std::string s, type * t)
	:name(s), ty(t)
{
}

var_decl::var_decl(std::string s, type * t)
	: decl(s, t)
{
}

var_decl::var_decl(std::string s, type * t, expr * e)
	:decl(s, t), e(e)
{
}
