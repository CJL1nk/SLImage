//
// Created by CJ on 12/7/25.
//

#include <stdio.h>

#include "write.h"
#include "read.h"
#include "types.h"

int main(const int argc, char* argv[]) {

    if (argc != 3) {
        printf("Usage: ./SLImage <mode> <filename>\n");
        return 1;
    }

    const char mode = argv[1][0];
    const char* fileName = argv[2];

    if (fileName == NULL) {
        fileName = "image.slmg";
    }

    switch (mode) {
        case 'w': {
            const char* writeBytes[] = {};
            write(fileName, 2048, 512, writeBytes);
            break;
        }

        case 'r': {
            SLImage* image = readImage(fileName);

            printf("xSize: %d\n", image->xSize);
            printf("ySize: %d\n", image->ySize);

            free(image);
            break;
        }

        default: {
            printf("Valid modes: w (Write), r (Read)\n");
        }
    }

    return 0;
}
