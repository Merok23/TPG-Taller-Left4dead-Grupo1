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

std::tuple<int, int> Map::getSurvivalModeSpawnPoint(const int &radius) {
    int middle = this->width / 2;
    return this->searchForSpawnPoint(middle, this->max_distance_from_centre, radius);
}

std::tuple<int, int> Map::getClearTheZoneSpawnPoint(const int &radius) {
    return this->searchForSpawnPoint(this->max_distance_from_centre * 2, this->max_distance_from_centre, radius);
}

std::tuple<int, int> Map::getCentreOfMassSpawnPoint(const int &radius) {
    int middle = this->calculateCentreOfMass();
    return this->searchForSpawnPoint(middle, this->max_distance_from_centre, radius);
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

int32_t Map::getCentreOfMass() {
    return this->centre_of_mass;
}

std::tuple<int, int> Map::searchForSpawnPoint(
    const int &middle, 
    const int &allowed_distance_from_middle, 
    const int &radius) {
    std::tuple<int, int> final_position;
    bool found = false;
    int start = middle - allowed_distance_from_middle;
    while (!found) {
        int x = rand() % (start);
        x += (start);
        int y = rand() % (this->height - 2 * radius);
        y += radius;
        if (!this->checkForCollisionInPosition(x, y, radius)) {
            final_position = std::make_tuple(x, y);
            found = true;
        }
    }
    return final_position;

}

bool Map::isEntityLookingAtAllignedAndInRange(const uint32_t &id, const uint32_t &id_target, const int32_t &range) {
    Movement *entity = this->entities[id];
    Movement *target = this->entities[id_target];
    //looking at
    if (entity->isLookingAt(*target)) {
        //alligned
        if (entity->isAligned(*target, this->height)) {
            //and in range
            int32_t distance = entity->calculateDistance(*target);
            return distance <= range;
        }
    }
    return false;
}

bool Map::isOutOfBoundaries(Movement &movement) {
    if (movement.getX() < 0 || movement.getX() > this->width) return true;
    if (movement.getY() < 0 || movement.getY() > this->height) return true;
    return false;
}

bool Map::checkForCentreOfMassDistanceCollision(const uint32_t &id) {
    if (soldiers.find(id) == soldiers.end()) return true;
    centre_of_mass = this->calculateCentreOfMass();
    return !soldiers[id]->movementExceedsDistanceFromX(centre_of_mass, max_distance_from_centre);
}

Map::~Map() {}
