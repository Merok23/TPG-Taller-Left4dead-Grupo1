#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "GraphicsEntityHolder.h"

#include <yaml-cpp/yaml.h>
#define DEFAULT_PATH_FROM_EXECUTABLE_TO_CONFIG "../../client/client_config.yaml"


#define BACKGROUND_WIDTH 7680
#define BACKGROUND_HEIGTH 1080

#define WINDOW_WIDTH (1590)
#define WINDOW_HEIGTH (1080-200)

#define EXTRA_SCREEN 200

class Camera {
    public:
    explicit Camera(SdlWindow &window, int main_player_x, int main_player_y);

    void render(GraphicsEntityHolder &ge_holder);
    int get_x_left();
    int get_x_right();

    private:
    void set_up_background();

    SdlWindow &window;
    YAML::Node config;

    std::unique_ptr<SdlTexture> background_sky;
    std::unique_ptr<SdlTexture> background_houses1;
    std::unique_ptr<SdlTexture> background_houses2;
    std::unique_ptr<SdlTexture> background_houses3;
    std::unique_ptr<SdlTexture> background_ruins;
    std::unique_ptr<SdlTexture> background_fence;
    std::unique_ptr<SdlTexture> background_road;
    
    Area destArea;
    int x_camera_world;
    int y_camera_world;
};

#endif //__CAMERA_H__
