#include "textures_holder.h"

#include <iostream>


void TexturesHolder::create_soldier(EntityType entity_type, const std::string &path) {
    std::string img("Idle.png");
    textures_holder[entity_type][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Shoot_1.png");
    textures_holder[entity_type][AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Walk.png");
    textures_holder[entity_type][AN_WALK] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Run.png");
    textures_holder[entity_type][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Dead.png");
    textures_holder[entity_type][AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Dropping.png");
    textures_holder[entity_type][AN_DOWN] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Recharge.png");
    textures_holder[entity_type][AN_RELOAD] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

void TexturesHolder::create_infected(EntityType entity_type, const std::string &path) {
    std::string img("Idle.png");
    textures_holder[entity_type][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Walk.png");
    textures_holder[entity_type][AN_WALK] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Run.png");
    textures_holder[entity_type][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Attack_1.png");
    textures_holder[entity_type][AN_ATTACK1] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Attack_2.png");
    textures_holder[entity_type][AN_ATTACK2] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Dead.png");
    textures_holder[entity_type][AN_DIE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Hurt.png");
    textures_holder[entity_type][AN_HURT] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    switch (entity_type)
    {
    case ZOMBIE:
        create_zombie(path);
        break;
    
    case VENOM:
        create_venom(path);
        break;

    case JUMPER:
        create_jumper(path);
        break;

    case SPEAR:
        create_spear(path);
        break;

    case WITCH:
        create_witch(path);
        break;

    default:
        break;
    }

}

void TexturesHolder::create_zombie(const std::string &path) {
    std::string img("Bite.png");
    textures_holder[ZOMBIE][AN_BITE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Attack_3.png");
    textures_holder[ZOMBIE][AN_ATTACK3] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Jump.png");
    textures_holder[ZOMBIE][AN_JUMP] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

void TexturesHolder::create_venom(const std::string &path) {
    std::string img("Jump.png");
    textures_holder[VENOM][AN_JUMP] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Attack_2.png");
    textures_holder[VENOM][AN_ATTACK2] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Run.png");
    textures_holder[VENOM][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Attack_1.png");
    textures_holder[VENOM][AN_SHOOT] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

void TexturesHolder::create_jumper(const std::string &path) {
    std::string img("Eating.png");
    textures_holder[JUMPER][AN_EATING] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Attack3.png");
    textures_holder[JUMPER][AN_ATTACK3] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Jump.png");
    textures_holder[JUMPER][AN_JUMP] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

void TexturesHolder::create_spear(const std::string &path) {
    std::string img("Fall.png");
    textures_holder[SPEAR][AN_FALL] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Protect.png");
    textures_holder[SPEAR][AN_PROTECT] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Run+attack.png");
    textures_holder[SPEAR][AN_RUN_ATTACK] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

void TexturesHolder::create_witch(const std::string &path) {
    std::string img("Attack_3.png");
    textures_holder[WITCH][AN_ATTACK3] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Scream.png");
    textures_holder[WITCH][AN_SCREAM] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Run.png");
    textures_holder[WITCH][AN_RUN] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

void TexturesHolder::create_obstacle(const std::string &path) {
    std::string img("crater1.png");
    textures_holder[CRATER][AN_IDLE] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

void TexturesHolder::create_projectiles(const std::string &path) {
    std::string img("Venom/ProjectileExploding.png");
    textures_holder[PROJECTILE_VENOM][AN_PROJECTILE_EXPLODING] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Venom/ProjectileFlying.png");
    textures_holder[PROJECTILE_VENOM][AN_PROJECTILE_FLYING] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Soldier_IDF/ProjectileExplosion.png");
    textures_holder[PROJECTILE_GRENADE][AN_PROJECTILE_EXPLODING] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Soldier_IDF/ProjectileFlying.png");
    textures_holder[PROJECTILE_GRENADE][AN_PROJECTILE_FLYING] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));

    img.replace(0, img.length(), "Soldier_Scout/Smoke.png");
    textures_holder[PROJECTILE_SMOKE][AN_PROJECTILE_EXPLODING] = std::shared_ptr<SdlTexture>(new SdlTexture(path+img, window));
}

TexturesHolder::TexturesHolder(SdlWindow &window) : window(window){
    const char* envVar = std::getenv("LEFT4DEAD_CLIENT_CONFIG_FILE");
    std::string configFile;
    if (!envVar) {
        std::cout << "Environment variable LEFT4DEAD_CLIENT_CONFIG_FILE not set. Using default value" << std::endl;
        configFile = DEFAULT_PATH_FROM_EXECUTABLE_TO_CONFIG;
    } else {
        std::cout << "Environment variable LEFT4DEAD_CLIENT_CONFIG_FILE set. Using it" << std::endl;
        configFile = envVar;
    }

    this->config = YAML::LoadFile(configFile);
    
    create_soldier(SOLDIER_IDF, config["idf_textures_path"].as<std::string>());
    create_soldier(SOLDIER_SCOUT, config["scout_textures_path"].as<std::string>());
    create_soldier(SOLDIER_P90, config["p90_textures_path"].as<std::string>());

    
    create_infected(ZOMBIE, config["zombie_textures_path"].as<std::string>());
    create_infected(SPEAR, config["spear_textures_path"].as<std::string>());
    create_infected(VENOM, config["venom_textures_path"].as<std::string>());
    create_infected(WITCH, config["witch_textures_path"].as<std::string>());
    /*
    path.replace(0, path.length(), "../../assets/Jumper/");
    create_infected(JUMPER, path);
    */

    create_obstacle(config["crater_textures_path"].as<std::string>());
    create_projectiles(config["projectiles_textures_path"].as<std::string>());
    
}

std::map<AnimationName, std::shared_ptr<SdlTexture>> TexturesHolder::find_textures(EntityType entity_type) {
    return this->textures_holder.find(entity_type)->second;
}