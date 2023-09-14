#include "ImageFormat.hpp"

class BMP {

    private:
        unsigned char   *_signature; // BMP : {0x42, 0x4D}
        std::string     _filename;

    public:
    
        BMP(std::string filename);
        ~BMP();

        int getMetaData();
};