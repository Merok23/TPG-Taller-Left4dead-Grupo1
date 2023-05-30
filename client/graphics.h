#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>

#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Animation.h"

#include <map>

#include "GraphicsEntityHolder.h"
#include "game_state.h"

#define BACKGROUND_WIDTH 1920
#define BACKGROUND_HEIGTH 1080

#define CAMARA_START_X 300
#define CAMARA_WIDTH 1320 //300 pixels to the left and 300 pixels to the right start hidden
#define CAMARA_MAX_X 1920-CAMARA_WIDTH

#define SCROLL_THREASHOLD 350

class Graphics {
    public:
    void run(GameState *gs);

    private:
    bool handleEvents(GraphicsEntityHolder &gr_entity_holder);
    void render(SdlWindow &window, GraphicsEntityHolder &gr_entity_holder, SdlTexture &im, Area &destArea);
    void update(GraphicsEntityHolder &gr_entity_holder, float dt);

};

#endif // __GRAPHICS_H__
