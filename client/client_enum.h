#ifndef CLIENT_ENUM_H
#define CLIENT_ENUM_H

enum State {
    IDLE,
    RUN,
    SHOOT,
    RELOAD, 
    DIE,
    ATTACKING,
    DOWN, 
    REVIVING,
    //witch:
    SCREAMING,
    //venom:
    BLASTING,
    //projectiles:
    FLYING,
    EXPLODING,
    DESTROYED,
};

enum AnimationName {
    AN_IDLE,
    AN_WALK,
    AN_RUN,
    AN_RUN_ATTACK,
    AN_JUMP,

    AN_ATTACK1,
    AN_ATTACK2,
    AN_ATTACK3,
    AN_BITE,
    AN_SCREAM,
    AN_SHOOT,

    AN_FALL,
    AN_EATING,
    AN_PROTECT,

    AN_RELOAD,
    AN_DOWN,
    AN_HURT,
    AN_DIE,

    AN_PROJECTILE_FLYING,
    AN_PROJECTILE_EXPLODING
};

enum EntityType {
    SOLDIER_IDF,
    SOLDIER_P90,
    SOLDIER_SCOUT,

    JUMPER,
    VENOM,
    SPEAR,
    WITCH,
    ZOMBIE,

    CRATER,
    
    PROJECTILE_VENOM,
    PROJECTILE_GRENADE,
    PROJECTILE_SMOKE
};

enum GameMode {
    TESTING,
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
