#pragma once

#include "lexer/lexer.hpp"
#include "ast/context.hpp"
#include "ast/expr.hpp"
#include "sema/translator.hpp"
#include "sema/conversion.hpp"

class context;
class conversion;
class translation;

class parser
{
public:
	parser(keyword_table * kw_tbl, symbol_table * sym_tbl, context * ctx);

	void parse(std::string);

private:
	std::vector<token *> tokens;
	keyword_table * kw_tbl;
	symbol_table * sy_tbl;
	lexer * lxr;
	token ** current;
	token ** last;

	bool empty();
	token * get();
	void next();
	void back();
	void match(token_kind);
	token * match_if(token_kind);
	token * consume();

	/// translation -> toplevel-declaration-seq
	decl * translation();

	// Declarations

	/// toplevel-declaration-seq -> toplevel-declaration-seq toplevel-declaration
	///                           | toplevel-declaration
	std::vector<decl *> toplevel_declaration_seq();

	/// toplevel-declaration -> module-declaration
	///                       | import-declaration
	///                       | function-declaration
	///                       | let-declaration
	decl * toplevel_declaration();

	/// block-declaration -> let-declaration
	///                    | variable-declaration
	decl * block_declaration();

	/// function-declaration -> 'def' function-prototype ';'
	///                       | 'def' function-prototype function-definition
	///
	/// function-prototype -> identifier '(' function-parameter-list? ')' '->' type-specifier
	///
	/// function-definition -> block-statement

	/// function-parameter-list -> function-parameter-list ',' function-parameter
	///                          | function-parameter
	std::vector<decl *> function_parameter_list();

	/// function-parameter -> type-specifier identifier?
	decl * function_parameter();

	/// let-declaration -> 'let' type-specifier identifier value-initializer ';'
	decl * let_declaration();

	/// variable-declaration -> 'var' type-specifier identifier initializer? ';'
	///
	/// initializer -> value-initializer
	///
	/// value-initializer -> '=' conditional-expression
	decl * variable_declaration();

	// Types

	/// type-specifier -> postfix-type-specifier reference-qualifier?
	///
	/// reference-qualifier -> '&'
	type * type_specifier();

	/// postfix-type-specifier -> primary-type-specifier '[' constant-expression ']'
	///                         | primary-type-specifier '[]'
	///                         | primary-type-specifier
	type * postfix_type_specifier();

	/// primary-type-specifier -> simple-type-specifier
	///                         | function-type-specifier
	///                         '(' primary-type-specifier ')'
	///
	/// function-type-specifier -> '(' type-specifier-list? ')' '->' type
	type * primary_type_specifier();

	/// type-specifier-list -> type-specifier 
	///                      | type-specifier-list ',' type-specifier
	std::vector<type*> type_specifier_list();

	/// simple-type-specifier -> 'void' | 'bool' | 'nat' | 'int'
	type * simple_type_specifier();

	// Statements

	/// statement-seq -> statement-seq statement | statement
	std::vector<stmt *> statement_seq();

	/// statement -> block-statement
	///            | if-statement
	///            | while-statement
	///            | break-statement
	///            | continue-statement
	///            | return-statement
	///            | assert-statement
	///            | print-statement
	///            | scan-statement
	///            | skip-statement
	///            | trap-statement
	///            | expression-statement
	///            | declaration-statement
	stmt * statement();

	/// block-statement -> '{' statement-seq '}'
	stmt * block_statement();

	/// if-statement -> 'if' '(' expression ')' statement 'else' statement
	stmt * if_statement();

	/// while-statement -> 'while' '(' expression ')' statement
	stmt * while_statement();

	/// break-statement -> 'break' ';'
	stmt * break_statement();

	/// continue-statement -> 'continue' ';'
	stmt * continue_statement();

	/// return-statement -> 'return' initializer? ';'
	stmt * return_statement();

	/// assert-statement -> 'assert' conditional-expression ';'
	stmt * assert_statement();

	/// print-statement -> 'print' conditional-expression ';'
	stmt * print_statement();

	/// scan-statement -> 'scan' conditional-expression ';'
	stmt * scan_statement();

	/// skip-statement -> 'skip' ';'
	stmt * skip_statement();

	/// trap-statement -> 'trap' ';'
	stmt * trap_statement();

	/// declaration-statement -> block-declaration
	stmt * declaration_statement();

	/// expression-statement -> expression ';'
	stmt * expression_statement();

	// Expressions

	/// expression -> assignment-expression
	expr * expression();

	/// assignment-expression -> logical-or-expression '=' assignment-expression
	///                        | conditional-expression
	expr * assignment_expression();

	/// conditional-expression -> logical-or-expression '?' expression ':' expression
	///                         | logical-or-expression
	expr * conditional_expression();

	/// logical-or-expression -> logical-or-expression '||' logical-and-expression
	///                        | logical-and-expression
	expr * logical_or_expression();

	/// logical-and-expression -> logical-and-expression '&&' inclusive-or-expression
	///                         | inclusive-or-expression
	expr * logical_and_expression();

	/// inclusive-or-expression -> inclusive-or-expression '|' exclusive-or-expression
	///                          | exclusive-or-expression
	expr * inclusive_or_expression();

	/// exclusive-or-expression -> exclusive-or-expression '^' and-expression
	///                          | and-expression
	expr * exclusive_or_expression();

	/// and-expression -> and-expression '&' ordering-expression
	///                 | ordering-expression
	expr * and_expression();

	/// ordering-expression -> ordering-expression '<' equality-expression
	///                      | ordering-expression '>' equality-expression
	///                      | ordering-expression '<=' equality-expression
	///                      | ordering-expression '>=' equality-expression
	///                      | equality-expression
	expr * ordering_expression();

	/// equality-expression -> equality-expression '==' additive-expression
	///                      | equality-expression '!=' additive-expression
	///                      | additive-expression
	expr * equality_expression();

	/// additive-expression -> additive-expression '+' multiplicative-expression
	///                      | additive-expression '-' multiplicative-expression
	///                      | multiplicative-expression
	expr * additive_expression();

	/// multiplicative-expression -> multiplicative-expression '*' unary-expression
	///                            | multiplicative-expression '/' unary-expression
	///                            | multiplicative-expression '%' unary-expression
	///                            | unary-expression
	expr * multiplicative_expression();

	/// unary-expression -> '-' unary-expression
	///                   | postfix-expression
	expr * unary_expression();

	/// postfix-expression -> postfix-expression '(' function-argument-list? ')'
	///                       postfix-expression '[' function-argument-list ')'
	///                       postfix-expression '.' identifier
	///                       primary-expression
	expr * postfix_expression();

	/// function-argument-list -> function-argument_list ',' function-argument
	///                           function-argument
	std::vector<expr *> function_argument_list();

	/// function-argument -> expression
	expr * function_argument();

	/// primary-expression -> literal
	///                     | id-expression
	///                     | '(' expression ')'
	///
	/// literal -> boolean-literal
	///          | integer-literal
	///          | character-literal
	///          | string-literal
	///
	/// boolean-literal -> 'true' | 'false'
	expr * primary_expression();

	/// id-expression -> identifier
	expr * id_expression();

	/// identifiers
	std::string identifier();

	translator * sema;

};

// essentially a scope with a pointer to the previous decl
class region
{
public:
	region(translator * sema, scope_kind kind)
		: sema(sema)
	{
		prev = nullptr;
		sema->new_scope(kind);
	}

	region(translator * sema, scope_kind kind, decl * d)
		: sema(sema)
	{
		prev = sema->current_decl;
		sema->current_decl = d;
	}

	~region()
	{
		if (prev)
		{
			sema->current_decl = prev;
		}

		sema->remove_scope();
	}

	translator * sema;
	decl * prev;
};
