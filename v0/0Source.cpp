#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>

#include"Tokenizer.hpp"
#include"Executioner.hpp"

int main(int argc, char* argv[]) {
	
	auto t = new TokenPack(
		"a:3\n"
		"b:4\n"
		"\n"
		"\n"
	);

	std::cout << "---------------";

	t->Debug();

	while(true){}

	return 0;
}