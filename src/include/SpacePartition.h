#pragma once
#include <vector>
#include <string>

std::vector<std::vector<std::vector<int>>> SpacePartition(const std::vector<std::vector<int>> &arrs, std::vector<std::vector<int>> (*pSeedClustering)(const std::vector<std::vector<int>> &), int beta);
std::vector<std::vector<int>>SeedClusteringWithLeftMostIndex(const std::vector<std::vector<int>>& arrs);
std::vector<std::vector<int>> SeedClusteringWithMaxCovering(const std::vector<std::vector<int>>& arrs);
std::string ClusteringRegion(const std::vector<std::vector<int>>& arrs);
// void testPartition(const std::string& path);