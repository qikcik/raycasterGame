#pragma once

#include <cmath>
#include <iostream>

class LevelEditor : public Window
{
    public:
        explicit LevelEditor(Level& level) : Window("LevelEditor"), level(level) {}

        void onInstanced() override
        {
            renderer.changeSize({512, 512});
        }

        void onResize(Vec2i oldSize, Vec2i newSize) override
        {
            renderer.changeSize({
                std::min(newSize.x,newSize.y),
                std::min(newSize.x,newSize.y)
            });
        }

        void onUpdate(float deltaTime) override
        {
            int tileSize = std::min(renderer.getTextureSize().x,renderer.getTextureSize().y) / std::max(level.size.x,level.size.y);

            Vector2 mousePos {};
            mousePos.x = GetMousePosition().x - renderer.lastRenderedScreenRect.x;
            mousePos.y = GetMousePosition().y - renderer.lastRenderedScreenRect.y;



            if(mousePos.x > 0 && mousePos.y > 0  && mousePos.x <= level.size.x*tileSize && mousePos.y <= level.size.y*tileSize)
            {
                Vec2i levelPos {static_cast<int>(mousePos.x / tileSize), static_cast<int>(mousePos.y / tileSize)};
                std::cout << levelPos.x << " " << levelPos.y << std::endl;
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    level.setTile(levelPos,Tile::Wall);
                }
                if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                {
                    level.setTile(levelPos,Tile::Empty);
                }
            }

            renderer.drawContent([&]()
            {
                for(int x = 0; x!= level.size.x; x++) {
                for(int y = 0; y!= level.size.y; y++)
                {
                    Tile tile = level.getTile({x,y});

                    if (tile == Tile::Wall)
                    {
                        DrawRectangle(tileSize*x,tileSize*y,tileSize,tileSize,BLACK);
                        DrawRectangleLines(tileSize*x,tileSize*y,tileSize,tileSize,WHITE);
                    }
                    else
                    {
                        DrawRectangleLines(tileSize*x,tileSize*y,tileSize,tileSize,WHITE);
                    }

                }}
            });
        }

        void onImGuiDraw() override
        {
            ImGui::SliderInt("x",&level.size.x,4,32);
            ImGui::SliderInt("y",&level.size.y,4,32);

            renderer.draw();
        }

    protected:
        Level level;
        TextureRenderer renderer;
};