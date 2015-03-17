#ifndef _SHIROKUMA_COMPONENTS_SUDOKUCOMPONENTS_HPP_
#define _SHIROKUMA_COMPONENTS_SUDOKUCOMPONENTS_HPP_

#include <polarbear/components/components.hpp>

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

#endif // _SHIROKUMA_COMPONENTS_SUDOKUCOMPONENTS_HPP_