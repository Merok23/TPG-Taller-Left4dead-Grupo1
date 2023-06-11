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
    int soldier_lives;
    int infected_health; //this is health is only for the common infected!
    int infected_speed;
    int infected_radius;
    int common_infected_range; //this is the range for chasing
    int common_infected_speed;
    int common_infected_attack_range; //this one for attacking.
    int common_infected_damage;
    int common_infected_attack_cooldown;
    int common_infected_radius;
    int spear_infected_health;
    int spear_infected_speed;
    int spear_infected_radius;
    int spear_infected_look_range;
    int spear_infected_attack_range;
    int spear_infected_attack_cooldown;
    int spear_infected_damage;
    int witch_infected_health;
    int witch_infected_speed;
    int witch_infected_radius;
    int witch_infected_look_range;
    int witch_infected_attack_range;
    int witch_infected_attack_cooldown;
    int witch_infected_attack_damage;
    int witch_infected_shout_cooldown;
    double witch_infected_shout_probability;
    int witch_infected_scream_spawn_ammount; //ammount spawned per scream
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
    int cheat_infinite_hitpoints;
    int survival_mode_timer;
    int survival_mode_max_common_infected;
    int survival_mode_max_spear_infected;
    int survival_mode_max_witch_infected;
    double survival_mode_accumulator; //rate of spawn + stat multiplier
    double survival_mode_starting_multiplier;
    int clear_the_zone_infected_total;
    double common_infected_zone_percentage; //these should always sum 1.0
    double spear_infected_zone_percentage;
    double witch_infected_zone_percentage;
    double jumper_infected_zone_percentage;
    double venom_infected_zone_percentage;
};


extern const struct config CONFIG;
