#include "../inc/scorpion.h"

class JPG {

    private:
        unsigned char   *_signature; // JPG : {0xFFu, 0xD8u} 
        std::string     _filename;

    public:
    
        JPG(std::string filename);
        ~JPG();

        int getMetaData();
};