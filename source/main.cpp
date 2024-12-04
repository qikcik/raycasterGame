#include <raylib.h>

#include "platform/qeditor.hpp"
#include "platform/textureRenderer.hpp"
#include "platform/window.hpp"

class TestWindow : public Window
{
public:
    explicit TestWindow() : Window("Test") {}

    void onInstanced() override
    {
        renderer.changeSize(GetScreenWidth(), GetScreenHeight());
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
    WindowManager::get()->queueAddWindowView(std::make_unique<TestWindow>());
    WindowManager::get()->properties.showImGuiShowcase    = false;
    WindowManager::get()->properties.showImGuiDebugInfo   = false;
    WindowManager::get()->run({640,480});

    return 0;
}