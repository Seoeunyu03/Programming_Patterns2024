#pragma comment(lib, "Opengl32.lib")
#include <iostream>
#include <GLFW/glfw3.h>
#include "MSList.h"
#include "star.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));  // 랜덤 시드 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Random Stars", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "GLFW 윈도우 생성 실패" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    MSList<Star> stars;  // 별들을 관리할 리스트 생성
    for (int i = 0; i < 300; i++) {
        stars.push_back(Star());  // 리스트에 별 추가
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // 화면 클리어

        for (Node<Star>* node = stars.begin(); node != stars.end(); node = node->next) {
            node->data.draw();  // 별 그리기
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}