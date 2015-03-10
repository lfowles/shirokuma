#ifndef _SHIROKUMA_SCENES_INTRO_HPP_
#define _SHIROKUMA_SCENES_INTRO_HPP_

#include <polarbear/systems/systemmanager.hpp>
#include <polarbear/events/event.hpp>
#include <polarbear/scenes/scene.hpp>

class IntroScene : public Scene
{

public:
    IntroScene(EventDispatch& dispatch) : dispatch(&dispatch), timer(0.0) {};

    virtual void Init(void) override;

    virtual void Pause(void) override {};

    virtual void Resume(void) override {};

    virtual void Update(ms elapsed) override;

    virtual void Destroy(void) override {};
private:
    void handle_input(EventPtr& event);

    SystemManager systems;
    EventDispatch* dispatch;
    s timer;
};

#endif // _SHIROKUMA_SCENES_INTRO_HPP_
