#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
// #include <cmath>
// #include <corecrt_math_defines.h> // M_PI

#include <shader.hpp>
#include <config.hpp>

double perf_freq = 0;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width , int height)
{
    // std::cout << "framebuffer " << width << "," << height << std::endl;
    glViewport(0, 0, width, height);
}

int main()
{
    std::cout << "main begin!" << std::endl;
    {
        LARGE_INTEGER lpFrequency;
        QueryPerformanceFrequency(&lpFrequency);
        std::cout << "perf_freq: " << lpFrequency.QuadPart << std::endl;
        perf_freq = lpFrequency.QuadPart * 1.0 / 1e9;
        std::cout << "perf_freq: " << perf_freq << std::endl;
    }
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
    Shader ourShader(VERTEX_PATH, FRAGMENT_PATH);

    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    GLuint VBO, VAO;
    { // 顶点缓冲对象
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    { // 查询可用的最大顶点属性数量
        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    }

    bool flag = true;
    flag = !flag;
    unsigned long long int t0, t1;
#define GET_TIME(v0) {LARGE_INTEGER temp; QueryPerformanceCounter(&temp); v0 = temp.QuadPart / perf_freq;}
    while(!glfwWindowShouldClose(window))
    {
        // GET_TIME(t0)
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(flag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // flag = !flag;

        ourShader.use();
        float now = glfwGetTime();
        ourShader.set_uniform("breathe", (sin(now) / 2.0f) + 0.5f);
        ourShader.set_uniform("move", (sin(now) / 2.0f), (cos(now) / 2.0f));
        // ourShader.set_uniform("move", (sin(now) / 2.0f), (sin(now) / 2.0f));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // GET_TIME(t1)
        // std::cout << "used: " << t1-t0 << " ns" << std::endl;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    std::cout << "main end!" << std::endl;
    exit(EXIT_SUCCESS);
}