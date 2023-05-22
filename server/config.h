#include <cstdint>
#pragma once

struct config {
    int soldier_health;
    int soldier_speed;
    int soldier_radius;
    int infected_health;
    int infected_speed;
    int infected_radius;
    int common_infected_range;
    int common_infected_speed;
    int scenario_width;
    int scenario_height;
    int default_radius;
    long int invalid_id;
};


extern const struct config CONFIG;
