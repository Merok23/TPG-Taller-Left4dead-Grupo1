#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SdlWindow.h"
#include "SdlTexture.h"

#define BACKGROUND_WIDTH 1920
#define BACKGROUND_HEIGTH 1080


#define WINDOW_WIDTH (1920-400)
#define WINDOW_HEIGTH (1080-200)

class Camera {
    public:
    Camera(SdlWindow &window);


    void render(size_t &x, size_t &y);

    private:
    SdlWindow &window;
    SdlTexture background;
    Area destArea;
};

#endif //__CAMERA_H__
