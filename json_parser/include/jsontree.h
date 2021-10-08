#ifndef JSONTREE_H
#define JSONTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;

enum JsonItemType {
    NUM,
    STR,
    OBJ,
    ARR,
    BOOL,
    _NULL,
    NONE,
};

struct Match {
    string path;
    int depth;
};

struct JsonItem {
    string name;
    JsonItemType key_type;
    JsonItemType value_type;
};


class JsonTree
{
public:
//    static vector<pair<string, string>> matches;

    JsonTree();

    JsonTree(const JsonItem& key);

    virtual ~JsonTree();

    auto addKey(const JsonItem& key) -> void;

    // remove a child by value, note:
    // if the node has multiple children with the same name value,
    // this will only delete the first child
    auto removeKey(const JsonItem& key) -> void;

    auto setKey(const JsonItem& key) -> void;

    auto getValue() -> JsonItem&;

    auto getKeys() -> vector<JsonTree>&;

    auto extractPath() -> string;
    auto findAllKeys(const string& key) -> vector<JsonTree*>;
    auto findKey(const string& key) -> JsonTree*;
    //auto findKey(vector<JsonTree*>& nodes, const string& key) -> bool;//vector<JsonTree*>*;

    // the type has to have an overloaded
    // std::ostream << operator for print to work
    auto printTree(int depth = 0) -> void;

private:
    JsonItem key;
    JsonTree *parent;


    vector<JsonTree> children;
};

#endif // JSONTREE_H
