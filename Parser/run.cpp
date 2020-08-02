#include "Parser.h"
#include<fstream>

//std::ofstream out("C:\\Users\\xxx\\Desktop\\out.txt");
//std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
//std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

//std::ifstream in("C:\\Users\\xxx\\Desktop\\dat.txt");
//std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
//std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

/* example input
6 4
<a>
<b name = "tag_one">
<c name = "tag_two" value = "val_907">
</c>
</b>
</a>
a.b~name
a.b.c~value
a.b.c~src
a.b.c.d~name
*/
vector<string> split_string(string);

int main_()
{
	std::ifstream in("C:\\Users\\xxx\\Desktop\\dat.txt");
	std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!


	int n, q;
	cin >> n >> q;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string line;
	vector<string> tags, queries;
	for (int i = 0; i < n; i++) {
		getline(cin, line);
		tags.push_back(line);
	}

	for (int i = 0; i < q; i++) {
		getline(cin, line);
		queries.push_back(line);
	}
	Parser::parse(tags, queries);

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y && x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
