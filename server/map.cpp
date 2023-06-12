#include <utility>

#include "map.h"

Map::Map(uint32_t width, uint32_t height) : 
    width(width),
    height(height),
    entities(),
    soldiers(),
    centre_of_mass(0),
    max_distance_from_centre(CONFIG.soldier_max_distance_from_mass_centre) {}

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

void Map::addSoldier(const uint32_t &id, Movement *soldier) {
    this->soldiers[id] = soldier;
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
    moved = checkForCentreOfMassDistanceCollision(id) && moved;
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
    this->soldiers.erase(id);
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

bool Map::checkForReviving(const uint32_t &id_down, const uint32_t &id_soldier, const int32_t &radius) {
    Movement *down = this->entities[id_down];
    Movement *soldier = this->entities[id_soldier];
    if (down->calculateDistance(*soldier) <= radius) return true;
    return false;
}

int32_t Map::calculateCentreOfMass() {
    int32_t sum = 0;
    for (auto soldier : this->soldiers) {
        sum += soldier.second->getX();
    }
    return sum / this->soldiers.size();
}

bool Map::checkForCentreOfMassDistanceCollision(const uint32_t &id) {
    if (soldiers.find(id) == soldiers.end()) return true;
    centre_of_mass = this->calculateCentreOfMass();
    return !soldiers[id]->movementExceedsDistanceFromX(centre_of_mass, max_distance_from_centre);
}

Map::~Map() {}
