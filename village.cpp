#include "village.h"

#include "utils.h"

#include "transition.h"

#include <math.h>

// ================= GLOBAL VARIABLES =================

float boatX = -20.0f;

float birdX = -10.0f;

float waterFlow = 0.0f;

float treeSwing = 0.0f;

// ================= HILL =================

void drawHill(float x,

              float y,

              float radius,

              float alpha)

{

    glColor4f(0.35f,

              0.65f,

              0.35f,

              alpha);

    drawCircle(x,

               y,

               radius);

}

// ================= TREE =================

void drawTree(float x,

              float y,

              float alpha)

{

    float sway =

    sin(treeSwing + x) * 0.8f;

    // Trunk

    glColor4f(0.45f,

              0.25f,

              0.10f,

              alpha);

    drawRectangle(x,

                  y,

                  x+2,

                  y+12);

    // Leaves

    glColor4f(0.10f,

              0.60f,

              0.15f,

              alpha);

    drawCircle(x+1+sway,

               y+17,

               5);

    drawCircle(x-2+sway,

               y+14,

               4);

    drawCircle(x+4+sway,

               y+14,

               4);

}

// ================= BUSH =================

void drawBush(float x,

              float y,

              float alpha)

{

    glColor4f(0.12f,

              0.55f,

              0.15f,

              alpha);

    drawCircle(x,

               y,

               2);

    drawCircle(x+2,

               y+1,

               2.5f);

    drawCircle(x+4,

               y,

               2);

}

// ================= FLOWER =================

void drawFlower(float x,

                float y,

                float alpha)

{

    glColor4f(1.0f,

              0.3f,

              0.5f,

              alpha);

    drawCircle(x,y,0.5f);

    glColor4f(1.0f,

              1.0f,

              0.0f,

              alpha);

    drawCircle(x,y,0.2f);

}

// ================= HOUSE =================

void drawVillageHouse(float x,

                      float y,

                      float alpha)

{

    // Body

    glColor4f(0.92f,

              0.78f,

              0.48f,

              alpha);

    drawRectangle(x,

                  y,

                  x+12,

                  y+10);

    // Roof

    glColor4f(0.65f,

              0.15f,

              0.15f,

              alpha);

    drawTriangle(x-1,

                 y+10,

                 x+13,

                 y+10,

                 x+6,

                 y+16);

    // Door

    glColor4f(0.35f,

              0.20f,

              0.10f,

              alpha);

    drawRectangle(x+4,

                  y,

                  x+7,

                  y+5);

    // Windows

    glColor4f(0.75f,

              0.90f,

              1.0f,

              alpha);

    drawRectangle(x+1.5f,

                  y+5,

                  x+3.5f,

                  y+7);

    drawRectangle(x+8,

                  y+5,

                  x+10,

                  y+7);

}

// ================= RIVER =================

void drawRiver(float alpha)

{

    glColor4f(0.20f,

              0.55f,

              0.95f,

              alpha);

    glBegin(GL_POLYGON);

        glVertex2f(0,15);

        glVertex2f(100,10);

        glVertex2f(100,0);

        glVertex2f(0,0);

    glEnd();

    // Water flow lines

    glColor4f(1.0f,

              1.0f,

              1.0f,

              alpha*0.4f);

    for(float i=0;i<120;i+=10)

    {

        drawLine(fmod(i+waterFlow,120)-20,

                 8,

                 fmod(i+waterFlow,120)-10,

                 8);

    }

}

// ================= RIVER BANK =================

void drawRiverBank(float alpha)

{

    glColor4f(0.72f,

              0.62f,

              0.38f,

              alpha);

    drawRectangle(0,

                  14,

                  100,

                  17);

}

// ================= BOAT =================

void drawBoat(float x,

              float y,

              float alpha)

{

    // Boat body

    glColor4f(0.45f,

              0.20f,

              0.05f,

              alpha);

    glBegin(GL_POLYGON);

        glVertex2f(x,y);

        glVertex2f(x+12,y);

        glVertex2f(x+10,y-3);

        glVertex2f(x+2,y-3);

    glEnd();

    // Boat person

    // Head

    glColor4f(1.0f,

              0.85f,

              0.65f,

              alpha);

    drawCircle(x+5,

               y+3,

               0.8f);

    // Body

    glColor4f(0.2f,

              0.2f,

              0.8f,

              alpha);

    drawRectangle(x+4.5f,

                  y+0.5f,

                  x+5.5f,

                  y+2.5f);

    // Paddle

    glColor4f(0.35f,

              0.20f,

              0.10f,

              alpha);

    drawLine(x+7,

             y+2,

             x+10,

             y-2);

}

// ================= FARMER =================

void drawFarmer(float x,

                float y,

                float alpha)

{

    // Head

    glColor4f(1.0f,

              0.85f,

              0.65f,

              alpha);

    drawCircle(x,

               y+6,

               1.4f);

    // Hat

    glColor4f(0.8f,

              0.6f,

              0.2f,

              alpha);

    drawRectangle(x-2,

                  y+7,

                  x+2,

                  y+7.5f);

    // Body

    glColor4f(0.1f,

              0.3f,

              0.8f,

              alpha);

    drawRectangle(x-1,

                  y+1,

                  x+1,

                  y+5);

    // Arms

    drawLine(x-1,

             y+4,

             x-3,

             y+2);

    drawLine(x+1,

             y+4,

             x+3,

             y+2);

    // Legs

    glColor4f(0.1f,

              0.1f,

              0.1f,

              alpha);

    drawLine(x-0.5f,

             y+1,

             x-1,

             y-2);

    drawLine(x+0.5f,

             y+1,

             x+1,

             y-2);

}

// ================= COW =================

void drawCow(float x,

             float y,

             float alpha)

{

    // Body

    glColor4f(1,

              1,

              1,

              alpha);

    drawRectangle(x,

                  y,

                  x+8,

                  y+4);

    // Spots

    glColor4f(0.1f,

              0.1f,

              0.1f,

              alpha);

    drawCircle(x+2,

               y+2,

               0.8f);

    drawCircle(x+5,

               y+1,

               0.6f);

    // Head

    glColor4f(1,

              1,

              1,

              alpha);

    drawRectangle(x+8,

                  y+2,

                  x+10,

                  y+5);

    // Legs

    glColor4f(0.1f,

              0.1f,

              0.1f,

              alpha);

    drawLine(x+1,y,x+1,y-3);

    drawLine(x+3,y,x+3,y-3);

    drawLine(x+5,y,x+5,y-3);

    drawLine(x+7,y,x+7,y-3);

    // Tail

    drawLine(x,

             y+3,

             x-2,

             y+5);

}

// ================= GOAT =================

void drawGoat(float x,

              float y,

              float alpha)

{

    glColor4f(0.85f,

              0.85f,

              0.85f,

              alpha);

    drawRectangle(x,

                  y,

                  x+5,

                  y+3);

    drawRectangle(x+5,

                  y+1,

                  x+7,

                  y+4);

}

// ================= BIRD =================

void drawBird(float x,

              float y,

              float alpha)

{

    glColor4f(0,

              0,

              0,

              alpha);

    glBegin(GL_LINE_STRIP);

        glVertex2f(x,y);

        glVertex2f(x+1,y+1);

        glVertex2f(x+2,y+1.5f);

        glVertex2f(x+3,y+1);

        glVertex2f(x+4,y);

    glEnd();

}

// ================= FENCE =================

void drawFence(float alpha)

{

    glColor4f(0.55f,

              0.30f,

              0.10f,

              alpha);

    for(float i=0;i<100;i+=4)

    {

        drawRectangle(i,

                      26,

                      i+0.5f,

                      30);

        drawLine(i,

                 29,

                 i+4,

                 29);

    }

}

// ================= WELL =================

void drawWell(float x,

              float y,

              float alpha)

{

    glColor4f(0.55f,

              0.55f,

              0.55f,

              alpha);

    drawCircle(x,

               y,

               3);

    drawRectangle(x-3,

                  y,

                  x+3,

                  y+4);

}

// ================= MAIN SCENE =================

void drawVillageScene(float alpha)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA,

                GL_ONE_MINUS_SRC_ALPHA);

    // Hills

    drawHill(15,45,20,alpha);

    drawHill(40,48,24,alpha);

    drawHill(70,45,22,alpha);

    // Green field

    glColor4f(0.25f,

              0.75f,

              0.25f,

              alpha);

    drawRectangle(0,

                  15,

                  100,

                  35);

    // Mud road

    glColor4f(0.45f,

              0.30f,

              0.15f,

              alpha);

    drawRectangle(0,

                  20,

                  100,

                  25);

    // River

    drawRiver(alpha);

    // River bank

    drawRiverBank(alpha);

    // Fence

    drawFence(alpha);

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

    // Bushes

    drawBush(12,30,alpha);

    drawBush(60,30,alpha);

    drawBush(82,29,alpha);

    // Flowers

    drawFlower(18,28,alpha);

    drawFlower(24,27,alpha);

    drawFlower(66,28,alpha);

    drawFlower(70,29,alpha);

    // Houses

    drawVillageHouse(30,32,alpha);

    drawVillageHouse(62,32,alpha);

    // Well

    drawWell(52,28,alpha);

    // Boat

    drawBoat(boatX,

             10,

             alpha);

    // Birds

    float birdY1 =

    82 + sin(birdX*0.08f)*2.5f;

    float birdY2 =

    86 + sin((birdX+15)*0.08f)*2.0f;

    float birdY3 =

    80 + sin((birdX+30)*0.08f)*2.8f;

    drawBird(birdX,birdY1,alpha);

    drawBird(birdX+8,birdY2,alpha);

    drawBird(birdX+16,birdY3,alpha);

    // Farmer

    drawFarmer(45,

               32,

               alpha);

    // Cow

    glPushMatrix();

    glScalef(cowScale,

             cowScale,

             1);

    drawCow(72,

            28,

            alpha);

    glPopMatrix();

    // Goat

    drawGoat(62,

             27,

             alpha);

    glDisable(GL_BLEND);

}

// ================= UPDATE =================

void updateVillageAnimation()

{

    if(pauseAnimation)

    {

        return;

    }

    // Boat movement

    boatX += 0.15f * animationSpeed;

    if(boatX > 110)

    {

        boatX = -20;

    }

    // Bird movement

    birdX += 0.35f * animationSpeed;

    if(birdX > 120)

    {

        birdX = -20;

    }

    // Water flow

    waterFlow += 0.4f * animationSpeed;

    if(waterFlow > 120)

    {

        waterFlow = 0;

    }

    // Tree wind swing

    treeSwing += 0.03f * animationSpeed;

}
