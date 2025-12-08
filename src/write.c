//
// Created by CJ on 12/7/25.
//

#include "write.h"
#include "types.h"

/*
 * Writes a full SLImage to a file
 */
int write(const char* fileName, int32_t xSize, int32_t ySize, const char* writeBytes[]) {

    FILE* f = fopen(fileName, "wb+");

    // Bytes for file header
    unsigned char headerBytes[4] = {0xFF, 0xA5, 0xFF, 0xE8};

    // Write header bytes
    fwrite(&headerBytes, sizeof(unsigned char), sizeof(headerBytes) / sizeof(unsigned char), f);

    // Write size to file
    fwrite(&xSize, sizeof(int32_t), 1, f);
    fwrite(&ySize, sizeof(int32_t), 1, f);

    fclose(f);

    return 0;
}