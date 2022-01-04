#pragma once

#include <string_view>
#include <map>
#include <stack>
#include <functional>
#include <stdio.h>

#include "../include/libtree/tree.hpp"
#include "../include/fp-cpp/statement.hpp"
// #include "jsonitemtype.hpp"
#include "jsonitem.hpp"
#include "symbol.hpp"
#include "production.hpp"

#define TESTING

namespace alionapermes {

using namespace std;

typedef tree<json_item> json_tree;
typedef string_view::const_iterator sview_citer;


class json_parser
{
public:
    json_parser(const char* json);

    const json_tree&
    parse();

    symbol
    lexer(char c);

#ifndef TESTING
private:
#endif
    const char* json;
    json_tree items;
    stack<symbol> expected;
    map<symbol, map<symbol, function<void(void)>>> table;

    void
    initTable();

    void
    matchWithExpected(symbol sym);

    function<void(void)> produceObject = [this]() {
        this->expected.push(NTS_OBJECT_END_COMMA);
        this->expected.push(NTS_PAIR);
        this->expected.push(TS_OBJECT_START);
    };

    function<void(void)> produceArray = [this]() {
        this->expected.push(NTS_ARRAY_END_COMMA);
        this->expected.push(NTS_ITEM);
        this->expected.push(TS_ARRAY_START);
    };

    function<void(void)> produceNumber = [this]() {
        this->expected.push(NTS_NUMBER);
    };

    function<void(void)> produceString = [this]() {
        this->expected.push(NTS_STRING);
    };

    function<void(void)> producePair = [this]() {
        this->expected.push(NTS_ITEM);
        this->expected.push(TS_CHAIN);
        this->expected.push(NTS_STRING);
    };

    function<void(void)> produceTrue = [this]() {
        this->expected.push(TS_E);
        this->expected.push(TS_U);
        this->expected.push(TS_R);
        this->expected.push(TS_T);
    };

    function<void(void)> produceFalse = [this]() {
        this->expected.push(TS_E);
        this->expected.push(TS_S);
        this->expected.push(TS_L);
        this->expected.push(TS_A);
        this->expected.push(TS_F);
    };

    function<void(void)> produceNull = [this]() {
        this->expected.push(TS_L);
        this->expected.push(TS_L);
        this->expected.push(TS_U);
        this->expected.push(TS_N);
    };

    function<void(void)> produceNextPair = [this]() {
        this->expected.push(NTS_PAIR);
        this->expected.push(TS_COMMA);
    };

    function<void(void)> produceNextItem = [this]() {
        this->expected.push(NTS_ITEM);
        this->expected.push(TS_COMMA);
    };

    function<void(void)> produceObjectEnd = [this]() {
        this->expected.push(TS_OBJECT_END);
    };

    function<void(void)> produceArrayEnd = [this]() {
        this->expected.push(TS_ARRAY_END);
    };

    function<void(void)> produceMark = [this]() {
        this->expected.push(TS_MARK);
    };

    // function<void(void)> produceNothing = [this]() {
    //     //
    // };
};

}
