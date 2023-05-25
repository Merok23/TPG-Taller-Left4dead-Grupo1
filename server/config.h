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
    int weapon_idf_base_damage;
    int weapon_idf_range;
    int weapon_idf_magazine_size;
    int weapon_idf_burst_size;
    double weapon_idf_distance_modifier;
};


extern const struct config CONFIG;
