#include "jsonparser.hpp"

using namespace std;
using namespace alionapermes;

typedef json_parser jp;
typedef json_item   ji;
typedef json_item_t jit;


jp::json_parser(const char* json)
{
    this->json = json;
    this->expected.push(symbol::NTS_OBJECT);
    this->initTable();
}

void
jp::producePair()
{
    this->expected.push(symbol::NTS_STRING);
    this->expected.push(symbol::TS_CHAIN);
    this->expected.push(symbol::NTS_ITEM);
}

void
jp::produceTrue()
{
    this->expected.push(symbol::TS_T);
    this->expected.push(symbol::TS_R);
    this->expected.push(symbol::TS_U);
    this->expected.push(symbol::TS_E);
}

void
jp::produceFalse()
{
    this->expected.push(symbol::TS_F);
    this->expected.push(symbol::TS_A);
    this->expected.push(symbol::TS_L);
    this->expected.push(symbol::TS_S);
    this->expected.push(symbol::TS_E);
}

void
jp::produceNull()
{
    this->expected.push(symbol::TS_N);
    this->expected.push(symbol::TS_U);
    this->expected.push(symbol::TS_L);
    this->expected.push(symbol::TS_L);
}

symbol
jp::lexer(char c)
{
    if ((('0' <= c) && (c <= '9')) || (c == '-')) {
        return symbol::TS_NUMBER;
    }

    switch (c) {
        case '{': return symbol::TS_OBJECT_START;
        case '}': return symbol::TS_OBJECT_END;
        case '[': return symbol::TS_ARRAY_START;
        case ']': return symbol::TS_ARRAY_END;
        case ':': return symbol::TS_CHAIN;
        case ',': return symbol::TS_COMMA;

        case 't': return symbol::TS_T;
        case 'r': return symbol::TS_R;
        case 'u': return symbol::TS_U;
        case 'e': return symbol::TS_E;

        case 'f': return symbol::TS_F;
        case 'a': return symbol::TS_A;
        case 'l': return symbol::TS_L;
        case 's': return symbol::TS_S;
//      case 'e': return symbol::TS_E;

        case 'n': return symbol::TS_N;
//      case 'u': return symbol::TS_U;
//      case 'l': return symbol::TS_L;
//      case 'l': return symbol::TS_L;

        default: return symbol::TS_UNKNOWN;
    }
}

const json_tree&
jp::parse()
{
    const char* ltr = this->json;

    while (*ltr != '\0') {
        symbol sym = this->lexer(*ltr);

        if (this->expected.top() == sym) {
            ltr++;
            this->expected.pop();
            continue;
        }

        this->matchTable(sym);
        // todo
    }
}

void
jp::matchTable(symbol sym)
{
    auto produce = this->table[this->expected.top()][sym];
    this->expected.pop();
    produce();
}

void
jp::initTable()
{
    this->table[NTS_OBJECT][TS_OBJECT_START] = produceObject;
    this->table[NTS_ARRAY][TS_ARRAY_START]   = produceArray;
}
