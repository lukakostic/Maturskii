#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#include "TokenPack.hpp"
#include "Runtime/Executioner.hpp"


int main(int argc, char* argv[]) {

	std::ifstream file("code.txt");
	std::string str;
	std::string file_contents;
	while (std::getline(file, str))
	{
		file_contents += str;
		file_contents.push_back('\n');
	}

	auto t = TokenPack();

	t.Build(
		file_contents
	);

	auto e = Executioner();

	e.Run(&t);

	for(;;){}

	return 0;
}