#include "config.h"

const struct config CONFIG {
    100, // soldier_health
    10, // soldier_speed
    5, // soldier_radius
    80, // infected_health
    10, // infected_speed
    5, // infected_radius
    50, // infected_range
    10, // common_infected_speed
    15, //common_infected_attack_range
    10, // common_infected_damage
    40, // common_infected_attack_cooldown
    1920, // scenario_width
    1080, // scenario_height
    5, // default_radius
    8589934591, // invalid_id
    50, // weapon_idf_base_damage
    100, // weapon_idf_range
    1000, // weapon_idf_magazine_size
    20, // weapon_idf_burst_size
    0.5, // weapon_idf_distance_modifier 0.25
    30, // weapon_p90_base_damage
    200, // weapon_p90_range
    300, // weapon_p90_magazine_size
    10, // weapon_p90_burst_size
    0.25, // weapon_p90_distance_modifier 0.25
    100, // weapon_scout_base_damage
    1000, // weapon_scout_range
    20, // weapon_scout_magazine_size
    0, // weapon_scout_distance_modifier
    0.1 // weapon_scout_damage_falloff
};
