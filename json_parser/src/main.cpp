#include <iostream>
#include <fstream>

#include "../include/jsonparser.h"

using namespace std;

string sources[] = {"deep.json", "some.json", "obj.json", "arr.json", "few.json"};


int main(int argc, char **argv)
{
    for (string testSrc : sources) {
        JsonParser parser("../test_sources/" + testSrc);

        cout << testSrc << ":" << endl;
        for (auto rule : parser.parse()) {
            //cout << rule.getString() << endl;
            cout << "";
        }
        //parser.printJson();
        cout << endl << endl;;



//        map<string, JsonTree*> *matches = parser.tree.findKey("underRoot2");
//        for (auto& [path, node] : *matches) {
//            cout << '"' << path << "\":\n";
//            node->printTree();
//        }


        vector<JsonTree*> *match = parser.tree.findKey("underRoot2");
        string path;

        JsonTree *jt = match->back();
        for (const auto& node : *match) {
            if (!node->getValue().name.empty())
                path += node->getValue().name;
        }

        cout << '"' << path << "\":\n" << endl;
        jt->printTree();

        //delete match;


        break;
    }


    return 0;
}
