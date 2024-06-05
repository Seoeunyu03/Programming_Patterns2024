#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>

const GLint WIDTH = 800, HEIGHT = 600;

// 중력 상수
const float GRAVITY = -9.8f;  // 중력 가속도 (m/s^2)

// 플레이어 속성
struct Player {
    float x, y;
    float size;
    float velocityY;
    bool isJumping;
    bool isChargingJump;
    float jumpStrength;
    std::chrono::steady_clock::time_point jumpStartTime;
} player;

// 바닥 속성
const float groundVertices[] = {
    -0.8f, -0.8f,
     0.8f, -0.8f,
     0.8f, -0.6f,
    -0.8f, -0.6f
};

// 플레이어 초기화
void initPlayer() {
    player.x = 0.0f;
    player.y = -0.5f;
    player.size = 0.1f;
    player.velocityY = 0.0f;
    player.isJumping = false;
    player.isChargingJump = false;
    player.jumpStrength = 0.0f;
}

// 바닥 그리기
void renderGround() {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; i += 2) {
        glVertex2f(groundVertices[i], groundVertices[i + 1]);
    }
    glEnd();
}

// 플레이어 그리기
void renderPlayer() {
    glBegin(GL_QUADS);
    glVertex2f(player.x - player.size / 2, player.y - player.size );
    glVertex2f(player.x + player.size / 2, player.y - player.size );
    glVertex2f(player.x + player.size / 2, player.y + player.size / 2);
    glVertex2f(player.x - player.size / 2, player.y + player.size / 2);
    glEnd();
}

// 플레이어 점프 처리
void handleJumping() {
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!player.isJumping && !player.isChargingJump) {
            player.isChargingJump = true;
            player.jumpStartTime = std::chrono::steady_clock::now();
        }
    }
    else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_RELEASE) {
        if (player.isChargingJump) {
            player.isChargingJump = false;
            player.isJumping = true;
            auto jumpDuration = std::chrono::steady_clock::now() - player.jumpStartTime;
            player.jumpStrength = std::chrono::duration_cast<std::chrono::milliseconds>(jumpDuration).count() * 0.01f;
            player.velocityY = player.jumpStrength;
        }
    }
}

// 중력 적용 및 플레이어 위치 업데이트
void applyPhysics(float deltaTime) {
    if (player.isJumping) {
        player.velocityY += GRAVITY * deltaTime;  // 중력 적용
        player.y += player.velocityY * deltaTime; // 위치 업데이트

        if (player.y <= -0.5f) {  // 바닥에 충돌
            player.y = -0.5f;
            player.isJumping = false;
            player.velocityY = 0.0f;
        }
    }
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    // GLFW 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "간단한 게임", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW 윈도우 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 플레이어 초기화
    initPlayer();

    // 타이머 초기화
    auto previousTime = std::chrono::steady_clock::now();

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        // 현재 시간과 이전 시간의 차이를 계산
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = currentTime - previousTime;
        previousTime = currentTime;
        float deltaTime = elapsed.count();

        // 화면 지우기
        glClear(GL_COLOR_BUFFER_BIT);

        // 바닥 그리기
        renderGround();

        // 플레이어 그리기
        renderPlayer();

        // 점프 입력 처리
        handleJumping();

        // 물리 엔진 적용
        applyPhysics(deltaTime);

        // 버퍼 교체 및 이벤트 처리
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
