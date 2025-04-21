#pragma once

// std
#include <vector>
#include <tuple>

namespace DynamicSystems {

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> GenerateLorenzAttractor(float x0, float y0, float z0, float sigma, float rho, float beta, float dt, int steps);

void DrawLorenzAttractor();

} // namespace DynamicSystems