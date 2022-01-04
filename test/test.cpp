#include <gtest/gtest.h>
#include <stdio.h>
#include "../include/fp-cpp/statement.hpp"
#include "../src/symbol.hpp"
#include "../src/jsonparser.hpp"

using namespace alionapermes;
using namespace std;


TEST(simple, matchPattern)
{
    char z = 'z';
    int test = match(z, -1, {
        {'x', 1},
        {'y', 2},
        {'z', 3}
    });

    ASSERT_EQ(test, 3);
}

// TEST(funcs, matchPattern)
// {
//     symbol sym = symbol::NTS_OBJECT;
//     using func = void (*)(void);

//     func f1 = [](){ printf("NTS OBJECT\n"); };
//     func f2 = [](){ printf("NTS ARRAY\n"); };

//     auto produce = match<symbol, func>(
//         sym, (func)NULL, {
//         {symbol::NTS_OBJECT, f1},
//         {symbol::NTS_ARRAY, f2}
//     });

//     ASSERT_NE(produce, (func)NULL);
//     // produce();
// }

TEST(stack, matchPattern)
{
    json_parser jp("");
    jp.matchWithExpected(symbol::TS_OBJECT_START);

    ASSERT_EQ(jp.expected.top(), symbol::TS_OBJECT_START);
    jp.expected.pop();
    ASSERT_EQ(jp.expected.top(), symbol::NTS_PAIR);
    jp.expected.pop();
    ASSERT_EQ(jp.expected.top(), symbol::NTS_OBJECT_END_COMMA);
    jp.expected.pop();
    ASSERT_TRUE(jp.expected.empty());
}

TEST(parse, jp)
{
    json_parser jp("{\"key\":123}");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
