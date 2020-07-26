#include "Context.h"

Context::Context(vector<string> words) {
	root = make_unique<State>(0);
	root.get()->failure = root.get();
	build_tree(words);
	reset();
}

void Context::next(char c) {
	current_node = search_execute_transition(current_node, c).first;
	for (const auto& out : current_node->outputs) {
		occurrences[out].push_back(char_count);
	}
	++char_count;
}

void Context::reset() { current_node = root.get(); char_count = 0; occurrences.clear(); }

void Context::build_tree(vector<string> words) {
	existing_states = 1;
	for (const auto& word : words) {
		add_word_to_tree(word);
	}
	nodes_to_set_failure_state.push(root.get());
	set_failure_states();
}

void Context::add_word_to_tree(const string & word) {
	State* node = root.get();
	for (const auto& c : word) {
		add_transition_to_node(node, c);
		node = node->transition(c);
	}
	node->add_output(word);
}

void Context::add_transition_to_node(State * node, char c) {
	if (!node->has_transition(c)) {
		State* next = node->add_transition(c, make_unique<State>(existing_states++));
	}
}

void Context::set_failure_states() {
	while (!nodes_to_set_failure_state.empty()) {
		State* node = nodes_to_set_failure_state.front();
		nodes_to_set_failure_state.pop();
		for (auto&[c, next] : node->transitions) {
			if (next->parent == root.get())
				next->failure = root.get();
			else {
				bool transition_possible = false;
				tie(next->failure, transition_possible) = search_execute_transition(node->failure, c);
				if (transition_possible)
					next->add_output(next->failure);
			}
			nodes_to_set_failure_state.push(next.get());
		}
	}
}

pair<State*, bool> Context::search_execute_transition(State * const node, char c) {
	State* n = node;
	bool transition_possible = false;
	bool search_next = true;
	while (search_next) {
		if (n->has_transition(c)) {
			n = n->transition(c);
			search_next = false;
			transition_possible = true;
		}
		else {
			if (n == n->failure)
				search_next = false;
			else
				n = n->failure;
		}
	}
	return make_pair(n, transition_possible);
}
