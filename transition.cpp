#include "transition.h"

#include "utils.h"

#include <math.h>

// ================= FLAGS =================

bool startTransition = false;

bool pauseAnimation = false;

bool rainMode = false;

bool isNight = false;

// ================= SPEED =================

float animationSpeed = 1.0f;

float zoomScale = 1.0f;

float transitionAlpha = 0.0f;

// ================= TRANSFORMATION =================

float buildingScale = 1.0f;

float treeScale = 0.0f;

float carScale = 1.0f;

float cowScale = 0.0f;

float roadTransition = 0.0f;

float cameraOffset = 0.0f;

// ================= LAYER FLAGS =================

bool showCityScene = true;

bool showVillageScene = true;

bool showBuildings = true;

bool showTrees = true;

// ================= SUN =================

float sunX = -20.0f;

float sunY = 88.0f;

// ================= MOON =================

float moonX = -40.0f;

float moonY = 88.0f;

// ================= SKY =================

float skyRed = 0.72f;


        // advance transition alpha (drives all synced transforms)
        transitionAlpha += 0.0015f * animationSpeed;
        if(transitionAlpha > 1.0f)
            transitionAlpha = 1.0f;

        // derive transforms directly from transitionAlpha for precise synchronization
        buildingScale = 1.0f - transitionAlpha;
        if(buildingScale < 0.0f) buildingScale = 0.0f;

        treeScale = transitionAlpha;
        if(treeScale > 1.0f) treeScale = 1.0f;

        carScale = 1.0f - transitionAlpha;
        if(carScale < 0.0f) carScale = 0.0f;

        cowScale = transitionAlpha;
        if(cowScale > 1.0f) cowScale = 1.0f;

        roadTransition = transitionAlpha;
        if(roadTransition > 1.0f) roadTransition = 1.0f;

        cameraOffset = transitionAlpha * 5.0f;
        if(cameraOffset > 5.0f) cameraOffset = 5.0f;
                   moonY,

                   4);

        // Moon shade

        glColor4f(0.08f,

                  0.10f,

                  0.20f,

                  alpha);

        drawCircle(moonX+1.5f,

                   moonY+0.5f,

                   3.5f);

    }

}

// ================= STARS =================

void drawStars(float alpha)

{

    if(!isNight)

    {

        return;

    }

    glColor4f(1,

              1,

              1,

              alpha);

    drawCircle(10,90,0.2f);

    drawCircle(20,85,0.2f);

    drawCircle(35,95,0.2f);

    drawCircle(50,88,0.2f);

    drawCircle(65,92,0.2f);

    drawCircle(80,86,0.2f);

    drawCircle(92,94,0.2f);

    drawCircle(75,97,0.2f);

    drawCircle(55,96,0.2f);

}

// ================= UPDATE =================

void updateTransition()

{

    if(pauseAnimation)

    {

        return;

    }

    // ================= DAY =================

    if(!isNight)

    {

        // Sun movement

        sunX += 0.100f * animationSpeed;

        // Arc movement

        sunY =

        88.0f -

        sin((sunX / 100.0f)

        * 3.1416f)

        * 30.0f;

        // Evening sky

        if(sunX > 45.0f)

        {

            skyRed -= 0.00025f;

            skyGreen -= 0.00035f;

            skyBlue -= 0.00050f;

            if(skyRed < 0.08f)

                skyRed = 0.08f;

            if(skyGreen < 0.12f)

                skyGreen = 0.12f;

            if(skyBlue < 0.25f)

                skyBlue = 0.25f;

        }

        // Switch to night

        if(sunX > 105.0f)

        {

            isNight = true;

            moonX = -1.0f;

            moonY = 88.0f;

        }

    }

    // ================= NIGHT =================

    if(isNight)

    {

        // Moon movement

        moonX += 0.02f * animationSpeed;

        // Arc

        moonY =

        88.0f -

        sin((moonX / 100.0f)

        * 3.1416f)

        * 20.0f;

        // Night sky

        skyRed = 0.05f;

        skyGreen = 0.08f;

        skyBlue = 0.18f;

        // Restart cycle

        if(moonX > 120.0f)

        {

            isNight = false;

            sunX = -20.0f;

            sunY = 88.0f;

            moonX = -40.0f;

            moonY = 88.0f;

            skyRed = 0.72f;

            skyGreen = 0.86f;

            skyBlue = 0.98f;

        }

    }

    // ================= TRANSITION =================

    if(startTransition)

    {

        transitionAlpha +=

        0.001f * animationSpeed;

        if(transitionAlpha > 1.0f)

        {

            transitionAlpha = 1.0f;

        }

        buildingScale -=

        0.001f * animationSpeed;

        if(buildingScale < 0.0f)

        {

            buildingScale = 0.0f;

        }

        treeScale +=

        0.001f * animationSpeed;

        if(treeScale > 1.0f)

        {

            treeScale = 1.0f;

        }

        carScale -=

        0.001f * animationSpeed;

        if(carScale < 0.0f)

        {

            carScale = 0.0f;

        }

        cowScale +=

        0.001f * animationSpeed;

        if(cowScale > 1.0f)

        {

            cowScale = 1.0f;

        }

        roadTransition +=

        0.001f * animationSpeed;

        if(roadTransition > 1.0f)

        {

            roadTransition = 1.0f;

        }

        cameraOffset +=

        0.005f * animationSpeed;

        if(cameraOffset > 5.0f)

        {

            cameraOffset = 5.0f;

        }

    }

}
