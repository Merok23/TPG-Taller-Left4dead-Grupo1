#include <cstdint>
#include <map>

class Map {
    private:
        uint32_t width;
        uint32_t height;
        std::map<uint32_t, Entity*> entities;
    public:
        Map(uint32_t width, uint32_t height);
        uint32_t getWidth();
        uint32_t getHeight();
        std::map<uint32_t, Entity> getEntities();
        void addEntity(Entity *entity);
        void removeEntity(uint32_t id);
        ~Map();
};
