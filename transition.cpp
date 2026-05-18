#include "transition.h"

#include <math.h>

// ---------------- FLAGS ----------------

bool startTransition = false;

bool pauseAnimation = false;

bool rainMode = false;

bool isNight = false;

// ---------------- SPEED ----------------

float animationSpeed = 1.0f;

float zoomScale = 1.0f;

float transitionAlpha = 0.0f;

// ---------------- TRANSFORMATION ----------------

float buildingScale = 1.0f;

float treeScale = 0.0f;

float carScale = 1.0f;

float cowScale = 0.0f;

float roadTransition = 0.0f;

float cameraOffset = 0.0f;

// ---------------- SUN ----------------

float sunX = -20.0f;

float sunY = 88.0f;

// ---------------- MOON ----------------

float moonX = -40.0f;

float moonY = 88.0f;

// ---------------- SKY ----------------

float skyRed = 0.72f;

float skyGreen = 0.86f;

float skyBlue = 0.98f;

// ---------------- UPDATE ----------------

void updateTransition()

{


    if(pauseAnimation)

    {

        return;

    }

    // =====================================

    // DAYTIME

    // =====================================

    if(!isNight)

    {

        // Slower sun movement (DOUBLE timing)

        sunX += 0.100f * animationSpeed;

        // Sun arc movement

        sunY =

        88.0f -

        sin((sunX / 100.0f) * 3.1416f)

        * 30.0f;

        // Slower evening transition

        if(sunX > 45.0f)

        {

            skyRed -= 0.00025f;

            skyGreen -= 0.00035f;

            skyBlue -= 0.00050f;

            if(skyRed < 0.08f)

            {

                skyRed = 0.08f;

            }

            if(skyGreen < 0.12f)

            {

                skyGreen = 0.12f;

            }

            if(skyBlue < 0.25f)

            {

                skyBlue = 0.25f;

            }

        }

        // Sun completely sets

        if(sunX > 105.0f)

        {

            isNight = true;

            // Moon starts from left sky

            moonX = -1.0f;

            moonY = 88.0f;

        }

    }

    // =====================================

    // NIGHTTIME

    // =====================================

    if(isNight)

    {

        // Slower moon movement (DOUBLE timing)

        moonX += 0.02f * animationSpeed;

        // Moon arc movement

        moonY =

        88.0f -

        sin((moonX / 100.0f) * 3.1416f)

        * 20.0f;

        // Night sky color

        skyRed = 0.05f;

        skyGreen = 0.08f;

        skyBlue = 0.18f;

        // Restart full cycle

        if(moonX > 120.0f)

        {

            isNight = false;

            // Reset sun

            sunX = -20.0f;

            sunY = 88.0f;

            // Reset moon

            moonX = -40.0f;

            moonY = 88.0f;

            // Reset sky

            skyRed = 0.72f;

            skyGreen = 0.86f;

            skyBlue = 0.98f;

        }

    }

    // =====================================

    // CITY → VILLAGE TRANSITION

    // =====================================

    if(startTransition)

    {

        transitionAlpha +=

        0.001f * animationSpeed;

        if(transitionAlpha > 1.0f)

        {

            transitionAlpha = 1.0f;

        }

        // Buildings disappear

        buildingScale -=

        0.001f * animationSpeed;

        if(buildingScale < 0.0f)

        {

            buildingScale = 0.0f;

        }

        // Trees appear

        treeScale +=

        0.001f * animationSpeed;

        if(treeScale > 1.0f)

        {

            treeScale = 1.0f;

        }

        // Cars disappear

        carScale -=

        0.001f * animationSpeed;

        if(carScale < 0.0f)

        {

            carScale = 0.0f;

        }

        // Cow appear

        cowScale +=

        0.001f * animationSpeed;

        if(cowScale > 1.0f)

        {

            cowScale = 1.0f;

        }

        // Road transformation

        roadTransition +=

        0.001f * animationSpeed;

        if(roadTransition > 1.0f)

        {

            roadTransition = 1.0f;

        }

        // Camera movement

        cameraOffset +=

        0.005f * animationSpeed;

        if(cameraOffset > 5.0f)

        {

            cameraOffset = 5.0f;

        }

    }

}
