#include "include/OutlierSeedDetection.h"
#include "include/utils.h"
#include <unordered_set>
// #include <iostream>

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> OutlierSeedDetection(const std::vector<std::vector<int>> &arrs, float threshold)
{
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> returnValue;
    std::vector<float> weight(arrs.size());

    for (int i = 0; i < 32; ++i)
    {
        std::vector<int> counter(16);
        for (const auto &arr : arrs)
            ++counter[arr[i]];

        int numOfGreaterThanZero = 0;
        for (decltype(counter.size()) j = 0; j < counter.size(); ++j)
            if (counter[j] > 0)
                ++numOfGreaterThanZero;

        if (numOfGreaterThanZero == 1)
            continue;
        else
        {
            auto w = std::move(IsolationTree(arrs, i));
            for (decltype(w.size()) j = 0; j < w.size(); ++j)
                weight[j] += w[j];
        }
    }

    for (decltype(arrs.size()) i = 0; i < arrs.size(); ++i)
    {
        if (weight[i] < threshold)
            returnValue.first.push_back(arrs[i]);
        else
            returnValue.second.push_back(arrs[i]);
    }
    return returnValue;
}

std::vector<float> IsolationTree(const std::vector<std::vector<int>> &arrs, int index)
{
    std::vector<float> weight(arrs.size());
    std::vector<int> counter(16);
    std::unordered_set<int> singleNibbles;

    for (const auto &arr : arrs)
        ++counter[arr[index]];

    for (decltype(counter.size()) i = 0; i < counter.size(); ++i)
        if (counter[i] == 1)
            singleNibbles.insert(i);

    for (decltype(arrs.size()) i = 0; i < arrs.size(); ++i)
        if (singleNibbles.find(arrs[i][index]) != singleNibbles.end())
            weight[i] = 1.0 / singleNibbles.size();

    return weight;
}
