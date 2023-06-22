#include "camera.h"
#include <iostream>
#include <cmath>

Camera::Camera(SdlWindow &window, int main_player_x) : window(window), 
    //background("../../assets/backgrounds/War1/Bright/War.png", window),
    background_sky("../../assets/backgrounds/War1/Bright/sky_long.png", window),
    background_houses1("../../assets/backgrounds/War1/Bright/houses1_long.png", window),
    background_houses2("../../assets/backgrounds/War1/Bright/houses2_long.png", window),
    background_houses3("../../assets/backgrounds/War1/Bright/houses3_long.png", window),
    background_ruins("../../assets/backgrounds/War1/Bright/ruins_long.png", window),
    background_fence("../../assets/backgrounds/War1/Bright/fence_long.png", window),
    background_road("../../assets/backgrounds/War1/Bright/road_long.png", window),
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

    x_camera_world = x_soldiers_world - WINDOW_WIDTH / 2 + 150; //offset para que se vea mas centrado

    if (x_camera_world < 0) {
        x_camera_world = 0;
    } else if (x_camera_world > BACKGROUND_WIDTH - WINDOW_WIDTH) {
        x_camera_world = BACKGROUND_WIDTH - WINDOW_WIDTH;
    }
    
    ge_holder.update_x(x_camera_world);

    Area srcArea(x_camera_world, 400, WINDOW_WIDTH, WINDOW_HEIGTH);
    window.fill();
    
    background_sky.render(srcArea, destArea, SDL_FLIP_NONE);
    background_ruins.render(srcArea, destArea, SDL_FLIP_NONE);
    background_houses3.render(srcArea, destArea, SDL_FLIP_NONE);
    background_houses2.render(srcArea, destArea, SDL_FLIP_NONE);
    background_houses1.render(srcArea, destArea, SDL_FLIP_NONE);
    background_fence.render(srcArea, destArea, SDL_FLIP_NONE);
    background_road.render(srcArea, destArea, SDL_FLIP_NONE);
}

int Camera::get_x_left(){
    return x_camera_world - EXTRA_SCREEN;
}

int Camera::get_x_right(){
    return x_camera_world + WINDOW_WIDTH + EXTRA_SCREEN;
}