#include "config.h"

const struct config CONFIG {
    100, // soldier_health
    10, // soldier_speed
    25, // soldier_radius
    20, // soldier_reload_cooldown
    15, // soldier time_to_revive
    9, // soldier max_time_to_revive
    3, // soldier distance_to_revive
    80, // infected_health
    10, // infected_speed
    25, // infected_radius
    350, // infected_range
    5, // common_infected_speed
    60, //common_infected_attack_range
    10, // common_infected_damage
    40, // common_infected_attack_cooldown
    25, // common_infected_radius
    100, // spear_infected_health
    10, // spear_infected_speed
    25, // spear_infected_radius
    350, // spear_infected_look_range
    120, // spear_infected_attack_range
    80, // spear_infected_attack_cooldown
    20, // spear_infected_damage
    40, // crater_radius
    100, // crater_hit_points
    1920-400, //1920, // scenario_width
    250,//1080, // scenario_height
    5, // default_radius
    8589934591, // invalid_id
    200, // weapon_idf_base_damage
    500, // weapon_idf_range
    1000, // weapon_idf_magazine_size
    20, // weapon_idf_burst_size
    0.2, // weapon_idf_distance_modifier 0.25
    100, // weapon_p90_base_damage
    700, // weapon_p90_range
    300, // weapon_p90_magazine_size
    10, // weapon_p90_burst_size
    0.1, // weapon_p90_distance_modifier 0.25
    200, // weapon_scout_base_damage
    1000, // weapon_scout_range
    20, // weapon_scout_magazine_size
    0, // weapon_scout_distance_modifier
    0.1, // weapon_scout_damage_falloff
    500, //survival_mode_timer
    5, //survival_mode_max_common_infected
    1.1 //survival_mode_accumulator
};
