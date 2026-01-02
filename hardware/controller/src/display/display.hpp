#ifndef CONTROLLER_DISPLAY_H
#define CONTROLLER_DISPLAY_H

#include "WString.h"

#include <LiquidCrystal.h>

bool DisplayAvailable();
void PrintToDisplay(String content);

#endif  // CONTROLLER_DISPLAY_H
