#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "GraphicsEntityHolder.h"

#define BACKGROUND_WIDTH 7680
#define BACKGROUND_HEIGTH 1080

#define WINDOW_WIDTH (1590)
#define WINDOW_HEIGTH (1080-200)

#define EXTRA_SCREEN 200
#define TRANSITION_MARGIN 5

class Camera {
    public:
    explicit Camera(SdlWindow &window, int main_player_x, int main_player_y);

    void render(GraphicsEntityHolder &ge_holder);
    int get_x_left();
    int get_x_right();

    private:
    SdlWindow &window;

    SdlTexture background_sky;
    SdlTexture background_houses1;
    SdlTexture background_houses2;
    SdlTexture background_houses3;
    SdlTexture background_ruins;
    SdlTexture background_fence;
    SdlTexture background_road;
    
    Area destArea;
    int x_camera_world;
    int y_camera_world;
};

#endif //__CAMERA_H__
