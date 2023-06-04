#pragma once
#include <utility>
#include <vector>

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> OutlierSeedDetection(const std::vector<std::vector<int>>&, float);
std::vector<float> IsolationTree(const std::vector<std::vector<int>>& arrs, int index);
void testDetection();