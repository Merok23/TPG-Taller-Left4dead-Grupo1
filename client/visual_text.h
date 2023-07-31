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
    SDL_Renderer* renderer;
};

#endif  //_VISUALTEXT_H_
