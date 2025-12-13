//
// Created by cj_link on 12/12/25.
//

#include "editor.h"
#include "write.h"

int createDefaultEditorWindow(const uint32_t xSize, const uint32_t ySize) {

    SLImage* slimage = createEmptyImage(xSize, ySize);

    const int returnVal = createEditorWindow(slimage);

    free(slimage);

    return returnVal;
}

int createEditorWindow(const SLImage* slimage) {

    XEvent event;
    char exit = 0;

    uint32_t color = 0xFF000000;
    uint8_t circleRadius = 10;

    Display* display = createDisplay();
    const Window window = createWindow(display, slimage->xSize, slimage->ySize);
    const GC gc = XCreateGC(display, window, 0, 0);

    const int screen = DefaultScreen(display);

    // Image to render within X11 window
    XImage *ximage = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), ZPixmap, 0, (char *)slimage->data, slimage->xSize, slimage->ySize, 32, 0);

    if (!ximage) {
        printf("Failed to create XImage.\n");
        return 1;
    }

    while (!exit) {

        XNextEvent(display, &event);

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

                    case 79: { // Numpad 7
                        color += 0x00050000;
                        printf("Color: %X\n", color);
                        break;
                    }
                    case 83: { // Numpad 4
                        color -= 0x00050000;
                        printf("Color: %X\n", color);
                        break;
                    }

                    case 80: { // Numpad 8
                        color += 0x00000500;
                        printf("Color: %X\n", color);
                        break;
                    }
                    case 84: { // Numpad 5
                        color -= 0x00000500;
                        printf("Color: %X\n", color);
                        break;
                    }

                    case 81: { // Numpad 9
                        color += 0x00000005;
                        printf("Color: %X\n", color);
                        break;
                    }
                    case 85: { // Numpad 6
                        color -= 0x00000005;
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

                printf("%d\n", event.xkey.keycode);
                break;
            }

            case ButtonPress: {

                int xpos = event.xbutton.x;
                int ypos = event.xbutton.y;

                // Generate circle in image data from given radius
                for (int x = xpos - circleRadius; x <= xpos + circleRadius; x++) {
                    for (int y = ypos - circleRadius; y <= ypos + circleRadius; y++) {

                        if (sqrt(pow((xpos - x), 2) + pow((ypos - y), 2)) <= circleRadius ) {
                            slimage->data[y * slimage->xSize + x] = color;
                        }
                    }
                }

                XPutImage(display, window, gc, ximage, 0, 0, 0, 0, slimage->xSize, slimage->ySize);
                XFlush(display);

                break;
            }

            default: {
                    printf("The hell just happened");
            };
        }
    }

    // Also frees allocated buffer
    XDestroyImage(ximage);
    XDestroyWindow(display, window);

    return 0;
}