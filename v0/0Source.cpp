#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#include "Tokenizer.hpp"
#include "Executioner.hpp"
#include "TokenizerWords.hpp"




int main(int argc, char* argv[]) {
	
	auto t = new Tokenizer_Words(
		"ab ae ds"
	);

	std::cout << "\n---------------\n";

	t->Debug();



	for(;;){}

	return 0;
}