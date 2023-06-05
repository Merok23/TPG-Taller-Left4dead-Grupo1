#include <cstdint>
#pragma once

struct config {
    int soldier_health;
    int soldier_speed;
    int soldier_radius;
    int soldier_reload_cooldown;
    int soldier_time_to_revive;
    int soldier_max_time_until_dead;
    int soldier_max_distance_to_revive;
    int infected_health;
    int infected_speed;
    int infected_radius;
    int common_infected_range; //this is the range for chasing
    int common_infected_speed;
    int common_infected_attack_range; //this one for attacking.
    int common_infected_damage;
    int common_infected_attack_cooldown;
    int common_infected_radius;
    int crater_radius;
    int crater_hit_points; //it can't be hit but since it's an entity it's needed.
    int scenario_width;
    int scenario_height;
    int default_radius;
    long int invalid_id;
    int weapon_idf_base_damage;
    int weapon_idf_range;
    int weapon_idf_magazine_size;
    int weapon_idf_burst_size;
    double weapon_idf_distance_modifier;
    int weapon_p90_base_damage;
    int weapon_p90_range;
    int weapon_p90_magazine_size;
    int weapon_p90_burst_size;
    double weapon_p90_distance_modifier;
    int weapon_scout_base_damage; 
    int weapon_scout_range; 
    int weapon_scout_magazine_size; 
    double weapon_scout_distance_modifier; 
    double weapon_scout_damage_falloff;
    int survival_mode_timer;
    int survival_mode_max_common_infected;
    double survival_mode_accumulator; //rate of spawn + stat multiplier
};


extern const struct config CONFIG;
