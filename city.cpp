#include "city.h"

#include "utils.h"

#include "transition.h"

#include <math.h>

#include <stdlib.h>

// ================= GLOBAL VARIABLES =================

float car1X = -20.0f;

float car2X = 110.0f;

float personX = -10.0f;

float cloudMove = 0.0f;

float smokeMove = 0.0f;

float airplaneX = -40.0f;

int trafficState = 0;

float trafficTimer = 0.0f;

// ================= SKY =================

void drawCitySky(float alpha)

{

    glBegin(GL_QUADS);

    if(isNight)

        glColor4f(0.04f,0.05f,0.12f,alpha);

    else

        glColor4f(0.45f,0.75f,0.98f,alpha);

    glVertex2f(0,100);

    glVertex2f(100,100);

    if(isNight)

        glColor4f(0.18f,0.18f,0.28f,alpha);

    else

        glColor4f(0.80f,0.88f,0.95f,alpha);

    glVertex2f(100,35);

    glVertex2f(0,35);

    glEnd();

}

// ================= CLOUD =================

void drawCloud(float x,float y,float alpha)

{

    glColor4f(1,1,1,alpha);

    drawCircle(x,y,3);

    drawCircle(x+3,y+1,3.5f);

    drawCircle(x+6,y,3);

    drawCircle(x+2,y-1,2.5f);

    drawCircle(x+5,y-1,2.5f);

}

// ================= AIRPLANE =================

void drawAirplane(float alpha)

{

    glPushMatrix();

    glTranslatef(airplaneX,90,0);

    // Body

    glColor4f(0.92f,0.92f,0.95f,alpha);

    drawRectangle(0,0,10,1.5f);

    // Nose

    drawTriangle(10,0,13,0.75f,10,1.5f);

    // Wings

    glColor4f(0.80f,0.80f,0.85f,alpha);

    drawTriangle(3,1,6,5,8,1);

    drawTriangle(3,0.5f,6,-3,8,0.5f);

    // Tail

    drawTriangle(1,1,-1,3,2,1);

    glPopMatrix();

}

// ================= WINDOWS =================

void drawWindows(float x,float y,float w,float h,float alpha)

{

    for(float row=y+3;row<h+y-3;row+=3.5f)

    {

        for(float col=x+1.5f;col<w+x-1.5f;col+=3)

        {

            int light=((int)(row+col))%2;

            if(isNight)

            {

                if(light)

                    glColor4f(1.0f,0.95f,0.65f,alpha);

                else

                    glColor4f(0.15f,0.15f,0.15f,alpha);

            }

            else

            {

                glColor4f(0.75f,0.90f,1.0f,alpha);

            }

            drawRectangle(col,row,col+2,row+2.5f);

        }

    }

}

// ================= MODERN BUILDING =================

void drawModernBuilding(float x,float y,float w,float h,

                        float r,float g,float b,float alpha)

{

    glColor4f(r,g,b,alpha);

    drawRectangle(x,y,x+w,y+h);

    // Top highlight

    glColor4f(r+0.08f,g+0.08f,b+0.08f,alpha);

    drawRectangle(x,y+h-1,x+w,y+h);

    drawWindows(x,y,w,h,alpha);

}

// ================= ROAD =================

void drawRoad(float alpha)

{

    // Main road

    glColor4f(0.18f,0.18f,0.20f,alpha);

    drawRectangle(0,10,100,28);

    // Divider

    glColor4f(1.0f,0.9f,0.2f,alpha);

    for(float i=0;i<100;i+=8)

    {

        drawRectangle(i+1,18.5f,i+5,19.3f);

    }

    // Footpath

    glColor4f(0.72f,0.72f,0.72f,alpha);

    drawRectangle(0,28,100,34);

    drawRectangle(0,6,100,10);

    // Zebra crossing

    glColor4f(1,1,1,alpha);

    for(float y=10.5f;y<27;y+=2)

    {

        drawRectangle(40,y,50,y+1);

    }

}

// ================= CAR =================

void drawCar(float x,float y,

             float r,float g,float b,

             float alpha,bool moveRight)

{

    float bounce=

    sin(glutGet(GLUT_ELAPSED_TIME)

    *0.01f)*0.3f;

    glPushMatrix();

    glTranslatef(0,bounce,0);

    // Body

    glColor4f(r,g,b,alpha);

    drawRectangle(x,y,x+10,y+4);

    drawRectangle(x+2,y+4,x+7,y+7);

    // Windows

    glColor4f(0.75f,0.90f,1.0f,alpha);

    drawRectangle(x+2.5f,y+4.5f,x+4.5f,y+6);

    drawRectangle(x+5,y+4.5f,x+6.8f,y+6);

    // Wheels

    glColor4f(0.1f,0.1f,0.1f,alpha);

    drawCircle(x+2,y,1);

    drawCircle(x+8,y,1);

    // Headlights

    if(isNight)

    {

        glColor4f(1.0f,1.0f,0.6f,0.3f);

        if(moveRight)

        {

            drawTriangle(x+10,y+3,

                         x+15,y+5,

                         x+15,y+1);

        }

        else

        {

            drawTriangle(x,y+3,

                         x-5,y+5,

                         x-5,y+1);

        }

    }

    glPopMatrix();

}

// ================= PARKED CAR =================

void drawParkedCar(float alpha)

{

    drawCar(78,

            30,

            0.8f,

            0.2f,

            0.2f,

            alpha,

            true);

}

// ================= HUMAN =================

void drawHuman(float x,float y,float alpha)

{

    float walk=

    sin(glutGet(GLUT_ELAPSED_TIME)

    *0.01f)*1.2f;

    // Head

    glColor4f(1.0f,0.85f,0.65f,alpha);

    drawCircle(x,y+5,1);

    // Body

    glColor4f(0.2f,0.4f,0.9f,alpha);

    drawRectangle(x-0.7f,y+1,x+0.7f,y+4);

    // Arms

    drawLine(x-0.7f,y+3,x-2,y+1);

    drawLine(x+0.7f,y+3,x+2,y+1);

    // Legs

    glColor4f(0.1f,0.1f,0.1f,alpha);

    drawLine(x-0.4f,y+1,x-1,y-2+walk);

    drawLine(x+0.4f,y+1,x+1,y-2-walk);

}

// ================= BUS STOP =================

void drawBusStop(float alpha)

{

    // Roof

    glColor4f(0.2f,0.2f,0.2f,alpha);

    drawRectangle(8,35,18,37);

    // Pillars

    drawRectangle(9,28,9.5f,35);

    drawRectangle(17,28,17.5f,35);

    // Bench

    glColor4f(0.5f,0.3f,0.1f,alpha);

    drawRectangle(10,29,16,30);

    // Sign

    glColor4f(0.2f,0.5f,1.0f,alpha);

    drawRectangle(18,34,20,38);

}

// ================= BILLBOARD =================

void drawBillboard(float alpha)

{

    // Stand

    glColor4f(0.3f,0.3f,0.3f,alpha);

    drawRectangle(86,34,87,55);

    // Board

    glColor4f(0.1f,0.1f,0.1f,alpha);

    drawRectangle(78,55,96,66);

    // Ad light

    float glow=

    fabs(sin(glutGet(GLUT_ELAPSED_TIME)

    *0.002f));

    glColor4f(1.0f,glow,0.2f,alpha);

    drawRectangle(79,56,95,65);

}

// ================= TRAFFIC LIGHT =================

void drawTrafficLight(float alpha)

{

    glColor4f(0.2f,0.2f,0.2f,alpha);

    drawRectangle(55,28,56,46);

    drawRectangle(53.5f,40,57.5f,48);

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

void drawStreetLight(float x,float alpha)

{

    glColor4f(0.25f,0.25f,0.25f,alpha);

    drawRectangle(x,28,x+0.8f,44);

    drawLine(x+0.4f,44,x+3.5f,44);

    drawLine(x+3.5f,44,x+3.5f,42);

    float glow;

    if(isNight)

        glow=1.0f;

    else

        glow=0.3f;

    glColor4f(1.0f*glow,

               1.0f*glow,

               0.7f*glow,

               alpha);

    drawCircle(x+3.5f,41.5f,1.3f);

}

// ================= SMOKE =================

void drawSmoke(float alpha)

{

    for(int i=0;i<6;i++)

    {

        glColor4f(0.6f,0.6f,0.6f,

                  alpha-i*0.1f);

        drawCircle(72+smokeMove*0.2f,

                   82+i*3+smokeMove,

                   2+i*0.5f);

    }

}

// ================= MAIN CITY =================

void drawCityScene(float alpha)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA,

                GL_ONE_MINUS_SRC_ALPHA);

    // Sky

    drawCitySky(alpha);

    // Shared functions

    drawStars(alpha);

    drawSunAndMoon(alpha);

    // Clouds

    drawCloud(fmod(5+cloudMove,130)-15,

              88,

              alpha);

    drawCloud(fmod(40+cloudMove*0.7f,130)-15,

              92,

              alpha);

    // Airplane

    drawAirplane(alpha);

    // Buildings

    glPushMatrix();

    glScalef(buildingScale,

             buildingScale,

             1);

    drawModernBuilding(4,34,12,28,

                       0.72f,0.42f,0.25f,

                       alpha);

    drawModernBuilding(18,34,14,36,

                       0.55f,0.75f,0.92f,

                       alpha);

    drawModernBuilding(34,34,16,46,

                       0.72f,0.85f,0.92f,

                       alpha);

    drawModernBuilding(53,34,14,30,

                       0.25f,0.55f,0.75f,

                       alpha);

    drawModernBuilding(70,34,16,34,

                       0.72f,0.42f,0.32f,

                       alpha);

    glPopMatrix();

    // Smoke

    drawSmoke(alpha);

    // Road

    drawRoad(alpha);

    // Bus stop

    drawBusStop(alpha);

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

            alpha,

            true);

    drawCar(car2X,

            21,

            0.20f,

            0.45f,

            0.90f,

            alpha,

            false);

    glPopMatrix();

    // Parked car

    drawParkedCar(alpha);

    // Human

    drawHuman(personX,

              31,

              alpha);

    // Traffic light

    drawTrafficLight(alpha);

    // Street lights

    drawStreetLight(18,alpha);

    drawStreetLight(38,alpha);

    drawStreetLight(76,alpha);

    // Billboard

    drawBillboard(alpha);

    glDisable(GL_BLEND);

}

// ================= UPDATE =================

void updateCityAnimation()

{

    if(pauseAnimation)

    {

        return;

    }

    bool stopTraffic=

    (trafficState==0);

    if(!stopTraffic)

    {

        car1X += 0.6f * animationSpeed;

        car2X -= 0.5f * animationSpeed;

    }

    if(car1X > 110)

        car1X = -20;

    if(car2X < -20)

        car2X = 110;

    // Human

    personX += 0.12f * animationSpeed;

    if(personX > 110)

    {

        personX = -10;

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

    // Airplane

    airplaneX += 0.15f * animationSpeed;

    if(airplaneX > 130)

    {

        airplaneX = -40;

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
