#ifndef CLIENT_ENUM_H
#define CLIENT_ENUM_H

enum State {
    IDLE,
    RUN,
    SHOOT,
    RELOAD, 
    DIE,
    ATTACKING
};

enum EntityTypeGS {
    SOLDIER,
    COMMON_INFECTED,
    SPEAR_INFECTED
};

enum WeaponType {
    IDF,
    P90,
    SCOUT,
    NONE
};

enum GameMode {
    SURVIVAL,
    CLEAR_THE_ZONE
};

enum Commands {
    CREATE_ROOM,
    JOIN_ROOM,
    MOVE_PLAYER,
    SHOOT_PLAYER,
    RELOAD_PLAYER,
    ADD_PLAYER,
    CHEAT_INFINITE_HITPOINTS,
    CHEAT_SPAWN_COMMON_INFECTED,
    CHEAT_KILL_ALL_INFECTED
};
#endif
