
#include "keyword.hpp"

// Key word table maps the reserved words with their token kinds
keyword_table::keyword_table()
{
	insert({ "bool", bool_kw });
	insert({ "true", true_kw });
	insert({ "false", false_kw });
	insert({ "int", int_kw });
	insert({ "var", var_kw });
}
