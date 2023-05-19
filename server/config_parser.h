#include <yaml-cpp/yaml.h>
#include <string>

struct config {
    int soldier_health;
    int soldier_speed;
    int soldier_radius;
    int infected_health;
    int infected_speed;
    int infected_radius;
    int scenario_width;
    int scenario_height;
    config() {
        this->soldier_health = 0;
        this->soldier_speed = 0;
        this->soldier_radius = 0;
        this->infected_health = 0;
        this->infected_speed = 0;
        this->infected_radius = 0;
        this->scenario_width = 0;
        this->scenario_height = 0;
    } 
};

class Parser {
    private:
        std::string file_name;
    public:
        explicit Parser(const std::string &file_name);
        config setSingletonStruct();
};