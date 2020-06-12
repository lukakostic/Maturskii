#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#include "Tokenizer/TokenPack.hpp"
//#include "Executioner/Executioner.hpp"


int main(int argc, char* argv[]) {
	
	auto t = new Tokenizer();

	t->Build("=(#a,3) =(#a,+(a,5)) print(a)");

	for(;;){}

	return 0;
}