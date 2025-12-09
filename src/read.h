//
// Created by CJ on 12/7/25.
//

#ifndef READ_H
#define READ_H

#include "includes.h"

/**
 * Reads and creates an image object from given filename
 * @param fileName Path to image to read
 * @return Pointer to created image object
 */
SLImage* readImage(const char* fileName);

#endif //READ_H
