#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>

#include"Tokenizer.hpp"
#include"Executioner.hpp"

int main(int argc, char* argv[]) {
	
	auto t = new TokenPack(
		"=($a,15)"
	);

	std::cout << "---------------";

	t->Debug();

	for(;;){}

	return 0;
}