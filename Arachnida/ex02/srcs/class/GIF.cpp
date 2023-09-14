#include "../../class/GIF.hpp"

GIF::GIF(std::string filename): _filename(filename) {
    this->_signature = new unsigned char[3];
    this->_signature[0] = 0x47;
    this->_signature[1] = 0x49;
    this->_signature[2] = 0x46;
}

GIF::~GIF() {
    delete [] this->_signature;
}

int GIF::getMetaData() {
    std::cout << "GIF::getMetaData() called for " << this->_filename << std::endl;
    
    std::ifstream file(this->_filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << this->_filename << std::endl;
        return 1;
    }

    char buf[3] = "\0";
    file.read(buf, 3);
    for (int i = 0; i < 3; i++) {
        if (static_cast<unsigned char>(buf[i]) != this->_signature[i]) {
            std::cout << "\e[91mThe file " << this->_filename << " isn't valid GIF.\e[39m" << std::endl;
            return 1;
        }
    }
    std::cout << "\e[92mThe file " << this->_filename << " is a valid GIF.\e[39m" << std::endl;
    
    return 0;
}