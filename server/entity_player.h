#ifndef SERVER_ENTITY_PLAYER_H
#define SERVER_ENTITY_PLAYER_H

#include <vector>
#include <string>
#include <utility>

#include "entity.h"
#include "movement.h"
#include "config.h"

enum SoldierState {
    IDLE_SOLDIER,
    MOVING_SOLDIER,
    SHOOTING_SOLDIER
};

class Player : public Entity {
    private:
        SoldierState state;
        
    public:
        Player(int id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        virtual bool isInfected() override;
        virtual std::string getEntityType() override;
        virtual ~Player() override;
};
#endif
