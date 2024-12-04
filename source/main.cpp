#include <raylib.h>

#include "platform/windowManager.hpp"
#include "platform/textureRenderer.hpp"
#include "platform/window.hpp"

#include "game/level.hpp"
#include "game/levelEditor.hpp"

class TestWindow : public Window
{
public:
    explicit TestWindow() : Window("Test") {}

    void onInstanced() override
    {
        renderer.changeSize({GetScreenWidth(), GetScreenHeight()});
    }

    void onUpdate(float deltaTime) override
    {
        renderer.drawContent([]()
        {

        });
    }

    void onImGuiDraw() override
    {
        renderer.drawContent([]()
        {
            DrawPixel(10,10,RED);
        });

        renderer.drawFit();
    }

protected:
    TextureRenderer renderer;
};


WindowManager* WindowManager::instance = nullptr;

int main(void)
{
    Level level;
    level.size = {16,16};
    level.setTile({0,0},Tile::Wall);
    WindowManager::get()->queueAddWindowView(std::make_unique<LevelEditor>(level));

    WindowManager::get()->properties.showImGuiShowcase    = false;
    WindowManager::get()->properties.showImGuiDebugInfo   = false;
    WindowManager::get()->run({640,480});

    return 0;
}