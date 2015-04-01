#ifndef _SHIROKUMA_SYSTEMS_INTENT_HPP_
#define _SHIROKUMA_SYSTEMS_INTENT_HPP_

#include <polarbear/systems/systems.hpp>

class IntentSystem : public System
{
public:
    IntentSystem(EventDispatch* dispatch, SystemManager* systems);
    ~IntentSystem(void);
    void HandleInput(EventPtr& event);

    virtual void update(ms time_elapsed) override;
private:
};

#endif // _SHIROKUMA_SYSTEMS_INTENT_HPP_