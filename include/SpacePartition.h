#pragma once
#include <vector>
#include <string>

std::vector<std::vector<std::vector<int>>> SpacePartition(std::vector<std::vector<int>>& arrs, int beta);
std::vector<std::vector<int>> SeedClustering(const std::vector<std::vector<int>>& arrs);
std::string ShowRegions(const std::vector<std::vector<int>>& arrs);
void testPartition(const std::string& path);