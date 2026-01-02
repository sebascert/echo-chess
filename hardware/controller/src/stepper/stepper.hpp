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

// vars (distance in mm)

constexpr double STEPS_PER_REV = 200;  // step
constexpr double MICROSTEPPING = 1;
constexpr double DISPLACEMENT_PER_REV = 32;  // mm
constexpr double STEPS_PER_MM =
    STEPS_PER_REV * MICROSTEPPING / DISPLACEMENT_PER_REV;

constexpr double SPEED = 100;  // mm/s

constexpr double MSEC = 1e6;  // micro seconds

constexpr double STEP_DELAY = MSEC / (STEPS_PER_MM * SPEED);
constexpr double STEP_DELAY_HALF = STEP_DELAY / (double)2;

#define NODE_DIST 400
#define SAFE_DIST 200

#define MAX_COORD_X 9
#define MAX_COORD_Y 9

typedef uint8_t Coord;
typedef int Dist;

void SetupMotor();

// move to origin
void MoveToCoord(Coord x, Coord y);

// move to destination in magnet line
void MoveToCoordInMagnetLine(Coord x, Coord y);

#endif  // CONTROLLER_STEPPER_H
