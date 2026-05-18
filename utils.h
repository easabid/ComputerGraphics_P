#ifndef UTILS_H

#define UTILS_H

#include <windows.h>

#include <GL/glut.h>

// ================= RECTANGLE =================

void drawRectangle(float x1,

                   float y1,

                   float x2,

                   float y2);

// ================= CIRCLE =================

void drawCircle(float x,

                float y,

                float radius);

// ================= TRIANGLE =================

void drawTriangle(float x1,

                  float y1,

                  float x2,

                  float y2,

                  float x3,

                  float y3);

// ================= LINE =================

void drawLine(float x1,

              float y1,

              float x2,

              float y2);

#endif
