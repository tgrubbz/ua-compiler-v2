#include "translator.hpp"
#include "conversion.hpp"
#include "../ast/context.hpp"


decl * translator::on_start_translation()
{
	return ctx->translation_unit;
}

decl * translator::on_finish_translation(decl * d)
{
	return d;
}

decl * translator::on_function_declaration(std::string s, std::vector<decl*> decls, type * t)
{
	return nullptr;
}

decl * translator::on_function_completion(decl *)
{
	return nullptr;
}

decl * translator::on_function_completion(decl *, stmt *)
{
	return nullptr;
}

decl * translator::on_function_parameter(type *, std::string)
{
	return nullptr;
}

decl * translator::on_function_parameter(type *)
{
	return nullptr;
}

decl * translator::on_let_declaration(type *, std::string)
{
	return nullptr;
}

decl * translator::on_let_completion(decl *, expr *)
{
	return nullptr;
}

decl * translator::on_variable_declaration(type *, std::string)
{
	return nullptr;
}

decl * translator::on_variable_completion(decl *)
{
	return nullptr;
}

decl * translator::on_variable_completion(decl *, expr *)
{
	return nullptr;
}

stmt * translator::on_block_statement(std::vector<stmt*> ss)
{
	return nullptr;
}

stmt * translator::on_if_statement(expr *, stmt *, stmt *)
{
	return nullptr;
}

stmt * translator::on_while_initiation(expr *)
{
	return nullptr;
}

stmt * translator::on_while_completion(stmt *, stmt *)
{
	return nullptr;
}

stmt * translator::on_break_statement()
{
	return nullptr;
}

stmt * translator::on_continue_statement()
{
	return nullptr;
}

stmt * translator::on_return_statement()
{
	return nullptr;
}

stmt * translator::on_return_statement(expr *)
{
	return nullptr;
}

stmt * translator::on_assert_statement(expr *)
{
	return nullptr;
}

stmt * translator::on_print_statement(expr *)
{
	return nullptr;
}

stmt * translator::on_scan_statement(expr *)
{
	return nullptr;
}

stmt * translator::on_skip_statement()
{
	return nullptr;
}

stmt * translator::on_trap_statement()
{
	return nullptr;
}

stmt * translator::on_declaration_statement(decl *)
{
	return nullptr;
}

stmt * translator::on_expression_statement(expr *)
{
	return nullptr;
}

type * translator::on_void_type(token *)
{
	return nullptr;
}

type * translator::on_bool_type(token *)
{
	return nullptr;
}

type * translator::on_int_type(token *)
{
	return nullptr;
}

type * translator::on_nat_type(token *)
{
	return nullptr;
}

type * translator::on_reference_type(type *)
{
	return nullptr;
}

type * translator::on_function_type(type *)
{
	return nullptr;
}

type * translator::on_function_type(std::vector<type*>, type *)
{
	return nullptr;
}

type * translator::on_buffer_type(type *)
{
	return nullptr;
}

type * translator::on_array_type(type *, expr *)
{
	return nullptr;
}

expr * translator::on_assign_expression(expr * e1, expr * e2)
{
	type * t = e1->ty;
	if (dynamic_cast<ref_type *>(t))
	{
		e2 = convert->from_ref(e1);
		return new assignment_expr(t, e1, e2);
	}
	
	throw std::runtime_error("expr is not ref_type");
}

expr * translator::on_cond_expression(expr * e1, expr * e2, expr * e3)
{
	expr * conv_expr = convert->to_bool(e1);
	std::pair<expr *, expr *> pair_expr = convert->to_same(e2, e3);
	return new cond_expr(pair_expr.first->ty, conv_expr, pair_expr.first, pair_expr.second);
}

expr * translator::on_logical_and_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_bool(e1, e2);
	return new and_then_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_logical_or_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_bool(e1, e2);
	return new or_else_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_or_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_bool(e1, e2);
	return new or_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_xor_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_bool(e1, e2);
	return new or_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_and_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_bool(e1, e2);
	return new and_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_lt_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new less_than_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_gt_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new greater_than_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_le_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new less_than_eq_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_ge_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new greater_than_eq_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_eq_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new equal_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_ne_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new not_equal_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_add_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new add_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_sub_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new sub_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_mul_expression(expr * e1, expr * e2) 
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new multi_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_div_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new div_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_rem_expression(expr * e1, expr * e2)
{
	std::pair<expr *, expr *> pair_expr = convert->to_arithmetic(e1, e2);
	return new rem_expr(pair_expr.first->ty, pair_expr.first, pair_expr.second);
}

expr * translator::on_neg_expression(expr * e)
{
	expr * conv_expr = convert->to_arithmetic(e);
	return new neg_expr(conv_expr->ty, conv_expr);
}

expr * translator::on_not_expression(expr * e)
{
	expr * conv_expr = convert->to_bool(e);
	return new neg_expr(conv_expr->ty, conv_expr);
}

expr * translator::on_call_expression(expr * e, std::vector<expr*> exprs)
{
	e = convert->to_func(e);
	if (auto * t = dynamic_cast<fn_type *>(e->ty))
	{
		// TODO: do some parameter stuff
		return new f_call_expr(t->ret, e, exprs);
	}

	throw std::runtime_error("expression is not a function type");
}

expr * translator::on_true_literal(token * t)
{
	return new bool_expr(ctx->bool_ty, true);
}

expr * translator::on_false_literal(token * t)
{
	return new bool_expr(ctx->bool_ty, false);
}

expr * translator::on_integer_literal(token * t)
{
	int_token * integer = static_cast<int_token *>(t);
	return new int_expr(ctx->int_ty, integer->val);
}

expr * translator::on_id_expression(std::string s)
{
	std::vector<decl *> decls;

	// TODO: Lookup in decls with the given name in the scope

	return on_id_expression(decls.front());
}

expr * translator::on_id_expression(decl * d)
{
	// Check if it is a var_decl
	if (var_decl * vd = dynamic_cast<var_decl *>(d))
	{
		return new reference_expr(d->ty, vd);
	}

	throw new std::runtime_error("decl was not a var_decl");
}

std::string translator::on_identifier(token * t)
{
	id_token * id = dynamic_cast<id_token *>(t);
	return id->name();
}

void translator::bind(decl * d)
{
	bind(d, current_scope());
}

void translator::bind(decl * d, scope * s)
{
	if (auto * item = env.lookup(d->name)) {
		throw std::runtime_error("name already exists in scope");
	}

	env.add(d, s);
}

void translator::declare(decl * d)
{
	declare(d, current_scope());
}

void translator::declare(decl * d, scope * s)
{
	bind(d, s);
}

std::vector<decl*> translator::lookup(std::string)
{
	return std::vector<decl*>();
}
