#include <gtest/gtest.h>
#include <stdio.h>
#include "../include/fp-cpp/statement.hpp"
#include "../src/symbol.hpp"
#include "../src/jsonparser.hpp"

using namespace alionapermes;
using namespace std;


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
