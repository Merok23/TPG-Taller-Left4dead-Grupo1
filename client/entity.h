#ifndef CLIENT_ENTITY_H
#define CLIENT_ENTITY_H
#include <cstdint>
#include <functional>
#include <string>


enum State {
    IDLE,
    RUN,
    SHOOT,
    RELOAD, 
    DIE
}; //Abril tendria que agregar el estado de reload

class Entity {
    private:
        uint32_t id;
        std::string type;
        State state;
        std::string weapon_type; //para la textura
        int32_t ammo_left; //para la cantidad de balas
        int32_t hit_points;
        int32_t x_position;
        int32_t y_position;
        bool is_facing_left;
        bool is_moving_up;

        
    public:
        Entity(uint32_t id, const std::string& type, State state, const std::string& weapon_type, int32_t ammo_left,  int32_t hit_points, 
            uint32_t x, uint32_t y, bool facing_left, bool moving_up);
        uint32_t getId();
        int32_t getHitPoints();
        std::string getType(); 
        std::string getWeaponType();
        int32_t getAmmoLeft();
        std::string getState();
        int32_t getPositionX();
        int32_t getPositionY();
        bool isFacingLeft();
        bool isMovingUp();
};
#endif