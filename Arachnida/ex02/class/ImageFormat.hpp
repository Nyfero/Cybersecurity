#pragma once
#include "../inc/scorpion.h"

class BMP;
class JPG;
class GIF;
class PNG;

class ImageFormat {

    private:
        std::vector<std::string> _args;
    
    public:

    ImageFormat(std::vector<std::string> args);
    ~ImageFormat();

    int getMetaData();
};
