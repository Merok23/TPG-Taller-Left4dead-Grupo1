#include "camera.h"
#include <iostream>

Camera::Camera(SdlWindow &window) : window(window), 
    background("../../assets/backgrounds/War1/Bright/War.png", window),
    destArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH),
    x_old_camera(0) {}


void Camera::render(GraphicsEntityHolder &ge_holder) {
    window.fill(); //lleno con el background gris
    int32_t x_solders, y;
    ge_holder.get_new_coordenates_center(&x_solders, &y);

    int32_t x_camera = x_solders - WINDOW_WIDTH / 2;
    if (x_camera >= BACKGROUND_WIDTH-WINDOW_WIDTH) {
        x_camera = BACKGROUND_WIDTH-WINDOW_WIDTH;
    }
    if (x_camera <= 0) {
        x_camera = 0;
    }
    int delta_x = x_old_camera - x_camera; // y el signo que onda
    ge_holder.update_x(delta_x);


    Area srcArea(x_camera, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    background.render(srcArea, destArea, SDL_FLIP_NONE);
    x_old_camera = x_camera;
}

int Camera::get_x_left(){
    return x_old_camera - EXTRA_SCREEN;
}

int Camera::get_x_right(){
    return x_old_camera + WINDOW_WIDTH + EXTRA_SCREEN;
}