#include "include/SpacePartition.h"
#include "include/utils.h"
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::vector<std::vector<int>>> SpacePartition(std::vector<std::vector<int>>& arrs, int beta = 16)
{
    std::queue<std::vector<std::vector<int>>> q;
    q.push(arrs);
    std::vector<std::vector<std::vector<int>>> regionArrs;
    while(!q.empty())
    {
        auto front = q.front(); q.pop();
        if(front.size() < beta)
        {
            regionArrs.push_back(front);
            continue;
        }
        auto splits = SeedClustering(front);
        for(auto& split : splits)
        {
            std::vector<std::vector<int>> tmp;
            for(auto& i : split)
            {
                tmp.push_back(front[i]);
            }
            q.push(tmp);
        }
    }
    return regionArrs;
}

std::vector<std::vector<int>> SeedClustering(const std::vector<std::vector<int>>& arrs)
{
    std::vector<int> covering;
    int leftMostIndex = -1;
    int leftMostCovering = -1;
    for(size_t i = 0; i < 32; ++i)
    {
        std::vector<int> t;
        for(const auto& arr : arrs)
            t.push_back(arr[i]);
        std::vector<int> splits(16);
        for(const auto& hex : t)
            splits[hex]++;

        int nonZero = 0;
        //s是所有出现过，但出现次数不为1的十六进制数的次数之和
        int s = 0;
        for(const auto& x : splits)
        {
            if(x != 0) ++nonZero;
            if(x != 1) s += x;
        }

        if(nonZero == 1) covering.push_back(-1);
        else
        {
            if(leftMostIndex == -1)
            {
                leftMostIndex = i;
                leftMostCovering = s;
            }
            covering.push_back(s);
        }
    }
    int maxCoveringIndex = 0;
    int maxCovering = -1;
    for(size_t i = 0; i < covering.size(); ++i)
    {
        if(covering[i] > maxCovering)
        {
            maxCovering = covering[i];
            maxCoveringIndex = i;
        }
    }
    if(maxCovering - leftMostCovering <= maxCoveringIndex - leftMostIndex)
        maxCoveringIndex = leftMostIndex;
    
    std::vector<int> yetAnotherSplits(16);
    for(const auto& arr : arrs)
    {
        yetAnotherSplits[arr[maxCoveringIndex]]++;
    }
    std::vector<int> nonZeroHexOfyetAnotherSplits;     //python代码里的splits_nibble
    for(size_t i = 0; i < yetAnotherSplits.size(); ++i)
        if(yetAnotherSplits[i] != 0)
            nonZeroHexOfyetAnotherSplits.push_back(i);
    
    std::vector<std::vector<int>> clustring;
    for(const auto& nibble : nonZeroHexOfyetAnotherSplits)
    {
        std::vector<int> p;
        for(size_t i = 0; i < arrs.size(); ++i)
        {
            if(arrs[i][maxCoveringIndex] == nibble) p.push_back(i);
        }
        clustring.push_back(p);
    }
    return clustring;
}

std::string ClustringRegions(const std::vector<std::vector<int>>& arrs)
{
    std::string addressSpace;
    

    for(int i = 0; i < 32; ++i)
    {
        std::vector<int> splits(16);
        for(const auto& arr : arrs)
            splits[arr[i]]++;

        int numOfGreaterThanZero = 0;
        int indexOfGreaterThanZero = 0;
        for(size_t j = 0; j < splits.size(); ++j)
        {
            if(splits[j] > 0)
            {
                ++numOfGreaterThanZero;
                indexOfGreaterThanZero = j;
            }
        }

        if(numOfGreaterThanZero == 1)
        {
            addressSpace.push_back(intToHexChar(indexOfGreaterThanZero));
        }
        else
            addressSpace.push_back('*');
    }
    return addressSpace;
}

void test(const std::string& path)
{
    std::cout << path << std::endl;
    std::ifstream input(path);
    if(!input.is_open())
    {
        std::cerr << "Oops, failed to open file." << std::endl;
        return;
    }
    std::string line;
    std::vector<std::vector<int>> arrs;

    while(getline(input, line))
    {
        std::vector<int> arr;
        for(auto& i : line)
        {
            arr.push_back(hexCharToInt(i));
        }
        arrs.push_back(arr);
    }
    input.close();
    auto results = SpacePartition(arrs);
    int p = 0;
    for(auto& r : results)
    {
        std::cout << ClustringRegions(r) << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
    std::cout << results.size() << std::endl;
}
