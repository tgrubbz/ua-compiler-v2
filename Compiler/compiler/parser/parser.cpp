#pragma once

#include "parser.hpp"
#include <iostream>

parser::parser(keyword_table * kw_tbl, symbol_table * sy_tbl, context * ctx)
	: kw_tbl(kw_tbl), sy_tbl(sy_tbl)
{
	sema = new translator(ctx, new conversion(ctx));
	lxr = new lexer(kw_tbl, sy_tbl);
}

void parser::parse(std::string s)
{
	tokens = lxr->lex(s);

	current = & tokens.front();
	last = & tokens.back();	

	std::vector<stmt *> sts = statement_seq();
	//std::cout << eval_expr(e) << std::endl;
}

bool parser::empty()
{
	return current > last;
}

token * parser::get()
{
	return * current;
}

void parser::next()
{
	++current;
}

void parser::back()
{
	--current;
}

void parser::match(token_kind kind)
{
	if (get()->kind != kind)
	{
		throw std::runtime_error("expected some token");
	}
	next();
}

token * parser::match_if(token_kind kind)
{
	if (!empty())
	{
		if (token * t = get())
		{
			if (t->kind == kind)
			{
				return consume();
			}
		}
	}

	return nullptr;
}

token * parser::consume()
{
	token * t = get();
	next();
	return t;
}

decl * parser::translation()
{
	decl * d = sema->on_start_translation();
	region r(sema, module, d);
	toplevel_declaration_seq();
	return sema->on_finish_translation(d);
}

// program
std::vector<decl*> parser::toplevel_declaration_seq()
{
	std::vector<decl*> decls;

	while (!empty())
	{
		decls.push_back(toplevel_declaration());
	}

	return decls;
}


decl * parser::toplevel_declaration()
{
	return nullptr;
}

decl * parser::block_declaration()
{
	return nullptr;
}

std::vector<decl*> parser::function_parameter_list()
{
	return std::vector<decl*>();
}

decl * parser::function_parameter()
{
	return nullptr;
}

decl * parser::let_declaration()
{
	return nullptr;
}

decl * parser::variable_declaration()
{
	return nullptr;
}

type * parser::type_specifier()
{
	return nullptr;
}

type * parser::postfix_type_specifier()
{
	return nullptr;
}

type * parser::primary_type_specifier()
{
	return nullptr;
}

std::vector<type*> parser::type_specifier_list()
{
	return std::vector<type*>();
}

type * parser::simple_type_specifier()
{
	return nullptr;
}

// statements
#pragma region statements

std::vector<stmt*> parser::statement_seq()
{
	std::vector<stmt*> stmts;

	while (!empty() && get()->kind != close_brace)
	{
		stmts.push_back(statement());
	}

	return stmts;
}

stmt * parser::statement()
{
	switch (get()->kind)
	{
	case open_brace:
		return block_statement();
	case if_kw:
		return if_statement();
	case while_kw:
		return while_statement();
	case break_kw:
		return break_statement();
	case continue_kw:
		return continue_statement();
	case return_kw:
		return return_statement();
	case var_kw:
		return declaration_statement();
	default:
		return expression_statement();
	}
}

stmt * parser::block_statement()
{
	region reg(sema, block);
	match(open_brace);
	std::vector<stmt*> stmts;
	if (!empty() && get()->kind != close_brace)
	{
		stmts = statement_seq();
	}
	match(close_brace);
	return sema->on_block_statement(stmts);
}

stmt * parser::if_statement()
{
	match(if_kw);
	match(open_parenthesis);
	expr * e = expression();
	match(close_parenthesis);
	stmt * s1 = statement();
	match(else_kw);
	stmt * s2 = statement();
	return sema->on_if_statement(e, s1, s2);
}

stmt * parser::while_statement()
{
	match(while_kw);
	match(open_parenthesis);
	expr * e = expression();
	match(close_parenthesis);
	stmt * l = sema->on_while_initiation(e);
	stmt * s = statement();
	return sema->on_while_completion(l, s);
}

stmt * parser::break_statement()
{
	match(break_kw);
	match(semicolon);
	return sema->on_break_statement();
}

stmt * parser::continue_statement()
{
	match(continue_kw);
	match(semicolon);
	return sema->on_continue_statement();
}

stmt * parser::return_statement()
{
	match(return_kw);
	if (match_if(semicolon))
	{
		return sema->on_return_statement();
	}
	expr * e = expression();
	match(semicolon);
	return sema->on_return_statement(e);
}

stmt * parser::declaration_statement()
{
	return sema->on_declaration_statement(block_declaration());
}

stmt * parser::expression_statement()
{
	expr * e = expression();
	match(semicolon);
	return sema->on_expression_statement(e);
}

#pragma endregion

// expressions
#pragma region expressions

expr * parser::expression()
{
	return assignment_expression();
}

expr * parser::assignment_expression()
{
	std::cout << "assignment_expression" << std::endl;
	expr * e1 = logical_or_expression();
	if (match_if(question_mark))
	{
		expr * e2 = expression();
		next();
		match(colon);
		expr * e3 = expression();
		return sema->on_cond_expression(e1, e2, e3);
	}
	else if (match_if(equals))
	{
		expr * e2 = assignment_expression();
		return sema->on_assign_expression(e1, e2);
	}
	return e1;
}

expr * parser::conditional_expression()
{
	std::cout << "conditional_expression" << std::endl;
	expr * e1 = logical_or_expression();
	if (match_if(question_mark))
	{
		expr * e2 = expression();
		next();
		match(colon);
		expr * e3 = expression();
		return sema->on_cond_expression(e1, e2, e3);
	}
	return e1;
}

expr * parser::logical_or_expression()
{
	std::cout << "logical_or_expression" << std::endl;
	expr * e1 = logical_and_expression();

	while (true)
	{
		if (match_if(bar_bar))
		{
			expr * e2 = logical_and_expression();
			e1 = sema->on_logical_or_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::logical_and_expression()
{
	std::cout << "logical_and_expression" << std::endl;
	expr * e1 = inclusive_or_expression();

	while (true)
	{
		if (match_if(ampersand_ampersand))
		{
			expr * e2 = inclusive_or_expression();
			e1 = sema->on_logical_and_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::inclusive_or_expression()
{
	std::cout << "inclusive_or_expression" << std::endl;
	expr * e1 = exclusive_or_expression();

	while (true)
	{
		if (match_if(bar))
		{
			expr * e2 = exclusive_or_expression();
			e1 = sema->on_or_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::exclusive_or_expression()
{
	std::cout << "exclusive_or_expression" << std::endl;
	expr * e1 = and_expression();

	while (true)
	{
		if (match_if(carat))
		{
			expr * e2 = and_expression();
			e1 = sema->on_xor_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::and_expression()
{
	std::cout << "and_expression" << std::endl;
	expr * e1 = ordering_expression();

	while (true)
	{
		if (match_if(carat))
		{
			expr * e2 = ordering_expression();
			e1 = sema->on_and_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::ordering_expression()
{
	std::cout << "ordering_expression" << std::endl;
	expr * e1 = equality_expression();

	while (true)
	{
		if (match_if(less_than))
		{
			expr * e2 = equality_expression();
			e1 = sema->on_lt_expression(e1, e2);
		}
		else if (match_if(greater_than))
		{
			expr * e2 = equality_expression();
			e1 = sema->on_gt_expression(e1, e2);
		}
		else if (match_if(less_than_equal))
		{
			expr * e2 = equality_expression();
			e1 = sema->on_le_expression(e1, e2);
		}
		else if (match_if(greater_than_equal))
		{
			expr * e2 = equality_expression();
			e1 = sema->on_ge_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::equality_expression()
{
	std::cout << "equality_expression" << std::endl;
	expr * e1 = additive_expression();

	while (true)
	{
		if (match_if(equal_equal))
		{
			expr * e2 = additive_expression();
			e1 = sema->on_eq_expression(e1, e2);
		}
		else if (match_if(exclamation_equal))
		{
			expr * e2 = additive_expression();
			e1 = sema->on_ne_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::additive_expression()
{
	std::cout << "additive_expression" << std::endl;
	expr * e1 = multiplicative_expression();

	while (true)
	{
		if (match_if(plus))
		{
			expr * e2 = multiplicative_expression();
			e1 = sema->on_add_expression(e1, e2);
		}
		else if (match_if(minus))
		{
			expr * e2 = multiplicative_expression();
			e1 = sema->on_sub_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::multiplicative_expression()
{
	std::cout << "multiplicative_expression" << std::endl;
	expr * e1 = unary_expression();

	while (true)
	{
		if (match_if(asterisk))
		{
			expr * e2 = unary_expression();
			e1 = sema->on_mul_expression(e1, e2);
		}
		else if (match_if(forward_slash))
		{
			expr * e2 = unary_expression();
			e1 = sema->on_div_expression(e1, e2);
		}
		else if (match_if(percent))
		{
			expr * e2 = unary_expression();
			e1 = sema->on_rem_expression(e1, e2);
		}
		else
		{
			break;
		}
	}

	return e1;
}

expr * parser::unary_expression()
{
	std::cout << "unary_expression" << std::endl;
	if (match_if(minus))
	{
		expr * e = unary_expression();
		return sema->on_neg_expression(e);
	}
	else if (match_if(exclamation))
	{
		expr * e = unary_expression();
		return sema->on_not_expression(e);
	}
	else
	{
		return postfix_expression();
	}
}

expr * parser::postfix_expression()
{
	std::cout << "postfix_expression" << std::endl;
	expr * e = primary_expression();
	std::vector<expr *> exprs;

	while (true) {
		if (match_if(open_parenthesis))
		{
			next();
			if (get()->kind != close_parenthesis)
			{
				exprs = function_argument_list();
			}
			next();
			match(close_parenthesis);
			e = sema->on_call_expression(e, exprs);
			break;
		}
		else
		{
			break;
		}
	}

	return e;
}

std::vector<expr*> parser::function_argument_list()
{
	std::cout << "function_argument_list" << std::endl;
	std::vector<expr*> exprs;

	while (true) {
		expr * arg = function_argument();
		exprs.push_back(arg);
		if (match_if(comma))
		{
			continue;
		}

		break;
	}

	return exprs;
}

expr * parser::function_argument()
{
	std::cout << "function_argument" << std::endl;
	return expression();
}

expr * parser::primary_expression()
{
	std::cout << "primary_expression" << std::endl;

	if (token * t = get())
	{
		switch (t->kind)
		{
		case true_kw:
			return sema->on_true_literal(consume());
		case false_kw:
			return sema->on_false_literal(consume());
		case int_literal:
			return sema->on_integer_literal(consume());
		case token_kind::identifier:
			return id_expression();
		case open_parenthesis:
			consume();
			expr * e = expression();
			match(close_parenthesis);
			return e;
		}
	}
	throw std::runtime_error("expected primary-expression");
}

expr * parser::id_expression()
{
	std::cout << "id_expression" << std::endl;
	return sema->on_id_expression(identifier());
}

std::string parser::identifier()
{
	std::cout << "identifier" << std::endl;
	next();
	match(token_kind::identifier);
	return sema->on_identifier(consume());
}

#pragma endregion
