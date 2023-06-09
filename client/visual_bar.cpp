#include "visual_bar.h"

#include "SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlWindow.h"
#include "SdlException.h"

#include <iostream>

VisualBar::VisualBar(int32_t max_value, const SdlWindow& window, Uint8 r_back, Uint8 g_back, Uint8 b_back,
                    Uint8 r_front, Uint8 g_front, Uint8 b_front) :
    max_value(max_value), current_value(max_value),
    r_back(r_back), g_back(g_back), b_back(b_back), r_front(r_front), g_front(g_front), b_front(b_front),
    renderer(window.getRenderer()) {}

void VisualBar::update(int32_t new_health) {
    this->current_value = new_health;
}

void VisualBar::max() {
    current_value = max_value;
}

void VisualBar::render(int x_origin, int y_origin) {
    SDL_SetRenderDrawColor(renderer, r_back, g_back, b_back, 255); //darker red for the outer bar
    float total_amount =  max_value;
    SDL_Rect outer_bar = {x_origin, y_origin, static_cast<int>(total_amount), 10}; // position and size of the outer bar
    SDL_RenderFillRect(renderer, &outer_bar);


    SDL_SetRenderDrawColor(renderer, r_front, g_front, b_front, 255); //dark red for the inside
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //green for testing purposes
    float amount_filled = (current_value * total_amount) / max_value; 
    SDL_Rect inner_bar = {outer_bar.x, outer_bar.y, static_cast<int>(amount_filled), outer_bar.h};
    SDL_RenderFillRect(renderer, &inner_bar);
    

    SDL_RenderPresent(renderer);
}



void VisualBar::damage(int32_t damage) {
    if (damage >= current_value)
        this->current_value  = 0;
    else
        this->current_value  = this->current_value  - damage;
}

int32_t VisualBar::get_health() {
    return this->current_value ;
}


VisualBar::~VisualBar() {}