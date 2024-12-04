#pragma once

#include <functional>

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "platform/windowManager.hpp"
#include "platform/vec2.hpp"


class TextureRenderer {
public:
    bool textureLoaded {false};
    RenderTexture texture {};
    Rectangle   lastRenderedScreenRect {};

    ~TextureRenderer() {
        if(textureLoaded)
            UnloadRenderTexture(texture);
    }


    void changeSize(Vec2i inSize) {
        if(textureLoaded)
            UnloadRenderTexture(texture);
        texture = LoadRenderTexture(inSize.x, inSize.y);
        textureLoaded = true;
    }

    Vec2i getTextureSize() const {
        if(textureLoaded)
            return {texture.texture.width,texture.texture.height};
        return {0,0};
    }

    void drawContent(const std::function<void()>& inDrawCallback)
    {
        if(!textureLoaded || texture.texture.width == 0)
            return;

        BeginTextureMode(texture);
        ClearBackground(DARKGRAY);
        inDrawCallback();
        EndTextureMode();
    }

    RenderTexture* getRenderTexture()
    {
        if(textureLoaded)
            return &texture;
        return nullptr;
    }

    void draw()
    {
        rlImGuiImageRenderTexture(&texture);
        afterImGuiDraw_updateRenderScreenRect();
    }

    void drawFit()
    {
        rlImGuiImageRenderTextureFit(&texture,true);
        afterImGuiDraw_updateRenderScreenRect();
    }

    void afterImGuiDraw_updateRenderScreenRect()
    {
        lastRenderedScreenRect = {
            ImGui::GetItemRectMin().x,
            ImGui::GetItemRectMin().y,
            ImGui::GetItemRectMax().x,
            ImGui::GetItemRectMax().y,
        };
        if(WindowManager::get()->properties.showImGuiDebugInfo)
            ImGui::GetForegroundDrawList()->AddRect( ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32( 255, 255, 0, 255 ) );
    }

};
