#pragma once

#include "type.hpp"

// Forward declarations
#pragma region declarations
class decl;

class bool_expr;
class and_expr;
class or_expr;
class xor_expr;
class not_expr;
class cond_expr;
class equal_expr;
class not_equal_expr;
class less_than_expr;
class greater_than_expr;
class less_than_eq_expr;
class greater_than_eq_expr;
class and_then_expr;
class or_else_expr;
class int_expr;
class add_expr;
class sub_expr;
class multi_expr;
class div_expr;
class rem_expr;
class neg_expr;
class assignment_expr;
class reference_expr;
class deref_expr;
class f_call_expr;

#pragma endregion

// Base expression class
class expr
{
public:
	type * ty;
	class visitor;
	virtual void accept(visitor &) = 0;

	expr(type * t) : ty(t) { }
	virtual ~expr() = default;

};

// Expression visistor
class expr::visitor
{
public:
	virtual void visit(bool_expr *) = 0;
	virtual void visit(and_expr *) = 0;
	virtual void visit(or_expr *) = 0;
	virtual void visit(xor_expr *) = 0;
	virtual void visit(not_expr *) = 0;
	virtual void visit(cond_expr *) = 0;
	virtual void visit(equal_expr *) = 0;
	virtual void visit(not_equal_expr *) = 0;
	virtual void visit(less_than_expr *) = 0;
	virtual void visit(greater_than_expr *) = 0;
	virtual void visit(less_than_eq_expr *) = 0;
	virtual void visit(greater_than_eq_expr *) = 0;
	virtual void visit(and_then_expr *) = 0;
	virtual void visit(or_else_expr *) = 0;
	virtual void visit(int_expr *) = 0;
	virtual void visit(add_expr *) = 0;
	virtual void visit(sub_expr *) = 0;
	virtual void visit(multi_expr *) = 0;
	virtual void visit(div_expr *) = 0;
	virtual void visit(rem_expr *) = 0;
	virtual void visit(neg_expr *) = 0;
	virtual void visit(assignment_expr *) = 0;
	virtual void visit(reference_expr *) = 0;
	virtual void visit(deref_expr *) = 0;
	virtual void visit(f_call_expr *) = 0;
};

// Boilerplate expressions
#pragma region boilerplate

class null_expr : public expr
{
public:
	null_expr(type * t) : expr(t) { }

};

class unary_expr : public expr
{
public:
	unary_expr(type * t, expr * e1) : expr(t), sub{ e1 } { }
	~unary_expr() { delete sub[0]; }

	expr * sub[1];

};

class binary_expr : public expr
{
public:
	binary_expr(type * t, expr * e1, expr * e2) : expr(t), sub{ e1, e2 } { }
	~binary_expr() { for (expr* e : sub) delete e; }

	expr* sub[2];

};

class ternary_expr : public expr
{
public:
	ternary_expr(type * t, expr * e1, expr * e2, expr * e3) : expr(t), sub{ e1, e2, e3 } { }
	~ternary_expr() { for (expr* e : sub) delete e; }

	expr* sub[3];

};

#pragma endregion

// Boolean expressions
#pragma region boolean

class bool_expr : public null_expr
{
public:
	bool val;

	bool_expr(type * t, bool val) : val(val), null_expr(t) { }
	~bool_expr() = default;

	void accept(visitor & v) { return v.visit(this); };

};

class and_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class or_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class xor_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class not_expr : public unary_expr
{
public:
	using unary_expr::unary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class cond_expr : public ternary_expr
{
public:
	using ternary_expr::ternary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class equal_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class not_equal_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class less_than_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class greater_than_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class less_than_eq_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class greater_than_eq_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class and_then_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class or_else_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

#pragma endregion

// Integer expressions
#pragma region integer

class int_expr : public null_expr
{
public:
	int val;

	int_expr(type * t, int val) : val(val), null_expr(t) { }
	~int_expr() = default;

	void accept(visitor & v) { return v.visit(this); };

};

class add_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class sub_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class multi_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class div_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class rem_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

class neg_expr : public unary_expr
{
public:
	using unary_expr::unary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

#pragma endregion

// Storage expressions
#pragma region storage

// Assignment expression
// e1 = e2
class assignment_expr : public binary_expr
{
public:
	using binary_expr::binary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

// Reference expression
// Refers to a named declaration
class reference_expr : public null_expr
{
public:
	decl * ref;

	reference_expr(type* t, decl* d) : null_expr(t), ref(d) { }

	void accept(visitor & v) { return v.visit(this); };
};

// Evaluation expression
// Dereference?
// *e1 ?
class deref_expr : public unary_expr
{
public:
	using unary_expr::unary_expr;

	void accept(visitor & v) { return v.visit(this); };
};

// Initialize expression
// var int x = 0;
//class initialize_expr : public unary_expr
//{
//public:
//	value_decl * d;
//	evaluation_expr(type * t, value_decl * d, expr * e) : unary_expr(t, e) { }
//
//	void accept(visitor & v) { return v.visit(this); };
//};

class f_call_expr : public expr
{
public:
	expr * func;
	std::vector<expr *> args;

	f_call_expr(type * t, expr * f, std::vector<expr *> args) : expr(t), func(f), args(args) { }

	void accept(visitor & v) { return v.visit(this); };
};

#pragma endregion

#pragma region visFuncs

static int convert(bool val) { return val ? 1 : 0; }

static int eval_expr(expr * e)
{
	// Derived expression visitor class
	// Overloaded visit function for each of the expression types
	// Part of the visitor pattern 
	class v : public expr::visitor
	{
	public:
		int val;
		void visit(bool_expr * e) { val = convert(e->val); }
		void visit(int_expr * e) { val = e->val; }
		void visit(and_expr * e) { val = convert(eval_expr(e->sub[0]) & eval_expr(e->sub[1])); }
		void visit(or_expr * e) { val = convert(eval_expr(e->sub[0]) | eval_expr(e->sub[1])); }
		void visit(xor_expr * e) { val = convert(eval_expr(e->sub[0]) ^ eval_expr(e->sub[1])); }
		void visit(not_expr * e) { val = convert(!eval_expr(e->sub[0])); }
		void visit(cond_expr * e) { val = (eval_expr(e->sub[0]) ? eval_expr(e->sub[1]) : eval_expr(e->sub[2])); }
		void visit(equal_expr * e) { val = convert(eval_expr(e->sub[0]) == eval_expr(e->sub[1])); }
		void visit(not_equal_expr * e) { val = convert(eval_expr(e->sub[0]) != eval_expr(e->sub[1])); }
		void visit(less_than_expr * e) { val = convert(eval_expr(e->sub[0]) < eval_expr(e->sub[1])); }
		void visit(greater_than_expr * e) { val = convert(eval_expr(e->sub[0]) > eval_expr(e->sub[1])); }
		void visit(less_than_eq_expr * e) { val = convert(eval_expr(e->sub[0]) <= eval_expr(e->sub[1])); }
		void visit(greater_than_eq_expr * e) { val = convert(eval_expr(e->sub[0]) >= eval_expr(e->sub[1])); }
		void visit(add_expr * e) { val = eval_expr(e->sub[0]) + eval_expr(e->sub[1]); }
		void visit(sub_expr * e) { val = eval_expr(e->sub[0]) - eval_expr(e->sub[1]); }
		void visit(multi_expr * e) { val = eval_expr(e->sub[0]) * eval_expr(e->sub[1]); }
		void visit(div_expr * e) { val = eval_expr(e->sub[0]) / eval_expr(e->sub[1]); }
		void visit(rem_expr * e) { val = eval_expr(e->sub[0]) % eval_expr(e->sub[1]); }
		void visit(neg_expr * e) { val = -eval_expr(e->sub[0]); }
		void visit(and_then_expr * e) { val = eval_expr(e->sub[0]) == 1 ? eval_expr(e->sub[1]) : 0; }
		void visit(or_else_expr * e) { val = 1 == 1 ? eval_expr(e->sub[0]) : eval_expr(e->sub[1]); }
		void visit(assignment_expr * e) { val = 0; };
		void visit(reference_expr * e) { val = 0; };
		void visit(deref_expr * e) { val = 0; };
		void visit(f_call_expr * e) { val = 0; };
	};

	// Create v (derived from visitor)
	v vis;

	// Call the expression argument's accept function with the (v) argument
	e->accept(vis);

	// Return the value of v
	// This is set in the corrsponding overloaded visit function defined in class v
	return vis.val;
}

#pragma endregion

