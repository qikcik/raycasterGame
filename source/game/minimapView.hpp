#pragma once

#include <cmath>
#include <iostream>
#include "player.hpp"

class MinimapView : public Window
{
    public:
        explicit MinimapView(Level& level) : Window("minimapView"), level(level) {}

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

            if(IsKeyDown(KEY_LEFT))
                player.rotationAngle += player.rotationSpeed*deltaTime;
            if(IsKeyDown(KEY_RIGHT))
                player.rotationAngle -= player.rotationSpeed*deltaTime;

            Vec2f rotationVec = {sin(player.rotationAngle),cos(player.rotationAngle)};

            Vec2f newPos = player.pos;
            if(IsKeyDown(KEY_UP))
                newPos += {rotationVec.x*player.moveSpeed*deltaTime,rotationVec.y*player.moveSpeed*deltaTime};
            if(IsKeyDown(KEY_DOWN))
                newPos += {-rotationVec.x*player.moveSpeed*deltaTime,-rotationVec.y*player.moveSpeed*deltaTime};

            if( level.getTile({(int)newPos.x,(int)newPos.y}) == Tile::Empty )
                player.pos = newPos;

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
                Vec2f renderPlayerPos = player.pos * tileSize;
                DrawCircle(renderPlayerPos.x,renderPlayerPos.y,10,RED);

                Vec2f rotationVec = {sin(player.rotationAngle),cos(player.rotationAngle)};
                DrawLine(renderPlayerPos.x,renderPlayerPos.y,renderPlayerPos.x+(rotationVec.x*100),renderPlayerPos.y+(rotationVec.y*100),RED);
            });
        }

        void onImGuiDraw() override
        {
            renderer.draw();
        }

    protected:
        Level& level;
        Player player {};
        TextureRenderer renderer;
};