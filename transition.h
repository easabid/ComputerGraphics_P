#ifndef TRANSITION_H

#define TRANSITION_H

// ---------------- FLAGS ----------------

extern bool startTransition;

extern bool pauseAnimation;

extern bool rainMode;

extern bool isNight;

// ---------------- SPEED ----------------

extern float animationSpeed;

extern float zoomScale;

extern float transitionAlpha;

// ---------------- TRANSFORMATION ----------------

extern float buildingScale;

extern float treeScale;

extern float carScale;

extern float cowScale;

extern float roadTransition;

extern float cameraOffset;

// ---------------- SUN & MOON ----------------

extern float sunX;

extern float sunY;

extern float moonX;

extern float moonY;

// ---------------- SKY ----------------

extern float skyRed;

extern float skyGreen;

extern float skyBlue;

// ---------------- FUNCTION ----------------

void updateTransition();

#endif
