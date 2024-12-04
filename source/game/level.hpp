#pragma once
#include <map>
#include "platform/vec2.hpp"

enum class Tile
{
    Empty,
    Wall
};

class Level
{
    public:
        Tile getTile(Vec2i inPos) const
        {
            auto x_it = data.find(inPos.x);
            if(x_it != data.end())
            {
                auto y_it = x_it->second.find(inPos.y);
                if(y_it != x_it->second.end())
                {
                    return y_it->second;
                }
            }
            return Tile::Empty;
        }

        void setTile(Vec2i inPos, Tile tile)
        {
            data[inPos.x][inPos.y] = tile;
        }

        Vec2i size {};
    protected:
        std::map<int,std::map<int,Tile>> data {};
};