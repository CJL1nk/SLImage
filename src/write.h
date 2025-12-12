//
// Created by CJ on 12/7/25.
//

#ifndef WRITE_H
#define WRITE_H

#include "includes.h"

/**
 * Writes image data to file
 * @param fileName Name of file to write
 * @param xSize Image width
 * @param ySize Image height
 * @param data Image datastream
 * @return 0 if successful, 1 otherwise
 */
int write(const char* fileName, uint32_t xSize, uint32_t ySize, const uint32_t* data);

/**
 * Generates a gradient to fill an image with
 * @param xSize Image width
 * @param ySize Image height
 * @return Pointer to generated image data
 */
uint32_t* generateTestData(uint32_t xSize, uint32_t ySize);

uint32_t* whiteImage(uint32_t xSize, uint32_t ySize);

SLImage* createEmptyImage(uint32_t xSize, uint32_t ySize);

#endif //WRITE_H
