#include "camera.h"

Camera::Camera(SdlWindow &window) : window(window), 
    background("../../assets/backgrounds/War1/Bright/War.png", window),
    destArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH) {}


void Camera::render(size_t &x, size_t &y) {
    window.fill(); //lleno con el background gris

    if (x >= BACKGROUND_WIDTH-WINDOW_WIDTH)
        x = BACKGROUND_WIDTH-WINDOW_WIDTH;
    if (x <= 0)
        x = 0;

    //por ahora no estoy usando la y
    // if (y <= 0)
    //     y = y;
    // if (y >= BACKGROUND_HEIGTH-WINDOW_HEIGTH)
    //     y = BACKGROUND_HEIGTH-WINDOW_HEIGTH;


    Area srcArea(x, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    background.render(srcArea, destArea, SDL_FLIP_NONE);
}