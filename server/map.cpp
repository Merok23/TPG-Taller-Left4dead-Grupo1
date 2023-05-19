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
    if (checkForBorderCollision(*entity)) return false;
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
    return moved;
}

std::vector<VectorWrapper> Map::shoot(uint32_t id) {
    std::vector<VectorWrapper> aligned_entitites;
    for (auto entity : this->entities) {
        if (entity.first != id) {
            if (this->entities[id]->isLookingAt(*entity.second)){
                if (this->entities[id]->isAligned(*entity.second, this->height)) {
                    VectorWrapper element(entity.first, entity.second->calculateDistance(*this->entities[id]));
                    aligned_entitites.push_back(element);
                }
            }
        }
    }
    return aligned_entitites;
}

//Only checks for y axis because x should loop (map is a torus)
//X THING NOT IMPLEMENTED!!!!
//the problem with that is that the movement is done in the entity
//and only the map know the width of the map, maybe the entity should
//have a special method to jump the x axis to the origin.
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

Map::~Map() {}
