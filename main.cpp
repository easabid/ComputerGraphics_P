#include <windows.h>

#include <GL/glut.h>

#include <stdlib.h>

#include <math.h>

#include "utils.h"

#include "city.h"

#include "village.h"

#include "transition.h"

// ================= STARS =================

void drawStars()

{

    if(!isNight)

    {

        return;

    }

    glColor3f(1.0f,

              1.0f,

              1.0f);

    for(int i=0;i<80;i++)

    {

        float x = rand()%100;

        float y = 55 + rand()%45;

        drawCircle(x,

                   y,

                   0.15f);

    }

}

// ================= RAIN =================

void drawRain()

{

    if(!rainMode)

    {

        return;

    }

    glColor4f(0.8f,

              0.8f,

              1.0f,

              0.7f);

    glBegin(GL_LINES);

    for(int i=0;i<150;i++)

    {

        float x = rand()%100;

        float y = rand()%100;

        glVertex2f(x,y);

        glVertex2f(x-1,

                   y-3);

    }

    glEnd();

}

// ================= SUN =================

void drawSun()

{

    // Do not draw at night

    if(isNight)

    {

        return;

    }

    glPushMatrix();

    glTranslatef(sunX,

                 sunY,

                 0);

    // Sun body

    glColor3f(1.0f,

              0.85f,

              0.2f);

    drawCircle(0,

               0,

               5);

    // Rays

    glColor3f(1.0f,

              0.75f,

              0.1f);

    for(int i=0;i<360;i+=30)

    {

        float angle =

        i * 3.1416f / 180.0f;

        float x1 =

        cos(angle)*6;

        float y1 =

        sin(angle)*6;

        float x2 =

        cos(angle)*8;

        float y2 =

        sin(angle)*8;

        drawLine(x1,y1,x2,y2);

    }

    glPopMatrix();

}

// ================= MOON =================

void drawMoon()

{

    // Only at night

    if(!isNight)

    {

        return;

    }

    glPushMatrix();

    glTranslatef(moonX,

                 moonY,

                 0);

    // Moon body

    glColor3f(0.95f,

              0.95f,

              1.0f);

    drawCircle(0,

               0,

               4.5f);

    // Crescent shadow

    glColor3f(skyRed,

              skyGreen,

              skyBlue);

    drawCircle(1.5f,

               0.5f,

               4);

    glPopMatrix();

}

// ================= GLOBAL SKY =================

void drawGlobalSky()

{

    glColor3f(skyRed,

              skyGreen,

              skyBlue);

    drawRectangle(0,

                  0,

                  100,

                  100);

}

// ================= SOUND PLACEHOLDER =================

void soundLogic()

{

    // Placeholder for future sound system

    // Example:

    // city traffic sound

    // rain sound

    // village birds sound

}

// ================= DISPLAY =================

void display()

{

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Sky

    drawGlobalSky();

    // Zoom

    glScalef(zoomScale,

             zoomScale,

             1);

    // Camera movement

    glTranslatef(-cameraOffset,

                 0,

                 0);

    // Celestial objects

    drawSun();

    drawMoon();

    drawStars();

    // Scenes

    drawCityScene(1.0f - transitionAlpha);

    drawVillageScene(transitionAlpha);

    // Weather

    drawRain();

    glutSwapBuffers();

}

// ================= UPDATE =================

void update(int value)

{

    // Scene animations

    updateCityAnimation();

    updateVillageAnimation();

    updateTransition();

    // Sound placeholder

    soundLogic();

    glutPostRedisplay();

    // Frame control ~60 FPS

    glutTimerFunc(16,

                  update,

                  0);

}

// ================= RESET =================

void resetScene()

{

    // Transition reset

    startTransition = false;

    transitionAlpha = 0.0f;

    // Object scales

    buildingScale = 1.0f;

    treeScale = 0.0f;

    carScale = 1.0f;

    cowScale = 0.0f;

    roadTransition = 0.0f;

    cameraOffset = 0.0f;

    // Day reset

    isNight = false;

    sunX = -20.0f;

    sunY = 88.0f;

    moonX = -40.0f;

    moonY = 88.0f;

    // Sky reset

    skyRed = 0.72f;

    skyGreen = 0.86f;

    skyBlue = 0.98f;

    // Rain

    rainMode = false;

    // Speed

    animationSpeed = 1.0f;

    // Zoom

    zoomScale = 1.0f;

}

// ================= KEYBOARD =================

void keyboard(unsigned char key,

              int x,

              int y)

{

    switch(key)

    {

        // Start transition

        case 't':

        case 'T':

            startTransition = true;

            break;

        // Force day

        case 'd':

        case 'D':

            isNight = false;

            sunX = -20.0f;

            sunY = 88.0f;

            skyRed = 0.72f;

            skyGreen = 0.86f;

            skyBlue = 0.98f;

            break;

        // Force night

        case 'n':

        case 'N':

            isNight = true;

            moonX = -20.0f;

            moonY = 88.0f;

            skyRed = 0.05f;

            skyGreen = 0.08f;

            skyBlue = 0.18f;

            break;

        // Rain toggle

        case 'r':

        case 'R':

            rainMode = !rainMode;

            break;

        // Pause

        case 'p':

        case 'P':

            pauseAnimation = true;

            break;

        // Resume

        case 's':

        case 'S':

            pauseAnimation = false;

            break;

        // Increase speed

        case '+':

            animationSpeed += 0.2f;

            break;

        // Decrease speed

        case '-':

            animationSpeed -= 0.2f;

            if(animationSpeed < 0.2f)

            {

                animationSpeed = 0.2f;

            }

            break;

        // Zoom in

        case 'z':

        case 'Z':

            zoomScale += 0.1f;

            break;

        // Zoom out

        case 'x':

        case 'X':

            zoomScale -= 0.1f;

            if(zoomScale < 0.5f)

            {

                zoomScale = 0.5f;

            }

            break;

        // Reset everything

        case '0':

            resetScene();

            break;

        // Exit

        case 27:

            exit(0);

    }

}

// ================= INIT =================

void init()

{

    glClearColor(0,

                 0,

                 0,

                 1);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0,

               100,

               0,

               100);

    glMatrixMode(GL_MODELVIEW);

}

// ================= MAIN =================

int main(int argc,

         char** argv)

{

    glutInit(&argc,

             argv);

    glutInitDisplayMode(

        GLUT_DOUBLE | GLUT_RGB

    );

    // Window size

    glutInitWindowSize(1200,

                       700);

    glutCreateWindow(

        "Urban To Rural Transition"

    );

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutTimerFunc(16,

                  update,

                  0);

    glutMainLoop();

    return 0;

}
