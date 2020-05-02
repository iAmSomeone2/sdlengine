#pragma once

#include <filesystem>

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
};
