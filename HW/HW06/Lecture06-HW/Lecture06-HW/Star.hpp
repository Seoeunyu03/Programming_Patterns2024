#pragma once
#include <GLFW/glfw3.h>
#include <cstdlib>  // rand() �� srand()�� ���� ���
#include <ctime>    // time()�� ���� ���

class Star {
public:
    float x, y, size;  // ���� ��ġ(x, y) �� ũ��(size)
    float r, g, b;  // ���� RGB ����

    Star() {
        // ���� ��ġ�� ������ �������� �ʱ�ȭ
        x = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;  // -1���� 1 ����
        y = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;  // -1���� 1 ����
        size = 0.02f;  // ���� ũ��
        r = static_cast<float>(rand()) / RAND_MAX;
        g = static_cast<float>(rand()) / RAND_MAX;
        b = static_cast<float>(rand()) / RAND_MAX;
    }

    void draw() {
        glColor3f(r, g, b);  // ���� ���� ����
        glBegin(GL_TRIANGLE_FAN);  // ���� �׸��� ����
        glVertex2f(x, y);  // ���� �߽� ��ġ
        // 10���� ���� �̿��� �� ����� �׸�
        for (int i = 0; i <= 10; i++) {
            float angle = 2.0f * 3.14159265f * i / 10;  // ���� ���
            float dx = (i % 2 == 0) ? size : size / 2;  // ���� �������� ������ ũ��
            glVertex2f(x + cos(angle) * dx, y + sin(angle) * dx);  // ���� �� ��ġ ���
        }
        glEnd();  // �� �׸��� ����
    }
};