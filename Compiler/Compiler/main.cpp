#include <iostream>

#include "LexicalAnalyzer.h"

int main()
{
	std::string sourceCode =
		"int main(){"
		"    float x = 3.14.15;"
		"    float y = 3.15"
		"    float z = x + y;"
		"    21898318asdqq"
		"    return 0;"
		"}";

	LexicalAnalyzer lexer(sourceCode);
	std::vector<Token> tokens = lexer.tokenize();
	lexer.printTokens(tokens);
}