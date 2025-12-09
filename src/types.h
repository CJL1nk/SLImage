//
// Created by CJ on 12/7/25.
//

#ifndef TYPES_H
#define TYPES_H

typedef struct SLImage {

    char* fileName;

    uint32_t xSize;
    uint32_t ySize;

    uint32_t size;
    uint32_t* data;

} SLImage;

#endif //TYPES_H
