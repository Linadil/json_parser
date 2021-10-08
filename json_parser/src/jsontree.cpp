#include "../include/jsontree.h"

typedef JsonTree JT;


JT::JsonTree()
{

}


JT::JsonTree(const JsonItem& item)
{
    this->item = item;
}


JT::~JsonTree()
{

}


void
JT::addItem(const JsonItem& item)
{
    JsonTree child(item);
    child.parent = this;

    this->items.push_back(JsonTree(item));
}


void
JT::removeItem(const JsonItem& item)
{
    for (uint i = 0; i < this->items.size(); i++) {
        if (this->items.at(i).item.name == item.name) {
            this->items.erase(this->items.begin() + i);
            return;
        }
    }
}


void
JT::setItem(const JsonItem& item)
{
    this->item = item;
}


JsonItem&
JT::getItem()
{
    return this->item;
}


vector<JT>&
JT::getItems()
{
    return this->items;
}


string
JT::extractPath()
{
    string path;
    stack<string> parts;

    for (JsonTree *cur = this; cur->parent != NULL; cur = this->parent)
        parts.push(cur->item.name);

    while (!parts.empty()) {
        path += "/" + parts.top();
        parts.pop();
    }

    return path;
}


vector<JsonTree*>
JT::findAllItems(const string& item)
{
    static vector<JsonTree*> matches;

    for (auto& node : this->items) {
        if ((node.item.name == item) && (node.item.value_type != NONE))
            matches.push_back(&node);

        node.findAllItems(item);
    }

    return matches;
}


JsonTree*
JT::findItem(const string& item)
{
    static vector<JsonTree*> nodes;

    for (auto& node : this->items) {
        nodes.push_back(&node);

        if ((node.item.name == item) && (node.item.value_type != NONE))
            return nodes.back();

        if (node.findItem(item) == NULL)
            nodes.pop_back();
    }

    return NULL;
}


void
JT::printTree(int depth)
{
    for (int i = 0; i < depth; i++)
        cout << (i != depth - 1 ? "    " : "|... ");


    if (!this->item.name.empty()) {
        if (this->item.key_type == STR)
            cout << '"' << this->item.name << "\" ";
        else
            cout << this->item.name + ' ';
    }


    switch (this->item.value_type) {
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


    for (uint i = 0; i < this->items.size(); i++)
        this->items.at(i).printTree(depth + 1);
}
