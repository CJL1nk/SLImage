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
Window createWindow(Display* display, uint32_t xSize, uint32_t ySize);

/**
 * Creates a simple window to view an image.
 * Frees slimage->data upon exit due to nature of X11
 * @param slimage SLImage to view
 * @return 0 if successful, 1 otherwise
 */
int viewImage(const SLImage* slimage);

#endif //DISPLAY_H
