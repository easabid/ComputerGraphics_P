#include "utils.h"

float clampColor(float value)
{
    if(value < 0.0f)
        return 0.0f;

    if(value > 1.0f)
        return 1.0f;

    return value;
}

void drawCircle(float cx, float cy,
                float r, int segments)
{
    glBegin(GL_POLYGON);

    for(int i = 0; i < segments; i++)
    {
        float theta =
        2.0f * 3.1416f * i / segments;

        float x = r * cos(theta);
        float y = r * sin(theta);

        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}

void drawRectangle(float x1, float y1,
                   float x2, float y2)
{
    glBegin(GL_QUADS);

        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);

    glEnd();
}

void drawTriangle(float x1, float y1,
                  float x2, float y2,
                  float x3, float y3)
{
    glBegin(GL_TRIANGLES);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);

    glEnd();
}

void drawLine(float x1, float y1,
              float x2, float y2)
{
    glBegin(GL_LINES);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);

    glEnd();
}
