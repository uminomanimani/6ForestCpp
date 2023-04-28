#include "include/SpacePartition.h"
#include <queue>

std::vector<std::vector<std::vector<char>>> SpacePartition(const std::vector<std::vector<char>>& arrs)
{
    std::queue<std::vector<std::vector<char>>> q;
    q.push(arrs);
    std::vector<std::vector<std::vector<char>>> regionArrs;
    while(!q.empty())
    {
        auto front = q.front(); q.pop();
        if(front.size() < 16)
        {
            regionArrs.push_back(front);
            continue;
        }
        auto splits = SeedClustering(front);
        for(auto& split : splits)
        {
            
        }
    }
}
