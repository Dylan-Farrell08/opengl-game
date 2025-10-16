#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "headers/globals.h"
float speed = 0.09;
float accel = 0.009;
float frict = 0.004;
bool dir;

int counter = 0;

struct input{
    bool w;
    bool a;
    bool s;
    bool d;
}input;


float lerp(float target_value, float goal, float rate){
    float diffrence = goal - target_value;
    if (fabs(diffrence) <= rate){
        return goal;
    };
    //(diffrence > 0 ? 1 : -1) the first part before the ? is basically an if statement but smaller, then the second part (rate : -rate) is then the true and false outcomes
    return target_value + (diffrence > 0.0 ? rate : -rate);
};

void input_handeler(GLFWwindow* highlighted_window){
    dir = false;
    player_dir = default_vec;
    input.w = glfwGetKey(highlighted_window, GLFW_KEY_W);
    input.a = glfwGetKey(highlighted_window, GLFW_KEY_A);
    input.s = glfwGetKey(highlighted_window, GLFW_KEY_S);
    input.d = glfwGetKey(highlighted_window, GLFW_KEY_D);
    if (input.w){player_dir.y =  1.0f;};
    if (input.s){player_dir.y = -1.0f;};
    if (input.a){player_dir.x =  -1.0f;};
    if (input.d){player_dir.x = 1.0f;}; 
}

void move(){
    if (player_dir.x != 0){
        player_vel.x = lerp(player_vel.x, (player_dir.x * speed), accel);
    }else{
        player_vel.x = lerp(player_vel.x, 0.0f , frict);
    };
    if (player_dir.y != 0){
        player_vel.y = lerp(player_vel.y, (player_dir.y * speed), accel);
    }else{
        player_vel.y = lerp(player_vel.y, 0.0f , frict);
    };
}

vec3 player_movement(GLFWwindow* window){
    input_handeler(window);
    move();
    counter++;
    return player_vel;
}