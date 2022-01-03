#ifndef TREE_H
#define TREE_H

#include <vector>


template <typename T>
class tree
{
public:
    T value;

    tree();
    tree(const T& value);
    ~tree();

    void
    add(const tree<T>& t);

    const std::vector<tree<T>*>&
    getChildren() const;

private:
    std::vector<tree<T>*> children;
};

// #############################################################

template<typename T>
tree<T>::tree() {}

template <typename T>
tree<T>::tree(const T& value)
{
    this->value = value;
}

template <typename T>
tree<T>::~tree()
{
    for (tree<T>* child : this->children) {
        delete child;
    }
}

template <typename T>
void
tree<T>::add(const tree<T>& t)
{ this->children.push_back(new tree<T>(t.value)); }

template <typename T>
const std::vector<tree<T>*>&
tree<T>::getChildren() const
{ return this->children; }

#endif
