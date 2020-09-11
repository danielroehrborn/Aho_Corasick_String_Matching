#pragma once
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
/*
Huffman Kodierung:
Effiziente Codierung (1100) von Zeichen (char).
Individueller Code für jedes Zeichen, das im Baum vorkommt.
Häufige Zeichen = kurzer Code, seltene Zeichen = längerer Code.
Je häufiger ein Zeichen bei Baumerstellung vorkam, desto kürzer sein Code.
Aufbau des Baumes
1)Ermittle für jedes Quellsymbol die relative Häufigkeit, d. h. zähle, wie oft jedes Zeichen vorkommt, und teile durch die Anzahl aller Zeichen.
2)Erstelle für jedes Quellsymbol einen einzelnen Knoten (die einfachste Form eines Baumes) und notiere im/am Knoten die Häufigkeit.
3)Wiederhole die folgenden Schritte so lange, bis nur noch ein Baum übrig ist:
	a)Wähle die m Teilbäume mit der geringsten Häufigkeit in der Wurzel, bei mehreren Möglichkeiten die Teilbäume mit der geringsten Tiefe.
	b)Fasse diese Bäume zu einem neuen (Teil-)Baum zusammen.
	c)Notiere die Summe der Häufigkeiten in der Wurzel.
*/
class HuffmanTree {
public:
	struct Node {
		char data = 0;
		int weight = 0;
		unique_ptr<Node> left;
		unique_ptr<Node> right;
	};
	void create(const string& s) {
		map<char, int> weights;
		for_each(s.begin(), s.end(), [&](char c) { ++weights[c]; });
		vector<unique_ptr<Node>> nodes;
		for_each(weights.begin(), weights.end(), [&](auto p) {
			auto n = make_unique<Node>();
			n->data = p.first;
			n->weight = p.second;
			nodes.push_back(move(n));
		});
		while (nodes.size() > 1) {
			auto parent = make_unique<Node>();
			int smallest = 0;
			for (int i = 0; i < nodes.size(); ++i)
				if (nodes[i]->weight < nodes[smallest]->weight)
					smallest = i;
			parent->left = move(nodes[smallest]);
			nodes.erase(nodes.begin() + smallest);
			smallest = 0;
			for (int i = 0; i < nodes.size(); ++i)
				if (nodes[i]->weight < nodes[smallest]->weight)
					smallest = i;
			parent->right = move(nodes[smallest]);
			nodes.erase(nodes.begin() + smallest);

			parent->weight = parent->left->weight + parent->right->weight;
			nodes.push_back(move(parent));
		}
		root = move(nodes.front());
	}
	void create(const map<char, string>& codes) {
		root = make_unique<Node>();
		for (auto&[data, code] : codes) {
			Node* current = root.get();
			for (char c : code) {
				if (c == '0') {
					if (current->left == nullptr)
						current->left = make_unique<Node>();
					current = current->left.get();
				}
				else if (c == '1') {
					if (current->right == nullptr)
						current->right = make_unique<Node>();
					current = current->right.get();
				}
			}
			current->data = data;
		}
	}
	map<char, string> get_codes() {
		map<char, string> codes;
		function<void(Node*, string)> recursive;
		recursive = [&](Node* n, string code) {
			if (n->left != nullptr)recursive(n->left.get(), code + "0");
			if (n->right != nullptr)recursive(n->right.get(), code + "1");
			if (n->data)codes[n->data] = code;
		};
		recursive(root.get(), "");
		return codes;
	}
	string encode(string text) {
		auto codes = get_codes();
		string result;
		for_each(text.begin(), text.end(), [&](char c) {result += codes[c]; });
		return result;
	}
	string decode(string encoded) {
		string result;
		Node* current = root.get();
		for_each(encoded.begin(), encoded.end(), [&](char c) {
			if (c == '0') {
				if (current->left == nullptr)
					current = root.get();
				current = current->left.get();
			}
			else if (c == '1') {
				if (current->right == nullptr)
					current = root.get();
				current = current->right.get();
			}
			if (current->data)result += current->data;
		});
		return result;
	}
private:
	unique_ptr<Node> root;
};
/*
int main()
{
	HuffmanTree tree;
	tree.create("ABRACADABRA");
	auto codes = tree.get_codes();
	string encoded = tree.encode("ABRACADABRA");
	string decoded = tree.decode(encoded);
	tree.create(codes);
	codes = tree.get_codes();
	string encoded2 = tree.encode("ABRACADABRA");
}
*/