#include "visual_bar.h"

#include "SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlWindow.h"
#include "SdlException.h"

#include <iostream>

VisualBar::VisualBar(int32_t max_health, const SdlWindow& window) :
    max_health(max_health), current_health(max_health),
    renderer(window.getRenderer()) {}

void VisualBar::update(int32_t new_health) {
    this->current_health = new_health;
}

void VisualBar::max() {
    current_health = max_health;
}

void VisualBar::render(int x_origin, int y_origin) {
    SDL_SetRenderDrawColor(renderer, 67, 2, 7, 255); //darker red for the outer bar
    float total_amount =  max_health;
    SDL_Rect outer_bar = {x_origin, y_origin, static_cast<int>(total_amount), 10}; // position and size of the outer bar
    SDL_RenderFillRect(renderer, &outer_bar);


    //SDL_SetRenderDrawColor(renderer, 107, 4, 14, 255); //dark red for the inside
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //green for testing purposes
    float amount_filled = (current_health * total_amount) / max_health; 
    SDL_Rect inner_bar = {outer_bar.x, outer_bar.y, static_cast<int>(amount_filled), outer_bar.h};
    SDL_RenderFillRect(renderer, &inner_bar);
    

    SDL_RenderPresent(renderer);
}



void VisualBar::damage(int32_t damage) {
    if (damage >= current_health)
        this->current_health  = 0;
    else
        this->current_health  = this->current_health  - damage;
}

int32_t VisualBar::get_health() {
    return this->current_health ;
}


VisualBar::~VisualBar() {}