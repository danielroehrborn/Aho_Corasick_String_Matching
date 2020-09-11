#pragma once
#include <iostream>
#include <fstream>
void redirect_input(std::string path = "C:\\Users\\xxx\\Desktop\\dat.txt") {
	std::ifstream in(path);
	std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
}
void redirect_output(std::string path = "C:\\Users\\xxx\\Desktop\\out.txt") {
	std::ofstream out(path);
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
}