#include "health_bar.h"

#include "SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "SdlWindow.h"
#include "SdlException.h"

#include <iostream>

HealthBar::HealthBar(int32_t max_health, const SdlWindow& window) :
    max_health(max_health), current_health(max_health),
    renderer(window.getRenderer()) {}

void HealthBar::update(int32_t new_health) {
    // this->current_health = new_health;
}

void HealthBar::render() {
    SDL_SetRenderDrawColor(renderer, 67, 2, 7, 255); //darker red for the outer bar
    float total_amount =  max_health * 5; 
    std::cout << "total_amount is " << total_amount << std::endl;
    SDL_Rect outer_bar = {200, 20, static_cast<int>(total_amount), 10}; // position and size of the outer bar
    SDL_RenderFillRect(renderer, &outer_bar);


    SDL_SetRenderDrawColor(renderer, 107, 4, 14, 255); //dark red for the inside
    //divide the current health by the max health, times the width of the outer_bar to get the percentage of the bar filled
    float amount_filled = (current_health * total_amount) / max_health; 
    std::cout << "A punto de calcular amount_filled. current_health vale " << current_health << " y amount_filled es " << amount_filled << std::endl;
    SDL_Rect inner_bar = {outer_bar.x, outer_bar.y, static_cast<int>(amount_filled), outer_bar.h};
    SDL_RenderFillRect(renderer, &inner_bar);
    

    SDL_RenderPresent(renderer);
}



void HealthBar::damage(int32_t damage) {
    std::cout << "Estoy en damage. current_health es " << current_health << std::endl;
    if (damage >= current_health)
        this->current_health  = 0;
    else
        this->current_health  = this->current_health  - damage;
    
    std::cout << "Ya pegue. Ahora current_health es " << current_health << std::endl;
}

int32_t HealthBar::get_health() {
    return this->current_health ;
}


HealthBar::~HealthBar() {}