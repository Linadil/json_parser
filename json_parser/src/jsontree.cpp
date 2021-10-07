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


vector<string>
JT::findKey(const string& key)
{
    vector<string> matches;



    return matches;
}


// the type has to have an overloaded
// std::ostream << operator for print to work
void
JT::printTree(const string& key, int depth)
{
//    static string path;
//    static bool found = false;

    for (int i = 0; i < depth; i++) {
        if (i != depth - 1)
            cout << "    ";
        else
            cout << "|-- ";
    }

    cout << this->key.name;
    switch (this->key.value_type) {
    case OBJ:
        cout << " (obj)\n";
        break;
    case ARR:
        cout << " (arr)\n";
        break;
    case NUM:
        cout << " (num)\n";
        break;
    case STR:
        cout << " (str)\n";
        break;
    case LITERALL:
        cout << " (liter)\n";
        break;
    case NONE:
        cout << " (none)\n";
        break;
    }

//    if (this->key.value_type == NONE)
//        path.clear();

//    if (found)
//        cout << this->key.name << endl;

//    if (!this->key.name.empty()) {
//        path += "/" + this->key.name;
//    }

//    if (this->key.name == key) {
//        found = true;
//        cout << path << ": ";
//    }

    for (uint i = 0; i < this->children.size(); i++) {
        this->children.at(i).printTree(key, depth + 1);
    }
}
