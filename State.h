#pragma once
#include<map>
#include<string>
#include<memory>
#include<set>
using std::set;
using std::string;
using std::map;
using std::unique_ptr;

class State {
public:
	State(int i) : id(i) {}
	State* transition(char c) { return transitions[c].get(); }
	bool has_transition(char c) { return transitions.find(c) != transitions.end(); }
	State* add_transition(char c, unique_ptr<State> s) { transitions[c] = move(s); transitions[c]->parent = this; return transitions[c].get(); }
	void add_output(string out) { outputs.insert(out); }
	void add_output(State* other) { outputs.insert(begin(other->outputs), end(other->outputs)); }
	State* parent = nullptr;
	State* failure = nullptr;
	set<string> outputs;
	int id;
	map<char, unique_ptr<State>>transitions;
};