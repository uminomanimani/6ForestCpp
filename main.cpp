#include "include/IPv6Parse.h"
#include "include/SpacePartition.h"
#include "include/OutlierSeedDetection.h"
#include "include/utils.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

void Preprocession()
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
}

void Baseline()
{
    ifstream input("./seeds.parse");

    std::string line;
    std::vector<std::vector<int>> arrs;

    while (getline(input, line))
    {
        std::vector<int> arr;
        for (auto &i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }

    auto r = std::move(SpacePartition(arrs, SeedClusteringWithLeftMostIndex, 16));
    std::vector<int> areaCount;
    for (const auto &x : r)
    {
        auto p = std::move(ClusteringRegion(x));
        int counter = 0;
        for (const auto &c : p)
            if (c == '*') ++counter;
        areaCount.push_back(counter);
    }
    ofstream output("./Baseline.txt");
    for (const auto &x : areaCount)
        output << x << endl;
    output.close();
    input.close();
}

void Experiment()
{
    ifstream input("./seeds.parse");

    std::string line;
    std::vector<std::vector<int>> arrs;

    while (getline(input, line))
    {
        std::vector<int> arr;
        for (auto &i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }

    auto r = std::move(SpacePartition(arrs, SeedClusteringWithMaxCovering, 16));
    std::vector<int> areaCount;
    for (const auto &x : r)
    {
        auto i = std::move(OutlierSeedDetection(x, 4.0f));
        auto p = std::move(ClusteringRegion(i.first));
        int counter = 0;
        for (const auto &c : p)
            if (c == '*') ++counter;
        areaCount.push_back(counter);
    }
    ofstream output("./Experiment.txt");
    for (const auto &x : areaCount)
    output << x << endl;
    output.close();
    
    input.close();
}

int main()
{
    Preprocession();
    Baseline();
    Experiment();
    return 0;
}