#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include <map>
#include <headers/shader.h>
GLFWwindow* window;

struct rgb{
    float r = 0.01;
    float g = 0.01;
    float b = 0.00;
}rgb;

struct input{
    bool w;
    bool a;
    bool s;
    bool d;
}input;

struct vec3{
    float x;
    float y;
    float z;
}player_vel;

float wrap(float lowest, float highest, float number){
    float remainder = 0.0;
    while (number > highest){
        remainder = (number - highest);
        number = lowest + remainder;
    };
    return number;
    
}

void input_handeler(){
    input.w = glfwGetKey(window, GLFW_KEY_W);
    input.a = glfwGetKey(window, GLFW_KEY_A);
    input.s = glfwGetKey(window, GLFW_KEY_S);
    input.d = glfwGetKey(window, GLFW_KEY_D);
    if (input.w){player_vel.y =  100.0f;};
    if (input.s){player_vel.y = -1.0f;};
    if (input.a){player_vel.x =  1.0f;};
    if (input.d){player_vel.x = -1.0f;}; 
}

int main(){
    //just turning on glfw basically does nbothing else to my knowledge
    glfwInit();
    //telling glfw what version and stuff that i am using, i used the compat profile because tahts the version i downloaded i think.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    //just making a blank window thats 800 by 800, with the second part being the name of the window. idk what the last two do
    window = glfwCreateWindow(800,800, "my awesome game", NULL, NULL);
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

    srand(time(0));
    rgb.r = (float)(rand()) / (float)(RAND_MAX);
    rgb.g = (float)(rand()) / (float)(RAND_MAX);
    rgb.b = (float)(rand()) / (float)(RAND_MAX);

    Shader ourShader("src/shaders/vertex.vs","src/shaders/fragment.fs");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);        
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //just defining the vertices of the triang with it being (x,y,z)
    float vertices[] = {
        0.5f,  0.5f, 0.0f,// top right
        0.5f, -0.5f, 0.0f,// bottom right
        -0.5f, -0.5f, 0.0f,// bottom left 
        -0.5f, 0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };
    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f,   // top-center corner
        -0.5f, 0.5f
    };
    
    //defining the vertex buffer object which is where they store vertex data in memory
    //so they can then smoothly show one each frame without worrying if its deformed or ts
    //vertex array object
    unsigned int VAO, VBO;
    unsigned int EBO;
    //just generating them
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    //-----------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)){
        std::cout << player_vel.x << " "<< player_vel.y;
        ourShader.setFloat("offset.x", player_vel.x);
        input_handeler();
        rgb.r = wrap(-1.0, 1.0, rgb.r + 0.002);
        rgb.g = wrap(-1.0, 1.0, rgb.g + 0.002);
        rgb.b = wrap(-1.0, 1.0, rgb.b + 0.002);
        glfwPollEvents();
        glClearColor(fabs(rgb.r), fabs(rgb.g), fabs(rgb.b), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    //alot of stuff that basically just destroys the window
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}