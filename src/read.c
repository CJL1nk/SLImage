//
// Created by CJ on 12/7/25.
//

#include "read.h"

/**
 * Reads and creates an image object from given filename
 * @param fileName Path to image to read
 * @return Pointer to created image object
 */
SLImage* readImage(const char* fileName) {

    // Bytes for file header
    const unsigned char headerBytes[4] = {0xFF, 0xA5, 0xFF, 0xE8};

    SLImage *image = (SLImage*) malloc(sizeof(SLImage));
    unsigned char dataBuffer[4];
    uint32_t value;

    FILE* f = fopen(fileName, "rb");

    // Read 4 bytes from offset 0, ensure the header is FF A5 FF E8
    fread(dataBuffer, 1, 4, f);
    for (int i = 0; i < 4; i++) {

        if (dataBuffer[i] != headerBytes[i]) {
          printf("Not a valid SLImage\n");

          exit(2);
        }
    }

    // Read 4 bytes from offset 4, the offset where xSize is stored (int32)
    fread(dataBuffer, 1, 4, f);
    value = (int32_t)((unsigned char)dataBuffer[0] |
                      (unsigned char)dataBuffer[1] << 8 |
                      (unsigned char)dataBuffer[2] << 16 |
                      (unsigned char)dataBuffer[3] << 24);

    image->xSize = value;

    // Read 4 bytes from offset 8, the offset where ySize is stored (int32)
    fread(dataBuffer, 1, 4, f);
    value = (int32_t)((unsigned char)dataBuffer[0] |
                      (unsigned char)dataBuffer[1] << 8 |
                      (unsigned char)dataBuffer[2] << 16 |
                      (unsigned char)dataBuffer[3] << 24);

    image->ySize = value;

    // Allocate space for pixel datastream
    image->data = (uint32_t *)malloc(image->xSize * image->ySize * sizeof(uint32_t));

    // Loop through every pixel in the image's pixel datastream and load to memory
    for (int y = 0; y < image->ySize; y++) {
        for (int x = 0; x < image->xSize; x++) {

            fread(dataBuffer, 1, 4, f);

            value = (uint32_t)((unsigned char)dataBuffer[0] |
                               (unsigned char)dataBuffer[1] << 8 |
                               (unsigned char)dataBuffer[2] << 16 |
                               (unsigned char)dataBuffer[3] << 24);
            image->data[y * image->xSize + x] = value;
        }
    }

    fclose(f);
    return image;
}