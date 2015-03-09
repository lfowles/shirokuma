#ifndef _SHIROKUMA_SCENES_MAINMENU_HPP_
#define _SHIROKUMA_SCENES_MAINMENU_HPP_

#include <polarbear/config.hpp>
#include <polarbear/systems/systemmanager.hpp>
#include <polarbear/events/event.hpp>
#include <polarbear/scenes/scene.hpp>

class MainMenuScene : public Scene
{

public:
    MainMenuScene(EventDispatch& dispatch) : dispatch(&dispatch) {};

    virtual void Init(void) override;

    virtual void Pause(void) override{};

    virtual void Resume(void) override {};

    virtual void Update(ms elapsed) override;

    virtual void Destroy(void) override {};
private:
    SystemManager systems;
    EventDispatch* dispatch;
};

#endif // _SHIROKUMA_SCENES_MAINMENU_HPP_
