#ifndef JSONTREE_H
#define JSONTREE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum JsonValueType {
    NUM,
    STR,
    OBJ,
    ARR,
    LITERALL,
    NONE
};

struct JsonKey {
    string name;
    JsonValueType value_type;
};


class JsonTree
{
public:
    JsonTree();

    JsonTree(const string& key);

    virtual ~JsonTree();

    auto addKey(const string& key) -> void;

    // remove a child by value, note:
    // if the node has multiple children with the same name value,
    // this will only delete the first child
    auto removeKey(const string& key) -> void;

    auto setKey(const string& key) -> void;

    auto getValue() -> string&;

    auto getKeys() -> vector<JsonTree>&;

    // the type has to have an overloaded
    // std::ostream << operator for print to work
    auto printTree(const int depth = 0) -> void;

private:
    string key;

    vector<JsonTree> children;
};

#endif // JSONTREE_H
