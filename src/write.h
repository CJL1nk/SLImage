//
// Created by CJ on 12/7/25.
//

#ifndef WRITE_H
#define WRITE_H

#include "includes.h"

/**
 * Writes image data to file
 * Does NOT free image->data
 * @param image Image to write
 * @return 0 if successful, 1 otherwise
 */
int writeImage(const SLImage* image);

/**
 * Writes image data to file
 * Does NOT free image->data
 * @param fileName Name of file to write
 * @param xSize Image width
 * @param ySize Image height
 * @param data Image datastream
 * @return 0 if successful, 1 otherwise
 */
int writeToFile(const char* fileName, uint32_t xSize, uint32_t ySize, const uint32_t* data);

/**
 * Generates a gradient to fill an image with
 * @param xSize Image width
 * @param ySize Image height
 * @return Pointer to generated image data
 */
uint32_t* generateTestData(uint32_t xSize, uint32_t ySize);

/**
 * Generates white image data
 * @param xSize Image width
 * @param ySize Image height
 * @return
 */
uint32_t * whiteImage(uint32_t xSize, uint32_t ySize);

/**
 * Creates an empty image
 * @param fileName Name for file
 * @param xSize Image width
 * @param ySize Image height
 * @return
 */
SLImage* createEmptyImage(char* fileName, uint32_t xSize, uint32_t ySize);

#endif //WRITE_H
