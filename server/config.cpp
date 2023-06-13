#include "config.h"

const struct config CONFIG {
    100, // soldier_health
    10, // soldier_speed
    23, // soldier_radius
    20, // soldier_reload_cooldown
    15, // soldier time_to_revive
    600, // soldier_max_time_until_dead
    3, // soldier distance_to_revive
    4, // soldier_lives
    700, // soldier_max_distance_from_mass_centre
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
    50, // witch_infected_health
    3, // witch_infected_speed
    25, // witch_infected_radius
    350, // witch_infected_look_range
    60, // witch_infected_attack_range
    80, // witch_infected_attack_cooldown
    20, // witch_infected_attack_damage
    80, // witch_infected_shout_cooldown
    0.005, // witch_infected_shout_probability
    10, // witch_infected_scream_spawn_ammount
    40, // crater_radius
    100, // crater_hit_points
    6, //crater_ammount
    5760,//-400, //1920, // scenario_width
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
    2147483647, // cheat_infinite_hitpoints
    500, //survival_mode_timer
    3, //survival_mode_max_common_infected
    2, //survival_mode_max_spear_infected
    1, //survival_mode_max_witch_infected
    1.1, //survival_mode_accumulator
    1.0, //survival_mode_starting_multiplier
    10, //clear_the_zone_infected_total
    0.7, //common_infected_zone_percentage
    0.2, //spear_infected_zone_percentage
    0.1, //witch_infected_zone_percentage
    0, //jumper_infected_zone_percentage
    0 //venom_infected_zone_percentage
};
