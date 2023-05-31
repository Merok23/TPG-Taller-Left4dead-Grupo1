#include "GraphicsEntityHolder.h"
#include <iostream>

GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs, std::map<AnimationName, std::shared_ptr<SdlTexture>> textures) {
        for (auto& pair : gs->entities) {
            if (pair.second->getType() == "player") {
                std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            std::move(textures),
                                                            pair.second->getPositionX(),
                                                            pair.second->getPositionY(),
                                                            pair.second->getHitPoints());  
                entities[pair.second->getId()] = player;
                MainPlayer = player;
            }
        }
    }

std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

void GraphicsEntityHolder::update(float& dt, GameState *gs) {
    //MainPlayer->update(dt);
    for (const auto& pair : entities) {
        pair.second->update(dt);
    }
        
}

void GraphicsEntityHolder::render() {
    //MainPlayer->render();
    for (const auto& pair : entities)
        pair.second->render();
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}