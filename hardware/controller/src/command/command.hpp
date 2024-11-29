#ifndef CONTROLLER_COMMAND_H
#define CONTROLLER_COMMAND_H

#include "WString.h"

#include "interface.hpp"

// abstract command interface
struct Command {
    // execution steps for the command
    virtual CommandResponse Execute() = 0;
    // parsing the args for the command, return EXECUTE if no error, else return
    // corresponding (client or hardware)
    virtual CommandResponse Parse(String args) = 0;
};

class AvailableCommand : public Command {
    CommandId command;

   public:
    static const bool enabled = true;

    AvailableCommand() = default;
    CommandResponse Execute();
    CommandResponse Parse(String args);
};

class MovementCommand : public Command {
    EncodedPosition origin;
    EncodedPosition dest;

   public:
    static const bool enabled = true;

    bool skip = false;

    MovementCommand() = default;
    CommandResponse Execute();
    CommandResponse Parse(String args);
};

class ClearMovementsCommand : public Command {
   public:
    static const bool enabled = true;

    ClearMovementsCommand() = default;
    CommandResponse Execute();
    CommandResponse Parse(String args);
};

class PrintCommand : public Command {
    String content;

   public:
    static const bool enabled = true;

    PrintCommand() = default;
    CommandResponse Execute();
    CommandResponse Parse(String args);
};

#endif  // CONTROLLER_COMMAND_H
