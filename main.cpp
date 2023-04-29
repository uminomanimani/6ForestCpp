#include "include/IPv6Parse.h"
#include "include/SpacePartition.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("./seeds");
    ofstream output("./seeds.parse");

    string line;
    while(getline(input, line))
    {
        std::string parsed = std::move(Parse(line));
        output << parsed << endl;
    }

    input.close();
    output.close();

    test("./seeds.parse");
    return 0;
}