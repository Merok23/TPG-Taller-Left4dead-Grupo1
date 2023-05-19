#include <cstdint>


class Weapon {        
    public:
        virtual uint32_t calculateDamage(uint32_t distance) = 0;
        virtual void reload() = 0;
        virtual bool isLoaded() = 0;
};
