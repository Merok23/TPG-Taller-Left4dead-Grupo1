#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

#include <yaml-cpp/yaml.h>

struct config {
    int soldier_health;
    int soldier_speed;
    int soldier_radius;
    int soldier_reload_cooldown;
    int soldier_time_to_revive;
    int soldier_max_time_until_dead;
    int soldier_max_distance_to_revive;
    int soldier_lives;
    double soldier_max_distance_from_mass_centre; //distance from centre of mass(average position of all players)
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
    int venom_infected_health;
    int venom_infected_speed;
    int venom_infected_radius;
    int venom_infected_look_range;
    int venom_infected_blast_range;
    int venom_infected_shoot_range;
    int venom_infected_blast_incapacitated_time;
    int venom_infected_shoot_incapacitated_time;
    int venom_infected_blast_damage;
    int venom_infected_blast_damage_timing;
    int venom_infected_shoot_damage;
    int venom_infected_shoot_timing; //time it takes from start of attack to projectile creation
    int venom_infected_blast_radius;
    int venom_infected_projectile_radius;
    int venom_infected_projectile_speed;
    int venom_infected_projectile_explosion_counter; //ammont of time from impact to dissapearing
    int witch_infected_scream_spawn_ammount; //ammount spawned per scream
    int crater_radius;
    int crater_hit_points; //it can't be hit but since it's an entity it's needed.
    int crater_ammount;
    int scenario_width;
    int scenario_height;
    int spawn_point_start_x_infected;
    int spawn_point_end_x_infected;
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
    int aligned_slack_grace;
    int survival_mode_timer;
    int survival_mode_max_common_infected;
    int survival_mode_max_spear_infected;
    int survival_mode_max_witch_infected;
    int survival_mode_max_venom_infected;
    int survival_mode_max_jumper_infected;
    double survival_mode_accumulator; //rate of spawn + stat multiplier
    double survival_mode_starting_multiplier;
    int clear_the_zone_infected_total;
    double common_infected_zone_percentage; //these should always sum 1.0
    double spear_infected_zone_percentage;
    double witch_infected_zone_percentage;
    double jumper_infected_zone_percentage;
    double venom_infected_zone_percentage;
};

extern struct config CONFIG;

class Config {    
    private:
        YAML::Node config_node;
        
        void loadConfig();
    public: 
        explicit Config(const char* configFile);
        ~Config();
};

#endif



