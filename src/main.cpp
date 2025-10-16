#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include <map>
#include <headers/shader.h>
#include <movement.cpp>
#include "headers/globals.h"
#include "headers/display.cpp"

vec3 player_dir = {0.0f, 0.0f, 0.0f};
vec3 player_vel = {0.0f, 0.0f, 0.0f};
vec3 default_vec = {0.0f, 0.0f, 0.0f};  

GLFWwindow* window;

int main(){          
    window = initialise_window(window);
    srand(time(0));
    gen_buffers();
    Shader ourShader("src/shaders/vertex.vs","src/shaders/fragment.fs");
    //-----------------------------------------------------------------------------------------------------
    int size = sizeof(vertices) / sizeof(vertices[0]);
    while (!glfwWindowShouldClose(window)){
        //std::cout << "X & Y:" << player_vel.x<< " " << player_vel.y << " ";
        for (int x = 0; x <= size;){
            vertices[x] += player_vel.x;
            vertices[x+1] += player_vel.y;
            x += 3;
        };
        player_movement(window);
        window_stuff(ourShader, window);
    }

    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    //alot of stuff that basically just destroys the window
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}