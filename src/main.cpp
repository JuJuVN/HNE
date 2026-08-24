#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>


std::string readShaderFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file)
    {
        std::cerr << "Failed to open shader: " << path << '\n';
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}


unsigned int createShader(
    const std::string& source,
    unsigned int type
)
{
    unsigned int shader = glCreateShader(type);

    const char* sourcePtr = source.c_str();

    glShaderSource(
        shader,
        1,
        &sourcePtr,
        nullptr
    );

    glCompileShader(shader);

    return shader;
}


int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Request OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
        "HNE - Honored Engine",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }

    // Triangle vertices
    float vertices[] =
    {
         0.0f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f
    };

    // Create VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // Tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);


    // Read shaders from files
    std::string vertexSource =
        readShaderFile("shaders/basic.vert");

    std::string fragmentSource =
        readShaderFile("shaders/basic.frag");

    if (vertexSource.empty() || fragmentSource.empty())
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }


    // Compile shaders
    unsigned int vertexShader =
        createShader(vertexSource, GL_VERTEX_SHADER);

    unsigned int fragmentShader =
        createShader(fragmentSource, GL_FRAGMENT_SHADER);


    // Create shader program
    unsigned int shaderProgram =
        glCreateProgram();

    glAttachShader(
        shaderProgram,
        vertexShader
    );

    glAttachShader(
        shaderProgram,
        fragmentShader
    );

    glLinkProgram(shaderProgram);


    // Individual shaders are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
