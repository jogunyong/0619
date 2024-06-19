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
    float x;      // ��ֹ��� x ��ġ
    float height; // ��ֹ��� ����
    float width;  // ��ֹ��� ���� ���� (������ 50cm)
};

std::vector<Obstacle> obstacles; // ��ֹ����� ������ ����

void InitializeObstacles() {
    // ��ֹ� �ʱ�ȭ (���� 50cm, ���̴� �پ��ϰ� ����)
    Obstacle obs1 = { 0.5f, 0.1f, 0.5f };   // x ��ġ, ���� 100cm
    Obstacle obs2 = { -0.3f, 0.3f, 0.5f };  // x ��ġ, ���� 300cm
    obstacles.push_back(obs1);
    obstacles.push_back(obs2);
}

void RenderObstacles() {
    glColor3f(0.0f, 1.0f, 0.0f); // ������� ����

    for (const auto& obstacle : obstacles) {
        // ��ֹ� �׸���
        glBegin(GL_QUADS);
        glVertex2f(obstacle.x, -0.5f);                            // ���� �Ʒ�
        glVertex2f(obstacle.x + obstacle.width, -0.5f);           // ������ �Ʒ�
        glVertex2f(obstacle.x + obstacle.width, -0.5f + obstacle.height); // ������ ��
        glVertex2f(obstacle.x, -0.5f + obstacle.height);          // ���� ��
        glEnd();
    }
}

void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Ű���� �Է� �ݹ� �Լ�
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Viewport ����
    glViewport(0, 0, width, height);

    // Orthographic Projection ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)width / (float)height;
    glOrtho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

int Physics() {
    // ���� ������Ʈ ó��
    return 0;
}

int Initialize() {
    // �ʱ�ȭ �۾�
    return 0;
}

int Update() {
    // ���� ���� ������Ʈ
    return 0;
}

int Render() {
    // ȭ���� �ϴû����� ����
    glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // ȭ���� �ʺ� �°� �ٴ��� ���� ���̸� ����
    float aspectRatio;
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    aspectRatio = (float)width / (float)height;

    // �ٴ��� ��������� ���� (R: 255, G: 200, B: 15)
    glColor3f(255.0f / 255.0f, 200.0f / 255.0f, 15.0f / 255.0f);

    // �ٴ��� �簢������ �׸���
    glBegin(GL_QUADS);
    glVertex2f(-aspectRatio, -0.5f); // ���� �Ʒ�
    glVertex2f(aspectRatio, -0.5f);  // ������ �Ʒ�
    glVertex2f(aspectRatio, -1.0f);  // ������ ��
    glVertex2f(-aspectRatio, -1.0f); // ���� ��
    glEnd();

    // ���������� �÷��̾� ĳ���� ���� (R: 255, G: 0, B: 0)
    glColor3f(255.0f / 255.0f, 0.0f, 0.0f);

    // �÷��̾� ĳ���͸� ���簢������ �׸��� (50cm ��)
    float playerSize = 0.1f; // 50cm�� ȭ�鿡 �°� ���� (0.1�� ������ �� ����)

    glBegin(GL_QUADS); // �簢�� �׸��� ����
    glVertex2f(-playerSize / 2, -0.5f + playerSize); // ���� �Ʒ� �𼭸�
    glVertex2f(playerSize / 2, -0.5f + playerSize);  // ������ �Ʒ� �𼭸�
    glVertex2f(playerSize / 2, -0.5f);               // ������ �� �𼭸�
    glVertex2f(-playerSize / 2, -0.5f);              // ���� �� �𼭸�
    glEnd(); // �簢�� �׸��� ��

    // ���������� �׵θ� ���� (R: 0, G: 0, B: 0)
    glColor3f(0.0f, 0.0f, 0.0f);

    // �÷��̾� ĳ���� �׵θ� �׸��� (3cm �β�)
    float borderWidth = 0.006f; // 3cm�� ȭ�鿡 �°� ���� (0.006�� ������ �� ����)

    // ��� �׵θ�
    glBegin(GL_QUADS);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f + playerSize);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f + playerSize);
    glEnd();

    // �ϴ� �׵θ�
    glBegin(GL_QUADS);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f - borderWidth);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f - borderWidth);
    glEnd();

    // ���� �׵θ�
    glBegin(GL_QUADS);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(-playerSize / 2, -0.5f + playerSize + borderWidth);
    glVertex2f(-playerSize / 2, -0.5f - borderWidth);
    glVertex2f(-playerSize / 2 - borderWidth, -0.5f - borderWidth);
    glEnd();

    // ���� �׵θ�
    glBegin(GL_QUADS);
    glVertex2f(playerSize / 2, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f + playerSize + borderWidth);
    glVertex2f(playerSize / 2 + borderWidth, -0.5f - borderWidth);
    glVertex2f(playerSize / 2, -0.5f - borderWidth);
    glEnd();

    return 0;
}

void UpdateObstacles(float deltaTime) {
    float obstacleSpeed = 0.2f; // ��ֹ� �̵� �ӵ�

    // ��ֹ����� �������� �������� �̵�
    for (auto& obstacle : obstacles) {
        obstacle.x -= obstacleSpeed * deltaTime;

        // ��ֹ��� ȭ�� ������ �Ѿ�� ���� ������ �ٽ� ��Ÿ���� ��Ȱ��
        if (obstacle.x + obstacle.width < -1.0f) {
            obstacle.x = 1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.5f; // �������� ������ ��ġ���� �����
        }
    }
}

int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // glfw ���̺귯�� �ʱ�ȭ
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

    // �����ӹ��� ũ�� ���� �ݹ� ����
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    Initialize();

    // �ʱ� ����Ʈ�� ���� ����
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebufferSizeCallback(window, width, height);

    // ��ֹ� �ʱ�ȭ
    InitializeObstacles();

    // ���� �ð� �ʱ�ȭ
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window)) {
        // ���� �ð� ���
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
        lastTime = currentTime;

        glfwPollEvents();
        Physics();
        UpdateObstacles(deltaTime);
        Update();
        Render();

        // ��ֹ� ������
        RenderObstacles();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
