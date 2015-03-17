#ifndef _SHIROKUMA_SYSTEMS_SUDOKULOGIC_HPP_
#define _SHIROKUMA_SYSTEMS_SUDOKULOGIC_HPP_

#include <polarbear/systems/systems.hpp>
#include <shirokuma/sudokuboard.hpp>

class SudokuLogicSystem : public System
{
public:
    SudokuLogicSystem(EventDispatch* dispatch);
    ~SudokuLogicSystem(void);
    void HandleInput(EventPtr& event);

    virtual void update(ms time_elapsed) override;

    int selected_row;
    int selected_col;
    bool entering_value;
    bool toggle_lock;
    int entered_value;

private:
    SudokuBoard board;
    bool gameover;

};

#endif // _SHIROKUMA_SYSTEMS_SUDOKULOGIC_HPP_