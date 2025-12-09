//
// Created by CJ on 12/7/25.
//

#include "display.h"

/**
 * Creates and opens X11 display
 * @return Pointer to created display object
 */
Display* createDisplay() {

    Display* display;
    display = XOpenDisplay(NULL);

    if (!display) {
        printf("Failed to open display.\n");
        exit(1);
    }

    return display;
}

/**
 * Creates and maps window from given display
 * @param display Display to create window for
 * @param xSize Window width
 * @param ySize Window height
 * @return Pointer to created window object
 */
Window createWindow(Display* display, int xSize, int ySize) {

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

    return window;
}

/**
 * Creates a simple window to view an image.
 * @param image Image to view
 * @return 0 if successful, 1 otherwise
 */
int viewImage(const SLImage* slimage) {

    XEvent event;
    char exit = 0;

    Display* display = createDisplay();
    Window window = createWindow(display, slimage->xSize, slimage->ySize);
    GC gc = XCreateGC(display, window, 0, 0);

    int screen = DefaultScreen(display);

    // Buffer that holds pixel data
    uint32_t* buffer = (uint32_t *)malloc(slimage->xSize * slimage->ySize * sizeof(uint32_t));

    // Image to render within X11 window
    XImage *image = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), ZPixmap, 0, (char *)buffer, slimage->xSize, slimage->ySize, 32, 0);

    // Loop through every pixel and load into X11 image buffer
    for (int y = 0; y < slimage->ySize; y++) {
        for (int x = 0; x < slimage->xSize; x++) {
            buffer[y * slimage->xSize + x] = slimage->data[y * slimage->xSize + x];
        }
    }

    // Continuously loop until exit is called
    while (!exit) {

        XNextEvent(display, &event);

        switch (event.type) {

            case Expose: {

                // Display image on window
                XPutImage(display, window, gc, image, 0, 0, 0, 0, slimage->xSize, slimage->ySize);
                XFlush(display);
                break;
            }
            case KeyPress: {
                exit = 1;
                break;
            }
            case ButtonPress: {
                printf("MousePress\n");
                break;
            }
        }
    }

    free(buffer);
    return 0;
}