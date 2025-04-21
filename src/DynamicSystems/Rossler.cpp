#include "Rossler.h"

// imgui
#include "imgui.h"

// implot3d
#include "implot3d.h"

namespace DynamicSystems {

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> GenerateRosslerAttractor(float x0, float y0, float z0, float a, float b, float c, float dt, int steps)
{
  std::vector<float> xs, ys, zs;
  xs.reserve(steps);
  ys.reserve(steps);
  zs.reserve(steps);

  float px = x0, py = y0, pz = z0; // initial condition

  for (int i = 0; i < steps; ++i) {
    float dx = -py - pz;
    float dy = px + a * py;
    float dz = b + pz * (px - c);

    px += dx * dt;
    py += dy * dt;
    pz += dz * dt;

    xs.push_back(px);
    ys.push_back(py);
    zs.push_back(pz);
  }

  return { xs, ys, zs };
}

void DrawRosslerAttractor() {

  static float x0 = 0.1f, y0 = 0.0f, z0 = 0.0f;
  static float a = 0.2f, b = 0.2f, c = 5.7f, dt = 0.01f;
  static int steps = 30000;
  static auto [xs, ys, zs] = GenerateRosslerAttractor(x0, y0, z0, a, b, c, dt, steps);

  if (ImGui::Begin("Rossler Attractor")) {

    if (ImGui::BeginTable("RosslerTable", 2, ImGuiTableFlags_Resizable)) {
      ImGui::TableSetupColumn("ParameterTable", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Plot", ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      if (ImGui::BeginTable("RosslerParameterTable", 2, ImGuiTableFlags_NoHostExtendX)) {
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
        ImGui::TextUnformatted("a");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##a", &a, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("b");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##b", &b, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("c");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##c", &c, 0.01f))
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
          std::tie(xs, ys, zs) = GenerateRosslerAttractor(x0, y0, z0, a, b, c, dt, steps);
        }

        ImGui::EndTable();
      }

      ImGui::TableNextColumn();

      if (ImPlot3D::BeginPlot("Rossler Attractor")) {
        ImPlot3D::PlotLine("Trajectory", xs.data(), ys.data(), zs.data(), (int)xs.size());
        ImPlot3D::EndPlot();
      }

      ImGui::EndTable();
    }
  }
  ImGui::End();
}

} // namespace DynamicSystems