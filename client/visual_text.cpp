#include "visual_text.h"

#include "SdlTexture.h"
#include <string>
#include "SdlWindow.h"
#include "SdlException.h"

#include <iostream>

VisualText::VisualText(std::string text, const SdlWindow& window) :
    text(text),
    renderer(window.getRenderer()) {

    const char* envVar = std::getenv("LEFT4DEAD_CLIENT_CONFIG_FILE");
    std::string configFile;
    if (!envVar) {
        //std::cout << "Environment variable LEFT4DEAD_CLIENT_CONFIG_FILE not set. Using default value" << std::endl;
        configFile = DEFAULT_PATH_FROM_EXECUTABLE_TO_CONFIG;
    } else {
        //std::cout << "Environment variable LEFT4DEAD_CLIENT_CONFIG_FILE set. Using it" << std::endl;
        configFile = envVar;
    }
    std::cout << "1" << std::endl;
    YAML::Node config = YAML::LoadFile(configFile);

    TTF_Init();
    std::cout << "2" << std::endl;
    std::string img("Roboto_Condensed/RobotoCondensed-Light.ttf");
    this->font = TTF_OpenFont((config["path_fonts"].as<std::string>()+img).c_str(), 36);
    std::cout << "4" << std::endl;
    if (!this->font)
        throw "Error: font didnt open";
    
    std::cout << "3" << std::endl;
    std::cout << "Text is " << text << std::endl;
}

void VisualText::render(int x_player, int y_player) {
    SDL_Color textColor = { 255, 255, 255, 255 };

    // Create a surface with the player's name
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    // Create a texture from the surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get the dimensions of the text
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Clean up the surface now that we have a texture
    SDL_FreeSurface(textSurface);

    // Calculate the position for the text above the player's position
    int textX = x_player + textWidth/2; // Center the text horizontally above the player
    int textY = y_player + 40; // Place the text 10 pixels above the player

    // Create an SDL_Rect to position and size the text
    SDL_Rect textRect = { textX, textY, textWidth, textHeight };

    // Draw the text above the player's position
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Clean up
    SDL_DestroyTexture(textTexture);
}

VisualText::~VisualText() {
    TTF_CloseFont(font);
    TTF_Quit();
}