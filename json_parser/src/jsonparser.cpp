#include "../include/jsonparser.h"

typedef JsonParser JP;


JP::JsonParser()
{

}


JP::JsonParser(const string& path)
{
    src.open(path);

    // [expected symbol][catched symbol] = rule number
    table[NTS_OBJ][TS_OBJ_START]   = 1; // { PAIR }
    table[NTS_ARR][TS_ARR_START]   = 2; // [ VALUE ]
    table[NTS_VALUE][TS_OBJ_START] = 3; // OBJ
    table[NTS_VALUE][TS_ARR_START] = 4; // ARR
    table[NTS_VALUE][TS_MARK]      = 5; // " LTR "
    table[NTS_KEY][TS_MARK]        = 6; // " LTR "
    table[TS_OBJ_END][TS_NEXT]     = 7; // , PAIR
    table[TS_ARR_END][TS_NEXT]     = 8; // , VALUE
    table[NTS_PAIR][TS_MARK]       = 9; // KEY : VALUE
    table[NTS_VALUE][TS_DIGIT]     = 10;
}

JP::~JsonParser()
{
    src.close();
}


Symbol
JP::lexer(const char sym)
{
    if (sym < ' ')
        return MOD_KEY;

    if ((sym >= '0') && (sym <= '9'))
        return TS_DIGIT;

    switch (sym)
    {
    case '{': return TS_OBJ_START;
    case '}': return TS_OBJ_END;
    case '[': return TS_ARR_START;
    case ']': return TS_ARR_END;
    case '"': return TS_MARK;
    case ':': return TS_CHAIN;
    case ',': return TS_NEXT;
    case ' ':
    case '\n':
    case '\t':
        return ESCAPE;
    default: return TS_UNKOWN;
    }
}


vector<Rule>
JP::parse()
{
    vector<Rule> rules;

    bool readingString = false;
    string line;
    int ltr;

#ifdef DEBUG
    bool skiped = false;
#endif

    symbol_stack.push(TS_EOS);
    symbol_stack.push(NTS_OBJ);


    while (!src.eof()) {
        ltr = 0;

        getline(src, line);

        while (!symbol_stack.empty() && ltr < line.size()) {
            Symbol sym = lexer(line[ltr]);
#ifdef DEBUG
            if (!skiped)
                printStack(symbol_stack);
            skiped = true;
#endif
//            switch (sym)
//            {
//            case TS_MARK:
//                if (symbol_stack.top() == NTS_STR) {
//                    symbol_stack.pop();
//                    ltr++;
//                }
//                continue;;
//            case ESCAPE:
//                ltr++;
//                continue;
//            default: break;
//            }

            // если в данный момент ожидается строка
            if (symbol_stack.top() == NTS_STR) {
                if (sym == TS_MARK) {
                    symbol_stack.pop();
                    //cout << endl << "STRING END" << endl << endl;
                }
                ltr++;
                continue;
            } else if (sym == ESCAPE) {
                ltr++;
                continue;
            }

            if (sym == TS_UNKOWN) {
                cout << "unexpected token: " << line[ltr]
                     << "(" << (int)line[ltr] << ")" << endl;
                return rules;
            }


            if (sym == symbol_stack.top()) {
                ltr++;
                symbol_stack.pop();
            } else {
                int ruleNum = table[symbol_stack.top()][sym];

                if (ruleNum > 0)
                    rules.push_back(Rule(ruleNum));

                switch (ruleNum)
                {
                case 1: // [OBJ][OBJ START]
                    symbol_stack.pop();
                    symbol_stack.push(TS_OBJ_END);   // }
                    symbol_stack.push(NTS_PAIR);     // PAIR
                    symbol_stack.push(TS_OBJ_START); // {
                    break;
                case 2: // [ARR][ARR START]
                    symbol_stack.pop();
                    symbol_stack.push(TS_ARR_END);   // ]
                    symbol_stack.push(NTS_VALUE);    // VALUE
                    symbol_stack.push(TS_ARR_START); // [
                    break;
                case 3: // [VALUE][OBJ START]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_OBJ); // OBJ
                    break;
                case 4: // [VALUE][ARR START]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_ARR); // ARR
                    break;
                case 5: // [VALUE][MARK]
                case 6: // [KEY][MARK]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_STR); // STR
                    ltr++; // skip first "
                    //symbol_stack.push(TS_MARK); // "
                    break;
                case 7: // [OBJ END][NEXT]
                    symbol_stack.push(NTS_PAIR); // PAIR
                    symbol_stack.push(TS_NEXT);  // ,
                    break;
                case 8: // [ARR END][NEXT]
                    symbol_stack.push(NTS_VALUE); // VALUE
                    symbol_stack.push(TS_NEXT);   // ,
                    break;
                case 9: // [PAIR][MARK]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_VALUE); // VALUE
                    symbol_stack.push(TS_CHAIN);  // :
                    symbol_stack.push(NTS_KEY);   // KEY
                    break;
                case 10: // [VALUE][DIGIT]
                    symbol_stack.push(NTS_NUM); // NUM
                    break;
                default:
                    if (sym != MOD_KEY) {
                        cout << "_" << (int)line[ltr] << "_";
                        return rules;
                    }
                }
            }

#ifdef DEBUG
            skiped = false;
#endif
        }
    }

    return rules;
}


#ifdef DEBUG

void
JP::printStack(stack<Symbol> stack)
{
    cout << "stack at the moment:" << endl;
    while (!stack.empty()) {
        switch (stack.top())
        {
        case NTS_OBJ: cout << "NTS_OBJ "; break;
        case NTS_ARR: cout << "NTS_ARR "; break;
        case NTS_VALUE: cout << "NTS_VALUE "; break;
        case NTS_PAIR: cout << "NTS_PAIR "; break;
        case NTS_KEY: cout << "NTS_KEY "; break;
        case NTS_STR: cout << "NTS_STR "; break;
        case NTS_NUM: cout << "NTS_NUM "; break;

        case TS_OBJ_START: cout << "TS_OBJ_START "; break;
        case TS_OBJ_END: cout << "TS_OBJ_END "; break;
        case TS_ARR_START: cout << "TS_ARR_START "; break;
        case TS_ARR_END: cout << "TS_ARR_END "; break;
        case TS_MARK: cout << "TS_MARK "; break;
        case TS_BSLASH: cout << "TS_BSLASH "; break;
        case TS_CHAIN: cout << "TS_CHAIN "; break;
        case TS_NEXT: cout << "TS_NEXT "; break;

        case TS_UNKOWN: cout << "TS_UNKOWN "; break;
        case TS_EOS: cout << "TS_EOS "; break;

        case ESCAPE: cout << "ESCAPE "; break;
        case MOD_KEY: cout << "MOD_KEY "; break;
        }

        stack.pop();
    }
    cout << endl << "###########################################" << endl;
}

#endif


Rule::Rule()
{

}

Rule::Rule(int ruleNum)
{
    num = ruleNum;
}

int
Rule::getNum()
{
    return num;
}

string
Rule::getString()
{
    switch (num)
    {
    case 1: return "OBJ -> { PAIR }";
    case 2: return "ARR -> [ VALUE ]";
    case 3: return "VALUE -> OBJ";
    case 4: return "VALUE -> ARR";
    case 5: return "VALUE -> STR";
    case 6: return "KEY -> STR";
    case 7: return "OBJ_END -> , PAIR";
    case 8: return "ARR_END -> , VALUE";
    case 9: return "PAIR -> KEY : VALUE";
    case 10: return "VALUE -> NUM";
    default: return "UNKOWN PRODUCTION";
    }
}
