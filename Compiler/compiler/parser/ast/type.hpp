#pragma once

#include <vector>

// Base type class
class type
{
public:
	type() = default;
	virtual ~type() = default;

};

class bool_type : public type { };

class int_type : public type { };

class ref_type : public type
{
public:
	type * ty;

	ref_type(type * t) : type(), ty(t) { }

};

class fn_type : public type
{
public:
	std::vector<type *> args;
	type * ret;

	fn_type(std::vector<type *> args, type * ret) : args(args), ret(ret) { }

};
