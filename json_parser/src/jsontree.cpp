#include "../include/jsontree.h"

typedef JsonTree JT;


JT::JsonTree()
{

}


JT::JsonTree(const JsonKey& key)
{
    this->key = key;
}


JT::~JsonTree()
{

}


void
JT::addKey(const JsonKey& key)
{
    this->children.push_back(JsonTree(key));
}


void
JT::removeKey(const JsonKey& key)
{
    for (uint i = 0; i < this->children.size(); i++) {
        if (this->children.at(i).key.name == key.name) {
            this->children.erase(this->children.begin() + i);
            return;
        }
    }
}


void
JT::setKey(const JsonKey& key)
{
    this->key = key;
}


JsonKey&
JT::getValue()
{
    return this->key;
}


vector<JT>&
JT::getKeys()
{
    return this->children;
}


// the type has to have an overloaded
// std::ostream << operator for print to work
void
JT::printTree(const int depth)
{
    for (int i = 0; i < depth; i++) {
        if (i != depth - 1)
            cout << "    ";
        else
            cout << "|-- ";
    }

    cout << this->key.name << endl;

    for (uint i = 0; i < this->children.size(); i++) {
        this->children.at(i).printTree(depth + 1);
    }
}
