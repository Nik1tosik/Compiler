#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Token.h"

class LexicalAnalyzer
{
private:
	std::string input;
	size_t position;
	std::unordered_map<std::string, TokenType> keyword;

	void initKeyword();

	bool isWhitespase(char c);
	bool isAlpha(char c);
	bool isDigit(char c);
	bool isAlphaNumeric(char c);

	std::string getNextWord();
	std::string getNextNumber();

public:
	LexicalAnalyzer(const std::string& source);

	std::vector<Token> tokenize();

	std::string getTokenTypeName(TokenType type);

	void printTokens(const std::vector<Token>& tokens);
};

