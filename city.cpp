#include "city.h"

#include "utils.h"

#include "transition.h"

#include <math.h>

// ================= GLOBAL VARIABLES =================

float car1X = -20.0f;

float car2X = 110.0f;

float cloudMove = 0.0f;

float smokeMove = 0.0f;

float particleMove = 0.0f;

int trafficState = 0;

float trafficTimer = 0.0f;

// ================= CLOUD =================

void drawCloud(float x,

               float y,

               float alpha)

{

    glColor4f(1.0f,

              1.0f,

              1.0f,

              alpha);

    drawCircle(x,y,3.0f);

    drawCircle(x+3,y+1,3.5f);

    drawCircle(x+6,y,3.0f);

    drawCircle(x+2,y-1,2.5f);

    drawCircle(x+5,y-1,2.5f);

}

void drawMovingClouds(float alpha)

{

    drawCloud(fmod(5 + cloudMove,130)-15,

              88,

              alpha);

    drawCloud(fmod(40 + cloudMove*0.7f,130)-15,

              92,

              alpha);

    drawCloud(fmod(75 + cloudMove*0.9f,130)-15,

              85,

              alpha);

}

// ================= BUILDING WINDOWS =================

void drawWindows(float x,

                 float y,

                 float w,

                 float h,

                 float alpha)

{

    for(float row=y+4;

        row<h+y-4;

        row+=5)

    {

        for(float col=x+2;

            col<w+x-2;

            col+=4)

        {

            float light =

            isNight ?

            fabs(sin(glutGet(GLUT_ELAPSED_TIME)*0.001f))

            : 1.0f;

            glColor4f(1.0f * light,

                      0.95f * light,

                      0.65f * light,

                      alpha);

            drawRectangle(col,

                          row,

                          col+2,

                          row+3);

        }

    }

}

// ================= BUILDING =================

void drawBuilding(float x,

                  float y,

                  float w,

                  float h,

                  float r,

                  float g,

                  float b,

                  float alpha)

{

    glColor4f(r,g,b,alpha);

    drawRectangle(x,

                  y,

                  x+w,

                  y+h);

    drawWindows(x,

                y,

                w,

                h,

                alpha);

}

// ================= ROAD =================

void drawRoad(float alpha)

{

    // Main road

    glColor4f(0.18f,

              0.18f,

              0.20f,

              alpha);

    drawRectangle(0,

                  10,

                  100,

                  28);

    // Divider

    glColor4f(1.0f,

              0.9f,

              0.2f,

              alpha);

    for(float i=0;i<100;i+=8)

    {

        drawRectangle(i+1,

                      18.5f,

                      i+5,

                      19.3f);

    }

    // Footpath

    glColor4f(0.65f,

              0.65f,

              0.65f,

              alpha);

    drawRectangle(0,

                  28,

                  100,

                  34);

    drawRectangle(0,

                  6,

                  100,

                  10);

    // Zebra crossing

    glColor4f(1,

              1,

              1,

              alpha);

    for(float y=10.5f;

        y<27;

        y+=2)

    {

        drawRectangle(38,

                      y,

                      48,

                      y+1);

    }

}

// ================= CAR =================

void drawCar(float x,

             float y,

             float r,

             float g,

             float b,

             float alpha)

{

    glColor4f(r,g,b,alpha);

    drawRectangle(x,

                  y,

                  x+10,

                  y+4);

    drawRectangle(x+2,

                  y+4,

                  x+7,

                  y+7);

    // Windows

    glColor4f(0.75f,

              0.90f,

              1.0f,

              alpha);

    drawRectangle(x+2.5f,

                  y+4.5f,

                  x+4.5f,

                  y+6);

    drawRectangle(x+5.0f,

                  y+4.5f,

                  x+6.8f,

                  y+6);

    // Wheels

    glColor4f(0.1f,

              0.1f,

              0.1f,

              alpha);

    drawCircle(x+2,

               y,

               1);

    drawCircle(x+8,

               y,

               1);

}

// ================= TRAFFIC LIGHT =================

void drawTrafficLight(float alpha)

{

    glColor4f(0.2f,

              0.2f,

              0.2f,

              alpha);

    drawRectangle(55,

                  28,

                  56,

                  46);

    drawRectangle(53.5f,

                  40,

                  57.5f,

                  48);

    // RED

    if(trafficState==0)

        glColor4f(1,0,0,alpha);

    else

        glColor4f(0.3f,0,0,alpha);

    drawCircle(55.5f,46,0.7f);

    // YELLOW

    if(trafficState==1)

        glColor4f(1,1,0,alpha);

    else

        glColor4f(0.3f,0.3f,0,alpha);

    drawCircle(55.5f,44,0.7f);

    // GREEN

    if(trafficState==2)

        glColor4f(0,1,0,alpha);

    else

        glColor4f(0,0.3f,0,alpha);

    drawCircle(55.5f,42,0.7f);

}

// ================= STREET LIGHT =================

void drawStreetLight(float x,

                     float alpha)

{

    glColor4f(0.25f,

              0.25f,

              0.25f,

              alpha);

    drawRectangle(x,

                  28,

                  x+0.8f,

                  44);

    drawLine(x+0.4f,

             44,

             x+3.5f,

             44);

    drawLine(x+3.5f,

             44,

             x+3.5f,

             42);

    float glow =

    isNight ?

    fabs(sin(glutGet(GLUT_ELAPSED_TIME)*0.002f))

    : 0.4f;

    glColor4f(1.0f*glow,

              1.0f*glow,

              0.7f*glow,

              alpha);

    drawCircle(x+3.5f,

               41.5f,

               1);

}

// ================= BUS STOP =================

void drawBusStop(float alpha)

{

    glColor4f(0.3f,

              0.3f,

              0.3f,

              alpha);

    drawRectangle(10,

                  28,

                  11,

                  38);

    drawRectangle(20,

                  28,

                  21,

                  38);

    drawRectangle(10,

                  38,

                  21,

                  40);

    glColor4f(0.2f,

              0.5f,

              0.9f,

              alpha);

    drawRectangle(11,

                  30,

                  20,

                  37);

}

// ================= BILLBOARD =================

void drawBillboard(float alpha)

{

    glColor4f(0.3f,

              0.3f,

              0.3f,

              alpha);

    drawRectangle(82,

                  34,

                  83,

                  55);

    drawRectangle(75,

                  55,

                  92,

                  65);

    glColor4f(1.0f,

              0.8f,

              0.2f,

              alpha);

    drawRectangle(76,

                  56,

                  91,

                  64);

}

// ================= ELECTRIC POLE =================

void drawElectricPole(float x,

                      float alpha)

{

    glColor4f(0.35f,

              0.20f,

              0.05f,

              alpha);

    drawRectangle(x,

                  34,

                  x+1,

                  55);

    drawLine(x-3,

             52,

             x+4,

             52);

}

void drawElectricWires(float alpha)

{

    glColor4f(0.1f,

              0.1f,

              0.1f,

              alpha);

    drawLine(6,52,31,50);

    drawLine(31,50,56,51);

    drawLine(56,51,81,49);

}

// ================= SMOKE =================

void drawSmoke(float alpha)

{

    for(int i=0;i<6;i++)

    {

        glColor4f(0.6f,

                  0.6f,

                  0.6f,

                  alpha - i*0.1f);

        drawCircle(73 + smokeMove*0.2f,

                   80 + i*3 + smokeMove,

                   2 + i*0.5f);

    }

}

// ================= POLLUTION =================

void drawPollution(float alpha)

{

    glColor4f(0.7f,

              0.7f,

              0.7f,

              alpha);

    for(int i=0;i<25;i++)

    {

        float x =

        fmod(i*7 + particleMove,100);

        float y =

        60 + sin(i)*8;

        drawCircle(x,

                   y,

                   0.3f);

    }

}

// ================= MAIN CITY SCENE =================

void drawCityScene(float alpha)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA,

                GL_ONE_MINUS_SRC_ALPHA);

    // Clouds

    drawMovingClouds(alpha);

    // Buildings

    glPushMatrix();

    glScalef(buildingScale,

             buildingScale,

             1);

    drawBuilding(2,34,12,28,

                 0.62f,0.74f,0.96f,alpha);

    drawBuilding(16,34,10,34,

                 0.95f,0.68f,0.72f,alpha);

    drawBuilding(28,34,14,30,

                 0.63f,0.86f,0.74f,alpha);

    drawBuilding(57,34,13,35,

                 0.72f,0.65f,0.92f,alpha);

    drawBuilding(72,34,12,45,

                 0.80f,0.55f,0.85f,alpha);

    glPopMatrix();

    // Smoke

    drawSmoke(alpha);

    // Pollution

    drawPollution(alpha);

    // Road

    drawRoad(alpha);

    // Moving cars

    glPushMatrix();

    glScalef(carScale,

             carScale,

             1);

    drawCar(car1X,

            14,

            0.90f,

            0.25f,

            0.20f,

            alpha);

    drawCar(car2X,

            21,

            0.20f,

            0.45f,

            0.90f,

            alpha);

    // Parked car

    drawCar(84,

            30,

            0.25f,

            0.8f,

            0.3f,

            alpha);

    glPopMatrix();

    // Traffic light

    drawTrafficLight(alpha);

    // Street lights

    drawStreetLight(18,alpha);

    drawStreetLight(38,alpha);

    drawStreetLight(76,alpha);

    // Bus stop

    drawBusStop(alpha);

    // Billboard

    drawBillboard(alpha);

    // Electric poles

    drawElectricPole(5,alpha);

    drawElectricPole(30,alpha);

    drawElectricPole(55,alpha);

    drawElectricPole(80,alpha);

    // Wires

    drawElectricWires(alpha);

    glDisable(GL_BLEND);

}

// ================= UPDATE =================

void updateCityAnimation()

{

    if(pauseAnimation)

    {

        return;

    }

    // Cars

    car1X += 0.6f * animationSpeed;

    if(car1X > 110)

    {

        car1X = -20;

    }

    car2X -= 0.5f * animationSpeed;

    if(car2X < -20)

    {

        car2X = 110;

    }

    // Clouds

    cloudMove += 0.05f * animationSpeed;

    if(cloudMove > 130)

    {

        cloudMove = 0;

    }

    // Smoke

    smokeMove += 0.03f * animationSpeed;

    if(smokeMove > 10)

    {

        smokeMove = 0;

    }

    // Pollution

    particleMove += 0.2f * animationSpeed;

    if(particleMove > 100)

    {

        particleMove = 0;

    }

    // Traffic timing

    trafficTimer += 0.02f;

    if(trafficTimer > 3.0f)

    {

        trafficState++;

        if(trafficState > 2)

        {

            trafficState = 0;

        }

        trafficTimer = 0.0f;

    }

}
