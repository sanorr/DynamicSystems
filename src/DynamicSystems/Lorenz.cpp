#include "Lorenz.h"

// imgui
#include "imgui.h"

// implot3d
#include "implot3d.h"

namespace DynamicSystems {


std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> GenerateLorenzAttractor(float x0, float y0, float z0, float sigma, float rho, float beta, float dt, int steps)
{
  std::vector<float> xs, ys, zs;
  xs.reserve(steps);
  ys.reserve(steps);
  zs.reserve(steps);

  float px = x0, py = y0, pz = z0; // initial condition

  for (int i = 0; i < steps; ++i) {
    float dx = sigma * (py - px);
    float dy = px * (rho - pz) - py;
    float dz = px * py - beta * pz;

    px += dx * dt;
    py += dy * dt;
    pz += dz * dt;

    xs.push_back(px);
    ys.push_back(py);
    zs.push_back(pz);
  }

  return { xs, ys, zs };
}

void DrawLorenzAttractor() {

  static float x0 = 0.1f, y0 = 0.0f, z0 = 0.0f;
  static float sigma = 10.0f, rho = 28.0f, beta = 8.0f / 3.0f, dt = 0.01f;
  static int steps = 10000;
  static auto [xs, ys, zs] = GenerateLorenzAttractor(x0, y0, z0, sigma, rho, beta, dt, steps);

  if (ImGui::Begin("Lorenz Attractor")) {

    if (ImGui::BeginTable("LorenzTable", 2, ImGuiTableFlags_Resizable)) {
      ImGui::TableSetupColumn("ParameterTable", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Plot", ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      if (ImGui::BeginTable("LorenzParameterTable", 2, ImGuiTableFlags_NoHostExtendX)) {
        ImGui::TableSetupColumn("Parameter", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 200.0f);
        // ImGui::TableHeadersRow();

        bool changed = false;

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("X0");
        ImGui::TableNextColumn();
        ImGui::PushItemWidth(-FLT_MIN);
        if (ImGui::DragFloat("##x0", &x0, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Y0");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##y0", &y0, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Z0");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##z0", &z0, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Sigma");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##Sigma", &sigma, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Rho");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##Rho", &rho, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Beta");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##Beta", &beta, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Delta T");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##dt", &dt, 0.01f, 0.0f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Steps");
        ImGui::TableNextColumn();
        if (ImGui::DragInt("##steps", &steps, 10, 0))
          changed |= true;

        if (changed) {
          std::tie(xs, ys, zs) = GenerateLorenzAttractor(x0, y0, z0, sigma, rho, beta, dt, steps);
        }

        ImGui::EndTable();
      }

      ImGui::TableNextColumn();

      if (ImPlot3D::BeginPlot("Lorenz Attractor")) {
        ImPlot3D::PlotLine("Trajectory", xs.data(), ys.data(), zs.data(), (int)xs.size());
        ImPlot3D::EndPlot();
      }

      ImGui::EndTable();
    }
  }
  ImGui::End();
}

} // namespace DynamicSystems