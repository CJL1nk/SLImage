//
// Created by CJ on 12/7/25.
//

#include "includes.h"
#include "write.h"
#include "display.h"
#include "read.h"
#include "editor.h"

int main(const int argc, char* argv[]) {

    if (argc < 3) {
        printf("Usage: ./SLImage <mode> <filename> <width> <height>\n");
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

            const int xSize = atoi(argv[3]);
            const int ySize = atoi(argv[4]);

            const uint32_t* testData = generateTestData(xSize, ySize);
            write(fileName, xSize, ySize, testData);

            free(testData);

            break;
        }

        case 'r': {
            const SLImage* image = readImage(fileName);

            printf("xSize: %d\n", image->xSize);
            printf("ySize: %d\n", image->ySize);

            viewImage(image);

            break;
        }

    case 'e': {

            createDefaultEditorWindow(512, 512);
            break;
    }

        default: {
            printf("Valid modes: w (Write), r (Read)\n");
        }
    }

    return 0;
}
