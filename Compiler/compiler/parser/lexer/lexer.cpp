#include "lexer.hpp"
#include <iostream>
#include <string>

std::vector<token*> lexer::lex(std::string s)
{
	// Clear the tokens in prep for a new batch
	tokens.clear();

	if (s.size() == 0)
	{
		return tokens;
	}

	// Get the first and last character pointers
	current = & s.front();
	last = & s.back();

	while (!empty())
	{
		space();
		switch (char c = get())
		{
		case '+':
			tokens.push_back(puncop(plus));
			break;
		case '-':
			tokens.push_back(puncop(minus));
			break;
		case '*':
			tokens.push_back(puncop(asterisk));
			break;
		case '/':
			tokens.push_back(puncop(forward_slash));
			break;
		case '%':
			tokens.push_back(puncop(percent));
			break;
		case '&':
			tokens.push_back(coalesce('&', ampersand_ampersand, ampersand));
			break;
		case '|':
			tokens.push_back(coalesce('|', bar_bar, bar));
			break;
		case '!':
			tokens.push_back(coalesce('=', exclamation_equal, exclamation));
			break;
		case '=':
			tokens.push_back(coalesce('=', equal_equal, equals));
			break;
		case '<':
			tokens.push_back(coalesce('=', less_than_equal, less_than));
			break;
		case '>':
			tokens.push_back(coalesce('=', greater_than_equal, greater_than));
			break;
		case '?':
			tokens.push_back(puncop(question_mark));
			break;
		case ':':
			tokens.push_back(puncop(colon));
			break;
		case '(':
			tokens.push_back(puncop(open_parenthesis));
			break;
		case ')':
			tokens.push_back(puncop(close_parenthesis));
			break;
		case '~':
			tokens.push_back(puncop(tilde));
			break;
		case '^':
			tokens.push_back(puncop(carat));
			break;
		case ';':
			tokens.push_back(puncop(semicolon));
			break;
		case '#':
			comment();
			break;
		case '0':
			switch (lookahead())
			{
			case 'b':
				tokens.push_back(binary());
				break;
			case 'h':
				tokens.push_back(hex());
				break;
			default:
				tokens.push_back(integer(c));
				break;
			}
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			tokens.push_back(integer(c));
			break;
		default:
			if (is_letter(c))
			{
				tokens.push_back(word());
			}
			else
			{
				std::cout << "Invalid character found: >" << c << "<" << std::endl;
				next();
			}
			break;
		}
		space();
	}

	return tokens;
}


bool lexer::is_digit(char c)
{
	return std::isdigit(c);
}

bool lexer::is_letter(char c)
{
	return std::isalpha(c) || c == '_';
}

bool lexer::is_letter_or_digit(char c)
{
	return is_letter(c) || is_digit(c);
}

bool lexer::empty()
{
	return current > last;
}

char lexer::get()
{
	return * current;
}

void lexer::next()
{
	++current;
}

void lexer::back()
{
	--current;
}

char lexer::lookahead()
{
	char ret = *(++current);
	back();
	return ret;
}

token * lexer::puncop(token_kind kind)
{
	next();
	return new token(kind);
}

token * lexer::integer(char c)
{
	std::string s;
	s += c;
	next();

	while (!empty() && is_digit(c = get()))
	{
		s += c;
		next();
	}

	try
	{
		//std::cout << "stoi: " << s << std::endl;
		return new int_token(std::stoi(s));
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

token * lexer::binary()
{
	std::string s;
	next();
	next();
	char c = get();

	while (c == '1' || c == '0')
	{
		s += c;
		next();
		c = get();
	}

	try
	{
		return new int_token(std::stoi(s, nullptr, 2), 2);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

token * lexer::hex()
{
	std::string s;
	next();
	next();
	char c = get();

	while (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7'
		|| c == '8' || c == '9' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F')
	{
		s += c;
		next();
		c = get();
	}

	try
	{
		return new int_token(std::stoi(s, nullptr, 16), 16);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

void lexer::comment()
{
	while (!empty())
	{
		next();
	}
}

void lexer::space()
{
	while (!empty() && std::isspace(get()))
	{
		next();
	}
}

token * lexer::word()
{
	std::string s;
	char c = get();

	// skip any initial whitespace
	while ((c = get()) == ' ')
	{
		next();
	};

	// get the string
	while (!empty() && is_letter_or_digit(c = get()))
	{
		s += get();
		next();
	}

	if (kw_tbl->count(s) > 0)
	{
		return new token(kw_tbl->at(s));
	}

	sym_tbl->add(s);
	return new id_token(s);
}

token * lexer::coalesce(char c, token_kind double_kind, token_kind single_kind)
{
	next();
	if (c == get())
	{
		next();
		return new token(double_kind);
	}
	else
	{
		return new token(single_kind);
	}
}
