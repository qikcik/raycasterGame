#pragma once

#include <string>

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "vec2.hpp"

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

        bool open {true};
        if (ImGui::Begin(title.c_str(), &open /*ImGuiWindowFlags_NoScrollbar*/))
        {
            Vec2i currentSize = ImGui::GetWindowSize();
            if(size.x != currentSize.x && size.y != currentSize.y)
            {
                auto oldSize = size;
                size = currentSize;
                onResize(oldSize,currentSize);
            }


            //focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
            onImGuiDraw();
        }
        if(!open) pendingDestroy = true;


        ImGui::End();
        ImGui::PopStyleVar();
    }

protected:
    bool pendingDestroy = false;
    Vec2i size {128,128};
    std::string title {};

    virtual void onResize(Vec2i oldSize, Vec2i newSize) {};
    virtual void onImGuiDraw() {};
};
