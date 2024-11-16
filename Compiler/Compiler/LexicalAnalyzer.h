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
	//std::unordered_map<std::string, TokenType> keyword;
	std::vector<std::pair<std::string, TokenType>> keyword;

	void initKeyword();

	bool findWord(const std::string& word) const;

	bool isWhitespase(char c) const;
	bool isAlpha(char c) const;
	bool isDigit(char c) const;
	bool isAlphaNumeric(char c) const;

	std::string getNextWord();
	std::string getNextNumber();

public:
	LexicalAnalyzer(const std::string& source);

	std::vector<Token> tokenize();

	std::string getTokenTypeName(const TokenType& type) const;

	void printTokens(const std::vector<Token>& tokens) const;
};

