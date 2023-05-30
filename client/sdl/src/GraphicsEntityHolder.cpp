#include "GraphicsEntityHolder.h"

GraphicsEntityHolder::GraphicsEntityHolder(std::map<AnimationName, SdlTexture *> textures) :
    MainPlayer(new Player(std::move(textures))){}

std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

GraphicsEntityHolder::~GraphicsEntityHolder() {

}