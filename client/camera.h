#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "GraphicsEntityHolder.h"

#define BACKGROUND_WIDTH 1920
#define BACKGROUND_HEIGTH 1080

#define WINDOW_WIDTH (1920-400)
#define WINDOW_HEIGTH (1080-200)

#define EXTRA_SCREEN 200
#define TRANSITION_MARGIN 5

class Camera {
    public:
    Camera(SdlWindow &window);

    void render(GraphicsEntityHolder &ge_holder);
    int get_x_left();
    int get_x_right();

    private:
    SdlWindow &window;
    SdlTexture background;
    Area destArea;
    int x_camera_world;
};

#endif //__CAMERA_H__
