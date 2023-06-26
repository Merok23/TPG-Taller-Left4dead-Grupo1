#ifndef SERVER_HIT_ENTITY_H
#define SERVER_HIT_ENTITY_H

#include <cstdint>
#pragma once

class Entity;

/**
 * @class HitEntity, a wrapper for having a vector of entities and their distance from a point 
 */
class HitEntity {
    private:
        Entity* entity;
        uint32_t distance;
    public:
        HitEntity(Entity* entity, uint32_t distance);
        void setEntity(Entity* entity);
        void setDistance(uint32_t &distance);
        Entity* getEntity();
        uint32_t getDistance();
        ~HitEntity();
};
#endif
