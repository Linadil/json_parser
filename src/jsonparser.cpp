#include "jsonparser.hpp"

#include <stack>

using namespace std;
using namespace alionapermes;

typedef JsonParser   jp;
typedef JsonItem     ji;
typedef JsonItemType jit;


const JsonTree&
jp::objectParser(sview_citer begin, sview_citer end)
{
    stack<Symbol> expected;
    expected.push(Symbol::NTS_OBJECT);

    for (auto it = begin; it != end; it++) {
        Symbol sym = jp::lexer(*it);

        switch (expected.top()) {
            //
        }
    }
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
