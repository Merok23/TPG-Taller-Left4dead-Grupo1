#include "hit_entity.h"

HitEntity::HitEntity(Entity* entity, uint32_t distance) : 
    entity(entity),
    distance(distance) {}

Entity* HitEntity::getEntity() {
    return this->entity;
}

uint32_t HitEntity::getDistance() {
    return this->distance;
}

HitEntity::~HitEntity() {}
