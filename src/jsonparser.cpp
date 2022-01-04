#include "jsonparser.hpp"

using namespace std;
using namespace alionapermes;

typedef json_parser jp;
typedef json_item   ji;
typedef json_item_t jit;


jp::json_parser(const char* json)
{
    this->json = json;
    this->expected.push(symbol::NTS_ITEM);
    this->initTable();
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

        try {
            this->matchWithExpected(sym);
        } catch (const char* str) {
            printf("error: %s\n", str);
        }
    }
}

void
jp::matchWithExpected(symbol sym)
{
    auto produce = this->table[this->expected.top()][sym];
    this->expected.pop();

    if (produce) {
        produce();
    } else {
        throw "unexcepted token";
    }
}

void
jp::initTable()
{
    this->table[NTS_ITEM][TS_OBJECT_START] = this->produceObject;
    this->table[NTS_ITEM][TS_ARRAY_START]  = this->produceArray;
    this->table[NTS_ITEM][TS_T]            = this->produceTrue;
    this->table[NTS_ITEM][TS_F]            = this->produceFalse;
    this->table[NTS_ITEM][TS_N]            = this->produceNull;
    this->table[NTS_ITEM][TS_MINUS]        = this->produceNumber;
    this->table[NTS_ITEM][TS_NUMBER]       = this->produceNumber;
    this->table[NTS_ITEM][TS_MARK]         = this->produceString;

    this->table[NTS_OBJECT_END_COMMA][TS_OBJECT_END] = this->produceObjectEnd;
    this->table[NTS_OBJECT_END_COMMA][TS_COMMA]      = this->produceNextPair;

    this->table[NTS_ARRAY_END_COMMA][TS_ARRAY_END] = this->produceArrayEnd;
    this->table[NTS_ARRAY_END_COMMA][TS_COMMA]     = this->produceNextItem;

    this->table[NTS_PAIR][TS_MARK] = this->producePair;

    this->table[NTS_STRING][TS_NUMBER] = this->produceString; // number
    this->table[NTS_STRING][TS_DOT]    = this->produceString; // dot
    this->table[NTS_STRING][TS_CHAR]   = this->produceString; // char
    this->table[NTS_STRING][TS_MARK]   = this->produceMark;   // mark

    this->table[NTS_NUMBER][TS_NUMBER]     = this->produceNumber;
    this->table[NTS_NUMBER][TS_DOT]        = this->produceNumber;
    this->table[NTS_NUMBER][TS_OBJECT_END] = this->produceObjectEnd;
    this->table[NTS_NUMBER][TS_ARRAY_END]  = this->produceArrayEnd;
}
