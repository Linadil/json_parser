#include "../lib/libtree/tree.hpp"
#include "jsonitem.hpp"


namespace alionapermes {

typedef tree<JsonItem> JsonTree;

class JsonParser
{
public:
    const JsonTree&
    parse();

private:
    JsonTree items;
    
    JsonTree (*handler)(void);
};

}
