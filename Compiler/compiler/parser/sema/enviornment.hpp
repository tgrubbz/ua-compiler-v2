#pragma once

#include "scope.hpp"
#include <memory>

class enviornment
{
public:
	class entry
	{
	public:
		entry(scope * s, decl * d) : s(s), d(d) { }
		scope * s;
		decl * d;

	};

	class bindings : public std::vector<entry>
	{
	public:
		entry & top() { return back(); }
		void push(scope * s, decl * d) { push_back({ s, d }); }
		void pop() { pop_back(); }

	};

	class stack : public std::vector<std::unique_ptr<scope>>
	{
	public:
		~stack() { empty(); }
		scope * top() { return back().get(); }

		void push(scope_kind);
		void pop();

	};

	void add(decl *);
	void add(decl *, scope *);
	bindings * get_bindings(std::string);
	void remove(std::string);
	void remove(decl *);
	entry * lookup(std::string);
	void new_scope(scope_kind);
	void remove_scope();
	scope * current_scope();
	// get bindings

	std::unordered_map<std::string, bindings> binding_map;
	stack stk;

};
