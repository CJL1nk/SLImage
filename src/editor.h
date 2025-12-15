//
// Created by cj_link on 12/12/25.
//

#ifndef SLIMAGE_EDITOR_H
#define SLIMAGE_EDITOR_H

#include "includes.h"
#include "display.h"

/**
 *
 * @param dsp Display to run timer
 * @param event_return Event to return to
 * @param tv Time value to timeout
 * @return 1 if event happened, 0 otherwise
 */
Bool XNextEventTimed(Display* dsp, XEvent* event_return, struct timeval* tv);

/**
 * Creates an editor window with a blank image
 * @param xSize Image width
 * @param ySize Image height
 * @return 0 if successful, 1 otherwise
 */
int createDefaultEditorWindow(uint32_t xSize, uint32_t ySize);

/**
 * Creates an editor window with a given image
 * @param slimage Image to load into window
 * @return 0 if successful, 1 otherwise
 */
int createEditorWindow(const SLImage* slimage);

#endif //SLIMAGE_EDITOR_H