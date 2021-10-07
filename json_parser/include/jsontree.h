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
    NONE,
    ANON
};

struct JsonKey {
    string name;
    JsonValueType value_type;
};


class JsonTree
{
public:
    JsonTree();

    JsonTree(const JsonKey& key);

    virtual ~JsonTree();

    auto addKey(const JsonKey& key) -> void;

    // remove a child by value, note:
    // if the node has multiple children with the same name value,
    // this will only delete the first child
    auto removeKey(const JsonKey& key) -> void;

    auto setKey(const JsonKey& key) -> void;

    auto getValue() -> JsonKey&;

    auto getKeys() -> vector<JsonTree>&;

    auto findKey(const string& key) -> vector<string>;

    // the type has to have an overloaded
    // std::ostream << operator for print to work
    auto printTree(const string& key, int depth = 0) -> void;

private:
    JsonKey key;

    vector<JsonTree> children;
};

#endif // JSONTREE_H
