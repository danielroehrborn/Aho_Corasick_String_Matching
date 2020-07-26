#pragma once
#include"State.h"
#include<vector>
#include<queue>
using std::vector;
using std::make_unique;
using std::pair;
using std::tie;
using std::make_pair;
using std::queue;

/* Aho Corasick String Matching
1) Build tree of states
For each word start from root node. Char by char transition to next node (create next node if not exists).
2) Add failure tansitions
Failure state of next node = Failure state of this node + transition
If no transition possible go to next failure state until reaching root node.
Start failure transition generation at root node. Set failure state of direct child nodes to root.
Order of operation:
Take node from queue. Set failure state to child nodes. Add child nodes to queue. Repeat.
3) Using tree to find occurrences of words in input string
Reset() Context. Pass input string char by char to Next(). Get result from Context.
Result is a map of words with vector of positions indices (last char position of word in input string).
*/

class Context {
public:
	Context(vector<string> words);
	void reset();
	void next(char c);
	map<string, vector<int>> get_result() { return occurrences; }

private:
	void build_tree(vector<string> words);
	void add_word_to_tree(const string& word);
	void add_transition_to_node(State* node, char c);
	void set_failure_states();
	pair<State*, bool> search_execute_transition(State* const node, char c);

	unique_ptr<State> root;
	int char_count;
	State* current_node;
	map<string, vector<int>> occurrences;
	int existing_states = 1;
	queue<State*> nodes_to_set_failure_state;
};