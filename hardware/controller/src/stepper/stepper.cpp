#include "esp32-hal-gpio.h"

#include "stepper.hpp"

void SetupMotorPins() {
    pinMode(STEPPER_DIR_X, OUTPUT);
    pinMode(STEPPER_STEP_X, INPUT_PULLUP);
    pinMode(LIMIT_SWITCH_X, INPUT);

    pinMode(STEPPER_DIR_Y, OUTPUT);
    pinMode(STEPPER_STEP_Y, INPUT);
    pinMode(LIMIT_SWITCH_Y, INPUT_PULLUP);
}

Dist currX;
Dist currY;

void InitializePosition() {
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

void MovePiece(Coord originX, Coord originY, Coord destX, Coord destY) {
    Dist originX_dist = NODE_DIST * originX;
    Dist originY_dist = NODE_DIST * originY;
    Dist destX_dist = NODE_DIST * destX;
    Dist destY_dist = NODE_DIST * destY;

    VectorMove(originX_dist - currX, originY_dist - currY);
    VectorMove(-SAFE_DIST, -SAFE_DIST);
    VectorMove(destX_dist-SAFE_DIST, 0);
    VectorMove(0, destY_dist);
    VectorMove(SAFE_DIST, -0);
}

void AxisMove(Dist dist, uint8_t dir_pin, uint8_t step_pin);

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
