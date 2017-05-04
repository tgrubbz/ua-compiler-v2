#include "enviornment.hpp"

void enviornment::stack::push(scope_kind kind)
{
	scope * s = empty() ? nullptr : back().get();
	push_back(std::make_unique<scope>(kind, s));
}

void enviornment::stack::pop()
{
	empty();
	pop_back();
}

void enviornment::add(decl * d)
{
	add(d, current_scope());
}

void enviornment::add(decl * d, scope * s)
{
	// Add declaration to the given scope
	s->push_back(d);

	// Add the declaration name to a new set of bindings
	auto result = binding_map.emplace(d->name, bindings{ });

	// Create a new set of bindings
	bindings & decls = result.first->second;

	// Emprty the bindings and add the new one
	decls.empty();
	decls.push(s, d);
}

void enviornment::remove(std::string s)
{
	get_bindings(s)->pop();
}

void enviornment::remove(decl * d)
{
	remove(d->name);
}

enviornment::bindings * enviornment::get_bindings(std::string s)
{
	// Find the entry in the bindings map
	auto iter = binding_map.find(s);

	// check that it exists
	if (iter != binding_map.end())
	{
		return &iter->second;
	}

	return nullptr;
}

enviornment::entry * enviornment::lookup(std::string s)
{
	// Check that the name correponds to some declarations
	if (bindings * decls = get_bindings(s)) {
		if (!decls->empty())
			// Return the first declaration
			return &decls->top();
	}

	return nullptr;
}

void enviornment::new_scope(scope_kind kind)
{
	stk.push(kind);
}

void enviornment::remove_scope()
{
	for (decl * d : *current_scope())
	{
		remove(static_cast<decl *>(d));
	}

	stk.pop();
}

scope * enviornment::current_scope()
{
	if (stk.empty())
	{
		new_scope(module);
	}

	return stk.top();
}
