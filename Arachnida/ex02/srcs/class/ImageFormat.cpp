#include "../../class/ImageFormat.hpp"
#include "../../class/JPG.hpp"
#include "../../class/GIF.hpp"
#include "../../class/PNG.hpp"
#include "../../class/BMP.hpp"

ImageFormat::ImageFormat(std::vector<std::string> args): _args(args) {}

ImageFormat::~ImageFormat() {}

int ImageFormat::getMetaData() {
    
    for (std::vector<std::string>::iterator it = _args.begin(); it != _args.end(); it++) {
        std::string ext = it->substr(it->find_last_of(".") + 1);
        if (ext == "jpg" || ext == "jpeg") {
            JPG jpg(*it);
            if (jpg.getMetaData())
                return 1;
        }
        else if (ext == "gif") {
            GIF gif(*it);
            if (gif.getMetaData())
                return 1;
        }
        else if (ext == "png") {
            PNG png(*it);
            if (png.getMetaData())
                return 1;
        }
        else if (ext == "bmp") {
            BMP bmp(*it);
            if (bmp.getMetaData())
                return 1;
        }
        else {
            std::cout << "Error: " << *it << " is not a valid image format" << std::endl;
            return 1;
        }

    }

    return 0;
}
