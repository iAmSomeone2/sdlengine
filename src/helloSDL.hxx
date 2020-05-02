#pragma once

#include <vector>
#include <filesystem>
#include <SDL2/SDL.h>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

namespace fs = std::filesystem;

/**
 * Starts up SDL and creates the window
 */
void init(SDL_Window** window, SDL_Surface** screenSurface);

/**
 * Loads BMP image into surface memory
 */
SDL_Surface* loadBMPSurface(const fs::path& imgPath);

SDL_Surface* loadPNGSurface(const fs::path& imgPath);

/**
 * Frees media and shuts down SDL
 */
void quit(SDL_Window** window, vector<SDL_Surface*>* surfacePtrs);
