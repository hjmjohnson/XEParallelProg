#ifndef __MANDLE_H__
#define __MANDLE_H__

#include <stdlib.h>

constexpr size_t factor = 8;
constexpr size_t maxThreshold = 96;
constexpr size_t maxIteration = 500;
constexpr size_t maxI = 1024 * factor;
constexpr size_t maxJ = 1024 * factor;
constexpr float deltaX = 4.0;
constexpr float deltaY = 4.0;

extern float zr[maxI][maxJ];
extern float zi[maxI][maxJ];
extern float zcolor[maxI][maxJ];

extern void Mandelbrot();

extern size_t CalculateMandelbrotSignature();
extern void WriteMandlebrot();

#endif
