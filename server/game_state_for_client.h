#include <cstdint>
#include <map>
#include "entity.h"


class GameStateForClient {
    private:
        std::map<uint32_t, Entity*> entities;
        uint32_t width;
        uint32_t height;
    public:
        GameStateForClient(const std::map<uint32_t, Entity*> &entities, 
            uint32_t width, uint32_t height);
        explicit GameStateForClient(GameStateForClient*& other);
        std::map<uint32_t, Entity*>& getEntities();
        uint32_t getWidth();
        uint32_t getHeight();
};
