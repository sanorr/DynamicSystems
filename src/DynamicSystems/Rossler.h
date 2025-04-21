#pragma once

// std
#include <vector>
#include <tuple>

namespace DynamicSystems {

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> GenerateRosslerAttractor(float x0, float y0, float z0, float a, float b, float c, float dt, int steps);

void DrawRosslerAttractor();

} // namespace DynamicSystems