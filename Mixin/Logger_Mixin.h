#pragma once
#include<iostream>

template<class T>
class Logger :public T {
public:
	int prefSum(const vector<int>& A);
	void reset();
};

template<class T>
inline int Logger<T>::prefSum(const vector<int>& A)
{
	std::cout << "Log prefSum start" << std::endl;
	int result = T::prefSum(A);
	std::cout << "Log prefSum end" << std::endl;
	return result;
}

template<class T>
inline void Logger<T>::reset()
{
	std::cout << "Log reset start" << std::endl;
	T::reset();
	std::cout << "Log reset end" << std::endl;
}

//Logger<Logic> logicWithLogger;
//logicWithLogger.prefSum({ 1,2 });