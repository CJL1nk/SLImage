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

    Display* display = createDisplay();
    const Window window = createWindow(display, slimage->xSize, slimage->ySize);
    const GC gc = XCreateGC(display, window, 0, 0);

    const int screen = DefaultScreen(display);

    // Buffer that holds slimage pixel data
    uint32_t* buffer = (uint32_t*)malloc(slimage->xSize * slimage->ySize * sizeof(uint32_t));

    if (!buffer) {
        printf("Failed to allocate buffer.\n");
        return 1;
    }

    // Image to render within X11 window
    XImage *ximage = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen), ZPixmap, 0, (char *)buffer, slimage->xSize, slimage->ySize, 32, 0);

    if (!ximage) {
        printf("Failed to create XImage.\n");
        return 1;
    }

    // Loop through every pixel and load into X11 image buffer
    for (int y = 0; y < slimage->ySize; y++) {
        for (int x = 0; x < slimage->xSize; x++) {
            buffer[y * slimage->xSize + x] = slimage->data[y * slimage->xSize + x];
        }
    }

    while (!exit)
    {
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

                    case 30: {
                            color += 0x00110000;
                            break;
                    }
                    case 44: {
                            color -= 0x00110000;
                            break;
                    }

                    default: {
                            exit = 1;
                    }
                }

          printf("%d", event.xkey.keycode);

                break;
        }
        case ButtonPress: {

                int xpos = event.xbutton.x;
                int ypos = event.xbutton.y;

                buffer[ypos * slimage->xSize + xpos] = color;
                buffer[ypos * slimage->xSize + (xpos + 1)] = color;
                buffer[ypos * slimage->xSize + (xpos - 1)] = color;
                buffer[(ypos + 1) * slimage->xSize + xpos] = color;
                buffer[(ypos - 1) * slimage->xSize + xpos] = color;

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