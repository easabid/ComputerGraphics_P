#include <GL/glut.h>
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

// FEATURE 1: City sky background
void drawCitySky() {
    setColor(0.50f, 0.80f, 1.00f);
    drawRectangle(0.0f, 400.0f, 1200.0f, 400.0f);
}

void drawCityScene() {
    drawCitySky();
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
