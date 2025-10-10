#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
struct rgb{
    float r = 0.01;
    float g = 0.01;
    float b = 0.00;
}rgb;
float wrap(float lowest, float highest, float number){
    float remainder = 0.0;
    while (number > highest){
        remainder = (number - highest);
        number = lowest + remainder;
    };
    return number;
    
}


int main(){
    //just turning on glfw basically does nbothing else to my knowledge
    glfwInit();
    //telling glfw what version and stuff that i am using, i used the compat profile because tahts the version i downloaded i think.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    //just making a blank window thats 800 by 800, with the second part being the name of the window. idk what the last two do
    GLFWwindow* window = glfwCreateWindow(800,800, "my awesome game", NULL, NULL);
    //checking if the windows not there and if its not then it basically kills of the program
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    //telling glfw to look at the window we just created
    glfwMakeContextCurrent(window);
    //loading glad up like glwfinit
    gladLoadGL();
    //sets up which way the window is done, in this case it goes from the top left (0,0) down to the bottom right (800, 800)
    glViewport(0,0,800,800);
    //making a pure color in whatever that is called
    glClearColor(0.1f, 0.13f, 0.54f, 1.0f);
    //gets rid of the back buffer and then puts the new stuff on it
    glClear(GL_COLOR_BUFFER_BIT);
    //swaps the back buffer with the front buffer
    glfwSwapBuffers(window);
    //checking if anyones pressed the close window button
    srand(time(0));
    rgb.r = (float)(rand()) / (float)(RAND_MAX);
    rgb.g = (float)(rand()) / (float)(RAND_MAX);
    rgb.b = (float)(rand()) / (float)(RAND_MAX);

    //-----------------------------------------------------------------------------------------------------

    const char* vertexShaderSrc =
        "#version 330 core\n" 
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "} \0";

    const char* fragmentShaderSrc = 
        "#version 330 core\n" 
        "out vec4 fragColor;\n"
        "void main() {\n"
        "   fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "} \0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, 0);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
        std::cout << "failed to make triangle ERR:" << infoLog << std::endl;
    };

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, 0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
        std::cout << "failed to make fragment ERR:" << infoLog << std::endl;
    };

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);  
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
        std::cout << "FAILED TO LINK SHADERS ERR:" << infoLog << std::endl; 
    };

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //gl_dynamic_draw, USE THIS IF THE THING IS MOVING AROUND ALOT
    //gl_static_draw, use this if you only plan on setting the thing once
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //-----------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)){
        rgb.r = wrap(-1.0, 1.0, rgb.r + 0.002);
        rgb.g = wrap(-1.0, 1.0, rgb.g + 0.002);
        rgb.b = wrap(-1.0, 1.0, rgb.b + 0.002);
        std::cout << rgb.r;
        glfwPollEvents();
        glClearColor(fabs(rgb.r), fabs(rgb.g), fabs(rgb.b), 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    //alot of stuff that basically just destroys the window
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}