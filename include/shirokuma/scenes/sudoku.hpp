#ifndef _SHIROKUMA_SCENES_SHIROKUMA_HPP_
#define _SHIROKUMA_SCENES_SHIROKUMA_HPP_

#include <polarbear/systems/systemmanager.hpp>
#include <polarbear/events/event.hpp>
#include <polarbear/scenes/scene.hpp>

class SudokuScene : public Scene
{

public:
    SudokuScene(EventDispatch& dispatch) : dispatch(&dispatch) {};

    virtual void Init(void) override;

    virtual void Pause(void) override{};

    virtual void Resume(void) override {};

    virtual void Update(ms elapsed) override;

    virtual void Destroy(void) override {};

    void BoardSolved(EventPtr& event);

//    void LoadBoard(EventPtr& event);
private:
    SystemManager systems;
    EventDispatch* dispatch;
};

#endif // _SHIROKUMA_SCENES_SHIROKUMA_HPP_
