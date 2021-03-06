#include <shirokuma/scenes/sudoku.hpp>

#include <polarbear/systems/cursesrender.hpp>
#include <polarbear/systems/cursesinput.hpp>

#include <shirokuma/components/sudokucomponents.hpp>
#include <shirokuma/systems/sudokulogic.hpp>
#include <shirokuma/systems/intent.hpp>
#include <shirokuma/events/events.hpp>


void SudokuScene::BoardSolved(EventPtr &event)
{
    Entity congrats{};
    auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(0, 10, 3));
    auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent("Congratulations! You solved the sudoku.\n Stats will be here some time.", 0x00));
    sprite->attr = A_REVERSE | A_BOLD;
    congrats.AddComponent(pos);
    congrats.AddComponent(sprite);
    systems.AddEntity(congrats);
}

void SudokuScene::Init(void)
{
    auto solved_delegate = std::make_shared<EventDelegateMemberFunction<SudokuScene>>(this, std::mem_fn(&SudokuScene::BoardSolved));
    dispatch->Register(SolvedEvent::type, solved_delegate, dispatch_id);

    auto logic_system = new SudokuLogicSystem(dispatch, &systems);
    systems.AddSystem(logic_system);

    auto rendering_system = new CursesRenderSystem(dispatch, &systems, render_duration);
    systems.AddSystem(rendering_system);

    auto curses = CursesSingleton::GetCurses();
    auto input_system = new CursesInputSystem(dispatch, &systems, curses->stdscr);
    systems.AddSystem(input_system);

    auto intent_system = new IntentSystem(dispatch, &systems);
    systems.AddSystem(intent_system);

    {
        Entity a{};
        auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(0, 0, 1));
        auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(RESOURCE_PATH "test.sprite"));
        auto movement = std::unique_ptr<KeyboardControlledMovementComponent>(new KeyboardControlledMovementComponent(1));
        a.AddComponent(pos);
        a.AddComponent(sprite);
        a.AddComponent(movement);
        systems.AddEntity(a);
    }
    {
        Entity board_highlights{};
        auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(0, 0, 2));
        auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(RESOURCE_PATH "test_overlay.sprite"));
        sprite->attr = A_BOLD;

        auto movement = std::unique_ptr<KeyboardControlledMovementComponent>(new KeyboardControlledMovementComponent(1));
        board_highlights.AddComponent(pos);
        board_highlights.AddComponent(sprite);
        board_highlights.AddComponent(movement);
        systems.AddEntity(board_highlights);
    }
//    {
//        Entity state{};
//        auto state_component = std::unique_ptr<StateComponent>(new StateComponent());
//        state.AddComponent(state_component);
//        systems.AddEntity(state);
//    }

    std::array<int, 81> values = {
            0,0,0,6,0,0,1,9,0,
            0,2,0,0,0,0,0,0,5,
            0,3,4,5,7,9,0,0,0,
            0,8,9,4,0,0,0,0,0,
            4,0,0,8,5,6,0,0,2,
            0,0,0,0,0,7,8,1,0,
            0,0,0,9,8,1,2,5,0,
            7,0,0,0,0,0,0,8,0,
            0,5,1,0,0,2,0,0,0};

    for (int r = 0; r < 9; r++)
    {
        auto y = r * 2 + 2;

        for (int c = 0; c < 9; c++)
        {
            Entity cell{};
            auto x = 4 * c + 4;
            auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(x, y, 1));
            cell.AddComponent(pos);
            auto cell_component = std::unique_ptr<CellComponent>(new CellComponent(CellComponent::CellType::Free, values[r*9+c], c, r));
            if (cell_component->value != 0)
            {
                cell_component->cell_type = CellComponent::CellType::Starting;
            }
            cell.AddComponent(cell_component);
            auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(0x30 + values[r*9+c]));
            cell.AddComponent(sprite);
            systems.AddEntity(cell);
        }
    }
}

void SudokuScene::Update(ms elapsed)
{
    systems.update(elapsed);
}