#include "visual_text.h"
#include "SdlTexture.h"
#include <string>
#include "SdlWindow.h"
#include "SdlException.h"

#include <iostream>

VisualText::VisualText(std::string text, const SdlWindow& window, int player_len) :
    text(text),
    renderer(window.getRenderer()),
    player_len(player_len) {

    const char* envVar = std::getenv("LEFT4DEAD_CLIENT_CONFIG_FILE");
    std::string configFile;
    if (!envVar) {
        configFile = DEFAULT_PATH_FROM_EXECUTABLE_TO_CONFIG;
    } else {
        configFile = envVar;
    }
    YAML::Node config = YAML::LoadFile(configFile);

    TTF_Init();
    std::string img("Roboto_Condensed/RobotoCondensed-Bold.ttf");
    this->font = TTF_OpenFont((config["path_fonts"].as<std::string>() + img).c_str(), 34);

    std::string img_border("Roboto_Condensed/RobotoCondensed-Bold.ttf");
    this->font_border = TTF_OpenFont((config["path_fonts"].as<std::string>() + img_border).c_str(), 40);

    // Set the outline size for the text (this will create the border effect)
    TTF_SetFontOutline(font_border, 1); // Change the "1" to adjust the border thickness

    // Inside color (fill color for the letters)
    SDL_Color insideColor = { 255, 255, 255, 255 };

    // Create a surface with the player's name with antialiased blending (for the inside of letters)
    SDL_Surface* insideSurface = TTF_RenderText_Blended(font, text.c_str(), insideColor);
    this->insideTexture = SDL_CreateTextureFromSurface(renderer, insideSurface);

    // Border color
    SDL_Color borderColor =  { 0, 0, 0, 255 };

    // Create a surface with the player's name (for the border)
    SDL_Surface* borderSurface = TTF_RenderText_Solid(font_border, text.c_str(), borderColor);
    this->borderTexture = SDL_CreateTextureFromSurface(renderer, borderSurface);

    // Get the dimensions of the text
    this->textWidth = insideSurface->w; // We use the insideSurface for dimensions since it has antialiasing
    this->textHeight = insideSurface->h;

    // Calculate the position for the text and the border above the player's position
    int x_player = 0; // Change this to adjust the x-coordinate of the player's position
    int y_player = 0; // Change this to adjust the y-coordinate of the player's position
    int textX = x_player + textWidth ; // Center the text horizontally above the player
    int textY = y_player + 40; // Place the text 40 pixels above the player (you can change this)

    // Create an SDL_Rect to position and size the text and the border
    this->textRect = { textX, textY, textWidth, textHeight };
    this->borderRect = { textX - 2, textY - 2, textWidth + 4, textHeight + 4 }; // Add the desired border thickness

    // Set the positions and dimensions of the inside texture and border texture

    textRect.x += 2; // Offset the inside text by 2 pixels (to match the border position)

    // Clean up the surface now that we have textures
    // (note: don't clean up insideSurface and borderSurface here since we need them for dimensions)
    SDL_FreeSurface(insideSurface);
    SDL_FreeSurface(borderSurface);
}

void VisualText::render(int x_player, int y_player) {
    // Update the positions based on the player's coordinates (if needed)
    textRect.x = x_player + player_len/2 - textWidth/2; // Center the text horizontally above the player with 2-pixel offset
    textRect.y = y_player + 40;
    borderRect.x = textRect.x - 2;
    borderRect.y = textRect.y - 2;

    // Draw the border first
    SDL_RenderCopy(renderer, borderTexture, NULL, &borderRect);

    // Then, draw the inside texture (filled letters)
    SDL_RenderCopy(renderer, insideTexture, NULL, &textRect);
}

VisualText::~VisualText() {
    SDL_DestroyTexture(insideTexture);
    SDL_DestroyTexture(borderTexture);
    TTF_CloseFont(font);
    TTF_CloseFont(font_border);
    TTF_Quit();
}
