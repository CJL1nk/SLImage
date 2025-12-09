//
// Created by CJ on 12/7/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include "includes.h"

/**
 * Creates and opens X11 display
 * @return Pointer to created display object
 */
Display* createDisplay();

/**
 * Creates and maps window from given display
 * @param display Display to create window for
 * @param xSize Window width
 * @param ySize Window height
 * @return Pointer to created window object
 */
Window createWindow(Display* display, int xSize, int ySize);

/**
 * Creates a simple window to view an image.
 * @param image Image to view
 * @return 0 if successful, 1 otherwise
 */
int viewImage(const SLImage* image);

#endif //DISPLAY_H
