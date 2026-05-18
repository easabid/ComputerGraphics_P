#include "utils.h"

#include <math.h>

// ================= RECTANGLE =================

void drawRectangle(float x1,

                   float y1,

                   float x2,

                   float y2)

{

    glBegin(GL_POLYGON);

        glVertex2f(x1,y1);

        glVertex2f(x2,y1);

        glVertex2f(x2,y2);

        glVertex2f(x1,y2);

    glEnd();

}

// ================= CIRCLE =================

void drawCircle(float x,

                float y,

                float radius)

{

    glBegin(GL_POLYGON);

    for(int i=0;i<360;i++)

    {

        float angle =

        i * 3.1416f / 180.0f;

        float dx =

        radius * cos(angle);

        float dy =

        radius * sin(angle);

        glVertex2f(x + dx,

                   y + dy);

    }

    glEnd();

}

// ================= TRIANGLE =================

void drawTriangle(float x1,

                  float y1,

                  float x2,

                  float y2,

                  float x3,

                  float y3)

{

    glBegin(GL_TRIANGLES);

        glVertex2f(x1,y1);

        glVertex2f(x2,y2);

        glVertex2f(x3,y3);

    glEnd();

}

// ================= LINE =================

void drawLine(float x1,

              float y1,

              float x2,

              float y2)

{

    glBegin(GL_LINES);

        glVertex2f(x1,y1);

        glVertex2f(x2,y2);

    glEnd();

}
