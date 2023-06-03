#include "entity.h"

class Crater : public Entity {
    public:
        Crater(uint32_t id, uint32_t positionX, uint32_t positionY);
        virtual void move(int32_t x_movement, int32_t y_movement) override;
        virtual void update(Map& map) override;
        virtual void shoot(std::vector<HitEntity>& entities_hit) override;
        virtual bool isInfected() override;
        virtual std::string getEntityType() override;
        virtual bool isDead() override;
        virtual std::string getState() override;
};
