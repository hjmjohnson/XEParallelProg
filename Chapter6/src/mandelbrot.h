#ifndef __MANDLE_H__
#define __MANDLE_H__
const int   factor = 8;
const int   maxThreshold = 96;
const int   maxIteration = 500;
const int   maxI = 1024 * factor;
const int   maxJ = 1024 * factor;
const float deltaX = 4.0;
const float deltaY = 4.0;

extern float zr[maxI][maxJ], zi[maxI][maxJ];
extern float zcolor[maxI][maxJ];

extern void Mandelbrot();

extern void WriteMandlebrot();

#endif
