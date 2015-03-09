#ifndef _SHIROKUMA_SYSTEMS_SUDOKULOGIC_HPP_
#define _SHIROKUMA_SYSTEMS_SUDOKULOGIC_HPP_

#include <polarbear/systems/systems.hpp>

class SudokuBoard
{
public:
    SudokuBoard(void);
    void set(int row, int col, int value);
    bool valid(int row, int col);
    bool solved(void);
    int& get(int row, int col);
private:
    std::array<int, 81> cells;
};

class SudokuLogicSystem : public System
{
public:
    SudokuLogicSystem(EventDispatch* dispatch);

    void HandleInput(EventPtr& event);

    virtual void update(ms time_elapsed) override;

    int selected_row;
    int selected_col;
    bool entering_value;
    int entered_value;

private:
    SudokuBoard board;

};

#endif // _SHIROKUMA_SYSTEMS_SUDOKULOGIC_HPP_