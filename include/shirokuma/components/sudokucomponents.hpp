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
};

#endif // _SHIROKUMA_COMPONENTS_SUDOKUCOMPONENTS_HPP_