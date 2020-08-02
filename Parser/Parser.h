#pragma once
#include<string>
#include<iostream>
#include<map>
#include<regex>
#include<vector>
using namespace std;

class Tag {
public:
	Tag(string n) :name(n) {};
	Tag* add_tag(string n) { tags[n] = unique_ptr<Tag>(new Tag(n)); tags[n]->parent = this; return tags[n].get(); }
	bool has_tag(string n) { return tags.find(n) != tags.end(); }
	Tag* get_tag(string n) { return tags[n].get(); }
	void add_attribute(string n, string val) { attributes[n] = val; }
	bool has_attribute(string n) { return attributes.find(n) != attributes.end(); }
	string get_attribute(string n) { return attributes[n]; }
	string name;
	Tag* parent;
	map<string, unique_ptr<Tag>> tags;
	map<string, string> attributes;
	void print() {
		cout << "Start: " << name << endl;
		for (const auto&[k, v] : attributes)
			cout << name << " [" << k << "]:" << v << endl;
		cout << "Sub tags" << endl;
		for (const auto&[k, v] : tags) {
			cout << name << ": " << k << endl;
			v->print();
		}
		cout << "End: " << name << endl;
	}
};

class Parser {
public:
	static void parse(const vector<string>& tags, const vector<string>& queries) {
		Tag root("root");
		Tag* current_tag = &root;
		for (const auto& line : tags) {
			current_tag = parse_tag(current_tag, line);
		}
		for (const auto& q : queries) {
			auto[query_tags, query_value] = parse_query(q);
			cout << execute_query(&root, query_tags, query_value) << endl;
		}
		return;
	}

	static Tag* parse_tag(Tag* t, const string& line) {
		Tag* tag = t;
		auto[line_matched, end_slash, tag_name, atts] = parse_three_groups(line, "^ *< *(\/?) *(\\w+)(.*)>");//group1=/ group2=tagname group3=attributes
		if (line_matched) {
			if (end_slash.empty()) {//add new sub tag
				tag = tag->add_tag(tag_name);
				tag->attributes = parse_assignments(atts, "\\s*(\\w+)\\s*=\\s*\"([\\w!§$%&\\.]+)\"\\s*");// " *(\\w+) *= *\"?(\\w+)\"? *");//group1=name group2=value
			}
			else {//closing tag, return to parent
				if (tag->name.compare(tag_name) == 0)
					tag = tag->parent;
				else cout << "last opened=" << tag->name << " closing tag=" << tag_name << endl;
			}
		}
		else cout << "Line !matched: " << line << endl;

		return tag;
	}

	static tuple<bool, string, string, string> parse_three_groups(const string& line, const string& reg) {
		regex regx(reg);
		smatch match;
		bool matched = regex_match(line, match, regx);
		return make_tuple(matched, match[1], match[2], match[3]);
	}

	static map<string, string> parse_assignments(const string& line, const string& reg) {
		regex regx(reg);
		map<string, string> result;
		auto begin = std::sregex_iterator(line.begin(), line.end(), regx);
		auto end = std::sregex_iterator();
		for (auto it = begin; it != end; ++it) {
			smatch match = *it;
			result[match[1]] = match[2];
		}
		return result;
	}

	static tuple<vector<string>, string> parse_query(const string& line) {
		auto query_elements = parse_delimiter(line, "\\s*(\\w+)\\s*\\.\\s*");
		auto last = parse_delimiter(line, "\\s*(\\w+)\\s*~\\s*(\\w+)\\s*$");
		string value_name;
		if (last.size() == 2) {
			query_elements.push_back(last[0]);
			value_name = last[1];
		}
		else
			cout << "last.size!=2 :" << last.size() << endl;
		return make_tuple(query_elements, value_name);
	}

	static vector<string> parse_delimiter(const string& line, const string& reg) {
		regex regx(reg);
		vector<string> result;
		auto begin = std::sregex_iterator(line.begin(), line.end(), regx);
		auto end = std::sregex_iterator();
		for (auto it = begin; it != end; ++it) {
			smatch match = *it;
			if (match[1].str().size())result.push_back(match[1]);
			if (match[2].str().size())result.push_back(match[2]);
		}
		return result;
	}

	static string execute_query(Tag* root, vector<string> tag_names, string value_name) {
		string value("Not Found!");
		Tag* t = root;
		for (const auto& tag_name : tag_names) {
			if (t->has_tag(tag_name)) {
				t = t->get_tag(tag_name);
			}
			else return value;
		}
		if (t->has_attribute(value_name))
			value = t->get_attribute(value_name);
		return value;
	}
};
