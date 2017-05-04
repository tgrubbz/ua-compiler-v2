#pragma once

#include "decl.hpp"

class context
{
public:
	context();

	decl * translation_unit;

	bool_type * bool_ty;
	int_type * int_ty;
};
