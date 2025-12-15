//
// Created by CJ on 12/7/25.
//

#include "write.h"

int writeImage(const SLImage * image) {
    return writeToFile(image->fileName, image->xSize, image->ySize, image->data);
}

int writeToFile(const char* fileName, const uint32_t xSize, const uint32_t ySize, const uint32_t* data) {

    // Bytes for file header
    const unsigned char headerBytes[4] = {0xFF, 0xA5, 0xFF, 0xE8};

    FILE* f = fopen(fileName, "wb+");

    // Write header bytes
    fwrite(&headerBytes, sizeof(unsigned char), sizeof(headerBytes) / sizeof(unsigned char), f);

    // Write size to file
    fwrite(&xSize, sizeof(int32_t), 1, f);
    fwrite(&ySize, sizeof(int32_t), 1, f);

    // Write pixel datastream to file
    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            fwrite(&data[y * xSize + x], sizeof(int32_t), 1, f);
        }
    }

    fclose(f);

    return 0;
}


uint32_t* generateTestData(const uint32_t xSize, const uint32_t ySize) {

    uint32_t* data = malloc(xSize * ySize * sizeof(uint32_t));

    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {

            const uint32_t pixelVal = ((uint32_t)tan(y) * 255 / ySize) | ((uint32_t)(tan(x) * 255 / (uint32_t)log(xSize)) << 19);
            data[y * xSize + x] = pixelVal;
        }
    }

    return data;
}

uint32_t* whiteImage(const uint32_t xSize, const uint32_t ySize) {

    uint32_t* data = malloc(xSize * ySize * sizeof(uint32_t));

    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            data[y * xSize + x] = 0xFFFFFFFF;
        }
    }

    return data;
}

SLImage* createEmptyImage(char* fileName, const uint32_t xSize, const uint32_t ySize) {

    SLImage* image = malloc(sizeof(SLImage));

    image->fileName = fileName;

    image->xSize = xSize;
    image->ySize = ySize;

    image->data = whiteImage(xSize, ySize);

    return image;
}