#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <shader.hpp>
#include <stb_image.h>
#include <used_glm.hpp>
#include <config.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width , int height) { glViewport(0, 0, width, height); }

int main()
{
    std::cout << "main begin!" << std::endl;
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearOpenGL", NULL, NULL);
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

// #define M_LINES
// #define M_PLANE
#define M_POINTS

#define TRANSPARENCE 0.8f

#ifdef M_LINES
    float vertices[] =
    { // 位置 颜色
         1.0f,  0.0f, 0.0f,    0.0f, 1.0f, 0.0f, TRANSPARENCE,
         0.0f,  0.0f, 0.0f,    0.0f, 0.6f, 0.0f, TRANSPARENCE,
        -1.0f,  0.0f, 0.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
         0.0f,  1.0f, 0.0f,    1.0f, 0.0f, 0.0f, TRANSPARENCE,
         0.0f,  0.0f, 0.0f,    0.6f, 0.0f, 0.0f, TRANSPARENCE,
         0.0f, -1.0f, 0.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
         0.0f,  0.0f, 1.0f,    0.0f, 0.0f, 1.0f, TRANSPARENCE,
         0.0f,  0.0f, 0.0f,    0.0f, 0.0f, 0.6f, TRANSPARENCE,
         0.0f,  0.0f,-1.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
    };
    int indices[] = { 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8 };
#define VERTICES_SIZE sizeof(vertices)
#define INDICES_SIZE sizeof(indices)
#endif

#ifdef M_PLANE
    float vertices[] =
    { // 位置 颜色
         1.0f,  0.0f, 1.0f,    0.0f, 1.0f, 0.0f, TRANSPARENCE,
         1.0f,  0.0f,-1.0f,    0.0f, 1.0f, 0.0f, TRANSPARENCE,
        -1.0f,  0.0f,-1.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
        -1.0f,  0.0f, 1.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
         1.0f,  1.0f, 0.0f,    1.0f, 0.0f, 0.0f, TRANSPARENCE,
        -1.0f,  1.0f, 0.0f,    1.0f, 0.0f, 0.0f, TRANSPARENCE,
        -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
         1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
         0.0f,  1.0f, 1.0f,    0.0f, 0.0f, 1.0f, TRANSPARENCE,
         0.0f, -1.0f, 1.0f,    0.0f, 0.0f, 1.0f, TRANSPARENCE,
         0.0f, -1.0f,-1.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
         0.0f,  1.0f,-1.0f,    0.0f, 0.0f, 0.0f, TRANSPARENCE,
    };
#define Point4ClockwiseToTriangle2(begin) begin, begin+1, begin+2, begin, begin+2, begin+3
#define P4CTT2 Point4ClockwiseToTriangle2
    int indices[] = { P4CTT2(0), P4CTT2(4), P4CTT2(8) };
#define VERTICES_SIZE sizeof(vertices)
#define INDICES_SIZE sizeof(indices)
#endif

#ifdef M_POINTS
#define DENSITY (5)
#define HALFDEN (DENSITY/2)
#define LASTDEN (DENSITY-1)
#define DENSITY3 (DENSITY * DENSITY * DENSITY)
#define MAP3TO1(x,y,z) ((z * DENSITY + y) * DENSITY + x)
    float * vertices = new float[DENSITY3 * 7];
    for (int i = 0; i < DENSITY; i++)
        for (int j = 0; j < DENSITY; j++)
            for (int k = 0; k < DENSITY; k++)
            {
                vertices[MAP3TO1(i,j,k) * 7] = -1.0 + i * (2.0 / LASTDEN);
                vertices[MAP3TO1(i,j,k) * 7 + 1] = -1.0 + j * (2.0 / LASTDEN);
                vertices[MAP3TO1(i,j,k) * 7 + 2] = -1.0 + k * (2.0 / LASTDEN);
                vertices[MAP3TO1(i,j,k) * 7 + 3] = 1.0 / LASTDEN * j;
                vertices[MAP3TO1(i,j,k) * 7 + 4] = 1.0 / LASTDEN * i;
                vertices[MAP3TO1(i,j,k) * 7 + 5] = 1.0 / LASTDEN * k;
                vertices[MAP3TO1(i,j,k) * 7 + 6] = TRANSPARENCE;
            }
    unsigned int indices[] = {
#define AXIS
#ifdef AXIS
        MAP3TO1(HALFDEN, HALFDEN, 0), MAP3TO1(HALFDEN, HALFDEN, LASTDEN),
        MAP3TO1(0, HALFDEN, HALFDEN), MAP3TO1(LASTDEN, HALFDEN, HALFDEN),
        MAP3TO1(HALFDEN, 0, HALFDEN), MAP3TO1(HALFDEN, LASTDEN, HALFDEN),
#endif
#define CUBE
#ifdef CUBE
#define DISTANCE (1)
#define ZERO1 (0+DISTANCE)
#define LASTDEN1 (LASTDEN-DISTANCE)
        MAP3TO1(LASTDEN1,    ZERO1,    ZERO1), MAP3TO1(   ZERO1,    ZERO1,    ZERO1),
        MAP3TO1(LASTDEN1,    ZERO1,    ZERO1), MAP3TO1(LASTDEN1,    ZERO1, LASTDEN1),
        MAP3TO1(LASTDEN1,    ZERO1,    ZERO1), MAP3TO1(LASTDEN1, LASTDEN1,    ZERO1),

        MAP3TO1(   ZERO1, LASTDEN1,    ZERO1), MAP3TO1(   ZERO1,    ZERO1,    ZERO1),
        MAP3TO1(   ZERO1, LASTDEN1,    ZERO1), MAP3TO1(LASTDEN1, LASTDEN1,    ZERO1),
        MAP3TO1(   ZERO1, LASTDEN1,    ZERO1), MAP3TO1(   ZERO1, LASTDEN1, LASTDEN1),
        
        MAP3TO1(   ZERO1,    ZERO1, LASTDEN1), MAP3TO1(   ZERO1,    ZERO1,    ZERO1),
        MAP3TO1(   ZERO1,    ZERO1, LASTDEN1), MAP3TO1(   ZERO1, LASTDEN1, LASTDEN1),
        MAP3TO1(   ZERO1,    ZERO1, LASTDEN1), MAP3TO1(LASTDEN1,    ZERO1, LASTDEN1),

        MAP3TO1(LASTDEN1, LASTDEN1, LASTDEN1), MAP3TO1(LASTDEN1, LASTDEN1,    ZERO1),
        MAP3TO1(LASTDEN1, LASTDEN1, LASTDEN1), MAP3TO1(   ZERO1, LASTDEN1, LASTDEN1),
        MAP3TO1(LASTDEN1, LASTDEN1, LASTDEN1), MAP3TO1(LASTDEN1,    ZERO1, LASTDEN1),
#endif
    };
#define VERTICES_SIZE (DENSITY3 * 7 * 4)
#define INDICES_SIZE sizeof(indices)
#endif

    GLuint VBO, VAO, EBO;
    { // 顶点缓冲对象
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, VERTICES_SIZE, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES_SIZE, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        // glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // { // 查询可用的最大顶点属性数量
    //     int nrAttributes;
    //     glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    //     std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    // }
    ourShader.use();
    ourShader.set_uniform("texture1", 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    while(!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        ourShader.use();
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // trans = glm::rotate(trans, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

#ifdef M_LINES
        glDrawElements(GL_LINES, 12, GL_UNSIGNED_INT, 0);
#endif
#ifdef M_PLANE
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
#endif
#ifdef M_POINTS
        glPointSize(5.0f);
        glLineWidth(5.0f);
        glDrawArrays(GL_POINTS, 0, DENSITY3);
        glDrawElements(GL_LINES, INDICES_SIZE/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
#endif

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    std::cout << "main end!" << std::endl;
    exit(EXIT_SUCCESS);
}