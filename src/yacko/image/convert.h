#pragma once

#include <ImageMagick/Magick++.h>

#include <string>

namespace Yacko {
    namespace Image {

        Magick::Blob resize(std::map<std::string, std::string> map, Magick::Image image);
        std::string getOutputFormat(std::map<std::string, std::string> map, std::string basetype);
    }
}
