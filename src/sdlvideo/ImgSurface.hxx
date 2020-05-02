#pragma once

#include <filesystem>
#include <cstdint>
#include <SDL2/SDL.h>
#include <png.h>

namespace fs = std::filesystem;

enum class ImgType {
    PNG,
    BMP,
    Unknown
};

class ImgSurface {
public:
    explicit ImgSurface(const fs::path& imgPath);
    ~ImgSurface();
private:
    SDL_Surface* sdlSurface = nullptr;
    ImgType imgType = ImgType::BMP;

    /**
     * Reads in the first few bytes of the specified file to determine the image
     * format.
     * 
     * @param imgPath filesystem path to image file.
     * 
     * @returns the file's image type.
     */
    static ImgType determineImgType(const fs::path& imgPath);
};
