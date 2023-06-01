/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Area.h"
#include "Animation.h"
#include "SdlTexture.h"

#include <iostream>

Animation::Animation(const std::shared_ptr<SdlTexture> texture) : texture(texture), currentFrame(0),
                                                  numFrames(this->texture->getWidth() / this->texture->getHeight()),
                                                  size(this->texture->getHeight()), elapsed(0.0f),
                                                  amountAnimationsMade(0) {
    assert(this->numFrames > 0);
    assert(this->size > 0);
}

Animation::~Animation() {}

bool Animation::amountPlayed() {
    return amountAnimationsMade;
}


void Animation::update(float dt) {
    this->elapsed += dt;
    /* checks if the frame should be updated based on the time elapsed since the last update */
    while (this->elapsed > FRAME_RATE) {
        this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
    if (currentFrame+1 == numFrames)
        amountAnimationsMade++;
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void Animation::render(const Area &dst, const SDL_RendererFlip &flipType) {
    Area src(1 + (1 + this->size) * this->currentFrame, 0, this->size, this->size);
    this->texture->render(src, dst, flipType);
}

void Animation::advanceFrame() {
    this->currentFrame += 1;
    this->currentFrame = this->currentFrame % this->numFrames; 
}
