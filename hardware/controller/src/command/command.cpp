#include "command.hpp"
#include "handler.hpp"
#include "interface.hpp"
#include "src/display/display.hpp"
#include "src/electromagnet/electromagnet.hpp"
#include "src/stepper/stepper.hpp"

CommandResponse AvailableCommand::Execute() {
    bool enabled;
    switch (command) {
        case CommandId::AVAILABLE_ID:
            enabled = AvailableCommand::enabled;
            break;
        case CommandId::MOVEMENT_ID:
            enabled = MovementCommand::enabled;
            break;
        case CommandId::CLEAR_MOVS_ID:
            enabled = ClearMovementsCommand::enabled;
            break;
        case CommandId::PRINT_ID:
            enabled = PrintCommand::enabled;
            break;
    }

    return enabled ? CommandResponse::AVAILABLE : CommandResponse::UNAVAILABLE;
}
CommandResponse AvailableCommand::Parse(String args) {
    command = static_cast<CommandId>(args[0]);
}

CommandResponse MovementCommand::Execute() {
    if (skip) {
        return CommandResponse::SKIPPED;
    }

    MoveToCoord(origin.coordX, origin.coordY);

    ElectromagnetSet(true);

    MoveToCoordInMagnetLine(dest.coordX, dest.coordY);

    ElectromagnetSet(false);
}
CommandResponse MovementCommand::Parse(String args) {
    origin = EncodedPosition(args[0]);
    dest = EncodedPosition(args[1]);
    return CommandResponse::EXECUTED;
}

CommandResponse ClearMovementsCommand::Execute() {
    size_t size = CommandQueueSize();
    for (size_t i = 0; i < size; i++) {
        if (COMMAND_QUEUE[i].id != CommandId::MOVEMENT_ID) {
            continue;
        }

        COMMAND_QUEUE[i].movement.skip = true;
    }
}
CommandResponse ClearMovementsCommand::Parse(String args) {
    return CommandResponse::EXECUTED;
}

CommandResponse PrintCommand::Execute() {
    PrintToDisplay(content);
}
CommandResponse PrintCommand::Parse(String args) {
    content = args;
    return CommandResponse::EXECUTED;
}
