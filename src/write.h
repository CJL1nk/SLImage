//
// Created by CJ on 12/7/25.
//

#ifndef WRITE_H
#define WRITE_H

#include "includes.h"

int write(const char* fileName, uint32_t xSize, uint32_t ySize, const uint32_t* data);
uint32_t* generateTestData(uint32_t xSize, uint32_t ySize);

#endif //WRITE_H
