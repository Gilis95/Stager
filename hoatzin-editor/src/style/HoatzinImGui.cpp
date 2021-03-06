//
// Created by christian on 04/11/2020.
//

#include <imgui.h>
#include <imgui_internal.h>
#include "style/HoatzinImGui.h"

namespace stinky::hoatzin::HoatzinImGui {

    /////////////////////////////////////////////////////////////////////////////////////////
    void
    DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue, float columnWidth) {
        ImGuiIO &io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    void OverrideImGuiColours() {
        auto &colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{0.96f, 0.96f, 0.96f, 1.0f};

        // Headers
        colors[ImGuiCol_Header] = ImVec4{0.8f, 0.8f, 0.8f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.85f, 0.85f, 0.85f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.75f, 0.75f, 0.75f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{0.8f, 0.8f, 0.8f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{0.85f, 0.85f, 0.85f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.75f, 0.75f, 0.75f, 1.0f};

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{0.8f, 0.8f, 0.8f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.85f, 0.85f, 0.85f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.75f, 0.75f, 0.75f, 1.0f};

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{0.9f, 0.9f, 0.9f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.85f, 0.85f, 0.85f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4{0.96f, 0.96f, 0.96f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.9f, 0.9f, 0.9f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.95f, 0.95f, 0.95f, 1.0f};

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{0.8f, 0.8f, 0.8f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.75f, 0.75f, 0.75f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.75f, 0.75f, 0.75f, 1.0f};
    }
}