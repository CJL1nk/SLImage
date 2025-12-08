//
// Created by CJ on 12/7/25.
//

#include "read.h"

/*
 * Reads an image from a given file name and returns an image object containing the image data
 * Returns an empty image if given image was not a valid image format (Header should begin with FF A5 FF E8)
 * fileName: Directory of file to read
 */
SLImage* readImage(const char* fileName) {

    // Bytes for file header
    const unsigned char headerBytes[4] = {0xFF, 0xA5, 0xFF, 0xE8};

    SLImage *image = (SLImage *) malloc(sizeof(SLImage));
    unsigned char dataBuffer[4];
    int32_t value;

    FILE* f = fopen(fileName, "rb");

    // Read 4 bytes from offset 0, ensure the header is FF A5 FF E8
    fread(dataBuffer, 1, 4, f);
    for (int i = 0; i < 4; i++) {

        if (dataBuffer[i] != headerBytes[i]) {
          printf("Not a valid SLImage\n");

          image->xSize = 0;
          image->ySize = 0;

          return image;
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

    fclose(f);
    return image;
}