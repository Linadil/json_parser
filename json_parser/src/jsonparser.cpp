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
    table[NTS_VALUE][TS_T]         = 11; // TRUE
    table[NTS_VALUE][TS_F]         = 12; // FALSE
    table[NTS_VALUE][TS_N]         = 13; // NULL

#ifdef TREE
    //nodes.push(&tree);
    //nodes.top()->setKey("root");
    tree.addKey("root");
    nodes.push(&tree);
    nodes.push(&tree.getKeys().back());
#endif
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
    case '\\': return TS_BSLASH;
    case 't': return TS_T;
    case 'r': return TS_R;
    case 'u': return TS_U;
    case 'e': return TS_E;
    case 'f': return TS_F;
    case 'a': return TS_A;
    case 'l': return TS_L;
    case 's': return TS_S;
    case 'n': return TS_N;
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

    bool escape_mark = false;
    string line;
    int ltr;

#ifdef DEBUG
    bool skiped = false;
#endif

    symbol_stack.push(TS_EOS);
    symbol_stack.push(NTS_OBJ);
    //symbol_stack.push(NTS_VALUE);


    string key;


    while (!src.eof()) {
        ltr = 0;
        //JsonKey key;

        getline(src, line);

        while (!symbol_stack.empty() && ltr < line.size()) {
            Symbol sym = lexer(line[ltr]);
#ifdef DEBUG
            if (!skiped)
                printStack(symbol_stack);
            skiped = true;
#endif
//            switch (sym) {
//            case TS_OBJ_START:
//            case TS_ARR_START:
//                nodes.push(&nodes.top()->getKeys().back());
//                break;
//            case TS_OBJ_END:
//            case TS_ARR_END:
//                nodes.top()->addKey(key);
//                nodes.pop();
//                key.clear();
//                break;
//            default: break;
//            }
            //cout << "kek ";
            if (sym != NTS_STR) {
                switch (sym) {
                case TS_CHAIN:
#ifdef TREE
                    if (!nodes.empty())
                        nodes.push(&nodes.top()->getKeys().back());
                    else
                        cout << "bad push\n";
#endif
                    break;
//                case TS_OBJ_START:
//                case TS_ARR_START:
//                    nodes.top()->addKey("");
//                    nodes.push(&nodes.top()->getKeys().back());
//                    break;
                case TS_OBJ_END:
#ifdef TREE
                    if (!nodes.empty())
                        nodes.pop();
                    else
                        cout << "!! 1 !!\n";
#endif
                case TS_ARR_END:
#ifdef TREE
                    if (!nodes.empty())
                        nodes.pop();
                    else
                        cout << "!! 2 !!\n";
#endif
//                    if (!nodes.empty()) {
//                        nodes.pop();
//                        cout << "end"; }
//                    else
//                        cout << "!! POP !!" << endl;
                    break;
                default: break;
                }
            }


            // если в данный момент ожидается строка
            if (symbol_stack.top() == NTS_STR) {
                switch (sym) {
                case TS_MARK:
                    if (!escape_mark) {
#ifdef TREE
                        if (!nodes.empty())
                            nodes.top()->addKey(key);
                        else
                            cout << "bad key save\n";
#endif
                        key.clear();
                        symbol_stack.pop();
                        escape_mark = false;
                    }
                    break;
                case TS_BSLASH:
                    escape_mark = true;
                    break;
                default:
                    if (escape_mark)
                        escape_mark = false;
                    key += line[ltr];
                    break;
                }

                ltr++;
                continue;
            } else if (sym == ESCAPE) {
                ltr++;
                continue;
            }


            if (symbol_stack.top() == NTS_NUM) {
                switch (sym) {
                case TS_DIGIT:
                    key += line[ltr];
                    ltr++;
                    continue;
                case TS_NEXT:
                case TS_OBJ_END:
                case TS_ARR_END:
                    symbol_stack.pop();
#ifdef TREE
                    if (!nodes.empty())
                        nodes.top()->addKey(key);
                    else
                        cout << "!! 3 !!\n";
#endif
                    key.clear();
                    break;
                default:
                    cout << "unexcepted token: " << line[ltr] << endl;
                    return rules;
                }
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

                switch (ruleNum) {
                case 1: // [OBJ][OBJ START]
                    symbol_stack.pop();
                    symbol_stack.push(TS_OBJ_END);   // }
                    symbol_stack.push(NTS_PAIR);     // PAIR
                    symbol_stack.push(TS_OBJ_START); // {
#ifdef TREE
                    if (!nodes.empty()) {
                        nodes.top()->addKey("");
                        nodes.push(&nodes.top()->getKeys().back());
                    } else {
                        cout << "!! 4 !!\n";
                    }
#endif
                    break;
                case 2: // [ARR][ARR START]
                    symbol_stack.pop();
                    symbol_stack.push(TS_ARR_END);   // ]
                    symbol_stack.push(NTS_VALUE);    // VALUE
                    symbol_stack.push(TS_ARR_START); // [
#ifdef TREE
                    if (!nodes.empty()) {
                        nodes.top()->addKey("");
                        nodes.push(&nodes.top()->getKeys().back());
                    } else {
                        cout << "!! 4 !!\n";
                    }
#endif
                    break;
                case 3: // [VALUE][OBJ START]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_OBJ); // OBJ
                    //key.value_type = JsonValueType::OBJ;
                    break;
                case 4: // [VALUE][ARR START]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_ARR); // ARR
                    //key.value_type = JsonValueType::ARR;
                    break;
                case 5: // [VALUE][MARK]
#ifdef TREE
                    if (!nodes.empty())
                        nodes.push(&nodes.top()->getKeys().back());  //// ????
                    else
                        cout << "bad push 1\n";
#endif
                case 6: // [KEY][MARK]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_STR); // STR
                    ltr++; // skip first "
                    break;
                case 7: // [OBJ END][NEXT]
                    symbol_stack.push(NTS_PAIR); // PAIR
                    symbol_stack.push(TS_NEXT);  // ,
#ifdef TREE
                    if (!nodes.empty()) {
                        nodes.pop();
                        cout << "next\n"; }
                    else
                        cout << "DANGEROUS POP!!" << endl;
#endif
                    break;
                case 8: // [ARR END][NEXT]
                    symbol_stack.push(NTS_VALUE); // VALUE
                    symbol_stack.push(TS_NEXT);   // ,
//                    nodes.top()->addKey(key);
//                    key.clear();
                    break;
                case 9: // [PAIR][MARK]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_VALUE); // VALUE
                    symbol_stack.push(TS_CHAIN);  // :
                    symbol_stack.push(NTS_KEY);   // KEY
                    break;
                case 10: // [VALUE][DIGIT]
                    symbol_stack.pop();
                    symbol_stack.push(NTS_NUM); // NUM
#ifdef TREE
                    if (!nodes.empty())
                        nodes.push(&nodes.top()->getKeys().back());  //// ????
                    else
                        cout << "bad push 1\n";
#endif
                    break;
                case 11: // [VALUE][TRUE]
                    symbol_stack.pop();
                    symbol_stack.push(TS_E);
                    symbol_stack.push(TS_U);
                    symbol_stack.push(TS_R);
                    symbol_stack.push(TS_T);
                    //key.value_type = JsonValueType::LITERALL;
                    break;
                case 12: // [VALUE][FALSE]
                    symbol_stack.pop();
                    symbol_stack.push(TS_E);
                    symbol_stack.push(TS_S);
                    symbol_stack.push(TS_L);
                    symbol_stack.push(TS_A);
                    symbol_stack.push(TS_F);
                    //key.value_type = JsonValueType::LITERALL;
                    break;
                case 13: // [VALUE][NULL]
                    symbol_stack.pop();
                    symbol_stack.push(TS_L);
                    symbol_stack.push(TS_L);
                    symbol_stack.push(TS_U);
                    symbol_stack.push(TS_N);
                    //key.value_type = JsonValueType::LITERALL;
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


void
JP::printJson()
{
    tree.printTree();
}


#ifdef DEBUG

void
JP::printStack(stack<Symbol> stack)
{
    cout << "stack at the moment:" << endl;
    while (!stack.empty()) {
        switch (stack.top()) {
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
        case TS_DIGIT: cout << "TS_DIGIT "; break;

        case TS_T: cout << "TS_T "; break;
        case TS_R: cout << "TS_A "; break;
        case TS_U: cout << "TS_U "; break;
        case TS_E: cout << "TS_E "; break;
        case TS_F: cout << "TS_F "; break;
        case TS_A: cout << "TS_A "; break;
        case TS_L: cout << "TS_L "; break;
        case TS_S: cout << "TS_S "; break;
        case TS_N: cout << "TS_N "; break;

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
    switch (num) {
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
    case 11: return "VALUE -> TRUE";
    case 12: return "VALUE -> FALSE";
    case 13: return "VALUE -> NULL";
    default: return "UNKOWN PRODUCTION";
    }
}
