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

    int32_t x_camera = x_solders - WINDOW_WIDTH / 2; //390
    //bool locked_camera = false;
    //std::cout << " el tope de x es " << BACKGROUND_WIDTH-WINDOW_WIDTH << std::endl;
    if (x_camera >= BACKGROUND_WIDTH-WINDOW_WIDTH) {
        x_camera = BACKGROUND_WIDTH-WINDOW_WIDTH;
       //locked_camera = true;
    }
    if (x_camera <= 0) {
        x_camera = 0;
        //locked_camera = true;
    }
    int delta_x = x_old_camera - x_camera; // y el signo que onda
    ge_holder.update_x(delta_x);
      

    //std::cout << "x of camera is " << x << std::endl;

    //std::cout << "El x nuevo es: " << x << std::endl;
    

    //por ahora no estoy usando la y
    // if (y <= 0)
    //     y = y;
    // if (y >= BACKGROUND_HEIGTH-WINDOW_HEIGTH)
    //     y = BACKGROUND_HEIGTH-WINDOW_HEIGTH;


    Area srcArea(x_camera, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    background.render(srcArea, destArea, SDL_FLIP_NONE);
    x_old_camera = x_camera;
}