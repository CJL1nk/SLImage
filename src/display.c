//
// Created by CJ on 12/7/25.
//

#include "display.h"

Display* createWindow(int xSize, int ySize) {

    Display* display;
    display = XOpenDisplay(NULL);

    if (!display) {
        printf("Failed to open display.\n");
        exit(1);
    }

    int screen_num = DefaultScreen(display);
    Window root_window = RootWindow(display, screen_num);

    Window window = XCreateSimpleWindow(
        display,
        root_window,
        0, 0, // x, y position
        xSize, ySize, // width, height
        1, // border_width
        BlackPixel(display, screen_num), // border_pixel
        WhitePixel(display, screen_num) // background_pixel
    );

    XSetStandardProperties(
        display,
        window,
        "SLImage Viewer", // window name
        "Hello", // icon name
        None, // icon pixmap
        NULL, 0, // command arguments
        NULL // hints
    );

    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);

    XMapWindow(display, window);

    return display;
}