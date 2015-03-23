#include <shirokuma/systems/intent.hpp>

#include <shirokuma/components/sudokucomponents.hpp>

IntentSystem::IntentSystem(EventDispatch *dispatch) : System(dispatch)
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
    auto state = interesting_entities[0]->Get<SudokuStateComponent>();

    switch (state->state)
    {
        case SudokuStateComponent::State::Main:
        {
            // Single key intents
            if (key == KEY_ENTER or key == 0x0A or key == 0x0D)
            {
                // I'm half tempted to just modify state directly and change to EnteringValue here
                // The alternative of course is to send an event saying the state needs changed, but who handles that?
            } else if (key == ' ') {
                // Send intent to Toggle Cell Lock
            } else if (key == KEY_LEFT) {
                // Send intent to Move Cursor Left
            } else if (key == KEY_RIGHT) {
                // Send intent to Move Cursor Right
            } else if (key == KEY_UP) {
                // Send intent to Move Cursor Up
            } else if (key == KEY_DOWN) {
                // Send intent to Move Cursor Down
            }

            // Key range intents
            else if (key >= 'a' and key <= 'i') { // See how I snuck that else in here?
                // Send intent to Move Cursor to Row $KEY
            } else if (key >= '1' and key <= '9') {
                // Send intent to Move Cursor to Column $KEY
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
