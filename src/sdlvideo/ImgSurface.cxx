#include <fstream>
#include <sstream>

#include <boost/format.hpp>

#include "ImgSurface.hxx"

using boost::format;

ImgSurface::ImgSurface(const fs::path& imgPath) {
    std::stringstream errStream;

    try{
        this->imgType = ImgSurface::determineImgType(imgPath);
    } catch (const std::runtime_error& err) {
        throw err;
    }

    switch(this->imgType) {
        case ImgType::BMP:
            this->sdlSurface = SDL_LoadBMP(imgPath.c_str());

            if (this->sdlSurface == nullptr) {
                errStream << format("Unable to load image %s! SDL Error: %s") % imgPath.string() % SDL_GetError();
                throw std::runtime_error(errStream.str());
            }
            break;
        case ImgType::PNG:
            // Convert image to BMP in memory, then load into SDL.
            break;
        default:
            errStream << "Unrecognized image format.";
            throw std::runtime_error(errStream.str());
    }
}

ImgSurface::~ImgSurface() {
    SDL_FreeSurface(this->sdlSurface);
    this->sdlSurface = nullptr;
}

ImgType ImgSurface::determineImgType(const fs::path& imgPath) {
    std::stringstream errStream;

    std::ifstream imgStream = std::ifstream(imgPath, std::ios::binary | std::ios::ate);
    
    if (!imgStream.is_open()) {
        errStream << format("Failed to open image: %s") % imgPath.string();
        throw std::runtime_error(errStream.str());
    }

    uint32_t imgSize = imgStream.tellg();
    imgStream.seekg(std::ios::beg);

    // We only need the first 8 bytes for signature checking.
    std::unique_ptr<char> buff = std::unique_ptr<char>(new char[9]);
    buff.get()[8] = '\0';
    imgStream.readsome(buff.get(), 8);
    imgStream.close();

    // Check if PNG image first
    if(!png_sig_cmp(reinterpret_cast<png_const_bytep>(buff.get()), 0, 8)) {
        return ImgType::PNG;
    }

    // Check if bitmap
    if(!strncmp(buff.get(), "BM", 2)) {
        return ImgType::BMP;
    }

    return ImgType::Unknown;
}
