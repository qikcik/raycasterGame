#pragma once

#include <functional>


#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"


class TextureRenderer {
public:
    bool textureLoaded {false};
    RenderTexture texture {};
    Rectangle   lastRenderedScreenRect {};

    ~TextureRenderer() {
        if(textureLoaded)
            UnloadRenderTexture(texture);
    }


    void changeSize(const int inWidth,const int inHeight) {
        if(textureLoaded)
            UnloadRenderTexture(texture);
        texture = LoadRenderTexture(inWidth, inHeight);
        textureLoaded = true;
    }


    void drawContent(const std::function<void()>& inDrawCallback)
    {
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
