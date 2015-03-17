#ifndef _SHIROKUMA_SUDOKUBOARD_HPP_
#define _SHIROKUMA_SUDOKUBOARD_HPP_

#include <array>

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

#endif // _SHIROKUMA_SUDOKUBOARD_HPP_