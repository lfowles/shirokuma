#ifndef _SHIROKUMA_COMPONENTS_SUDOKUCOMPONENTS_HPP_
#define _SHIROKUMA_COMPONENTS_SUDOKUCOMPONENTS_HPP_

#include <polarbear/components/components.hpp>

#include <shirokuma/sudokuboard.hpp>

class CellComponent : public BaseComponent<CellComponent>
{
public:
    enum class CellType
    {
        Starting,
        Locked,
        Free
    };

    CellComponent(CellType t, int val, int x, int y) :
            cell_type(t), value(val), x(x), y(y) {};

    CellType cell_type;
    int value;
    int x, y;
};

class SudokuStateComponent : public BaseComponent<SudokuStateComponent>
{
public:
    enum class State
    {
        Main, // Default state
        EnteringValue, // Entering a single value onto the board
        EnteringBoard, // Entering the code for a board to be loaded
        GameOver // Completed board (quit would exit the game)
    };

    SudokuBoard board;
    State state;
    int cursor_x, cursor_y;
};

// Inspired by: https://www.reddit.com/r/gamedev/comments/2rrie6/ecs_and_observer_pattern/cnilgg8
class CursorMovedRelativeComponent : public BaseComponent<CursorMovedRelativeComponent>
{
public:
    CursorMovedRelativeComponent(int vertical, int horizontal) :
            steps_vertical(vertical), steps_horizontal(horizontal) {}
    int steps_vertical, steps_horizontal;
};

class CursorMovedAbsoluteComponent : public BaseComponent<CursorMovedAbsoluteComponent>
{
public:
    CursorMovedAbsoluteComponent(int x, int y) : x(x), y(y) {}
    int x, y;
};

#endif // _SHIROKUMA_COMPONENTS_SUDOKUCOMPONENTS_HPP_