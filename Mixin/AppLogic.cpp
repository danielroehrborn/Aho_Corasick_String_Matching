#include "AppLogic.h"
#include<iostream>

int Logic::prefSum(const vector<int>& A)
{
	std::cout << "prefSum" << std::endl;
	for (auto it = A.begin(); it != A.end(); ++it) {
		pSum += *it;
	}
	return 0;
}

void Logic::reset()
{
	std::cout << "reset" << std::endl;
	pSum = 0;
}
