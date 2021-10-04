#include <iostream>
#include <fstream>

#include "../include/jsonparser.h"

using namespace std;

string sources[] = {"obj.json", "arr.json", "few.json", "deep.json"};


int main(int argc, char **argv)
{
    for (string testSrc : sources) {
        //ifstream file("test_sources/" + testSrc);
        //string buf;

        JsonParser parser("../test_sources/" + testSrc);

        cout << testSrc << ":" << endl;
        for (auto rule : parser.parse()) {
            cout << rule.getString() << endl;
        }
        cout << endl;

        //file.close();
    }


    return 0;
}
