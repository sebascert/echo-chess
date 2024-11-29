#include <cstdint>
#ifndef CONTROLLER_STEPPER_H
#define CONTROLLER_STEPPER_H

// pins

#define STEPPER_DIR_X 23
#define STEPPER_STEP_X 22
#define LIMIT_SWITCH_X 4

#define STEPPER_DIR_Y 21
#define STEPPER_STEP_Y 19
#define LIMIT_SWITCH_Y 18

typedef uint8_t Coord;

void SetupMotorPins();

void MovePiece(Coord originX, Coord originY, Coord destX, Coord destY);

#endif  // CONTROLLER_STEPPER_H
