#ifndef _VISUALTEXT_H_
#define _VISUALTEXT_H_


#include <memory>
#include <string>
#include "SdlException.h"
#include "SdlWindow.h"

#include <yaml-cpp/yaml.h>
#define DEFAULT_PATH_FROM_EXECUTABLE_TO_CONFIG "../../client/client_config.yaml"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SDL_Renderer;

class VisualText {
   public:
    VisualText(std::string text, const SdlWindow& window);
    void render(int x_origin, int y_origin);
    ~VisualText();

   private:
    std::string text;
    TTF_Font* font;
    TTF_Font* font_border;
    SDL_Renderer* renderer;
    YAML::Node config;

    SDL_Texture* insideTexture;
    SDL_Texture* borderTexture;

    SDL_Rect textRect;
    SDL_Rect borderRect;

    int textWidth;
    int textHeight;
    int borderWidth;
    int borderHeight;
};

#endif  //_VISUALTEXT_H_
