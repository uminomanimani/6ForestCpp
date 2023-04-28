#include "include/SpacePartition.h"
#include <queue>

std::vector<std::vector<std::vector<char>>> SpacePartition(const std::vector<std::vector<char>>& arrs, int beta = 16)
{
    std::queue<std::vector<std::vector<char>>> q;
    q.push(arrs);
    std::vector<std::vector<std::vector<char>>> regionArrs;
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
            std::vector<std::vector<char>> tmp;
            for(auto& i : split)
            {
                tmp.push_back(front[i]);
            }
            regionArrs.push_back(tmp);
        }
    }
    return regionArrs;
}
