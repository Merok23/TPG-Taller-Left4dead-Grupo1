#include "config_parser.h"



Parser::Parser(const std::string &file_name) : file_name(file_name) {}

config Parser::setSingletonStruct(){
    YAML::Node config = YAML::LoadFile(this->file_name);
    struct config new_config;
    new_config.soldier_health = config["soldier_health"].as<int>();
    new_config.soldier_speed = config["soldier_speed"].as<int>();
    new_config.soldier_radius = config["soldier_radius"].as<int>();
    new_config.infected_health = config["infected_health"].as<int>();
    new_config.infected_speed = config["infected_speed"].as<int>();
    new_config.infected_radius = config["infected_radius"].as<int>();
    new_config.scenario_width = config["scenario_width"].as<int>();
    new_config.scenario_height = config["scenario_height"].as<int>();
    return new_config;
}