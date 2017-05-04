#pragma once

#include "../ast/decl.hpp"
#include "../ast/expr.hpp"
#include "../ast/stmt.hpp"
#include "../lexer/token.hpp"
#include "enviornment.hpp"

class context;
class conversion;
class stmt;

class translator
{
public:
	translator(context * ctx, conversion * convert) : ctx(ctx), convert(convert) { }

	// on declarations

	decl * on_start_translation();
	decl * on_finish_translation(decl *);

	decl * on_function_declaration(std::string, std::vector<decl *>, type *);
	decl * on_function_completion(decl *);
	decl * on_function_completion(decl *, stmt *);
	decl * on_function_parameter(type *, std::string);
	decl * on_function_parameter(type *);

	decl * on_let_declaration(type *, std::string);
	decl * on_let_completion(decl *, expr *);

	decl * on_variable_declaration(type *, std::string);
	decl * on_variable_completion(decl *);
	decl * on_variable_completion(decl *, expr *);

	// on statements

	stmt * on_block_statement(std::vector<stmt *>);
	stmt * on_if_statement(expr *, stmt *, stmt *);
	stmt * on_while_initiation(expr *);
	stmt * on_while_completion(stmt *, stmt *);
	stmt * on_break_statement();
	stmt * on_continue_statement();
	stmt * on_return_statement();
	stmt * on_return_statement(expr *);
	stmt * on_assert_statement(expr *);
	stmt * on_print_statement(expr *);
	stmt * on_scan_statement(expr *);
	stmt * on_skip_statement();
	stmt * on_trap_statement();
	stmt * on_declaration_statement(decl *);
	stmt * on_expression_statement(expr *);

	// on types

	type * on_void_type(token *);
	type * on_bool_type(token *);
	type * on_int_type(token *);
	type * on_nat_type(token *);
	type * on_reference_type(type *);
	type * on_function_type(type *);
	type * on_function_type(std::vector<type *>, type *);
	type * on_buffer_type(type *);
	type * on_array_type(type *, expr *);

	// on expressions

	expr * on_assign_expression(expr *, expr *);
	expr * on_cond_expression(expr *, expr *, expr *);
	expr * on_logical_and_expression(expr *, expr *);
	expr * on_logical_or_expression(expr *, expr *);
	expr * on_or_expression(expr *, expr *);
	expr * on_xor_expression(expr *, expr *);
	expr * on_and_expression(expr *, expr *);
	expr * on_lt_expression(expr *, expr *);
	expr * on_gt_expression(expr *, expr *);
	expr * on_le_expression(expr *, expr *);
	expr * on_ge_expression(expr *, expr *);
	expr * on_eq_expression(expr *, expr *);
	expr * on_ne_expression(expr *, expr *);
	expr * on_add_expression(expr *, expr *);
	expr * on_sub_expression(expr *, expr *);
	expr * on_mul_expression(expr *, expr *);
	expr * on_div_expression(expr *, expr *);
	expr * on_rem_expression(expr *, expr *);
	expr * on_neg_expression(expr *);
	expr * on_not_expression(expr *);
	expr * on_call_expression(expr *, std::vector<expr *>);

	expr * on_true_literal(token *);
	expr * on_false_literal(token *);
	expr * on_integer_literal(token *);

	expr * on_id_expression(std::string);
	expr * on_id_expression(decl *);

	std::string on_identifier(token *);

	// scope

	void new_scope(scope_kind kind) { env.new_scope(kind); }
	void remove_scope() { env.remove_scope(); }
	scope * current_scope() { return env.current_scope(); }
	
	// declarations

	decl * current_decl;
	void bind(decl *);
	void bind(decl *, scope *);
	void declare(decl *);
	void declare(decl *, scope *);

	std::vector<decl *> lookup(std::string);


private:
	context * ctx;
	conversion * convert;
	enviornment env;
	std::vector<stmt *> stmt_stack;

};
