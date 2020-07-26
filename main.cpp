#include<iostream>
#include<memory>
using std::cout;
using std::endl;
#include"CyclicRotation.h"
#include"OddOccurrencesInArray.h"
#include"TapeEquilibrium.h"
#include"FrogJmp.h"
#include"PermMissingElem.h"
#include"FrogRiverOne.h"
#include"PermCheck.h"
#include"MaxCounters.h"
#include"MissingInteger.h"
#include"MinAvgTwoSlice.h"
#include"PassingCars.h"
#include"NumberOfDiscIntersections.h"
#include"GenomicRangeQuery.h"
#include"CountDiv.h"
#include"MaxProductOfThree.h"
#include"Triangle.h"
#include"Distinct.h"
#include"Nesting.h"
#include"Brackets.h"
#include"AppLogic.h"
#include"Logger_Mixin.h"

#include<chrono>
#include<thread>
#include<future>
#include<mutex>
#include<string>
using namespace std::chrono_literals;

class Base {
public:
	int x = 0;
	virtual void f() {
		cout << "Base::f()" << endl;
	}
	Base() {
		f();
	}
	virtual ~Base() = default;
	Base(const Base&) = default;
	Base& operator=(const Base&) = default;
	Base(Base&&) = default;
	Base& operator=(Base&&) = default;
};

class Derived :public virtual Base {
public:
	void f() {
		cout << "Derived::f()" << endl;
	}
	Derived() {
		f();
	}
	Derived(const Derived&) = default;
	Derived& operator=(const Derived&) = default;
	Derived(Derived&&) = default;
	Derived& operator=(Derived&&) = default;
	~Derived() = default;
};


#include<map>
#include<iomanip>
#include<numeric>
#include<sstream>
#include<fstream>
#include<queue>
#include<set>
using namespace std;

//std::ifstream in("C:\\Users\\xxx\\Desktop\\dat.txt");
//std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
//std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

vector<string> split_string(string);

#include"Context.h"

int main()
{
	//expected 15806635 20688978289
	//std::ifstream in("C:\\Users\\xxx\\Desktop\\dat4.txt");//READ FROM FILE INSTEAD OF CONSOLE INPUT
	//std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	//std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string genes_temp_temp;
	getline(cin, genes_temp_temp);

	vector<string> genes_temp = split_string(genes_temp_temp);

	vector<string> genes(n);

	for (int i = 0; i < n; i++) {
		string genes_item = genes_temp[i];

		genes[i] = genes_item;
	}

	string health_temp_temp;
	getline(cin, health_temp_temp);

	vector<string> health_temp = split_string(health_temp_temp);
	struct Gene_health_and_index {
		//int health;
		int index;
		uint32_t prefsum;
	};
	map<string, vector<Gene_health_and_index>> healths;
	int prefsum = 0;
	for (int i = 0; i < n; i++) {
		int health_item = stoi(health_temp[i]);
		auto& health_and_index = healths[genes[i]];
		uint32_t prefsum = health_and_index.size() ? health_and_index.back().prefsum : 0;
		health_and_index.push_back({ /*health_item, */i, prefsum + health_item });
	}

	Context context(genes);

	int s;
	cin >> s;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	uint64_t min_sum = UINT64_MAX, max_sum = 0;
	for (int s_itr = 0; s_itr < s; s_itr++) {
		string firstLastd_temp;
		getline(cin, firstLastd_temp);

		vector<string> firstLastd = split_string(firstLastd_temp);

		int first = stoi(firstLastd[0]);

		int last = stoi(firstLastd[1]);

		string d = firstLastd[2];
		//cout << "########  dna: " << d << " first: " << first << " last: " << last << endl;//debug
		uint64_t health_sum = 0;

		context.reset();
		// Traverse the text through the nuilt machine to find 
		// all occurrences of words in arr[] 
		for (int i = 0; i < d.size(); ++i)
		{
			context.next(d[i]);
		}
		auto occurrences = context.get_result();//{ {b,{1,7}} , {c,{0}} }
		for (const auto&[gene_name, positions_in_dna] : occurrences) {//name=b positions={1,7}

			//for (const auto& position : positions_in_dna) cout << "Word " << gene_name << " occures from " << position - gene_name.size() + 1 << " to " << position << endl;//debug
			
			const Gene_health_and_index* first_obj = nullptr, *last_obj = nullptr;
			for (const auto& index_and_psum : healths[gene_name]) {
				int index = index_and_psum.index;
				//cout << "Gene index " << index << endl;//debug
				if (index < first) {
					first_obj = &index_and_psum;
					last_obj = &index_and_psum;
				}
				else {
					if (index <= last) {
						last_obj = &index_and_psum;
					}
					else break;
				}
			}
			if (last_obj != nullptr) {
				uint64_t psum_diff = last_obj->prefsum;
				if (first_obj != nullptr)psum_diff -= first_obj->prefsum;
				health_sum += psum_diff * positions_in_dna.size();
				//cout << "added health " << psum_diff * positions_in_dna.size() << endl;//debug
			}		
		}
		min_sum = min(min_sum, health_sum);
		max_sum = max(max_sum, health_sum);
	}
	cout << min_sum << " " << max_sum;

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


/*int main()
{

	/*std::string s ("abc");
	f(s);

	cout << "start\n";
	auto obj1 = std::make_shared<ThreadFunc>();
	ThreadFunc obj2;
	auto t1_future = std::async(std::launch::deferred, &ThreadFunc::spam, &obj2, "t1");
	auto t2_future = std::async(std::launch::async, &ThreadFunc::spam, &obj2, "t2");
	t1_future.wait();
	t2_future.wait();
	std::this_thread::sleep_for(10s);
	cout << "end\n";

	//Brackets::test();

	cout << endl << endl;
	return 0;
}*/

