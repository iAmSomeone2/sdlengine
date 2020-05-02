#include <boost/format.hpp>
#include <iostream>
#include <sstream>
#include <cstdint>

#include "helloSDL.hxx"

using boost::format;

// Screen dimension constants
static const uint32_t SCREEN_WIDTH = 640;
static const uint32_t SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
    // Set up window and rendering surface pointers
    SDL_Window* window;
    SDL_Surface* renderSurface;

    vector<SDL_Surface*> dispSurfaces;

    try {
        init(&window, &renderSurface);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what();
        exit(1);
    }

    // Load in example picture
    try{
        dispSurfaces.push_back(loadBMPSurface(fs::path("../hello.bmp")));
    } catch (const std::runtime_error& err) {
        std::cerr << err.what();
        exit(1);
    }

    SDL_FillRect(renderSurface, nullptr, SDL_MapRGB(renderSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_BlitSurface(dispSurfaces[0], nullptr, renderSurface, nullptr);

    SDL_UpdateWindowSurface(window);

    SDL_Delay(2000);

    quit(&window, &dispSurfaces);

    return 0;
}

void init(SDL_Window** window, SDL_Surface** screenSurface) {
    std::stringstream errStream;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        errStream << format("SDL could not initialize! SDL_ERROR: %s\n") % SDL_GetError();
        throw std::runtime_error(errStream.str());
    }

    // Create window
    *window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (*window == nullptr) {
        errStream << format("Window could not be created! SDL_Error: %s\n") % SDL_GetError();
        throw std::runtime_error(errStream.str());
    }

    // Get the window surface and fill it white
    *screenSurface = SDL_GetWindowSurface(*window);
}

SDL_Surface* loadBMPSurface(const fs::path& imgPath) {
    std::stringstream errStream;

    // Set up surface
    SDL_Surface* surf = nullptr;

    // Load specified image
    surf = SDL_LoadBMP(imgPath.c_str());

    if (surf == nullptr) {
        errStream << format("Unable to load image %s! SDL Error: %s\n") % imgPath.string() % SDL_GetError();
        throw std::runtime_error(errStream.str());
    }

    return surf;
}

void quit(SDL_Window** window, vector<SDL_Surface*>* surfacePtrs) {
    // Deallocate used surfaces
    for (auto surf : *surfacePtrs) {
        SDL_FreeSurface(surf);
        surf = nullptr;
    }

    // Destroy the window
    SDL_DestroyWindow(*window);
    *window = nullptr;

    // Shutdown SDL subsystems
    SDL_Quit();
}
