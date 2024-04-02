#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

// 전역 변수로 현재 색을 저장
float currentColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // 초기 검정색 설정
bool rightMouseDown = false;
bool leftMouseDown = false;
bool dragging = false;


// GLFW에서 발생한 오류를 처리하는 역할
void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}


// esc 누르면 윈도우 창이 닫힌다.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// 마우스 이벤트 콜백
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // 오른쪽 마우스 
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            rightMouseDown = true;
            // 오른쪽 버튼이 눌렸을 때 즉시 빨간색
            currentColor[0] = 1.0f;
            currentColor[1] = 0.0f;
            currentColor[2] = 0.0f;
            dragging = false;
        }
        else if (action == GLFW_RELEASE)
        {
            rightMouseDown = false;
            // 오른쪽 버튼을 떼면 검정색
            currentColor[0] = 0.0f;
            currentColor[1] = 0.0f;
            currentColor[2] = 0.0f;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftMouseDown = true;
            // 왼쪽 버튼이 눌렸을 때 즉시 녹색
            currentColor[0] = 0.0f;
            currentColor[1] = 1.0f;
            currentColor[2] = 0.0f;
            dragging = false;
        }
        else if (action == GLFW_RELEASE)
        {
            leftMouseDown = false;
            // 왼쪽 버튼을 떼면 검정색
            currentColor[0] = 0.0f;
            currentColor[1] = 0.0f;
            currentColor[2] = 0.0f;
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (rightMouseDown)
    {
        // 오른쪽 버튼을 누른 상태에서 드래그 중이면 파란색
        currentColor[0] = 0.0f;
        currentColor[1] = 0.0f;
        currentColor[2] = 1.0f;
        dragging = true;
    }
    else if (leftMouseDown)
    {
        // 왼쪽 버튼을 누른 상태에서 드래그 중이면 마젠타색
        currentColor[0] = 1.0f;
        currentColor[1] = 0.0f;
        currentColor[2] = 1.0f;
        dragging = true;
    }
    else
    {
        dragging = false;
    }
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
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}