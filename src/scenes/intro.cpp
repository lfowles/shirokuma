#include <shirokuma/scenes/intro.hpp>

#include <polarbear/config.hpp>
#include <polarbear/cursessingleton.hpp>
#include <polarbear/systems/cursesrender.hpp>
#include <polarbear/systems/cursesinput.hpp>

#include <shirokuma/scenes/mainmenu.hpp>

#include <iostream>
void IntroScene::Init(void)
{
    EventDelegate delegate = std::bind(&IntroScene::handle_input, this, std::placeholders::_1);
    dispatch->Register(EventType::Input, delegate);

    auto curses = CursesSingleton::GetCurses();
    systems.SetUpdateTime(update_duration);

    auto rendering_system = new CursesRenderSystem(dispatch, render_duration);
    systems.AddSystem(rendering_system);

    auto input_system = new CursesInputSystem(dispatch, curses->stdscr);
    systems.AddSystem(input_system);

    {
        Entity splash;
        auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(0, 0, 1));
        auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(RESOURCE_PATH "intro.sprite"));
        splash.AddComponent(pos);
        splash.AddComponent(sprite);
        systems.AddEntity(splash);
    }
}

void IntroScene::Update(ms elapsed)
{
    systems.update(elapsed);
    timer += elapsed;
    if (timer.count() > 5)
    {
        auto next_scene = std::make_shared<MainMenuScene>(*dispatch);
        auto event = std::make_shared<SceneChangeEvent>(SceneChangeEvent::Operation::Replace, next_scene);
        dispatch->QueueEvent(event);
    }
}

// TODO: unregister for input
void IntroScene::handle_input(EventPtr &event)
{
    auto next_scene = std::make_shared<MainMenuScene>(*dispatch);
    auto scene_change_event = std::make_shared<SceneChangeEvent>(SceneChangeEvent::Operation::Replace, next_scene);
    dispatch->QueueEvent(scene_change_event);
    std::cout << "handling" << std::endl;
    EventDelegate delegate = std::bind(&IntroScene::handle_input, this, std::placeholders::_1);
    dispatch->Unregister(EventType::Input, delegate);
}
