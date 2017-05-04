#pragma once

#include <cctype>
#include <vector>
#include "keyword.hpp"
#include "symbol.hpp"
#include "token.hpp"

class lexer
{
public:
	lexer(keyword_table * kw, symbol_table * sy) : kw_tbl(kw), sym_tbl(sy) { }
	std::vector<token *> lex(std::string);
	
private:
	char * current;
	char * last;
	std::vector<token *> tokens;
	symbol_table * sym_tbl;
	keyword_table * kw_tbl;


	bool empty();
	char get();
	void next();
	void back();
	char lookahead();
	bool is_digit(char);
	bool is_letter(char);
	bool is_letter_or_digit(char);

	token * puncop(token_kind);
	token * integer(char);
	token * binary();
	token * hex();
	token * word();
	token * coalesce(char, token_kind, token_kind);
	void comment();
	void space();

};
