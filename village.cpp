#include "village.h"

#include "utils.h"

#include "transition.h"

#include <math.h>

// ================= GLOBAL VARIABLES =================

float boatX = -20.0f;

float birdX = -10.0f;

float waterFlow = 0.0f;

float treeSwing = 0.0f;

float goatWalk = 0.0f;

float fireflyMove = 0.0f;

// ================= SKY =================

void drawVillageSky(float alpha)

{

    glBegin(GL_QUADS);

    if(isNight)

        glColor4f(0.05f,0.08f,0.18f,alpha);

    else

        glColor4f(0.45f,0.75f,0.95f,alpha);

    glVertex2f(0,100);

    glVertex2f(100,100);

    if(isNight)

        glColor4f(0.10f,0.12f,0.22f,alpha);

    else

        glColor4f(0.85f,0.90f,0.70f,alpha);

    glVertex2f(100,40);

    glVertex2f(0,40);

    glEnd();

}

// ================= HILLS =================

void drawHill(float x,

              float y,

              float radius,

              float r,

              float g,

              float b,

              float alpha)

{

    glColor4f(r,g,b,alpha);

    drawCircle(x,y,radius);

}

// ================= TREE =================

void drawTree(float x,float y,float alpha)

{

    float sway =

    sin(treeSwing + x)

    * 1.2f;

    // Shadow

    glColor4f(0,0,0,0.10f);

    drawCircle(x+2,y,4);

    // Trunk

    glColor4f(0.45f,0.25f,0.10f,alpha);

    drawRectangle(x,y,x+2,y+14);

    // Branches

    drawLine(x+1,y+10,x-2+sway,y+16);

    drawLine(x+1,y+11,x+4+sway,y+17);

    // Leaves

    glColor4f(0.10f,0.60f,0.15f,alpha);

    drawCircle(x+1+sway,y+20,5);

    drawCircle(x-2+sway,y+17,4);

    drawCircle(x+4+sway,y+17,4);

    drawCircle(x+1+sway,y+15,4);

}

// ================= GRASS =================

void drawGrass(float alpha)

{

    glColor4f(0.20f,0.70f,0.20f,alpha);

    for(float i=0;i<100;i+=2)

    {

        float sway =

        sin(treeSwing + i)

        * 0.8f;

        drawLine(i,15,i+sway,17);

    }

}

// ================= CROP FIELD =================

void drawCropField(float alpha)

{

    glColor4f(0.45f,0.30f,0.12f,alpha);

    drawRectangle(5,18,28,28);

    glColor4f(0.85f,0.75f,0.20f,alpha);

    for(float i=7;i<27;i+=2)

    {

        drawLine(i,18,i,28);

    }

}

// ================= FLOWER FIELD =================

void drawFlowerField(float alpha)

{

    for(float i=60;i<95;i+=3)

    {

        for(float j=18;j<30;j+=3)

        {

            glColor4f(0.1f,0.6f,0.1f,alpha);

            drawLine(i,j,i,j+1);

            int type=((int)(i+j))%3;

            if(type==0)

                glColor4f(1,0.3f,0.5f,alpha);

            else if(type==1)

                glColor4f(1,1,0.2f,alpha);

            else

                glColor4f(0.8f,0.3f,1,alpha);

            drawCircle(i,j+1.2f,0.35f);

        }

    }

}

// ================= HOUSE =================

void drawVillageHouse(float x,float y,float alpha)

{

    // Body

    glColor4f(0.88f,0.72f,0.45f,alpha);

    drawRectangle(x,y,x+12,y+10);

    // Roof

    glColor4f(0.55f,0.25f,0.05f,alpha);

    drawTriangle(x-1,y+10,x+13,y+10,x+6,y+16);

    // Door

    glColor4f(0.35f,0.20f,0.10f,alpha);

    drawRectangle(x+4,y,x+7,y+5);

    // Windows

    if(isNight)

        glColor4f(1.0f,0.95f,0.55f,alpha);

    else

        glColor4f(0.75f,0.90f,1.0f,alpha);

    drawRectangle(x+1.5f,y+5,x+3.5f,y+7);

    drawRectangle(x+8,y+5,x+10,y+7);

}

// ================= TEMPLE =================

void drawTemple(float alpha)

{

    glColor4f(0.85f,0.75f,0.55f,alpha);

    drawRectangle(82,30,92,40);

    glColor4f(0.65f,0.25f,0.10f,alpha);

    drawTriangle(80,40,94,40,87,50);

    glColor4f(1.0f,0.8f,0.2f,alpha);

    drawLine(87,50,87,55);

}

// ================= RIVER =================

void drawRiver(float alpha)

{

    glColor4f(0.20f,0.55f,0.95f,alpha);

    glBegin(GL_POLYGON);

        glVertex2f(0,15);

        glVertex2f(100,10);

        glVertex2f(100,0);

        glVertex2f(0,0);

    glEnd();

    // Waves

    glColor4f(1.0f,1.0f,1.0f,alpha * 0.35f);

    for(float i=0;i<120;i+=8)

    {

        float wave =

        sin((i + waterFlow) * 0.1f);

        drawLine(fmod(i+waterFlow,120)-20,

                 8+wave,

                 fmod(i+waterFlow,120)-12,

                 8+wave);

    }

    // Moon reflection

    if(isNight)

    {

        glColor4f(1.0f,1.0f,1.0f,0.12f);

        drawRectangle(moonX-3,

                      5,

                      moonX+3,

                      15);

    }

}

// ================= BRIDGE =================

void drawBridge(float alpha)

{

    glColor4f(0.45f,0.25f,0.10f,alpha);

    drawRectangle(35,13,55,15);

}

// ================= WATERMILL =================

void drawWatermill(float alpha)

{

    glPushMatrix();

    glTranslatef(20,17,0);

    glColor4f(0.40f,0.20f,0.05f,alpha);

    drawRectangle(-1,0,1,12);

    glRotatef(glutGet(GLUT_ELAPSED_TIME)*0.05f,

              0,0,1);

    glColor4f(0.55f,0.35f,0.15f,alpha);

    drawCircle(0,0,4);

    for(int i=0;i<360;i+=45)

    {

        float angle =

        i * 3.1416f / 180.0f;

        drawLine(0,0,

                 cos(angle)*4,

                 sin(angle)*4);

    }

    glPopMatrix();

}

// ================= BOAT =================

void drawBoat(float x,float y,float alpha)

{

    float floatY =

    sin(glutGet(GLUT_ELAPSED_TIME)

    * 0.005f) * 1.0f;

    glPushMatrix();

    glTranslatef(0,floatY,0);

    glColor4f(0.45f,0.20f,0.05f,alpha);

    glBegin(GL_POLYGON);

        glVertex2f(x,y);

        glVertex2f(x+12,y);

        glVertex2f(x+10,y-3);

        glVertex2f(x+2,y-3);

    glEnd();

    // Person

    glColor4f(1.0f,0.85f,0.65f,alpha);

    drawCircle(x+5,y+3,0.8f);

    glColor4f(0.2f,0.2f,0.8f,alpha);

    drawRectangle(x+4.5f,y+0.5f,

                  x+5.5f,y+2.5f);

    glPopMatrix();

}

// ================= FARMER =================

void drawFarmer(float x,float y,float alpha)

{

    glColor4f(1.0f,0.85f,0.65f,alpha);

    drawCircle(x,y+6,1.4f);

    glColor4f(0.1f,0.3f,0.8f,alpha);

    drawRectangle(x-1,y+1,x+1,y+5);

}

// ================= COW =================

void drawCow(float x,float y,float alpha)

{

    glColor4f(1,1,1,alpha);

    drawRectangle(x,y,x+8,y+4);

    drawRectangle(x+8,y+2,x+10,y+5);

}

// ================= GOAT =================

void drawGoat(float x,float y,float alpha)

{

    float walk =

    sin(goatWalk) * 0.5f;

    glColor4f(0.85f,0.85f,0.85f,alpha);

    drawRectangle(x+walk,y,

                  x+5+walk,y+3);

    drawRectangle(x+5+walk,y+1,

                  x+7+walk,y+4);

}

// ================= BIRD =================

void drawBird(float x,float y,float alpha)

{

    float wing =

    sin(glutGet(GLUT_ELAPSED_TIME)

    * 0.02f) * 2.0f;

    glColor4f(0,0,0,alpha);

    glBegin(GL_LINES);

        glVertex2f(x,y);

        glVertex2f(x+2,y+wing);

        glVertex2f(x+2,y+wing);

        glVertex2f(x+4,y);

    glEnd();

}

// ================= MAIN SCENE =================

void drawVillageScene(float alpha)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA,

                GL_ONE_MINUS_SRC_ALPHA);

    drawVillageSky(alpha);

    // IMPORTANT:

    // Shared functions from transition.cpp

    drawStars(alpha);

    drawSunAndMoon(alpha);

    // Hills

    drawHill(10,50,22,

             0.25f,0.45f,0.25f,

             alpha);

    drawHill(35,52,26,

             0.30f,0.50f,0.30f,

             alpha);

    drawHill(65,50,24,

             0.25f,0.45f,0.25f,

             alpha);

    // Field

    glColor4f(0.25f,0.75f,0.25f,alpha);

    drawRectangle(0,15,100,35);

    drawCropField(alpha);

    drawFlowerField(alpha);

    drawGrass(alpha);

    drawRiver(alpha);

    drawBridge(alpha);

    drawWatermill(alpha);

    drawTemple(alpha);

    // Trees

    // Trees (can be toggled)
    if(showTrees)
    {
        glPushMatrix();
        glScalef(treeScale,
                 treeScale,
                 1);
        drawTree(8,32,alpha);
        drawTree(22,32,alpha);
        drawTree(55,32,alpha);
        drawTree(80,32,alpha);
        glPopMatrix();
    }

    // Houses

    drawVillageHouse(30,32,alpha);

    drawVillageHouse(62,32,alpha);

    // Boat

    drawBoat(boatX,10,alpha);

    // Birds

    float birdY1 =

    82 + sin(birdX*0.08f)*2.5f;

    float birdY2 =

    86 + sin((birdX+15)*0.08f)*2.0f;

    drawBird(birdX,birdY1,alpha);

    drawBird(birdX+8,birdY2,alpha);

    // Farmer

    drawFarmer(45,32,alpha);

    // Cow

    glPushMatrix();

    glScalef(cowScale,

             cowScale,

             1);

    drawCow(72,28,alpha);

    glPopMatrix();

    // Goat

    drawGoat(62,27,alpha);

    glDisable(GL_BLEND);

}

// ================= UPDATE =================

void updateVillageAnimation()

{

    if(pauseAnimation)

        return;

    // Boat

    boatX += 0.15f * animationSpeed;

    if(boatX > 110)

        boatX = -20;

    // Birds

    birdX += 0.35f * animationSpeed;

    if(birdX > 120)

        birdX = -20;

    // Water

    waterFlow += 0.4f * animationSpeed;

    if(waterFlow > 120)

        waterFlow = 0;

    // Tree wind

    treeSwing += 0.03f * animationSpeed;

    // Goat movement

    goatWalk += 0.08f * animationSpeed;

    // Fireflies

    fireflyMove += 0.02f * animationSpeed;

}
