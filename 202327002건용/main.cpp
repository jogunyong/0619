#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cstdio>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Obstacle {
    float x;      // 장애물의 x 위치
    float height; // 장애물의 높이
    float width;  // 장애물의 가로 길이 (고정값 50cm)
};

std::vector<Obstacle> obstacles; // 장애물들을 관리할 벡터

void InitializeObstacles() {
    // 장애물 초기화 (가로 50cm, 높이는 다양하게 설정)
    Obstacle obs1 = { 0.5f, 0.1f, 0.5f };   // x 위치, 높이 100cm
    Obstacle obs2 = { -0.3f, 0.3f, 0.5f };  // x 위치, 높이 300cm
    obstacles.push_back(obs1);
    obstacles.push_back(obs2);
}

void RenderObstacles() {
    glColor3f(0.0f, 1.0f, 0.0f); // 녹색으로 설정

    for (const auto& obstacle : obstacles) {
        // 장애물 그리기
        glBegin(GL_QUADS);
        glVertex2f(obstacle.x, -0.5f);                            // 왼쪽 아래
        glVertex2f(obstacle.x + obstacle.width, -0.5f);           // 오른쪽 아래
        glVertex2f(obstacle.x + obstacle.width, -0.5f + obstacle.height); // 오른쪽 위
        glVertex2f(obstacle.x, -0.5f + obstacle.height);          // 왼쪽 위
        glEnd();
    }
}

void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // 키보드 입력 콜백 함수
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Viewport 설정
    glViewport(0, 0, width, height);

    // Orthographic Projection 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)width / (float)height;
    glOrtho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

int Physics() {
    // 물리 업데이트 처리
    return 0;
}

int Initialize() {
    // 초기화 작업
    return 0;
}

int Update() {
    // 게임 상태 업데이트
    return 0;
}

int Render() {
    // 화면을 하늘색으로 지움
    glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 화면의 너비에 맞게 바닥의 가로 길이를 조정
    float aspectRatio;
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    aspectRatio = (float)width / (float)height;

    // 바닥을 노란색으로 설정 (R: 255, G: 200, B: 15)
    glColor3f(255.0f / 255.0f, 200.0f / 255.0f, 15.0f / 255.0f);

    // 바닥을 사각형으로 그리기
    glBegin(GL_QUADS);
    glVertex2f(-aspectRatio, -0.5f); // 왼쪽 아래
    glVertex2f(aspectRatio, -0.5f);  // 오른쪽 아래
    glVertex2f(aspectRatio, -1.0f);  // 오른쪽 위
    glVertex2f(-aspectRatio, -1.0f); // 왼쪽 위
    glEnd();

    // 빨간색으로 플레이어 캐릭터 설정 (R: 255, G: 0, B: 0)
    glColor3f(255.0f / 255.0f, 0.0f, 0.0f);

    // 플레이어 캐릭터를 정사각형으로 그리기 (50cm 변)
    float playerSize = 0.1f; // 50cm를 화면에 맞게 조정 (0.1은 적절한 값 예시)

    glBegin(GL_QUADS); // 사각형 그리기 시작
    glVertex2f(-playerSize / 2, -0.5f + playerSize); // 왼쪽 아래 모서리
    glVertex2f(playerSize / 2, -0.5f + playerSize);  // 오른쪽 아래 모서리
    glVertex2f(playerSize / 2, -0.5f);               // 오른쪽 위 모서리
    glVertex2f(-playerSize / 2, -0.5f);              // 왼쪽 위 모서리
    glEnd(); // 사각형 그리기 끝

    // 검정색으로 테두리 설정 (R: 0, G: 0, B: 0)
    glColor3f(0.0f, 0.0f, 0.0f);

    // 플레이어 캐릭터 테두리 그리기 (3cm 두께)
    float borderWidth = 0.006f; // 3cm를 화면에 맞게 조정 (0.006은 적절한 값 예시)

    // 상단 테두리
    glBegin(GL_QUADS);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f + playerSize);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f + playerSize);
    glEnd();

    // 하단 테두리
    glBegin(GL_QUADS);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f - borderWidth);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f - borderWidth);
    glEnd();

    // 좌측 테두리
    glBegin(GL_QUADS);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(-playerSize / 2, -0.5f + playerSize + borderWidth);
    glVertex2f(-playerSize / 2, -0.5f - borderWidth);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f - borderWidth);
    glEnd();

    // 우측 테두리
    glBegin(GL_QUADS);
    glVertex2f(playerSize / 2, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f - borderWidth);
    glVertex2f(playerSize / 2, -0.5f - borderWidth);
    glEnd();

    return 0;
}

void UpdateObstacles(float deltaTime) {
    float obstacleSpeed = 0.2f; // 장애물 이동 속도

    // 장애물들을 우측에서 좌측으로 이동
    for (auto& obstacle : obstacles) {
        obstacle.x -= obstacleSpeed * deltaTime;

        // 장애물이 화면 왼쪽을 넘어가면 우측 끝에서 다시 나타나게 재활용
        if (obstacle.x + obstacle.width < -1.0f) {
            obstacle.x = 1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.5f; // 우측에서 임의의 위치에서 재생성
        }
    }
}

int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // glfw 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    // 프레임버퍼 크기 변경 콜백 설정
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    Initialize();

    // 초기 뷰포트와 투영 설정
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebufferSizeCallback(window, width, height);

    // 장애물 초기화
    InitializeObstacles();

    // 이전 시간 초기화
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window)) {
        // 현재 시간 계산
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
        lastTime = currentTime;

        glfwPollEvents();
        Physics();
        UpdateObstacles(deltaTime);
        Update();
        Render();

        // 장애물 렌더링
        RenderObstacles();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
