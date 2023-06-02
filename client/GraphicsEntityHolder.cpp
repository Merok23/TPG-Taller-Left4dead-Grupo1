#include "GraphicsEntityHolder.h"
#include <iostream>

GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs, std::map<AnimationName, std::shared_ptr<SdlTexture>> textures, SdlWindow &window) :
    window(window), textures(std::move(textures))
{
        for (auto& pair : gs->entities) {
            if (pair.second->getType() == "player") {
                std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            this->textures,
                                                            window,
                                                            pair.second->getId(),
                                                            pair.second->getPositionX(),
                                                            pair.second->getPositionY(),
                                                            pair.second->getHitPoints());  
                entities[pair.second->getId()] = player;
            }
        }
    }

// std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
//     //return MainPlayer;
// }

void GraphicsEntityHolder::add_entity(Entity *entity) {
    //tengo que crear un nuevo elemento con la data que me pasaron.
    std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            this->textures, //por ahora, que compartan texturas
                                                            window,
                                                            entity->getId(),
                                                            entity->getPositionX(),
                                                            entity->getPositionY(),
                                                            entity->getHitPoints());  
    entities[entity->getId()] = player;
}

void GraphicsEntityHolder::update(float& dt, GameState *gs) {
    
    for (const auto &pair : this->entities) {
        uint32_t this_id = pair.second->getId();
        
        if (gs != NULL) {
            auto it_gs_entity = gs->entities.find(this_id);

            if (it_gs_entity != gs->entities.end()) {
                gs->entities.erase(this_id);
                pair.second->update(dt, it_gs_entity->second);
            } else {
                pair.second->update(dt, NULL);
            }
        } else {
            pair.second->update(dt, NULL);
        } 
    }

    if (gs != NULL) {
        for (const auto &pair : gs->entities) {
            add_entity(pair.second);
        }
    }
}

void GraphicsEntityHolder::render() {
    for (const auto& pair : entities)
        pair.second->render();
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}
