//
// Created by CJ on 12/7/25.
//

#include "includes.h"
#include "write.h"
#include "display.h"
#include "read.h"

int main(const int argc, char* argv[]) {

    if (argc != 3) {
        printf("Usage: ./SLImage <mode> <filename>\n");
        return 1;
    }

    const char mode = argv[1][0];
    const char* fileName = argv[2];

    // Should never happen
    if (fileName == NULL || fileName == "") {
        fileName = "image.slmg";
    }

    switch (mode) {
        case 'w': {
            const char* writeBytes[] = {};
            write(fileName, 128, 128, writeBytes);
            break;
        }

        case 'r': {
            SLImage* image = readImage(fileName);

            printf("xSize: %d\n", image->xSize);
            printf("ySize: %d\n", image->ySize);

            Display* display = createWindow(image->xSize, image->ySize);

            XEvent event;
            while (1) {
                XNextEvent(display, &event);
                switch (event.type) {
                    case Expose:
                        printf("Expose\n");
                        break;
                    case KeyPress:
                        printf("KeyPress\n");
                        break;
                    case ButtonPress:
                        printf("MousePress\n");
                        break;
                }
            }

            // Goodbye memory
            XCloseDisplay(display);
            free(display);
            free(image);
            break;
        }

        default: {
            printf("Valid modes: w (Write), r (Read)\n");
        }
    }

    return 0;
}
