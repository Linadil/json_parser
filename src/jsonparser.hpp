#include <string_view>
#include <map>
#include <stack>

#include "../lib/libtree/tree.hpp"
#include "jsonitemtype.hpp"
#include "jsonitem.hpp"
#include "symbol.hpp"
#include "production.hpp"

using namespace std;
namespace alionapermes {

typedef tree<JsonItem> JsonTree;
typedef string_view::const_iterator sview_citer;

using ProduceFunc = void (*)(void);


class JsonParser
{
public:
    JsonParser(const string_view& json);

    const JsonTree&
    parse();

    Symbol
    lexer(char c);

private:
    string_view json;
    JsonTree items;
    stack<Symbol> expected;

    void
    produceObject();

    void
    produceArray();

    void
    producePair();

    void
    produceTrue();

    void
    produceFalse();

    void
    produceNull();
};

}
