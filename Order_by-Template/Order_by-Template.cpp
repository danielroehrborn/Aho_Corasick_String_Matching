#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct Person { string name; int age, height; };

template<class F> //F is Person::* e.g. &Person::age
auto order_by_0(F f) {
	return [f](const Person& smaller, const Person& bigger) {
		return smaller.*f < bigger.*f;
	};
}

template<class Class, class Type>
auto order_by(Type Class::* f) {
	return [f](const Class& smaller, const Class& bigger) {
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
	int Person::* test = &Person::age;
	auto test2 = &Person::age;
	vector<Person> persons = { {"a",50,170},{"b",65,170}, {"c",15,170}, {"d",65,190}, {"e",15,160}, {"f",65,180} };
	auto result = max_element(persons.begin(), persons.end(), order_by(&Person::age));
	result = max_element(persons.begin(), persons.end(), order_by(&Person::age) | order_by(&Person::height));

}