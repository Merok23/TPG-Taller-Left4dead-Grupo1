#include "config.h"

struct config CONFIG {
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
    5, // common_infected_damage
    20, // common_infected_attack_cooldown
    25, // common_infected_radius
    6, // common_infected_attack_duration
    100, // spear_infected_health
    10, // spear_infected_speed
    25, // spear_infected_radius
    350, // spear_infected_look_range
    90, // spear_infected_attack_range
    80, // spear_infected_attack_cooldown
    20, // spear_infected_damage
    5, // spear_infected_attack_duration
    50, // witch_infected_health
    3, // witch_infected_speed
    25, // witch_infected_radius
    200, // witch_infected_look_range
    60, // witch_infected_attack_range
    80, // witch_infected_attack_cooldown
    20, // witch_infected_attack_damage
    80, // witch_infected_shout_cooldown
    0.005, // witch_infected_shout_probability
    5, // witch_infected_attack_duration
    600, // witch_infected_shout_minimum_distance
    100, // venom_infected_health
    10, // venom_infected_speed
    25, // venom_infected_radius
    600, // venom_infected_look_range
    100, // venom_infected_blast_range
    500, // venom_infected_shoot_range
    14, //venom_infected_blast_incapacitated_time
    33, // venom_infected_shoot_incapacitated_time
    30, // venom_infected_blast_damage
    7, //venom_infected_blast_damage_timing
    50, // venom_infected_shoot_damage
    32, // venom_infected_shoot_timing
    50, // venom_infected_blast_radius
    5, // venom_infected_projectile_radius
    15, // venom_infected_projectile_speed
    3, // venom_infected_projectile_explosion_counter
    10, // witch_infected_scream_spawn_ammount
    40, // crater_radius
    100, // crater_hit_points
    1, //crater_ammount
    7680,//-400, //1920, // scenario_width
    200,//1080, // scenario_height
    200, // spawn_point_start_x_infected
    5560, // spawn_point_end_x_infected    
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
    2147483637, // cheat_infinite_hitpoints
    10, //aligned_slack_grace
    100, //survival_mode_timer
    3, //survival_mode_max_common_infected
    2, //survival_mode_max_spear_infected
    1, //survival_mode_max_witch_infected
    1, //survival_mode_max_venom_infected
    1, //survival_mode_max_jumper_infected
    1.0000005, //survival_mode_accumulator
    1.0, //survival_mode_starting_multiplier
    30, //clear_the_zone_infected_total
    0.6, //common_infected_zone_percentage
    0.2, //spear_infected_zone_percentage
    0.1, //witch_infected_zone_percentage
    0, //jumper_infected_zone_percentage
    0.1 //venom_infected_zone_percentage
};

Config::Config(const char* config_file) {
    this->config_node = YAML::LoadFile(config_file);
    this->loadConfig();
}
void Config::loadConfig() {
    CONFIG.soldier_health = config_node["soldier"]["health"].as<int>();
    CONFIG.soldier_speed = config_node["soldier"]["speed"].as<int>();
    CONFIG.soldier_radius = config_node["soldier"]["radius"].as<int>();
    CONFIG.soldier_reload_cooldown = config_node["soldier"]["reload_cooldown"].as<int>();
    CONFIG.soldier_time_to_revive = config_node["soldier"]["time_to_revive"].as<int>();
    CONFIG.soldier_max_time_until_dead = config_node["soldier"]["max_time_until_dead"].as<int>();
    CONFIG.soldier_max_distance_to_revive = config_node["soldier"]["max_distance_to_revive"].as<int>();
    CONFIG.soldier_lives = config_node["soldier"]["lives"].as<int>();
    CONFIG.soldier_max_distance_from_mass_centre = config_node["soldier"]["max_distance_from_mass_centre"].as<double>();
    CONFIG.infected_health = config_node["infected"]["health"].as<int>();
    CONFIG.infected_speed = config_node["infected"]["speed"].as<int>();
    CONFIG.infected_radius = config_node["infected"]["radius"].as<int>();

    // Common Infected:
    //  Stats:
    CONFIG.common_infected_range = config_node["infected"]["common"]["range"].as<int>();
    CONFIG.common_infected_speed = config_node["infected"]["common"]["speed"].as<int>();
    CONFIG.common_infected_radius = config_node["infected"]["common"]["radius"].as<int>();
    // Attack:
    CONFIG.common_infected_attack_range = config_node["infected"]["common"]["attack_range"].as<int>();
    CONFIG.common_infected_damage = config_node["infected"]["common"]["damage"].as<int>();
    CONFIG.common_infected_attack_cooldown = config_node["infected"]["common"]["attack_cooldown"].as<int>();
    CONFIG.common_infected_attack_duration = config_node["infected"]["common"]["attack_duration"].as<int>();
    
    // Spear Infected:
    //  Stats:
    CONFIG.spear_infected_health = config_node["infected"]["spear"]["health"].as<int>();
    CONFIG.spear_infected_speed = config_node["infected"]["spear"]["speed"].as<int>();
    CONFIG.spear_infected_radius = config_node["infected"]["spear"]["radius"].as<int>();
    CONFIG.spear_infected_look_range = config_node["infected"]["spear"]["look_range"].as<int>();
    CONFIG.spear_infected_attack_duration = config_node["infected"]["spear"]["attack_duration"].as<int>();
    //  Attack:
    CONFIG.spear_infected_attack_range = config_node["infected"]["spear"]["attack_range"].as<int>();
    CONFIG.spear_infected_attack_cooldown = config_node["infected"]["spear"]["attack_cooldown"].as<int>();
    CONFIG.spear_infected_damage = config_node["infected"]["spear"]["damage"].as<int>();

    // Witch Infected:
    //  Stats:
    CONFIG.witch_infected_health = config_node["infected"]["witch"]["health"].as<int>();
    CONFIG.witch_infected_speed = config_node["infected"]["witch"]["speed"].as<int>();
    CONFIG.witch_infected_radius = config_node["infected"]["witch"]["radius"].as<int>();
    CONFIG.witch_infected_look_range = config_node["infected"]["witch"]["look_range"].as<int>();
    // Attack:
    CONFIG.witch_infected_attack_range = config_node["infected"]["witch"]["attack_range"].as<int>();
    CONFIG.witch_infected_attack_cooldown = config_node["infected"]["witch"]["attack_cooldown"].as<int>();
    CONFIG.witch_infected_attack_damage = config_node["infected"]["witch"]["attack_damage"].as<int>();
    CONFIG.witch_infected_attack_duration = config_node["infected"]["witch"]["attack_duration"].as<int>();
    // Shout:
    CONFIG.witch_infected_shout_cooldown = config_node["infected"]["witch"]["shout_cooldown"].as<int>();
    CONFIG.witch_infected_shout_probability = config_node["infected"]["witch"]["shout_probability"].as<double>();
    CONFIG.witch_infected_scream_spawn_amount = config_node["infected"]["witch"]["scream_spawn_ammount"].as<int>();
    CONFIG.witch_infected_shout_minimum_distance = config_node["infected"]["witch"]["shout_minimum_distance"].as<int>();
    
    // Venom Infected:
    //  Stats:
    CONFIG.venom_infected_health = config_node["infected"]["venom"]["health"].as<int>();
    CONFIG.venom_infected_speed = config_node["infected"]["venom"]["speed"].as<int>();
    CONFIG.venom_infected_radius = config_node["infected"]["venom"]["radius"].as<int>();
    // Attacks:
    CONFIG.venom_infected_look_range = config_node["infected"]["venom"]["look_range"].as<int>();
    CONFIG.venom_infected_blast_range = config_node["infected"]["venom"]["blast_range"].as<int>();
    CONFIG.venom_infected_shoot_range = config_node["infected"]["venom"]["shoot_range"].as<int>();
    CONFIG.venom_infected_blast_incapacitated_time = config_node["infected"]["venom"]["blast_incapacitated_time"].as<int>();
    CONFIG.venom_infected_shoot_incapacitated_time = config_node["infected"]["venom"]["shoot_incapacitated_time"].as<int>();
    CONFIG.venom_infected_blast_damage = config_node["infected"]["venom"]["blast_damage"].as<int>();
    CONFIG.venom_infected_blast_damage_timing = config_node["infected"]["venom"]["blast_damage_timing"].as<int>();
    CONFIG.venom_infected_shoot_damage = config_node["infected"]["venom"]["shoot_damage"].as<int>();
    CONFIG.venom_infected_shoot_timing = config_node["infected"]["venom"]["shoot_timing"].as<int>();
    CONFIG.venom_infected_blast_radius = config_node["infected"]["venom"]["blast_radius"].as<int>();
    CONFIG.venom_infected_projectile_radius = config_node["infected"]["venom"]["projectile_radius"].as<int>();
    CONFIG.venom_infected_projectile_speed = config_node["infected"]["venom"]["projectile_speed"].as<int>();
    CONFIG.venom_infected_projectile_explosion_counter = config_node["infected"]["venom"]["projectile_explosion_counter"].as<int>();

    CONFIG.crater_radius = config_node["crater"]["radius"].as<int>();
    CONFIG.crater_hit_points = config_node["crater"]["hit_points"].as<int>();
    CONFIG.crater_amount = config_node["crater"]["ammount"].as<int>();
    CONFIG.scenario_width = config_node["scenario"]["width"].as<int>();
    CONFIG.scenario_height = config_node["scenario"]["height"].as<int>();
    CONFIG.spawn_point_start_x_infected = config_node["scenario"]["spawn_point_start_x_infected"].as<int>();
    CONFIG.spawn_point_end_x_infected = config_node["scenario"]["spawn_point_end_x_infected"].as<int>();
    CONFIG.default_radius = config_node["general"]["default_radius"].as<int>();
    CONFIG.invalid_id = config_node["general"]["invalid_id"].as<long int>();
    CONFIG.weapon_idf_base_damage = config_node["weapon"]["idf"]["base_damage"].as<int>();
    CONFIG.weapon_idf_range = config_node["weapon"]["idf"]["range"].as<int>();
    CONFIG.weapon_idf_magazine_size = config_node["weapon"]["idf"]["magazine_size"].as<int>();
    CONFIG.weapon_idf_burst_size = config_node["weapon"]["idf"]["burst_size"].as<int>();
    CONFIG.weapon_idf_distance_modifier = config_node["weapon"]["idf"]["distance_modifier"].as<double>();
    CONFIG.weapon_p90_base_damage = config_node["weapon"]["p90"]["base_damage"].as<int>();
    CONFIG.weapon_p90_range = config_node["weapon"]["p90"]["range"].as<int>();
    CONFIG.weapon_p90_magazine_size = config_node["weapon"]["p90"]["magazine_size"].as<int>();
    CONFIG.weapon_p90_burst_size = config_node["weapon"]["p90"]["burst_size"].as<int>();
    CONFIG.weapon_p90_distance_modifier = config_node["weapon"]["p90"]["distance_modifier"].as<double>();
    CONFIG.weapon_scout_base_damage = config_node["weapon"]["scout"]["base_damage"].as<int>();
    CONFIG.weapon_scout_range = config_node["weapon"]["scout"]["range"].as<int>();
    CONFIG.weapon_scout_magazine_size = config_node["weapon"]["scout"]["magazine_size"].as<int>();
    CONFIG.weapon_scout_distance_modifier = config_node["weapon"]["scout"]["distance_modifier"].as<double>();
    CONFIG.weapon_scout_damage_falloff = config_node["weapon"]["scout"]["damage_falloff"].as<double>();
    CONFIG.cheat_infinite_hitpoints = config_node["cheats"]["infinite_hitpoints"].as<int>();
    CONFIG.aligned_slack_grace = config_node["aligned_slack_grace"].as<int>();
    CONFIG.survival_mode_timer = config_node["modes"]["survival"]["timer"].as<int>();
    CONFIG.survival_mode_max_common_infected = config_node["modes"]["survival"]["max_common_infected"].as<int>();
    CONFIG.survival_mode_max_spear_infected = config_node["modes"]["survival"]["max_spear_infected"].as<int>();
    CONFIG.survival_mode_max_witch_infected = config_node["modes"]["survival"]["max_witch_infected"].as<int>();
    CONFIG.survival_mode_max_jumper_infected = config_node["modes"]["survival"]["max_jumper_infected"].as<int>();
    CONFIG.survival_mode_max_venom_infected = config_node["modes"]["survival"]["max_venom_infected"].as<int>();
    CONFIG.survival_mode_accumulator = config_node["modes"]["survival"]["accumulator"].as<double>();
    CONFIG.survival_mode_starting_multiplier = config_node["modes"]["survival"]["starting_multiplier"].as<double>();
    CONFIG.clear_the_zone_infected_total = config_node["modes"]["clear_the_zone"]["infected_total"].as<int>();
    CONFIG.common_infected_zone_percentage = config_node["zone_percentages"]["common_infected"].as<double>();
    CONFIG.spear_infected_zone_percentage = config_node["zone_percentages"]["spear_infected"].as<double>();
    CONFIG.witch_infected_zone_percentage = config_node["zone_percentages"]["witch_infected"].as<double>();
    CONFIG.jumper_infected_zone_percentage = config_node["zone_percentages"]["jumper_infected"].as<double>();
    CONFIG.venom_infected_zone_percentage = config_node["zone_percentages"]["venom_infected"].as<double>();
}

