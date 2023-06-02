#ifndef __HEALTHBAR_H_
#define __HEALTHBAR_H_


#include <memory>
#include "SdlException.h"
#include "SdlWindow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDL_Renderer;

class HealthBar {
   public:
    HealthBar(int32_t max_health, const SdlWindow& window);
    int32_t get_health();
    void damage(int32_t damage);
    void update(int32_t current_health);
    void render(int x_origin, int y_origin);
    ~HealthBar();

   private:
    int32_t max_health;
    int32_t current_health;
    SDL_Renderer* renderer;
};

#endif  //__HEALTHBAR_H_
