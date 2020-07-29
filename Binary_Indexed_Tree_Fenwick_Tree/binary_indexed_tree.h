#pragma once
#include<vector>
using std::vector;
/*
Sum: Calculate prefix sum
Add: Change a value in prefix sum array without changing all following values
*/
int sum(const vector<int>& prefsums, int index) {
	int result = 0;
	while (index) {
		result += prefsums[index];
		index -= index & -index;
	}
	return result;
}

void add(vector<int>& prefsums, int index, int value) {
	int size = prefsums.size();
	while (index < size) {
		prefsums[index] += value;
		index += index & -index;
	}
}
