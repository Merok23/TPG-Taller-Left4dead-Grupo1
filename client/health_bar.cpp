#include "health_bar.h"

#include "SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlWindow.h"
#include "SdlException.h"

HealthBar::HealthBar(int32_t max_health, const SdlWindow& window) :
    max_health(max_health), current_health(max_health),
    renderer(window.getRenderer()) {}

void HealthBar::update(int32_t new_health) {
    current_health = new_health;
}

void HealthBar::render() {
    SDL_SetRenderDrawColor(renderer, 107, 4, 14, 255); //dark red
    SDL_Rect rect = {40, 20, 300, 10}; // position and size
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}


HealthBar::~HealthBar() {}