#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include<fstream>
using namespace std;

//std::ofstream out("C:\\Users\\xxx\\Desktop\\out.txt");
//std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
//std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

//std::ifstream in("C:\\Users\\xxx\\Desktop\\dat.txt");
//std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
//std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {
protected:
	map<int, Node*> mp; //map the key to the node in the linked list
	int cp;  //capacity
	Node* tail; // double linked list tail pointer
	Node* head; // double linked list head pointer
	virtual void set(int key, int value) = 0; //set function
	virtual int get(int key) = 0; //get function
};

#include<memory>
using namespace std;
class LRUCache :public Cache {
public:
	LRUCache(int c) {
		cp = c; cache_size = 1;
		nodes[0] = unique_ptr<Node>(new Node(0, -1)); tail = head = nodes[0].get();
	}
	Node* inc_tail() {
		Node* old_tail = tail;
		tail = tail->prev;
		tail->next = tail;
		return old_tail;
	}
	void drop_tail() {
		Node* old_tail = inc_tail();
		old_tail->prev = old_tail;
		old_tail->next = old_tail;
	}
	void exclude(Node* n) {
		n->prev->next = n->next;
		n->next->prev = n->prev;
		n->prev = n;
		n->next = n;
	}
	void set_head(Node* n) {
		n->prev = n;
		head->prev = n;
		n->next = head;
		head = n;
	}
	void move_first(Node* n) {
		if (n->next == n) {
			if (n->prev == n) {//has no next, no prev
				//n not in cache	
				//move n to head
				set_head(n);
				//drop tail if necessary
				if (cache_size > cp) {
					--cache_size;
					drop_tail();
				}
			}
			else {//has no next but prev
				//n is tail
				//move tail to head
				inc_tail();
				set_head(n);
			}
		}
		else {
			if (n->prev == n) {//has next, no prev
				//n is head. do nothing
				;
			}
			else {//has next and prev
				//n is in cache between head and tail
				//move n to head and close gap
				exclude(n);
				set_head(n);
			}
		}
	}
	void set(int key, int value) override {
		Node* current;
		if (nodes.find(key) == nodes.end()) {
			++cache_size;
			nodes[key] = unique_ptr<Node>(new Node(key, value));
			current = nodes[key].get();
			current->next = current;
			current->prev = current;
			if (!head && !tail) { head = current; tail = current; }
		}
		else current = nodes[key].get();
		current->value = value;
		move_first(current);
	}
	int get(int key)override {
		Node* n = head;
		int result = -1;
		for (int i = 0; i < cache_size; ++i) {
			if (n->key == key) {
				result = n->value;
				move_first(n);
				break;
			}
			n = n->next;
		}
		if (result == -1 && nodes.find(key) != nodes.end()) {
			++cache_size;
			move_first(nodes[key].get());
		}
		return result;
	}
	void print_cache() {
		Node* n = head;
		cout << "Cache: ";
		while (n) {
			cout << n->key << ", ";
			if (n->next == n)break;
			n = n->next;
		}
		cout << endl << endl;
	}
private:
	map<int, unique_ptr<Node>> nodes;
	int cache_size;
};

int main() {
	std::ifstream in("C:\\Users\\xxx\\Desktop\\dat.txt");
	std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

	int n, capacity, i;
	cin >> n >> capacity;
	LRUCache l(capacity);
	for (i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "get") {
			int key;
			cin >> key;
			cout << "get " << key << endl;
			cout << l.get(key) << endl;
		}
		else if (command == "set") {
			int key, value;
			cin >> key >> value;
			cout << "set " << key << " " << value << endl;
			l.set(key, value);
		}
		l.print_cache();
	}
	return 0;
}
