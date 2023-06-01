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
    //current_health = new_health;
    std::cout << "current health is " << current_health << std::endl;
    if (current_health > 10)
        current_health = current_health-10;
}

void HealthBar::render() {
    SDL_SetRenderDrawColor(renderer, 67, 2, 7, 255); //darker red for the outer bar
    float total_amount =  300; 
    std::cout << "total_amount is " << total_amount << std::endl;
    SDL_Rect outer_bar = {200, 20, static_cast<int>(total_amount), 10}; // position and size of the outer bar
    SDL_RenderFillRect(renderer, &outer_bar);


    SDL_SetRenderDrawColor(renderer, 107, 4, 14, 255); //dark red for the inside
    //divide the current health by the max health, times the width of the outer_bar to get the percentage of the bar filled
    float amount_filed = (current_health * total_amount) / max_health; 
    std::cout << "amount_filed is " << amount_filed << std::endl;
    SDL_Rect inner_bar = {outer_bar.x, outer_bar.y, static_cast<int>(amount_filed), outer_bar.h};
    SDL_RenderFillRect(renderer, &inner_bar);
    

    SDL_RenderPresent(renderer);
}



HealthBar::~HealthBar() {}