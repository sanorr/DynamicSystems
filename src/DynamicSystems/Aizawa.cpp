#include "Aizawa.h"

// imgui
#include "imgui.h"

// implot3d
#include "implot3d.h"

namespace DynamicSystems {

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> GenerateAizawaAttractor(float x0, float y0, float z0, float a, float b, float c, float d, float e, float f, float dt, int steps)
{
  std::vector<float> xs, ys, zs;
  xs.reserve(steps);
  ys.reserve(steps);
  zs.reserve(steps);

  float px = x0, py = y0, pz = z0; // initial condition

  for (int i = 0; i < steps; ++i) {
    float dx = (pz - b) * px - d * py;
    float dy = d * px + (pz - b) * py;
    float dz = c + a * pz - pz * pz * pz / 3.0f - ((px * px + py * py) * (1.0f + e * pz)) + f * pz * px * px * px;

    px += dx * dt;
    py += dy * dt;
    pz += dz * dt;

    xs.push_back(px);
    ys.push_back(py);
    zs.push_back(pz);
  }

  return { xs, ys, zs };
}

void DrawAizawaAttractor() {

  static float x0 = 0.1f, y0 = 0.0f, z0 = 0.0f;
  static float a = 0.95f, b = 0.7f, c = 0.6f, d = 3.6, e = 0.25, f = 0.1f, dt = 0.01f;
  static int steps = 30000;
  static auto [xs, ys, zs] = GenerateAizawaAttractor(x0, y0, z0, a, b, c, d, e, f, dt, steps);

  if (ImGui::Begin("Aizawa Attractor")) {

    if (ImGui::BeginTable("AizawaTable", 2, ImGuiTableFlags_Resizable)) {
      ImGui::TableSetupColumn("ParameterTable", ImGuiTableColumnFlags_WidthFixed);
      ImGui::TableSetupColumn("Plot", ImGuiTableColumnFlags_WidthStretch);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      if (ImGui::BeginTable("AizawaParameterTable", 2, ImGuiTableFlags_NoHostExtendX)) {
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
        ImGui::TextUnformatted("d");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##d", &d, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("e");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##e", &e, 0.01f))
          changed |= true;
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("f");
        ImGui::TableNextColumn();
        if (ImGui::DragFloat("##f", &f, 0.01f))
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
          std::tie(xs, ys, zs) = GenerateAizawaAttractor(x0, y0, z0, a, b, c, d, e, f, dt, steps);
        }

        ImGui::EndTable();
      }

      ImGui::TableNextColumn();

      if (ImPlot3D::BeginPlot("Aizawa Attractor")) {
        ImPlot3D::PlotLine("Trajectory", xs.data(), ys.data(), zs.data(), (int)xs.size());
        ImPlot3D::EndPlot();
      }

      ImGui::EndTable();
    }
  }
  ImGui::End();
}

} // namespace DynamicSystems