#include "../include/jsontree.h"

typedef JsonTree JT;


JT::JsonTree()
{

}


JT::JsonTree(const JsonItem& key)
{
    this->key = key;
}


JT::~JsonTree()
{

}


void
JT::addKey(const JsonItem& key)
{
    JsonTree child(key);
    child.parent = this;

    this->children.push_back(JsonTree(key));
}


void
JT::removeKey(const JsonItem& key)
{
    for (uint i = 0; i < this->children.size(); i++) {
        if (this->children.at(i).key.name == key.name) {
            this->children.erase(this->children.begin() + i);
            return;
        }
    }
}


void
JT::setKey(const JsonItem& key)
{
    this->key = key;
}


JsonItem&
JT::getValue()
{
    return this->key;
}


vector<JT>&
JT::getKeys()
{
    return this->children;
}


string
JT::extractPath()
{
    string path;
    stack<string> parts;

    for (JsonTree *cur = this; cur->parent != NULL; cur = this->parent)
        parts.push(cur->key.name);

    while (!parts.empty()) {
        path += "/" + parts.top();
        parts.pop();
    }

    return path;
}


vector<JsonTree*>
JT::findAllKeys(const string& key)
{
    static vector<JsonTree*> matches;

    for (auto& node : this->children) {
        if (node.key.name == key)
            matches.push_back(&node);

        node.findAllKeys(key);
    }

//    JsonTree *match;

//    for (auto& node : this->children) {
//        match = node.findKey(key);

//        while (match != NULL) {
//            matches.push_back(match);

//        }
//    }

    return matches;
}


JsonTree*
JT::findKey(const string& key)
{
    static vector<JsonTree*> nodes;

    for (auto& node : this->children) {
        nodes.push_back(&node);

        if (node.key.name == key)
            return nodes.back();

        if (node.findKey(key) == NULL)
            nodes.pop_back();
    }

    return NULL;
}


//bool
//JT::findKey(vector<JsonTree*>& nodes, const string& key)
//{
//    //static vector<JsonTree*> nodes;

//    for (auto& node : this->children) {
//        nodes.push_back(&node);

//        if (node.key.name == key) {
//            //return nodes;
//            return true;
//        }

//        if (!node.findKey(nodes, key))
//            nodes.pop_back();
//    }

//    return false;//NULL;
//}


// the type has to have an overloaded
// std::ostream << operator for print to work
void
JT::printTree(int depth)
{
    for (int i = 0; i < depth; i++)
        cout << (i != depth - 1 ? "    " : "|... ");


    if (!this->key.name.empty()) {
        if (this->key.key_type == STR)
            cout << '"' << this->key.name << "\" ";
        else
            cout << this->key.name + ' ';
    }


    switch (this->key.value_type) {
    case OBJ:
        cout << "(object)\n";
        break;
    case ARR:
        cout << "(array)\n";
        break;
    case NUM:
        cout << "(number)\n";
        break;
    case STR:
        cout << "(string)\n";
        break;
    case BOOL:
        cout << "(boolean)\n";
        break;
    case _NULL:
        cout << "(null)\n";
        break;
    case NONE:
        cout << endl;
        break;
    default: break;
    }


    for (uint i = 0; i < this->children.size(); i++)
        this->children.at(i).printTree(depth + 1);
}
