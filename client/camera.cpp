#include "camera.h"
#include <iostream>

Camera::Camera(SdlWindow &window) : window(window), 
    background("../../assets/backgrounds/War1/Bright/War.png", window),
    destArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH) {}


void Camera::render(GraphicsEntityHolder &ge_holder) {
    window.fill(); //lleno con el background gris
    int32_t x, y;
    ge_holder.get_new_coordenates_center(&x, &y);
    std::cout << "x of player is " << x << std::endl;

    x = x - WINDOW_WIDTH / 2; //100 es el player.width
    if (x <= 0)
        x = x;
    else 
        ge_holder.update_x(x);

    //std::cout << "El x original es: " << x << std::endl;
    //x = x - WINDOW_WIDTH/2;
    //std::cout << " el tope de x es " << BACKGROUND_WIDTH-WINDOW_WIDTH << std::endl;
    // if (x >= BACKGROUND_WIDTH-WINDOW_WIDTH)//+WINDOW_WIDTH/2)
    //     x = BACKGROUND_WIDTH-WINDOW_WIDTH;//+WINDOW_WIDTH/2;
    // if (x <= 0)
    //     x = 0;
    

    std::cout << "x of camera is " << x << std::endl;

    //std::cout << "El x nuevo es: " << x << std::endl;
    

    //por ahora no estoy usando la y
    // if (y <= 0)
    //     y = y;
    // if (y >= BACKGROUND_HEIGTH-WINDOW_HEIGTH)
    //     y = BACKGROUND_HEIGTH-WINDOW_HEIGTH;


    Area srcArea(x, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    background.render(srcArea, destArea, SDL_FLIP_NONE);
}