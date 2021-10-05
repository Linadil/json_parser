#include <iostream>
#include <fstream>

#include "../include/jsonparser.h"

using namespace std;

string sources[] = {"obj.json", "arr.json", "few.json", "deep.json"};


int main(int argc, char **argv)
{
//    JsonTree tree;

//    tree.addKey({"z", JsonValueType::OBJ});
//    tree.getKeys()[0].addKey({"k", JsonValueType::NUM});
//    tree.getKeys()[0].addKey({"y", JsonValueType::STR});

//    tree.printTree();

//    stack<string*> test;
//    string a = "a str";
//    string b = "b str";

//    test.push(&a);
//    test.push(&b);

//    while (!test.empty()) {
//        *test.top() = "*empty*";
//        test.pop();
//    }

//    cout << "a: " << a << endl;
//    cout << "b: " << b << endl;

    return 0;

    for (string testSrc : sources) {
        //ifstream file("test_sources/" + testSrc);
        //string buf;

        JsonParser parser("../test_sources/" + testSrc);

        cout << testSrc << ":" << endl;
        for (auto rule : parser.parse()) {
            cout << rule.getString() << endl;
        }
        cout << endl;
        break;
        //file.close();
    }


    return 0;
}
