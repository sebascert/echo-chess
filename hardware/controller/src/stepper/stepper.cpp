#include "esp32-hal-gpio.h"

#include "stepper.hpp"

Dist currX;
Dist currY;
Coord coordX;
Coord coordY;

void SetupMotor() {
    pinMode(STEPPER_DIR_X, OUTPUT);
    pinMode(STEPPER_STEP_X, INPUT_PULLUP);
    pinMode(LIMIT_SWITCH_X, INPUT);

    pinMode(STEPPER_DIR_Y, OUTPUT);
    pinMode(STEPPER_STEP_Y, INPUT);
    pinMode(LIMIT_SWITCH_Y, INPUT_PULLUP);

    // initialize position
    currX = 0;
    currY = 0;

    while (digitalRead(LIMIT_SWITCH_X) == LOW &&
           digitalRead(LIMIT_SWITCH_Y) == LOW) {
        VectorMove(-1, -1);
    }

    while (digitalRead(LIMIT_SWITCH_X) == LOW == LOW) {
        VectorMove(-1, 0);
    }

    while (digitalRead(LIMIT_SWITCH_Y) == LOW == LOW) {
        VectorMove(0, -1);
    }
}

void AxisMove(Dist dist, uint8_t dir_pin, uint8_t step_pin);

void MoveToCoord(Coord x, Coord y) {
    AxisMove((NODE_DIST * x) - currX, STEPPER_DIR_X, STEPPER_STEP_X);
    AxisMove((NODE_DIST * y) - currY, STEPPER_DIR_Y, STEPPER_STEP_X);

    coordX = x;
    coordY = y;
}

void MoveToCoordInMagnetLine(Coord x, Coord y) {
    // move to magnet line, left botoom corner of square
    VectorMove(-SAFE_DIST, -SAFE_DIST);
    // move to dest y magnet line
    VectorMove((NODE_DIST * (x - currX)), 0);
    // move to dest x line
    VectorMove(0, (NODE_DIST * (x - currX)) + SAFE_DIST);
    // move to dest y line
    VectorMove(SAFE_DIST, 0);
}

void VectorMove(Dist x, Dist y) {
    AxisMove(x, STEPPER_DIR_X, STEPPER_STEP_X);
    AxisMove(y, STEPPER_DIR_Y, STEPPER_STEP_X);
}

void AxisMove(Dist dist, uint8_t dir_pin, uint8_t step_pin) {
    if (dist > 0) {
        digitalWrite(dir_pin, HIGH);
    } else {
        digitalWrite(dir_pin, LOW);
        dist = -dist;
    }

    int steps = dist * STEPS_PER_MM;

    for (int i = 0; i < steps; i++) {
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(STEP_DELAY_HALF);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(STEP_DELAY_HALF);
    }
}
