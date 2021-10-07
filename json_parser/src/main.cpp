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
        cout << endl << endl;;
        parser.printJson();
        break;
    }


    return 0;
}
