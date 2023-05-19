#include <cstdint>
#pragma once

class VectorWrapper {
    private:
        uint32_t id;
        int32_t distance;
    public:
    //por alguna razon no me deja definirlo todo en un cpp
        VectorWrapper(uint32_t id, int32_t distance) : id(id), distance(distance) {}
        uint32_t getId(){
            return this->id;
        }
        int32_t getDistance(){
            return this->distance;
        }
        //no me deja usar el vector de C++ si no :l
        VectorWrapper& operator=(const VectorWrapper &other) {
            this->id = other.id;
            this->distance = other.distance;
            return *this;
        }
};
