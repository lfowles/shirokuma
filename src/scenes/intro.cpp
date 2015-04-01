#include <shirokuma/scenes/intro.hpp>

#include <polarbear/cursessingleton.hpp>
#include <polarbear/systems/cursesrender.hpp>
#include <polarbear/systems/cursesinput.hpp>

#include <shirokuma/scenes/sudoku.hpp>

void IntroScene::Init(void)
{
    auto delegate = std::make_shared<EventDelegateMemberFunction<IntroScene>>(this, std::mem_fn(&IntroScene::handle_input));
    dispatch->Register<InputEvent>(delegate, dispatch_id);

    auto curses = CursesSingleton::GetCurses();

    auto rendering_system = new CursesRenderSystem(dispatch, &systems, render_duration);
    systems.AddSystem(rendering_system);

    auto input_system = new CursesInputSystem(dispatch, &systems, curses->stdscr);
    systems.AddSystem(input_system);

    {
        Entity splash;
        auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(0, 0, 1));
        auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(RESOURCE_PATH "intro/splash.sprite"));
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
        auto next_scene = std::make_shared<SudokuScene>(*dispatch);
        auto event = std::make_shared<SceneChangeEvent>(SceneChangeEvent::Operation::Replace, next_scene);
        dispatch->QueueEvent(event);
    }
}

// TODO: unregister for input
void IntroScene::handle_input(EventPtr &event)
{
    auto next_scene = std::make_shared<SudokuScene>(*dispatch);
    auto scene_change_event = std::make_shared<SceneChangeEvent>(SceneChangeEvent::Operation::Replace, next_scene);
    dispatch->QueueEvent(scene_change_event);
}

void IntroScene::Destroy(void)
{
    dispatch->UnregisterAll(dispatch_id);
}