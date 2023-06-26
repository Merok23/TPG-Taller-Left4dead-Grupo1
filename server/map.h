#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include <cstdint>
#include <map>
#include <vector>
#include <utility>

#include "movement.h"
#include "vector_wrapper.h"
# pragma once

/**
 * @class Map
 * @brief Has all the collision and movement logic  
 */
class Map {
    private:
        int32_t width; /**< Width of the map. */
        int32_t height; /**< Height of the map. */
        std::map<uint32_t, Movement*> entities; /**< Movement of all entities. */
        std::map<uint32_t, Movement*> soldiers; /**< Movement of soldiers only. */
        int32_t centre_of_mass; /**< Centre of mass of the soldiers. */
        double max_distance_from_centre; /**< Max distance soldiers can move from centre of mass. */
    public:
        /**
         * @brief Constructor
         * @param width Width of the map.
         * @param height Height of the map.
         */
        Map(uint32_t width, uint32_t height);

        /**
         * @brief Gets the width of the map.
         * @returns Width of the map.
         */
        uint32_t getWidth();

        /**
         * @brief Gets the height of the map.
         * @returns Height of the map.
         */
        uint32_t getHeight();

        /**
         * @brief used for when you need a spawn point in survival mode (middle of the map)
         * @param radius radius of the entity.
         * @returns a tuple with the x and y coordinates of the spawn point.
         */
        std::tuple<int, int> getSurvivalModeSpawnPoint(const int &radius);

        /**
         * @brief used for when you need a spawn point in clear the zone mode (start of the map)
         * @param radius radius of the entity.
         * @returns a tuple with the x and y coordinates of the spawn point.
         */
        std::tuple<int, int> getClearTheZoneSpawnPoint(const int &radius);

        /**
         * @brief used for when you need a spawn point near the centre of mass of the soldiers.
         * @param radius radius of the entity.
         * @returns a tuple with the x and y coordinates of the spawn point.
         */
        std::tuple<int, int> getCentreOfMassSpawnPoint(const int &radius);

        /**
         * @brief Gets the current centre of mass. 
         * @returns the current centre of mass. 
         */
        int32_t getCentreOfMass();

        /**
         * @brief Gets the map of entities(not used I think)
         * @returns the map of entities. 
         */
        std::map<uint32_t, Movement*> getEntities();

        /**
         * @brief Tries to move the id given.
         * @param id id of the entity to move.
         * @returns true if the entity was moved, false otherwise. 
         */
        bool move(const uint32_t &id);

        /**
         * @brief Used for when you need to shoot with a soldier.
         * @param id id of the soldier.
         * @returns a vector of VectorWrappers with the id of the entity and the distance to the soldier. 
         */
        std::vector<VectorWrapper> shoot(uint32_t id);

        /**
         * @brief adds a new entity to the map.
         * @param id id of the entity.
         * @param entity pointer to the entity's movement.  
         */
        void addEntity(const uint32_t &id, Movement *entity);

        /**
         * @brief adds a new soldier to the map.
         * @param id id of the soldier.
         * @param soldier pointer to the soldier's movement. 
         */
        void addSoldier(const uint32_t &id, Movement *soldier);

        /**
         * @brief Checks if there is a collision in the position given.
         * @param x x coordinate of the position.
         * @param y y coordinate of the position.
         * @param radius radius of the entity.
         * @returns true if there is a collision, false otherwise. 
         */
        bool checkForCollisionInPosition(const uint32_t &x, const uint32_t &y, const uint32_t &radius);

        /**
         * @brief Checks id_soldier can revive id_down.
         * @param id_down id of the entity that is down.
         * @param id_soldier id of the soldier.
         * @param radius radius of the soldier.
         * @returns true if id_soldier can revive id_down, false otherwise.
         */
        bool checkForReviving(const uint32_t &id_down, const uint32_t &id_soldier, const int32_t &radius);

        /**
         * @brief Removes given id from the map.
         * @param id id of the entity to remove. 
         */
        void removeEntity(const uint32_t &id);

        /**
         * @brief Checks if given id is looking, it's allinged and in range with target id.
         * @param id id of the entity.
         * @param id_target id of the target.
         * @param range range of the entity.
         * @returns true if id is looking, it's allinged and in range with target id, false otherwise.
         */
        bool isEntityLookingAtAllignedAndInRange(const uint32_t &id, const uint32_t &id_target, const int32_t &range);

        /**
         * @brief Checks if given movement is outside of the map boundaries.
         * @param movement movement of the entity.
         * @returns true if given movement is outside of the map boundaries, false otherwise. 
         */
        bool isOutOfBoundaries(Movement &movement);
        ~Map();
    private:

        /**
         * @brief Searchs for a spawn point in the position given, with max distance given.
         * @param middle middle of the map.
         * @param allowed_distance_from_middle max distance from the middle of the map. 
         */
        std::tuple<int, int> searchForSpawnPoint(const int &middle, 
                                                const int &allowed_distance_from_middle, 
                                                const int &radius);

        /**
         * @brief Checks if the given id is collisioning with the borders of the centre of the mass.
         * @param id id of the entity.
         * @returns true if the given id is collisioning, false otherwise. 
         */
        bool checkForCentreOfMassDistanceCollision(const uint32_t &id);
        /**
         * @brief Checks if the next movement of the entity
         *        will cause a collision with the borders of the map.(when it moves.)
         * @param entity entity to check.
         * @returns true if the next movement of the entity
         */
        //intentionally recieves a copy
        bool checkForBorderCollision(Movement entity);

        /**
         * @brief Moves the entity closest to the border of the map as it can.
         * @param entity entity to move.
         * @returns true if the entity was moved, false otherwise. 
         */
        bool moveClosestToBorder(Movement *entity);

        /**
         * @brief Calculates the centre of mass of the soldiers.
         * @returns the centre of mass of the soldiers. 
         */
        int32_t calculateCentreOfMass();
        //bool makeBestMovement(Movement *entity, Movement *other_entity);
};
#endif
