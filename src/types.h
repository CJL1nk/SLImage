//
// Created by CJ on 12/7/25.
//

#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

typedef struct SLImage {

    char* fileName;

    int32_t xSize;
    int32_t ySize;

    const char* imageData[];
} SLImage;

#endif //TYPES_H
