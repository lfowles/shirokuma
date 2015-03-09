#include <shirokuma/game.hpp>

#include <shirokuma/scenes/mainmenu.hpp>

void Shirokuma::Init(void)
{
    scenemanager.PushScene(std::make_shared<MainMenuScene>(dispatch));
}
