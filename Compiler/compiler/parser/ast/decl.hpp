#pragma once

#include "type.hpp"
#include "expr.hpp"

class decl
{
public:
	decl(std::string, type *);
	virtual ~decl() = default;

	std::string name;
	type * ty;

};

class var_decl : public decl
{
public:
	var_decl(std::string, type *, expr *);

	expr * e;

};

//class param_decl : public decl
//{
//
//};
//
//class func_decl : public decl
//{
//
//};
