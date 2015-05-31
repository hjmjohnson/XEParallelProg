#ifndef __MANDLE_H__
#define __MANDLE_H__
constexpr int   factor = 8;
constexpr int   maxThreshold = 96;
constexpr int   maxIteration = 500;
constexpr int   maxI = 1024 * factor;
constexpr int   maxJ = 1024 * factor;
constexpr float deltaX = 4.0;
constexpr float deltaY = 4.0;

extern float zr[maxI][maxJ];
extern float zi[maxI][maxJ];
extern float zcolor[maxI][maxJ];

extern void Mandelbrot();

extern void WriteMandlebrot();

#endif
