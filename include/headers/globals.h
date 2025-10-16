#ifndef GLOBAL_H_
#define GLOBAL_H_

typedef struct vec3 {
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
} vec3;

extern vec3 player_dir, player_vel, default_vec;

#endif