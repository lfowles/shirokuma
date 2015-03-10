#include <shirokuma/game.hpp>

#include <shirokuma/scenes/intro.hpp>

void Shirokuma::Init(void)
{
    scenemanager.PushScene(std::make_shared<IntroScene>(dispatch));
}
