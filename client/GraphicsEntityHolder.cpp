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
                players.push_back(player);
                MainPlayer = player;
            } else {
                std::map<AnimationName, std::shared_ptr<SdlTexture>> textures = this->textures_holder.find_textures(ZOMBIE);
                
                std::shared_ptr<Player> player = std::make_shared<Player>(
                                                            textures,
                                                            window,
                                                            pair.second->getId(),
                                                            pair.second->getPositionX(),
                                                            pair.second->getPositionY(),
                                                            pair.second->getHitPoints());  
                entities[pair.second->getId()] = player;
            }
        }
    }

std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

void GraphicsEntityHolder::get_new_coordenates_center(size_t *x, size_t *y) {
    size_t x_total = 0;
    size_t y_total = 0;
    size_t i;
    for (i = 0; i < players.size(); ++i) {
        x_total += players[i]->getX();
        y_total += players[i]->getY();
    }

    *x = x_total / i;
    *y = y_total / i;
}
int i = 0;
std::shared_ptr<Player> GraphicsEntityHolder::add_player(Entity *entity) {
    if (entity->getType() == "player") {
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
        players.push_back(player);
        return player;
    } else if (i <= 1) {
        std::cout << "Me piden agregar un infectado" << std::endl;
        std::map<AnimationName, std::shared_ptr<SdlTexture>> textures = this->textures_holder.find_textures(ZOMBIE);
        
        std::shared_ptr<Player> player = std::make_shared<Player>(
                                                    textures,
                                                    window,
                                                    entity->getId(),
                                                    entity->getPositionX(),
                                                    entity->getPositionY(),
                                                    entity->getHitPoints());  
        entities[entity->getId()] = player;
        i++;
        return player;
    }
    return NULL;
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
            if (player)
                player->update(dt, NULL);
        }
    }
}

void GraphicsEntityHolder::render() {
    for (const auto& pair : entities) {
        pair.second->render();
        //pair.second->get_ammo().render(50, 300); //dependiendo de donde renderizo, titilan los demas que fueron renderizados en el mismo scope
        //pair.second->get_health_bar().render(50, 200);
    }
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}
