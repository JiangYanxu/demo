#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <iomanip>

#include <shader.hpp>
#include <stb_image.h>
#include <used_glm.hpp>
#include <config.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width , int height) { glViewport(0, 0, width, height); }
void show_mat4(glm::mat4 &mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << std::setw(10) << std::fixed << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    // glm::mat4 trans = glm::mat4(1.0f);
    // show_mat4(trans);
    // // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // 移动
    // // show_mat4(trans);
    // // vec = trans * vec;
    // // std::cout << vec.x << vec.y << vec.z << std::endl;
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); // 旋转
    // show_mat4(trans);
    // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5)); // 缩放
    // show_mat4(trans);
    // // return 0;


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

    float vertices[] =
    { // 位置 颜色 纹理坐标
         0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
    };
    int indices[] = 
    {
        0, 1, 3,
        1, 2, 3
    };
    GLuint VBO, VAO, EBO;
    { // 顶点缓冲对象
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        // glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    GLuint texture1, texture2;
    { // 纹理
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        {
            int width, height, nrChannels;
            auto image = IMAGES_PATH "/container.jpg";
            unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);
            if (data)
            {
                std::cout << "Load " << image << " width:" << width << " height:" << height << " nrChannels:" << nrChannels << std::endl;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
                std::cerr << "Load error! " << image << " width:" << width << " height:" << height << " nrChannels:" << nrChannels << std::endl;
            stbi_image_free(data);
        }
        // glBindTexture(GL_TEXTURE_2D, 0);

        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        {
            int width, height, nrChannels;
            auto image = IMAGES_PATH "/awesomeface.png";
            // stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);
            if (data)
            {
                std::cout << "Load " << image << " width:" << width << " height:" << height << " nrChannels:" << nrChannels << std::endl;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
                std::cerr << "Load error! " << image << " width:" << width << " height:" << height << " nrChannels:" << nrChannels << std::endl;
            stbi_image_free(data);
            stbi_set_flip_vertically_on_load(false);
        }
        // glBindTexture(GL_TEXTURE_2D, 0);
    }
    // { // 查询可用的最大顶点属性数量
    //     int nrAttributes;
    //     glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    //     std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    // }
    ourShader.use();
    ourShader.set_uniform("texture1", 0);
    ourShader.set_uniform("texture2", 1);

    glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    while(!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        ourShader.use();
        glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);

    glfwTerminate();
    std::cout << "main end!" << std::endl;
    exit(EXIT_SUCCESS);
}







