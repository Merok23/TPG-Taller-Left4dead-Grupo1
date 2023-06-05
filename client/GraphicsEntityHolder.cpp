#include "GraphicsEntityHolder.h"
#include <iostream>

GraphicsEntityHolder::GraphicsEntityHolder(GameState *gs,  TexturesHolder textures_holder, SdlWindow &window) :
    window(window), textures_holder(std::move(textures_holder))
{
        for (auto& pair : gs->entities) {
            if (pair.second->getType() == "player") {
                std::map<AnimationName, std::shared_ptr<SdlTexture>> textures = this->textures_holder.find_textures(SOLDIER_IDF);
                if (pair.second->getWeaponType() == "scout")
                    textures = this->textures_holder.find_textures(SOLDIER_SCOUT);
                else if (pair.second->getWeaponType() == "p90")
                    textures = this->textures_holder.find_textures(SOLDIER_P90);
                
                std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            textures,
                                                            window,
                                                            pair.second->getId(),
                                                            pair.second->getPositionX(),
                                                            pair.second->getPositionY(),
                                                            pair.second->getHitPoints());  
                entities[pair.second->getId()] = player;
                players[pair.second->getId()] = player;
                MainPlayer = player;
            }
        }
    }

std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

std::shared_ptr<Player> GraphicsEntityHolder::add_player(Entity *entity) {
    //por ahora solo me envian players, no infectados
    std::map<AnimationName, std::shared_ptr<SdlTexture>> textures = this->textures_holder.find_textures(SOLDIER_IDF);
    if (entity->getWeaponType() == "scout")
        textures = this->textures_holder.find_textures(SOLDIER_SCOUT);
    else if (entity->getWeaponType() == "p90")
        textures = this->textures_holder.find_textures(SOLDIER_P90);

    std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            textures,
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
