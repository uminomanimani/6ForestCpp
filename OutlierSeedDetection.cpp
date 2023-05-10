#include "include/OutlierSeedDetection.h"
#include "include/utils.h"
#include <unordered_set>
#include <iostream>

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> OutlierSeedDetection(const std::vector<std::vector<int>>& arrs, float threshold)
{
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> returnValue;
    std::vector<int> a;
    std::vector<float> weight(arrs.size());

    for(int i = 0; i < 32; ++i)
    {
        std::vector<int> counter(16);
        for(const auto& arr : arrs)
            ++counter[arr[i]];
        
        int numOfGreaterThanZero = 0;
        for(size_t j = 0; j < counter.size(); ++j)
            if(counter[j] > 0)
                ++numOfGreaterThanZero;
        
        if(numOfGreaterThanZero == 1)
            continue;
        else
        {
            auto w = std::move(IsolationTree(arrs, i));
            for(decltype(w.size()) j = 0; j < w.size(); ++j)
                weight[j] += w[j];
        }
    }

    for(decltype(arrs.size()) i = 0; i < arrs.size(); ++i)
    {
        if(weight[i] < threshold)
            returnValue.first.push_back(arrs[i]);
        else
            returnValue.second.push_back(arrs[i]);
    }
    return returnValue;
}

std::vector<float> IsolationTree(const std::vector<std::vector<int>>& arrs, int index)
{
    std::vector<float> weight(arrs.size());
    std::vector<int> counter(16);
    std::unordered_set<int> singleNibbles;

    for(const auto& arr : arrs)
        ++counter[arr[index]];
    
    for(decltype(counter.size()) i = 0; i < counter.size(); ++i)
        if(counter[i] == 1)
            singleNibbles.insert(i);
    
    for(decltype(arrs.size()) i = 0; i < arrs.size(); ++i)
        if(singleNibbles.find(arrs[i][index]) != singleNibbles.end())
            weight[i] = 1.0 / singleNibbles.size();
    
    return weight;
}

void testDetection()
{
    std::vector<std::string> addresses = {
        "2a0107c8aacb024c505400fffe2d61ad",
        "2a0107c8aacb02540000000000000001",
        "2a0107c8aacb02580000000000000001",
        "2a0107c8aacb0258505400fffec5f4af",
        "2a0107c8aacb02650000000000000001",
        "2a0107c8aacb0276505400fffe93673b",
        "2a0107c8aacb027a0000000000000000",
        "2a0107c8aacb027c0000000000000001",
        "2a0107c8aacb027e0000000000000001",
        "2a0107c8aacb027f10de51e8eb667583",
        "2a0107c8aacb02810000000000000001",
        "2a0107c8aacb02900000000000000001",
        "2a0107c8aacb02ba505400fffee8eb27",
        "2a0107c8aacb02c4505400fffe8312eb"
    };

    std::vector<std::vector<int>> arrs;
    for(auto& line : addresses)
    {
        std::vector<int> arr;
        for(auto& i : line)
            arr.push_back(hexCharToInt(i));
        arrs.push_back(arr);
    }
    auto r = OutlierSeedDetection(arrs, 5.0f);
}