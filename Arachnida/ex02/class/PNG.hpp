#include "ImageFormat.hpp"

class PNG {

    private:
        unsigned char   *_signature; // = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}; // PNG : {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}
        std::string     _filename;

    public:
    
        PNG(std::string filename);
        ~PNG();

        int getMetaData();
};