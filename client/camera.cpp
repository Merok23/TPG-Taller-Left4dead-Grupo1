#include "camera.h"
#include <iostream>
#include <cmath>

Camera::Camera(SdlWindow &window, int main_player_x, int main_player_y) : window(window), 
    //background("../../assets/backgrounds/War1/Bright/War.png", window),
    background_sky("../../assets/backgrounds/War1/Bright/sky_long.png", window),
    background_houses1("../../assets/backgrounds/War1/Bright/houses1_long.png", window),
    background_houses2("../../assets/backgrounds/War1/Bright/houses2_long.png", window),
    background_houses3("../../assets/backgrounds/War1/Bright/houses3_long.png", window),
    background_ruins("../../assets/backgrounds/War1/Bright/ruins_long.png", window),
    background_fence("../../assets/backgrounds/War1/Bright/fence_long.png", window),
    background_road("../../assets/backgrounds/War1/Bright/road_long.png", window),
    destArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH),
    x_camera_world(main_player_x- WINDOW_WIDTH/2),
    y_camera_world(main_player_y- WINDOW_HEIGTH/2) {
        if (x_camera_world < 0) {
            x_camera_world = 0;
        } else if (x_camera_world > BACKGROUND_WIDTH - WINDOW_WIDTH) {
            x_camera_world = BACKGROUND_WIDTH - WINDOW_WIDTH;
        }

        if (y_camera_world < 0) {
            y_camera_world = 0;
        } else if (y_camera_world > BACKGROUND_HEIGTH - WINDOW_HEIGTH) {
            y_camera_world = BACKGROUND_HEIGTH - WINDOW_HEIGTH;
        }
    }


void Camera::render(GraphicsEntityHolder &ge_holder) {
    int x_soldiers_world, y_soldiers_world;
    ge_holder.get_new_coordenates_center(&x_soldiers_world, &y_soldiers_world);

    x_camera_world = x_soldiers_world - WINDOW_WIDTH / 2 + 150; //offset para que se vea mas centrado
    y_camera_world = y_soldiers_world - WINDOW_HEIGTH * 1 / 4 + 150; //offset para que se vea mas centrado

    if (x_camera_world < 0) {
        x_camera_world = 0;
    } else if (x_camera_world > BACKGROUND_WIDTH - WINDOW_WIDTH) {
        x_camera_world = BACKGROUND_WIDTH - WINDOW_WIDTH;
    }

    if (y_camera_world > BACKGROUND_HEIGTH - WINDOW_HEIGTH) {
        y_camera_world = BACKGROUND_HEIGTH - WINDOW_HEIGTH;
    }
    
    ge_holder.update_x(x_camera_world, y_camera_world);

    Area srcAreaRoad(x_camera_world, y_camera_world, WINDOW_WIDTH, WINDOW_HEIGTH);
    Area srcAreaFence(x_camera_world-x_camera_world/8, y_camera_world, WINDOW_WIDTH, WINDOW_HEIGTH);

    Area srcAreaHouses1(x_camera_world-x_camera_world/5, y_camera_world, WINDOW_WIDTH, WINDOW_HEIGTH);
    Area srcAreaHouses2(x_camera_world-x_camera_world/4, y_camera_world, WINDOW_WIDTH, WINDOW_HEIGTH);
    Area srcAreaHouses3(x_camera_world-x_camera_world/3, y_camera_world, WINDOW_WIDTH, WINDOW_HEIGTH);

    Area srcAreaRuins(x_camera_world-x_camera_world/3, y_camera_world, WINDOW_WIDTH, WINDOW_HEIGTH);
    Area srcAreaSky(x_camera_world-x_camera_world/2, y_camera_world, WINDOW_WIDTH, WINDOW_HEIGTH);
    
    window.fill();
    
    background_sky.render(srcAreaSky, destArea, SDL_FLIP_NONE);
    background_ruins.render(srcAreaRuins, destArea, SDL_FLIP_NONE);

    background_houses3.render(srcAreaHouses3, destArea, SDL_FLIP_NONE);
    background_houses2.render(srcAreaHouses2, destArea, SDL_FLIP_NONE);
    background_houses1.render(srcAreaHouses1, destArea, SDL_FLIP_NONE);

    background_fence.render(srcAreaFence, destArea, SDL_FLIP_NONE);
    background_road.render(srcAreaRoad, destArea, SDL_FLIP_NONE);
}

int Camera::get_x_left(){
    return x_camera_world - EXTRA_SCREEN;
}

int Camera::get_x_right(){
    return x_camera_world + WINDOW_WIDTH + EXTRA_SCREEN;
}