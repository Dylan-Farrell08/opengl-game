#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

float speed = 15;
float accel = 0.15;
float frict = 0.04;
bool dir;

int counter = 0;
struct vec3{
    float x;
    float y;
    float z;
}player_dir, player_vel, default_vec;

struct input{
    bool w;
    bool a;
    bool s;
    bool d;
}input;


float lerp(float target_value, float goal, float rate){
    if (goal <= 0){
        rate = -rate;
    };
    target_value = target_value + rate;

    if (abs(target_value) >= goal){
        target_value = goal;
    };
    return target_value;
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
    if (input.a){player_dir.x =  1.0f;};
    if (input.d){player_dir.x = -1.0f;}; 
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

void body(GLFWwindow* window){
    input_handeler(window);
    move();
    counter++;
}