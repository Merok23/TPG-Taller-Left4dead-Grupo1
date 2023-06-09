#ifndef CLIENT_ENTITY_H
#define CLIENT_ENTITY_H
#include <cstdint>
#include <functional>
#include <string>
#include "client_enum.h"

class Entity {
    private:
        uint32_t id;
        EntityTypeGS type;
        uint8_t lives;
        WeaponType weapon_type; //para la textura
        int32_t ammo_left; //para la cantidad de balas
        int32_t hit_points;
        int32_t x_position;
        int32_t y_position;
        bool is_facing_left;
        bool is_moving_up;

        
    public:


        State state;


        Entity(uint32_t id, EntityTypeGS type, State state, uint8_t lives, WeaponType weapon_type, int32_t ammo_left,  int32_t hit_points, 
            uint32_t x, uint32_t y, bool facing_left, bool moving_up);
        Entity(uint32_t id, EntityTypeGS type, State state,  int32_t hit_points, 
            uint32_t x, uint32_t y, bool facing_left, bool moving_up);
        uint32_t getId();
        int32_t getHitPoints();
        std::string getType(); 
        EntityTypeGS getEntityType();
        WeaponType getWeaponType();
        std::string getWeapon();
        int32_t getAmmoLeft();
        std::string getStateEnum();
        State getState();
        uint8_t getLives();
        int32_t getPositionX();
        int32_t getPositionY();
        bool isFacingLeft();
        bool isMovingUp();
};
#endif