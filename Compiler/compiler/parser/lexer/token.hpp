#pragma once

#include <map>

#pragma region token_kind

// Kinds of tokens
enum token_kind
{
	eof,

	// operators and punctuators
	plus,
	minus,
	asterisk,
	forward_slash,
	percent,
	ampersand,
	ampersand_ampersand,
	bar,
	bar_bar,
	exclamation,
	equal_equal,
	exclamation_equal,
	less_than,
	greater_than,
	less_than_equal,
	greater_than_equal,
	question_mark,
	colon,
	open_parenthesis,
	close_parenthesis,
	open_brace,
	close_brace,
	tilde,
	carat,
	pound,
	semicolon,
	equals,
	comma,

	// keywords
	bool_kw,
	false_kw,
	true_kw,
	int_kw,
	var_kw,
	if_kw,
	while_kw,
	break_kw,
	continue_kw,
	return_kw,
	else_kw,

	// literals
	bool_literal,
	int_literal,
	binary_literal,
	hex_literal,
	comment_literal,
	variable_literal,

	identifier
};

#pragma endregion

// Base token class
class token
{
public:
	token_kind kind;
	std::string name();

	token(token_kind tk) : kind(tk) { }
	virtual ~token() = default;

};

// Integer token
class int_token : public token
{
public:
	int val;
	int radix;

	int_token(int val, int radix = 10) : val(val), radix(radix), token(int_literal) { }

};

// Boolean token
class bool_token : public token
{
public:
	bool val;

	bool_token(bool val) : val(val), token(bool_literal) { }

};

// Identifier token
class id_token : public token
{
public:
	std::string sym;

	id_token(std::string s) : token(identifier), sym(s) { }
};
