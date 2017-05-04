#include "token.hpp"

// Names of token kinds
std::map<token_kind, std::string> token_kind_map
{
	{ eof, "EOF" },

	{ plus, "PLUS" },
	{ minus, "MINUS" },
	{ asterisk, "ASTERISK" },
	{ forward_slash, "FORWARD_SLASH" },
	{ percent, "PERCENT" },
	{ ampersand, "AMPERSAND" },
	{ ampersand_ampersand, "AMPERSAND_AMPERSAND" },
	{ bar, "BAR" },
	{ bar_bar, "BAR_BAR" },
	{ exclamation, "EXCLAMATION" },
	{ equal_equal, "EQUAL_EQUAL" },
	{ exclamation_equal, "EXCLAMATION_EQUAL" },
	{ less_than, "LESS_THAN" },
	{ greater_than, "GREATER_THAN" },
	{ less_than_equal, "LESS_THAN_EQUAL" },
	{ greater_than_equal, "GREATER_THAN_EQUAL" },
	{ question_mark, "QUESTION_MARK" },
	{ colon, "COLON" },
	{ open_parenthesis, "OPEN_PARENTHESIS" },
	{ close_parenthesis, "CLOSE_PARENTHESIS" },
	{ tilde, "TILDE" },
	{ carat, "CARAT" },
	{ pound, "POUND" },
	{ semicolon, "SEMICOLON" },
	{ equals, "EQUALS" },
	{ open_brace, "OPEN_BRACE" },
	{ close_brace, "CLOSE_BRACE" },
	{ comma, "COMMA" },
	{ open_bracket, "OPEN_BRACKET" },
	{ close_bracket, "CLOSE_BRACKET" },

	// keywords
	{ bool_kw, "BOOL_KW" },
	{ false_kw, "FALSE_KW" },
	{ true_kw, "TRUE_KW" },
	{ int_kw, "INT_KW" },
	{ var_kw, "VAR_KW" },
	{ if_kw, "IF" },
	{ while_kw, "WHILE" },
	{ break_kw, "BREAK" },
	{ continue_kw, "CONTINUE" },
	{ return_kw, "RETURN" },
	{ else_kw, "ELSE" },

	// literals
	{ bool_literal, "BOOL_LITERAL" },
	{ int_literal, "INT_LITERAL" },
	{ binary_literal, "BINARY_LITERAL" },
	{ hex_literal, "HEX_LITERAL" },
	{ comment_literal, "COMMENT_LITERAL" },
	{ variable_literal, "VARIABLE_LITERAL" },

	{ identifier, "IDENTIFIER" }
};

// Get the name associated with the token kind
std::string token::name()
{
	return token_kind_map[kind];
}
