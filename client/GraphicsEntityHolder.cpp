#include "GraphicsEntityHolder.h"
#include <algorithm>
#include <iostream>

GraphicsEntityHolder::GraphicsEntityHolder(std::shared_ptr<GameState> gs, TexturesHolder texture_holder, SdlWindow &window) :
    window(window), 
    textures_holder(texture_holder) {
    for (auto& pair : gs->entities) {
        if (pair.second->getEntityType() == EntityType::SOLDIER_IDF
        || pair.second->getEntityType() == EntityType::SOLDIER_SCOUT
        || pair.second->getEntityType() == EntityType::SOLDIER_P90) {
            this->MainPlayer = this->createSoldier(pair.second, pair.second->getEntityType());
        } else {
            this->createInfected(pair.second, pair.second->getEntityType());
        }
    }
}

std::shared_ptr<Player> GraphicsEntityHolder::createSoldier(Entity* entity, EntityType entity_type) {
    std::map<AnimationName, std::shared_ptr<SdlTexture>> textures = this->textures_holder.find_textures(entity_type);
    std::shared_ptr<Player> player = std::make_shared<Player>(textures, window, entity->getId(),
                                    entity->getPositionX(),
                                    entity->getPositionY(),
                                    entity->getHitPoints(),
                                    entity->getAmmoLeft(),
                                    entity->getLives());  
        entities[entity->getId()] = player;
        players.push_back(player);
    return player;
}

std::shared_ptr<GraphicsEntity> GraphicsEntityHolder::createInfected(Entity* entity, EntityType type) {
    std::map<AnimationName, std::shared_ptr<SdlTexture>> textures = this->textures_holder.find_textures(type);
        
    std::shared_ptr<GraphicsEntity> infected = std::make_shared<GraphicsEntity>(
                                                textures,
                                                entity->getId(),
                                                entity->getPositionX(),
                                                entity->getPositionY());  
    entities[entity->getId()] = infected;
    return infected;
}


std::shared_ptr<Player> GraphicsEntityHolder::getMainPlayer() {
    return MainPlayer;
}

void GraphicsEntityHolder::get_new_coordenates_center(int32_t *x, int32_t *y) {
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

void GraphicsEntityHolder::update_x(int32_t delta_x) {
    for (size_t i = 0; i < players.size(); ++i) {
        players[i]->update_x(players[i]->getX() + delta_x);
    }
}

void  GraphicsEntityHolder::add_player(Entity* entity) {
    if (entity->getEntityType() == EntityType::SOLDIER_IDF
        || entity->getEntityType() == EntityType::SOLDIER_SCOUT
        || entity->getEntityType() == EntityType::SOLDIER_P90) {
            this->createSoldier(entity, entity->getEntityType());
    } else {
        this->createInfected(entity, entity->getEntityType());
    }
}

void GraphicsEntityHolder::update(float& dt, std::shared_ptr<GameState> gs) {
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
            add_player(pair.second);
        }
    }
}


bool compare_players_by_y(const std::shared_ptr<GraphicsEntity> entity1, 
                            const std::shared_ptr<GraphicsEntity> entity2) {
    return entity1->getY() < entity2->getY();
}


void GraphicsEntityHolder::render(int x_left, int x_right) {
    std::vector<std::shared_ptr<GraphicsEntity>> entities_in_screen;

    for (const auto& pair : entities) {
        //only render entities in the screen's range
        if (x_left <= pair.second->getX() || pair.second->getX() <= x_right)
            entities_in_screen.push_back(pair.second);
    }
    std::sort(entities_in_screen.begin(), entities_in_screen.end(), compare_players_by_y);

    for (const auto& entity : entities_in_screen) {
        entity->render();
    }
}

GraphicsEntityHolder::~GraphicsEntityHolder() {}
