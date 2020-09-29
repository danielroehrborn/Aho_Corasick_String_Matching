#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct Person {
	string name;
	int age;
	int height;
};

template<class F> //F == Person::*
auto order_by(F f) { //&Person::alter
	return [f](const Person& smaller, const Person& bigger) {
		return smaller.*f < bigger.*f;
	};
}

//compose two orderings :
template<class F1, class F2>
auto operator|(F1 f1, F2 f2) {
	return [f1, f2](auto a, auto b) {
		auto res = f1(a, b);
		auto inv_res = f1(b, a);
		if (res != inv_res)
			return res;
		return f2(a, b);
	};
}

static void test() {

	vector<Person> persons = { {"a",50,170},{"b",65,170}, {"c",15,170}, {"d",65,190}, {"e",15,160}, {"f",65,180} };
	auto result = max_element(persons.begin(), persons.end(), order_by(&Person::age));
	result = max_element(persons.begin(), persons.end(), order_by(&Person::age) | order_by(&Person::height));

}
