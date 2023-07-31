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
    YAML::Node config = YAML::LoadFile(configFile);

    TTF_Init();
    std::string img("Roboto_Condensed/RobotoCondensed-Regular.ttf");
    this->font = TTF_OpenFont((config["path_fonts"].as<std::string>()+img).c_str(), 36);

    std::string img_border("Roboto_Condensed/RobotoCondensed-Bold.ttf");
    this->font_border = TTF_OpenFont((config["path_fonts"].as<std::string>()+img_border).c_str(), 36);
}

void VisualText::render(int x_player, int y_player) {
    //border
    SDL_Color borderColor = { 255, 255, 255, 255 };

    // Create a surface with the player's name
    SDL_Surface* borderSurface = TTF_RenderText_Solid(font_border, text.c_str(), borderColor);

    // Create a texture from the surface
    SDL_Texture* borderTexture = SDL_CreateTextureFromSurface(renderer, borderSurface);

    // Get the dimensions of the text
    int borderWidth = borderSurface->w;
    int borderHeight = borderSurface->h;

    // Clean up the surface now that we have a texture
    SDL_FreeSurface(borderSurface);

    // Calculate the position for the text above the player's position
    int borderX = x_player + borderWidth /2; // Center the text horizontally above the player
    int borderY = y_player + 40; // Place the text 10 pixels above the player

    // Create an SDL_Rect to position and size the text
    SDL_Rect borderRect = { borderX, borderY, borderWidth, borderHeight };

    // Draw the text above the player's position
    SDL_RenderCopy(renderer, borderTexture, NULL, &borderRect);


    //text
    SDL_Color textColor = { 0, 0, 0, 255 };

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
    int textX = x_player + textWidth /2; // Center the text horizontally above the player
    int textY = y_player + 40; // Place the text 10 pixels above the player

    // Create an SDL_Rect to position and size the text
    SDL_Rect textRect = { textX, textY, textWidth, textHeight };

    // Draw the text above the player's position
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Clean up
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(borderTexture);
}

VisualText::~VisualText() {
    TTF_CloseFont(font);
    TTF_CloseFont(font_border);
    TTF_Quit();
}