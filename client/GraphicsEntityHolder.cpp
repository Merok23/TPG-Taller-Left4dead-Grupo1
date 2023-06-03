#include "GraphicsEntityHolder.h"
#include <iostream>



GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs, std::map<EntityType, std::map<AnimationName, std::shared_ptr<SdlTexture>>> textures_holder, SdlWindow &window) :
    window(window), textures_holder(std::move(textures_holder))
{
        for (auto& pair : gs->entities) {
            if (pair.second->getType() == "player") {
                auto it = this->textures_holder.find(SOLDIER_IDF);
                if (pair.second->getWeaponType() == "scout")
                    it = this->textures_holder.find(SOLDIER_SCOUT);
                else if (pair.second->getWeaponType() == "p90")
                    it = this->textures_holder.find(SOLDIER_P90);
                    
                std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            it->second,
                                                            window,
                                                            pair.second->getId(),
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

std::shared_ptr<Player> GraphicsEntityHolder::add_player(Entity *entity) {
    //tengo que crear un nuevo elemento con la data que me pasaron.
    auto it = this->textures_holder.find(SOLDIER_IDF);
    std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            it->second, //por ahora, que compartan texturas
                                                            window,
                                                            entity->getId(),
                                                            entity->getPositionX(),
                                                            entity->getPositionY(),
                                                            entity->getHitPoints());  
    entities[entity->getId()] = player;
    return player;
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
            std::shared_ptr<Player> player = add_player(pair.second);
            player->update(dt, NULL);
        }
    }
}

void GraphicsEntityHolder::render() {
    for (const auto& pair : entities)
        pair.second->render();
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}
