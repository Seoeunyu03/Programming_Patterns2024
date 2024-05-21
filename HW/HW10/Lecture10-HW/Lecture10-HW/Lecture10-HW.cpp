#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>


const int screenWidth = 1000;
const int screenHeight = 1000;

// 공전자전
const double sunRotationPeriod = 30.0; 
const double earthRotationPeriod = 10.0; 
const double earthOrbitPeriod = 60.0;  
const double moonRotationPeriod = 3.0; 
const double moonOrbitPeriod = 3.0; 
const double PI = 3.14159; 

void sun(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * PI * i / 100;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void earth(float x1, float y1, float x2, float y2 ) {
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void star(float x, float y, float radius, int points) {
    float innerRadius = radius * 0.5f;
    float angleStep = PI / points;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < points; i++) {
        float outerAngle1 = 2 * i * angleStep;
        float outerAngle2 = 2 * (i + 1) * angleStep;
        float innerAngle = (2 * i + 1) * angleStep;

        float x1 = x + cos(outerAngle1) * radius;
        float y1 = y + sin(outerAngle1) * radius;
        float x2 = x + cos(outerAngle2) * radius;
        float y2 = y + sin(outerAngle2) * radius;
        float xInner = x + cos(innerAngle) * innerRadius;
        float yInner = y + sin(innerAngle) * innerRadius;

        glVertex2f(x, y);         // 중심점
        glVertex2f(x1, y1);       // 외각 점
        glVertex2f(xInner, yInner); // 내각 점

        glVertex2f(x, y);         // 중심점
        glVertex2f(xInner, yInner); // 내각 점
        glVertex2f(x2, y2);       // 외각 점
    }
    glEnd();
}


int main() {

    if (!glfwInit()) {
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Solar System", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 태양
        double sunAngle = (currentTime / sunRotationPeriod) * 360;
        float sunRadius = screenWidth / 6;
        glPushMatrix();
        glTranslatef(screenWidth / 2, screenHeight / 2, 0);
        glRotatef(sunAngle, 0, 0, 1);
        glColor3f(1.0f, 0.851f, 0.4f); // #FFD966 색상
        sun(0, 0, sunRadius); 
        glPopMatrix();


        // 지구
        double earthOrbitRadius = screenWidth / 3;
        double earthOrbitAngle = (currentTime / earthOrbitPeriod) * 360;
        double earthAngle = (currentTime / earthRotationPeriod) * 360;
        glPushMatrix();
        glTranslatef(screenWidth / 2, screenHeight / 2, 0);
        glRotatef(earthOrbitAngle, 0, 0, 1);
        glTranslatef(earthOrbitRadius, 0, 0);
        glRotatef(earthAngle, 0, 0, 1);
        glColor3f(0.0f, 0.0f, 1.0f);
        earth(0, 0, 40,40); 
        glPopMatrix();

        // 달
        double moonOrbitRadius = screenWidth / 15;
        double moonOrbitAngle = (currentTime / moonOrbitPeriod) * 360;
        double moonAngle = (currentTime / moonRotationPeriod) * 360;
        glPushMatrix();
        glTranslatef(screenWidth / 2, screenHeight / 2, 0);
        glRotatef(earthOrbitAngle, 0, 0, 1);
        glTranslatef(earthOrbitRadius, 0, 0);
        glRotatef(moonOrbitAngle, 0, 0, 1);
        glTranslatef(moonOrbitRadius, 0, 0);
        glRotatef(moonAngle, 0, 0, 1);
        glColor3f(1.0f, 1.0f, 0.0f);
        star(0, 0, screenWidth / 50, 5); 
        glPopMatrix();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
