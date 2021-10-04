#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stack>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include "symbols.h"

//#define DEBUG

using namespace std;


class Rule
{
public:
    Rule();

    Rule(int ruleNum);

    auto getNum() -> int;
    auto getString() -> string;

private:
    int num;
};


class JsonParser
{
public:
    JsonParser();

    JsonParser(const string& path);

    ~JsonParser();

    auto parse() -> vector<Rule>;

private:
    stack<Symbol> symbol_stack;
    map<Symbol, map<Symbol, int>> table;

    ifstream src;


    auto lexer(const char sym) -> Symbol;
    auto getRuleByNum() -> void;
#ifdef DEBUG
    auto printStack(stack<Symbol> stack) -> void;
#endif
};

#endif // JSONPARSER_H
