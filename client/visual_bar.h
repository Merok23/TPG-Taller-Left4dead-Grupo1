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
    VisualBar(int32_t max_value, const SdlWindow& window, Uint8 r_back, Uint8 g_back, Uint8 b_back,
                Uint8 r_front, Uint8 g_front, Uint8 b_front);
    void update(int32_t new_value);
    void render(int x_origin, int y_origin);
    ~VisualBar();

   private:
    int32_t max_value;
    int32_t current_value;
    Uint8 r_back;
    Uint8 g_back; 
    Uint8 b_back; //for the bar behind your actual value
    Uint8 r_front;
    Uint8 g_front; 
    Uint8 b_front; //for the bar with your actual value
    SDL_Renderer* renderer;
};

#endif  //_VISUALBAR_H_
