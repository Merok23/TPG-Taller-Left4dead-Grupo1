#include <utility>

#include "map.h"

Map::Map(uint32_t width, uint32_t height) : 
    width(width),
    height(height),
    entities() {}

uint32_t Map::getWidth() {
    return this->width;
}

uint32_t Map::getHeight() {
    return this->height;
}

std::map<uint32_t, Movement*> Map::getEntities() {
    return this->entities;
}

void Map::addEntity(const uint32_t &id, Movement *entity) {
    this->entities[id] = entity;
}

bool Map::move(const uint32_t& id) {
    bool moved = true;
    Movement *entity = this->entities[id];
    if (checkForBorderCollision(*entity)) return moveClosestToBorder(entity);
    for (auto mapEntity : entities) {
        if (mapEntity.first != id) {
            if (entity->checkForCollision(*mapEntity.second)) {
                moved = false;
                break;
            }
        }
    }
    if (moved) {
        entity->move();
    }
    int64_t signed_width = this->width;
    if (entity->getX() > signed_width) {
        entity->setX(entity->getX() - signed_width);
    } else if (entity->getX() < 0) {
        entity->setX(signed_width + entity->getX());
    }
    return moved;
}


bool Map::moveClosestToBorder(Movement *entity) {
    Movement copy = *entity;
    int32_t initial_y = copy.getY();
    copy.move();
    int32_t y = copy.getY();
    int32_t radius = entity->getRadius();
    int64_t signed_height = this->height;
    if (y - radius < 0) {
        entity->setY(radius);
    } else if (y + radius > signed_height) {
        entity->setY(signed_height - radius);
    }
    return (initial_y != entity->getY());
}

std::vector<VectorWrapper> Map::shoot(uint32_t id) {
    std::vector<VectorWrapper> aligned_entitites;
    for (auto entity : this->entities) {
        if (entity.first != id) {
            if (this->entities[id]->isLookingAt(*entity.second)){
                if (this->entities[id]->isAligned(*entity.second, this->height)) {
                    VectorWrapper element(entity.first,    
                        entity.second->calculateDistance(*this->entities[id]));
                            aligned_entitites.push_back(element);
                }
            }
        }
    }
    return aligned_entitites;
}

bool Map::checkForBorderCollision(Movement entity) {
    entity.move();
    int64_t y = entity.getY();
    int64_t radius = entity.getRadius();
    int64_t difference = y - radius;
    if (difference < 0) return true;
    if (y + radius > this->height) return true;
    return false;
}

void Map::removeEntity(const uint32_t &id) {
    this->entities.erase(id);
}

bool Map::checkForCollisionInPosition(const uint32_t &x, const uint32_t &y, const uint32_t &radius) {
    Movement entity(x, y, radius);
    for (auto entity_map : this->entities) {
        if (entity_map.second->checkForCollision(entity)) {
            return true;
        }
    }
    return false;
}

Map::~Map() {}
