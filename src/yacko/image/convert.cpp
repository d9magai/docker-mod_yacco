#include "convert.h"

namespace Yacko {
    namespace Image {

        Magick::Blob resize(std::map<std::string, std::string> map, Magick::Image image)
        {

            int w = std::stoi(map["w"]);
            int h = std::stoi(map["h"]);
            Magick::Geometry newSize = Magick::Geometry(w, h);
            newSize.aspect(false);
            image.resize(newSize);
            Magick::Blob blob;
            image.magick("JPEG");
            image.write(&blob);
            return blob;
        }
    }
}
