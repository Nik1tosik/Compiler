#include "LexicalAnalyzer.h"
#include <vector>
#include <string>
#include <iostream>

void LexicalAnalyzer::initKeyword()
{
	keyword.push_back(std::pair<std::string, TokenType>(std::string("int"), TokenType::KEYWORD));
	keyword.push_back(std::pair<std::string, TokenType>(std::string("float"), TokenType::KEYWORD));
	keyword.push_back(std::pair<std::string, TokenType>(std::string("if"), TokenType::KEYWORD));
	keyword.push_back(std::pair<std::string, TokenType>(std::string("else"), TokenType::KEYWORD));
	keyword.push_back(std::pair<std::string, TokenType>(std::string("while"), TokenType::KEYWORD));
	keyword.push_back(std::pair<std::string, TokenType>(std::string("return"), TokenType::KEYWORD));
}

bool LexicalAnalyzer::findWord(const std::string& word) const
{
	for(size_t i = 0; i < keyword.size(); ++i)
	{
		if(word == keyword[i].first)
		{
			return true;
		}
	}
	return false;
}

bool LexicalAnalyzer::isWhitespase(char c) const
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool LexicalAnalyzer::isAlpha(char c) const
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool LexicalAnalyzer::isDigit(char c) const
{
	return (c >= '0' && c <= '9');
}

bool LexicalAnalyzer::isAlphaNumeric(char c) const
{
	return isAlpha(c) || isDigit(c);
}

std::string LexicalAnalyzer::getNextWord()
{
	size_t start = position;
	while(position < input.length() && isAlphaNumeric(input[position]))
	{
		++position;
	}
	return input.substr(start, position - start);
}

std::string LexicalAnalyzer::getNextNumber()
{
	size_t start = position;
	bool hasDecimal = false;
	while((position < input.length() && isDigit(input[position])) || input[position] == '.')
	{
		if(input[position] == '.')
		{
			if(hasDecimal)
				break;
			hasDecimal = true;
		}
		++position;
	}
	return input.substr(start, position - start);;
}

LexicalAnalyzer::LexicalAnalyzer(const std::string& source)
	: input(source), position(0)
{
	initKeyword();
}

std::vector<Token> LexicalAnalyzer::tokenize()
{
	std::vector<Token> tokens;

	while(position < input.length())
	{
		char currentChar = input[position];

		// Skip whitespace
		if(isWhitespase(currentChar))
		{
			++position;
			continue;
		}

		if(isAlpha(currentChar))
		{
			std::string word = getNextWord();
			if(findWord(word))
			{
				tokens.push_back(Token(TokenType::KEYWORD, word));
			}
			else
			{
				tokens.push_back(Token(TokenType::IDENTIFIER, word));
			}
		}

		else if(isDigit(currentChar))
		{
			std::string number = getNextNumber();
			if(number.find('.') != std::string::npos)
			{
				tokens.push_back(Token(TokenType::FLOAT_LITERAL, number));
			}
			else
			{
				tokens.push_back(Token(TokenType::INTEGER_LITERAL, number));
			}
		}

		else if(currentChar == '+' || currentChar == '-' ||
				currentChar == '*' || currentChar == '/')
		{
			tokens.push_back(Token(TokenType::OPERATOR, std::string(1, currentChar)));
			++position;
		}

		else if(currentChar == '(' || currentChar == ')' ||
				currentChar == '{' || currentChar == '}' ||
				currentChar == ';')
		{
			tokens.push_back(Token(TokenType::PUNCTUATOR, std::string(1, currentChar)));
			++position;
		}

		else
		{
			tokens.push_back(Token(TokenType::UNKNOWN, std::string(1, currentChar)));
			++position;
		}
	}
	return tokens;
}

std::string LexicalAnalyzer::getTokenTypeName(const TokenType& type) const
{
	switch(type)
	{
		case TokenType::KEYWORD: return "KEYWORD";
		case TokenType::IDENTIFIER: return "IDENTIFIER";
		case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";
		case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
		case TokenType::OPERATOR: return "OPERATOR";
		case TokenType::PUNCTUATOR: return "PUNCTUATOR";
		case TokenType::UNKNOWN: return "UNKNOWN";
		default: return "UNDEFINED";
	}
}

void LexicalAnalyzer::printTokens(const std::vector<Token>& tokens) const
{
	for(size_t i = 0; i < tokens.size(); ++i)
	{
		std::cout
			<< "Type: " << getTokenTypeName(tokens[i].type)
			<< ", Value: " << tokens[i].value << std::endl;
	}
}
