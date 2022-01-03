#pragma once

#include <string_view>
#include <map>
#include <stack>
#include <functional>

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
    using produce_func = void (*)(json_parser*);
    const char* json;
    json_tree items;
    stack<symbol> expected;
    map<symbol, map<symbol, function<void(void)>>> table;

    void
    initTable();

    void
    matchTable(symbol sym);

    function<void(void)> produceObject = [this]() {
        this->expected.push(symbol::TS_OBJECT_END);
        this->expected.push(symbol::NTS_PAIR);
        this->expected.push(symbol::TS_OBJECT_START);
    };

    function<void(void)> produceArray = [this]() {
        this->expected.push(symbol::TS_ARRAY_END);
        this->expected.push(symbol::NTS_ITEM);
        this->expected.push(symbol::TS_ARRAY_START);
    };

    void
    produceNumber();

    void
    produceString();

    void
    producePair();

    void
    produceTrue();

    void
    produceFalse();

    void
    produceNull();
};

}
