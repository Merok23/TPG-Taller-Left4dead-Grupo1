#include "camera.h"
#include <iostream>
#include <cmath>

Camera::Camera(SdlWindow &window, int main_player_x) : window(window), 
    background("../../assets/backgrounds/War1/Bright/War.png", window),
    destArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH),
    x_camera_world(main_player_x- WINDOW_WIDTH/2) {
        if (x_camera_world < 0) {
            x_camera_world = 0;
        } else if (x_camera_world > BACKGROUND_WIDTH - WINDOW_WIDTH) {
            x_camera_world = BACKGROUND_WIDTH - WINDOW_WIDTH;
        }
    }


void Camera::render(GraphicsEntityHolder &ge_holder) {
    int x_soldiers_world, y_soldiers_world;
    ge_holder.get_new_coordenates_center(&x_soldiers_world, &y_soldiers_world);

    x_camera_world = x_soldiers_world - WINDOW_WIDTH / 2;

    if (x_camera_world < 0) {
        x_camera_world = 0;
    } else if (x_camera_world > BACKGROUND_WIDTH - WINDOW_WIDTH) {
        x_camera_world = BACKGROUND_WIDTH - WINDOW_WIDTH;
    }
    
    ge_holder.update_x(x_camera_world);

    Area srcArea(x_camera_world, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    window.fill();
    background.render(srcArea, destArea, SDL_FLIP_NONE);
}

int Camera::get_x_left(){
    return x_camera_world - EXTRA_SCREEN;
}

int Camera::get_x_right(){
    return x_camera_world + WINDOW_WIDTH + EXTRA_SCREEN;
}