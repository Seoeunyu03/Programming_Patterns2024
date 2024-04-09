#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactorX = 0.0f;
float moveFactorY = 0.0f;
float scaleFactor = 1.0f;
double lastX = 0.0, lastY = 0.0;
bool isRightMouseDown = false;
bool isLeftMouseDown = false;
const float minScaleFactor = 0.1f; // 최소 축소 비율 설정

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        isRightMouseDown = true;
        glfwGetCursorPos(window, &lastX, &lastY);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        isRightMouseDown = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        isLeftMouseDown = true;
        glfwGetCursorPos(window, &lastX, &lastY);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        isLeftMouseDown = false;
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (isRightMouseDown)
    {
        double deltaX = xpos - lastX;
        double deltaY = ypos - lastY;

        float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        
        if (scaleFactor * distance > minScaleFactor) { // 일정 크기 이상일 때만 확대/축소
            if (deltaX > 0)
            {
                // 오른쪽으로 드래그할 때 확대
                scaleFactor += 0.01f * distance;
            }
            else if (deltaX < 0)
            {
                // 왼쪽으로 드래그할 때 축소
                scaleFactor -= 0.01f * distance;
                if (scaleFactor < minScaleFactor) scaleFactor = minScaleFactor; // 최소 축소 비율 제한
            }
        }

        lastX = xpos;
        lastY = ypos;
    }
    else if (isLeftMouseDown)
    {
        double deltaX = xpos - lastX;
        double deltaY = ypos - lastY;

        moveFactorX += static_cast<float>(deltaX) / 1280.0f;
        moveFactorY -= static_cast<float>(deltaY) / 768.0f; // Reverse Y-axis for OpenGL coordinates

        lastX = xpos;
        lastY = ypos;
    }
}

int render()
{
    glBegin(GL_TRIANGLES);

    // 첫 번째 삼각형 (위쪽 삼각형)
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((-0.5f + moveFactorX) * scaleFactor, (0.5f + moveFactorY) * scaleFactor);
    glVertex2f((0.5f + moveFactorX) * scaleFactor, (0.5f + moveFactorY) * scaleFactor);
    glVertex2f((moveFactorX)*scaleFactor, (-0.8f + moveFactorY) * scaleFactor);

    // 두 번째 삼각형 (아래쪽 삼각형)
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f((-0.5f + moveFactorX) * scaleFactor, (-0.5f + moveFactorY) * scaleFactor);
    glVertex2f((0.5f + moveFactorX) * scaleFactor, (-0.5f + moveFactorY) * scaleFactor);
    glVertex2f((moveFactorX)*scaleFactor, (0.8f + moveFactorY) * scaleFactor);

    glEnd();

    return 0;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}