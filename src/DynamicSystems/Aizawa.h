#pragma once

// std
#include <vector>
#include <tuple>

namespace DynamicSystems {

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> GenerateAizawaAttractor(float x0, float y0, float z0, float a, float b, float c, float d, float e, float f, float dt, int steps);

void DrawAizawaAttractor();

} // namespace DynamicSystems