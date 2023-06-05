#include "camera.h"

Camera::Camera(SdlWindow &window) : window(window), 
    background("../../assets/backgrounds/War1/Bright/War.png", window),
    destArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH) {}


void Camera::render(size_t &x, size_t &y) {
    window.fill(); //lleno con el background gris
    Area srcArea(x, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    background.render(srcArea, destArea, SDL_FLIP_NONE);
}