//
// Created by CJ on 12/7/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include "includes.h"

Display* createDisplay();
Window createWindow(Display* display, int xSize, int ySize);
int viewImage(const SLImage* image);

#endif //DISPLAY_H
