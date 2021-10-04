#ifndef SYMBOLS_H
#define SYMBOLS_H


enum Symbol {
    NTS_OBJ,      // {PAIR}
    NTS_ARR,      // [VALUE]
    NTS_VALUE,    //
    NTS_PAIR,     // KEY:VALUE
    NTS_KEY,      // "STR"
    NTS_STR,      //
    NTS_NUM,      //

    TS_OBJ_START, // {
    TS_OBJ_END,   // }
    TS_ARR_START, // [
    TS_ARR_END,   // ]
    TS_MARK,      // "
    TS_DIGIT,     // 0-9
    TS_BSLASH,    // '\'
    TS_CHAIN,     // :
    TS_NEXT,      // ,

    TS_UNKOWN,
    TS_EOS,

    ESCAPE,
    MOD_KEY,
};


#endif
