#include "include/IPv6Parse.h"
#include "include/SpacePartition.h"
#include "include/OutlierSeedDetection.h"
#include "include/utils.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("./seeds");
    ofstream output("./seeds.parse");

    string address;
    while(getline(input, address))
    {
        std::string parsed = std::move(Parse(address));
        output << parsed << endl;
    }

    input.close();
    output.close();

    std::string path = "./seeds.parse";
    std::cout << path << std::endl;
    std::ifstream seedInput(path);
    if(!seedInput.is_open())
    {
        std::cerr << "Oops, failed to open file." << std::endl;
        return 0;
    }
    std::string line;
    std::vector<std::vector<int>> arrs;

    while(getline(seedInput, line))
    {
        std::vector<int> arr;
        for(auto& i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }
    input.close();
    auto results = SpacePartition(arrs, 16);

    for(const auto& r : results)
    {
        auto x = OutlierSeedDetection(r, 12.0f);
        cout << ShowRegions(x.first) << endl;
    }

    return 0;
}