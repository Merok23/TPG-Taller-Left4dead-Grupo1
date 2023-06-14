#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include <cstdint>
#include <map>
#include <vector>
#include <utility>

#include "movement.h"
#include "vector_wrapper.h"
# pragma once

class Map {
    private:
        uint32_t width;
        uint32_t height;
        std::map<uint32_t, Movement*> entities;
        std::map<uint32_t, Movement*> soldiers;
        int32_t centre_of_mass;
        double max_distance_from_centre;
    public:
        Map(uint32_t width, uint32_t height);
        uint32_t getWidth();
        uint32_t getHeight();
        std::tuple<int, int> getSurvivalModeSpawnPoint(const int &radius);
        std::tuple<int, int> getClearTheZoneSpawnPoint(const int &radius);
        std::tuple<int, int> getCentreOfMassSpawnPoint(const int &radius);
        std::map<uint32_t, Movement*> getEntities();
        bool move(const uint32_t &id);
        std::vector<VectorWrapper> shoot(uint32_t id);
        void addEntity(const uint32_t &id, Movement *entity);
        void addSoldier(const uint32_t &id, Movement *soldier);
        bool checkForCollisionInPosition(const uint32_t &x, const uint32_t &y, const uint32_t &radius);
        bool checkForReviving(const uint32_t &id_down, const uint32_t &id_soldier, const int32_t &radius);
        void removeEntity(const uint32_t &id);
        ~Map();
    private:
        std::tuple<int, int> searchForSpawnPoint(const int &middle, 
                                                const int &allowed_distance_from_middle, 
                                                const int &radius);
        //intentionally recieves a copy
        bool checkForCentreOfMassDistanceCollision(const uint32_t &id);
        bool checkForBorderCollision(Movement entity);
        bool moveClosestToBorder(Movement *entity);
        int32_t calculateCentreOfMass();
        //bool makeBestMovement(Movement *entity, Movement *other_entity);
};
#endif
