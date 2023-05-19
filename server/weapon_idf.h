#include "weapon.h"

class MachineGun : public Weapon {
    private:
        uint32_t base_damage;
        uint32_t range;
        uint32_t magazine_size;
        uint32_t rounds_left;
        double distance_modifier;
    public:
        MachineGun(uint32_t damage, uint32_t range, uint32_t magazine_size);
        virtual uint32_t calculateDamage(uint32_t distance) override;
        virtual void reload() override;
        virtual bool isLoaded() override;

};