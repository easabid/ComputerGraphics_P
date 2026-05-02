#include <GL/glut.h>
#include <cmath>
#include <iostream>

int windowWidth = 1200;
int windowHeight = 800;

void setColor(float r, float g, float b, float a = 1.0f) {
    glColor4f(r, g, b, a);
}

void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawCircle(float x, float y, float radius, int segments = 40) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * 3.1415926f * i / segments;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// FEATURE 1: City sky background
void drawCitySky() {
    setColor(0.50f, 0.80f, 1.00f);
    drawRectangle(0.0f, 400.0f, 1200.0f, 400.0f);
}

// FEATURE 2: Sun in city
void drawCitySun() {
    setColor(1.0f, 0.9f, 0.0f);
    drawCircle(1080.0f, 700.0f, 45.0f);
}

// FEATURE 3: Tall buildings
void drawTallBuildings() {
    setColor(0.45f, 0.45f, 0.50f);
    drawRectangle(60.0f, 400.0f, 90.0f, 220.0f);

    setColor(0.50f, 0.50f, 0.55f);
    drawRectangle(180.0f, 400.0f, 100.0f, 270.0f);

    setColor(0.42f, 0.42f, 0.48f);
    drawRectangle(320.0f, 400.0f, 110.0f, 240.0f);

    setColor(0.52f, 0.52f, 0.58f);
    drawRectangle(470.0f, 400.0f, 95.0f, 290.0f);

    setColor(0.47f, 0.47f, 0.53f);
    drawRectangle(600.0f, 400.0f, 105.0f, 250.0f);
}

// FEATURE 4: Building windows
void drawBuildingWindows() {
    setColor(1.0f, 1.0f, 0.4f);

    for (float y = 430.0f; y <= 590.0f; y += 35.0f) {
        for (float x = 75.0f; x <= 125.0f; x += 20.0f) {
            drawRectangle(x, y, 10.0f, 15.0f);
        }
    }

    for (float y = 430.0f; y <= 640.0f; y += 35.0f) {
        for (float x = 200.0f; x <= 250.0f; x += 20.0f) {
            drawRectangle(x, y, 10.0f, 15.0f);
        }
    }

    for (float y = 430.0f; y <= 610.0f; y += 35.0f) {
        for (float x = 340.0f; x <= 390.0f; x += 20.0f) {
            drawRectangle(x, y, 10.0f, 15.0f);
        }
    }

    for (float y = 430.0f; y <= 660.0f; y += 35.0f) {
        for (float x = 490.0f; x <= 540.0f; x += 20.0f) {
            drawRectangle(x, y, 10.0f, 15.0f);
        }
    }

    for (float y = 430.0f; y <= 620.0f; y += 35.0f) {
        for (float x = 620.0f; x <= 670.0f; x += 20.0f) {
            drawRectangle(x, y, 10.0f, 15.0f);
        }
    }
}

void drawCityScene() {
    drawCitySky();
    drawCitySun();
    drawTallBuildings();
    drawBuildingWindows();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Ground placeholder
    setColor(0.20f, 0.60f, 0.20f);
    drawRectangle(0.0f, 0.0f, 1200.0f, 400.0f);

    // Current implemented scene
    drawCityScene();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("City to Village Transition - Basic 2D");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    std::cout << "ESC to exit" << std::endl;

    glutMainLoop();
    return 0;
}
