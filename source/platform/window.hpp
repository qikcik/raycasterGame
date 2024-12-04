#pragma once

#include <string>

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

class Window
{
public:
    explicit Window(std::string title) : title(std::move(title)) {}
    virtual ~Window() = default;

    virtual void onInstanced() {};

    virtual void onUpdate(float deltaTime) {}
    bool isPendingDestroy() const {return pendingDestroy;};

    void ImGuiDraw()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::SetNextWindowSizeConstraints(ImVec2(128, 128), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

        bool open {true};
        if (ImGui::Begin(title.c_str(), &open /*ImGuiWindowFlags_NoScrollbar*/))
        {
            //focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
            onImGuiDraw();
        }
        if(!open) pendingDestroy = true;


        ImGui::End();
        ImGui::PopStyleVar();
    }

protected:
    bool pendingDestroy = false;
    std::string title {};

    virtual void onImGuiDraw() {};
};
