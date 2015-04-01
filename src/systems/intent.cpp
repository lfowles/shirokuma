#include <shirokuma/systems/intent.hpp>

#include <shirokuma/components/sudokucomponents.hpp>

IntentSystem::IntentSystem(EventDispatch *dispatch, SystemManager *systems) : System(dispatch, systems)
{
    auto delegate = std::make_shared<EventDelegateMemberFunction<IntentSystem>>(this, std::mem_fn(&IntentSystem::HandleInput));
    dispatch->Register(InputEvent::type, delegate, dispatch_id);

    system_mask.set(SudokuStateComponent::type);
}

IntentSystem::~IntentSystem(void)
{
    dispatch->UnregisterAll(dispatch_id);
}

void IntentSystem::HandleInput(EventPtr &event)
{
    // Hey hey, let's merge input Update into Entity::Update and get rid of InputEvents almost entirely?
    auto input_event = std::dynamic_pointer_cast<InputEvent>(event);
    auto& key = input_event->key;
    auto& state_entity = interesting_entities[0];
    auto state = state_entity->Get<SudokuStateComponent>();

    switch (state->state)
    {
        // TODO : Shit this doesn't work!!!! Maybe I want to go back to events and just have the respective systems handle intent events....
        case SudokuStateComponent::State::Main:
        {
            // Should try a CursorMovedComponent with horiz and vert values
            // Single key intents
            if (key == KEY_ENTER or key == 0x0A or key == 0x0D)
            {
                // I'm half tempted to just modify state directly and change to EnteringValue here
                // The alternative of course is to send an event saying the state needs changed, but who handles that?
            } else if (key == ' ') {
                // Send intent to Toggle Cell Lock
            } else if (key == KEY_LEFT) {
                // Send intent to Move Cursor Left
                auto cursor_moved = state_entity->Get<CursorMovedRelativeComponent>();
                if (cursor_moved == nullptr)
                {
                    cursor_moved = new CursorMovedRelativeComponent(0, 0);
                    state_entity->AddComponent(std::unique_ptr<CursorMovedRelativeComponent>(cursor_moved));
                }
                cursor_moved->steps_vertical -= 1;
                // Add component to .... entity with SudokuStateComponent?
            } else if (key == KEY_RIGHT) {
                // Send intent to Move Cursor Right
                auto cursor_moved = state_entity->Get<CursorMovedRelativeComponent>();
                if (cursor_moved == nullptr)
                {
                    cursor_moved = new CursorMovedRelativeComponent(0, 0);
                    state_entity->AddComponent(std::unique_ptr<CursorMovedRelativeComponent>(cursor_moved));
                }
                cursor_moved->steps_vertical += 1;
            } else if (key == KEY_UP) {
                // Send intent to Move Cursor Up
                auto cursor_moved = state_entity->Get<CursorMovedRelativeComponent>();
                if (cursor_moved == nullptr)
                {
                    cursor_moved = new CursorMovedRelativeComponent(0, 0);
                    state_entity->AddComponent(std::unique_ptr<CursorMovedRelativeComponent>(cursor_moved));
                }
                cursor_moved->steps_horizontal -= 1;
            } else if (key == KEY_DOWN) {
                // Send intent to Move Cursor Down
                auto cursor_moved = state_entity->Get<CursorMovedRelativeComponent>();
                if (cursor_moved == nullptr)
                {
                    cursor_moved = new CursorMovedRelativeComponent(0, 0);
                    state_entity->AddComponent(std::unique_ptr<CursorMovedRelativeComponent>(cursor_moved));
                }
                cursor_moved->steps_horizontal += 1;
            }

            // Key range intents
            else if (key >= 'a' and key <= 'i') { // See how I snuck that else in here?
                // Send intent to Move Cursor to Row $KEY
                auto cursor_moved = std::unique_ptr<CursorMovedAbsoluteComponent>(new CursorMovedAbsoluteComponent(state->cursor_x, key-'a'));
                state_entity->ReplaceComponent(cursor_moved);
            } else if (key >= '1' and key <= '9') {
                // Send intent to Move Cursor to Column $KEY
                auto cursor_moved = std::unique_ptr<CursorMovedAbsoluteComponent>(new CursorMovedAbsoluteComponent(key-'1', state->cursor_x));
                state_entity->ReplaceComponent(cursor_moved);
            }
        };
        case SudokuStateComponent::State::EnteringValue:
        {
            if (key >= '0' and key <= '9')
            {
                // Send intent to Set Cell To $KEY
            } else {
                // Revert state to main? See thoughts for KEY_ENTER above
            }
        };
        case SudokuStateComponent::State::EnteringBoard:
        {
            if (key >= '0' and key <= '9')
            {
                // Accumulate until 81 digits, then send intent to Load Board With Code $ACCUMULATED
            } else if (key == KEY_ENTER or key == 0x0A or key == 0x0D) {
                // Error, Will Robinson
            }
        };
        case SudokuStateComponent::State::GameOver:
        {
            // Future: R to restart, Q to quit
            return;
        };
    }
}

void IntentSystem::update(ms time_elapsed)
{

}
