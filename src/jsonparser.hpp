#include <string_view>

#include "../lib/libtree/tree.hpp"
#include "jsonitemtype.hpp"
#include "jsonitem.hpp"
#include "symbol.hpp"

namespace alionapermes {

typedef tree<JsonItem> JsonTree;
typedef std::string_view::const_iterator sview_citer;


class JsonParser
{
public:
    const JsonTree&
    parse();

    Symbol
    lexer(char c);

private:
    JsonTree items;
    
    const JsonTree&
    (*handler)(sview_citer begin, sview_citer end);

    const JsonTree&
    objectParser(sview_citer begin, sview_citer end);

    const JsonTree&
    arrayParser(sview_citer begin, sview_citer end);

    const JsonTree&
    stringParser(sview_citer begin, sview_citer end);

    const JsonTree&
    numberParser(sview_citer begin, sview_citer end);

    const JsonTree&
    trueParser(sview_citer begin, sview_citer end);

    const JsonTree&
    falseParser(sview_citer begin, sview_citer end);

    const JsonTree&
    nullParser(sview_citer begin, sview_citer end);
};

}
