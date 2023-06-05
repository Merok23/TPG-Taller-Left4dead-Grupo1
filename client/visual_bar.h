#ifndef _VISUALBAR_H_
#define _VISUALBAR_H_


#include <memory>
#include "SdlException.h"
#include "SdlWindow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDL_Renderer;

class VisualBar {
   public:
    VisualBar(int32_t max_health, const SdlWindow& window);
    int32_t get_health();
    void damage(int32_t damage);
    void max();
    void update(int32_t current_health);
    void render(int x_origin, int y_origin);
    ~VisualBar();

   private:
    int32_t max_health;
    int32_t current_health;
    SDL_Renderer* renderer;
};

#endif  //_VISUALBAR_H_
