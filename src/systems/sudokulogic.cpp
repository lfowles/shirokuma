#include <shirokuma/systems/sudokulogic.hpp>

#include <polarbear/components/components.hpp>

#include <shirokuma/components/sudokucomponents.hpp>
#include <shirokuma/events/events.hpp>

SudokuLogicSystem::SudokuLogicSystem(EventDispatch *dispatch, SystemManager *systems) :
        System(dispatch, systems), selected_row(0), selected_col(0), entered_value(0), entering_value(false), toggle_lock(false), gameover(false)
{
    auto delegate = std::make_shared<EventDelegateMemberFunction<SudokuLogicSystem>>(this, std::mem_fn(&SudokuLogicSystem::HandleInput));
    dispatch->Register(InputEvent::type, delegate, dispatch_id);

    system_mask.set(CellComponent::type);
    system_mask.set(SpriteComponent::type);
}

SudokuLogicSystem::~SudokuLogicSystem(void)
{
    dispatch->UnregisterAll(dispatch_id);
}

void SudokuLogicSystem::HandleInput(EventPtr & event)
{
    if (gameover)
    {
        return;
    }

    auto input_event = std::dynamic_pointer_cast<InputEvent>(event);

    if (input_event->key == KEY_ENTER or input_event->key == 0x0A or input_event->key == 0x0D )
    {
        entering_value = not entering_value;
        entered_value = -1;
        return;
    } else if (input_event->key == ' ') {
        toggle_lock = true;
        return;
    }

    if (input_event->key == KEY_LEFT) {
        selected_col = (selected_col+8) % 9; // +8, because % is more of a remainder than modulo
        entering_value = false;
    } else if (input_event->key == KEY_RIGHT) {
        selected_col = (selected_col+1) % 9;
        entering_value = false;
    } else if (input_event->key == KEY_UP) {
        selected_row = (selected_row+8) % 9; // +8, because % is more of a remainder than modulo
        entering_value = false;
    } else if (input_event->key == KEY_DOWN) {
        selected_row = (selected_row+1) % 9;
        entering_value = false;
    }

    if (entering_value)
    {
        if (input_event->key >= '0' and input_event->key <= '9')
        {
            entered_value = input_event->key - '0';
        }
    } else {

        if (input_event->key >= 'a' and input_event->key <= 'i') {
            selected_row = input_event->key-'a';
        } else if (input_event->key >= '1' and input_event->key <= '9') {
            selected_col = input_event->key-'1';
        }
    }
}

void SudokuLogicSystem::update(ms time_elapsed)
{
    if (gameover)
    {
        return;
    }

    // Populate board
    for (auto& entity : interesting_entities)
    {
        auto cell = entity->Get<CellComponent>();
        board.set(cell->y, cell->x, cell->value);
    }

    gameover = board.solved();
    if (gameover)
    {
        // Don't _unlock_ a cell or allow a value change if the puzzle has been solved
        // With the gameover bool disabling updates, this doesn't matter, but it will render correctly with these set
        entering_value = false;
        toggle_lock = false;
        dispatch->QueueEvent(std::make_shared<SolvedEvent>());
    }

    for (auto& entity : interesting_entities)
    {
        auto cell = entity->Get<CellComponent>();
        auto sprite = entity->Get<SpriteComponent>();

        if (gameover)
        {
            cell->cell_type = CellComponent::CellType::Locked;
        }

        if (cell->x == selected_col and cell->y == selected_row)
        {
            if (toggle_lock)
            {
                if (cell->cell_type == CellComponent::CellType::Free)
                {
                    cell->cell_type = CellComponent::CellType::Locked;
                } else if (cell->cell_type == CellComponent::CellType::Locked) {
                    cell->cell_type = CellComponent::CellType::Free;
                }
                toggle_lock = false;
            }

            if (cell->cell_type == CellComponent::CellType::Free)
            {
                if (entering_value and entered_value != -1)
                {
                    cell->value = entered_value;
                    board.set(cell->y, cell->x, cell->value);
                    entering_value = false;
                }
            }
        }

        sprite->attr = 0;

        if (cell->cell_type == CellComponent::CellType::Locked or cell->cell_type == CellComponent::CellType::Starting)
        {
            sprite->attr |= A_BOLD;
        } else if (cell->cell_type == CellComponent::CellType::Free and cell->x == selected_col and cell->y == selected_row) {
            sprite->attr |= A_UNDERLINE;
        }

        if (not board.valid(cell->y, cell->x) and not cell->value == 0)
        {
            sprite->attr |= A_REVERSE;
        }

        if (cell->value == 0)
        {
            sprite->sprite_chars[0] = '_';
        } else {
            sprite->sprite_chars[0] = '0'+cell->value;
        }
    }
}
