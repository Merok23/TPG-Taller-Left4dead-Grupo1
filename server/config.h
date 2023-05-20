#pragma once

struct config {
    int soldier_health;
    int soldier_speed;
    int soldier_radius;
    int infected_health;
    int infected_speed;
    int infected_radius;
    int scenario_width;
    int scenario_height;
    int default_radius;
};


extern const struct config CONFIG;
