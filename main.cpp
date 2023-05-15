#include "include/IPv6Parse.h"
#include "include/SpacePartition.h"
#include "include/OutlierSeedDetection.h"
#include "include/utils.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

int beta = 256;
float threshold = 8.0f;

void Preprocession()
{
    ifstream input("./seeds");
    ofstream output("./seeds.parse");
    string address;
    while(getline(input, address))
    {
        string parsed = move(Parse(address));
        output << parsed << endl;
    }
    input.close();
    output.close();
}

vector<int> Baseline()
{
    ifstream input("./seeds.parse");

    string line;
    vector<vector<int>> arrs;

    while (getline(input, line))
    {
        vector<int> arr;
        for (auto &i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }
    input.close();
    ofstream output("./Baseline.txt");
    auto r = move(SpacePartition(arrs, SeedClusteringWithLeftMostIndex, beta));
    vector<int> areaCount;
    for (const auto &x : r)
    {
        auto p = move(ClusteringRegion(x));
        // output << p << endl;
        int counter = 0;
        for (const auto &c : p)
            if (c == '*') ++counter;
        areaCount.push_back(counter);
    }
    
    for (const auto &x : areaCount)
        output << x << endl;
    output.close();
    return areaCount;
}

vector<int> Experiment()
{
    ifstream input("./seeds.parse");

    string line;
    vector<vector<int>> arrs;

    while (getline(input, line))
    {
        vector<int> arr;
        for (auto &i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }
    input.close();
    ofstream output("./Experiment.txt");
    auto r = move(SpacePartition(arrs, SeedClusteringWithMaxCovering, beta));
    vector<int> areaCount;
    for (const auto &x : r)
    {
        auto i = move(OutlierSeedDetection(x, threshold));
        auto p = move(ClusteringRegion(i.first));
        int counter = 0;
        // output << p << endl;
        for (const auto &c : p)
            if (c == '*') ++counter;
        areaCount.push_back(counter);
    }
    
    for (const auto &x : areaCount)
        output << x << endl;
    output.close();    
    
    return areaCount;
}

int main()
{
    Preprocession();
    Baseline();
    Experiment();
    return 0;
}