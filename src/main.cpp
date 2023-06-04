#include "include/IPv6Parse.h"
#include "include/SpacePartition.h"
#include "include/OutlierSeedDetection.h"
#include "include/utils.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <utility>
#include <exception>
#include <getopt.h>

void Preprocession()
{
    std::ifstream input("./dataset/seeds");
    std::ofstream output("./dataset/seeds.parse");
    std::string address;
    while(std::getline(input, address))
    {
        std::string parsed = move(Parse(address));
        output << parsed << std::endl;
    }
    input.close();
    output.close();
}

std::vector<int> Baseline(int beta)
{
    std::ifstream input("./dataset/seeds.parse");

    std::string line;
    std::vector<std::vector<int>> arrs;

    while (std::getline(input, line))
    {
        std::vector<int> arr;
        for (auto &i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }
    input.close();
    std::ofstream output("./Baseline.txt");
    auto r = move(SpacePartition(arrs, SeedClusteringWithLeftMostIndex, beta));
    std::vector<int> areaCount;
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
        output << x << std::endl;
    output.close();
    return areaCount;
}

std::vector<int> Experiment(float threshold, int beta)
{
    std::ifstream input("./dataset/seeds.parse");
    std::string line;
    std::vector<std::vector<int>> arrs;

    while (std::getline(input, line))
    {
        std::vector<int> arr;
        for (auto &i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }

    input.close();

    std::ofstream output("./Experiment.txt");
    auto r = std::move(SpacePartition(arrs, SeedClusteringWithMaxCovering, beta));
    std::vector<int> areaCount;
    for (const auto &x : r)
    {
        auto i = std::move(OutlierSeedDetection(x, threshold));
        auto p = std::move(ClusteringRegion(i.first));
        int counter = 0;
        // output << p << endl;
        for (const auto &c : p)
            if (c == '*') ++counter;
        areaCount.push_back(counter);
    }
    
    for (const auto &x : areaCount)
        output << x << std::endl;
    output.close();    
    
    return areaCount;
}

std::pair<float, int> ArgumentsParse(int argc, char **argv)
{
    if(argc != 5) throw std::invalid_argument("Invalid arguments number.");
    int option;
    int beta = 0;
    float threshold = 0.0f;
    std::pair<float, int> returnValue;
    while ((option = getopt(argc, argv, "b:t:")) != -1) {
        switch (option) {
            case 'b':
                beta = std::stoi(optarg);
                if (beta <= 0) throw std::invalid_argument("beta must be greater than 0.");
                returnValue.second = beta;
                break;
            case 't':
                threshold = std::stof(optarg);
                if(threshold <= 0) throw std::invalid_argument("threshold must be greater than 0.");
                returnValue.first = threshold;
                break;
            case '?':
                break;
            default:
                break;
        }
    }
    return returnValue;
}

int main(int argc, char **argv)
{
    int beta = 0;
    float threshold = 0.0f;
    try
    {
        auto arguments = std::move(ArgumentsParse(argc, argv));
        threshold = arguments.first;
        beta = arguments.second;
        // std::cout << threshold << ',' << beta << std::endl;
    }
    catch(const std::exception& e)
    {
        std::endl(std::cerr << e.what());
        std::endl(std::cerr << "Usage");
        std::endl(std::cerr);
        std::endl(std::cerr << "  " << argv[0] << " -b <beta[positive int]> -t <threshold[positive float]>");
        return -1;
    }

    Preprocession();
    Baseline(beta);
    Experiment(threshold, beta);
    return 0;
}