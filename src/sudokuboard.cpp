#include <shirokuma/sudokuboard.hpp>

SudokuBoard::SudokuBoard(void)
{
    cells.fill(0);
}

// Value can be 0-9
void SudokuBoard::set(int row, int col, int value)
{
    cells[row*9+col] = value;
}

int& SudokuBoard::get(int row, int col)
{
    return cells[row*9+col];
}

bool SudokuBoard::valid(int row, int col)
{
    // Can immediately return invalid if sum of row, column, or square is not 45
    // This is annoying and clutters up the code though :) I'm not sure how much faster it would be as a first pass

    auto value = get(row, col);

    if (value == 0)
    {
        return false;
    }

    // Duplicate number check
    for (auto r=0; r < 9; r++)
    {
        if (get(r, col) == value and r != row)
        {
            return false;
        }
    }

    for (auto c=0; c < 9; c++)
    {
        if (get(row, c) == value and c != col)
        {
            return false;
        }
    }

    auto box_col = col/3;
    auto box_row = row/3;

    for (auto r=0; r<3; r++)
    {
        auto actual_row = box_row*3+r;
        for (auto c=0; c<3; c++)
        {
            auto actual_col = box_col*3+r;
            if (get(actual_row, actual_col) == value and not (actual_row == row and actual_col == col))
            {
                return false;
            }
        }
    }

    return true;
}

bool SudokuBoard::solved(void)
{
    // There is probably a shortcut,
    // maybe something like one sample from every row, every column, and every square would work?

    for (auto cell : cells)
    {
        // Not solved if it's not filled out
        if (cell == 0)
        {
            return false;
        }
    }

    for (auto i=0; i<9; i++)
    {
        if (not valid(i, 0))
        {
            return false;
        }
        if (not valid(0, i))
        {
            return false;
        }
    }
    for (auto box_row=0; box_row<3; box_row++)
    {
        for (auto box_col=0; box_col<3; box_col++)
        {
            if (not valid(box_row*3, box_col*3))
            {
                return false;
            }
        }
    }

    return true;
}
