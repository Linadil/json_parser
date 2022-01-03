#pragma once

namespace alionapermes {

enum symbol
{
    NTS_ITEM,   // <string>
    NTS_OBJECT, // { NTS_PAIR , }
    NTS_ARRAY,  // [ ITEM , ]
    NTS_PAIR,   // NAME : ITEM
    NTS_TRUE,   // true
    NTS_FALSE,  // false
    NTS_NULL,   // null
    NTS_STRING, // <string>

    TS_OBJECT_START, // {
    TS_OBJECT_END,   // }
    TS_ARRAY_START,  // [
    TS_ARRAY_END,    // ]
    TS_CHAIN,        // :
    TS_COMMA,        // ,
    TS_CHAR,         // 'a'-'z', '0'-'9', <special symbols> ????
    TS_NUMBER,       // 0..9
    TS_MARK,         // "
    TS_ESCAPE,       // eh?
    
    TS_T, // t char
    TS_R, // r char
    TS_U, // u char
    TS_E, // e char

    TS_F, // f char
    TS_A, // a char
    TS_L, // l char
    TS_S, // s char
//  TS_E, // e char

    TS_N, // n char
//  TS_U, // u char
//  TS_L, // l char
//  TS_L, // l char

    TS_UNKNOWN,
};

}
