#include "include/SpacePartition.h"
#include "include/utils.h"
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

// 对应python代码中的DHC函数
std::vector<std::vector<std::vector<int>>> SpacePartition(const std::vector<std::vector<int>> &arrs, std::vector<std::vector<int>> (*pSeedClustering)(const std::vector<std::vector<int>> &), int beta = 16)
{
    std::queue<std::vector<std::vector<int>>> q;
    q.push(arrs);
    std::vector<std::vector<std::vector<int>>> regionArrs;
    while (!q.empty())
    {
        auto front = q.front();
        q.pop();
        if (front.size() < beta)
        {
            regionArrs.push_back(front);
            continue;
        }
        auto splits = std::move(pSeedClustering(front));
        for (auto &split : splits)
        {
            std::vector<std::vector<int>> tmp;
            for (auto &i : split)
                tmp.push_back(front[i]);
            q.push(tmp);
        }
    }
    return regionArrs;
}

std::vector<std::vector<int>> SeedClustering(const std::vector<std::vector<int>> &arrs, int index)
{
    std::vector<int> yetAnotherCounter(16);
    for (const auto &arr : arrs)
        yetAnotherCounter[arr[index]]++;

    std::vector<int> nonZeroHexOfyetAnotherCounter; // python代码里的splits_nibble
    for (size_t i = 0; i < yetAnotherCounter.size(); ++i)
        if (yetAnotherCounter[i] != 0)
            nonZeroHexOfyetAnotherCounter.push_back(i);

    std::vector<std::vector<int>> clustring;
    for (const auto &nibble : nonZeroHexOfyetAnotherCounter)
    {
        std::vector<int> p;
        for (size_t i = 0; i < arrs.size(); ++i)
            if (arrs[i][index] == nibble)
                p.push_back(i);
        clustring.push_back(p);
    }
    return clustring;
}

//用leftMostIndex作为筛选，给baseline用
std::vector<std::vector<int>> SeedClusteringWithLeftMostIndex(const std::vector<std::vector<int>> &arrs)
{
    int leftMostIndex = -1;
    for(size_t i = 0; i < 32; ++i)
    {
        std::vector<int> counter(16);
        for (const auto &arr : arrs)
            counter[arr[i]]++;

        int nonZero = 0;
        for(const auto &x : counter)
            if(x != 0) ++nonZero;
        
        if(nonZero == 1) continue;
        else
        {
            leftMostIndex = i;
            break;
        }
    }
    return std::move(SeedClustering(arrs, leftMostIndex));
}

// 对应python代码中的maxcovering函数
std::vector<std::vector<int>> SeedClusteringWithMaxCovering(const std::vector<std::vector<int>> &arrs)
{
    std::vector<int> covering;
    int leftMostIndex = -1;
    int leftMostCovering = -1;
    for (size_t i = 0; i < 32; ++i)
    {
        std::vector<int> counter(16);
        for (const auto &arr : arrs)
            counter[arr[i]]++;

        int nonZero = 0;
        // s是所有出现过，但出现次数不为1的十六进制数的次数之和
        int s = 0;
        for (const auto &x : counter)
        {
            if (x != 0)
                ++nonZero;
            if (x != 1)
                s += x;
        }

        if (nonZero == 1)
            covering.push_back(-1);
        else
        {
            if (leftMostIndex == -1)
            {
                leftMostIndex = i;
                leftMostCovering = s;
            }
            covering.push_back(s);
        }
    }
    int maxCoveringIndex = 0;
    int maxCovering = -1;
    for (size_t i = 0; i < covering.size(); ++i)
        if (covering[i] > maxCovering)
        {
            maxCovering = covering[i];
            maxCoveringIndex = i;
        }
    if (maxCovering - leftMostCovering <= maxCoveringIndex - leftMostIndex)
        maxCoveringIndex = leftMostIndex;
    
    return std::move(SeedClustering(arrs, maxCoveringIndex));
}

// 对应python代码中的show_region函数
std::string ClusteringRegion(const std::vector<std::vector<int>> &arrs)
{
    std::string addressSpace;

    for (int i = 0; i < 32; ++i)
    {
        std::vector<int> counter(16);
        for (const auto &arr : arrs)
            counter[arr[i]]++;

        int numOfGreaterThanZero = 0;
        int indexOfGreaterThanZero = 0;
        for (size_t j = 0; j < counter.size(); ++j)
        {
            if (counter[j] > 0)
            {
                ++numOfGreaterThanZero;
                indexOfGreaterThanZero = j;
            }
        }

        if (numOfGreaterThanZero == 1)
            addressSpace.push_back(intToHexChar(indexOfGreaterThanZero));
        else
            addressSpace.push_back('*');
    }
    return addressSpace;
}

// void testPartition(const std::string &path)
// {
//     std::cout << path << std::endl;
//     std::ifstream input(path);
//     if (!input.is_open())
//     {
//         std::cerr << "Oops, failed to open file." << std::endl;
//         return;
//     }
//     std::string line;
//     std::vector<std::vector<int>> arrs;

//     while (getline(input, line))
//     {
//         std::vector<int> arr;
//         for (auto &i : line)
//             arr.push_back(hexCharToInt(i));
//         arrs.push_back(arr);
//     }
//     input.close();
//     auto results = SpacePartition(arrs, SeedClusteringWithMaxCovering);
//     for (auto &r : results)
//     {
//         std::cout << ClusteringRegion(r) << std::endl;
//         std::cout << "-------------------------" << std::endl;
//     }
//     std::cout << results.size() << std::endl;
// }
