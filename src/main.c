//
// Created by CJ on 12/7/25.
//

#include "includes.h"
#include "write.h"
#include "display.h"
#include "read.h"
#include "editor.h"

int main(const int argc, char* argv[]) {

    if (argc < 2) {
        printf("Usage: ./SLImage <mode> <filename> <width> <height>\n");
        return 1;
    }

    const char mode = argv[1][0];
    const char* fileName = argv[2];

    switch (mode) {
        case 'w': { // Generates a test image

            const int xSize = atoi(argv[3]);
            const int ySize = atoi(argv[4]);

            if (!xSize || !ySize) {
                printf("Please specify a width and height!\n");
                return 1;
            }

            const uint32_t* testData = generateTestData(xSize, ySize);
            writeToFile(fileName, xSize, ySize, testData);

            free(testData);

            break;
        }

        case 'r': {
            if (!fileName) {
                printf("Please specify a filename!\n");
                return 1;
            }
            const SLImage* image = readImage(fileName);

            printf("xSize: %d\n", image->xSize);
            printf("ySize: %d\n", image->ySize);

            viewImage(image);

            break;
        }

        case 'e': {

            unsigned int xSize;
            unsigned int ySize;

            if (!fileName) {
                createDefaultEditorWindow(512, 512);
                return 0;
            }

            char* width = argv[3];
            char* height = argv[4];

            if (!width || !height) {
                xSize = 512;
                ySize = 512;
            } else {
                xSize = atoi(width);
                ySize = atoi(height);
            }

            SLImage* slimage = readImage(fileName);

            if (!slimage) {
                slimage = createEmptyImage(fileName, xSize, ySize);
            }

            createEditorWindow(slimage);
            break;
        }

        default: {
            printf("Valid modes: r (Read), e (Editor), w (Test Write)\n");
        }
    }

    return 0;
}
