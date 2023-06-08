enum State {
    IDLE,
    RUN,
    SHOOT,
    RELOAD, 
    DIE,
    ATTACKING
};

enum EntityType {
    SOLDIER,
    COMMON_INFECTED,
    SPEAR
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
    DEFAULT,
    CREATE_ROOM,
    JOIN_ROOM,
    MOVE_PLAYER,
    SHOOT_PLAYER,
    RELOAD_PLAYER,
    ADD_PLAYER,
    CHEAT_INFINITE_HITPOINTS,
    CHEAT_SPAWN_COMMON_INFECTED
};

