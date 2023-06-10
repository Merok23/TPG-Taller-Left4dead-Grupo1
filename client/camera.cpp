#include "camera.h"
#include <iostream>
#include <cmath>

Camera::Camera(SdlWindow &window) : window(window), 
    background("../../assets/backgrounds/War1/Bright/War.png", window),
    destArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH),
    x_camera_world(0) {}


void Camera::render(GraphicsEntityHolder &ge_holder) {
    window.fill(); //lleno con el background gris
    int32_t x_solders, y;
    ge_holder.get_new_coordenates_center(&x_solders, &y);

    int32_t target_x_camera_world = x_solders - WINDOW_WIDTH / 2;
    int delta_x = 0;

    if (abs(target_x_camera_world - x_camera_world) <= TRANSITION_MARGIN) {
        x_camera_world = target_x_camera_world;
        delta_x = target_x_camera_world - x_camera_world;
    }
    else {
        int32_t direction = (target_x_camera_world < x_camera_world) ? -1 : 1;
        x_camera_world += direction * TRANSITION_MARGIN;
        delta_x = direction * TRANSITION_MARGIN;
    }

    if (x_camera_world >= BACKGROUND_WIDTH - WINDOW_WIDTH) {
        x_camera_world = BACKGROUND_WIDTH - WINDOW_WIDTH;
    }
    if (x_camera_world <= 0) {
        x_camera_world = 0;
    }

    ge_holder.update_x(delta_x);

    x_camera_world+=5;

    Area srcArea(x_camera_world, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    background.render(srcArea, destArea, SDL_FLIP_NONE);
}

int Camera::get_x_left(){
    return x_camera_world - EXTRA_SCREEN;
}

int Camera::get_x_right(){
    return x_camera_world + WINDOW_WIDTH + EXTRA_SCREEN;
}