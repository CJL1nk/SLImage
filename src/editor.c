//
// Created by cj_link on 12/12/25.
//

#include "editor.h"
#include "write.h"

int createDefaultEditorWindow(int xSize, int ySize) {
    SLImage* slimage = createEmptyImage(xSize, ySize);

    const int returnVal = createEditorWindow(slimage);

    free(slimage);

    return returnVal;
}

int createEditorWindow(const SLImage* slimage) {

    XEvent event;
    char exit = 0;

    uint32_t color = 0xFFFF0000;
    int circleRadius = 20;

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
                            break;
                    }
                    case 83: { // Numpad 4
                            color -= 0x00050000;
                            break;
                    }

                    case 80: { // Numpad 8
                          color += 0x00000500;
                          break;
                    }
                    case 84: { // Numpad 5
                          color -= 0x00000500;
                          break;
                    }

                    case 81: { // Numpad 9
                          color += 0x00000005;
                          break;
                    }
                    case 85: { // Numpad 6
                          color -= 0x00000005;
                          break;
                    }

                    case 24: { // q
                        write(slimage->fileName, slimage->xSize, slimage->ySize, slimage->data);
                        printf("Saved image");
                        exit = 1;
                        break;
                    }

                    case 39: { // s
                        write(slimage->fileName, slimage->xSize, slimage->ySize, slimage->data);
                        printf("Saved image");
                        break;
                    }

                    default: {
                            exit = 1;
                            break;
                    }
                }

                printf("%d\n", event.xkey.keycode);
                break;
            }
            case ButtonPress: {

                int xpos = event.xbutton.x;
                int ypos = event.xbutton.y;

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