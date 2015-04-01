#ifndef _SHIROKUMA_EVENTS_EVENTS_HPP_
#define _SHIROKUMA_EVENTS_EVENTS_HPP_

#include <polarbear/events/event.hpp>

class SolvedEvent : public BaseEvent<SolvedEvent> {};

class LoadBoard : public BaseEvent<LoadBoard>
{
    std::vector<int> board;
};

class MoveCursorEvent : public BaseEvent<MoveCursorEvent>
{
public:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    MoveCursorEvent(Direction dir) : dir(dir) {};

    Direction dir;
};

#endif // _SHIROKUMA_EVENTS_EVENTS_HPP_