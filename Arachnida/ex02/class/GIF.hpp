#include "ImageFormat.hpp"

class GIF {

    private:
        unsigned char   *_signature; // GIF : {0x47, 0x49, 0x46}
        std::string     _filename;

    public:
    
        GIF(std::string filename);
        ~GIF();

        int getMetaData();
};