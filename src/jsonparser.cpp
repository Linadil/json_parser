#include "jsonparser.hpp"

using namespace std;
using namespace alionapermes;

typedef JsonParser   jp;
typedef JsonItem     ji;
typedef JsonItemType jit;


jp::JsonParser(const string_view& json)
{
    this->json = json;
    this->expected.push(Symbol::NTS_ITEM);
}

void
jp::produceObject()
{
    this->expected.push(Symbol::TS_OBJECT_START);
    this->expected.push(Symbol::NTS_PAIR);
    this->expected.push(Symbol::TS_OBJECT_END);
}

void
jp::produceArray()
{
    this->expected.push(Symbol::TS_ARRAY_START);
    this->expected.push(Symbol::NTS_ITEM);
    this->expected.push(Symbol::TS_ARRAY_END);
}

void
jp::producePair()
{
    this->expected.push(Symbol::NTS_STRING);
    this->expected.push(Symbol::TS_CHAIN);
    this->expected.push(Symbol::NTS_ITEM);
}

void
jp::produceTrue()
{
    this->expected.push(Symbol::TS_T);
    this->expected.push(Symbol::TS_R);
    this->expected.push(Symbol::TS_U);
    this->expected.push(Symbol::TS_E);
}

void
jp::produceFalse()
{
    this->expected.push(Symbol::TS_F);
    this->expected.push(Symbol::TS_A);
    this->expected.push(Symbol::TS_L);
    this->expected.push(Symbol::TS_S);
    this->expected.push(Symbol::TS_E);
}

void
jp::produceNull()
{
    this->expected.push(Symbol::TS_N);
    this->expected.push(Symbol::TS_U);
    this->expected.push(Symbol::TS_L);
    this->expected.push(Symbol::TS_L);
}

Symbol
jp::lexer(char c)
{
    if (('0' <= c) && (c <= '9')) {
        return Symbol::TS_NUMBER;
    }

    switch (c) {
        case '{': return Symbol::TS_OBJECT_START;
        case '}': return Symbol::TS_OBJECT_END;
        case '[': return Symbol::TS_ARRAY_START;
        case ']': return Symbol::TS_ARRAY_END;
        case ':': return Symbol::TS_CHAIN;
        case ',': return Symbol::TS_COMMA;

        case 't': return Symbol::TS_T;
        case 'r': return Symbol::TS_R;
        case 'u': return Symbol::TS_U;
        case 'e': return Symbol::TS_E;

        case 'f': return Symbol::TS_F;
        case 'a': return Symbol::TS_A;
        case 'l': return Symbol::TS_L;
        case 's': return Symbol::TS_S;
//      case 'e': return Symbol::TS_E;

        case 'n': return Symbol::TS_N;
//      case 'u': return Symbol::TS_U;
//      case 'l': return Symbol::TS_L;
//      case 'l': return Symbol::TS_L;

        default: return Symbol::TS_UNKNOWN;
    }
}

const JsonTree&
jp::parse()
{
    const char* ltr = this->json.data();

    while (ltr != '\0') {
        Symbol sym = this->lexer(*ltr);

        if (this->expected.top() == sym) {
            ltr++;
            this->expected.pop();
            continue;
        }

        //
    }
}
