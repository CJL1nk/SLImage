//
// Created by cj_link on 12/12/25.
//

#include "editor.h"
#include "write.h"

// Thank you Google
Bool XNextEventTimed(Display* dsp, XEvent* event_return, struct timeval* tv) {
    // If events are already pending, process one immediately.
    if (XPending(dsp) > 0) {
        XNextEvent(dsp, event_return);
        return True;
    }

    // If no events pending, use select() to wait with a timeout.
    int fd = ConnectionNumber(dsp);
    fd_set readset;
    FD_ZERO(&readset);
    FD_SET(fd, &readset);

    // select() modifies the timeval structure, so a copy may be needed if
    // you want to reuse the same initial timeout value in a loop.
    struct timeval timeout_copy = *tv;

    if (select(fd + 1, &readset, NULL, NULL, &timeout_copy) == 0) {
        // Timeout occurred.
        return False;
    } else {
        // Data is ready on the X11 file descriptor.
        XNextEvent(dsp, event_return);
        return True;
    }
}

int createDefaultEditorWindow(const uint32_t xSize, const uint32_t ySize) {

    SLImage* slimage = createEmptyImage("unnamed.slmg", xSize, ySize);

    const int returnVal = createEditorWindow(slimage);

    free(slimage);

    return returnVal;
}

int createEditorWindow(const SLImage* slimage) {

    XEvent event;
    char exit = 0;
    struct timeval timeVal = {0, 20};

    uint32_t color = 0x00000000;
    uint8_t red = 0x00;
    uint8_t green = 0x00;
    uint8_t blue = 0x00;
    uint8_t alpha = 0xFF;

    uint8_t circleRadius = 5;
    uint8_t mouseDown = 0;

    int root_x, root_y, win_x, win_y;
    unsigned int mask;

    Display* display = createDisplay();
    const Window window = createWindow(display, slimage->xSize, slimage->ySize, "SLImage Editor");
    const GC gc = XCreateGC(display, window, 0, 0);
    Window rootWindow = XDefaultRootWindow(display); // Used for querying pointer position
    Window childWindow;

    const int screen = DefaultScreen(display);

    // Image to render within X11 window
    XImage *ximage = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), ZPixmap, 0, (char *)slimage->data, slimage->xSize, slimage->ySize, 32, 0);

    if (!ximage) {
        printf("Failed to create XImage.\n");
        return 1;
    }

    while (!exit) {

        if (XNextEventTimed(display, &event, &timeVal) == 1) {
            // Death by switch case
            switch (event.type) {

                case Expose: {
                    // Display image on window
                    XPutImage(display, window, gc, ximage, 0, 0, 0, 0, slimage->xSize, slimage->ySize);
                    XFlush(display);
                    break;
                }

                case KeyPress: {
                    switch (event.xkey.keycode) {

                        case 87: { // Numpad 1
                            alpha += 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            color = color | (uint32_t)red << 16;
                            printf("Color: %X\n", color);
                            break;
                        }
                        case 90: { // Numpad 0
                            alpha -= 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            color = color | (uint32_t)red << 16;
                            printf("Color: %X\n", color);
                            break;
                        }
                        case 79: { // Numpad 7
                            red += 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            color = color | (uint32_t)red << 16;
                            printf("Color: %X\n", color);
                            break;
                        }
                        case 83: { // Numpad 4
                            red -= 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            printf("Color: %X\n", color);
                            break;
                        }

                        case 80: { // Numpad 8
                            green += 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            printf("Color: %X\n", color);
                            break;
                        }
                        case 84: { // Numpad 5
                            green -= 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            printf("Color: %X\n", color);
                            break;
                        }

                        case 81: { // Numpad 9
                            blue += 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            printf("Color: %X\n", color);
                            break;
                        }
                        case 85: { // Numpad 6
                            blue -= 0x05;
                            color = ((uint32_t)alpha << 24) |
                                    ((uint32_t)red << 16) |
                                    ((uint32_t)green << 8) |
                                    ((uint32_t)blue);
                            printf("Color: %X\n", color);
                            break;
                        }

                        case 20: { // -
                            circleRadius -= 1;
                            printf("Brush Radius: %d\n", circleRadius);
                            break;
                        }
                        case 21: { // +
                            circleRadius += 1;
                            printf("Brush Radius: %d\n", circleRadius);
                            break;
                        }

                        case 24: { // q
                            writeImage(slimage);
                            printf("Saved image\n");
                            exit = 1;
                            break;
                        }

                        case 39: { // s
                            writeImage(slimage);
                            printf("Saved image\n");
                            break;
                        }

                        case 9: { // ESC
                            exit = 1;
                            break;
                        }

                        default: {
                            break;
                        }
                    }

                    break;
                }

                case ButtonPress: {
                    mouseDown = 1;
                    break;
                }

                case ButtonRelease: {
                    mouseDown = 0;
                    break;
                }
            }
        }

        // If clicking, query pointer position and draw
        if (mouseDown) {

            XQueryPointer(display, window, &rootWindow, &childWindow, &root_x, &root_y, &win_x, &win_y, &mask);

            // Generate circle in image data from given radius
            for (int x = win_x - circleRadius; x <= win_x + circleRadius; x++) {
                for (int y = win_y - circleRadius; y <= win_y + circleRadius; y++) {

                    // Check euclidian distance and within image limits
                    if (y < slimage->ySize && x < slimage->xSize) {
                        if (sqrt(pow((win_x - x), 2) + pow((win_y - y), 2)) <= circleRadius &&
                            y < slimage->ySize &&
                            x < slimage->xSize) {
                            slimage->data[y * slimage->xSize + x] = color;
                        }
                    }
                }
            }

            // Draw image on dat screen xd
            XPutImage(display, window, gc, ximage, 0, 0, 0, 0, slimage->xSize, slimage->ySize);
            XFlush(display);
        }
    }

    // Also frees allocated buffer
    XDestroyImage(ximage);
    XDestroyWindow(display, window);

    return 0;
}