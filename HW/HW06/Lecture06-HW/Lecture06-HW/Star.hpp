#pragma once
#include <GLFW/glfw3.h>
#include <cstdlib>  // rand() 및 srand()를 위한 헤더
#include <ctime>    // time()을 위한 헤더

class Star {
public:
    float x, y, size;  // 별의 위치(x, y) 및 크기(size)
    float r, g, b;  // 별의 RGB 색상

    Star() {
        // 별의 위치와 색상을 랜덤으로 초기화
        x = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;  // -1에서 1 사이
        y = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;  // -1에서 1 사이
        size = 0.02f;  // 별의 크기
        r = static_cast<float>(rand()) / RAND_MAX;
        g = static_cast<float>(rand()) / RAND_MAX;
        b = static_cast<float>(rand()) / RAND_MAX;
    }

    void draw() {
        glColor3f(r, g, b);  // 별의 색상 설정
        glBegin(GL_TRIANGLE_FAN);  // 별을 그리기 시작
        glVertex2f(x, y);  // 별의 중심 위치
        // 10개의 점을 이용해 별 모양을 그림
        for (int i = 0; i <= 10; i++) {
            float angle = 2.0f * 3.14159265f * i / 10;  // 각도 계산
            float dx = (i % 2 == 0) ? size : size / 2;  // 별의 꼭짓점과 내접점 크기
            glVertex2f(x + cos(angle) * dx, y + sin(angle) * dx);  // 별의 점 위치 계산
        }
        glEnd();  // 별 그리기 종료
    }
};